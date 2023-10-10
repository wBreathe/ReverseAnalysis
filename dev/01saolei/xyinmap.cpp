#include <stdio.h>
#include <windows.h>
#define KEY_DOWN(state) (state&0x8000 ? true:false) //获取鼠标点击并弹起事件
#include <iostream>

using namespace std;

//int main() {
//	//找到扫雷窗口的句柄
//	HWND hWnd = FindWindow(NULL, "扫雷");
//	short b_state_pre, b_state_post;
//	while (1) {
//		b_state_pre = GetAsyncKeyState(VK_LBUTTON);
//		Sleep(100);
//		b_state_post = GetAsyncKeyState(VK_LBUTTON);
//		if (KEY_DOWN(b_state_pre) && !KEY_DOWN(b_state_post)){
//			POINT p;
//			GetCursorPos(&p); //在屏幕的位置坐标
//			printf("key down of the whole screen: %d, %d\n", p.x, p.y);
//			ScreenToClient(hWnd, &p); //在窗口的位置坐标
//			printf("key down of the window: %d, %d\n", p.x, p.y);
//		}
//		Sleep(100);
//	}
//	return 0;
//}