dynamic :弱类型转换提供灵活性
C#强转javaspri弱
没有头文件，方法声明与定义不分开
字段：成员变量
静态只读字段：初始化实例（构造不可变）

2.属性：微软自动封装
using System
class sudent
{
private int age;
public int Age
{
	get
	{
		return this.age;
	}
	set
	{
		if(value>=o&&value<=100)
		{
			this.age=value;
		}
		else
		{
			throw new EXception("the value out");
		}
	}
}
}
sudent.Age=20;
console.WriteLine(sudent.Age);
简略声明：
class student{
pulic int Age{get;set;}
}
 student.Age

只读属性:
class student{
pulic int Age{get;}
}

外界无法访问set
class student{
pulic int Age{
	get{}
private	set
{
	arg=valu-e;
}
}}

2.索引器：index
using System;;
using System.Collections.Generic;
namespace idexTest
{
	static void Main(String[] args)
	{
		student stu=new student();
		stu["chinese"]=100;
		var check=stu["chinese"];
		console.WriteLine(check);//索引科目
	}
class student
{
	private Dictionary<string ,int>sorce=new Dictionary<string ,int>(); //调用库泛型编程为string类型与下标值
	public int? this[string subject]
	{

		get
		{
			if(this.sorce.ContainKey[subject])  
			{
				return this.sorce[subject];
			}
			else
			{
				return null;
			}
		}
		set
		{
			if(value.HasValue==false)
			{
				throw new EXception("the value is error");
			}
			if(this.sorce.ContainKey[subject])
			{
				this.sorce[subject] =value.Value;
			}
			else
			{
				this.sorce.Add(subject,value.Value);//没有找到科目且分数合格则添加到字典中
			}
		}
	}	
}	
}

3.参数
值参数
引用参数： ref
	static void setstudent(ref student stu)
	{
		stu.name="Tom";
	}
	static void Main(String[] args)
	{
		student stu=new student();
		setstudent(stu);
	}
输出参数： out 
		与引用的区别：引用需要调用前初始化，out必须在离开前赋值 
		static void Main(string[] args)
	{
		console.WriteLine("please input the number");
		string arg1= console.ReadLine();
		double x=0;
		double y=0;
		bool b1=double.TryParse(arg1,out x);
		if(b1==false)
		{
			console.WriteLine("")
			return;
		}
		console.WriteLine("please input second number");
		string arg2= console.ReadLine();
		bool b2=double.TryParse(arg2,out y);
		if(b2==false)
		{
			console.WriteLine("  ")
			return;
		}
		console.WriteLine(x+y);
	}
	实现机制：
		static bool TryParse(string input,out double result)
		{
			try
			{
				result = double.parse(input); //类型转换 if转换错误则catch
				return true;
			}
			catch
			{
				result=0;
				return false;
			}
		}
	输出类型：
	static void Main(string[] args)
	{
		student stu=null;
		if(Create(stu))  //参数？？？
		{
			console.WriteLine(stu.name,stu.age);
		}

	}
	class student
	{
		public int age{get;set;};
		public string name{get;set;};
	}
	static bool Create(out student result)
	{
		result=null;
		if(student.name.isEmptyorNull(name))
		{

			return false;
		}
		if(student.age>20||student.age<80)
		{
			return false;
		}
		return = new student("wriken",22);
		return true;
	}
数组参数： params 必须是形参列表的最后一个
	static void Main(string[] args)
	{
		console.WriteLine(addAll({0,1,2}));//数组对象构造重载
		string str="wrien;yukong";
	 	string []result=str.Split(';','.','/');//自动按照符号分割字符串
	 	foreach(var item in result)
	 	{
	 		console.WriteLine(item);
	 	}
	}
	static int addAll(params int[]Array)
	{
		int sum=0;
		foreach(var item in Array)
		{
			sum+=item;
		}
		return sum;
	}	
具名参数：参数的位置不受约束而且可读性好
	static void Main(string[] args)
	{
		 prin(name:"wriken",age:22);
	}
	static void prin(string name,int age)
	{
		console.WriteLine(name,age);
	}
	
可选参数：参数有默认值,与C++中的缺省差不多
	static void Main(string[] args)
	{
		 prin();//具有默认值
	}
	static void prin(string name="wriken",int age=22)
	{
		console.WriteLine(name,age);
	}
扩展方法：共有静态函数，必须放在静态类（XXExtension）中
	static void Main(string[] args)
	{
		 double x=3.1415;
		 double y=x.Round(4); //使用double的拓展方式
	}
	static class DoubleExtension
	{
		public static double Round(this double input,int digits)
		{
			double result=Math.Round(input,digits);
			return result;
		}
	}
	举例：LI NQ 语言集成查询
	using System.linq
4.委托
delegate 是函数指针的升级版
简单使用：Action Func
	static void Main(string[] args)
	{
		int x,y,z;
		Calculator cal= new Calculator();
		Action action=new Action(cal.pri);//委托函数名代表地址 
		//使用函数
		action();
		action.lnvoke();
		//Func
		Func <int,int ,int> func1=new Func<int ,int,int>(cal.Add);
		Func <int,int ,int> func2=new Func<int ,int,int>(cal.Sub);
		x=func1.lnvoke(1,2);
		y=func2.lnvoke(3,2);
	}

	class Calculator
	{
		public void pri()
		{
			console.WriteLine("hello");
		}
		public int Add(int a, intn b)
		{
			int result =a+b;
			return result;
		}
		public int Sub(int a, intn b)
		{
			int result =a-b;
			return result;
		}
	}
自定义委托：
	namespace DelegateExamle
	{
		//注意类型兼容
		public delegate double Calu(double x,double y);
		class Calculator 
		{
			static void Main(String[] args)
			{
				Calculator cal=new Calculator();
				Calu func1=new Calu(cal.Add);
				Calu func2=new Calu(cal.Sub);
				console.WriteLine(func1.lnvoke(1,2),func2.lnvoke(3,2));			
			}
		}
	}
	class Calculator
	{
		public void pri()
		{
			console.WriteLine("hello");
		}
		public int Add(int a, intn b)
		{
			int result =a+b;
			return result;
		}
		public int Sub(int a, intn b)
		{
			int result =a-b;
			return result;
		}
	}
委托的使用：模板方法，回调方法
	模板方法：	
	static void Main(string[] args)
	{
		ProFactor factory=new ProFactor();
		WrapFactry warp=new WrapFactry();
		Logger log=new Logger();
	/*	warp.WrapProduct(factory.MakePizza);
		warp.WrapProduct(factory.MakeCar);	*/
		Func<product> func1=new Func<product>(factory.MakePizza);
		Func<product> func2=new Func<product>(factory.MakeCar);
		Action<product>func3=new Action<product>(log);
		Box box1 = new Box();
		Box box2= new Box();
		box1 = warp.WrapProduct(func1,func3);
		box2 = warp.WrapProduct(func2,func3);
		console.WriteLine(box1.product.Name);
		console.WriteLine(box2.product.Name);	
	}
	class product
	{
		public string Name{get;set;}
		public int price{get;set;}
	}
	class Box
	{
		public product{get;set;}
	}
	class WrapFactry
	{
		//函数内部以委托为参数调用。
		public Box WrapProduct(Func<product> getpro,Action<product> log)
		{
			Box box =new Box();
			//这里兼容各种同类型的委托，实现多种方法
			box.product=getpro.lnvoke();
			//使用回调函数
			if(box.product>=52)
			{
				log.Log(box.product); //以添加函数参数做调用
			}
			return box;
		}
	}
	class ProFactor
	{
		public product MakePizza()
		{
			product Pizza=new product();
			Pizza.Name="Pizza";
			Pizza.price=60;
			return Pizza;
		}
		public product MakeCar()
		{
			product Car=new product();
			Car.Name="car";
			Car.price=50;
			return Car;
		}
	}

	//记录程序的运行状态
	class Logger
	{
		public void Log(product pro)
		{
			console.WriteLine(product.Name,DataTime.UtcNow.product.price);
		}
	}
缺点：这是一种方法级别的紧耦合，可能突破进程内存，注意使用
	可读性下降、debug难度下降
异步调用：
	隐式
	BeginInvoke(null,null);
尽量用接口取代委托
6.事件与委托的关系
事件拥有者+事件成员+事件响应者+事件处理器+事件订阅
 	using System.Timer
 	class Peogram
 	{
 		static void Main(string[] args)
 		{
 			Timer time =new Timer();
 			time.Inteval=1000;
 			Boy boy=new Boy();
 			time.Elapsed+=boy.Action;//订阅事件
 			time.start();
 			console.WriteLine(" ");
 		}
 	}
 	class Boy
 	{ 		//事件处理器
 		internal void Action(object sender,ElapsedEnentArgs e)
 		{
 			console.WriteLine("hello");

 		}
 	}


























