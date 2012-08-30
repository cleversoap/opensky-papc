int Function test()
    int f = 2
endFunction

double Function test2()
    double l = 3.0
    int f = 4
    test()
    f = 3
endFunction

double Function test3()
    test2()
endFunction

Event onSomething()
    int x = 2
endEvent

Function tFunc()
    double v = 0.0
endFunction

double Function retTest(int t)
    return t + 10
endFunction

int x = retTest(20)
