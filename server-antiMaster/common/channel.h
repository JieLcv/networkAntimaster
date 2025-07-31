#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<functional>
//定义函数指针
//函数指针可以指向普通函数和类中静态函数，这两种函数只要函数被定义出来，就存在了，而类中普通成员函数，只有实例化后才存在
//类中普通成员函数属于对象的，而静态函数不属于对象，属于类
//typedef int(*handleFunc)(void* arg);
//using handleFunc = int(*)(void* arg);

//定义文件描述符的读写事件, 强类型枚举，使用时需要加上枚举类型::, 因此可以在不同的强类型枚举内定义相同的名字, 定义强类型枚举时，class和struct没区别
//使用里面的值时，值的类型是枚举的类型，而不是int不能进行隐式类型转换
enum class FDEvent
{
	TimeOut = 0x01,
	ReadEvent = 0x02,
	WriteEvent = 0x04
};


//可调用对象包装器打包的是什么？1.函数指针(各种函数） 2.可调用对象(可以像函数一样使用，例如仿函数)
// 最终得到了地址，但是没有调用
// 也可以将无参函数包装为有参函数，通过包装器调用时，需指定参数
// 可调用对象包装器本来不能绑定非静态成员函数，通过绑定器绑定后，就可以被可调用对象包装器包装了
//文件描述符通道
class Channel
{
public:
	using handleFunc = std::function<int(void*)>;
	//初始化一个Channel
	Channel(int fd, FDEvent events, handleFunc readFunc, handleFunc writeFunc, handleFunc destroyFunc, void* arg);
	//修改fd的写事件（检测 or 不检测）
	void writeEventEnable(bool flag);
    //对当前检要检测的时间进行检测
    void setCurrentEvent(FDEvent ev);
	//判断是否需要检测文件描述符的写事件
	bool isWriteEventEnable();
    //判断是否需要检测文件描述符的读事件
    bool isReadEventEnable();
	//取出私有成员的值
	//内联函数，好处，调用时不需要进行入栈出栈操作，直接进行代码块替换，执行效率高，坏处需要消耗更多内存
	inline int getEvent()
	{
		return m_events;
	}
	inline int getSocket()
	{
		return m_fd;
	}
	//const 类型不能传入非const 形参，需要进行类型转换
	inline const void* getArg()
	{
		return m_arg;
	}
	//回调函数
	handleFunc readCallback;
	handleFunc writeCallback;
	handleFunc destroyCallback;

private:
	//文件描述符
	int m_fd;
	//事件
	int m_events;
	//回调函数的参数
	void* m_arg;
};

