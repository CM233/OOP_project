/*temporary类，即临时卡，使用了公有继承，以及各种虚方法，由于主函数中是用数组存放对象，则需要用虚方法来识别不同对象的类型。
大部分方法原理同card中的方法，仅对于临时卡特性进行了增添处理。*/
#ifndef _TEMPORARY_H_
#define _TEMPORARY_H_
#include "card.h"
#include <string>
class Temp_card : public Card{
    private:
        int Limit_aging;//时效（天数）
        int Spent_aging;//已过时间
        bool Ifcanuse;//是否能用（冻结）
    public:
        Temp_card();
        Temp_card(CARDTYPE type,const std::string & name, 
                const std::string &number, int balance, 
                int usedtimes, int validtime);
        virtual ~Temp_card();
        virtual void breakdown();//销毁
        virtual void show();//显示信息
        virtual void refresh();//重新激活
        virtual void Swipcard();//刷卡
        virtual void timepass();//有效期更新
    protected:    
        void freeze();//冻结判定
};
#endif