#include <windows.h>


typedef struct CHARACTER
{
	TCHAR c;
	int x;
	int y;
	int color;
}CHARACTER;

int numberOfCharacters;
CHARACTER *p;
LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);




VOID CALLBACK timer(HWND hwnd,UINT message, UINT id,DWORD time)
{
	static int calls;
	int i,n;
	HDC hdc;
	RECT rect;
	HBRUSH hBrush;
	TCHAR c;
	hdc=GetWindowDC(hwnd);

	SetBkColor(hdc,RGB(0,0,0));
	SetTextColor(hdc,RGB(0,255,0));
	SelectObject(hdc,CreateFont(20,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
               CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Lucida Console")));
	if (calls==0)
	{
		SetTimer(hwnd,2,50,timer);
		HideCaret(hwnd);
		DestroyCaret();
		TextOut(hdc,0,0,TEXT("  "),2);
	}

		n=numberOfCharacters;
		for(i=0; i<n; i++)
		{
			if (p[i].color) SetTextColor(hdc,RGB(p[i].color,255,p[i].color));
			else SetTextColor(hdc,RGB(0,0,0));
					if (p[i].y==0)
					{

						p=(CHARACTER*)realloc(p,(numberOfCharacters+1)*sizeof(CHARACTER));
						p[numberOfCharacters].c=rand()%256;
						p[numberOfCharacters].x=p[i].x;
						p[numberOfCharacters].y=0;
						if (p[i].color)
						{
							p[numberOfCharacters].color=p[i].color-20;
							if (p[numberOfCharacters].color<0) p[numberOfCharacters].color=1;
							if (calls%10==0 && i%3==0) p[numberOfCharacters].color=0;
						}
						else
						{
							p[numberOfCharacters].color=p[i].color;
						}
						TextOut(hdc,p[numberOfCharacters].x,p[numberOfCharacters].y,&p[numberOfCharacters].c,1);
						numberOfCharacters++;

					}
					TextOut(hdc,p[i].x,p[i].y+20,&p[i].c,1);


					p[i].y+=20;	

		}


		if (calls%2==0)
		{

			c=(TCHAR)rand()%256;
			p=(CHARACTER*)realloc(p,(numberOfCharacters+1)*sizeof(CHARACTER));
			p[numberOfCharacters].c=c;
	
				p[numberOfCharacters].x=rand()%GetSystemMetrics(SM_CXSCREEN);
				p[numberOfCharacters].y=0;

			p[numberOfCharacters].color=255;
			TextOut(hdc,p[numberOfCharacters].x,p[numberOfCharacters].y,&p[numberOfCharacters].c,1);
			numberOfCharacters++;
		}

		if (calls%300==0)
		{
			rect.left=0;
			rect.top=0;
			rect.right=GetSystemMetrics(SM_CXSCREEN);
			rect.bottom=GetSystemMetrics(SM_CYSCREEN);
			
			FillRect(hdc,&rect,(HBRUSH)GetStockObject(BLACK_BRUSH));
			p=(CHARACTER*)realloc(p,sizeof(CHARACTER));
			numberOfCharacters=1;
		}

		calls++;
		ReleaseDC(hwnd,hdc);

}

VOID CALLBACK timer1(HWND hwnd,UINT message, UINT id,DWORD time)
{
	HDC hdc;
	static int i;
	TCHAR c;
	char a[26]="Destroy the system";
	hdc=GetWindowDC(hwnd);
	SetBkColor(hdc,RGB(0,0,0));
	SetTextColor(hdc,RGB(0,255,0));
	SelectObject(hdc,CreateFont(20,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
               CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Lucida Console")));
	if (i<18)
	{
		HideCaret(hwnd);
		c=(TCHAR)a[i];
		TextOut(hdc,10+12*i,10,TEXT("  "),2);
		TextOut(hdc,10+12*i,10,&(TCHAR)c,1);
		SetCaretPos(30+12*i,10);
		ShowCaret(hwnd);
		SetTimer(hwnd,3,150,timer1);
	}
	else
	{
		KillTimer(hwnd,3);
		SetTimer(hwnd,2,3000,timer);
	}
	i++;
	ReleaseDC(hwnd,hdc);
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE nPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[]=TEXT("WP Lab 2 Window");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;



	wndclass.cbClsExtra=0;
	wndclass.cbWndExtra=0;
	wndclass.hbrBackground=CreateSolidBrush(RGB(0,0,255));//(HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hInstance=hInstance;
	wndclass.lpfnWndProc=WindowProcedure;
	wndclass.lpszClassName=szAppName;
	wndclass.lpszMenuName=NULL;
	wndclass.style=CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL,TEXT("Could not register the window class!"),szAppName,MB_ICONERROR);
		return 0;
	}

//Creates an overlapped, pop-up, or child window with an extended window style; 
	//otherwise - identical with CreateWindow

	hwnd=CreateWindowEx(WS_EX_LEFT, //The window has generic left-aligned properties. This is the default.
		szAppName,
		TEXT("Matrix"),
		WS_POPUP,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);




	ShowWindow(hwnd,iCmdShow);

	UpdateWindow(hwnd);


	ShowCursor(FALSE); //Cursor is invisible

	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}



LRESULT CALLBACK WindowProcedure(HWND hwnd,UINT message, WPARAM wParam, LPARAM lParam)
{
	static int calls;
	POINT apt[100];
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	HBRUSH hBrush;

	TCHAR c;
	int i,k;
	int x,y;
	switch(message)
	{
	case WM_CREATE:
		numberOfCharacters=0;
		return 0;

	case WM_ACTIVATEAPP:
		SetTimer(hwnd,1,3000,NULL);
		SetWindowPos(hwnd,HWND_TOP,0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),0L);
		hdc=GetWindowDC(hwnd);

		SetBkColor(hdc,RGB(0,0,255));
		SetTextColor(hdc,RGB(255,255,255));
		SelectObject(hdc,CreateFont(20,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
               CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Lucida Console")));
		TextOut(hdc,10,20,TEXT("A problem has been detected and Windows has been shut down to prevent damage to your computer."),94);
		TextOut(hdc,10,80,TEXT("Technical Information:"),22);	
		TextOut(hdc,10,140,TEXT("*** STOP: 0x00000D1 (0x000000C, 0x00DF200, 0x000000, 0xFD970031)"),64);
		TextOut(hdc,10,160,TEXT("*** gv3.sys - Address F86B541A9 base at 0x00000D1"),49);
		TextOut(hdc,10,240,TEXT("Beggining dump of physical memory"),33);
		TextOut(hdc,10,260,TEXT("Physical memory dump complete."),30);
		


		ReleaseDC(hwnd,hdc);
		return 0;
		
	case WM_TIMER:
		calls++;
		SetTimer(hwnd,1,100,NULL);
		hdc=GetWindowDC(hwnd);

		rect.left=0;
		rect.top=0;
		rect.right=GetSystemMetrics(SM_CXSCREEN);
		rect.bottom=GetSystemMetrics(SM_CYSCREEN);

		apt[0].x=rand()%GetSystemMetrics(SM_CXSCREEN);
		apt[0].y=rand()%GetSystemMetrics(SM_CYSCREEN);
		for(i=1; i<100; i++)
		{
			x=rand()%2;
			y=rand()%2;
			if (!x) x=-1;
			if (!y) y=-1;
				apt[i].x=apt[i-1].x+x*rand()%20*(calls/10);
				apt[i].y=apt[i-1].y+y*rand()%20*(calls/10);
		}
		SelectObject(hdc,(HBRUSH)GetStockObject(BLACK_BRUSH));
		Polygon(hdc,apt,100);
		if (calls>100)
		{	
		FillRect(hdc,&rect,(HBRUSH)GetStockObject(BLACK_BRUSH));
		KillTimer(hwnd,1);


		SetBkColor(hdc,RGB(0,0,0));
		SetTextColor(hdc,RGB(0,255,0));
		SelectObject(hdc,CreateFont(20,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
               CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Lucida Console")));
		CreateCaret(hwnd,NULL,10,20);
		SetCaretPos(10,10);
		ShowCaret(hwnd);
		SetTimer(hwnd,3, 3000,timer1);
		}

		ReleaseDC(hwnd,hdc);
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		KillTimer(hwnd,2);
		return 0;
	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}