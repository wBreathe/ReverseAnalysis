### 补充

based on https://zhuanlan.zhihu.com/p/382699090

#### 关于长宽的确定

ESI 是指针，在二维矩阵内游动，应该会有边界check，或许可以通过边界check来猜测长宽高

![image-20231008161526241](C:\Users\Emma\AppData\Roaming\Typora\typora-user-images\image-20231008161526241.png)

follow in dump(memory address)发现1005334和1005338的值都是9 猜测他们对应长宽高，自定义长宽高以验证

![image-20231008161712699](C:\Users\Emma\AppData\Roaming\Typora\typora-user-images\image-20231008161712699.png)

改成高24 宽17

![image-20231008162209728](C:\Users\Emma\AppData\Roaming\Typora\typora-user-images\image-20231008162209728.png)

![image-20231008162242908](C:\Users\Emma\AppData\Roaming\Typora\typora-user-images\image-20231008162242908.png)

![image-20231008162348134](C:\Users\Emma\AppData\Roaming\Typora\typora-user-images\image-20231008162348134.png)

#### vstudio不能运行画图程序

报错找不到符号 32和64不匹配啥的（排除了依赖的问题https://blog.csdn.net/Scoful/article/details/121516956），需要把x64换成x32，这是个32的库？

![image-20231008173045487](C:\Users\Emma\AppData\Roaming\Typora\typora-user-images\image-20231008173045487.png)![image-20231008173126885](C:\Users\Emma\AppData\Roaming\Typora\typora-user-images\image-20231008173126885.png)

![image-20231008173214900](C:\Users\Emma\AppData\Roaming\Typora\typora-user-images\image-20231008173214900.png)

#### 使用多字节字符集

主要是为了兼容C（winAPI）

两者常规区别：

- char  wchar_t  TCHAR

  TCHAR是前两者的宏定义（用词不一定准确，大致意思就是用TCHAR就不用再做区分了）

- 其他常规字符代码如下：
  - WCHAR Unicode字符
  - PWSTR 指向Unicode字符串的指针
  - PCWSTR 指向一个恒定的Unicode字符串的指针
  - 对应的ANSI数据类型为CHAR，LPSTR和LPCSTR
  - ANSI/Unicode通用数据类型为TCHAR，PTSTR，LPCTSTR

https://blog.csdn.net/weixin_47187658/article/details/126083640

#### spy++ 

[path_to_visual_studio]\Microsoft Visual Studio\2022\Community\Common7\Tools 下面spyxx_amd64.exe 64位，spyxx.exe 32位

#### 扫雷外挂

- 基本思路

  遍历map，点开所有非雷

  <font color=red>需要注意的是鼠标包含两个操作，点击下和松开</font>

- 需要的信息

  map的起始点：0x01005361

  map的大小：0x1005334 column 0x1005338 row

  鼠标在map上的位置映射
  
- 如何找到鼠标与map的映射？

  参考https://blog.csdn.net/wangxun20081008/article/details/113915805

  ```c++
  #include <stdio.h>
  #include <windows.h>
  #define KEY_DOWN(state) (state&0x8000 ? true:false) //获取鼠标点击并弹起事件
  #include <iostream>
  
  using namespace std;
  
  int main() {
  	//找到扫雷窗口的句柄
  	HWND hWnd = FindWindow(NULL, "扫雷");
  	short b_state_pre, b_state_post;
  	while (1) {
  		b_state_pre = GetAsyncKeyState(VK_LBUTTON);
  		Sleep(100);
  		b_state_post = GetAsyncKeyState(VK_LBUTTON);
  		if (KEY_DOWN(b_state_pre) && !KEY_DOWN(b_state_post)){
  			POINT p;
  			GetCursorPos(&p); //在屏幕的位置坐标
  			printf("key down of the whole screen: %d, %d\n", p.x, p.y);
  			ScreenToClient(hWnd, &p); //在窗口的位置坐标
  			printf("key down of the window: %d, %d\n", p.x, p.y);
  		}
  		Sleep(100);
  	}
  	return 0;
  }
  ```

- 基于以上信息实现扫雷辅助程序

  ![image-20231010111626174](C:\Users\Emma\AppData\Roaming\Typora\typora-user-images\image-20231010111626174.png)

  边界10之间有0f填充