//Author: Chetrusca Maxim


//Include everything:
#include <windows.h>
#include <math.h>
#include <stdio.h>

//Declare the windows procedure:
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int distance;

//WinMain:
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR szCmdLine,int iCmdShow)
{

	static	TCHAR szAppName[]=TEXT("ChetruscaLab1");	
	HWND hwnd; //Handle var for window
	MSG msg;
	WNDCLASS wndclass; //Define this class:

	//defines all the fields of the class:
	wndclass.style= CS_HREDRAW | CS_VREDRAW; //windows redraws if we change the size horizontally or vertically
	wndclass.lpfnWndProc=WndProc;//long pointer to a function which handles the events : windows procedure
	wndclass.cbClsExtra=0;
	wndclass.cbWndExtra=0;
	wndclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hInstance=hInstance;
	wndclass.lpszClassName=szAppName;
	wndclass.lpszMenuName=NULL;

	//Register the class: 
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL,TEXT("Failed to register wndclass!"),szAppName,MB_ICONERROR);
		return 0;
	}

	//Create the window:
	hwnd=CreateWindow(szAppName, //window class name - should coincide with wndclass.lpszClassName !!!
		TEXT("Child windows"), //Caption
		WS_OVERLAPPEDWINDOW, //window style
		CW_USEDEFAULT, //initial x position
		CW_USEDEFAULT, // intitial y position
		CW_USEDEFAULT, //initial x size
		CW_USEDEFAULT, //initial y size
		NULL, //parent window handle - MessageBox, for example, will create a window in a window
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);// it should be drawn for the first time

	//Message-loop
	while (GetMessage(&msg,NULL,0,0))//returns 0 at Close or Alt+F4
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

float computeDistance(POINT one,POINT two)
{
	return sqrt(pow((float)one.x-two.x,2)+pow((float)one.y-two.y,2));
}

float computeAngle(POINT p,POINT center)
{
	float x,y;
	x=p.x-center.x;
	y=p.y-center.y;
	if (x>0) return atan(y/x);
	else if (x<0)
	{
		if (y>=0) return atan(y/x)+3.14;
		else if(y<0) return atan(y/x)-3.14;
	}
	else if (x==0)
	{
		if (y>0) return 3.14/2;
		else if (y<0) return -3.14/2;
		else return 0;
	}
}

void rotatePoint(POINT *p,float angle,POINT center)
{

	float currentAngle;
/*	char str[256];


	sprintf(str,"%i \n",computeDistance(*p,center));
	OutputDebugStringA(str);*/
	currentAngle=computeAngle(*p,center);

	currentAngle+=angle;
	p->x=center.x+distance*cos(currentAngle);
	p->y=center.y+distance*sin(currentAngle);
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	HBRUSH hBrush;

	int i;
	static POINT pts[4]={120,150,170,150,170,200,120,200};
	HWND hwndChild;
	static POINT center,rectangleCenter;
	static int timerOn,figure,color; //figure =1 -square, =2 triangle, =3 circle; similar to color

	switch(message)
	{
	case WM_CREATE:

		center.x=320;
		center.y=200;

	
		for (i=0; i<4; i++)
		{
			rectangleCenter.x+=pts[i].x;
			rectangleCenter.y+=pts[i].y;
		}
		rectangleCenter.x/=4;
		rectangleCenter.y/=4;

		distance=computeDistance(rectangleCenter,center);

		timerOn=0;
		figure=0;
		color=0;
		CreateWindow(TEXT("button"),
			TEXT("Rotate"),
			WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			10,
			10,
			100,
			40,
			hwnd,
			(HMENU)0,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		CreateWindow(TEXT("button"),
			TEXT("Stop"),
			WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			10,
			60,
			100,
			40,
			hwnd,
			(HMENU)1,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		CreateWindow(TEXT("button"),
			TEXT("Sqare"),
			WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON,
			10,
			110,
			100,
			40,
			hwnd,
			(HMENU)2,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		CreateWindow(TEXT("button"),
			TEXT("Triangle"),
			WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON,
			10,
			150,
			100,
			40,
			hwnd,
			(HMENU)3,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		CreateWindow(TEXT("button"),
			TEXT("Circle"),
			WS_CHILD|WS_VISIBLE|BS_RADIOBUTTON,
			10,
			190,
			100,
			40,
			hwnd,
			(HMENU)4,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		CreateWindow(TEXT("button"),
			TEXT("Red"),
			WS_CHILD|WS_VISIBLE|BS_CHECKBOX|BS_AUTOCHECKBOX,
			10,
			250,
			100,
			40,
			hwnd,
			(HMENU)5,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		CreateWindow(TEXT("button"),
			TEXT("Green"),
			WS_CHILD|WS_VISIBLE|BS_CHECKBOX|BS_AUTOCHECKBOX,
			10,
			290,
			100,
			40,
			hwnd,
			(HMENU)6,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		CreateWindow(TEXT("button"),
			TEXT("Blue"),
			WS_CHILD|WS_VISIBLE|BS_CHECKBOX|BS_AUTOCHECKBOX,
			10,
			330,
			100,
			40,
			hwnd,
			(HMENU)7,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);

		return 0;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case 0: //Rotate
			timerOn=1;
			SetTimer(hwnd,1,100,NULL);
			//MessageBox(hwnd,TEXT("0"),NULL,NULL);
			break;

		case 1: //Stop
			
			if (timerOn) KillTimer(hwnd,1);
			timerOn=0;
			//MessageBox(hwnd,TEXT("1"),NULL,NULL);
			break;

		case 2: //Sqare
			figure=1;
			hwndChild=GetDlgItem(hwnd,3);
			SendMessage(hwndChild,BM_SETCHECK,0,0);

			hwndChild=GetDlgItem(hwnd,4);
			SendMessage(hwndChild,BM_SETCHECK,0,0);

			SendMessage((HWND)lParam,BM_SETCHECK,1,0);
			break;

		case 3: //Triangle
			figure=2;
			hwndChild=GetDlgItem(hwnd,2);
			SendMessage(hwndChild,BM_SETCHECK,0,0);

			hwndChild=GetDlgItem(hwnd,4);
			SendMessage(hwndChild,BM_SETCHECK,0,0);

			SendMessage((HWND)lParam,BM_SETCHECK,1,0);
			break;

		case 4://Circle
			figure=3;
			hwndChild=GetDlgItem(hwnd,3);
			SendMessage(hwndChild,BM_SETCHECK,0,0);

			hwndChild=GetDlgItem(hwnd,2);
			SendMessage(hwndChild,BM_SETCHECK,0,0);

			SendMessage((HWND)lParam,BM_SETCHECK,1,0);
			break;
		
		case 5://Red
			if (SendMessage((HWND)lParam,BM_GETCHECK,0,0))
			{
				color=1;
				hwndChild=GetDlgItem(hwnd,6);
				EnableWindow(hwndChild,FALSE);

				hwndChild=GetDlgItem(hwnd,7);
				EnableWindow(hwndChild,FALSE);
			}
			else
			{
				color=0;
				hwndChild=GetDlgItem(hwnd,6);
				EnableWindow(hwndChild,TRUE);

				hwndChild=GetDlgItem(hwnd,7);
				EnableWindow(hwndChild,TRUE);
			}

		break;
		
		case 6://Green
			if (SendMessage((HWND)lParam,BM_GETCHECK,0,0))
			{
				color=2;
				hwndChild=GetDlgItem(hwnd,5);
				EnableWindow(hwndChild,FALSE);

				hwndChild=GetDlgItem(hwnd,7);
				EnableWindow(hwndChild,FALSE);
			}
			else
			{
				color=0;
				hwndChild=GetDlgItem(hwnd,5);
				EnableWindow(hwndChild,TRUE);

				hwndChild=GetDlgItem(hwnd,7);
				EnableWindow(hwndChild,TRUE);
			}

		break;

		case 7://blue
			if (SendMessage((HWND)lParam,BM_GETCHECK,0,0))
			{
				color=3;
				hwndChild=GetDlgItem(hwnd,6);
				EnableWindow(hwndChild,FALSE);

				hwndChild=GetDlgItem(hwnd,5);
				EnableWindow(hwndChild,FALSE);
			}
			else
			{
				color=0;
				hwndChild=GetDlgItem(hwnd,6);
				EnableWindow(hwndChild,TRUE);

				hwndChild=GetDlgItem(hwnd,5);
				EnableWindow(hwndChild,TRUE);
			}


		break;
		}
		SetRect(&rect,120,0,520,400);
		InvalidateRect(hwnd,&rect,TRUE);
		return 0;

	case WM_TIMER:
		rotatePoint(&rectangleCenter,0.15,center);
		pts[0].x=rectangleCenter.x-25;
		pts[0].y=rectangleCenter.y-25;
		pts[1].x=rectangleCenter.x+25;
		pts[1].y=pts[0].y;
		pts[2].x=pts[1].x;
		pts[2].y=rectangleCenter.y+25;
		pts[3].x=pts[0].x;
		pts[3].y=pts[2].y;
		SetRect(&rect,120,0,520,400);
		InvalidateRect(hwnd,&rect,TRUE);
		return 0;

	case WM_PAINT:
		hdc=BeginPaint(hwnd,&ps);
		hBrush=NULL;
		if (color==1)
		{
			hBrush=CreateSolidBrush(RGB(255,0,0));
		}
		else if (color==2)
		{
			hBrush=CreateSolidBrush(RGB(0,255,0));
		}
		else if (color==3)
		{
			hBrush=CreateSolidBrush(RGB(0,0,255));
		}
		if (figure==1)
		{
			SelectObject(hdc,hBrush);
			Polygon(hdc,pts,4);
		}
		else if (figure==2)
		{
			POINT pts1[3];
			pts1[0].x=(pts[0].x+pts[1].x)/2;
			pts1[0].y=pts[0].y;
			pts1[1]=pts[2];
			pts1[2]=pts[3];

			SelectObject(hdc,hBrush);
			Polygon(hdc,pts1,3);
		}
		else if(figure==3)
		{
			SelectObject(hdc,hBrush);
			Ellipse(hdc,pts[0].x,pts[0].y,pts[2].x,pts[2].y);
		}

		if (color!=0) DeleteObject(hBrush);
		EndPaint(hwnd,&ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd,message,wParam,lParam);
	
}