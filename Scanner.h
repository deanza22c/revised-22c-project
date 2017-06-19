#ifndef SCANNER_H
#define SCANNER_H
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<windows.h>   

static HWND  hConWnd;
void displayPicture();
HWND BCX_Bitmap(char*, HWND = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
HWND GetConsoleWndHandle(void);

void startScanner()
{
	system("cls");
	std::cout << "A wild Pokemon has appeared!\n";
	std::cout << "press <Enter> to start scanning the creature...\n";
	std::cin.get();
	//Sleep(5000);
	system("cls");
	std::cout << "scanning...";
	Sleep(1000);
	system("cls");
	Sleep(600);
	std::cout << "scanning...";
	Sleep(1000);
	system("cls");
	Sleep(600);
	std::cout << "scanning...";

	std::cin.get();


	displayPicture();

	std::cout << "press enter to return to main menu...";
	std::cin.get();

}


void displayPicture()
{
	hConWnd = GetConsoleWndHandle();
	if (hConWnd)
	{
		// select a bitmap file you have or use one of the files in the Windows folder
		// filename, handle, ID, ulcX, ulcY, width, height   0,0 auto-adjusts
		BCX_Bitmap("testbitmap.bmp", hConWnd, 123, 1, 1, 0, 0);

		getchar();  // wait
					//DestroyWindow(hConWnd);
	}
}
// draw the bitmap
HWND BCX_Bitmap(char* Text, HWND hWnd, int id, int X, int Y, int W, int H, int Res, int Style, int Exstyle)
{
	HWND pictureFrame;
	HBITMAP hBitmap;

	// set default style
	if (!Style) Style = WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE | SS_BITMAP | WS_TABSTOP;

	// form for the image
	pictureFrame = CreateWindowEx(Exstyle, "static", NULL, Style, X, Y, 0, 0, hWnd, (HMENU)id, GetModuleHandle(0), NULL);

	// Text contains filename
	hBitmap = (HBITMAP)LoadImage(0, Text, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	// auto-adjust width and height
	if (W || H) hBitmap = (HBITMAP)CopyImage(hBitmap, IMAGE_BITMAP, W, H, LR_COPYRETURNORG);
	SendMessage(pictureFrame, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
	if (W || H) SetWindowPos(pictureFrame, HWND_TOP, X, Y, W, H, SWP_DRAWFRAME);

	std::cin.get();

	DestroyWindow(pictureFrame);
	return pictureFrame;
}

// tricking Windows just a little ...
HWND GetConsoleWndHandle(void)
{
	//return 0;
	HWND hConWnd;
	OSVERSIONINFO os;
	char szTempTitle[64], szClassName[128], szOriginalTitle[1024];
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetConsoleTitle(szOriginalTitle, sizeof(szOriginalTitle));
	sprintf_s(szTempTitle, "%u - %u", GetTickCount(), GetCurrentProcessId());
	SetConsoleTitle(szTempTitle);
	Sleep(40);

	hConWnd = FindWindow(NULL, szTempTitle);
	SetConsoleTitle(szOriginalTitle);

	return hConWnd;
}


#endif