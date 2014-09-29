#define _WIN32_WINNT 0x0500
#define DEBUG 1
#define VERSION 0.1

#include<Windows.h>
#include <stdio.h>

HHOOK hHock = NULL;
bool running = true;
DWORD pauseKey = VK_F8;

void MouseClick()
{
    INPUT buffer[1];
    ZeroMemory(&buffer,sizeof(buffer)); //Prevent the screen to go black LOL
    buffer->type = INPUT_MOUSE;
    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
    SendInput(1, buffer, sizeof(INPUT));
    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
    SendInput(1, buffer, sizeof(INPUT));
}

LRESULT CALLBACK MyLowLevelHook ( int nCode , WPARAM wParam , LPARAM lParam)
{
    KBDLLHOOKSTRUCT *kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
    if (kbdStruct->vkCode == pauseKey) {
        if (wParam == WM_KEYDOWN) {
            if (running) {
                printf("\nDesactivated");
            } else
                printf("\nActivated");
            running = !running;
        }
    }
    else if (running) {
#if DEBUG == 1
        printf(".");
#endif // DEBUG
        if (wParam == WM_KEYUP) {
            //Generate click
            MouseClick();
#if DEBUG == 1
            printf("o");
#endif // DEBUG
        }
    }
    return CallNextHookEx(hHock , nCode ,wParam , lParam);
}

int main(int argc, char *argv[])
{
    printf("--------------------------------------------------------------------------------\n");
    printf("Smarter Quick Cast %.1f\n", VERSION);
    printf("--------------------------------------------------------------------------------\n");

    if (argc == 2) {
        pauseKey == atoi(argv[1]);
        printf("Pause key: 0x%x\n", pauseKey);
    }
    else {
        printf("Default pause key: F8\n");
    }

    MSG msg;
	hHock = SetWindowsHookEx(WH_KEYBOARD_LL, MyLowLevelHook , NULL,NULL);

    printf("Activated");
    while(!GetMessage(&msg, NULL, NULL, NULL)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hHock);
}
