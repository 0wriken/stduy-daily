using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace supermarkey
{
    class Cashier
    {
        public  Payway p;
	//支付方式
	public int Cashier_way(int i)
	{
		switch(i)
		{
			//默认模式
			case 0:
			{
				Console.WriteLine("当前支付无优惠");
				 p=new PayDiscount(1);		
				break;
			}
			case 1:
			{
				Console.WriteLine("已打八折优惠");
				 p=new PayDiscount(0.8);
				break;
			}
			case 2:
			{
				Console.WriteLine("已打六折优惠");
				 p=new PayDiscount(0.6);
				break;
			}
			//满减
			case 3:
			{
				Console.WriteLine("已满减");
				 p=new Full_re();
				break;
			}
			default:
			{
				Console.WriteLine("没有这种支付方式请重新选择");
				return 1;
			}
		}
        return 0;
	}
	public double Cashier_pro(production pro,int num)
	{
		Console.WriteLine("选择商品为");
		Console.WriteLine(pro.name);
		Console.WriteLine("原价为");
		Console.WriteLine(pro.price*num);
		this.p.Pay_mon(pro.price*num);
		return this.p.Pay_money;
	}
    }
}
