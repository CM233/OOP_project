/*17130188007 陈铭 一卡通乘车系统
（各文件介绍详见个各文件开头）
主函数内容包括了一个简单的命令行ui，和一套处理不同order输入的程序，以及乘客和车的初始化
由于编写习惯，没有在类的构造函数中获取输入，而是在主函数中获取输入再通过构造函数赋值给相应的类
为了避免内存管理不当，本项目没有使用new和delete对对象进行动态管理，卡和车都是存放在定长数组中都有创建数量的最大值。
本项目提示性的语句较多，运行时不会存在用户不友好的情况。（即不知道该句输入或输出是什么意义）
本项目的亮点在于代码书写风格严谨，用户友好和对不同类型卡、不同指令的精确处理，缺点在于对于班车和乘客的管理，对于时间的管理不够灵活。*/
#include <iostream>
#include <string>
#include "card.h"
#include "car.h"
#include "person.h"
#include "temporary.h"
using namespace std;

void ui();
void carinit(Car bus[5],int n);

int main()
{
    cout<<"\\\\\\\\\\\\\\\\\\\\欢迎来到一卡通乘车系统\\\\\\\\\\\\\\\\\\\\\\\\"<<endl;
    cout<<"(如果没有定义班车运行，请先输入班车信息)"<<endl;
    int m;//自定义操作一卡通系统的人数
    int n;//自定义班车数
    cout<<"输入两个数m n，m表示操作本系统人数（50>m>1），n表示班车数(10>n>1):";
    cin>>m>>n;
    Car bus[10];
    carinit(bus,n);
    Card c[50];
    Temp_card te[50];
    bool iftemp[50];
    Person p[50];
    ui();
    int order;
    int i;//临时变量+用于标记第i个人
    int j;//用于标记第j辆班车
    int count[50];
    for (i=0;i<m;i++)
        count[i] = 0;//持卡数初始化
    cin>>order;
    i=0;
    while(order!=0)//第i位乘客和第j辆车针对不同指令的操作
    {
        
        if(order==2&&count[i]<1)//办卡
        {
            int a;
            cout<<"是否办理临时卡：1、是。2、否。";
            cin>>a;
            cout<<"你要办卡的类型：1、教师卡。2、学生卡。3、限制卡。";
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
            
            cout<<"输入你的性别：（0为男，1为女）"<<endl;
            int q;
            sex s;
            cin>>q;
            if(q==0)
                s=male;
            if(q==1)      
                s=female;

            cout<<"输入你的号码："<<endl;
            string nu;
            cin>>nu;
            
            cout<<"输入你的职务："<<endl;
            string jo;
            cin>>jo;

            string wp="西安电子科技大学";
           
            cout<<"输入充值金额；(教师免费乘车，输入0即可)"<<endl;
            int ba;
            cin>>ba;

            int ut=0;
            
            if(a==2)
            {
                c[i]=Card(t,na,nu,ba,ut,1460);//强制转换为Card基类类型构建对象
                p[i]=Person(na,s,jo,wp,nu,c[i]);//处理个人信息
                iftemp[i]=0;
            }    
            if(a==1)
            {
                te[i]=Temp_card(t,na,nu,ba,ut,1460);//使用临时卡构造函数
                p[i]=Person(na,s,jo,wp,nu,te[i]);//处理个人信息
                iftemp[i]=1;
            }
                
            
            cout<<"成功办理"<<endl;
            count[i]++;
            if(i<m-1)
                i++;
        }
        else if(order==2&&count[i]>=1)//多次办卡报错
        {
            cout<<"你已经办过卡了"<<endl;
        }
        
        if(order==1&&count[i]==1)//持1张卡刷卡,正确操作
        {    
            
            static int u[50][10]={0};//防重复刷卡
            cout<<"您要乘哪辆班车？(0~"<<n-1<<"号)"<<endl;
            cin>>j;
            if(u[i][j]==0)
            {
                if(iftemp[i]==0)
                    c[i].Swipcard();
                else
                    te[i].Swipcard();
                p[i].takeon();
                bus[j].amountlimit();
                u[i][j]++;
            }
            else if(u[i][j]>1)
            {
                cout<<"您已经刷过卡了"<<endl;
            }
        }
        else if(order==1&&count[i]==0)//无卡刷卡报错
        {
            cout<<"请先办卡"<<endl;
        }

        if(order==3)//显示信息
        {
            if(iftemp[i]==0)
                c[i].show();
            else
                te[i].show();
        }

        if(order==4)//班车信息汇总
        {
            int i;
            static double ontime=0;
            cout<<"各班车时刻表汇总:"<<endl;
            for(i=0;i<n;i++)
            {
                bus[i].schedule();
                cout<<endl;
                ontime += bus[i].on_time_test();
                cout<<"该车实际乘车人数与载乘人数比：";
                printf("%.2lf",bus[i].exact_rate()*100);
                cout<<'%'<<endl;
            }
            cout<<endl<<"发车准时率：";
            printf("%.2lf",ontime/n*100);
            cout<<'%'<<endl; 
        }

        if(order==5)//注销卡
        {
            if(iftemp[i]==0)
                c[i].breakdown();
            else
                te[i].breakdown();
            p[i].~Person();
            if(i<n-1)
            {   
                int l;
                cout<<"i号后的用户将会向前覆盖"<<endl; 
                for(l=i;l<m;l++)    
                {
                    c[l]=c[l-1];//向前覆盖
                    p[l]=p[l-1];
                }
            }
        }

        if(order==6)//申请新卡
        {
            if(count[i]==1)
            {
                if(iftemp[i]==0)
                    c[i].recreate();
                else
                    te[i].recreate();
            }    
            if(count[i]==0)
                cout<<"没有办卡，不能申请新卡"<<endl;
        }
        if(order==7)
        {
            if(iftemp[i]==1)
                te[i].refresh();
            else
                cout<<"不是临时卡，不需要重新激活"<<endl;
        }
        if(order==8)//跳转操作者
        {
            cout<<"输入需要进行操作的人的编号(第一个人为0号)：0～"<<m-1<<endl;
            cin>>i;
        }
        if(order==9&&i<m)//下一位操作者
        {
            i++;
            if(i==m-1)
                cout<<"已经是最后一位"<<endl;        
        }
        else if(order==9&&i>=m-1)
            cout<<"没有下一位了，是否选择跳转到8号指令或者选择退出系统？"<<endl;
            
        cout<<"下一步指令："<<endl;
        cin>>order;
    }
    return 0;
}


void ui()
{
    cout<<"请选择功能:"<<endl;
    cout<<"1、乘车"<<endl;
    cout<<"2、办卡"<<endl;
    cout<<"3、显示信息"<<endl;
    cout<<"4、车辆运行管理"<<endl;
    cout<<"5、注销一卡通"<<endl;
    cout<<"6、申请新卡"<<endl;
    cout<<"7、临时卡重新激活"<<endl;
    cout<<"8、跳转到其他乘客操作"<<endl;
    cout<<"9、下一位乘客操作"<<endl;

    cout<<"按0退出"<<endl;
}

void carinit(Car bus[10],int n)//调用了班车构造函数，批量构造对象
{
    int i;
    cout<<"共有"<<n<<"辆班车,请编制时刻表："<<endl;
    for(i=0;i<n;i++){
        cout<<"第"<<i+1<<"辆的车牌号："<<endl;
        string carnumber;
        cin>>carnumber;
        cout<<"第"<<i+1<<"辆的车型："<<endl;
        string cartype;
        cin>>cartype;
        cout<<"第"<<i+1<<"辆的承载人数："<<endl;
        int amount;
        cin>>amount;
        cout<<"第"<<i+1<<"辆的驾驶员姓名："<<endl;
        string drivername;
        cin>>drivername;
        cout<<"第"<<i+1<<"辆的出发时间："<<endl;
        Time dt;
        cin>>dt.hour;
        cin>>dt.minute;
        cout<<"第"<<i+1<<"辆的到达时间："<<endl;
        Time at;
        cin>>at.hour;
        cin>>at.minute;
        
        cout<<"第"<<i+1<<"辆应到乘车点的时间："<<endl;
        Time reach;
        cin>>reach.hour;
        cin>>reach.minute;
        cout<<"第"<<i+1<<"辆应离开乘车点的时间："<<endl;
        Time leave;
        cin>>leave.hour;
        cin>>leave.minute;
        
        cout<<"第"<<i+1<<"辆实际到乘车点的时间："<<endl;
        Time reach_;
        cin>>reach_.hour;
        cin>>reach_.minute;
        cout<<"第"<<i+1<<"辆实际离开乘车点的时间："<<endl;
        Time leave_;
        cin>>leave_.hour;
        cin>>leave_.minute;
        
        cout<<"第"<<i+1<<"辆的实际出发时间："<<endl;
        Time edt;
        cin>>edt.hour;
        cin>>edt.minute;
        cout<<"第"<<i+1<<"辆的实际到达时间："<<endl;
        Time eat;
        cin>>eat.hour;
        cin>>eat.minute;

        bus[i]=Car(carnumber,cartype,amount,drivername,dt,at,reach,leave,reach_,leave_,edt,eat);
    }
}
