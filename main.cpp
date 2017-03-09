#include "Windows.h"
#include "resource.h"
#include "cmath"
#include "stdio.h"
BOOL CALLBACK DialogProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char Text[64];
	double x, z;
	switch (message)
	{
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hwnd, LOWORD(wParam));
			break;
		case IDC_BUTTON_Y1:
		case IDC_BUTTON_Y2:
			SendDlgItemMessage(hwnd, IDC_EDITX, WM_GETTEXT, 63, (LPARAM)Text);
			if (sscanf_s(Text, "%lf", &x) < 1)
			{
				MessageBox(hwnd, "Неверный формат первого операнда", "Ошибка формата", MB_OK | MB_ICONHAND);
				return TRUE;
			}
			char Func;
			if (LOWORD(wParam) == IDC_BUTTON_Y1) { z = exp(x); Func = 'e'; }
			if (LOWORD(wParam) == IDC_BUTTON_Y2) { z = 2 * x;  Func = '2'; }
			sprintf(Text, "%f", z);
			SendDlgItemMessage(hwnd, IDC_EDIT_Y, WM_SETTEXT, 0, (LPARAM)Text);
			sprintf_s(Text, "%c(%f)=%f", Func, x, z);
			SendDlgItemMessage(hwnd, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)Text);
			break;
		case IDC_BUTTON_CLEAR:
			SendDlgItemMessage(hwnd, IDC_LIST1, LB_RESETCONTENT, 0, 0);
			return TRUE;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		return FALSE;
	}
	return FALSE;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DialogProc);
	return 0;
}

