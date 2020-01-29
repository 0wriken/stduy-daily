using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace supermarkey
{
    class Full_re : Payway
    {
        public double Full_mon
        {
            get;
            set;
        }
        //设置满减的构造函数
        public override void  Pay_mon(double user_mon)
        {
            if (user_mon >= 1000)
                Full_mon = 200;
            else if (user_mon >= 500)
                Full_mon = 50;
            else if (user_mon >= 300)
                Full_mon = 50;
            else if (user_mon >= 100)
                Full_mon = 20;
            this.Pay_money = user_mon - Full_mon;
        }
    }
}
