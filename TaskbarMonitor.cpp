#include <windows.h>
#include <commctrl.h>
#include "crtrepl.h"

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

const size_t BUF_SZ = 1024;

struct Configuration
{
	size_t MaintainedWidth;
};

void GetConfigPath(wchar_t* ConfigPath, size_t ConfigPathSz)
{
	// Search for ini file in the application directory
	if (GetModuleFileName(NULL, ConfigPath, static_cast<DWORD>(ConfigPathSz)) == 0)
	{
		*ConfigPath = L'\0';
		return;
	}

	size_t path_len = wcslen(ConfigPath);

	size_t idx_slash, idx_dot;
	idx_slash = wcsrchr_pos(ConfigPath, path_len, L'\\');
	idx_dot = wcsrchr_pos(ConfigPath, path_len, L'.');
	if ((idx_dot == 0) || ((idx_slash != 0) && (idx_dot < idx_slash)))
	{
		// Extension not found, append '.ini'
		if (path_len + 5 > ConfigPathSz)
		{
			*ConfigPath = L'\0';
			return;
		}
		wcscpylen_s(ConfigPath + path_len, ConfigPathSz - path_len, L".ini");
	}
	else
	{
		// Extension found, replace with 'ini'
		if (idx_dot + 4 > ConfigPathSz)
		{
			*ConfigPath = L'\0';
			return;
		}
		wcscpylen_s(ConfigPath + idx_dot, ConfigPathSz - idx_dot, L"ini");
	}
}

bool ReadConfig(const wchar_t* ConfigPath, Configuration* ConfigData)
{
	if (ConfigData == NULL)
		return false;
	ConfigData->MaintainedWidth = GetPrivateProfileInt(L"Configuration", L"MaintainedWidth", 175, ConfigPath);
	return true;
}

int wWinMainCRTStartup(void)
{
	const WCHAR* const MsgBoxTitle = L"Taskbar Monitor";
	Configuration ConfigData;
	wchar_t ConfigPath[BUF_SZ];
	GetConfigPath(ConfigPath, BUF_SZ);

	InitCommonControls();

	HWND hTaskbarWnd = FindWindow(L"Shell_TrayWnd", NULL);
	if (!hTaskbarWnd)
	{
		MessageBox(NULL, L"Taskbar window was not found!", MsgBoxTitle, MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}

	HANDLE hMutex = CreateMutex(NULL, TRUE, L"Global\\TaskbarMonitor");
	if ((hMutex != NULL) && (GetLastError() == ERROR_ALREADY_EXISTS))
	{
		MessageBox(NULL, L"Application is already running!", MsgBoxTitle, MB_OK | MB_ICONWARNING);
		ExitProcess(0);
	}

	ReadConfig(ConfigPath, &ConfigData);

	RECT rc;
	for (;;)
	{
		Sleep(1000);
		if (!GetWindowRect(hTaskbarWnd, &rc))
		{
			hTaskbarWnd = FindWindow(L"Shell_TrayWnd", NULL);
			continue;
		}
		if ((rc.right - rc.left) == ConfigData.MaintainedWidth)
			continue;

		if (rc.left < 0)
			rc.left = 0;
		rc.right = rc.left + static_cast<LONG>(ConfigData.MaintainedWidth);

		SendMessage(hTaskbarWnd, WM_SIZING, WMSZ_RIGHT, (LPARAM)&rc);
		SetWindowPos(hTaskbarWnd, NULL, 0, 0, static_cast<int>(ConfigData.MaintainedWidth), rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}
