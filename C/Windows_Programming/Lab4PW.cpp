//Include everything:
#include <windows.h>
#include <math.h>
#include <stdio.h>

//Declare the windows procedure:
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
//RECT rect;
POINT pts[10], centre;
float distance[10];

//WinMain:
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR szCmdLine,int iCmdShow)
{

	static	TCHAR szAppName[]=TEXT("ChetruscaLab4");	
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
		TEXT("Keyboard"), //Caption
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
int computeDistance(POINT one)
{
	return sqrt(pow((float)one.x-centre.x,2)+pow((float)one.y-centre.y,2));
}

float computeAngle(POINT p)
{
	float x,y;
	x=p.x-centre.x;
	y=p.y-centre.y;
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

void rotatePoint(POINT *p,float angle,int distanceIndex)
{
	float currentAngle;
	char str[256];


	sprintf(str,"%i \n",distance);
	OutputDebugStringA(str);
	currentAngle=computeAngle(*p);

	currentAngle+=angle;
	p->x=centre.x+distance[distanceIndex]*cos(currentAngle);
	p->y=centre.y+distance[distanceIndex]*sin(currentAngle);
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int i,width,height;
	char str[256];

	switch(message)
	{
	case WM_ACTIVATEAPP:
		//hdc=GetDC(hwnd);
		width=GetSystemMetrics(SM_CXFULLSCREEN);
		height=GetSystemMetrics(SM_CYFULLSCREEN);
		for (i=0; i<10; i++)
		{
		pts[i].x=rand()%400;
		pts[i].y=rand()%400;
		centre.x+=pts[i].x;
		centre.y+=pts[i].y;
		}
		centre.x/=10;
		centre.y/=10;
		for (i=0; i<10; i++)
		{
			distance[i]=computeDistance(pts[i]);
		}
		sprintf(str,"x=%i y=%i",centre.x,centre.y);
		OutputDebugStringA(str);

		

		//FillRect(hdc,&rect,(HBRUSH)GetStockObject(BLACK_BRUSH));
		//Polygon(hdc,pts,10);
		//ReleaseDC(hwnd,hdc);
		return 0;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_DOWN:
			//MessageBox(hwnd,TEXT("DOWN"),NULL,NULL);
			for (i=0; i<10; i++)
			{
				pts[i].y+=20;
			}
			centre.y+=20;
			break;
		case VK_UP:
			//MessageBox(hwnd,TEXT("UP"),NULL,NULL);
			for (i=0; i<10; i++)
			{
				pts[i].y-=20;
			}
			centre.y-=20;
			break;	
		case VK_LEFT:
			//MessageBox(hwnd,TEXT("LEFT"),NULL,NULL);
			for (i=0; i<10; i++)
			{
				pts[i].x-=20;
			}
			centre.x-=20;

			break;
		case VK_RIGHT:
			//MessageBox(hwnd,TEXT("RIGHT"),NULL,NULL);
			for (i=0; i<10; i++)
			{
				pts[i].x+=20;
			}
			centre.x+=20;
			break;
		}

		InvalidateRect(hwnd,NULL,TRUE);
		//hdc=GetDC(hwnd);

		//FillRect(hdc,&rect,(HBRUSH)GetStockObject(BLACK_BRUSH));
		
		//ReleaseDC(hwnd,hdc);

		return 0;
		
	case WM_CHAR:
		switch(wParam)
		{
		case  '+':
			//MessageBox(hwnd,TEXT("+"),NULL,NULL);
			for (i=0; i<10; i++)
			{
				rotatePoint(&pts[i],0.15,i);
			}
			break;
		case  '-':
			for (i=0; i<10; i++)
			{
				rotatePoint(&pts[i],-0.15,i);
			}
			//MessageBox(hwnd,TEXT("-"),NULL,NULL);
			break;
		}
		InvalidateRect(hwnd,NULL,TRUE);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hwnd,&ps);

		//FillRect(hdc,&rect,(HBRUSH)GetStockObject(BLACK_BRUSH));
		SelectObject(hdc,(HBRUSH)GetStockObject(BLACK_BRUSH));
		Polygon(hdc,pts,10);

		EndPaint(hwnd,&ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd,message,wParam,lParam);
	
}