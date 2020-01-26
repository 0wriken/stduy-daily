using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace wriken_study1
{
    class judger
    {
        public string mes_end
        {
            get;
            set;   
        }
        public void get_end(int user,int com)
        {
            Console.WriteLine(user);
            Console.WriteLine(com);
            int end=user-com;
            if(end==-1||end==2)
            {
                mes_end="玩家赢";
                return ;
            }   
            else if(end==1||end==-2)
            {
                mes_end="电脑赢";
                return ;
            }
            else if(end==0)
            {
                mes_end="平局";
                return ;
            }
        }
    }
}
