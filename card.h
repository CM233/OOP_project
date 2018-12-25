/*card类，是本程序中最关键的类，对于三种卡的处理我没有选择三个继承，而是使用了枚举类型，逻辑上更简便
其中用到了静态变量来记录卡的数量，目的是将只属于类不属于对象的变量进行管理。*/
#ifndef CARD_H_
#define CARD_H_
#include <string>
enum CARDTYPE {teacher,student,limit};
class Card{ 
    private:
        CARDTYPE Card_type;//卡类型    
        std::string Name;//姓名
        std::string Number;//编号
        int Balance;//余额
        int Used_times;//使用次数
        int Valid_time;//有效期
        static int TcardAmount;//教师卡数量
        static int ScardAmount;//学生卡数量
        static int LcardAmount;//限制卡数量
    public:
        Card();//default
        Card(CARDTYPE type,const std::string & name, 
                const std::string &number, int balance, 
                int usedtimes, int validtime);
        virtual ~Card();
        virtual void Swipcard();//order1
        void warning1();//过低
        void warning2();//不足
        void swip();//扣钱
        virtual void show();//显示信息
        void breakdown();//销毁
        virtual void recreate();//申请新卡
        // int usedtimes_out();//导出使用次数
        virtual void timepass();//日期更替
        virtual void refresh();
};

#endif