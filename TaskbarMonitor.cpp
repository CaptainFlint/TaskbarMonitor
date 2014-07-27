#include <windows.h>

int wWinMainCRTStartup(void)
{
	const int MaintainedWidth = 175;

	HWND hTaskbarWnd = FindWindow(L"Shell_TrayWnd", NULL);
	if (!hTaskbarWnd)
	{
		MessageBox(NULL, L"Taskbar window was not found!", L"TaskbarMonitor", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}

	RECT rc;
	for (;;)
	{
		Sleep(1000);
		GetWindowRect(hTaskbarWnd, &rc);
		if ((rc.right - rc.left) == MaintainedWidth)
			continue;

		if (rc.left < 0)
			rc.left = 0;
		rc.right = rc.left + MaintainedWidth;

		SendMessage(hTaskbarWnd, WM_SIZING, WMSZ_RIGHT, (LPARAM)&rc);
		SetWindowPos(hTaskbarWnd, NULL, 0, 0, MaintainedWidth, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}
