#include <iostream>

using namespace std;
 
class A
{
public:
	virtual void show()
	{
		cout<<"in A::show()\n";
	}
    virtual void virtual_fun1(void)=0;
};
 
class B:public A
{
public:
    B(void )
    {
        cout<<"struction b" <<endl;
    }

    ~B(void )
    {
        cout<<"destruction b" <<endl;
    }
public:
	void show()
	{
		cout<<"in B::show()\n";
	}

    void virtual_fun1(void);
};



void B::virtual_fun1(void)
   {
       cout<<"virtual_fun1" <<endl;
   }

//void func(A a)
//{
//	a.show();	//a是A的一个实例，并不是指向类A对象的指针或引用，所以为实调用。
//}
 
int main()
{
	B* b_ptr;
    b_ptr=&B;
    //B b;
    //b.show();
	//func(b);	//调用类A的拷贝构造函数，产生一个A类对象作为a进入函数func()的函数体
			//在函数体内，a是一个纯粹的类A 对象，与类型B 毫无关系

    //delete b_ptr;
	return 0;
}

