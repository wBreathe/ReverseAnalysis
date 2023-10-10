#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <cassert>

using namespace std;

int main() {
	HWND hWnd = FindWindow(NULL, "扫雷");
	short xs = 16; //starting x position
	short ys = 61; //starting y position
	short gap = 16; //gap between two blocks
	DWORD start_pos = 0x01005361;
	DWORD column_pos = 0x01005334;
	DWORD row_pos = 0x01005338;
	DWORD dwWidth = 0, dwHeight = 0, curSize = 1;
	PBYTE dwPos = NULL;
	dwPos = (PBYTE)malloc(curSize);

	if (hWnd != 0) {
		DWORD Pid;
		HANDLE hProcess;
		GetWindowThreadProcessId(hWnd, &Pid);
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Pid);
		if (hProcess == 0) {
			printf("Open winmine process failed.");
			return 0;
		}
		DWORD count = 0, i = 0;
		ReadProcessMemory(hProcess, (LPVOID)(column_pos), &dwWidth, sizeof(DWORD), 0);
		ReadProcessMemory(hProcess, (LPVOID)(row_pos), &dwHeight, sizeof(DWORD), 0); //存储的时候先列后行
		while (1) {
			if (count >= dwWidth * dwHeight) {
				break;
			}
			ReadProcessMemory(hProcess, (LPVOID)(start_pos + i), dwPos, curSize, 0);
			++i;

			// 两行中间有0x0f填充
			if (*dwPos == 0x10) {
				while (1) {
					ReadProcessMemory(hProcess, (LPVOID)(start_pos + i), dwPos, curSize, 0);
					++i;
					assert(*dwPos == 0x10 || *dwPos == 0x0f);
					if (*dwPos == 0x10) {
						break;
					}
				}
			}
			if (*dwPos != 0x10) {
				++count;
			}
			int cur_row = 0, cur_col = 0;

			//注意边界block的坐标
			if (*dwPos == 0x0f) {
				if (count % dwWidth == 0) {
					cur_row = count / dwWidth - 1;
					cur_col = dwWidth - 1;
				}
				else {
					cur_row = count / dwWidth;
					cur_col = count % dwWidth - 1;
				}
				SendMessage(hWnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(xs + gap * cur_col, ys + gap * cur_row));   //鼠标按下
				SendMessage(hWnd, WM_LBUTTONUP, MK_LBUTTON, MAKELONG(xs + gap * cur_col, ys + gap * cur_row));     //鼠标抬起
			}
		}
		free(dwPos);
		CloseHandle(hProcess);
	}
	else {
		printf("Open handle failed.");
		return 0;
	}
	return 0;
}