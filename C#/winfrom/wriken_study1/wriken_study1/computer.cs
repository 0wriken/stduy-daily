using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace wriken_study1
{
    class computer
    {
        public string message
        {
            get;
            set;
        }

        public int com_get()
        {
            int r=0;
            Random i=new Random();
            r=i.Next(1,4);
            switch(r)
            {
                case 1:
                    {
                        this.message="石头";
                        return 1;
                    }
                case 2:
                    {
                        this.message="剪刀";
                        return 2;
                    }
                case 3:
                    {
                        this.message="布";
                        return 3;
                    }
                default:
                    {
                        Console.WriteLine("error"); 
                        break;
                    }
            }
            return 0;
        }
    }
}
