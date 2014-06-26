//Last time modified: 27.02.2012
//Author: Chetrusca Maxim


//Include everything:
#include <windows.h>
#include <math.h>

//Declare the windows procedure:
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);


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
		TEXT("The First Laboratory work"), //Caption
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

int computeDistance(POINT one,POINT two)
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
	//char str[256];


	//sprintf(str,"%i \n",distance);
	//OutputDebugStringA(str);
	currentAngle=computeAngle(*p,center);

	currentAngle+=angle;
	p->x=center.x+computeDistance(*p,center)*cos(currentAngle);
	p->y=center.y+computeDistance(*p,center)*sin(currentAngle);
}



LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	switch(message)
	{
	case WM_PAINT:
		hdc=BeginPaint(hwnd,&ps);

		GetClientRect(hwnd,&rect);

		DrawText(hdc,TEXT("Chetrusca Maxim's laboratory work No 1"),-1,&rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd,&ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd,message,wParam,lParam);
	
}