// apisimulate.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <windows.h>
int _tmain(int argc, _TCHAR* argv[])
{
	//��������һ�����ָ��ʹ���������ѭ��״̬�����������õ�������λ�����Ӧ�Ļ��ָ��λ��
	__asm jmp $
	//�������ʽ�������ǽ���ֱ�Ӵ�ӡ������ID,����ʹ��GetCurrentProcessIDϵͳ����
	//���ǵ�Ŀ�����ڹ۲�Asprotect����ϵͳ�Ըú������еĺ���ģ��
	printf("Current ProcessID:%d\n", GetCurrentProcessId());
	return 0;
}

