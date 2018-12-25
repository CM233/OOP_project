/*临时卡成员函数的实现，主要是对card.cpp重的成员函数进行重写，大多数都是虚函数*/
#include <iostream>
#include <string>
#include "card.h"
#include "temporary.h"
using namespace std;
Temp_card::Temp_card():Card()//default
{
    Limit_aging=30;
    Spent_aging=0;
    Ifcanuse=1;
}

Temp_card::Temp_card(CARDTYPE type,const std::string & name, 
                const std::string &number, int balance, 
                int usedtimes, int validtime)
                :Card(type, name, number,balance, usedtimes, validtime)
{
    int la;
    cout<<"请输入申请的时效：";
    cin>>la;
    Limit_aging=la;
    Spent_aging=0;
    Ifcanuse=1;
}

Temp_card::~Temp_card()
{
}

void Temp_card::breakdown()//销毁
{
    Temp_card::~Temp_card();
}

void Temp_card::show()//显示信息
{
    cout<<"此卡为临时卡";
    Card::show();
    if(Ifcanuse==1)
        cout<<"时效："<<Limit_aging-Spent_aging;
    else
        cout<<"已超时，被冻结。";
}

void Temp_card::freeze()//冻结判定
{
    if(Limit_aging<Spent_aging)
    Ifcanuse=0;
}

void Temp_card::refresh()//重新激活
{
    freeze();
    Spent_aging = 0;
    cout<<"设置新的时效：";
    int l;
    cin>>l;
    Limit_aging = l;
    Ifcanuse=1;
}

void Temp_card::Swipcard()//刷卡
{
    freeze();
    if(Ifcanuse==1)
        Card::Swipcard();
    else
    {
        cout<<"已冻结，需重新激活.";
    }
}

void Temp_card::timepass()//有效期更新
{
    Card::timepass();
    Spent_aging++;
    freeze();
}
