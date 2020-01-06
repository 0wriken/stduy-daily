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
	public int? this(string subject) //int? 返回值包括NULL this 用于构造函数 
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
			console.WriteLine("  ");
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
	class Calculator
	{
		public void pri()
		{
			console.WriteLine("hello");
		}
		public int Add(double a, double b)
		{
			int result =a+b;
			return result;
		}
		public int Sub(double a, double b)
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
 	{ 		//事件处理器
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
 			Example i=new Car();
 			i.Run();//多态
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
		/*虚函数要定义方法*/
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
	class volue
	{
		public int GAS{get;private set;}
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
			//userPhone user=new(new SAMSUM());
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
using namespace program
{
	class Program
	{
		public static void Main(string []args)
		{

		}
	}
} 
class Apple
{
	public string color{get;set;}
}
class book
{
	public string Name{get;set;}
}
class box <TID>
{
	public <TID> console{get;set;}
}


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

			if(p1 is student)
			s3=p1 as student;

			//里氏转换应用
			ArrayList list=new ArrayList();
			int[] num=new int [10]{1,2,3,4,5,6};
			string[] str=new iu=string [3]{"wriken","look","nothing"};
			list.Add(num);
			list.Add(str);
			list.Add(p1);
			list.Add(s2);
			foreach(int i in list.length)
			{
				if(list[i] is int[])
				{
					foreach(int j in (list[i] as int[])[j])
					{

						console.WriteLine("整数",(list[i] as int[])[j]));
					}
				}
				if(list[i] is string[])
				{
					int  j=0;
					foreach( j in (list[i] as string[][j])
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
		//不继承父类构造函数 但是会调用
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
	 			console.WriteLine(ht[i]);
	 		}
	 	} 

	}
}
/*简繁转换*/
	class program
	{
		static void Main(string[] args)
		{
			HashTable ht=new HashTable();
			const string s1="繁体中文合集";
			const string s2 ="简体中文合集";
			for(int i=0;i<s2.length;i++)
			{
				ht.Add(s2[i],s1[i]);
			}
			console.WriteLine("写入汉字,将他转换为火星文");
			string str=console.ReadLine();
			for(i=0;i<str.length;i++)
			{
				if(ht.ContainKeyn(str[i]))
				{
					console.WriteLine(ht[str[i]]);
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
			object o=n;//装箱
			int nn=(int)o;//拆箱
		}
	}
}

namespace 键值泛型结合
{
	class propgram
	{
		static void Main(string[] args)
		{
			Dictionary <in,string> dic=new <int,string>();
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
				foreach(char i in str)
				{
					if(dic.ContainValue)
						dic[str[i]]++;
					else
					dic[str[i]]=1;
				}
				for(var a in dic.Keys)
				{
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







