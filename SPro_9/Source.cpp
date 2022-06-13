#include <windows.h>
#include <xstring>
#include <string>
typedef std::basic_string<TCHAR, std::char_traits<TCHAR>,
	std::allocator<TCHAR> > String;

using namespace std;

#define ID_NUM1 444
#define ID_NUM2 555
#define ID_SUM 666
#define ID_FIB 777
#define ID_FAC 999

#define ID_OUTPUT 888

//String dec2bin(int num);
//string formString(int* pointer);

int doSum(int num);
int doFib(int num);
int doFac(int num);


HINSTANCE hInst;
LPCTSTR szWindowClass = (LPCTSTR)"QWERTY";
LPCTSTR szTitle = (LPCTSTR)"ÂÎÑÜÌÀ ÏÐÎÃÐÀÌÀ";

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_HAND);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = NULL;
	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance;
	hWnd = CreateWindow(szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		400,
		150,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hWnd)
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}
HWND firstEdit, secondEdit , sumButton, fibButton, facButton/*, outputText*/;
int s[32];
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt;

	string get, result;

	for (int i = 0; i < 32; i++)
		s[i] = 0;

	switch (message)
	{
	case WM_CREATE:
		firstEdit = CreateWindow((LPCSTR)"edit", (LPCSTR)"0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 90, 40, 70, 25, hWnd, (HMENU)ID_NUM1, NULL, NULL);
		secondEdit = CreateWindow((LPCSTR)"edit", (LPCSTR)"0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, 220, 40, 70, 25, hWnd, (HMENU)ID_NUM2, NULL, NULL);
		sumButton = CreateWindow((LPCSTR)"button", (LPCSTR)"sum", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON, 165, 10, 50, 25, hWnd, (HMENU)ID_SUM, NULL, NULL);
		fibButton = CreateWindow((LPCSTR)"button", (LPCSTR)"fib", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON, 165, 40, 50, 25, hWnd, (HMENU)ID_FIB, NULL, NULL);
		facButton = CreateWindow((LPCSTR)"button", (LPCSTR)"fac", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON, 165, 70, 50, 25, hWnd, (HMENU)ID_FAC, NULL, NULL);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND:
		switch (wParam) {
		case ID_SUM:
			GetWindowText(firstEdit, &get[0], 3);

			result = std::to_string(doSum(stoi(get)));

			SetWindowTextA(secondEdit, &result[0]);
			break;

		case ID_FIB:
			GetWindowText(firstEdit, &get[0], 3);

			result = std::to_string(doFib(stoi(get)));

			SetWindowTextA(secondEdit, &result[0]);
			break;


		case ID_FAC:
			GetWindowText(firstEdit, &get[0], 3);

			result = std::to_string(doFac(stoi(get)));

			SetWindowTextA(secondEdit, &result[0]);
			break;
		}

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
int Sum(int num)
{
	__asm
	{
		mov eax,num
		mov ebx, 0
		mov ecx, eax
		c :
			add ebx, ecx
		loop c
		mov eax,ebx	
		
	}
}
int doSum(int num)
{
	int result;
	__asm
	{
		mov eax, num
		push eax
		call [Sum]
		mov result, eax
		pop eax
	}
	return result;
}
int Fib(unsigned int num)
{
	__asm
	{
		
		mov eax, num
		mov ebx, 0
		mov edx, 1
		mov ecx, eax
		//0 1 1 2 3 5 8 13 21 
		c :
		mov eax, edx
			add edx, ebx
			mov ebx, eax

			loop c
			mov eax, edx

	}
}
int doFib(int num)
{
	int result;
	__asm
	{
		mov eax, num
		
		push eax
	
		call[Fib]
		mov result, eax
		
		pop eax
		
	}
	return result;
}
int Fac(unsigned int num)
{
	__asm
	{
		mov eax, num
		mov ebx, 1
		mov ecx, eax
		c :
		imul ebx, ecx
			loop c
			mov eax, ebx
	}
}
int doFac(int num)
{
	int result;
	__asm
	{
		mov eax, num

		push eax

		call[Fac]
		mov result, eax

		pop eax

	}
	return result;
}