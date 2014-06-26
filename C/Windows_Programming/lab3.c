	#include <windows.h>
	#include <math.h>
	#include <stdio.h>


	POINT apt[4]={100,100,200,300,600,100,700,500};
	int leftPointOn,rightPointOn;
	LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);


	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE nPrevInstance, PSTR szCmdLine, int iCmdShow)
	{
		static TCHAR szAppName[]=TEXT("WP Lab 2 Window");
		HWND hwnd;
		MSG msg;
		WNDCLASS wndclass;



		wndclass.cbClsExtra=0;
		wndclass.cbWndExtra=0;
		wndclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
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



		hwnd=CreateWindow(szAppName,
			TEXT("Bezier Curves"),
			WS_OVERLAPPEDWINDOW, 
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



		while (GetMessage(&msg,NULL,0,0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return msg.wParam;
	}


	void drawBezier1(HDC hdc,POINT* apt)
	{
		POINT *drawPoints;
		char str[256];
		int interval,i;
		float t;


		interval=apt[3].x-apt[0].x;
		drawPoints=(POINT*)malloc(interval*(sizeof(POINT)));
		for (i=0; i<4; i++)
		{
			Ellipse(hdc,apt[i].x-10,apt[i].y-10,apt[i].x+10,apt[i].y+10);
		}
		for (i=0; i<interval; i++)
		{
			t=(i*1.0)/interval;
			drawPoints[i].x=pow(1-t,3)*apt[0].x+3*t*pow(1-t,2)*apt[1].x+3*pow(t,2)*(1-t)*apt[2].x+pow(t,3)*apt[3].x;
			drawPoints[i].y=pow(1-t,3)*apt[0].y+3*t*pow(1-t,2)*apt[1].y+3*pow(t,2)*(1-t)*apt[2].y+pow(t,3)*apt[3].y;

			//sprintf(str,"%i %i \n",drawPoints[i].x,drawPoints[i].y);
			//OutputDebugStringA(str);
			//MessageBox(hwnd,TEXT("OK"),NULL,NULL);
		}

		Polyline(hdc,drawPoints,interval);

	}


	LRESULT CALLBACK WindowProcedure(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
	{
		HDC hdc;
		PAINTSTRUCT ps;
		RECT rect;
		int x,y;


		switch(message)
		{
		case WM_LBUTTONDOWN:
			{
				hdc=GetDC(hwnd);
				x=LOWORD(lParam);
				y=HIWORD(lParam);

				SetPixel(hdc,x,y,RGB(255,0,0));
				leftPointOn=1;
				/*if ((x<apt[1].x+10) && (x>apt[1].x-10) && (y<apt[1].y+10) && (y>apt[1].y-10) )
				{
					apt[1].x=x;
					apt[1].y=y;		
					leftPointOn=1;
				}

				if ((x<apt[2].x+10) && (x>apt[2].x-10) && (y<apt[2].y+10) && (y>apt[2].y-10) )
				{
					apt[2].x=x;
					apt[2].y=y;	
					rightPointOn=1;
				}
				*/
				ReleaseDC(hwnd,hdc);
				return 0;
			}
		case WM_LBUTTONUP:
			{
				leftPointOn=0;
				rightPointOn=0;
				return 0;
			}
		case WM_MOUSEMOVE:
			if (leftPointOn)
			{
			/*if (leftPointOn || rightPointOn)
			{*/
					hdc=GetDC(hwnd);
					/*SelectObject(hdc,GetStockObject(WHITE_BRUSH));
					GetClientRect(hwnd,&rect);
					FillRect(hdc,&rect,NULL);
					*/
					x=LOWORD(lParam);
					y=HIWORD(lParam);


					SelectObject(hdc,GetStockObject(BLACK_BRUSH));
					//SetPixel(hdc,x,y,RGB(255,0,0));
					Ellipse(hdc,x-2,y-2,x+2,y+2);
					/*hdc=GetDC(hwnd);
					if (leftPointOn)
					{
						apt[1].x=x;
						apt[1].y=y;	
					}

					if (rightPointOn)
					{
						apt[2].x=x;
						apt[2].y=y;
					}
					SelectObject(hdc,GetStockObject(BLACK_PEN));
					drawBezier1(hdc,apt);
					*/
				ReleaseDC(hwnd,hdc);
			}
			//}


			return 0;
		case WM_PAINT:
			hdc=BeginPaint(hwnd,&ps);
			//drawBezier1(hdc,apt);
			//PolyBezier(hdc,apt,4);
			EndPaint(hwnd,&ps);
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		}

		return DefWindowProc(hwnd,message,wParam,lParam);
	
	}