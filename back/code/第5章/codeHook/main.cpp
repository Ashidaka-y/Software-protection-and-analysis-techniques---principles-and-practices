#include <windows.h>

#pragma comment(linker,"/SECTION:.text,ERW")
void func1()
{
    MessageBoxA(0,"��Ϣ1","��ʾ",MB_OK);
}

void hookedproc()
{
    MessageBoxA(0,"Hooked��Ϣ","��ʾ",MB_OK);
}
void* glpCode = 0;
void __declspec(naked) hookentry()
{
    __asm{
        pushfd
        pushad
        call hookedproc
        popad
        popfd
        jmp glpCode
    }
}

BYTE gCodeBackup[32];
void hookproc1()
{
    __asm int 3	//��λָ������ֱ���õ��Ե��Զ�λ������۲�Ч��
    //ȡ��func1��ڵ�ַ��Ҳ�ǵ�һ�л��ָ���ַ
    BYTE* lpFunc1 = (BYTE*)func1;
    //���������Ѿ�Ԥ�ȼ�������ǻ�Ӱ��6���ֽڵ�ԭʼָ���С
    memcpy(gCodeBackup,lpFunc1,6);

    //����һ�ο�ִ���ڴ�ռ���ԭʼָ��Ƭ��
    glpCode = (void*)VirtualAlloc(0,1000,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
    //Ǩ��ԭʼָ��Ƭ�ε����ڴ�ռ�
    //�˴�Ϊָ��Ǩ�ƴ��룬��Ҫ��Ƶ�������λ����
    DWORD szMove = 16;
    BYTE* lpTemp = (BYTE*)glpCode;
    int len = 0;
    int pos = 0;
    do
    {
        //��ʾ����Ҫ�������н��LDE����
        len = LDE64((BYTE*)(lpFunc1+pos));
        BYTE* codeIP	=	lpFunc1+pos;
        //������jmc
        if ((BYTE)codeIP[0] >= 0x70 && (BYTE)codeIP[0] <= 0x7F )
        {
            WORD*	pJmpCode	=	(WORD*)(lpTemp);
            *pJmpCode			=	(codeIP[0] * 0x100) + 0x100F;
            *(ULONG*)(lpTemp+2) = *(ULONG*)((ULONG)codeIP+1)+(ULONG)codeIP-(ULONG)lpTemp;
            lpTemp+=6;
        }else if ((BYTE)codeIP[0] == 0x0F &&((BYTE)codeIP[1] >= 0x80 && (BYTE)codeIP[1] <= 0x8F))
        {
            //������jmc
            *(WORD*)(lpTemp) = *(WORD*)codeIP;
            *(ULONG_PTR*)(lpTemp+2) = *(ULONG_PTR*)((ULONG)codeIP+2)+(ULONG)codeIP-(ULONG)lpTemp;
            lpTemp+=6;
        }
        else if((BYTE)codeIP[0] == 0xE9 || (BYTE)codeIP[0] == 0xE8)
        {
            //����jmp,CALL
            *(lpTemp) = codeIP[0];
            *(ULONG*)(lpTemp+1) = *(ULONG*)((ULONG)codeIP+1)+(ULONG)codeIP-(ULONG)lpTemp;
            lpTemp+=5;
        }
        else
        {
            //����ָ��ֱ�Ӹ���
            memcpy((char*)(lpTemp),(char*)(lpFunc1+pos),len);
            lpTemp+=len;
        }
        pos += len;
    } while(pos<6);

    //��Ǩ�ƺ��ָ��Ƭ�κ��������ת����ת��ԭʼָ������
    BYTE* lpCode = (BYTE*)glpCode+pos;
    lpCode[0] = 0x68;
    *(ULONG_PTR*)&lpCode[1] = (ULONG_PTR)lpFunc1+szMove;
    lpCode[5] = 0xC3;
    //HOOK����ָ��
    lpFunc1[0] = 0x68;
    *(ULONG_PTR*)&lpFunc1[1] = (ULONG_PTR)hookentry;
    lpFunc1[5] = 0xC3;
}

void unhookproc1()
{
    BYTE* lpFunc1 = (BYTE*)func1;
    memcpy(lpFunc1,gCodeBackup,6);
}

int main()
{
    hookproc1();
    func1();
    return 0;
}

