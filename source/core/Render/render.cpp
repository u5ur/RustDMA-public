#include "render.h"
#include <string>
#include <format>
#include <chrono>

ID3D11Device* Device = nullptr;
ID3D11DeviceContext* Context = nullptr;
IDXGISwapChain* SwapChain = nullptr;
ID3D11RenderTargetView* RenderTarget = nullptr;
HWND Window = nullptr;
MSG Msg = {};

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK Render::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (Device && wParam != SIZE_MINIMIZED)
        {
            if (RenderTarget) { RenderTarget->Release(); RenderTarget = nullptr; }

            SwapChain->ResizeBuffers(0, Width, Height, DXGI_FORMAT_UNKNOWN, 0);

            ID3D11Texture2D* backBuffer = nullptr;
            SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
            Device->CreateRenderTargetView(backBuffer, nullptr, &RenderTarget);
            backBuffer->Release();

            Context->OMSetRenderTargets(1, &RenderTarget, nullptr);

            D3D11_VIEWPORT vp = { 0, 0, (FLOAT)Width, (FLOAT)Height, 0.0f, 1.0f };
            Context->RSSetViewports(1, &vp);
        }
        return 0;

    case WM_SYSCOMMAND:
        if ((wParam & 0xFFF0) == SC_KEYMENU)
            return 0;
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

HRESULT Render::InitDirectX()
{
    WNDCLASSEXA wc = {
        sizeof(wc), CS_CLASSDC, WindowProc, 0, 0,
        GetModuleHandle(nullptr), LoadIcon(nullptr, IDI_APPLICATION),
        LoadCursor(nullptr, IDC_ARROW), nullptr, nullptr,
        "RustDMA", LoadIcon(nullptr, IDI_APPLICATION)
    };

    RegisterClassExA(&wc);

    Window = CreateWindowExA(0, "RustDMA", "", WS_POPUP | WS_VISIBLE,
        0, 0, Width, Height, nullptr, nullptr, wc.hInstance, nullptr);

    SetWindowLong(Window, GWL_EXSTYLE, GetWindowLong(Window, GWL_EXSTYLE) | WS_EX_LAYERED | WDA_EXCLUDEFROMCAPTURE);
    SetLayeredWindowAttributes(Window, RGB(0, 0, 0), 255, LWA_ALPHA);
    MARGINS margins = { -1 };
    DwmExtendFrameIntoClientArea(Window, &margins);
    ShowWindow(Window, SW_SHOW);
    UpdateWindow(Window);

    DXGI_SWAP_CHAIN_DESC desc = {};
    desc.BufferCount = 1;
    desc.BufferDesc = { (UINT)Width, (UINT)Height, { 60,1 }, DXGI_FORMAT_R8G8B8A8_UNORM };
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.OutputWindow = Window;
    desc.SampleDesc = { 1, 0 };
    desc.Windowed = TRUE;

    if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
        D3D11_SDK_VERSION, &desc, &SwapChain, &Device, nullptr, &Context)))
        return E_FAIL;

    ID3D11Texture2D* backBuffer = nullptr;
    SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    Device->CreateRenderTargetView(backBuffer, nullptr, &RenderTarget);
    backBuffer->Release();
    Context->OMSetRenderTargets(1, &RenderTarget, nullptr);

    D3D11_VIEWPORT vp = { 0, 0, (FLOAT)Width, (FLOAT)Height, 0.0f, 1.0f };
    Context->RSSetViewports(1, &vp);

    ImGui::CreateContext();
    ImGui_ImplWin32_Init(Window);
    ImGui_ImplDX11_Init(Device, Context);

    return S_OK;
}

WPARAM Render::RenderLoop(void (*func)()) {
    MSG message = { 0 };
    using clock = std::chrono::high_resolution_clock;

    auto lastTime = clock::now();
    int frameCount = 0;
    float fps = 0.0f;

    while (message.message != WM_QUIT) {
        if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else {
            auto now = clock::now();
            frameCount++;
            float elapsed = std::chrono::duration<float>(now - lastTime).count();
            if (elapsed >= 1.0f) {
                fps = frameCount / elapsed;
                frameCount = 0;
                lastTime = now;
            }

            POINT cursorPos;
            GetCursorPos(&cursorPos);
            ImGuiIO& io = ImGui::GetIO();
            io.MousePos = ImVec2(static_cast<float>(cursorPos.x), static_cast<float>(cursorPos.y));
            io.MouseDown[0] = GetAsyncKeyState(VK_LBUTTON) != 0;
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            func();

            // Draw FPS in top-right corner
            char buffer[64];
            snprintf(buffer, sizeof(buffer), "FPS: %.1f", fps);
            ImGui::GetBackgroundDrawList()->AddText(ImVec2(io.DisplaySize.x - 100.0f, 10.0f), IM_COL32(255, 255, 0, 255), buffer);

            ImGui::EndFrame();

            float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
            Context->ClearRenderTargetView(RenderTarget, color);
            ImGui::Render();
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            HRESULT result = SwapChain->Present(0, 0);
            if (result == DXGI_ERROR_DEVICE_REMOVED || result == DXGI_ERROR_DEVICE_RESET) {
                ImGui_ImplDX11_InvalidateDeviceObjects();
                Device->Release();
                Context->Release();
                SwapChain->Release();
                RenderTarget->Release();

                if (FAILED(InitDirectX())) return E_FAIL;
                ImGui_ImplDX11_CreateDeviceObjects();
            }
        }
    }

    return message.wParam;
}
