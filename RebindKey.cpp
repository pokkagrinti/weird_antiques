#define _WIN32_WINNT 0x0501
#pragma comment( lib, "user32.lib" )

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <ctime>

int randNum(int min, int max)
{
    return rand() % max + min;
}

HHOOK hKeyboardHook;
int deleet = 0;
int randnumber = randNum(1, 3);

__declspec(dllexport) LRESULT CALLBACK KeyboardEvent(int nCode, WPARAM wParam, LPARAM lParam)
{
    DWORD SHIFT_key = 0;
    DWORD CTRL_key = 0;
    DWORD ALT_key = 0;

    if (deleet > randnumber) {
        deleet = 0;
        randnumber = randNum(1, 3);
        INPUT input;
        WORD vkey = '\b'; // see link below
        input.type = INPUT_KEYBOARD;
        input.ki.time = 0;
        input.ki.dwExtraInfo = 0;
        input.ki.wVk = vkey;
        input.ki.dwFlags = 0; // there is no KEYEVENTF_KEYDOWN
        SendInput(1, &input, sizeof(INPUT));

        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input, sizeof(INPUT));
        
    }

    if ((nCode == HC_ACTION) && ((wParam == WM_SYSKEYDOWN) || (wParam == WM_KEYDOWN)))
    {
        KBDLLHOOKSTRUCT hooked_key = *((KBDLLHOOKSTRUCT*)lParam);
        DWORD dwMsg = 1;
        dwMsg += hooked_key.scanCode << 16;
        dwMsg += hooked_key.flags << 24;
        char lpszKeyName[1024] = { 0 };
        //lpszKeyName[0] = '[';

        int i = GetKeyNameTextA(dwMsg, (lpszKeyName + 1), 0xFF) + 1;
        //lpszKeyName[i] = ']';

        
        int key = hooked_key.vkCode;

        SHIFT_key = GetAsyncKeyState(VK_SHIFT);
        CTRL_key = GetAsyncKeyState(VK_CONTROL);
        ALT_key = GetAsyncKeyState(VK_MENU);

        if (key >= 'A' && key <= 'Z')
        {

            if (GetAsyncKeyState(VK_SHIFT) >= 0) key += 32;

            if (CTRL_key != 0 && key == 'q')
            {
                MessageBoxA(NULL, "Shutting down", "H O T K E Y", MB_OK);
                PostQuitMessage(0);
            }

            deleet += 1;

            //printf("key = %c\n", key);
            printf("%c", key);

            SHIFT_key = 0;
            CTRL_key = 0;
            ALT_key = 0;

        }

        //printf("lpszKeyName = %s\n",  lpszKeyName );
    //  printf("%s",  lpszKeyName );
    }
    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

void MessageLoop()
{
    MSG message;
    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

DWORD WINAPI my_HotKey(LPVOID lpParm)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    if (!hInstance) hInstance = LoadLibraryA((LPCSTR)lpParm);
    if (!hInstance) return 1;

    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardEvent, hInstance, NULL);
    MessageLoop();
    UnhookWindowsHookEx(hKeyboardHook);
    return 0;
}

int main(int argc, char** argv)
{   
    srand(time(0));
    HANDLE hThread;
    DWORD dwThread;

    hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)my_HotKey, (LPVOID)argv[0], NULL, &dwThread);

    //ShowWindow(FindWindowA("ConsoleWindowClass", NULL), false);

    if (hThread) return WaitForSingleObject(hThread, INFINITE);
    else return 1;

}