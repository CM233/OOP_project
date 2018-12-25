/*car类的具体实现，包括时刻表打印，人满检测，准时率相关的处理*/
#include <iostream>
#include "car.h"
#include <string>
using namespace std;
Car::Car(){
    Carnumber = "A00000";
    Cartype = "schoolbus";
    Amount = 30;
    Drivername = "NULL";
    departtime.hour = 0;
    departtime.minute = 00;
    reach.hour = 12;
    reach.minute = 00;
    exact_reach.hour = 12;
    exact_reach.minute = 00;
    leave.hour = 12;
    leave.minute = 30;
    exact_leave.hour = 12;
    exact_leave.minute = 30;
    arrivetime.hour = 23;
    arrivetime.minute = 59;
    amt=0;
}

Car::Car(string & CN, string & CT, int A, string & DN, Time DT, Time AT, Time rt, Time ert, Time lt, Time elt, Time EDT, Time EAT)
{
    Carnumber = CN;
    Cartype = CT;
    Amount = A;
    Drivername = DN;
    departtime = DT;
    arrivetime = AT;
    reach = rt;
    exact_reach = ert;
    leave = lt;
    exact_leave = elt;
    exact_departtime = EDT;
    exact_arrivetime = EAT;
    amt=0;
    settime();
}

Car::~Car(){}

void Car::schedule()//时刻表打印
{
    cout<<"\\\\\\\\\\\\\\\\\\"<<Carnumber<<"时刻表\\\\\\\\\\\\\\\\\\"<<endl;
    cout<<"应发车时间："<<departtime.hour<<":"<<departtime.minute<<endl;
    cout<<"应到达乘车点时间："<<reach.hour<<":"<<reach.minute<<endl;
    cout<<"应离开乘车点时间："<<leave.hour<<":"<<leave.minute<<endl;
    cout<<"应到达终点时间："<<arrivetime.hour<<":"<<arrivetime.minute<<endl;
    cout<<"预计全程时间："<<totaltime.hour<<":"<<totaltime.minute<<"\n"<<endl;
    
    cout<<"实际到达乘车点时间："<<exact_reach.hour<<":"<<exact_reach.minute<<endl;
    cout<<"实际离开乘车点时间："<<exact_leave.hour<<":"<<exact_leave.minute<<endl;
    cout<<"实际发车时间："<<exact_departtime.hour<<":"<<exact_departtime.minute<<endl;    cout<<"实际到达终点时间："<<exact_arrivetime.hour<<":"<<exact_arrivetime.minute<<endl;
}

int Car::amountlimit()//最大人数检测
{
    
    if(amt>=Amount)
    {
        cout<<"人满"<<endl;
        return 1;
    }
    else 
        amt++;
    return 0;
}                              

double Car::exact_rate()//准时率计算
{
   return (double)amt/Amount;
}

double Car::on_time_test()//发车准时检测
{
    if(departtime.hour==exact_departtime.hour&&departtime.minute==exact_departtime.minute)
        return 1.0;
    else 
        return 0.0;
}