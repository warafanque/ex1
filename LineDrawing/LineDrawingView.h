#pragma once
#include "CLine.h"

class CLineDrawingView : public CView
{
protected:
    CLineDrawingView() noexcept;
    DECLARE_DYNCREATE(CLineDrawingView)

public:
    CLineDrawingDoc* GetDocument() const;

public:
    virtual void OnDraw(CDC* pDC);
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
    virtual ~CLineDrawingView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);

private:
    bool m_bDrawing;           // 是否正在绘制
    CPoint m_ptStart;          // 起点
    CPoint m_ptEnd;            // 终点
    CLine m_currentLine;       // 当前正在绘制的直线
    
    // 坐标系相关
    int m_nOriginX;            // 原点X坐标
    int m_nOriginY;            // 原点Y坐标
    
    // 坐标转换函数
    CPoint ClientToLogical(const CPoint& pt) const;
    CPoint LogicalToClient(const CPoint& pt) const;
    
    // 绘制坐标系
    void DrawCoordinateSystem(CDC* pDC);
};

#ifndef _DEBUG
inline CLineDrawingDoc* CLineDrawingView::GetDocument() const
   { return reinterpret_cast<CLineDrawingDoc*>(m_pDocument); }
#endif
