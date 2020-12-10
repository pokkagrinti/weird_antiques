#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <iostream>
#include <time.h>

#define WM_QUIT                         0x0012

HHOOK hHook{ NULL };

void moveMouse(int x, int y) {

	int count = 30;
	int movex, movey;
	float angle = 0.0f;

	// set mouse at center screen
	SetCursorPos(x, y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	// begin spiral! :)


	for (int i = 30; i <= count + 30; i++) {
		angle = 0.6 * i;
		movex = (angle * cos(angle) * 2) + x;
		movey = (angle * sin(angle) * 2) + y;
		SetCursorPos(movex, movey);
		Sleep(20);
	}

}

int randomgen(int min, int max)
{
	int range = max - min + 1;
	return rand() % range + min;
}
enum Keys
{
	ShiftKey = 16,
	Capital = 20,
};

int shift_active() {
	return GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0;
}

int capital_active() {
	return (GetKeyState(VK_CAPITAL) & 1) == 1;
}

LRESULT CALLBACK keyboard_hook(const int code, const WPARAM wParam, const LPARAM lParam) {
	if (wParam == WM_KEYDOWN) {
		KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
		DWORD wVirtKey = kbdStruct->vkCode;
		DWORD wScanCode = kbdStruct->scanCode;

		BYTE lpKeyState[256];
		GetKeyboardState(lpKeyState);
		lpKeyState[Keys::ShiftKey] = 0;
		lpKeyState[Keys::Capital] = 0;
		if (shift_active()) {
			lpKeyState[Keys::ShiftKey] = 0x80;
		}
		if (capital_active()) {
			lpKeyState[Keys::Capital] = 0x01;
		}
		srand(time(0));

		char result;
		ToAscii(wVirtKey, wScanCode, lpKeyState, (LPWORD)&result, 0);

		if (result == 'a') {



			std::cout << "HARISH" << std::endl;

			SetCursorPos(800, 400);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			Sleep(10);
			SetCursorPos(850, 300);
			Sleep(10);
			SetCursorPos(900, 200);
			Sleep(10);
			SetCursorPos(950, 300);
			Sleep(10);
			SetCursorPos(1000, 400);
			Sleep(10);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			
		}

		if (result == 's') {
			std::cout << "HARISH" << std::endl;

			SetCursorPos(800, 200);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			Sleep(10);
			SetCursorPos(850, 300);
			Sleep(10);
			SetCursorPos(900, 400);
			Sleep(10);
			SetCursorPos(950, 300);
			Sleep(10);
			SetCursorPos(1000, 200);
			Sleep(10);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

		}

		if (result == 'k') {

			std::cout << "HARISH" << std::endl;

			SetCursorPos(800 + randomgen(10,20), 200 + randomgen(0, 10));
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			Sleep(20);
			SetCursorPos(800 + randomgen(10, 20), 300 + randomgen(0, 10));
			Sleep(20);
			SetCursorPos(800 + randomgen(10, 20), 400 + randomgen(0, 10));
			Sleep(20);
			SetCursorPos(800 + randomgen(10, 20), 500 + randomgen(0, 10));
			Sleep(20);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}

		if (result == 'l') {
			std::cout << "HARISH" << std::endl;

			SetCursorPos(800 + randomgen(0, 10), 300 + randomgen(10, 20));
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			Sleep(20);
			SetCursorPos(900 + randomgen(0, 10), 300 + randomgen(10, 20));
			Sleep(20);
			SetCursorPos(1000 + randomgen(0, 10), 300 + randomgen(10, 20));
			Sleep(20);
			SetCursorPos(1100 + randomgen(0, 10), 300 + randomgen(10, 20));
			Sleep(20);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}

		if (result == 'j') {

			
			moveMouse(900, 450);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}

		if (result == 'q') {
			PostQuitMessage(0);
		}

	}

	return CallNextHookEx(hHook, code, wParam, lParam);
}



int main(int argc, char* argv[])
{
	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboard_hook, NULL, 0);
	if (hHook == NULL) {
		std::cout << "Keyboard hook failed!" << std::endl;
	}

	while (GetMessage(NULL, NULL, 0, 0));
	return 0;
}