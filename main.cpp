#include "APP/App.h"

// #pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

int main()
{
    App a;
    if(!a.init()) return -1;
    a.Run();
    return 0;
}