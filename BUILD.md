# 构建指南

## 使用 Visual Studio 2022 构建（推荐）

### 前置要求
1. 安装 Visual Studio 2022
2. 确保安装了以下组件：
   - 使用 C++ 的桌面开发
   - MFC 和 ATL 支持（v143 生成工具）
   - Windows 10 SDK 或更高版本

### 构建步骤
1. 双击打开 `LineDrawing.sln`
2. 在 Visual Studio 菜单栏选择：
   - 配置：Debug 或 Release
   - 平台：x86 或 x64
3. 按 `F7` 或选择"生成" > "生成解决方案"
4. 按 `Ctrl+F5` 运行程序（不调试）

### 输出位置
- Debug 版本：`LineDrawing/Debug/` 或 `LineDrawing/x64/Debug/`
- Release 版本：`LineDrawing/Release/` 或 `LineDrawing/x64/Release/`

## 使用 MSBuild 命令行构建

### 前置要求
- 安装 Visual Studio 2022 或 Build Tools for Visual Studio 2022
- 配置环境变量（或使用 Developer Command Prompt）

### 构建命令

#### Debug 版本
```cmd
# x86 平台
msbuild LineDrawing.sln /p:Configuration=Debug /p:Platform=Win32

# x64 平台
msbuild LineDrawing.sln /p:Configuration=Debug /p:Platform=x64
```

#### Release 版本
```cmd
# x86 平台
msbuild LineDrawing.sln /p:Configuration=Release /p:Platform=Win32

# x64 平台
msbuild LineDrawing.sln /p:Configuration=Release /p:Platform=x64
```

#### 清理构建
```cmd
msbuild LineDrawing.sln /t:Clean /p:Configuration=Debug /p:Platform=x64
```

#### 重新构建
```cmd
msbuild LineDrawing.sln /t:Rebuild /p:Configuration=Release /p:Platform=x64
```

## 使用 Developer Command Prompt

### 打开方式
1. 开始菜单搜索"Developer Command Prompt for VS 2022"
2. 右键以管理员身份运行（可选）

### 构建示例
```cmd
cd /d D:\path\to\ex1
msbuild LineDrawing.sln /p:Configuration=Release /p:Platform=x64 /m
```

参数说明：
- `/m`：启用多核并行构建
- `/v:minimal`：最小输出
- `/v:detailed`：详细输出

## 配置说明

### 项目配置
- **Debug**：包含调试信息，未优化，用于开发和调试
- **Release**：优化代码，无调试信息，用于发布

### 平台选择
- **Win32 (x86)**：32 位应用程序
- **x64**：64 位应用程序（推荐）

## 依赖项

### 运行时依赖
- **Debug 版本**：需要 Visual C++ Debug 运行时库（mfcXXXd.dll, msvcpXXXd.dll 等）
- **Release 版本**：需要 Visual C++ Redistributable for Visual Studio 2022

### 安装运行时
如果在没有 Visual Studio 的机器上运行 Release 版本，需要安装：
- [Microsoft Visual C++ Redistributable for Visual Studio 2022](https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist)

## 常见问题

### 1. 找不到 MFC 头文件
**错误**：`fatal error C1083: Cannot open include file: 'afxwin.h'`

**解决方案**：
- 通过 Visual Studio Installer 安装"用于 v143 生成工具的 C++ MFC（x86 和 x64）"

### 2. Windows SDK 版本不匹配
**错误**：`error MSB8036: The Windows SDK version 10.0 was not found`

**解决方案**：
- 方案1：安装项目所需的 Windows SDK 版本
- 方案2：修改项目文件中的 SDK 版本
  1. 右键项目 > 属性
  2. 配置属性 > 常规 > Windows SDK 版本
  3. 选择已安装的版本

### 3. 平台工具集不匹配
**错误**：`error MSB8020: The build tools for v143 cannot be found`

**解决方案**：
- 安装 Visual Studio 2022 或
- 修改项目文件使用已安装的平台工具集

### 4. 链接器错误
**错误**：`LNK2001: unresolved external symbol`

**解决方案**：
- 确保所有 `.cpp` 文件都包含在项目中
- 检查预编译头设置（`pch.cpp` 应设置为"创建"）

### 5. 资源编译错误
**错误**：资源文件编译失败

**解决方案**：
- 确保 `res/` 目录下的文件存在
- 检查 `.rc` 文件中的路径是否正确

## 项目清理

### 清理构建输出
```cmd
# 删除所有构建输出
msbuild LineDrawing.sln /t:Clean /p:Configuration=Debug /p:Platform=x64
msbuild LineDrawing.sln /t:Clean /p:Configuration=Release /p:Platform=x64
```

### 手动清理
删除以下目录：
- `LineDrawing/Debug/`
- `LineDrawing/Release/`
- `LineDrawing/x64/`
- `.vs/`（Visual Studio 缓存）

## 性能优化

### Release 构建优化
项目已配置以下优化选项：
- 函数级链接 (Function Level Linking)
- 内联函数展开 (Intrinsic Functions)
- COMDAT 折叠 (COMDAT Folding)
- 引用优化 (Optimize References)
- 全程序优化 (Whole Program Optimization)

### 构建性能
- 使用 `/m` 参数启用多核并行构建
- 使用 SSD 存储项目文件
- 增加系统 RAM

## 自动化构建

### 批处理脚本示例
```batch
@echo off
echo Building LineDrawing Project...

REM 清理
echo Cleaning...
msbuild LineDrawing.sln /t:Clean /p:Configuration=Release /p:Platform=x64 /v:minimal

REM 构建
echo Building Release x64...
msbuild LineDrawing.sln /t:Rebuild /p:Configuration=Release /p:Platform=x64 /m /v:minimal

if %ERRORLEVEL% EQU 0 (
    echo Build succeeded!
    echo Output: LineDrawing\x64\Release\LineDrawing.exe
) else (
    echo Build failed with error code %ERRORLEVEL%
    exit /b %ERRORLEVEL%
)

pause
```

保存为 `build.bat` 并运行。

## CI/CD 集成

### GitHub Actions 示例
```yaml
name: Build MFC Application

on: [push, pull_request]

jobs:
  build:
    runs-on: windows-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Add MSBuild to PATH
      uses: microsoft/setup-msbuild@v1.1
    
    - name: Restore NuGet packages
      run: nuget restore LineDrawing.sln
    
    - name: Build
      run: msbuild LineDrawing.sln /p:Configuration=Release /p:Platform=x64 /m
    
    - name: Upload artifacts
      uses: actions/upload-artifact@v3
      with:
        name: LineDrawing-Release-x64
        path: LineDrawing/x64/Release/LineDrawing.exe
```

## 总结

本项目支持多种构建方式：
- ✅ Visual Studio 2022 GUI（最简单）
- ✅ MSBuild 命令行（适合自动化）
- ✅ Developer Command Prompt（开发者友好）
- ✅ CI/CD 集成（自动化构建）

选择最适合你的构建方式开始使用吧！
