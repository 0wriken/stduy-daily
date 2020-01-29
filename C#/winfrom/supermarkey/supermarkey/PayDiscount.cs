using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace supermarkey
{
    class PayDiscount:Payway
    {
        public double dis_count
        {
            get;
            set;
        }
        //设置折扣
        public PayDiscount(double d1)
        {
            dis_count = d1;
        }
        public override void  Pay_mon(double user_mon)
        {
            this.Pay_money = user_mon * dis_count;
        }
        
    }
}
