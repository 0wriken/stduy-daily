using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace supermarkey
{
    class Program
    {
        static void Main(string[] args)
        {
            char ch='1';
            Warehouse w=new Warehouse();
            //导入数据
            w.import("NoteBook",100);
            w.import("Apple",100);
            w.import("Banana",100);
            w.import("Iphone",100);
            Console.WriteLine(w.number[0].ToString() ,w.number[1],w.number[2],w.number[3]);
    error1:           
            Console.WriteLine("您好欢迎光临，请选择那您要的商品？");
            string pro=Console.ReadLine();
            Console.WriteLine("选择商品的个数");
            int i=(int)Convert.ToUInt32(Console.ReadLine());
            if(w.export(pro,i)==1)
            {
                Console.WriteLine("是否重新选购?");
                Console.WriteLine("是 Y           否N");
                
                ch=(char)Console.Read();
                Console.ReadLine();
                if(ch=='Y')
                    goto error1;
                else if(ch=='N')
                    goto error3;
            }
            Cashier c=new Cashier();
    error2:  
            Console.WriteLine("已为您取出货物请选择您的支付方式");
            int k=(int)Convert.ToUInt32(Console.ReadLine());
            if(c.Cashier_way(k)==1)
            {
                Console.WriteLine("是否选择重新支付");
                Console.WriteLine("是 Y           否N");
                ch=(char)Console.Read();
                Console.ReadLine();
                if(ch=='Y')
                    goto error2;
                else if(ch=='N')
                    goto error3;
            }
            c.Cashier_pro(w.p,i);
            Console.WriteLine("实际支付费用：");
            Console.WriteLine(c.p.Pay_money);
            Console.WriteLine("是否继续采购？？");
            Console.WriteLine("是 Y           否N");
            ch=(char)Console.Read();
            Console.ReadLine();
                if(ch=='Y')
                    goto error1;
                else if(ch=='N')
                    goto error3;
            Console.Read();   
error3:
            Console.WriteLine("谢谢光顾");
            Console.Read();
        }

    }
}
