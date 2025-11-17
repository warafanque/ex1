#include "pch.h"
#include "CLine.h"
#include <cmath>

CLine::CLine()
    : m_x1(0), m_y1(0), m_x2(0), m_y2(0)
{
}

CLine::CLine(int x1, int y1, int x2, int y2)
    : m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2)
{
    CalculatePoints();
}

CLine::~CLine()
{
}

void CLine::SetStartPoint(int x, int y)
{
    m_x1 = x;
    m_y1 = y;
}

void CLine::SetEndPoint(int x, int y)
{
    m_x2 = x;
    m_y2 = y;
    CalculatePoints();
}

void CLine::GetStartPoint(int& x, int& y) const
{
    x = m_x1;
    y = m_y1;
}

void CLine::GetEndPoint(int& x, int& y) const
{
    x = m_x2;
    y = m_y2;
}

void CLine::CalculatePoints()
{
    m_points.clear();
    BresenhamLine(m_x1, m_y1, m_x2, m_y2);
}

// 通用整数Bresenham算法实现
void CLine::BresenhamLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;  // x方向步进
    int sy = (y1 < y2) ? 1 : -1;  // y方向步进
    int err = dx - dy;
    int x = x1;
    int y = y1;

    while (true)
    {
        // 添加当前点
        POINT pt;
        pt.x = x;
        pt.y = y;
        m_points.push_back(pt);

        // 到达终点
        if (x == x2 && y == y2)
            break;

        // 计算误差并更新坐标
        int e2 = 2 * err;
        
        if (e2 > -dy)
        {
            err -= dy;
            x += sx;
        }
        
        if (e2 < dx)
        {
            err += dx;
            y += sy;
        }
    }
}

void CLine::Draw(HDC hdc, COLORREF color) const
{
    if (m_points.empty())
        return;

    // 绘制所有点
    for (const auto& pt : m_points)
    {
        SetPixel(hdc, pt.x, pt.y, color);
    }
}
