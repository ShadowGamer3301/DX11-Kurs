#include "DxBase.h"

DxBase::DxBase(HWND hWnd)
{
    //Otwórz plik konfiguracyjny
    mINI::INIFile cfg_file("Config.ini");
    mINI::INIStructure cfg_struct;

    bool ReadSucess = cfg_file.read(cfg_struct);

    if (!ReadSucess)
    {
        throw std::runtime_error("Failed to load configuration file");
    }

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = std::stoi(cfg_struct["Window"]["Width"]);
    sd.BufferDesc.Height = std::stoi(cfg_struct["Window"]["Height"]);
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Denominator = 144;
    sd.BufferDesc.RefreshRate.Numerator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    D3D_FEATURE_LEVEL fLevels[] = 
    {
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
            D3D_FEATURE_LEVEL_9_3,
            D3D_FEATURE_LEVEL_9_2,
            D3D_FEATURE_LEVEL_9_1,
    };

    HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, fLevels, ARRAYSIZE(fLevels), D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pDevice, NULL, &m_pDeviceContext);
    if (FAILED(hr))
    {
        throw std::runtime_error("D3D11CreateDeviceAndSwapChain failed");
    }

    ID3D11Texture2D* pBB;
    if (FAILED(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBB)))
    {
        throw std::runtime_error("m_pSwapChain->GetBuffer failed");
    }
    hr = m_pDevice->CreateRenderTargetView(pBB, NULL, &m_pRenderTV);
    pBB->Release();
    if (FAILED(hr))
        throw std::runtime_error("m_pSwapChain->GetBuffer failed");

    m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTV, NULL);


    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)std::stoi(cfg_struct["Window"]["Width"]);;
    vp.Height = (FLOAT)std::stoi(cfg_struct["Window"]["Height"]);
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    m_pDeviceContext->RSSetViewports(1, &vp);
}

DxBase::~DxBase()
{
}

void DxBase::Render(float r, float g, float b, float a)
{
    float ClearColor[4] = { r,g,b,a };
    m_pDeviceContext->ClearRenderTargetView(m_pRenderTV, ClearColor);

    m_pSwapChain->Present(0, 0);
}
