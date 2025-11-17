#include "pch.h"
#include "framework.h"
#include "LineDrawing.h"
#include "LineDrawingDoc.h"
#include "LineDrawingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CLineDrawingView, CView)

BEGIN_MESSAGE_MAP(CLineDrawingView, CView)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

CLineDrawingView::CLineDrawingView() noexcept
    : m_bDrawing(false)
    , m_nOriginX(0)
    , m_nOriginY(0)
{
}

CLineDrawingView::~CLineDrawingView()
{
}

BOOL CLineDrawingView::PreCreateWindow(CREATESTRUCT& cs)
{
    return CView::PreCreateWindow(cs);
}

void CLineDrawingView::OnDraw(CDC* pDC)
{
    CLineDrawingDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // 获取客户区大小
    CRect rect;
    GetClientRect(&rect);
    
    // 设置坐标系原点在客户区中心
    m_nOriginX = rect.Width() / 2;
    m_nOriginY = rect.Height() / 2;

    // 绘制坐标系
    DrawCoordinateSystem(pDC);

    // 获取设备上下文句柄
    HDC hdc = pDC->GetSafeHdc();
    
    // 绘制所有已保存的直线
    const std::vector<CLine>& lines = pDoc->GetLines();
    for (const auto& line : lines)
    {
        line.Draw(hdc, RGB(0, 0, 255));  // 蓝色
    }

    // 绘制当前正在绘制的直线
    if (m_bDrawing)
    {
        m_currentLine.Draw(hdc, RGB(0, 0, 255));  // 蓝色
    }
}

void CLineDrawingView::DrawCoordinateSystem(CDC* pDC)
{
    CRect rect;
    GetClientRect(&rect);

    CPen axisPen(PS_SOLID, 1, RGB(128, 128, 128));  // 灰色坐标轴
    CPen* pOldPen = pDC->SelectObject(&axisPen);

    // 绘制X轴
    pDC->MoveTo(0, m_nOriginY);
    pDC->LineTo(rect.Width(), m_nOriginY);

    // 绘制Y轴
    pDC->MoveTo(m_nOriginX, 0);
    pDC->LineTo(m_nOriginX, rect.Height());

    // 绘制刻度线（可选）
    int tickSize = 5;
    CPen tickPen(PS_SOLID, 1, RGB(200, 200, 200));  // 浅灰色刻度
    pDC->SelectObject(&tickPen);

    // X轴刻度
    for (int x = 0; x < rect.Width(); x += 50)
    {
        pDC->MoveTo(x, m_nOriginY - tickSize);
        pDC->LineTo(x, m_nOriginY + tickSize);
    }

    // Y轴刻度
    for (int y = 0; y < rect.Height(); y += 50)
    {
        pDC->MoveTo(m_nOriginX - tickSize, y);
        pDC->LineTo(m_nOriginX + tickSize, y);
    }

    pDC->SelectObject(pOldPen);
}

CPoint CLineDrawingView::ClientToLogical(const CPoint& pt) const
{
    // 将客户区坐标转换为逻辑坐标（以原点为中心）
    CPoint logicalPt;
    logicalPt.x = pt.x - m_nOriginX;
    logicalPt.y = m_nOriginY - pt.y;  // Y轴反向
    return logicalPt;
}

CPoint CLineDrawingView::LogicalToClient(const CPoint& pt) const
{
    // 将逻辑坐标转换为客户区坐标
    CPoint clientPt;
    clientPt.x = pt.x + m_nOriginX;
    clientPt.y = m_nOriginY - pt.y;  // Y轴反向
    return clientPt;
}

void CLineDrawingView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // 开始绘制直线
    m_bDrawing = true;
    m_ptStart = point;
    m_ptEnd = point;
    
    // 初始化当前直线
    m_currentLine.SetStartPoint(point.x, point.y);
    m_currentLine.SetEndPoint(point.x, point.y);
    
    // 捕获鼠标
    SetCapture();

    CView::OnLButtonDown(nFlags, point);
}

void CLineDrawingView::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (m_bDrawing)
    {
        m_bDrawing = false;
        m_ptEnd = point;
        
        // 完成直线绘制
        m_currentLine.SetEndPoint(point.x, point.y);
        
        // 将直线添加到文档
        CLineDrawingDoc* pDoc = GetDocument();
        if (pDoc)
        {
            pDoc->AddLine(m_currentLine);
        }
        
        // 释放鼠标捕获
        ReleaseCapture();
        
        // 重绘
        Invalidate();
    }

    CView::OnLButtonUp(nFlags, point);
}

void CLineDrawingView::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_bDrawing)
    {
        // 更新当前直线的终点
        m_ptEnd = point;
        m_currentLine.SetEndPoint(point.x, point.y);
        
        // 重绘
        Invalidate();
    }

    CView::OnMouseMove(nFlags, point);
}

BOOL CLineDrawingView::OnEraseBkgnd(CDC* pDC)
{
    // 清除背景为白色
    CRect rect;
    GetClientRect(&rect);
    pDC->FillSolidRect(&rect, RGB(255, 255, 255));
    return TRUE;
}

#ifdef _DEBUG
void CLineDrawingView::AssertValid() const
{
    CView::AssertValid();
}

void CLineDrawingView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CLineDrawingDoc* CLineDrawingView::GetDocument() const
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLineDrawingDoc)));
    return (CLineDrawingDoc*)m_pDocument;
}
#endif
