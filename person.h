/*乘客类，原理和card类相似，也是主要以存放信息、显示信息为主。特别的是takeon方法用于人车交互*/
#ifndef PERSON_H_
#define PERSON_H_
#include <string>
#include <iostream>
#include "card.h"
using namespace std;
enum sex{male, female};
class Person{
    private:
        string Name;
        sex Gender;
        string Job;
        string Workplace;
        string Number;
        int Take_on_times;
    public:
        Person();
        Person(string name, sex gender, string job, string workplace, string number, Card c);
        ~Person();
        void takeon();//上车
        void show();
};

#endif