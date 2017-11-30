#include "xapispy.h"
#include <QApplication>
#include <QProcess>
#include "bookcover.h"

#define _ENABLE_BOOK_MODE

#ifdef _ENABLE_BOOK_MODE
#pragma comment(lib,"Q:/ToolKit/VMProtect/Lib/COFF/VMProtectSDK32.lib")
#include "Q:/ToolKit/VMProtect/Include/C/VMProtectSDK.h"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("xApiSpy");
    app.setApplicationName("xApiSpy");
#ifdef _ENABLE_BOOK_MODE
    VMProtectBeginUltra("VM Mark");    //VMProtect SDK�������
    BookCover bkcov;
#endif


    QSettings settings;
    QByteArray st = settings.value("winpos").toByteArray();
    xApiSpy win;
    if (!st.isEmpty())
        win.restoreState(st);
#ifdef _ENABLE_BOOK_MODE
    srand(GetTickCount());
    while(true)
    {
        int idx = rand() % 17;
        int idx2 = rand() % 13;
        wchar_t chaptitles[18][50] =
        {
            L"�����������",
            L"�������ϵͳ",
            L"�������ǿ��",
            L"����ƽ⹤��",
            L"����ƽ⼼��",
            L"�����������",
            L"���캯��������",
            L"������Դ�ؽ�����",
            L"�����ض�λ�޸�����",
            L"����������ջ�",
            L"���캯��ͨ��׷����",
            L"����Ԥִ�е�����",
            L"����α������",
            L"VMPROTECT���������",
            L"WINLICENSE���������",
            L"VMPROTECT�ѿ�",
            L"WINLICENSE�ѿ�"
        };
        wchar_t chaptitles2[13][50] =
        {
            L"�������⻯ԭ��",
            L"ģ�����⻯",
            L"�Զ�������ԭ��",
            L"�����滻����",
            L"�����Զ�����������",
            L"����������ṹ����",
            L"OP��֧�����Է���",
            L"�ԱȲ��Է���",
            L"ʵʱ��ط���",
            L"OPʵʱ���Է���",
            L"Winlicense 2.3.2 ����",
            L"VMProtect����",
            L"xVMDebug���"
        };
            bkcov.setTip(idx+1);
            bkcov.setTip2(idx2+1);
        if (bkcov.exec() != QDialog::Accepted)
            return -1;
        int nbook =bkcov.getBookIndex();
        QString sText = bkcov.inputText(nbook).trimmed();
        if (sText.isEmpty())
            return -1;

        QString sComp = QString::fromWCharArray((nbook==0)?chaptitles[idx]:chaptitles2[idx2]);
        if (sComp.compare(sText,Qt::CaseInsensitive) == 0)
        {
            win.show();
            app.exec();
            break;
        }
    }
    VMProtectEnd();
#else
    win.show();
    app.exec();
#endif
    return 0;
}
