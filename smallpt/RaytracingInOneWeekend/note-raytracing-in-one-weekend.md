# Chapter 0: Overview
## [问题一：CodeBlocks环境搭建及创建第一个C++程序](https://blog.csdn.net/libing_zeng/article/details/54410627)
Windows
Run command line ```g++ main.cpp``` in Cygwin, and this output a ```a.exe``` file. Run the file with ```./a.exe``` and this generate the final file ```test.ppm```. File can be opened with **File Viewer Plus**.

# Chapter 1: Output an image
## 问题二：用C++输出第一张图片
将结果输出到文件
```c
#include <fstream>
/*iostream是输入输出流库标准文件（注意它没有后缀），它包含cout的信息，这对我们的程序是必需的。#include是预处理器指示符（preprocessor directive），它把iostream的内容读入我们的文本文件中*/
ofstream outfile( ".\\results\\FirstImage.txt", ios_base::out);
/*打开当前目录（工程目录）下results文件夹中的FirstImage.txt文件*/
outfile << "P3\n" << nx << " " << ny << "\n255\n";
/*往文件中写入数据*/
```
顺便说一下标准输出：
```c
#include <iostream>
using namespace std;
/*这条语句被称作using指示符（using directive）。 C++标准库中的名字都是在一个称作std的名字空间中声明的，这些名字在我们的程序文本文件中是不可见的，除非我们显式地使它们可见。using指示符告诉编译器要使用在名字空间std中声明的名字。*/
std::cout << "P3\n" << nx << " " << ny << "\n255\n";
/*往屏幕上输出数据*/
```

# Chapter 2: The vec3 class
## 问题三：类的头文件和实现文件分别写什么（用向量表示RGB输出“第一张图片”）
## 问题四：C++中inline是干嘛用的
## 问题五：C++中const是干嘛用的
## 问题六：C++中&是干嘛用的（引用类型）
## 问题七：operator+=()是什么鬼函数？（重载操作符）
## 问题八：C++中this是干嘛用的
## 问题九：C++中::是干嘛用的（域解析操作符）
## 问题十：【总结】解决了问题四~问题九，vec3这个类的代码应该都能看懂了
