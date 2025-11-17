#include "pch.h"
#include "framework.h"
#include "LineDrawing.h"
#include "LineDrawingDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CLineDrawingDoc, CDocument)

BEGIN_MESSAGE_MAP(CLineDrawingDoc, CDocument)
END_MESSAGE_MAP()

CLineDrawingDoc::CLineDrawingDoc() noexcept
{
}

CLineDrawingDoc::~CLineDrawingDoc()
{
}

BOOL CLineDrawingDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    m_lines.clear();
    return TRUE;
}

void CLineDrawingDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // 保存
    }
    else
    {
        // 加载
    }
}

void CLineDrawingDoc::AddLine(const CLine& line)
{
    m_lines.push_back(line);
    SetModifiedFlag();
    UpdateAllViews(NULL);
}

void CLineDrawingDoc::ClearLines()
{
    m_lines.clear();
    SetModifiedFlag();
    UpdateAllViews(NULL);
}

#ifdef _DEBUG
void CLineDrawingDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CLineDrawingDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif
