#include <Windows.h>
#include <random>
#include <thread>
#include <vector>

DWORD WINAPI CursorGDI(LPVOID parameters32)
{
    HDC hdc = GetDC(0);
    POINT cursor;
    INT32 ix = GetSystemMetrics(SM_CXICON) / 2;
    INT32 iy = GetSystemMetrics(SM_CYICON) / 2;
    while (true)
    {
        GetCursorPos(&cursor);
        DrawIcon(hdc, cursor.x - ix, cursor.y - iy, LoadIconW(0, IDI_ERROR));
    }
}

DWORD WINAPI ColorHellGDI(LPVOID param)
{
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    int signX = 1;
    int signY = 1;
    int signX1 = 1;
    int signY1 = 1;
    int incrementor = 10;
    int x = 10;
    int y = 10;
    for (;;)
    {
        HDC hdc = GetDC(0);
        x += incrementor * signX;
        y += incrementor * signY;
        int top_x = 0 + x;
        int top_y = 0 + y;
        int bottom_x = 100 + x;
        int bottom_y = 100 + y;
        POINT cursor;
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, brush);
        BitBlt(hdc, x, y, w, h, hdc, rand() % 2, rand() % 2, PATINVERT);
        if (y >= GetSystemMetrics(SM_CYSCREEN))
        {
            signY = -1;
        }
        if (x >= GetSystemMetrics(SM_CXSCREEN))
        {
            signX = -1;
        }
        if (y == 0)
        {
            signY = 1;
        }
        if (x == 0)
        {
            signX = 1;
        }
        Sleep(10);
        DeleteObject(brush);
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI MeltGDI(LPVOID parameters32)
{
    for (;;)
    {
        HDC hdcWindow = GetDC(0);
        int nRandWidth = 150, nRandHeight = 15;
        int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
        int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
        int	nXPos = (rand() % nScreenWidth) - (nRandWidth / 2),
            nYPos = (rand() % nRandHeight),
            nWidth = (rand() % nRandWidth);
        BitBlt(hdcWindow, nXPos, nYPos, nWidth, nScreenHeight, hdcWindow, nXPos, 0, SRCCOPY);
        ReleaseDC(0, hdcWindow);
    }
}

DWORD WINAPI RainbowGDI(LPVOID parameters32)
{
    int time = GetTickCount();
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    for (int i = 0;; i++, i %= 3) {
        HDC desk = GetDC(NULL);
        HDC hdcdc = CreateCompatibleDC(desk);
        HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcdc, hbm);
        BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
        GetBitmapBits(hbm, 4 * h * w, data);
        int v = 0;
        BYTE byte = 0;
        if ((GetTickCount() - time) > 10)
            byte = rand() % 0xff;
        for (int i = 0; w * h > i; ++i) {
            if (!(i % h) && !(rand() % 110))
                v = rand() % 24;
            *((BYTE*)data + 4 * i + v) -= 5;
        }
        SetBitmapBits(hbm, w * h * 4, data);
        BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);
        DeleteObject(hbm);
        DeleteObject(hdcdc);
        DeleteObject(desk);
    }
}

DWORD WINAPI FlashGDI(LPVOID parameters32)
{
    SetProcessDPIAware();
    int sw = GetSystemMetrics(0);
    int sh = GetSystemMetrics(1);
    double color32 = 0.0;
    srand(static_cast<unsigned int>(time(0)));

    for (;;)
    {
        HDC hdc = GetDC(0);
        INT32 r = static_cast<int>(std::fmod(color32, 1.0) * 255);
        INT32 g = static_cast<int>(std::fmod(color32 + 0.333, 1.0) * 255);
        INT32 b = static_cast<int>(std::fmod(color32 + 0.666, 1.0) * 255);
        HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
        SelectObject(hdc, brush);
        BitBlt(hdc, rand() % 21 - 10, rand() % 21 - 10, sw, sh, hdc, 0, 0, NOTSRCCOPY);
        BitBlt(hdc, rand() % 21 - 10, rand() % 21 - 10, sw, sh, hdc, 0, 0, SRCCOPY);
        BitBlt(hdc, rand() % 21 - 10, rand() % 21 - 10, sw, sh, hdc, 0, 0, PATINVERT);
        DeleteObject(brush);
        ReleaseDC(0, hdc);
        color32 += 0.05;
    }
}