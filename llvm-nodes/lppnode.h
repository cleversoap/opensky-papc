class LPPNode : public PPNode
{
    public:
        virtual llvm::Value* codeGen(CodeGenContext &context);
}
