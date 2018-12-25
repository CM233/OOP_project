/*乘客类的具体实现*/
#include <string>
#include <iostream>
#include "card.h"
#include "person.h"
Person::Person()//default
{
}

Person::Person(string name, sex gender, string job, string workplace, string number, Card c)
{
    Name = name;
    Gender = gender;
    Job = job;
    Workplace = workplace;
    Number = number;
    Take_on_times = 0;
}

Person::~Person()
{
}

void Person::takeon()
{
    Take_on_times++;
}


void Person::show()
{
    cout<<"姓名："<<Name<<endl; 
    if(Gender==male)
        cout<<"性别：男"<<endl;
    else
        cout<<"性别：女"<<endl;
    cout<<"职务："<<Job<<endl;
    cout<<"工作地点："<<Workplace<<endl;
    cout<<"工资号学号："<<Number<<endl;
    cout<<"乘车次数："<<Take_on_times<<endl;
}