#include <windows.h>
#include <stdio.h>
#include <math.h>

POINT center;


LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT ("Clocks, Clocks, Clocks...") ;
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass ;
	
	wndclass.style = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc = WndProc ;
	wndclass.cbClsExtra = 0 ;
	wndclass.cbWndExtra = 0 ;
	wndclass.hInstance = hInstance ;
	wndclass.hIcon = NULL ;
	wndclass.hCursor = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
	wndclass.lpszMenuName = NULL ;
	wndclass.lpszClassName = szAppName ;

	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL, TEXT ("Shit happens! Unable to register the class."),szAppName, MB_ICONERROR) ;
		return 0 ;
	}

	hwnd = CreateWindow (szAppName, TEXT ("Clocks, Clocks, Clocks..."),
	WS_OVERLAPPEDWINDOW,
	CW_USEDEFAULT, CW_USEDEFAULT,
	CW_USEDEFAULT, CW_USEDEFAULT,
	NULL, NULL, hInstance, NULL) ;
	ShowWindow (hwnd, iCmdShow) ;
	UpdateWindow (hwnd) ;

	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage (&msg) ;
		DispatchMessage (&msg) ;
	}

	return msg.wParam ;
}

int computeDistance(POINT one,POINT two)
{
	return sqrt(pow((float)one.x-two.x,2)+pow((float)one.y-two.y,2));
}

float computeAngle(POINT p,POINT center1)
{
	float x,y;
	x=p.x-center1.x;
	y=p.y-center1.y;
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

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	static int cxClient, cyClient ;
	static SYSTEMTIME previousTime;
	static HFONT font;
	HDC hdc ;
	PAINTSTRUCT ps ;
	SYSTEMTIME time ;
	RECT rect;
	char str[256];
	int i;
	POINT p,clockCenter,centerForLines;
	static POINT minute[4],hour[4];
	static HBRUSH hourBrush,minuteBrush;
	static HPEN secondPen,secondWhitePen;


	switch (message)
	{
	case WM_CREATE :
		SetTimer (hwnd, 1, 1000, NULL) ;
		GetLocalTime (&time) ;
		previousTime.wMinute=0;
		previousTime.wHour=0;

		hourBrush=CreateSolidBrush(RGB(0,255,0));
		minuteBrush=CreateSolidBrush(RGB(255,255,0));
		secondPen=CreatePen(PS_SOLID,2,RGB(255,0,0));
		secondWhitePen=CreatePen(PS_SOLID,4,RGB(255,255,255));

		font=CreateFont(80,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
               CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Lucida Console"));
		return 0 ;
	
	case WM_SIZE :
		cxClient = LOWORD (lParam) ;
		cyClient = HIWORD (lParam) ;
		center.x=cxClient/2;
		center.y=cyClient/2;

		return 0 ;

	case WM_TIMER :
		InvalidateRect(hwnd,NULL,FALSE);
		return 0 ;

	case WM_PAINT :
		hdc = BeginPaint (hwnd, &ps) ;
/*
		rect.left=center.x-center.y;
		rect.top=0;
		rect.right=center.x+center.y;
		rect.bottom=center.y*2;

		FillRect(hdc,&rect,WHITE_BRUSH);

		*/
		GetLocalTime(&time);
		
		sprintf(str," %i:%i:%i ",time.wHour, time.wMinute, time.wSecond);
		SelectObject(hdc,font);
		TextOutA(hdc,center.x-(strlen(str)-1)*25,center.y*2-100,str,strlen(str));
		
		SetTextColor(hdc, RGB(0,0,255));
		p.x=center.x;
		p.y=0;
		clockCenter=center;
		clockCenter.y*=0.7;
		centerForLines.x=clockCenter.x;
		centerForLines.y=clockCenter.y+40;

		minute[0]=centerForLines;
		minute[1].x=center.x-10;
		minute[1].y=center.y*.5;
		minute[2].x=center.x;
		minute[2].y=0;
		minute[3].x=center.x+10;
		minute[3].y=minute[1].y;

		hour[0]=centerForLines;
		hour[1].x=center.x-20;
		hour[1].y=center.y*.5;
		hour[2].x=center.x;
		hour[2].y=0;
		hour[3].x=center.x+20;
		hour[3].y=minute[1].y;


		//CLEAR EVERYTHING:
		MoveToEx(hdc,centerForLines.x,centerForLines.y,NULL);
		p.x=centerForLines.x+centerForLines.y*cos(2*3.14*(time.wSecond-16)/60);
		p.y=centerForLines.y+centerForLines.y*sin(2*3.14*(time.wSecond-16)/60);
		SelectObject(hdc,secondWhitePen);
		LineTo(hdc,p.x,p.y);


		SelectObject(hdc,GetStockObject(WHITE_BRUSH));
		for (i=0; i<4; i++)
		{
			rotatePoint(&hour[i],2*3.14*(time.wHour-1)/12,centerForLines);
			//sprintf(str,"x=%i y=%i \n",minute[i].x,minute[i].y);
			//OutputDebugStringA(str);
		}
		for (i=0; i<4; i++)
		{
			rotatePoint(&minute[i],2*3.14*(time.wMinute-1)/60,centerForLines);
			//sprintf(str,"x=%i y=%i \n",minute[i].x,minute[i].y);
			//OutputDebugStringA(str);
		}
		Polygon(hdc,hour,4);
		Polygon(hdc,minute,4);



		SelectObject(hdc,GetStockObject(BLACK_PEN));
		SelectObject(hdc,GetStockObject(BLACK_BRUSH));
		minute[0]=centerForLines;
		minute[1].x=center.x-10;
		minute[1].y=center.y*.5;
		minute[2].x=center.x;
		minute[2].y=0;
		minute[3].x=center.x+10;
		minute[3].y=minute[1].y;

		hour[0]=centerForLines;
		hour[1].x=center.x-20;
		hour[1].y=center.y*.5;
		hour[2].x=center.x;
		hour[2].y=0;
		hour[3].x=center.x+20;
		hour[3].y=minute[1].y;
		
		Ellipse(hdc,centerForLines.x-10,centerForLines.y-10,centerForLines.x+10,centerForLines.y+10);
		for (i=1; i<=12; i++)
		{
			p.x=clockCenter.x+clockCenter.y*cos(2*3.14*(i-3)/12);
			p.y=clockCenter.y+40+clockCenter.y*sin(2*3.14*(i-3)/12);
			//rotatePoint(&p,2*3.14/12);
			itoa(i,str,10);
			TextOutA(hdc,p.x-25,p.y-40,str,strlen(str));
		}





		SelectObject(hdc,hourBrush);
		for (i=0; i<4; i++)
		{
			rotatePoint(&hour[i],2*3.14*(time.wHour)/12,centerForLines);
			//sprintf(str,"x=%i y=%i \n",minute[i].x,minute[i].y);
			//OutputDebugStringA(str);
		}
		Polygon(hdc,hour,4);


		SelectObject(hdc,minuteBrush);
		for (i=0; i<4; i++)
		{
			rotatePoint(&minute[i],2*3.14*(time.wMinute)/60,centerForLines);
			//sprintf(str,"x=%i y=%i \n",minute[i].x,minute[i].y);
			//OutputDebugStringA(str);
		}
		Polygon(hdc,minute,4);




		MoveToEx(hdc,centerForLines.x,centerForLines.y,NULL);
		p.x=centerForLines.x+centerForLines.y*cos(2*3.14*(time.wSecond-15)/60);
		p.y=centerForLines.y+centerForLines.y*sin(2*3.14*(time.wSecond-15)/60);
		SelectObject(hdc,secondPen);
		LineTo(hdc,p.x,p.y);


			//MessageBox(hwnd,TEXT("awe"),NULL,NULL);






		


		previousTime=time;
		EndPaint (hwnd, &ps) ;
		return 0 ;

	case WM_DESTROY :
		KillTimer (hwnd, 1) ;
		DeleteObject(hourBrush);
		DeleteObject(minuteBrush);
		DeleteObject(secondPen);
		DeleteObject(secondWhitePen);
		PostQuitMessage (0) ;
		return 0 ;
	}

return DefWindowProc (hwnd, message, wParam, lParam) ;
}
