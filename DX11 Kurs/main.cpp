#include <Windows.h>
#include "loguru.hpp"

LRESULT WindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

int main(int argc, char** argv)
{
	loguru::init(argc, argv);
	loguru::add_file("Log.txt", loguru::Append, loguru::Verbosity_MAX);

	//Stworzenie i zdefiniowanie klasy okna
	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = nullptr;
	wcex.hIcon = nullptr;
	wcex.hCursor = nullptr;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"BaseWindow";
	wcex.hIconSm = wcex.hIcon;

	//Rejstracja klasy okna
	if (!RegisterClassEx(&wcex))
	{
		LOG_F(ERROR, "Failed to register window class");
		return -1;
	}
	
	//Swtórz okno
	HWND wnd = CreateWindow(L"BaseWindow", L"Kurs DirectX", WS_OVERLAPPEDWINDOW, 0, 0, 1280, 720, nullptr, nullptr, nullptr, nullptr);
	if (!wnd)
	{
		LOG_F(ERROR, "Failed to create window");
		return -1;
	}


	//Poka¿ okno
	ShowWindow(wnd, SW_SHOWDEFAULT);

	MSG msg = {};

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

LRESULT WindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(4);
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
		break;
	}
}