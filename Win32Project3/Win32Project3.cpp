// Win32Project3.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Win32Project3.h"
#include <afx.h>
using namespace std;

#define MAX_LOADSTRING 100

#define map_size 100
#define Tetris_size 4

// 全局变量: 

HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
MAX m;											//最大值类名
HBRUSH hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
HBRUSH hBrush1 = (HBRUSH)GetStockObject(NULL_BRUSH);
HBRUSH hBrush2 = (HBRUSH)GetStockObject(GRAY_BRUSH);
int time_passed=0;

HFONT font = CreateFont(30, 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, NULL, CString("Simsun"));


VOID DrawMap(HDC hdc)
{
	SelectObject(hdc, hBrush);
	SelectObject(hdc, font);
	MoveToEx(hdc, 0, 300, NULL);
	LineTo(hdc, 600, 300);

	MoveToEx(hdc, 300, 0, NULL);
	LineTo(hdc, 300, 600);

	for (int x = -7; x < 8; x++)
	{
		MoveToEx(hdc, 300 + x * 30, 300, NULL);
		LineTo(hdc, 300 + x * 30, 295);
	}

	for (int y = -7; y < 8; y++)
	{
		MoveToEx(hdc, 300 , 300 + y * 30, NULL);
		LineTo(hdc, 305, 300 + y * 30);
	}

	for (int i = 0; i < m.popu; i++)
	{
		double x = m.all_x[i][0];
		double y = m.all_x[i][1];
		
		Rectangle(hdc, (int)(30 * (x + 10)), (int)(30 * (y + 10)), (int)(30 * (x + 10)) + Tetris_size, (int)(30 * (y + 10)) + Tetris_size);
	}

	char strx1[20] = { '\0' };
	char stry1[20] = { '\0' };
	sprintf_s(strx1, "%.9f", m.all_x[0][0]);
	sprintf_s(stry1, "%.9f", m.all_x[0][1]);
	CString strx = strx1;
	CString stry = stry1;
	CString str = m.rst;
	char t[10] = {'\0'};
	_itoa_s(time_passed, t, 10);
	CString tt = t;

	
	TextOut(hdc, map_size * 7, 50, TEXT("x,y: ") + strx + TEXT(", ") + stry, wcslen(TEXT("x,y: ") + strx + TEXT(", ") + stry));
	TextOut(hdc, map_size * 7, 100, TEXT("当前最大值为：")+str, wcslen(TEXT("当前最大值为：") + str));
	TextOut(hdc, map_size * 7, 150, TEXT("计算次数：") + tt+TEXT("次"), wcslen(TEXT("计算次数：") + tt + TEXT("次")));
}



// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此放置代码。

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WIN32PROJECT3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT3));

	MSG msg;

	// 主消息循环: 
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT3));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WIN32PROJECT3);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CREATE:
		{
			//产生随机数种子
			time_t rawtime = 0;
			time(&rawtime);
			srand((unsigned int)rawtime);
			//初始化一个种群的所有个体
			for (int i = 0; i < m.popu; i++)
				m.init(m.pop[i]);
			//InvalidateRect(hWnd, NULL, TRUE);
			SetTimer(hWnd, 1, 1000, NULL);
			break;
		}
		case WM_TIMER:
		{
			m.procForOutput();
			InvalidateRect(hWnd, NULL, TRUE);
			//每次执行进化一代
			m.FMAX(1);
			time_passed++;
			break;
		}
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// 分析菜单选择: 
			switch (wmId)
			{
				case IDM_ABOUT:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: 在此处添加使用 hdc 的任何绘图代码...
			DrawMap(hdc);
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
	}
	return (INT_PTR)FALSE;
}
