using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace wriken_study1
{
    class player
    {
        public int user_get(string list)
        {
            switch(list)
            {
                case "石头":
                    return 1;
                case "剪刀":
                    return 2;
                case "布":
                    return 3;
            }
            return 0;
        }

    }
}
