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
//	a.show();	//a��A��һ��ʵ����������ָ����A�����ָ������ã�����Ϊʵ���á�
//}
 
int main()
{
	B* b_ptr;
    b_ptr=&B;
    //B b;
    //b.show();
	//func(b);	//������A�Ŀ������캯��������һ��A�������Ϊa���뺯��func()�ĺ�����
			//�ں������ڣ�a��һ���������A ����������B ���޹�ϵ

    //delete b_ptr;
	return 0;
}

