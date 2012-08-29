#include "node.h"
#include "codegen.h"
#include "parser.hpp"

using namespace std;

// Compile the AST into a module
void CodeGenContext::generateCode(NBlock &root)
{
	std::cout << "Generating code..." << std::endl;

	// Create the top level interpreter function to call as entry
	vector<const Type*> argTypes;
	FunctionType* ftype = FunctionType::get(Type::getVoidTy(getGlobalContext()), argTypes, false);
	mainFunction = Function::Create(ftype, GlobalValue::InternalLinkage, "main", module);
	BasicBlock* bblock = BasicBlock::Create(getGlobalContext(), "entry", mainFunction, 0);

	// Push a new variable/block context
	pushBlock(bblock);
	root.codeGen(*this); // emit bytecode for the toplevel block
	ReturnInst::Create(getGlobalContext(), bblock);
	popBlock();

	// Print the bytecode in a human-readable format to see if our program compiled properly
	std::cout << "Code is generated." << std::endl;
	PassManager pm;
	pm.add(createPrintModulePass(&outs()));
	pm.run(*module);
}

// Executes the AST by running the main function
GenericValue CodeGenContext::runCode()
{
	std::cout << "Running code..." << std::endl;
	ExistingModuleProvider* mp = new ExistingModuleProvider(module);
	ExecutionEngine* ee = ExecutionEngine::create(mp, false);
	vector<GenericValue> noargs;
	GenericValue v = ee->runFunction(mainFunction, noargs);
	std::cout << "Code was run." << std::endl;
	return v;
}

// Returns an LLVM type based on the identifier
static const Type* typeOf(const NIdentifier &type)
{
    if (type.name.compare("void") == 0)
    {
        return Type::getVoidTy(getGlobalContext());
    }
    else if (type.name.compare("int") == 0 || type.name.compare("Int") == 0)
	{
		return Type::getInt64Ty(getGlobalContext());
	}
	else if (type.name.compare("double") == 0 || type.name.compare("Double") == 0)
	{
		return Type::getDoubleTy(getGlobalContext());
	}
    else if (type.name.compare("float") == 0 || type.name.compare("Float") == 0)
    {
        return Type::getFloatTy(getGlobalContext()); // Still is parsed like a double - may remove if it's not in Pap spec
    }
	else
	{
		return Type::getVoidTy(getGlobalContext());
	}
}

//------------------------------------------------------------------------------- [ CODE GENERATION ]

Value* NInteger::codeGen(CodeGenContext &context)
{
	std::cout << "Creating integer:\t" << value << std::endl;
	return ConstantInt::get(Type::getInt64Ty(getGlobalContext()), value, true);
}

Value* NDouble::codeGen(CodeGenContext &context)
{
	std::cout << "Creating double:\t" << value << std::endl;
	return ConstantFP::get(Type::getDoubleTy(getGlobalContext()), value);
}

Value* NIdentifier::codeGen(CodeGenContext &context)
{
	std::cout << "Creating identifier reference:\t" << name << std::endl;
	if (context.locals().find(name) == context.locals().end())
	{
		std::cerr << "Undeclared variable " << name << std::endl;
		return NULL;
	}
	else
	{
		return new LoadInst(context.locals()[name], "", false, context.currentBlock());
	}
}

Value* NMethodCall::codeGen(CodeGenContext &context)
{
	Function* function = context.module->getFunction(id.name.c_str());
	if (function == NULL)
	{
		std::cerr << "No such function " << id.name << std::endl;
	}

	std::vector<Value*> args;
	ExpressionList::const_iterator it;
	for (it = arguments.begin(); it != arguments.end(); it++)
	{
		args.push_back((**it).codeGen(context));
	}
	CallInst* call = CallInst::Create(function, args.begin(), args.end(), "", context.currentBlock());
	std::cout << "Creating method call:\t" << id.name << std::endl;
	return call;
}

Value* NBinaryOperator::codeGen(CodeGenContext &context)
{
	std::cout << "Creating binary operation:\t" << op << std::endl;
	Instruction::BinaryOps instr;
	switch(op)
	{
		case TPLUS:
			instr = Instruction::Add;
		break;

		case TMINUS:
			instr = Instruction::Sub;
		break;

		case TMUL:
			instr = Instruction::Mul;
		break;

		case TDIV:
			instr = Instruction::SDiv;
		break;

		// TODO: Comparison

		default:
			return NULL;
	}

	return BinaryOperator::Create(instr, lhs.codeGen(context), rhs.codeGen(context), "", context.currentBlock());
}

Value* NAssignment::codeGen(CodeGenContext &context)
{
	std::cout << "Creating assignment for:\t" << lhs.name << std::endl;
	if (context.locals().find(lhs.name) == context.locals().end())
	{
		std::cerr << "Undeclared variable:\t" << lhs.name << std::endl;
		return NULL;
	}
	return new StoreInst(rhs.codeGen(context), context.locals()[lhs.name], false, context.currentBlock());
}

Value* NBlock::codeGen(CodeGenContext &context)
{
	StatementList::const_iterator it;
	Value* last = NULL;
	for (it = statements.begin(); it != statements.end(); it++)
	{
		std::cout << "Generating code for " << typeid(**it).name() << std::endl;
		last = (**it).codeGen(context);
	}

	std::cout << "Creating block" << std::endl;
	return last;
}

Value* NExpressionStatement::codeGen(CodeGenContext &context)
{
	std::cout << "Generating code for:\t" << typeid(expression).name() << std::endl;
	return expression.codeGen(context); 
}

Value* NVariableDeclaration::codeGen(CodeGenContext &context)
{
	std::cout << "Creating variable declaration:\t" << type.name << " " << id.name << std::endl;
	AllocaInst* alloc = new AllocaInst(typeOf(type), id.name.c_str(), context.currentBlock());
	context.locals()[id.name] = alloc;
	if (assignmentExpr != NULL)
	{
		NAssignment assn(id, *assignmentExpr);
		assn.codeGen(context);
	}
	return alloc;
}

Value* NFunctionDeclaration::codeGen(CodeGenContext &context)
{
    std::cout << "Generating code for function " << typeOf(type) << std::endl;
	vector<const Type*> argTypes;
	VariableList::const_iterator it;
	for (it = arguments.begin(); it != arguments.end(); it++)
	{
		argTypes.push_back(typeOf((**it).type));
	}
	FunctionType* ftype = FunctionType::get(typeOf(type), argTypes, false);
	Function* function = Function::Create(ftype, GlobalValue::InternalLinkage, id.name.c_str(), context.module);
	BasicBlock* bblock = BasicBlock::Create(getGlobalContext(), "entry", function, 0);

	context.pushBlock(bblock);

	for (it = arguments.begin(); it != arguments.end(); it++)
	{
		(**it).codeGen(context);
	}

	block.codeGen(context);
	ReturnInst::Create(getGlobalContext(), bblock);

	context.popBlock();
	std::cout << "Creating function:\t" << id.name << std::endl;
	return function;
}
