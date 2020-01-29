using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace supermarkey
{
    abstract class Payway
    {
        public double Pay_money
        {
            get;
            set;
        }
        public abstract void Pay_mon(double user_mon);

    }
}
