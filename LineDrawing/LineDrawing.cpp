#include "pch.h"
#include "framework.h"
#include "LineDrawing.h"
#include "MainFrm.h"
#include "LineDrawingDoc.h"
#include "LineDrawingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CLineDrawingApp, CWinApp)
    ON_COMMAND(ID_APP_ABOUT, &CLineDrawingApp::OnAppAbout)
    ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
END_MESSAGE_MAP()

CLineDrawingApp::CLineDrawingApp() noexcept
{
    m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}

CLineDrawingApp theApp;

BOOL CLineDrawingApp::InitInstance()
{
    CWinApp::InitInstance();

    EnableTaskbarInteraction(FALSE);

    SetRegistryKey(_T("LineDrawing Application"));

    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(CLineDrawingDoc),
        RUNTIME_CLASS(CMainFrame),
        RUNTIME_CLASS(CLineDrawingView));
    if (!pDocTemplate)
        return FALSE;
    AddDocTemplate(pDocTemplate);

    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    if (!ProcessShellCommand(cmdInfo))
        return FALSE;

    m_pMainWnd->ShowWindow(SW_SHOW);
    m_pMainWnd->UpdateWindow();

    return TRUE;
}

int CLineDrawingApp::ExitInstance()
{
    return CWinApp::ExitInstance();
}

// 关于应用程序命令的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg() noexcept;

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

void CLineDrawingApp::OnAppAbout()
{
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}
