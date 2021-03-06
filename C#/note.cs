/*
dynamic :弱类型转换提供灵活性
C#强转javaspri弱
没有头文件，方法声明与定义不分开
字段：成员变量
静态只读字段：初始化实例（构造不可变）
*/
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
using System;
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
	//使用字典，键为stirng类型，值为int类型
	private Dictionary<string ,int>sorce=new Dictionary<string ,int>(); 
	//？表示包括返回值为NULL this用于构造函数
	public int? this(string subject) 
	{
		get
		{
			//containKey是否包含键
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
			//如果当前的键值存在则替换其对应的数据
			if(this.sorce.ContainKey[subject])
			{
				this.sorce[subject] =value.Value;
			}
			//如果不存在就添加键值
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
			console.WriteLine("  ");
			return;
		}
		console.WriteLine(x+y);
	}
	Tryparse实现机制：
		//Tryparse 不会产生异常,只有faulse 和ture
		static bool TryParse(string input,out double result)
		{
			try
			{
				//parse用于类型转换，类型.parse(string) 如果为null则抛出异常
				result = double.parse(input); 
				return true;
			}
			catch
			{
				result=0;
				return false;
			}
		}
namespace 输出类型
{
	static void Main(string[] args)
	{
		student stu=null;
		//同引用一样，不过引用要初始化数据吗，分配空间  
		if(Create(stu))  
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
}
数组参数： params 必须是形参列表的最后一个
	static void Main(string[] args)
	{
		console.WriteLine(addAll({0,1,2}));//数组对象构造重载
		string str="wrien;yukong";
	 	string []result=str.Split(';' , '.' , '/');//自动按照符号分割字符串
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
		 prin(age:78,name:"YU KONG")
		 prin(name:"wriken",age:22);
	}
	static void prin(string name,int age)
	{
		console.WriteLine(name,age);
	}
可选参数：参数有默认值,与C++中的缺省差不多
	static void Main(string[] args)
	{
		//具有默认值
		 prin();
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
		public delegate Calu int(double x,double y);
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
委托的使用：模板方法，回调方法
	模板方法：	
	static void Main(string[] args)
	{
		//创建对象
		ProFactor factory=new ProFactor();
		WrapFactry warp=new WrapFactry();
		Logger log=new Logger();
	/*	warp.WrapProduct(factory.MakePizza);
		warp.WrapProduct(factory.MakeCar);	*/
		/*
		使用 func Action 泛型委托
		func 与action的区别 func 有返回值 而 action无返回值 
		*/
		Func<product> func1=new Func<product>(factory.MakePizza);
		Func<product> func2=new Func<product>(factory.MakeCar);
		Action<product> func3=new Action<product>(log);
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
			console.WriteLine(pro.Name,pro.price);
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
 	{ 	
		//internal 关键字是类型和类型的成员 访问修饰符。只有在同一程序集的文件中，内部类型或成员才是可访问的
 		internal void Action(object sender,ElapsedEnentArgs e)
 		{
 			console.WriteLine("hello");

 		}
 	}

8.接口 抽象类 abstract public 
开闭原则：封装稳定的成员，把不稳定的抽象为类
重写关键字：override 
不同于虚函数 virtual 抽象修饰无方法体，且类也要定义为抽象类
	using System;
namespace wriken{
 	class program
 	{
 		static void Main(string[] args)
 		{
			 /*定义基类实现多态*/
 			Example i=new Car();
 			//多态实现方法
			 i.Run();
		}
	}		
	/*类似于C++中的虚函数*/
	class Example
	{
		/*虚函数要定义方法*/
		public virtual void RUN()
		{
			console.WriteLine("Exaanpole is Run..");
		}
	}
	class Car:Example
	{
		//继承后开始重写函数
		public override void Run()
		{
			console.WriteLine("Car is Runing..");
		}
	}
	class Trush: Example
	{
		public override void Run()
		{
			console.WriteLine("Trush is runing..");
		}
	}
	/* C#中的抽象类使用**/
	abstract class Example
	{
		/*抽象类中不得实现方法 */
		public abstract void RUN();
	}
	class Car:Example
	{
		public override void Run()
		{
			console.WriteLine("Car is Runing..");
		}
	}
	class Trush: Example
	{
		public override void Run()
		{
			console.WriteLine("Trush is runing..");
		}
	}
	/*接口 为了节省全抽象的麻烦，使用接口 不能包含字段*/
	interface IVaBase
	{
		void RUN();
		void Fill();
		void Stop();
	}
	/*在使用抽象类来继承*/
	abstract class Example:IVaBase
	{
		/*此时不必重写*/
		public void Run()
		{	
			console.WriteLine("Example runing..");
		}
		public void Stop()
		{
			console.WriteLine("Example Stop..");	
		}
		/*未使用的继续保存抽象类*/
		abstract void Fill();
	}
	class Car:Example
	{
		public override void Fill()
		{
			console.WriteLine("CAR is FiLL..");
		}
	}
}
/*接口与耦合*/
using System;
namespace wriken{
 	class program
 	{
 		static void Main(string[] args)
 		{
 			volue v1=new volue();
 			Car c1=new Car(v1);
 			c1.Run(100);
 			console.WriteLine("%d",c1.Speed);
		}
	/*汽油类*/	
	class volue
	{
		public int GAS{get;private set;}
		/* 算出需要的汽油量*/
		public void work(int value)
		{
			this.GAS=value*1000;
		}	
	}
	class Car
	{
		/*紧耦合 */
		private volue _volue;
 		public Car(volue volue1)
 		{
 			this._volue=volue1;1
 		}
 		public int Speed{get;private set;}
 		public void  Run(int value)
 		{
 			 _volue.work(value);
 			 this.Speed=this._volue.GAS/30;
 		}
	}
}
/*使用接口实现低耦合*/
using system;
namespace wriken{
 	class program
 	{
 		static void Main(string[] args)
 		{
			userPhone user=new (new Apple());
			user.whatabout();
		}
	interface phone
	{
		void message();
		void size();
		void CPU();
	}

	class userPhone
	{
		private phone _phone{get;set;}
		public userPhone(phone phone)
		{
			this._phone=phone;
		}
		public void whatabout()
		{	
			this._phone.message();
			this._phone.size();1
			this._phone.CPU();
		}
	}
	class Apple:phone
	{
		public void message()
		{
			console.WriteLine("Apple is good");
		}
		public void size()
		{
		console.WriteLine("Apple size is good");	
		}
		public void CPU()
		{
			console.WriteLine("Apple CPU is good");	
		}
	}
	class SAMSUM:phone
	{
		public void message()
		{
			console.WriteLine("SAMSUM: is good");
		}
		public void size()
		{
		console.WriteLine("SAMSUM: size is good");	
		}
		public void CPU()
		{
			console.WriteLine("SAMSUM: CPU is good");	
		}
	}
}
}
}
/*依赖反转原则  倒置 单元测试*/
namespace wriken
{
	class program
	{
		static void Main(string []args)
		{
			Check_Pow ch1=new Check_Pow(new DeskFan());
			return ;
		}
		interface IPowerLow
		{
			int GetPower();
		}	
		class DeskFan:IPowerLow
		{
			public int GetPower()
			{
				console.WriteLine("get the Desk FAN");
				return 110;
			}
		}
		class Check_Pow
		{
			public IPowerLow _IPowerLow;
			//在一个类中嵌套另一个类，同时作为构造函数的参数传入数据`
			public Check_Pow(IPowerLow IPowerLow)
			{
				this._IPowerLow=IPowerLow;
			}
			public void check(void)
			{
				if(this._IPowerLow.GetPower()<0)
				{
					console.WriteLine("NO POWer");
				}
				else if(this._IPowerLow.GetPower()<100)
				{
					console.WriteLine("the power is find");	
				}
				else if(this._IPowerLow.GetPower()>100)
				{
					console.WriteLine("the power is out");
				}
				else
				{
					console.WriteLine("such enouch power..");
				}
			}
		}

}
}
/*测试环节*/
namespace InterfaceExample.idexTest
{	
	class DeskFan_Text
	{
		//[Fact]使用特性
		[Fact]
		public void IPowerthanZero.OK()
		{
			Check_Pow c1=new Check_Pow(new IPowerthanZero());
			var str="the power is find";
			var str1=c1.check();
			Asset.Equal(str,str1);
		} 
	}
	class IPowerthanZero:IPowerLow
	{
		public int GetPower()
		{
			console.WriteLine("IPowerLow getpower");
			return 0;
		}
	}
}


/*一个接口继承多个接口*/


9./*泛型 编程*/
/*为了避免编程时候的成员膨胀
  正交性 */
using System;
namespace wriken
{
	//interna只在当前程序集中访问
	internal class  my_po
	{
		static void Main(string [] args)
		{
			//里氏转换
			person p1;
			student s1=new student("weiken",22,"M");
			//子类可以转换为父类
			p1=s1;
			//父类由相应子类转换后可以赋值相应的子类对象
			student s2=(student ) p1;
			//is 用于判断双方是否符合里氏转换
			if(p1 is student)
			//as用于里氏转换为对应的类型数据
				s3=p1 as student;
			//里氏转换应用
			/*列表数组*/
			ArrayList list=new ArrayList();
			int[] num=new int [10]{1,2,3,4,5,6};
			string[] str=new string [3]{"wriken","look","nothing"};
			list.Add(num);
			list.Add(str);
			list.Add(p1);
			list.Add(s2);
			foreach(int i in list.length)
			{
				//判断是否为该类型的父子类？
				if(list[i] is int[])
				{
					 int j=0;
					//遍历该列表并转换为数组迭代出每个数据
					foreach(j in (list[i] as int[]).length)
					{
						console.WriteLine("整数",(list[i] as int[])[j]));
					}
				}
				if(list[i] is string[])
				{
					int  j=0;
					foreach( j in (list[i] as string[]).length) 
					{
						console.WriteLine("字符串",(list[i] as string[])[j]));
					}
				}
				if(list[i] is person)
				{
					{
						console.WriteLine("整数",(list[i] as person).show());
					}
				}
				if(list[i] is student)
				{
					{
						console.WriteLine("整数",(list[i] as student).show());
					}
				}
	}
	public class person
	{
		public string Name{get;set;}
		public int age{get;set;}
		public chae sex{get;set;}
		public void person(string NAME,int age,char sex)
		{
			this.NAME=NAME;
			this.age=age;
			this.sex=sex;
		}
		public void show()
		{
			console.WriteLine("名字%s，年龄%d,性别%c",NAME,age,sex);
		} 
	}
	public class student :person
	{
		//自定义父类的构造函数则会调用
		public student(string NAME,int age,char sex):base(NAME,age,sex)
		{
			this.NAME=NAME;
			this.age=age;
			this.sex=sex;	
		}
	}



/*1.值与键的关系*/
using System.Collections;
namespace wriken
{
	class program
	{
	 	static void Main(string[] args)
	 	{	
	 		HashTable ht= new HashTable();
	 		ht.Add(1,"Wriken");
	 		ht.Addp('2',"yukong");
	 		HT.Add(3,"LinKen");
	 		foreach(var i in ht.value)
	 		{
	 			console.WriteLine(i);
	 		}
		 	foreach(var i in ht.Keys)
	 		{
				console.Write("键:",i);
	 			console.WriteLine("值:",ht[i]);
	 		}
	 	} 

	}
}
/*简繁转换*/
	class program
	{
		static void Main(string[] args)
		{
			int F_flag=0;
			HashTable ht=new HashTable();
			const string s1="繁体中文合集";
			const string s2 ="简体中文合集";
			/*将简体与繁体组合为字典*/
			for(int i=0;i<s2.length;i++)
			{
				ht.Add(s2[i],s1[i]);
			}
			console.WriteLine("写入任意汉字,将他转换为相反的数据形式");
			string str=console.ReadLine();
			for(i=0;i<str.length;i++)
			{
				/*使用关键字来遍历字典*/
				foreach(KeyValuePairvar find<string,string> in ht)
				{
					if(find.value=str[])
					{
						console.WriteLine(find.Key);
					}
					if (find.Key=str[i])
					{
						console.WriteLine(find.value);	
					}
				}
				/*自己的方法实现对字典的分别查询*/		
				//判断字典中是否有该数据
				if(ht.ContainKey(str[i])
					F_flag=0;
				if(ht.ContainValue(str[i]))
					F_flag=1;
				if(!F_flag)
				{
					//已知键，用下标显示值
					console.WriteLine(ht[str[i]]);
				}
				else
				{
					//已知值得，用遍历来寻找键
					for(var key in ht.keys)
					{
						if(ht[key]==str[i])
						{
							console.WriteLine(key);
						}
					}
					
				}
			}
		}
	
	/*实例分拣奇偶数*/
	static void Main(string[] args)
	{
		list <int> l1=new list <int>();
		list <int> l2=new list <int>();
		list <int> l3=new list <int>();
		int sum=0;
		for(int i=0;i<100;i++)
		{
			l1.Add(i);
		}
		for(var a in l1)
		{
			if(l1[i]%2)
			{
				l2.Add(a)
			}
			else
			{
				l3.Add(a);
			}
		}
		console.WriteLine("奇数如下");
		for(var a1 in l2)
		{
			sum+=a1;
			console.Write(" ",a1);
		}
		console.WriteLine("sum l2 is %d",sum);
		console.WriteLine("偶数如下");
		for(var a2 in l2)
		{
			sum+=a2;
			console.Write(" ",a2);
		}
		console.WriteLine("sum l3 is %d",sum);
	}
}

namespace 拆箱装箱
{
	class program
	{
		static void Main(string[] args)
		{  
			int n=10;
			//装箱
			object o=n;
			//拆箱
			int nn=(int);
		}
	}
}

namespace 键值泛型结合
{
	class propgram
	{
		static void Main(string[] args)
		{
			Dictionary <in,string> dic=new Dictionary<int,string>();
			foreahc(var i in dic.Keys)
			{
				console.WriteLine(dic[i]);
			}

		}
		//统计每种字符串中每种字符出现的次数
		class check
		{
			public Dictionary<int,char> dic;
			public void check(string str)
			{
				dic=new <char,int>();
				/*循环遍历字符*/
				foreach(char i in str)
				{
					/*判断字符是否存在于字典键中*/
					if(dic.ContainKey(i))
					/*在字典中则代表值（个数）自加*/
						dic[str[i]]++;
					else
					/*不在字典中则，个数从0到1*/
					dic[str[i]]=1;
				}
				for(var a in dic.Keys)
				{
					/*输出每个字符和字符的个数*/
					console.WriteLine("%s,%d",a,dic[a]);
				}
		}

	}
}
namespace 09File类
{
	class program
	{
		 static void Main(string[] args)
		 {
		 	//判断是否存在
		 	bool b=File.Exists(@"C:\user\wriken\1.txt");
		 	File.Copy(@"C:\user\wriken\1.txt",@"C:\user\wriken\2.txt");
		 	File.Move(@"C:\user\wriken\1.txt",@"C:\user\wriken\2.txt");
		 	File.Delete(@"C:\user\wriken\1.txt");

		 	//读取数据
		 	byte[] buf= File.ReadAllBytes(@"C:\user\wriken\1.txt");
			string str=System.Text.Encoding.Default.GetString(buf);
		 	console.WriteLine(str);
		 	string str1=File.ReadAllLines(@"C:\user\wriken\1.txt",Encoding.Default);
		 	//写入数据
		 	string str1="hello wriken\r\n";
		 	byte[] buf1=System.Text.Encoding.Default.GetBytes(str);
		 	File.WriteAllBytes(@"C:\user\wriken\1.txt",buf1);

		 	string[] names={"wriken","yukong","LinKen"};
		 	File.WriteAllLines(@"C:\user\wriken\2.txt",names); 
		 	File.WriteAllText(@"C:\user\wriken\2.txt","新建文件写入");
		 	File.AppendAllText(@"C:\user\wriken\2.txt","追加写入");
		 	
		 	Dictionary.CreateDirectory(@"C:\Wriken\6.txt");
		 	Dictionary.Delete(@"C:\wriken\6.txt",ture);

		 }
	}
}
using system;
using System.Runtime.Serialization.Formatters.Binary;
namespace _序列号
{
	class wriken
	{
		static void Main(string[]args)
		{
			person per=new person();
			person per1;
			per.name=wrien;
			per.age=20;
			per.sex=M;
		   //写入二进制数据
		   FileStream fs = new FileStream("C:/user/yukong/1.txt", FileMode.Create,FileMode.Write,FileMode.open);
		   BinaryFormatter bf = new BinaryFormatter();
		   bf.Serialize(fs,per);
		   //读取二级制数据
		   FileStream fs1 = new FileStream(@"C:/user/yukong/1.txt", FileMode.Create,FileMode.Read,FileMode.open);
		   BinaryFormatter bf1 = new BinaryFormatter();
		   per1=bf1.deSerialize(fs1);
		   console.WriteLine(per1.name);
		   console.WriteLine(per1.age);
		   console.WriteLine(per1.sex);
		}
	}
	public class person
	{
		public int age{get;set;}
		public string name{get;set;}
		public char sex{set;get;}
	}
}
using System.Security.Cryptography;
using System;
namespace _MD5加密
{
	class wriken{
		static void Main(string[]args)
		{
			console.WriteLine("请输入密码");
			string str=console.ReadLine();
			console,WriteLine(GetMD5(str));
			return ;
		}
	}
	public string GetMD5(string str)
	{
		MD5 M=MD5.Create();
		byte[] buffer=System.Text.Encoding.Default.GetBytes(str);
		byte[] pass= M.ComputeHash(buffer);
		string str_pass;
		for(int i=0;i<str_pass.length;i++)
		{
			str_pass+=pass[i].ToString("x2");
		}
		console.WriteLine("转换密码成功");
		return str_pass;
	}
}
string.Trim();//去掉空格

//winform
	SoundPlayer.SoundLocation=...;


openFileDialog 
SaveFileDialog 
FileStream(path,FileMode,FileAccess.Write)
using(FileStream )
	System.Text.Encoding.Default.GetBytes(string );
	Write(buf,0,buf.length);
//超市收银系统
//收银方式类:用户付钱+返回价格 原价 打折 满减	
//商品类：产品的编号名称价格 笔记本 苹果 香蕉  
//仓库数据 以商品类为参数  显示商品信息  导入自创商品的类型+个数 提取货物数量
	Guid 不会重复
//超市 创建仓库 
 public Apple(int i,string n,double p):base(i,n,p)
{
    this.id=i;
    this.name=n;
    this.price=p;
}
abstract class Payway
{
	public double Pay_money
    {
        get;
        set;
    }
	public abstract void 	Pay_mon(double user_mon)
	{

	}

}
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
 		dis_count=d1;
 	}   
 	public void Pay_mon(double user_mon)
 	{
 		this.Pay_money=user_mon*dis_count;
 	}
}

class Full_re:Payway
{
	public double Full_mon
	{
		get;
		set;
	}
	//设置满减的构造函数
	public void Pay_mon(double user_mon)
	{
		if(user_mon>=1000)
			Full_mon=200;
		else if(user_mon>=500)
			Full_mon=50;
		else if(user_mon>=300)
			Full_mon=50;
		else if(user_mon>=100)
			Full_mon=20;
		this.Pay_money=user_mon- Full_mon;
	}
}
//收银台
//满减与折扣不得共享
class Cashier
{
	public  Payway p;
	//支付方式
	public Cashier_way(int i)
	{
		switch(i)
		{
			//默认模式
			case 0:
			{
				PayDiscount p=new PayDiscount(1);		
				break;
			}
			case 1:
			{
				PayDiscount p=new PayDiscount(0.8);
				break;
			}
			case 2:
			{
				PayDiscount p=new PayDiscount(0.6);
				break;
			}
			//满减
			case 3:
			{
				Full_re p=new Full_re();
				break;
			}
		}
	}
	public double Cashier_pro(production pro,int num)
	{
		p.Pay_mon(pro.price*num);
		return this.p.Pay_money;
	}
}
//设置商品类
abstract class production
{
	public int id
	{
		get;
		set;
	}
	public string names
	{
		get;
		set;
	}
	public double price
	{
		get;
		set;
	} 
	public production(int i,string n,double p) 
	{
		this.id=i;
		this.name=n;
		this.price=p;
	}
}

//商品类的继承
class xxx :production
{
	public xxx(int i,string n,double p):base(id,name,price)
	{
		this.id=i;
		this.name=n;
		this.price=p;
	}
}
//仓库类
namespace supermarkey
{
    class Warehouse
    {
        //仓库对象
	public int []number
	{
		get;set;
	}
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
                        NoteBook p = new NoteBook( Convert.ToInt32(Guid.NewGuid()), "惠普笔记本", 10000.0);
                        list[0].Add(p);
                        i++;
                    }
                    break;
                }
            case "Apple":
                {
                    for (i=0; i < num; number[1]++)
                    {
                        Apple p = new Apple(Convert.ToInt32(Guid.NewGuid()), "蓝牙耳机", 1200.0);
                        list[1].Add(p);
                        i++;
                    }
                    break;
                }
            case "Banana":
                {
                    for (i=0; i < num; number[2]++)
                    {
                        Banana p = new Banana(Convert.ToInt32(Guid.NewGuid()), "香蕉", 100.0);
                        list[2].Add(p);
                        i++;
                    }
                    break;
                }
            case "Iphone":
                {
                    for (i=0; i < num; number[3]++)
                    {
                        Iphone p = new Iphone(Convert.ToInt32(Guid.NewGuid()), "苹果手机", 8000.0);
                        list[3].Add(p);
                        i++;
                    }
                    break;
                }
        }
    }
		//导出货物	
		public void export(string pro,int num)
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
						return ;
					}
					for(i=0;i<num;number[0]--)
					{
						//取出数据
						list[0].RemoveAt(number[0]);
						i++;
					}
                    break;
				}
				case "Apple":
				{
					if(number[1]<num)
					{
						Console.WriteLine(pro+"货物已不够","error");
						return ;
					}
					for(i=0;i<num;number[1]--)
					{
						
						list[1].RemoveAt(number[1]);
						i++;
					}
                    break;
				}
				case "Banana":
				{
					if(number[2]<num)
					{
						Console.WriteLine(pro+"货物已不够","error");
						return ;
					}
					for(i=0;i<num;number[2]--)
					{
						
						list[2].RemoveAt(number[2]);
						i++;
					}
                    break;
				}
				case "Iphone":
				{
					if(number[3]<num)
					{
						Console.WriteLine(pro+"货物已不够","error");
						return ;
					}
					for(i=0;i<num;number[3]++)
					{
						list[3].RemoveAt(number[3]) ;
						i++;
					}
                    break;
				}
		}

    }
    }
}
//GDI 
类 Graphics
   Pen Point 
   Graphics.drawline();
   Font()
   Bitmap (bmp)//操作系统下的图片
   微软雅黑 楷体 隶书 仿宋 华文行云
   setpixe
1. 复习：
接口实现方法的重名问题
M1.fly();
M2.fly();
继承抽象或者接口必须方法全部实现
虚函数与抽象函数的区别:
	简单来说虚函数（Virtual）已经包含了也必须包含默认的实现，所以在派生类中可以重新实现也可以不实现这些虚函数。 
抽象函数（abstract）没有提供默认实现，所以在派生类中必须实现这些抽象函数。 
接口中的函数类似于抽象函数，也不提供默认实现，实现接口的类也必须实现这些函数。 
但接口可用于多继承，即，类只能从一个类继承，但可同时实现多个接口。
序列化:
	将对象转换为二进制
反序列化:	
	二进制转化为对象
[Serializable]  //可序列化
FileStream(@"",FileMode.openorCreate,FileAccess.write);
BinaryFormatter();//序列化对象
//服务端
BinaryFormatter.Serialize(new FileStream(@"",FileMode,FileAccess),person);
//客户端
 per=(per)BinaryFormatter.deSerialize(new FileStream(@"",FileMode,FileAccess));
装箱:
	将值类型转换为引用类型
拆箱:
	引用转换为值类型
必须符合两种类型间的继承关系
字典:	
Dictionary<int string>dic =new Dictionary<int string>();
dic.Add(1,"hujk");
dic[2]="掌声";
//遍历所有键与值
foreach(KeValuePair<int string> kv in dic)
{
	kv.Key;
	kv.Value;
}
结构中的构造有且只有0或多个参数
静态方法与非静态: 静态不需要构造，只需要类.方法;
静态类和非静态类:
























