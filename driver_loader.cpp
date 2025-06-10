// ixusions_loader_gui.cpp
// Minimal GUI for silent driver install/uninstall
// Supports mouse.sys and keyboard.sys

#include <windows.h>
#include <string>
#include <shlobj.h>

const char* MOUSE_SERVICE = "ixusionsM";
const char* KEYBOARD_SERVICE = "ixusionsK";
const char* MOUSE_SYS = "mouse.sys";
const char* KEYBOARD_SYS = "keyboard.sys";

bool CopySysFile(const char* name) {
    char dst[MAX_PATH];
    GetSystemDirectoryA(dst, MAX_PATH);
    strcat_s(dst, "\\drivers\\");
    strcat_s(dst, name);
    return CopyFileA(name, dst, FALSE);
}

bool InstallDriver(const char* serviceName, const char* sysName) {
    char path[MAX_PATH];
    GetSystemDirectoryA(path, MAX_PATH);
    strcat_s(path, "\\drivers\\");
    strcat_s(path, sysName);

    SC_HANDLE scm = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (!scm) return false;

    SC_HANDLE svc = CreateServiceA(
        scm, serviceName, serviceName, SERVICE_ALL_ACCESS,
        SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE,
        path, NULL, NULL, NULL, NULL, NULL);

    if (!svc) svc = OpenServiceA(scm, serviceName, SERVICE_ALL_ACCESS);
    if (!svc) { CloseServiceHandle(scm); return false; }

    StartServiceA(svc, 0, NULL);
    CloseServiceHandle(svc);
    CloseServiceHandle(scm);
    return true;
}

bool UninstallDriver(const char* serviceName) {
    SC_HANDLE scm = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (!scm) return false;

    SC_HANDLE svc = OpenServiceA(scm, serviceName, SERVICE_ALL_ACCESS);
    if (!svc) { CloseServiceHandle(scm); return false; }

    SERVICE_STATUS status;
    ControlService(svc, SERVICE_CONTROL_STOP, &status);
    DeleteService(svc);

    CloseServiceHandle(svc);
    CloseServiceHandle(scm);
    return true;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_COMMAND:
        if (wParam == 1) {
            CopySysFile(MOUSE_SYS);
            CopySysFile(KEYBOARD_SYS);
            InstallDriver(MOUSE_SERVICE, MOUSE_SYS);
            InstallDriver(KEYBOARD_SERVICE, KEYBOARD_SYS);
        }
        else if (wParam == 2) {
            UninstallDriver(MOUSE_SERVICE);
            UninstallDriver(KEYBOARD_SERVICE);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
    const char CLASS_NAME[] = "IxusionsWnd";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, "Ixusions Driver Loader",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 260, 120,
        NULL, NULL, hInst, NULL);

    CreateWindow("BUTTON", "Install Drivers", WS_VISIBLE | WS_CHILD,
        30, 20, 180, 30, hwnd, (HMENU)1, hInst, NULL);

    CreateWindow("BUTTON", "Uninstall Drivers", WS_VISIBLE | WS_CHILD,
        30, 60, 180, 30, hwnd, (HMENU)2, hInst, NULL);

    ShowWindow(hwnd, SW_SHOW);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

