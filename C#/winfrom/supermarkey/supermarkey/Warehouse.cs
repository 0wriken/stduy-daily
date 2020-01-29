using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace supermarkey
{
    class Warehouse
    {
        //仓库对象
		public int []number
		{
			get;set;
		}
		public production p;
		List<List<production>> list =new List<List<production>>();

		public Warehouse()
		{	
			this.number=new int[4]{0,0,0,0};
			list.Add(new List<production>());
			list.Add(new List<production>());
			list.Add(new List<production>());
			list.Add(new List<production>());
		}
		public void import(string pro, int num)
		{
			int i = 0;
			switch (pro)
			{
				case "NoteBook":
					{
						for (i=0; i < num; number[0]++)
						{
							p = new NoteBook( 1, "惠普笔记本", 10000.0);
							list[0].Add(p);
							i++;
						}
						break;
					}
				case "Apple":
					{
						for (i=0; i < num; number[1]++)
						{
							p = new Apple(2, "蓝牙耳机", 1200.0);
							list[1].Add(p);
							i++;
						}
						break;
					}
				case "Banana":
					{
						for (i=0; i < num; number[2]++)
						{
							p = new Banana(3, "香蕉", 100.0);
							list[2].Add(p);
							i++;
						}
						break;
					}
				case "Iphone":
					{
						for (i=0; i < num; number[3]++)
						{
							p = new Iphone(4, "苹果手机", 8000.0);
							list[3].Add(p);
							i++;
						}
						break;
					}
			}
		}
			//导出货物	
			public int export(string pro,int num)
			{
				int i=0;
				switch(pro)
				{
					//逐位取出数据
					case "NoteBook":
					{
						if(number[0]<num)
						{
							Console.WriteLine(pro+"货物已不够","error");
							return 1;
						}
						p = new NoteBook( 1, "惠普笔记本", 10000.0);
						for(i=0;i<num;number[0]--)
						{
							//取出数据
							list[0].RemoveAt(number[0]-1);
							i++;
						}
						break;
					}
					case "Apple":
					{
						if(number[1]<num)
						{
							Console.WriteLine(pro+"货物已不够","error");
							return 1;
						}
						p = new Apple(2, "蓝牙耳机", 1200.0);
						for(i=0;i<num;number[1]--)
						{
							
							list[1].RemoveAt(number[1]-1);
							i++;
						}
						break;
					}
					case "Banana":
					{
						if(number[2]<num)
						{
							Console.WriteLine(pro+"货物已不够","error");
							return 1;
						}
						p = new Banana(3, "香蕉", 100.0);
						for(i=0;i<num;number[2]--)
						{
							
							list[2].RemoveAt(number[2]-1);
							i++;
						}
						break;
					}
					case "Iphone":
					{
						if(number[3]<num)
						{
							Console.WriteLine(pro+"货物已不够","error");
							return 1;
						}
						p = new Iphone(4, "苹果手机", 8000.0);
						for(i=0;i<num;number[3]--)
						{
							list[3].RemoveAt(number[3]-1);
							i++;
						}
						break;
					}
					default:
					{
						Console.WriteLine("没有找到您要的商品,请重新选择");
						return 1;
					}
				}
				return 0;
			}
    }
}
