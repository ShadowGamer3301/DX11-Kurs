#include "Window.h"
#include "loguru.hpp"
#include "ini.h"
#include <string>
#include <sstream>

Window::Window()
{
	//Otwórz plik konfiguracyjny
	mINI::INIFile cfg_file("Config.ini");
	mINI::INIStructure cfg_struct;
	
	bool ReadSucess = cfg_file.read(cfg_struct);
	
	if (!ReadSucess)
	{
		throw std::runtime_error("Failed to load configuration file");
	}

	//Konwersja const char* do const wchar_t*
	std::wstringstream wss;
	wss << cfg_struct["Window"]["Title"].c_str();
	std::wstring wstr = wss.str();

	//Konwersja const char* do const wchar_t*
	std::wstringstream wss2;
	wss2 << cfg_struct["Window"]["Icon"].c_str();
	std::wstring wstr_icon = wss2.str();

	UINT icon_flag = LR_LOADFROMFILE | LR_DEFAULTSIZE;

	HANDLE hIcon = LoadImage(nullptr, wstr_icon.c_str(), IMAGE_ICON, 0, 0, icon_flag);

	if (hIcon == NULL)
	{
		throw std::runtime_error("Failed to load icon");
	}

	//Stworzenie i zdefiniowanie klasy okna
	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = (HICON)hIcon;
	wcex.hCursor = nullptr;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = wstr.c_str();
	wcex.hIconSm = (HICON)hIcon;

	//Rejstracja klasy okna
	if (!RegisterClassEx(&wcex))
	{
		throw std::runtime_error("Failed to register window class");
	}

	//Swtórz okno
	m_hWnd = CreateWindow(wstr.c_str(), wstr.c_str(), WS_OVERLAPPEDWINDOW, 0, 0, std::stoi(cfg_struct["Window"]["Width"]), std::stoi(cfg_struct["Window"]["Height"]), nullptr, nullptr, m_hInstance, nullptr);
	if (!m_hWnd)
	{
		throw std::runtime_error("Failed to create a window");
	}

	//Poka¿ okno
	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
}

LRESULT Window::WindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
		break;
	}
}
