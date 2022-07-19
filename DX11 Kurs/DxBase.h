#pragma once
#include "Window.h"
#include <D3D11.h>
#include <D3DX11.h>
#include "ini.h"

class DxBase
{
public:
	DxBase(HWND hWnd);
	~DxBase();

	void Render(float r, float g, float b, float a);

private:
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	ID3D11RenderTargetView* m_pRenderTV;
	IDXGISwapChain* m_pSwapChain;
};

