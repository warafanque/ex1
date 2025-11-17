#pragma once
#include <windows.h>
#include <vector>

// 直线类 - 使用整数Bresenham算法
class CLine
{
public:
    CLine();
    CLine(int x1, int y1, int x2, int y2);
    ~CLine();

    // 设置起点和终点
    void SetStartPoint(int x, int y);
    void SetEndPoint(int x, int y);
    
    // 获取起点和终点
    void GetStartPoint(int& x, int& y) const;
    void GetEndPoint(int& x, int& y) const;

    // 使用Bresenham算法计算直线上的所有点
    void CalculatePoints();
    
    // 绘制直线
    void Draw(HDC hdc, COLORREF color) const;

private:
    int m_x1, m_y1;  // 起点
    int m_x2, m_y2;  // 终点
    std::vector<POINT> m_points;  // 存储直线上的所有点
    
    // Bresenham算法实现
    void BresenhamLine(int x1, int y1, int x2, int y2);
};
