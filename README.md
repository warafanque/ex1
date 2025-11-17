# Bresenham 直线绘制程序

## 项目简介

这是一个基于 Visual Studio 2022 和 MFC 开发的图形绘制程序，实现了使用整数 Bresenham 算法绘制直线的功能。

## 功能特性

- ✅ 自定义二维坐标系（原点位于客户区中心）
- ✅ 鼠标交互式绘制直线
  - 按下鼠标左键选择起点
  - 拖动鼠标预览直线
  - 释放鼠标左键完成绘制
- ✅ 基于通用整数 Bresenham 算法实现
- ✅ 蓝色一像素宽度直线绘制
- ✅ 支持多条直线绘制

## 技术实现

### 核心类设计

#### CLine 类
- **功能**: 封装直线数据和 Bresenham 算法实现
- **关键方法**:
  - `SetStartPoint()` / `SetEndPoint()`: 设置起点和终点
  - `CalculatePoints()`: 计算直线上的所有点
  - `BresenhamLine()`: 通用整数 Bresenham 算法核心实现
  - `Draw()`: 绘制直线

#### Bresenham 算法特点
- 使用整数运算，避免浮点数计算
- 高效计算直线上的所有像素点
- 支持任意斜率的直线绘制

### MFC 架构
- **CLineDrawingApp**: 应用程序类
- **CMainFrame**: 主框架窗口
- **CLineDrawingDoc**: 文档类，管理所有绘制的直线
- **CLineDrawingView**: 视图类，处理鼠标事件和绘制

## 系统要求

- Windows 10 或更高版本
- Visual Studio 2022
- C++ MFC 开发工具

## 编译和运行

### 使用 Visual Studio

1. 打开 `LineDrawing.sln` 解决方案文件
2. 选择配置（Debug 或 Release）
3. 选择平台（x86 或 x64）
4. 点击"生成" -> "生成解决方案"（F7）
5. 点击"调试" -> "开始执行（不调试）"（Ctrl+F5）

### 使用 MSBuild（命令行）

```bash
# 编译 Debug 版本
msbuild LineDrawing.sln /p:Configuration=Debug /p:Platform=x64

# 编译 Release 版本
msbuild LineDrawing.sln /p:Configuration=Release /p:Platform=x64
```

## 使用说明

1. 启动程序后，窗口中央会显示二维坐标系
2. 在客户区任意位置按下鼠标左键，标记直线起点
3. 保持按下状态拖动鼠标，可以预览即将绘制的直线
4. 释放鼠标左键，完成一条蓝色直线的绘制
5. 重复上述步骤可以绘制多条直线
6. 选择"文件" -> "新建"可以清空画布

## 项目结构

```
LineDrawing/
├── LineDrawing.sln          # Visual Studio 解决方案文件
├── LineDrawing/
│   ├── CLine.h              # 直线类头文件
│   ├── CLine.cpp            # 直线类实现（Bresenham 算法）
│   ├── LineDrawing.h        # 应用程序类头文件
│   ├── LineDrawing.cpp      # 应用程序类实现
│   ├── MainFrm.h            # 主框架窗口头文件
│   ├── MainFrm.cpp          # 主框架窗口实现
│   ├── LineDrawingDoc.h     # 文档类头文件
│   ├── LineDrawingDoc.cpp   # 文档类实现
│   ├── LineDrawingView.h    # 视图类头文件
│   ├── LineDrawingView.cpp  # 视图类实现（鼠标事件处理）
│   ├── pch.h                # 预编译头文件
│   ├── pch.cpp              # 预编译源文件
│   ├── framework.h          # 框架头文件
│   ├── targetver.h          # Windows 版本定义
│   ├── resource.h           # 资源头文件
│   ├── LineDrawing.rc       # 资源文件
│   ├── LineDrawing.vcxproj  # 项目文件
│   └── res/                 # 资源目录
│       ├── LineDrawing.ico  # 应用程序图标
│       └── LineDrawing.rc2  # 额外资源文件
├── README.md                # 项目说明文档
└── .gitignore              # Git 忽略文件配置
```

## 算法说明

### Bresenham 直线算法

Bresenham 算法是一种高效的直线光栅化算法，其核心思想是：

1. 计算直线的增量 `dx` 和 `dy`
2. 确定 x 和 y 方向的步进方向
3. 使用误差累积来决定下一个像素的位置
4. 只使用整数加法和移位运算，避免浮点数计算

**算法优势**：
- 纯整数运算，速度快
- 内存占用小
- 精度高，无累积误差
- 适用于任意斜率的直线

## 开发环境

- IDE: Visual Studio 2022
- 语言: C++17
- 框架: MFC (Microsoft Foundation Classes)
- 平台工具集: v143

## 许可证

本项目仅用于学习和教学目的。

## 作者

计算机图形学实验项目
