#include <windows.h>
#include <tchar.h>
#include <iostream>

#include "Q:/ToolKit/WL/WinlicenseSDK/Include/C/winlicensesdk.h"
using namespace std;

int main()
{
    int Status = WLRegGetStatus(NULL);
    if (Status == wlIsRegistered)
        printf("��ע��!\n");
    else
        printf("δע��!\n");
    getchar();
    return 0;
}


int __stdcall myWLRegGetStatus()
{
    return wlIsRegistered;
}
