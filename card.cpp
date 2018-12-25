/*该程序是card类的成员函数的具体实现，包括：
构造函数（默认+手动创建）、析构函数、
刷卡（对三种卡分别处理，包括了处理信息，扣钱，以及对余额过低、不足的处理）、
销毁、重新创建（同主函数中的代码块）、导出使用时间、有效期更新（主函数中没有体现，不过只需调用就可以体现了）。*/
#include <iostream>
#include <string>
#include "card.h"
#include "car.h"
#include "temporary.h"
using namespace std;
Card::Card()//default
{
    Card_type = student;
    Name = "no name";
    Number = "00000000000";
    Balance = 100;
    Used_times = 0;
    Valid_time = 1460;
};

Card::Card(CARDTYPE type,const std::string & name, const std::string &number, int balance, int usedtimes, int validtime)
//办卡，order2
{    
    Card_type = type;
    Name = name;
    Number = number;
    Balance = balance;
    Used_times = usedtimes;
    Valid_time = validtime;
    // if(Card_type==student)
    //         ScardAmount++;
    //     else if(Card_type==teacher&&TcardAmount<ScardAmount-1)
    //         TcardAmount++;
    //     else if(Card_type==limit&&LcardAmount<TcardAmount-1)
    //         LcardAmount++;
}

Card::~Card()
{
    // if(Card_type==student)
    //         ScardAmount--;
    //     else if(Card_type==teacher&&TcardAmount<ScardAmount-1)
    //         TcardAmount--;
    //     else if(Card_type==limit&&LcardAmount<TcardAmount-1)
    //         LcardAmount--;
}

void Card::Swipcard()
//刷卡，order1
{
    cout<<"你的用户信息："<<"\n"
        <<Name<<"\n"
        <<Number<<"\n";  
    
    if(Card_type==student)//学生卡刷卡
        Card::swip();
    
    if(Card_type==limit)//限制卡刷卡
    {
        cout<<"限制卡本月已使用次数："<<++Used_times<<endl;
        if (Used_times==20)
            cout<<"这是本月最后一次免费乘车"<<endl; 
        else if (Used_times==21)
            cout<<"开始收费："<<endl;  
        if (Used_times>=21)
            {
                swip();
                Used_times--;
            }
    }
    if(Card_type!=teacher)    
        cout<<"余额："<<Balance<<endl;
    else
        cout<<"欢迎老师乘车"<<endl;//显示信息
}

void Card::warning1()//余额过低
{
    if(Balance<=5)
        cout<<"余额过低，请及时充值"<<endl;
}
void Card::warning2()//余额不足
{
    if(Balance<2)
        cout<<"余额不足，不准乘车"<<endl;
}
void Card::swip()//扣钱
{
    if(Balance>2)
    {
        Balance-=2;
        Card::warning1();
        Used_times++;
    }
    else
        Card::warning2();
}
void Card::show()//显示信息,order3
{
    cout<<"持卡人姓名： "<<Name<<" 一卡通编号："<<Number<<'\n';
    cout<<"余额："<<Balance<<"元"<<endl;
    cout<<"单位：西安电子科技大学"<<endl;
    cout<<"剩余有效期："<<Valid_time<<endl;
    cout<<"使用次数："<<Used_times<<endl;
}
void Card::breakdown()//销毁
{
    Card::~Card();
}
void Card::recreate()//办新卡（包含了临时卡创建）
{
    cout<<"是否办理临时卡：1、是。2、否。";
    int a;
    cin>>a;
    cout<<"你要办卡的类型：1、教师卡。2、学生卡。3、限制卡";
            int v;
            CARDTYPE t;
            cin>>v;
            if(v==1)
                t=teacher;
            if(v==2)
                t=student;
            if(v==3)
                t=limit;
            
            cout<<"输入你的姓名："<<endl;
            string na;
            cin>>na;
            
            cout<<"输入你的号码："<<endl;
            string nu;
            cin>>nu;
            
            cout<<"输入充值金额；(教师免费乘车，输入0即可)"<<endl;
            int ba;
            cin>>ba;

            int ut=0;
            
            if(a==2)
                *this=Card(t,na,nu,ba,ut,1460);
            if(a==1)
                *this=Temp_card(t,na,nu,ba,ut,1460);//使用临时卡构造函数
            cout<<"成功办理"<<endl;
}

// int Card::usedtimes_out()//导出使用时间，前期测试用函数，不能提现封装特性，已弃用
// {
//     return Used_times;
// }

void Card::timepass()//有效期更新
{
    Valid_time--;
}

void Card::refresh()//用于区分子类父类，并未出现子类父类混淆情况，半弃用
{
    cout<<"不是临时卡，不需要重新激活"<<endl;
}
