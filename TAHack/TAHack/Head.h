#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <Mmsystem.h>
#include <thread>
#include <cstring>
#include <TlHelp32.h>
#include <time.h>
#include <ctime>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <compare>
#include <string>
#include <string_view>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <tchar.h>
#include <vfw.h>
#include <vector>
#include <io.h>
#include <gdiplus.h>
#include <gdiplusgraphics.h>
#include <dwmapi.h>
#include <urlmon.h>
#include <sapi.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "MSIMG32.LIB")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "sapi.lib")
#pragma comment(lib, "ole32.lib")
using namespace std;
namespace Window//窗口
{
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    template<class A>//防止同窗口冲突  不同的窗口改不同的类
    vector<int> Get_PixelColor(int X, int Y, HWND Window_HWND = 0) noexcept//采取屏幕颜色
    {//Window::Get_PixelColor<class Get_PixelColor>(100, 100)[0];
        static HDC DC = GetWindowDC(Window_HWND);
        COLORREF pixel = GetPixel(DC, X, Y);
        return { GetRValue(pixel), GetGValue(pixel), GetBValue(pixel) };//[0]red  [1]green  [2]blue
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    vector<int> Get_Resolution() noexcept//获取屏幕分辨率（像素）
    {//Window::Get_Resolution()[0];
        return { GetSystemMetrics(SM_CXSCREEN) ,GetSystemMetrics(SM_CYSCREEN) };//[0]==X [1]==Y
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Set_Resolution(int X, int Y) noexcept//模拟英伟达控制台更改像素 (只适用于系统已经创建的像素搭配!)
    {//Window::Set_Resolution(1440,1080);
        if (X != GetSystemMetrics(SM_CXSCREEN) || Y != GetSystemMetrics(SM_CYSCREEN))//设立条件防止放入循环崩溃
        {
            DEVMODE DevMode = {};
            EnumDisplaySettings(NULL, 0, &DevMode);
            DevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
            DevMode.dmPelsWidth = X;
            DevMode.dmPelsHeight = Y;
            DevMode.dmDisplayFrequency = 30;
            DevMode.dmBitsPerPel = 32;
            ChangeDisplaySettings(&DevMode, 0);
        }
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    vector<int> Get_WindowResolution(HWND WindowHwnd) noexcept//获取窗口分辨率（窗口模式不精准，全屏精准）
    {//Window::Get_WindowResolution(FindWindow(NULL, L"WindowName"))[0];
        RECT rect; GetWindowRect(WindowHwnd, &rect);
        return{ rect.right - rect.left ,rect.bottom - rect.top,  rect.left, rect.top };//[0]==X [1]==Y
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    int Get_Window_PID(string processName) noexcept//获取窗口PID   *如果快速循环使用占用高*
    {//Window::Get_Window_PID("explorer.exe");  //特定窗口名要任务管理器里面的
        uintptr_t processId = 0;
        PROCESSENTRY32 entrys = { };
        entrys.dwSize = sizeof(PROCESSENTRY32);
        const auto snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//问题
        while (Process32Next(snapShot, &entrys))
        {
            if (wcscmp(entrys.szExeFile, wstring(processName.begin(), processName.end()).c_str()) == 0)
            {
                processId = entrys.th32ProcessID;
                OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);//开通权限
                break;
            }
        }
        CloseHandle(snapShot);
        return processId;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    string Get_ForegroundWindowName() noexcept//获取您正在活动时的窗口标题
    {//Window::Get_ForegroundWindowName();
        char NM[MAX_PATH]; GetWindowTextA(GetForegroundWindow(), NM, MAX_PATH);//获取窗口标题
        return NM;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    BOOL Get_WindowEnable(HWND WindowHwnd) noexcept//获取您正在活动时的特定窗口标题是否为真
    {//Window::Get_WindowEnable(FindWindow(NULL, L"WindowName"));
        if (GetForegroundWindow() == WindowHwnd)return true; else return false;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    BOOL Get_WindowEnable_s(string processName) noexcept//获取您正在活动时的特定窗口标题是否为真(特定窗口名要任务管理器里面的)   *占用高*
    {//Window::Get_WindowEnable_s("explorer.exe");
        uintptr_t processId = 0;
        PROCESSENTRY32 entrys = { };
        entrys.dwSize = sizeof(PROCESSENTRY32);
        const auto snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//问题
        while (Process32Next(snapShot, &entrys))
        {
            if (wcscmp(entrys.szExeFile, wstring(processName.begin(), processName.end()).c_str()) == 0)
            {
                processId = entrys.th32ProcessID;
                OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);//开通权限
                break;
            }
        }
        CloseHandle(snapShot);
        DWORD ProcessID; GetWindowThreadProcessId(GetForegroundWindow(), &ProcessID);
        if (processId == ProcessID)return true;
        else return false;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Set_WindowName(HWND WindowHWND, string Title) noexcept//修改特定窗口标题 修改之后再次修改要修改修改后的标题
    {//Window::Set_WindowName(FindWindow(NULL, L"TestWindow"),"Test Window 1");
        SetWindowText(WindowHWND, wstring(Title.begin(), Title.end()).c_str());//修改窗口标题
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Mini_Window(HWND Window_HWND) noexcept//最小化指定窗口
    {//Window::Mini_Window(FindWindowA(NULL, "Test Windows"));
        ShowWindow(Window_HWND, SW_MINIMIZE);
    }
    void Show_Window(HWND Window_HWND) noexcept//显示指定窗口
    {//Window::Show_Window(FindWindowA(NULL, "Test Windows"));
        SetForegroundWindow(Window_HWND);
        ShowWindow(Window_HWND, true);
    }
    void Hide_Window(HWND Window_HWND) noexcept//隐藏指定窗口
    {//Window::Hide_Window(FindWindowA(NULL, "Test Windows"));
        ShowWindow(Window_HWND, false);
    }
    void Kill_Window(HWND Window_HWND) noexcept//关闭指定窗口
    {//Window::Kill_Window(FindWindowA(NULL, "Test Windows"));
        DWORD ProcessID; GetWindowThreadProcessId(Window_HWND, &ProcessID);
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
        TerminateProcess(hProcess, 0);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    BOOL Message_Box(LPCTSTR BT, LPCTSTR NR, int MS = MB_OK) noexcept//弹出提示框(更方便选择返回值) 说明：https://blog.csdn.net/yuyan987/article/details/78558648
    {//Window::Message_Box(L"提示", L"你的头上有点绿");
        int XXK = MessageBox(0, NR, BT, MS);
        if (XXK == 1 || XXK == 4 || XXK == 6)return true;//当确认
        else if (XXK == 2 || XXK == 3 || XXK == 5 || XXK == 7)return false;//当否定
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Hide_ConsoleWindow() noexcept//隐藏原控制台窗口
    {//Window::Hide_ConsoleWindow();
        ShowWindow(GetConsoleWindow(), false);//隐藏
    }
    void Show_ConsoleWindow() noexcept//显示原控制台窗口
    {//Window::Show_ConsoleWindow();
        ShowWindow(GetConsoleWindow(), true);//显示
    }
    void Set_ConsoleWindowTitle(string title) noexcept//修改原控制台窗口标题
    {//Window::Set_ConsoleWindowTitle("ah");
        system(("title " + title).c_str());
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    LRESULT WINAPI Start_GDI_Window_Prosess(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept//辅助
    {
        switch (msg)
        {
        case WM_ERASEBKGND: return TRUE;
            break;
        case WM_PAINT: return TRUE;
            break;
        }
        return DefWindowProcW(hwnd, msg, wp, lp);  //定义回调函数的返回值
    }
    class Windows//更加方便的 窗口创建
    {
        HWND GUIWindowHwnd = NULL;//GUI Window HWND
        int BKX = 0;
        int BKY = 0;
    public:
        //----------------------------------------------------------------------------------------
        HWND Create_Window(int Size_X, int Size_Y, string WindowName, BOOL IfTop = 0) noexcept//创建窗口
        {
            static int 窗口类型 = (WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
            if (IfTop)窗口类型 = (WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
            else 窗口类型 = (WS_EX_LAYERED | WS_EX_TOOLWINDOW);
            WNDCLASS RenderWindowM;
            memset(&RenderWindowM, 0, sizeof(RenderWindowM));
            RenderWindowM.style = CS_HREDRAW | CS_VREDRAW;
            RenderWindowM.lpfnWndProc = Start_GDI_Window_Prosess;//关联消息处理函数,告诉操作系统，如果有事件发生调用这个函数
            RenderWindowM.cbClsExtra = 0;
            RenderWindowM.cbWndExtra = 0;
            RenderWindowM.hInstance = GetModuleHandle(NULL);//实例句柄
            RenderWindowM.hIcon = LoadIcon(NULL, IDI_SHIELD);//图标
            RenderWindowM.hCursor = LoadCursor(NULL, IDC_ARROW);//光标样式
            RenderWindowM.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);//画刷
            RenderWindowM.lpszMenuName = NULL;
            RenderWindowM.lpszClassName = wstring(WindowName.begin(), WindowName.end()).c_str();//窗口类的名称，操作系统根据类的名称做映射
            RegisterClass(&RenderWindowM);//将这个窗体注册（告诉）到操作系统
            HWND hWnd = CreateWindowEx(//创建窗口
                窗口类型//窗口的扩展风格 不显示窗口图标
                , wstring(WindowName.begin(), WindowName.end()).c_str()//窗口类的名称，必须和上面的lpszClassName一致
                , wstring(WindowName.begin(), WindowName.end()).c_str()//窗口的标题
                , WS_POPUP//窗口的风格 透明WS_POPUP 正常WS_CAPTION
                , GetSystemMetrics(SM_CXSCREEN) / 2 - Size_X / 2 //屏幕位置
                , GetSystemMetrics(SM_CYSCREEN) / 2 - Size_Y / 2
                , Size_X//宽高
                , Size_Y
                , 0//父窗口
                , 0//系统菜单
                , GetModuleHandle(NULL)
                , 0//用户数据
            );
            if (hWnd)//更新显示
            {
                UpdateWindow(hWnd);
                ShowWindow(hWnd, SW_SHOW);
                SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 255, LWA_ALPHA);
                GUIWindowHwnd = hWnd;
                BKX = Size_X;
                BKY = Size_Y;
            }
            return hWnd;
        }
        //----------------------------------------------------------------------------------------
        HWND Create_RenderBlock_Alpha(int Size_X, int Size_Y, string WindowName) noexcept//创建绘制画板(专门用于绘制的窗口 支持阿尔法 不支持颜色为0,0,0的图形绘制)
        {
            WNDCLASS RenderWindowM;
            memset(&RenderWindowM, 0, sizeof(RenderWindowM));
            RenderWindowM.style = CS_HREDRAW | CS_VREDRAW;
            RenderWindowM.lpfnWndProc = Start_GDI_Window_Prosess;
            RenderWindowM.cbClsExtra = 0;
            RenderWindowM.cbWndExtra = 0;
            RenderWindowM.hInstance = GetModuleHandle(NULL);
            RenderWindowM.hIcon = LoadIcon(NULL, IDI_SHIELD);
            RenderWindowM.hCursor = LoadCursor(NULL, IDC_ARROW);
            RenderWindowM.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
            RenderWindowM.lpszMenuName = NULL;
            RenderWindowM.lpszClassName = wstring(WindowName.begin(), WindowName.end()).c_str();
            RegisterClass(&RenderWindowM);
            HWND hWnd = CreateWindowEx((WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW), wstring(WindowName.begin(), WindowName.end()).c_str(), wstring(WindowName.begin(), WindowName.end()).c_str(), WS_POPUP, 0, 0, Size_X, Size_Y, HWND_DESKTOP, 0, GetModuleHandle(NULL), 0);
            if (hWnd)//更新显示
            {
                DWM_BLURBEHIND bb = { 0 };
                HRGN Hrgn = CreateRectRgn(0, 0, -1, -1);
                bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
                bb.hRgnBlur = Hrgn;
                bb.fEnable = TRUE;
                DwmEnableBlurBehindWindow(hWnd, &bb);
                UpdateWindow(hWnd);
                ShowWindow(hWnd, SW_SHOW);
                SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
                GUIWindowHwnd = hWnd;
                BKX = Size_X;
                BKY = Size_Y;
            }
            return hWnd;
        }
        //----------------------------------------------------------------------------------------
        HWND Create_RenderBlock(int Size_X, int Size_Y, string WindowName) noexcept//创建绘制画板(专门用于绘制的窗口 不支持阿尔法 不支持颜色为0,0,0的图形绘制)
        {
            WNDCLASS RenderWindowM;
            memset(&RenderWindowM, 0, sizeof(RenderWindowM));
            RenderWindowM.style = CS_HREDRAW | CS_VREDRAW;
            RenderWindowM.lpfnWndProc = Start_GDI_Window_Prosess;
            RenderWindowM.cbClsExtra = 0;
            RenderWindowM.cbWndExtra = 0;
            RenderWindowM.hInstance = GetModuleHandle(NULL);
            RenderWindowM.hIcon = LoadIcon(NULL, IDI_SHIELD);
            RenderWindowM.hCursor = LoadCursor(NULL, IDC_ARROW);
            RenderWindowM.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
            RenderWindowM.lpszMenuName = NULL;
            RenderWindowM.lpszClassName = wstring(WindowName.begin(), WindowName.end()).c_str();
            RegisterClass(&RenderWindowM);
            HWND hWnd = CreateWindowEx((WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW), wstring(WindowName.begin(), WindowName.end()).c_str(), wstring(WindowName.begin(), WindowName.end()).c_str(), WS_POPUP, 0, 0, Size_X, Size_Y, HWND_DESKTOP, 0, GetModuleHandle(NULL), 0);
            if (hWnd)//更新显示
            {
                UpdateWindow(hWnd);
                ShowWindow(hWnd, SW_SHOW);
                SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
            }
            GUIWindowHwnd = hWnd;
            BKX = Size_X;
            BKY = Size_Y;
            return hWnd;
        }
        //----------------------------------------------------------------------------------------
        void UpdateRenderBlock() noexcept//DeleteColor(Put in the while() and Update < Render)
        {
            static HDC wind = GetWindowDC(GUIWindowHwnd);
            static HGDIOBJ huabi = SelectObject(wind, CreateSolidBrush(RGB(0, 0, 0)));
            BitBlt(wind, 0, 0, 99999, 99999, wind, 0, 0, PATCOPY);
        }
        //----------------------------------------------------------------------------------------
        HWND Get_HWND() noexcept//获取窗口HWND
        {
            return GUIWindowHwnd;
        }
        //----------------------------------------------------------------------------------------
        vector<int> Get_Window_Pos() noexcept//获取窗口坐标
        {
            RECT Windowrect;
            GetWindowRect(GUIWindowHwnd, &Windowrect);
            BKX = Windowrect.right - Windowrect.left;
            BKY = Windowrect.bottom - Windowrect.top;
            return { Windowrect.left ,Windowrect.top };
        }
        void Set_Window_Pos(int X, int Y) noexcept//移动窗口到指定坐标
        {
            RECT Windowrect;
            GetWindowRect(GUIWindowHwnd, &Windowrect);
            BKX = Windowrect.right - Windowrect.left;
            BKY = Windowrect.bottom - Windowrect.top;
            MoveWindow(GUIWindowHwnd, X, Y, Windowrect.right - Windowrect.left, Windowrect.bottom - Windowrect.top, TRUE);
        }
        //----------------------------------------------------------------------------------------
        vector<int> Get_Window_Size() noexcept//获取窗口大小
        {
            RECT Windowrect;
            GetWindowRect(GUIWindowHwnd, &Windowrect);
            BKX = Windowrect.right - Windowrect.left;
            BKY = Windowrect.bottom - Windowrect.top;
            return { Windowrect.right - Windowrect.left ,Windowrect.bottom - Windowrect.top };
        }
        void Set_Window_Size(int XX, int YY) noexcept//修改窗口大小
        {
            RECT Windowrect;
            GetWindowRect(GUIWindowHwnd, &Windowrect);
            BKX = Windowrect.right - Windowrect.left;
            BKY = Windowrect.bottom - Windowrect.top;
            MoveWindow(GUIWindowHwnd, Windowrect.left, Windowrect.top, XX, YY, TRUE);
        }
        //----------------------------------------------------------------------------------------
        void Set_WindowDeleteColor(vector<int>Color = { 0,0,0 }) noexcept//遍历删除特定颜色像素(不用放在循环内)
        {
            SetLayeredWindowAttributes(GUIWindowHwnd, RGB(Color[0], Color[1], Color[2]), 0, LWA_COLORKEY);
        }
        //----------------------------------------------------------------------------------------
        void Set_WindowAlpha(int Alpha = 255) noexcept//窗口整体阿尔法通道(不用放在循环内)
        {
            if (Alpha <= 0)Alpha = 0; else if (Alpha >= 255)Alpha = 255;//限制
            SetLayeredWindowAttributes(GUIWindowHwnd, RGB(0, 0, 0), Alpha, LWA_ALPHA);
        }
        //----------------------------------------------------------------------------------------
        void Show_Window() noexcept//强制显示窗口
        {
            SetForegroundWindow(GUIWindowHwnd);
            ShowWindow(GUIWindowHwnd, true);
        }
        //----------------------------------------------------------------------------------------
        void Hide_Window() noexcept//强制隐藏窗口
        {
            ShowWindow(GUIWindowHwnd, false);
        }
        //----------------------------------------------------------------------------------------
        BOOL Window_Move(int KD = 30) noexcept//移动窗口 KD = 宽度（放在循环）
        {
            static BOOL 防止脱离 = false;
            static int OldX;//按下时坐标X
            static int OldY;//按下时坐标Y
            POINT MousePos;
            GetCursorPos(&MousePos);
            RECT Windowrect;
            GetWindowRect(GUIWindowHwnd, &Windowrect);
            BKX = Windowrect.right - Windowrect.left;
            BKY = Windowrect.bottom - Windowrect.top;
            static BOOL 保存鼠标坐标 = false;
            if (GetForegroundWindow() == GUIWindowHwnd)//检测窗口是否在最前端
            {
                if ((MousePos.x - Windowrect.left >= 0 && MousePos.x - Windowrect.left <= BKX && MousePos.y - Windowrect.top >= 0 && MousePos.y - Windowrect.top <= KD) && GetAsyncKeyState(VK_LBUTTON) && !防止脱离)
                {
                    if (保存鼠标坐标)
                    {
                        OldX = (MousePos.x - Windowrect.left);
                        OldY = (MousePos.y - Windowrect.top);
                        保存鼠标坐标 = false;
                    }
                    MoveWindow(GUIWindowHwnd, MousePos.x - OldX, MousePos.y - OldY, Windowrect.right - Windowrect.left, Windowrect.bottom - Windowrect.top, TRUE);//移动窗口到鼠标坐标
                    防止脱离 = true;
                }
                else if (防止脱离 && GetAsyncKeyState(VK_LBUTTON))
                {
                    MoveWindow(GUIWindowHwnd, MousePos.x - OldX, MousePos.y - OldY, Windowrect.right - Windowrect.left, Windowrect.bottom - Windowrect.top, TRUE);//移动窗口到鼠标坐标
                    return true;
                }
                else {
                    防止脱离 = false;
                    保存鼠标坐标 = true;
                    return false;
                }
            }
        }
        //----------------------------------------------------------------------------------------
        void Fix_inWhile() noexcept//修复窗口转圈
        {
            MSG msg = { 0 };
            if (GetMessageW(&msg, 0, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        //----------------------------------------------------------------------------------------
    private:
    };
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    HWND Get_PIDtoHWND(DWORD dwProcessID) noexcept//通过pid获取窗口句柄
    {//Window::Get_PIDtoHWND(8102);
        HWND h = GetTopWindow(0);
        HWND retHwnd = NULL;
        while (h)
        {
            DWORD pid = 0;
            DWORD dwTheardId = GetWindowThreadProcessId(h, &pid);
            if (dwTheardId != 0 && pid == dwProcessID && GetParent(h) == NULL && IsWindowVisible(h))retHwnd = h;
            h = GetNextWindow(h, GW_HWNDNEXT);
        }
        return retHwnd;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    DWORD Get_WindowPID(HWND dwHWND) noexcept//通过窗口HWND句柄获取窗口PID
    {//Window::Get_WindowPID(FindWindow(NULL, NULL));
        DWORD ProcessIDReturnValue;//进程
        GetWindowThreadProcessId(dwHWND, &ProcessIDReturnValue);//获取进程id
        return ProcessIDReturnValue;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    class Render//双缓冲2D绘制类 （将绘制信息转移到图像内一并绘制）
    {
        /*
        int main()
        {
            Window::Windows Window_Var;//window class
            Window_Var.Create_Window(500, 500, "Test Windows");//Create
            Window::Render Render_DoubleBuffer_BL;//render class
            Render_DoubleBuffer_BL.CreatePaint(Window_Var.Get_HWND(), 0, 0, 500, 500);//Create
            while (1)
            {
                Render_DoubleBuffer_BL.Render_SolidRect(0, 0, 99999, 99999, { 255,255,255 });
                Render_DoubleBuffer_BL.Render_Line(0, 0, 300, 200, { 0,0,0 });
                Render_DoubleBuffer_BL.Render_SimpleString(5, 5, "Hello my bro! 123456789 ABCabc !@#$%^&*().", { 255,200,0 });
                Render_DoubleBuffer_BL.Render_SolidRect(100, 400, 100, 100, { 255,0,0 });
                Render_DoubleBuffer_BL.RenderA_GradientCircle(150, 150, 200, { 255,255,255,255 }, { 0,0,0,255 }, 0.5);
                Render_DoubleBuffer_BL.DrawPaint();
                Window_Var.Fix_inWhile();//**
                Sleep(1);
            }
        }
        */
        HDC HdcWind;
        HDC hMenDC;
        vector<int> StartPos;
        vector<int> EndPos;
        int Draw_FPS;
    public:
        //--------------------------------------------------------------------------------------------------------
        HDC CreatePaint(HWND WindowHWND, int X, int Y, int XX, int YY) noexcept//创建画布（在返回值内进行绘制 请勿放在循环*）
        {
            //-----------------------------------------------------------初始化GDI+
            Gdiplus::GdiplusStartupInput gdiplusstartupinput;
            ULONG_PTR gdiplusToken;
            Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusstartupinput, nullptr);
            //---------------------------------------------------------------------
            StartPos = { X,Y };
            EndPos = { XX,YY };
            HdcWind = GetWindowDC(WindowHWND);
            hMenDC = CreateCompatibleDC(HdcWind);
            SelectObject(hMenDC, (HBITMAP)CreateCompatibleBitmap(HdcWind, EndPos[0], EndPos[1]));
            return hMenDC;
        }
        HDC Get_HDC() noexcept { return hMenDC; }//获取绘制DC
        void DrawPaint() noexcept//绘制画布（如果单单绘制到屏幕NULL依然会闪烁但是不会出现上下图层闪烁*）
        {
            BitBlt(HdcWind, StartPos[0], StartPos[1], EndPos[0], EndPos[1], hMenDC, 0, 0, SRCCOPY);
            //--------------------------------帧数计算
            static int m_fps = 0; m_fps++;
            const int Tick = GetTickCount64(); static int Tick_Old = Tick;
            if (Tick >= Tick_Old + 1000)//每1秒刷新 (计时器)
            {
                Tick_Old = Tick;
                Draw_FPS = m_fps;
                m_fps = 0;
            }
            //----------------------------------------
        }
        int FPS() noexcept { return Draw_FPS; }//获取绘制帧数
        //--------------------------------------------------------------------------------------------------------以下为绘制函数
        void RenderA_Line(int X, int Y, int XX, int YY, vector<int>Color, int LineThickness = 1) noexcept//屏幕画线(包含Alpha)
        {
            Gdiplus::Graphics HDCwind(hMenDC);
            Gdiplus::Pen pen(Gdiplus::Color(Color[3], Color[0], Color[1], Color[2]), LineThickness);
            HDCwind.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);//抗锯齿 https://blog.csdn.net/hgy413/article/details/6692932
            HDCwind.DrawLine(&pen, X, Y, XX, YY);
        }
        //------------------------------------------------------------------------------------------------
        void RenderA_GradientLine(int X, int Y, int XX, int YY, vector<int>Color_1, vector<int>Color_2, int LineThickness = 1) noexcept//屏幕画渐变直线(包含Alpha)
        {
            Gdiplus::Graphics HDCwind(hMenDC);
            Gdiplus::LinearGradientBrush linGrBrush(Gdiplus::Point(X, Y), Gdiplus::Point(XX + 1, YY + 1), Gdiplus::Color(Color_1[3], Color_1[0], Color_1[1], Color_1[2]), Gdiplus::Color(Color_2[3], Color_2[0], Color_2[1], Color_2[2]));
            Gdiplus::Pen pen(&linGrBrush, LineThickness);
            HDCwind.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);//抗锯齿 https://blog.csdn.net/hgy413/article/details/6692932
            HDCwind.DrawLine(&pen, X, Y, XX, YY);
        }
        //------------------------------------------------------------------------------------------------
        void RenderA_SolidRect(int X, int Y, int XX, int YY, vector<int>Color) noexcept//绘制实心矩形(包含Alpha)
        {
            Gdiplus::Graphics HDCwind(hMenDC);
            Gdiplus::SolidBrush Pen(Gdiplus::Color(Color[3], Color[0], Color[1], Color[2]));
            HDCwind.FillRectangle(&Pen, X, Y, XX, YY);
        }
        //------------------------------------------------------------------------------------------------
        void RenderA_HollowRect(int X, int Y, int XX, int YY, vector<int>Color, int LineThickness = 1) noexcept//绘制空心矩形(包含Alpha)
        {
            Gdiplus::Graphics HDCwind(hMenDC);
            Gdiplus::Pen Pen(Gdiplus::Color(Color[3], Color[0], Color[1], Color[2]), LineThickness);
            HDCwind.DrawRectangle(&Pen, X, Y, XX, YY);
        }
        //------------------------------------------------------------------------------------------------
        void RenderA_GradientRect(int X, int Y, int XX, int YY, vector<int>Color_1, vector<int>Color_2, BOOL Style = 0) noexcept//绘制渐变色矩形(包含Alpha) 0横向渐变 1竖向渐变
        {
            Gdiplus::Graphics HDCwind(hMenDC);
            if (!Style)
            {
                Gdiplus::LinearGradientBrush Pen(Gdiplus::Point(X - 1, 0), Gdiplus::Point(X + XX + 1, 0), Gdiplus::Color(Color_1[3], Color_1[0], Color_1[1], Color_1[2]), Gdiplus::Color(Color_2[3], Color_2[0], Color_2[1], Color_2[2]));
                HDCwind.FillRectangle(&Pen, X, Y, XX, YY);
            }
            else {
                Gdiplus::LinearGradientBrush Pen(Gdiplus::Point(0, Y - 1), Gdiplus::Point(0, Y + YY + 1), Gdiplus::Color(Color_1[3], Color_1[0], Color_1[1], Color_1[2]), Gdiplus::Color(Color_2[3], Color_2[0], Color_2[1], Color_2[2]));
                HDCwind.FillRectangle(&Pen, X, Y, XX, YY);
            }
        }
        //------------------------------------------------------------------------------------------------
        void Render_DrawImage(string ImageFile, int X, int Y, int XX, int YY) noexcept//屏幕图像绘制  CPU占用高 绘制慢*
        {
            Gdiplus::Graphics HDCwind(hMenDC);
            Gdiplus::Bitmap bmp(wstring(ImageFile.begin(), ImageFile.end()).c_str());
            HDCwind.DrawImage(&bmp, X, Y, XX, YY);
        }
        //------------------------------------------------------------------------------------------------
        void RenderA_GradientCircle(int X, int Y, int Size, vector<int>Color_1, vector<int>Color_2, float Focus = 1) noexcept//绘制路径渐变圆形(包含Alpha) 内到外
        {
            Gdiplus::Graphics HDCwind(hMenDC);
            Gdiplus::GraphicsPath m_Path;//构造空路径
            m_Path.AddEllipse(X - Size / 2, Y - Size / 2, Size, Size);//添加椭圆
            Gdiplus::PathGradientBrush pathBrush(&m_Path);//使用路径创建画刷
            pathBrush.SetCenterColor(Gdiplus::Color(Color_1[3], Color_1[0], Color_1[1], Color_1[2]));//设置中心颜色
            Gdiplus::Color colors[] = { Gdiplus::Color(Color_2[3], Color_2[0], Color_2[1], Color_2[2]) };//边界颜色
            int i = 1; pathBrush.SetSurroundColors(colors, &i);
            pathBrush.SetFocusScales(Focus, Focus);//设置聚焦缩放0-1 float
            HDCwind.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);//抗锯齿 https://blog.csdn.net/hgy413/article/details/6692932
            HDCwind.FillEllipse(&pathBrush, X - Size / 2, Y - Size / 2, Size, Size);
        }
        //------------------------------------------------------------------------------------------------
        int Render_String(int X, int Y, string String, string FontName, int FontSize, vector<int>Color, BOOL AntiAlias = true) noexcept//文字绘制(不包含Alpha)
        {
            HDC HMS = hMenDC;
            HGDIOBJ FontPen;
            if (AntiAlias)FontPen = SelectObject(HMS, CreateFont(FontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, wstring(FontName.begin(), FontName.end()).c_str()));
            else FontPen = SelectObject(HMS, CreateFont(FontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, wstring(FontName.begin(), FontName.end()).c_str()));
            SetTextColor(HMS, RGB(Color[0], Color[1], Color[2]));//文字颜色
            SetBkMode(HMS, TRANSPARENT);//背景透明
            TextOutA(HMS, X, Y, String.c_str(), strlen(String.c_str()));
            DeleteObject(FontPen);
            return strlen(String.c_str());
        }
        //------------------------------------------------------------------------------------------------
        void Render_Line(int X, int Y, int XX, int YY, vector<int>Color, int LineThickness = 1) noexcept//屏幕画线(不包含Alpha 无抗锯齿)
        {
            HDC DC = hMenDC;
            HGDIOBJ LineColor = SelectObject(DC, CreatePen(PS_SOLID, LineThickness, RGB(Color[0], Color[1], Color[2])));
            MoveToEx(DC, X, Y, NULL);
            LineTo(DC, XX, YY);
            DeleteObject(LineColor);
        }
        //------------------------------------------------------------------------------------------------
        void Render_SolidRect(int X, int Y, int XX, int YY, vector<int>Color) noexcept//屏幕画实心矩形带颜色(不包含Alpha)
        {
            HDC HMS = hMenDC;
            HGDIOBJ BIANKUANG = SelectObject(HMS, CreatePen(PS_SOLID, 1, RGB(Color[0], Color[1], Color[2])));
            HGDIOBJ TIANCHONG = SelectObject(HMS, CreateSolidBrush(RGB(Color[0], Color[1], Color[2])));
            Rectangle(HMS, X, Y, X + XX, Y + YY);
            DeleteObject(BIANKUANG);
            DeleteObject(TIANCHONG);
        }
        //------------------------------------------------------------------------------------------------
        void Render_HollowRect(int X, int Y, int XX, int YY, int K, vector<int>Color) noexcept//屏幕画空心矩形带颜色(不包含Alpha)
        {
            HDC HMS = hMenDC;
            HGDIOBJ BIANKUANG = SelectObject(HMS, CreatePen(PS_SOLID, K, RGB(Color[0], Color[1], Color[2])));
            HGDIOBJ TIANCHONG = SelectObject(HMS, (HBRUSH)GetStockObject(NULL_BRUSH));
            Rectangle(HMS, X, Y, X + XX, Y + YY);
            DeleteObject(BIANKUANG);
            DeleteObject(TIANCHONG);
        }
        //------------------------------------------------------------------------------------------------
        void Render_GradientRect(int X, int Y, int XX, int YY, vector<int>Color_1, vector<int>Color_2, BOOL Style = 0) noexcept//绘制渐变色矩形(不包含Alpha) 0横向渐变 1竖向渐变
        {
            TRIVERTEX vert[2];
            GRADIENT_RECT gRect;
            vert[0].Alpha = 0x0000;
            vert[1].Alpha = 0x0000;
            gRect.UpperLeft = 0;
            gRect.LowerRight = 1;
            COLORREF Color1 = RGB(Color_1[0], Color_1[1], Color_1[2]);
            COLORREF Color2 = RGB(Color_2[0], Color_2[1], Color_2[2]);
            vert[0].x = X;
            vert[0].y = Y;
            vert[1].x = X + XX;
            vert[1].y = Y + YY;
            vert[0].Red = GetRValue(Color1) << 8;
            vert[0].Green = GetGValue(Color1) << 8;
            vert[0].Blue = GetBValue(Color1) << 8;
            vert[1].Red = GetRValue(Color2) << 8;
            vert[1].Green = GetGValue(Color2) << 8;
            vert[1].Blue = GetBValue(Color2) << 8;
            if (!Style)GradientFill(hMenDC, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_H);
            else GradientFill(hMenDC, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_V);
        }
        //------------------------------------------------------------------------------------------------
        void Render_HollowCircle(int X, int Y, int Size, vector<int>Color, int LineThickness = 1) noexcept//绘制空心圆形(不包含Alpha 无抗锯齿)
        {
            HDC wind = hMenDC;
            HGDIOBJ BIANKUANG = SelectObject(wind, CreatePen(PS_SOLID, LineThickness, RGB(Color[0], Color[1], Color[2])));
            HGDIOBJ TIANCHONG = SelectObject(wind, (HBRUSH)GetStockObject(NULL_BRUSH));
            Ellipse(wind, X - Size / 2, Y - Size / 2, X + Size / 2, Y + Size / 2);//通过绘制曲线来绘制圆*
            DeleteObject(BIANKUANG);
            DeleteObject(TIANCHONG);
        }
        //------------------------------------------------------------------------------------------------
        void Render_SolidCircle(int X, int Y, int Size, vector<int>Color_1, vector<int>Color_2, int LineThickness = 1) noexcept//绘制实心圆形(不包含Alpha 无抗锯齿)
        {
            HDC wind = hMenDC;
            HGDIOBJ BIANKUANG = SelectObject(wind, CreatePen(PS_SOLID, LineThickness, RGB(Color_1[0], Color_1[1], Color_1[2])));
            HGDIOBJ TIANCHONG = SelectObject(wind, CreateSolidBrush(RGB(Color_2[0], Color_2[1], Color_2[2])));
            Ellipse(wind, X - Size / 2, Y - Size / 2, X + Size / 2, Y + Size / 2);//通过绘制曲线来绘制圆*
            DeleteObject(BIANKUANG);
            DeleteObject(TIANCHONG);
        }
        //------------------------------------------------------------------------------------------------
        void Render_GradientTriangle(vector<int>Pos_3Point, vector<int>Color_1, vector<int>Color_2, vector<int>Color_3) noexcept//绘制渐变色三角形（3种颜色）(不包含Alpha 无抗锯齿)
        {
            TRIVERTEX vert[3];
            GRADIENT_TRIANGLE gTRi;
            COLORREF Color1 = RGB(Color_1[0], Color_1[1], Color_1[2]);
            COLORREF Color2 = RGB(Color_2[0], Color_2[1], Color_2[2]);
            COLORREF Color3 = RGB(Color_3[0], Color_3[1], Color_3[2]);
            vert[0].x = Pos_3Point[0];
            vert[0].y = Pos_3Point[1];
            vert[1].x = Pos_3Point[2];
            vert[1].y = Pos_3Point[3];
            vert[2].x = Pos_3Point[4];
            vert[2].y = Pos_3Point[5];
            vert[0].Red = GetRValue(Color1) << 8;
            vert[0].Green = GetGValue(Color1) << 8;
            vert[0].Blue = GetBValue(Color1) << 8;
            vert[0].Alpha = 0x0000;
            vert[1].Red = GetRValue(Color2) << 8;
            vert[1].Green = GetGValue(Color2) << 8;
            vert[1].Blue = GetBValue(Color2) << 8;
            vert[1].Alpha = 0x0000;
            vert[2].Red = GetRValue(Color3) << 8;
            vert[2].Green = GetGValue(Color3) << 8;
            vert[2].Blue = GetBValue(Color3) << 8;
            vert[2].Alpha = 0x0000;
            gTRi.Vertex1 = 0;
            gTRi.Vertex2 = 1;
            gTRi.Vertex3 = 2;
            GradientFill(hMenDC, vert, 3, &gTRi, 1, GRADIENT_FILL_TRIANGLE);
        }
        //------------------------------------------------------------------------------------------------
        void Render_SimpleString(int X, int Y, string String, vector<int>Color_1, vector<int>Color_2 = { 0,0,0 }) noexcept//文字绘制(简单样式)(不包含Alpha)
        {
            HDC Hdc = hMenDC;
            HGDIOBJ FontPen = SelectObject(Hdc, CreateFont(9, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, L"Lucida Console"));
            SetBkMode(Hdc, TRANSPARENT);//背景透明
            SetTextColor(Hdc, RGB(Color_2[0], Color_2[1], Color_2[2]));//文字颜色
            TextOutA(Hdc, X + 1, Y + 1, String.c_str(), strlen(String.c_str()));
            TextOutA(Hdc, X - 1, Y - 1, String.c_str(), strlen(String.c_str()));
            TextOutA(Hdc, X + 1, Y - 1, String.c_str(), strlen(String.c_str()));
            TextOutA(Hdc, X - 1, Y + 1, String.c_str(), strlen(String.c_str()));
            TextOutA(Hdc, X + 1, Y, String.c_str(), strlen(String.c_str()));
            TextOutA(Hdc, X - 1, Y, String.c_str(), strlen(String.c_str()));
            TextOutA(Hdc, X, Y - 1, String.c_str(), strlen(String.c_str()));
            TextOutA(Hdc, X, Y + 1, String.c_str(), strlen(String.c_str()));
            SetTextColor(Hdc, RGB(Color_1[0], Color_1[1], Color_1[2]));//文字颜色
            TextOutA(Hdc, X, Y, String.c_str(), strlen(String.c_str()));
            DeleteObject(FontPen);
        }
        //------------------------------------------------------------------------------------------------
        void RenderA_String(int X, int Y, string String, string Font, int FontSize, vector<int>Color) noexcept//文字绘制(包含Alpha)
        {
            if (Font == "0" || Font == "NONE")Font = "Lucida Console";//默认字体
            Gdiplus::Graphics HDCwind(hMenDC);//HDC
            Gdiplus::FontFamily  fontFamily(wstring(Font.begin(), Font.end()).c_str());
            HDCwind.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);//抗锯齿
            Gdiplus::Font font(&fontFamily, FontSize, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);//字体状况（大小 斜体）
            Gdiplus::PointF pointF(X, Y);//文字绘制坐标
            Gdiplus::SolidBrush solidBrush(Gdiplus::Color(Color[3], Color[0], Color[1], Color[2]));//文字颜色（包含Alpha）
            HDCwind.DrawString(wstring(String.begin(), String.end()).c_str(), -1, &font, pointF, &solidBrush);//最终绘制
        }
        //--------------------------------------------------------------------------------------------------------
    private:
    };
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
}
namespace System//Windows系统
{
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    vector<int> RainbowColor(int Speed, const int Follo = 0) noexcept//彩虹色值
    {//System::RainbowColor(100);//颜色变换速度 (越大越慢)
        return { (int)floor(sin((float)GetTickCount64() / (Speed * 100) * 2 + Follo) * 127 + 128), (int)floor(sin((float)GetTickCount64() / (Speed * 100) * 2 + 2 + Follo) * 127 + 128), (int)floor(sin((float)GetTickCount64() / (Speed * 100) * 2 + 4 + Follo) * 127 + 128) };
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Source_ExecuteCommand(string String, const HWND m_hEngine = FindWindow(L"Valve001", 0)) noexcept//起源引擎游戏执行命令
    {//System::Source_ExecuteCommand("kill");
        COPYDATASTRUCT m_cData; m_cData.cbData = strlen(String.c_str()) + 1; m_cData.dwData = 0; m_cData.lpData = (void*)String.c_str();
        SendMessage(m_hEngine, WM_COPYDATA, 0, (LPARAM)&m_cData);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Mouse_Move(int X, int Y) noexcept//移动鼠标坐标(可实现游戏内改变视觉角度)鼠标原来的坐标加上设定值
    {//System::Mouse_Move(100, 100);
        mouse_event(MOUSEEVENTF_MOVE, X, Y, 0, 0);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Key_Click(int VK_CODE, BOOL Sleep_ = false) noexcept//按下弹起键盘上的某个键位 VK_CODE: https://docs.microsoft.com/zh-cn/windows/win32/inputdev/virtual-key-codes
    {//System::Key_Click(VK_RETURN);
        if (Sleep_)//添加睡眠函数程序更容易接收
        {
            keybd_event(VK_CODE, 0, 0, 0);
            Sleep(1);
            keybd_event(VK_CODE, 0, KEYEVENTF_KEYUP, 0);
            Sleep(1);
        }
        else {
            keybd_event(VK_CODE, 0, 0, 0);
            keybd_event(VK_CODE, 0, KEYEVENTF_KEYUP, 0);
        }
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    vector<int> Get_MousePos() noexcept//获取鼠标坐标
    {//System::GetMousePos()[0];
        POINT XY; GetCursorPos(&XY);
        return { XY.x, XY.y };//[0]X坐标  [1]Y坐标
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Play_Sound_WAV(string Str_WAV) noexcept//播放WAV文件（声音）（同时播放2个文件会中断）
    {//System::Play_Sound_WAV("D:\\SteamLibrary\\steamapps\\common\\Counter-Strike Global Offensive\\55.wav");
        PlaySound(wstring(Str_WAV.begin(), Str_WAV.end()).c_str(), NULL, SND_FILENAME | SND_ASYNC);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Open_Website(string Link) noexcept//打开浏览器网址
    {//System::Open_Website("https://www.baidu.com/");
        system(("start " + Link).c_str());
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    vector<int> Time() noexcept//获取系统时间
    {//System::Time()[0];
        SYSTEMTIME sys; GetLocalTime(&sys);
        return { sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond,sys.wMilliseconds,sys.wDayOfWeek };//0=年份 1=月份 2=天 3=小时 4=分钟 5=秒 6=毫秒 7=星期几
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    string Time_String() noexcept//获取系统时间(有了格式的String)
    {//string Time = System::Time_String();
        SYSTEMTIME sys;
        GetLocalTime(&sys);
        string Hour = to_string(sys.wHour);
        string Minute = to_string(sys.wMinute);
        string Second = to_string(sys.wSecond);
        if (sys.wHour < 10)Hour = "0" + Hour;
        if (sys.wMinute < 10)Minute = "0" + Minute;
        if (sys.wSecond < 10)Second = "0" + Second;
        return Hour + ":" + Minute + ":" + Second;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Create_Folder(string filename) noexcept//创建文件夹(空文件夹)
    {//System::Create_Folder("Test Folder");
        system(("mkdir " + filename).c_str());
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    BOOL Judge_File(string FileName) noexcept//判断 文件or夹 是否存在
    {//System::Judge_File("Test File.txt");
        if (_access(FileName.c_str(), 0) == -1)return false;
        else return true;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Create_File(string FileName, string Content, BOOL Append = false) noexcept//生成并且改写任何文件 //详细：https://blog.csdn.net/qq_29406323/article/details/81261926
    {//System::Create_File("Test File.txt","1\n2\n3\n");
        if (Append)//Append
        {
            fstream foundfile(FileName.c_str(), ios::app);
            if (foundfile.is_open())foundfile << Content.c_str(); foundfile.close();
        }
        else {//Set
            fstream foundfile(FileName.c_str(), ios::out);
            if (foundfile.is_open())foundfile << Content.c_str(); foundfile.close();
        }
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    string Get_File(string file, int line) noexcept//获取文件信息中的特定行数
    {//System::Get_File("Free(武器力度参数).txt", 2);
        ifstream infile; infile.open(file, ios::in);//将文件流对象与文件连接起来 
        static char str[2048];//初始化缓冲区
        for (int i = 0; i < line; i++)infile.getline(str, sizeof(str));//遍历
        infile.close();//关闭文件输入流 
        return str;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    template<class A>//为了防止双函数同步
    BOOL Key_Toggle(int key) noexcept//切换模式按键触发 另一种写法：GetKeyState(VK_TAB)
    {//System::Key_Toggle<class Key_Toggle>(VK_TAB);
        static BOOL keys = false;
        if (!keys && (GetAsyncKeyState(key) & 0x8000))
        {
            keys = true;
            keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (keys && (GetAsyncKeyState(key) & 0x8000))
        {
            keys = false;
            keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
        }
        return keys;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Copy(string String) noexcept//复制指定内容到剪贴板 (汉子会乱码 解决方法：输入法调成中文)
    {//System::Copy("汉子 中 !@# abc");
        OpenClipboard(NULL);//打开剪切板
        EmptyClipboard();//清空剪切板
        HANDLE hHandle = GlobalAlloc(GMEM_FIXED, strlen(String.c_str()) + 1);//分配内存
        char* pData = (char*)GlobalLock(hHandle);//锁定内存，返回申请内存的首地址
        strcpy_s(pData, strlen(String.c_str()) + 1, String.c_str());//或strcpy(pData, "this is a ClipBoard Test.");
        SetClipboardData(CF_TEXT, hHandle);//设置剪切板数据
        GlobalUnlock(hHandle);//解除锁定
        CloseClipboard();//关闭剪切板
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Stickup() noexcept//粘贴剪切板内容 (按键脚本)
    {//System::Stickup();
        keybd_event(VK_CONTROL, 0, 0, 0);//按下ctrl
        keybd_event(0x56, 0x2F, 0, 0);//按下v
        keybd_event(0x56, 0x2F, KEYEVENTF_KEYUP, 0);//松开v
        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);//松开ctrl
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Copy_Stickup(string String) noexcept//复制粘贴 (汉子会乱码 解决方法：输入法调成中文)
    {//System::Copy_Stickup("汉子 中 !@# abc");
        OpenClipboard(NULL);//打开剪切板
        EmptyClipboard();//清空剪切板
        HANDLE hHandle = GlobalAlloc(GMEM_FIXED, strlen(String.c_str()) + 1);//分配内存
        char* pData = (char*)GlobalLock(hHandle);//锁定内存，返回申请内存的首地址
        strcpy_s(pData, strlen(String.c_str()) + 1, String.c_str());//或strcpy(pData, "this is a ClipBoard Test.");
        SetClipboardData(CF_TEXT, hHandle);//设置剪切板数据
        GlobalUnlock(hHandle);//解除锁定
        CloseClipboard();//关闭剪切板
        keybd_event(VK_CONTROL, 0, 0, 0);//按下ctrl
        keybd_event(0x56, 0x2F, 0, 0);//按下v
        keybd_event(0x56, 0x2F, KEYEVENTF_KEYUP, 0);//松开v
        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);//松开ctrl
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    int Rand_Number(int 以上, int 以下) noexcept//随机数（每次都不同）
    {//System::Rand_Number(0, 1000);//返回0~1000整数
        srand(GetTickCount64() + time(0) * GetTickCount64());//防止一样的函数同步
        return rand() % (以下 - 以上 + 1) + 以上;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    string Get_UserName() noexcept//获取电脑用户名
    {//System::Get_UserName();
        char szBuffer[256];
        DWORD dwNameLen = 256;
        GetUserNameA(szBuffer, &dwNameLen);
        return (string)szBuffer;
    }
    string Get_ComputerName() noexcept//获取电脑名
    {//System::Get_ComputerName();
        char szBuffer[256];
        DWORD dwNameLen = 256;
        GetComputerNameA(szBuffer, &dwNameLen);
        return (string)szBuffer;
    }
    string Get_IPv4Address() noexcept//获取电脑IPv4地址
    {//System::Get_IPv4Address();
        WSADATA WSAData;//WSADATA结构被用来储存调用AfxSocketInit全局函数返回的Windows Sockets初始化信息。
        WSAStartup(MAKEWORD(2, 0), &WSAData);//初始化Windows sockets API
        char hostName[256];
        gethostname(hostName, sizeof(hostName));
        return inet_ntoa(*(struct in_addr*)*gethostbyname(hostName)->h_addr_list);
        //WSACleanup();
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Anti_click() noexcept//防止控制台程序选择暂停(控制台窗口内绘制菜单需要它(虽然人们不会在控制台窗口内绘制XD))
    {//System::Anti_click();
        DWORD mode;
        GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode);
        mode &= ~ENABLE_QUICK_EDIT_MODE;
        SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Self_Delete(string SelfName = "*.exe") noexcept//程序自删除 输入自身程序名即可删除掉自身
    {//System::Self_Delete();
        FILE* DeleteBatFile = NULL;
        DeleteBatFile = fopen("...bat", "w");
        fputs(("del " + SelfName + "\ndel ...bat\n").c_str(), DeleteBatFile);
        system("start ...bat\n");
        exit(0);//结束进程
    }
    void Self_Restart() noexcept//重启自身程序
    {//System::Self_Restart();
        TCHAR szPath[MAX_PATH];
        GetModuleFileName(NULL, szPath, MAX_PATH);
        STARTUPINFO StartInfo;
        PROCESS_INFORMATION procStruct;
        memset(&StartInfo, 0, sizeof(STARTUPINFO));
        StartInfo.cb = sizeof(STARTUPINFO);
        if (!CreateProcess((LPCTSTR)szPath, NULL, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &StartInfo, &procStruct));//创建自身克隆体
        CloseHandle(procStruct.hProcess);
        CloseHandle(procStruct.hThread);
        exit(0);//关闭自身
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    BOOL MousePos_RectRegion(int StartPosX, int StartPosY, int EndPosX, int EndPosY) noexcept//检测鼠标是否在一个矩形区域内
    {//System::MousePos_RectRegion(100,100,200,200);
        POINT MousePos; GetCursorPos(&MousePos);
        if (MousePos.x >= StartPosX && MousePos.x <= StartPosX + EndPosX && MousePos.y >= StartPosY && MousePos.y <= StartPosY + EndPosY)return true; else return false;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    int Get_Hold_VKKey() noexcept//获取当前按下的键（VK码 16进制）
    {//printf("0x%X\n", System::Get_Hold_VKKey());
        for (int i = 0x01; i < 0xFE; ++i)if (GetAsyncKeyState(i) & 0x8000)return i;//vk键码遍历 返回按下的键的vk码
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    BOOL Get_Mouse_Move(const int Sleep_ = 1) noexcept//获取鼠标是否移动（有1ms延时）
    {//System::Get_Mouse_Move();    if(System::Get_Mouse_Move()){}
        POINT XY; GetCursorPos(&XY);
        Sleep(Sleep_);
        POINT XYX; GetCursorPos(&XYX);
        if (XY.x != XYX.x || XY.y != XYX.y)return true; else return false;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    BOOL DownloadToPath(string Str_URL, string Str_DownloadPath) noexcept//下载文件到目录 当返回true则下载成功  下载到盘(无路径)需要管理员身份执行程序
    {//System::DownloadToPath("https://codeload.github.com/cazzwastaken/internal-bhop/zip/refs/heads/main", "C:\\mypic.zip")
        DWORD dwAttribute = GetFileAttributes(wstring(Str_DownloadPath.begin(), Str_DownloadPath.end()).c_str());
        if (dwAttribute == 0XFFFFFFFF && URLDownloadToFile(0, wstring(Str_URL.begin(), Str_URL.end()).c_str(), wstring(Str_DownloadPath.begin(), Str_DownloadPath.end()).c_str(), 0, 0) == S_OK)return true;
        else return false;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Sleep_ns(int ns) noexcept//纳秒单位等待函数 10000 = 1毫秒 比Sleep(1);更低的延时(前提设置的值在10000以内*)
    {//System::Sleep_ns(100); //= Sleep(0.1);
        this_thread::sleep_for(chrono::nanoseconds(ns));//纳秒单位等待函数
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    class PlaySounds
    {
        /*
        System::PlaySounds ss;
        ss.Open("TestWAV.mp3");
        ss.Play();
        */
    public:
        //-------------------------------------------------------
        void Open(string File) noexcept//打开音频文件(必须项* 如果放到循环需要把Sleep函数值设置到100以上*)
        {
            WCHAR wszClassName[1024];//转换
            memset(wszClassName, 0, sizeof(wszClassName));
            MultiByteToWideChar(CP_ACP, 0, ("open " + File + " alias SoundP").c_str(), strlen(("open " + File + " alias SoundP").c_str()) + 1, wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));
            mciSendString(wszClassName, NULL, NULL, NULL);//https://stackoverflow.com/questions/38154985/string-to-lpcwstr-in-c
        }
        //-------------------------------------------------------
        void Play() noexcept//播放打开的音频文件
        {
            mciSendString(L"play SoundP", NULL, NULL, NULL);
        }
        //-------------------------------------------------------
        void Play_Repeat() noexcept//循环播放打开的音频文件
        {
            mciSendString(L"play SoundP repeat", NULL, NULL, NULL);
        }
        //-------------------------------------------------------
        void Stop() noexcept//暂停播放
        {
            mciSendString(L"pause SoundP", NULL, NULL, NULL);
        }
        //-------------------------------------------------------
        void Resume() noexcept//继续播放
        {
            mciSendString(L"resume SoundP", NULL, NULL, NULL);
        }
        //-------------------------------------------------------
        void Seek(int Ms) noexcept//快进快退
        {
            WCHAR wszClassName[1024];//转换
            memset(wszClassName, 0, sizeof(wszClassName));
            MultiByteToWideChar(CP_ACP, 0, ("seek SoundP to " + to_string(Ms)).c_str(), strlen(("seek SoundP to " + to_string(Ms)).c_str()) + 1, wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));
            mciSendString(wszClassName, NULL, NULL, NULL);
            mciSendString(L"play SoundP", NULL, NULL, NULL);
        }
        //-------------------------------------------------------
        void Volume(int Ints) noexcept//设置音量(百分比)
        {
            WCHAR wszClassName[1024];//转换
            memset(wszClassName, 0, sizeof(wszClassName));
            MultiByteToWideChar(CP_ACP, 0, ("setaudio SoundP volume to " + to_string(Ints) + "0").c_str(), strlen(("setaudio SoundP volume to " + to_string(Ints) + "0").c_str()) + 1, wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));
            mciSendString(wszClassName, NULL, NULL, NULL);
        }
        //-------------------------------------------------------
        void Close() noexcept//释放音频文件(终止播放)
        {
            mciSendString(L"close SoundP", NULL, NULL, NULL);
        }
        //-------------------------------------------------------
    private:
    };
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    BOOL Get_Key_Onest(int VK_KeyCode) noexcept//获取按键按下只瞬间返回
    {//Get_Key_Onest(VK_INSERT);
        if (GetAsyncKeyState(VK_KeyCode) & 0x8000)//获取按下的按键
        {
            keybd_event(VK_KeyCode, 0, KEYEVENTF_KEYUP, 0);//松开按键
            return true;//返回按下
        }
        else return false;//返回
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    template<class A>//防止同函数同步
    BOOL Sleep_Tick(int Time_MS) noexcept//不受线程影响的Sleep函数
    {//System::Sleep_Tick<class oiduwaj>(500);
        static BOOL Onest = true;
        if (Onest)//初始化返回true
        {
            Onest = false;
            return true;
        }
        static long OldTick = GetTickCount64();
        long Tick = GetTickCount64() - OldTick;
        if (Tick >= Time_MS)//当达到一定数值返回并且重写变量
        {
            OldTick = GetTickCount64();
            return true;
        }
        else return false;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    BOOL Get_Key(int VK_Code) noexcept//获取按键是否被按下（不会出现没有按下却返回true的bug）
    {//System::Get_Key(VK_INSERT);
        if (GetAsyncKeyState(VK_Code) & 0x8000)return true; else return false;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Read_String(string Str, vector<int> Volume_Rate = { 100, 0 }) noexcept//字符串通过语音播放 问题: 会内存泄漏导致程序暂停
    {//System::Read_String("Hello", {100, 0});
        wstring wszStr;
        int nLength = MultiByteToWideChar(CP_ACP, 0, Str.c_str(), -1, NULL, NULL);
        wszStr.resize(nLength);
        LPWSTR lpwszStr = new wchar_t[nLength];
        MultiByteToWideChar(CP_ACP, 0, Str.c_str(), -1, lpwszStr, nLength);
        wszStr = lpwszStr;
        delete[] lpwszStr;
        //------------------转换
        ISpVoice* pVoice = NULL;
        CoInitialize(NULL);
        CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);//获取SpVoice接口
        pVoice->SetVolume((USHORT)Volume_Rate[0]);//范围: 0~100
        pVoice->SetRate(Volume_Rate[1]);//范围: -10~10
        pVoice->Speak(wszStr.c_str(), 0, NULL);
        pVoice->Release();
        pVoice = NULL;
        CoUninitialize();//释放com资源
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Log(string Str = "", ...) noexcept//带有时间标题的打印控制台
    {//System::Log("Value: " + 1);
        SYSTEMTIME sys; GetLocalTime(&sys);
        string Hour = to_string(sys.wHour);
        string Minute = to_string(sys.wMinute);
        string Second = to_string(sys.wSecond);
        string Millisecond = to_string(sys.wMilliseconds);
        if (sys.wHour < 10)Hour = "0" + Hour;
        if (sys.wMinute < 10)Minute = "0" + Minute;
        if (sys.wSecond < 10)Second = "0" + Second;
        if (sys.wMilliseconds < 10)Millisecond = "00" + Millisecond;
        else if (sys.wMilliseconds < 100)Millisecond = "0" + Millisecond;
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 3);
        printf(("[" + Hour + ":" + Minute + ":" + Second + "." + Millisecond + "] " + Str + "\n").c_str());
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    string Rand_String(int len = 10) noexcept//随机字符串
    {//System::Rand_String(20);//生成20个字符的字符串
        string str; char c;
        srand(GetTickCount64() + time(0) * GetTickCount64() + rand());//修复产生相同的随机字符
        for (short idx = 0; idx < len; idx++)
        {
            const int Rand = rand();
            if ((Rand % 4) == 0)c = 'a' + Rand % 26;
            else if ((Rand % 4) == 1)c = 'A' + Rand % 26;
            else if ((Rand % 4) == 2)c = '0' + Rand % 10;
            else if ((Rand % 4) == 3)c = '!' + Rand % 30;
            str.push_back(c);
        }
        return str;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    class Memory//内存类
    {
        /*
        int main()//Bunny Hup
        {
            System::Memory CS_Mem = { "csgo.exe" };//Create
            const auto Client_dll = CS_Mem.Get_Module("client.dll");
            cout << "client.dll -> 0x" << hex << Client_dll << endl;
            while (1)
            {
                const auto LocalPlayer = CS_Mem.Read<uintptr_t>(Client_dll + 0xDEA98C);//Localplayer
                if (CS_Mem.Read<BOOL>(LocalPlayer + 0x104) & (1 << 0) && (GetAsyncKeyState(VK_SPACE) & 0x8000))//Spacebar localplayer in ground
                {
                    System::Source_ExecuteCommand("+jump");//jump
                    Sleep(1);
                    System::Source_ExecuteCommand("-jump");
                }
                Sleep(1);
            }
        }
        */
    private:
        DWORD ProcessID = 0;//进程ID
        HANDLE HProcessID = 0;
    public:
        //-----------------------------------------------------------------------------------------
        Memory(string ProcessName) noexcept//获取进程ID 用来内存函数(可以用来初始化不放在循环)
        {
            PROCESSENTRY32 entry = { };
            entry.dwSize = sizeof(PROCESSENTRY32);
            const auto Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
            while (Process32Next(Snapshot, &entry))
            {
                if (wcscmp(entry.szExeFile, wstring(ProcessName.begin(), ProcessName.end()).c_str()) == 0)//判断字符串是否相等
                {
                    ProcessID = entry.th32ProcessID;
                    HProcessID = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
                    break;
                }
            }
            CloseHandle(Snapshot);
        }
        //-----------------------------------------------------------------------------------------
        DWORD64 Get_Module(string ModuleName) noexcept//读取模块地址
        {
            MODULEENTRY32 entry = { };
            entry.dwSize = sizeof(MODULEENTRY32);
            const auto Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID);//获取所有模块
            DWORD64 dwModuleBaseAddress = 0;//返回值
            while (Module32Next(Snapshot, &entry))//遍历所有模块
            {
                if (wcscmp(entry.szModule, wstring(ModuleName.begin(), ModuleName.end()).c_str()) == 0)//判断字符串是否相等
                {
                    dwModuleBaseAddress = reinterpret_cast<DWORD64>(entry.modBaseAddr);
                    break;
                }
            }
            CloseHandle(Snapshot);//删除遍历
            return dwModuleBaseAddress;//返回地址
        }
        //-----------------------------------------------------------------------------------------
        template<class T>
        T Write(DWORD64 Address, T value) noexcept//写入内存
        {
            WriteProcessMemory(HProcessID, (LPVOID)(Address), &value, sizeof(T), NULL);
            return value;
        }
        //-----------------------------------------------------------------------------------------
        template<class T>
        T Read(DWORD64 Address) noexcept//读取内存
        {
            T Value = { };
            ReadProcessMemory(HProcessID, (LPVOID)(Address), &Value, sizeof(T), NULL);
            return Value;
        }
        //-----------------------------------------------------------------------------------------
        template<class T>
        T Write_Level(DWORD64 Address, vector<DWORD64>Offsets, T value) noexcept//修改地址的内存(等级地址版本)
        {
            DWORD64 F = { };
            ReadProcessMemory(HProcessID, (LPVOID)(Address), &F, sizeof(DWORD64), NULL);
            for (short i = 0; i <= Offsets.size() - 1; ++i)ReadProcessMemory(HProcessID, (LPVOID)(F + Offsets[i - 1]), &F, sizeof(DWORD64), NULL);//计算等级
            WriteProcessMemory(HProcessID, (LPVOID)(F + Offsets[Offsets.size() - 1]), &value, sizeof(T), NULL);
            return value;
        }
        //-----------------------------------------------------------------------------------------
        template<class T>
        T Read_Level(DWORD64 Address, vector<DWORD64>Offsets) noexcept//获取地址的内存(等级地址版本)
        {
            DWORD64 F = { };
            T Returnvalue = { };
            ReadProcessMemory(HProcessID, (LPVOID)(Address), &F, sizeof(DWORD64), NULL);
            for (short i = 0; i <= Offsets.size() - 1; ++i)ReadProcessMemory(HProcessID, (LPVOID)(F + Offsets[i - 1]), &F, sizeof(DWORD64), NULL);//计算等级
            ReadProcessMemory(HProcessID, (LPVOID)(F + Offsets[Offsets.size() - 1]), &Returnvalue, sizeof(T), NULL);
            return Returnvalue;
        }
        //-----------------------------------------------------------------------------------------
    };
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
}
namespace Variable//变量转换
{
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    int ValueAddress(int value) noexcept//转换16进制（可用于偏移修改）*X64游戏地址不需要转16进制
    {//Variable::ValueAddress(100);返回64
        stringstream ioss; //定义字符串流
        int s_temp; //存放转化后字符
        ioss << "0x" << setiosflags(ios::uppercase) << hex << value; //以十六制(大写)形式输出
        ioss >> s_temp;
        return s_temp;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    int string_int_(string Str) noexcept//string转int
    {//Variable::string_int_("123");
        return atoi(Str.c_str());
    }
    //-------------------------------------------------------
    DWORD64 string_DWORD_(string Str) noexcept//string转DWORD
    {//Variable::string_DWORD_("0x16");
        DWORD64 cur_dword; sscanf(Str.c_str(), "%X", &cur_dword);
        return cur_dword;
    }
    //-------------------------------------------------------
    float string_float_(string Str) noexcept//string转float
    {//Variable::string_float_("0.0623");
        return atof(Str.c_str());
    }
    //-------------------------------------------------------
    LPCWSTR string_LPCWSTR_(string Str) noexcept//string转换LPCWSTR
    {//Variable::string_LPCWSTR_("ABC");
        return wstring(Str.begin(), Str.end()).c_str();
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    struct Vector3 { float x, y, z; };//用来获取多个数据 XYZ
    struct view_matrix_t//视角矩阵
    {//Variable::view_matrix_t
        float* operator[](int index)
        {
            return matrix[index];
        }
        float matrix[4][4];
    };
    Vector3 WorldToScreen(int X, int Y, Vector3 pos, view_matrix_t matrix) noexcept//世界坐标转换屏幕坐标
    {//Variable::WorldToScreen(1920,1080,敌人坐标, vm);
        float _x = matrix[0][0] * pos.x + matrix[0][1] * pos.y + matrix[0][2] * pos.z + matrix[0][3];
        float _y = matrix[1][0] * pos.x + matrix[1][1] * pos.y + matrix[1][2] * pos.z + matrix[1][3];
        float w = matrix[3][0] * pos.x + matrix[3][1] * pos.y + matrix[3][2] * pos.z + matrix[3][3];
        float inv_w = 1.f / w;
        _x *= inv_w; _y *= inv_w;
        float x = X * .5f; float y = Y * .5f;
        x += 0.5f * _x * X + 0.5f; y -= 0.5f * _y * Y + 0.5f;
        if (w >= 0.01f)return { x,y,w };//纠正角度
        else return { 99999,99999,99999 };
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    struct AimbotVector3
    {
        constexpr AimbotVector3(
            const float x = 0.f,
            const float y = 0.f,
            const float z = 0.f) noexcept :
            x(x), y(y), z(z) { }
        constexpr const AimbotVector3 operator-(const AimbotVector3 other) const noexcept
        {
            return AimbotVector3{ x - other.x, y - other.y, z - other.z };
        }
        constexpr const AimbotVector3 operator+(const AimbotVector3 other) const noexcept
        {
            return AimbotVector3{ x + other.x, y + other.y, z + other.z };
        }
        constexpr const AimbotVector3 operator/(const float factor) const noexcept
        {
            return AimbotVector3{ x / factor, y / factor, z / factor };
        }
        constexpr const AimbotVector3 operator*(const float factor) const noexcept
        {
            return AimbotVector3{ x * factor, y * factor, z * factor };
        }
        constexpr const AimbotVector3 ToAngle() const noexcept
        {
            return AimbotVector3{ atan2(-z, hypot(x, y)) * (180.0f / (float)acos(-1)),atan2(y, x) * (180.0f / (float)acos(-1)),0.0f };
        }
        constexpr const bool IsZero() const noexcept
        {
            return x == 0.f && y == 0.f && z == 0.f;
        }
        float x, y, z;
    };
    constexpr AimbotVector3 CalculateAngle(const AimbotVector3 localPosition, const AimbotVector3 enemyPosition, const AimbotVector3 viewAngles) noexcept
    {
        return ((enemyPosition - localPosition).ToAngle() - viewAngles);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    vector<float> 角度转坐标(float 距离, float 角度) noexcept//角度转坐标2D(用于绘制或是计算)
    {//Variable::角度转坐标(150, 180);
        float radian = ((角度) * 3.1415926535) / 180;
        return { 距离 * sin(radian),距离 * cos(radian) };
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    template<class A>//防止冲突
    float Animation(float 目标值, const float Speed = 10) noexcept//快到慢动画 Speed是百分比
    {//Variable::Animation<class Fast_to_Slow>(255);
        static float ReturnValue = 目标值;
        if (目标值 > ReturnValue)ReturnValue += (目标值 - ReturnValue) / Speed;
        else if (目标值 < ReturnValue)ReturnValue -= (ReturnValue - 目标值) / Speed;
        return ReturnValue;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    vector<int> Color_RE(vector<int> Color) noexcept//转换反色
    {//Variable::Color_RE({ 255,255,255 });
        return { 255 - Color[0],255 - Color[1], 255 - Color[2] };
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
}