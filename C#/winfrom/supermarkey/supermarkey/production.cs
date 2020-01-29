using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace supermarkey
{
    abstract class production
    {
        public int id
        {
            get;
            set;
        }
        public string name
        {
            get;
            set;
        }
        public double price
        {
            get;
            set;
           
        }
        public production(int i, string n, double p)
        {
            this.id = i;
            this.name = n;
            this.price = p;
        }

    }
}
