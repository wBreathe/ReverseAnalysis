#include <stdio.h>
#include <windows.h>
#define KEY_DOWN(state) (state&0x8000 ? true:false) //��ȡ������������¼�
#include <iostream>

using namespace std;

//int main() {
//	//�ҵ�ɨ�״��ڵľ��
//	HWND hWnd = FindWindow(NULL, "ɨ��");
//	short b_state_pre, b_state_post;
//	while (1) {
//		b_state_pre = GetAsyncKeyState(VK_LBUTTON);
//		Sleep(100);
//		b_state_post = GetAsyncKeyState(VK_LBUTTON);
//		if (KEY_DOWN(b_state_pre) && !KEY_DOWN(b_state_post)){
//			POINT p;
//			GetCursorPos(&p); //����Ļ��λ������
//			printf("key down of the whole screen: %d, %d\n", p.x, p.y);
//			ScreenToClient(hWnd, &p); //�ڴ��ڵ�λ������
//			printf("key down of the window: %d, %d\n", p.x, p.y);
//		}
//		Sleep(100);
//	}
//	return 0;
//}