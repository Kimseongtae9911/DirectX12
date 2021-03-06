#include "pch.h"
#include "GameFramework.h"

void CGameFramework::OnCreate(HINSTANCE hInstance, HWND hMainWnd)
{
    ::srand(timeGetTime());

    m_hInstance = hInstance;
    m_hWnd = hMainWnd;

    BuildFrameBuffer();

    BuildObjects();

    _tcscpy_s(m_pszFrameRate.data(), m_pszFrameRate.size(), _T("LabProject ("));
}

void CGameFramework::OnDestroy()
{
    ReleaseObjects();

    if (m_hBitmapFrameBuffer)
        ::DeleteObject(m_hBitmapFrameBuffer);
    if (m_hDCFrameBuffer)
        ::DeleteDC(m_hDCFrameBuffer);
}

void CGameFramework::BuildFrameBuffer()
{
    ::GetClientRect(m_hWnd, &m_rcClient);

    HDC hdc = ::GetDC(m_hWnd);

    m_hDCFrameBuffer = ::CreateCompatibleDC(hdc);
    m_hBitmapFrameBuffer = ::CreateCompatibleBitmap(hdc, m_rcClient.right - m_rcClient.left, m_rcClient.bottom - m_rcClient.top);
    ::SelectObject(m_hDCFrameBuffer, m_hBitmapFrameBuffer);

    ::ReleaseDC(m_hWnd, hdc);
    ::SetBkMode(m_hDCFrameBuffer, TRANSPARENT);
}

void CGameFramework::ClearFrameBuffer(DWORD dwColor)
{
    HPEN hPen = ::CreatePen(PS_SOLID, 0, dwColor);
    HPEN hOldPen = (HPEN)::SelectObject(m_hDCFrameBuffer, hPen);
    HBRUSH hBrush = ::CreateSolidBrush(dwColor);
    HBRUSH hOldBrush = (HBRUSH)::SelectObject(m_hDCFrameBuffer, hBrush);

    ::Rectangle(m_hDCFrameBuffer, m_rcClient.left, m_rcClient.top, m_rcClient.right, m_rcClient.bottom);
    ::SelectObject(m_hDCFrameBuffer, hOldBrush);
    ::SelectObject(m_hDCFrameBuffer, hOldPen);
    ::DeleteObject(hPen);
    ::DeleteObject(hBrush);
}

void CGameFramework::PresentFrameBuffer()
{
    HDC hDC = ::GetDC(m_hWnd);
    ::BitBlt(hDC, m_rcClient.left, m_rcClient.top, m_rcClient.right - m_rcClient.left, m_rcClient.bottom - m_rcClient.top, m_hDCFrameBuffer, m_rcClient.left, m_rcClient.top, SRCCOPY);
    ::ReleaseDC(m_hWnd, hDC);
}

void CGameFramework::BuildObjects()
{
}

void CGameFramework::ReleaseObjects()
{
}

void CGameFramework::ProcessInput()
{
}

void CGameFramework::AnimateObjects()
{
}

void CGameFramework::FrameAdvance()
{
    m_GameTimer.Tick(60.0f);

    ProcessInput();

    AnimateObjects();

    ClearFrameBuffer(RGB(125, 20, 255));

    PresentFrameBuffer();

    m_GameTimer.GetFrameRate(m_pszFrameRate.data() + 12, 37);
    ::SetWindowText(m_hWnd, m_pszFrameRate.data());
}

void CGameFramework::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
    switch (nMessageID)
    {
    case WM_RBUTTONDOWN:
    case WM_LBUTTONDOWN:
        break;
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
        break;
    case WM_MOUSEMOVE:
        break;
    default:
        break;
    }
}

void CGameFramework::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
    switch (nMessageID)
    {
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            ::PostQuitMessage(0);
            break;
        case VK_RETURN:
            break;
        case VK_CONTROL:
            break;
        default:           
            break;
        }
        break;
    default:
        break;
    }
}

LRESULT CGameFramework::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
    switch (nMessageID)
    {
    case WM_ACTIVATE:
    {
        if (LOWORD(wParam) == WA_INACTIVE)
            m_GameTimer.Stop();
        else
            m_GameTimer.Start();
        break;
    }
    case WM_SIZE:
        break;
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MOUSEMOVE:
        OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
        break;
    case WM_KEYDOWN:
    case WM_KEYUP:
        OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
        break;
    }
    return(0);
}
