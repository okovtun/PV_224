#include<Windows.h>

CONST CHAR gsz_MY_WINDOW_CLASS[] = "MyWindowClass";

INT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) ����������� ������ ����:
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.cbSize = sizeof(wc);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszClassName = gsz_MY_WINDOW_CLASS;
	wc.lpfnWndProc = (WNDPROC)WndProc;

	//2) �������� ����:
	//3) ������ ����� ���������:
	return 0;
}