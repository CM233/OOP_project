/*car类，主要是处理班车的信息，自定义了time结构用于管理时间，但班车信息必须手动输入比较麻烦，可改进的一个方法是通过文件读入*/
#ifndef CAR_H_
#define CAR_H_
#include <string>
using namespace std;
typedef struct time{
    int hour;
    int minute;
}Time;
class Car{
    private:
        string Carnumber;//车牌号
        string Cartype;//型号
        int Amount;//载承人数
        string Drivername;//驾驶员姓名
        Time departtime;//出发时间
        Time arrivetime;//离开时间
        Time reach;//应到达乘车点时间
        Time exact_reach;//实际到达乘车点时间
        Time leave;//应离开乘车点时间
        Time exact_leave;//实际到达乘车点时间
        Time exact_departtime;//实际到站时间
        Time exact_arrivetime;//离开时间
        int amt;//已有人数
        Time totaltime;//全程时间
        void settime(){
            if(arrivetime.minute>=departtime.minute){
                totaltime.hour=arrivetime.hour-departtime.hour;
                totaltime.minute=arrivetime.minute-departtime.minute;
            } 
            if(arrivetime.minute<departtime.minute){
                totaltime.hour=arrivetime.hour-departtime.hour-1;
                totaltime.minute=60+arrivetime.minute-departtime.minute;
            }
        };
    public:
        Car();//default
        Car(string & CN, string & CT, int A, string & DN, Time DT, Time AT, Time rt, Time ert, Time lt, Time elt, Time EDT, Time EAT);
        ~Car();
        void schedule();//时刻表打印
        int amountlimit();//最大人数检测
        double exact_rate();//发车准时率计算
        double on_time_test();//发车准时检测
};

#endif