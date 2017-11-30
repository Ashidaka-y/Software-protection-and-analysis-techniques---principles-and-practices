#include <windows.h>
#include <iostream>
#include <TlHelp32.h>

using namespace std;


typedef NTSTATUS (NTAPI* LPNtQueryInformationProcess)(
        IN HANDLE hProcess,
        IN INT/*PROCESSINFOCLASS*/ ProcessInfoClass,
        OUT PVOID ProcessInfoBuffer,
        IN ULONG ProcessInfoBufferLength,
        OUT PULONG BytesReturned OPTIONAL
        );

int main()
{
    //�������
    if (IsDebuggerPresent())
        cout << "���̴��ڱ�����״̬!" << endl;

    LPNtQueryInformationProcess lpNtQueryInformationProcess =
            (LPNtQueryInformationProcess)GetProcAddress(
                GetModuleHandleA("NTDLL"),
                "NtQueryInformationProcess");
    DWORD dbgPort = 0;
    lpNtQueryInformationProcess(GetCurrentProcess(),
                                5/*ProcessDebugPort*/,
                                &dbgPort,
                                sizeof(dbgPort),0);
    if (dbgPort != 0)
    {
        cout << "���̴��ڱ�����״̬!" << endl;
    }
    //���ݼ��
    BOOL BeingDebug = FALSE;
    //    __asm{
    //        mov eax,dword ptr fs:[018h]
    //            mov eax,dword ptr [eax+030h]
    //            movzx eax,byte ptr [eax+2]
    //            mov BeingDebug,eax

    //    }
    if (BeingDebug)
    {
        cout << "���̴��ڱ�����״̬!" << endl;
    }

    //���ż��
    HANDLE hDevice = CreateFileA("\\\\.\\PROCEXP152",
                                 GENERIC_READ,
                                 FILE_SHARE_READ,
                                 0,OPEN_EXISTING,0,0);
    if (hDevice)
    {
        cout << "��⵽���̲鿴��!" << endl;
    }

    //���ڼ��
    HWND hwnd = FindWindowA("OllyDbg",0);
    if (hwnd)
    {
        cout << "��⵽ollydbg��������������!" << endl;
    }

    //��������
    BYTE sign[] = {0x41, 0x00, 0x62, 0x00, 0x6F, 0x00, 0x75, 0x00, 0x74, 0x00,
                   0x20, 0x00, 0x4F, 0x00, 0x6C, 0x00, 0x6C, 0x00, 0x79, 0x00,
                   0x44, 0x00, 0x62, 0x00, 0x67, 0x00, 0x00, 0x00, 0x4F, 0x00,
                   0x4B, 0x00, 0x00, 0x00};

    PROCESSENTRY32 sentry32 = {0};
    sentry32.dwSize = sizeof(sentry32);
    HANDLE phsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

    Process32First(phsnap,&sentry32);
    do{

        HANDLE hps = OpenProcess(MAXIMUM_ALLOWED,FALSE,sentry32.th32ProcessID);
        if (hps != 0)
        {
            DWORD szReaded = 0;
            BYTE signRemote[sizeof(sign)];
            ReadProcessMemory(hps,(LPCVOID)0x4F632A,signRemote,
                              sizeof(signRemote),&szReaded);
            if (szReaded > 0)
            {
                if (memcmp(sign,signRemote,sizeof(sign)) == 0)
                {
                    cout << "��⵽ollydbg��������������!" << endl;
                    break;
                }
            }
        }
        sentry32.dwSize = sizeof(sentry32);
    }while(Process32Next(phsnap,&sentry32));
    CloseHandle(phsnap);

    return 0;
}

