#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    cout << "�밴���������!" << endl;
    DebugBreak();
    if (getchar())
        cout << "����1!" << endl;
    else
        cout << "����2!" << endl;
    //��ͣ���򷽱�鿴���
    getchar();
    return 0;
}

