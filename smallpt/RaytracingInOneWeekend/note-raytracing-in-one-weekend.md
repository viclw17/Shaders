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
http://www.cnblogs.com/lichkingct/archive/2009/04/21/1440848.html
http://duramecho.com/ComputerInformation/WhyHowCppConst.html
### Simple Use of ‘const’
```c
// const修饰的类型为char的变量 *pContent 为常量，因此，pContent的 内容 为常量不可变
const char *pContent;
char const *pContent;
// const修饰的类型为char*的变量 pContent 为常量，因此，pContent的 指针本身 为常量不可变
char* const pContent;
const char* pContent;
// 指针本身和指针内容两者皆为常量不可变
const char* const pContent;
```
It also works with pointers but one has to be careful where ‘const’ is put as that determines whether the pointer or what it points to is constant. For example,

- _const_ int * Constant2
    - declares that Constant2 is a variable pointer to a constant integer and
- int _const_ * Constant2
    - is an alternative syntax which does the same, whereas
- int * _const_ Constant3
    - declares that Constant3 is constant pointer to a variable integer and
- int _const_ * _const_ Constant4
    - declares that Constant4 is constant pointer to a constant integer.


Basically ‘const’ applies to whatever is on its **immediate left** (other than if there is nothing there in which case it applies to whatever is its **immediate right**).

Of the possible combinations of pointers and ‘const’, the **constant pointer to a variable** is useful for storage that can be changed in value but not moved in memory.

Even more useful is **a pointer (constant or otherwise) to a ‘const’ value**. This is useful for returning constant strings and arrays from functions which, because they are implemented as pointers, the program could otherwise try to alter and crash. Instead of a difficult to track down crash, the attempt to alter unalterable values will be detected during compilation.

### Use of ‘const’ in Functions Return Values
- ```const int fun1()``` 这个其实无意义，因为参数返回本身就是赋值。
- ```const int * fun2()``` 调用时 ```const int *pValue = fun2();```
    - 我们可以把fun2()看作成一个变量，那么就是我们上面所说的 **指针内容** 不可变。
- ```int* const fun3()``` 调用时 ```int * const pValue = fun2();```
    - 我们可以把fun2()看作成一个变量，那么就是我们上面所说的 **指针本身** 不可变。


Even more useful is a pointer (constant or otherwise) to a ‘const’ value. This is useful for returning constant strings and arrays from functions which, because they are implemented as pointers, the program could otherwise try to alter and crash. Instead of a difficult to track down crash, the attempt to alter unalterable values will be detected during compilation.

### Where it Gets Messy - in Parameter Passing
```c
void function(const int Var);  //传递过来的参数在函数内不可以改变，无意义，因为Var是形参
void function(const char * Var);//传递过来的参数指针所指内容 为常量不可变
void function(char * const Var);//传递过来的参数指针本身 为常量不可变,无意义，因为char* Var也是形参

// 参数为引用，增加效率，防止修改
void function(const TYPE& Var);
```

When a **subroutine or function** is called with parameters, variables passed as the parameters might be read from in order to transfer data into the subroutine/function, written to in order to transfer data back to the calling program or both to do both.

Some languages enable one to specify this directly, such as having ```in:, out: inout:``` parameter types, whereas in C one has to work at a lower level and specify the method for passing the variables choosing one that also allows the desired data transfer direction.

For example, a subroutine like

```
void Subroutine1(int Parameter1)
{ printf("%d",Parameter1);}
```

accepts the parameter passed to it in the default C & C++ way - which is a **copy**. Therefore the subroutine can read the value of the variable passed to it but not alter it because any alterations it makes are only made to the copy and are lost when the subroutine ends. E.g.

```
void Subroutine2(int Parameter1)
{ Parameter1=96;}
```

would leave the variable it was called with unchanged not set to 96.

The addition of an ‘&’ to the parameter name in C++ causes the actual variable itself, rather than a copy, to be used as the parameter in the subroutine and therefore can be written to thereby passing data back out the subroutine. Therefore

```
void Subroutine3(int &Parameter1)
{ Parameter1=96;}
```

would set the variable it was called with to 96. This method of passing a variable as itself rather than a copy is called a **reference** in C++.

That way of passing variables was a C++ addition to C. To pass an alterable variable in original C, a rather involved method was used. This involved using a **pointer** to the variable as the parameter then altering what it pointed to was used. For example

```
void Subroutine4(int *Parameter1)
{ *Parameter1=96;}
```

works but requires the every use of the variable in the called routine altered like that and the calling routine also altered to pass a pointer to the variable. It is rather **cumbersome**.

But where does ‘const’ come into this? Well, there is a second common use for passing data by reference or pointer instead of as a copy. That is **when copying the variable would waste too much memory or take too long**. This is particularly likely with large & compound user-defined variable types (‘structures’ in C & ‘classes’ in C++). So a subroutine declared

```
void Subroutine4(big_structure_type &Parameter1);
```

might being using ‘&’ because it is going to alter the variable passed to it or it might just be to save copying time and there is no way to tell which it is if the function is compiled in someone else’s library.** This could be a risk if one needs to trust the subroutine not to alter the variable.**

To solve this, ‘const’ can be used in the parameter list. E.g.

```
void Subroutine4(big_structure_type const &Parameter1);
```

which will cause the variable to be passed without copying but stop it from then being altered. This is messy because it is essentially making an in-only variable passing method from a both-ways variable passing method which was itself made from an in-only variable passing method just to trick the compiler into doing some optimization.

Ideally, the programmer should not need control this detail of specifying exactly how it variables are passed, just say which direction the information goes and leave the compiler to optimize it automatically, but C was designed for raw low-level programming on far less powerful computers than are standard these days so the programmer has to do it explicitly.

### Messier Still - in the Object Oriented Programming
const修饰 **类的对象** 表示该对象为 **常量对象**，其中的任何成员都不能被修改。对于对象指针和对象引用也是一样。该对象的任何 **非const成员函数** 都不能被调用，因为任何非const成员函数会有修改成员变量的企图。
```
class AAA{
    void func1();
    void func2() const;
}

const AAA aObj;
aObj.func1(); // wrong!!!
aObj.func2(); // 正确

const AAA* aObj = new AAA();
aObj->func1(); // wrong
aObj->func2(); // 正确
```
const修饰 **类的成员变量**，表示成员常量，不能被修改，同时它只能在初始化列表中赋值。
```
class A{
    const int nValue;       //成员常量不能被修改
    A(int x): nValue(x) {}; //只能在初始化列表中赋值
}
```
const修饰 **类的成员函数**，则该成员函数不能修改类中任何 **非const成员变量**。
一般写在函数的最后来修饰
```
class A{
    void function()const; //常成员函数, 它不改变对象的成员变量. 也不能调用类中任何非const成员函数。
}
```

In Object Oriented Programming, calling a ‘method’ (the Object Oriented name for a function) of an object gives an extra complication. As well as the variables in the parameter list, the method has access to the member variables of the object itself which are always passed directly not as copies. For example a trivial class, ‘Class1’, defined as

```
class Class1{
    void Method1();
    int MemberVariable1;
}
```
has no explicit parameters at all to ‘Method1’ but calling it in an object in this class might alter ‘MemberVariable1’ of that object if ‘Method1’ happened to be, for example,
```
void Class1::Method1(){
    MemberVariable1=MemberVariable1+1;
}
```

The solution to that is to put ‘const’ after the parameter list like
```
class Class2{
    void Method1() const;
    int MemberVariable1;
}
```
which will ban Method1 in Class2 from doing anything which can attempt to alter any member variables in the object.

Of course one sometimes needs to combine some of these different uses of ‘const’ which can get confusing as in
```
const int*const Method3(const int*const&)const;
```
where the 5 uses ‘const’ respectively mean that the variable pointed to by the returned pointer & the returned pointer itself won’t be alterable and that the method does not alter the variable pointed to by the given pointer, the given pointer itself & the object of which it is a method!.

### const常量与define宏定义的区别
1. 编译器处理方式不同
    - define宏是在预处理阶段展开。
    - const常量是编译运行阶段使用。
2. 类型和安全检查不同
    - define宏没有类型，不做任何类型检查，仅仅是展开。
    - const常量有具体的类型，在编译阶段会执行类型检查。
3. 存储方式不同
    - define宏仅仅是展开，有多少地方使用，就展开多少次，不会分配内存。
    - const常量会在内存中分配(可以是堆中也可以是栈中)。




## 问题六：C++中&是干嘛用的（引用类型）
## 问题七：operator+=()是什么鬼函数？（重载操作符）
## 问题八：C++中this是干嘛用的
## 问题九：C++中::是干嘛用的（域解析操作符）
## 问题十：【总结】解决了问题四~问题九，vec3这个类的代码应该都能看懂了
