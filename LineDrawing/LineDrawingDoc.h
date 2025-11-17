#pragma once
#include "CLine.h"
#include <vector>

class CLineDrawingDoc : public CDocument
{
protected:
    CLineDrawingDoc() noexcept;
    DECLARE_DYNCREATE(CLineDrawingDoc)

public:
    virtual ~CLineDrawingDoc();
    
    // 添加直线
    void AddLine(const CLine& line);
    
    // 获取所有直线
    const std::vector<CLine>& GetLines() const { return m_lines; }
    
    // 清空所有直线
    void ClearLines();

public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    DECLARE_MESSAGE_MAP()

private:
    std::vector<CLine> m_lines;  // 存储所有绘制的直线
};
