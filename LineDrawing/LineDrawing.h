#pragma once

#ifndef __AFXWIN_H__
    #error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"

class CLineDrawingApp : public CWinApp
{
public:
    CLineDrawingApp() noexcept;

public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();

    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()
};

extern CLineDrawingApp theApp;
