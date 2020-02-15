//特性 MVC IOC ORM
public  abstract class Attribute
{}
public class MyAttribute:Attribute
{
	public string diaction{get;set;}
	public MyAttribute(string str)
	{
		diaction=str;
	}
	public void show()
	{
		return  diaction;
	}	
	public bool flag{get;set;}
}
[MyAttribute("这是自定义的特性")]
/*特性是一个类 
默认特性
	Obsolete 标识类是否可用
	AttributeUsage 标识类的自定义功能
自定义特性
	只能在一个类上使用一次
	多次使用则使用特性的特性 [AttributeUsage(AttributeTargets.AllowMultiple=ture)]
	自定义需要继承:AttributeUsage Inherited=true
	使用范围AttributeTargets
特性是用来对属性+字段+方法+类进行描述
*/
//属性
[Obsolete]
message  bool error("是否启动自检测");
//引用特性
[MyAttribute("ok") flag=ture]

/*管理特性
1.使用反射操作
*/
[MyAttribute("用于反射使用")]
class student
{
	public string ID{get;set;}
	public void Answer()
	{
		console.writeline("i am a student");
	}
}
static void Main(string[] args)
{
	//反射获取特性
	Type type =typeof(student);
	if(type.isDefined(MyAttribute).ture)
	{
		foreach(object attribute in type.GetCustomAttribute(typeof(MyAttribute).true))
		{
			MyAttribute m=(MyAttribute)attribute ;
			console.write(m.show());
		}
	}
	//获取字段 属性反射
	PropertyInfo PropertyInfo=type.GetProperty("ID");
	MyAttribute m1=(MyAttribute)PropertyInfo.GetCustomAttribute(typeof(MyAttribute).true);
	//获取方法  方法反射
	MethodInfo methodInfo=type.GeTMethod("Answer");
	MyAttribute M1=(MyAttribute)methodInfo.GetCustomAttribute(typeof(MyAttribute).true);
}	
2.反射 
//MVC AOP TOC ASP.net 
//加载程序集
Assembly assembly=Assembly.Load("Myreflection");
//创建反射类型
Type type=assembly.Gettype("Myreflection.MyAttribute");
//创建对象实例
object o=Activator.CreateInstance(type);
m(o).show();
/*
作用:提升程序的动态能力
操作对象:就是定义.cs结尾的对象
三种方式:
	使用Assembly获取命名空间下的
	通过对象实例获取(Gettype)
	通过引用类型获取(typeof)
*/


/*
作用:使用特性对数据库的切换
*/

public class MyAttribute:Attribute
{
	public string dbstring{get;set;}
	public MyAttribute(string str)
	{
		bdstring=str;
	}
	public string show()
	{
		return  dbstring;
	}	
	public bool flag{get;set;}
}


abstract class UsageDb
{
	void use();
}
class First_DB:UsageDb
{
	void use()
	{
		console.writeline("第一个数据库");
	}
}

class Second_DB:UsageDb
{
	void use()
	{
		console.writeline("第二个数据库");
	}
}
//通过反射来特性来控制数据库的多态
[MyAttribute("程序集.数据库类名")]
class Wriken
{
	public static test()
	{
		Assembly a=Assembly.Load("程序集");
		//反射获取特性
		Type type =typeof(Wriken);
		MyAttribute M1= (MyAttribute)type.GetCustomAttribute(typeof(MyAttribute).true);
		//加载反射数据库类
		Type t1=a.Gettype(M1.show());

		//实例化反射对象 利用接口接收
		UsageDb o=(UsageDb)Activator.CreateInstance(t1);
		o.use();
	}
} 
3.委托
delegate 
	委托使用delegate在方法上声明(本质上是一个类)
	操作的目标是方法
		传进来的方法必须与委托的方法一摸一样
	委托作用是代理,目标对象的所有方法。
	委托多播:按顺序执行多个委托方法.
namespace 委托
{
	
	public delegate void MyInt(int num);
	public delegate T My_T<T>(T num);
	public delegate int MulAdd (int num);
	
	class Mydelegate
	{
		public void show_int(int num)
		{
			console.writeline(num);
		}
		public T show_T<T>(T num)
		{
			console.writeline(num);
		}
	}
	class math{
		public static int num=10;
		public int Add(int p)
		{
			num+=p;
			return num;
		} 
		public int Mul(int p)
		{
			num*=p;
			return num;
		}

	}
	class Wriken
	{
		static void Main(string []argv) 
		{
			Mydelegate mydelegate=new mydelegate();
			MyInt myint=new MyInt(mydelegate.show_int);
			//使用委托q	
			myInt(123);	
			My_T<int> my_t=new My_T<int>(mydelegate.show_T);
			my_t(87456132);		
			//委托多播
			math m=new math();
			MulAdd m_father=null;
			MulAdd m_mul=new MulAdd(math.Mul);
			m_father+=m+Mul;
			MulAdd m_add=new MulAdd(math.Add);
			m_father+=m_add;
			//该多播效果类似于链表组合多个算法
			m_father(10);


		}
	}
}	
4.事件
是委托的一种方法;
	从表面上看是委托类上的引用
	从IL文件上看，他是一个委托的方法
事件订阅:把目标类的方法添加到委托上
事件发布：定义的委托事件
事件触发:调用委托对象
class MyEvent
{
	public delegate void ShowEvent();
	//事件类型
	public event ShowEvent showevent;

	//委托方法
	public void show()
	{
		console.writeline("我是委托的show")；
	}
	public void show_new()
	{
		console.writeline("新的方法由事件调用");
		//事件触发
		showevent();	
	}

}	
class Wriken
{

	static void Main(string[]argv)
	{
		//创建对象
		MyEvent m1=new MyEvent();
		//事件添加方法
		m1.showevent +=new ShowEvent(m1.show);
		m1.show_new();
	}
}
实例:病人和医生间的监控系统;
class painent
{
	//体温
	public float painent_tmp{get;set;} 
	
	public delegate void painent_care();
	//事件
	public event painent_care painent_handle;

	public painent(float tmp)
	{
		this.painent_tmp=tmp;
	}
	void painent_call()
	{
		if(this.painent_tmp>38)
		{
			console.writeline("病人有发烧迹象");
		}
		//事件发布
		painent_handle();
	}

}
class doctor
{
	public void doctor_care()
	{
		console.writeline("医生来了");
	}

}
class Wriken
{
	static void Main(string[]argv)
	{
		painent p=new painent(38.0);
		doctor d=new doctor();
		//订阅事件
		p.painent_handle+=new painent_care(d.doctor_care);
		//事件触发
		p.painent_call();
	}
}
5.redis分布式锁...看API即可
6.集合框架
普通数组:list源码解析
	private const int _defaultCapacity=4;//默认数组长度
	private T[] _items;//泛型数组
	private int _size;//数组中的元素个数
	private int _version;//版本号
	调用Add判断是否扩容
		if(_size==lenth)
			_size++; 
			T[]_items=new _items[_size];
			arry.copy();
	每一次扩容，性能出现问题：[1,2,3,4]=[1,2,3,4,5]增删改太慢 查会快一点
链表: LinkedList  


7.多线程
class Wriken_pthread
{
	public void pthread_show()
	{
		console.writeline("启动线程");
	}
	public void Main(string[] args)
	{
		ThreadStart thread_satrt=new ThreadStarto(pthread_show);
		Thread thread=new Thread(thread_satrt);
		thread.Start();//启动线程
		thread.Abort();//终止线程 删除
		thread.Join();
		thread.Sleep(2300);//进入休眠状态
		console.writeline("主线程执行程序");
	}
}
//多线程的应用 秒杀
class Production
{
	public int Num_Pro=10;
	public void Get_Pro()
	{
		lock(this);//加锁使其同步
		if(Num_Pro==0)
		{
			console.writeline("货物已秒杀");
		}
		console.writeline1("获取到货物{0}"Num_Pro);
		Num_Pro--;
	}
}
class Comstum
{
	void Comstum_task()
	{
		Production p=new Production();
		for(int i=0;i<20;i++)
		{
			Thread thread=new Thread(new ThreadStart(p.Get_Pro);
			thread.Start();
			console.writeline("秒杀开始");
		}
	}
}
//Thread 无序性 无返回值

//4个线程 算1~100和
class sum
{
	public int sum1()
	{
		int sum=0;
		for(int i=0;i<26;i++)
		{
			sum+=i;
		}
		return sum;
	}

	public int sum2()
	{
		int sum=0;
		for(int i=26;i<51;i++)
		{
			sum+=i;
		}
		return sum;

	}
	public int sum3()
	{
		int sum=0;
		for(int i=51;i<76;i++)
		{
			sum+=i;
		}
		return sum;

	}
	public int sum4()
	{
		int sum=0;
		for(int i=76;i<101;i++)
		{
			sum+=i;
		}
		return sum;

	}
}
class sum_task
{
	
	public void show_sum()
	{
		sum s=new sum();
		Func <int> fun1=new Func<int>(s.sum1);
		Task<int> task1=new Task<int>(fun1);
		Func <int> fun2=new Func<int>(s.sum2);
		Task<int> task2=new Task<int>(fun2);
		Func <int> fun3=new Func<int>(s.sum3);
		Task<int> task3=new Task<int>(fun3);
		Func <int> fun4=new Func<int>(s.sum4);
		Task<int> task4=new Task<int>(fun4);
		task1.Start();
		task2.Start();
		task3.Start();
		task4.Start();	
		console.writeline("every thread end sum is {0}"，task1.Result);
		console.writeline("every thread end sum is {0}"，task2.Result);
		console.writeline("every thread end sum is {0}"，task3.Result);
		console.writeline("every thread end sum is {0}"，task4.Result);
		console.writeline("the end sum is {0}",task1.Result+task2.Result+task3.Result+task4.Result);
	}
}

//重构此代码，使其多态化
class sum_num
{
	public int start{get;set;}
	public int end{get;set;}
	public int sum_end
	{
		int sum=0;
		for(int i=start;i<end;i++)
		{	
			sum+=i;
		}
		return sum;
	}
}
class Task_sum
{
	private int count;
	private int sum;
	public Task_sum(int c)
	{
			count=c;
	}
	public void Task_end()
	{
		for(int i=0;i<count;i++)
		{
			sum_num s=new sum_num();
			s.start=i*25;
			s.end=(++i)*25+1;
			Task <int> t=new <int>Task.Run(()=>s.sum_end());
			sum+=t.Result();
		}
		console.writeline("get the end sum is {0}",this.sum);
	}
}

8.加密解密
/*
MD5加密算法
	不可逆算法
	特性:1.通过加密是32位的
        2.加密字符串不可逆
	MD5破解:2的32次方
	MD5的运用: 
		1.MD5做电子身份证(电子签名)==(消息摘要)
		2.svn版本控制，git提交代码，如果是没有修改则不允许提交
		3.文件上传，分布式文件上传
		4.项目运用：用户加密(密码具有唯一的校验性)
*/
class MD5
{
	public static string MD5_encryption(string str)
	{
		//MD5为抽象类 ，实例化如下
		MD5 md5=new MD5CrpyServiceProvice();
		//将string 转换为字节数组
		byte[] buffer=Encoding.Default.GetBytes(str);
		//开始加密
		byte[] new_buffer=md5.ComputeHash(buffer);
		StringBuilder sb=new StringBuilder(); 
		for(int i=0;i<new_buffer.lenth;i++)
		{
			//将加密后得到的字符串转换为string并输出格式为十六进制每次输出两位数
			sb.Append(new_buffer[i].Tostring("x2"));
		}
		return sb.Tostring();
	}
	//以文件流为参数时
	public static string MD5_cryptography(Stream input)
	{
		MD5 m=new MD5.Create();
		byte[] buffer=m.ComputeHash(input);
		StringBuilder sb=new StringBuilderO();
		for(int i=0;i<buffer.lenth;i++)
		{
			sb.Append(buffer[i].Tostring("x2"));
		}
		return sb.Tostring();

	}
}
/*DES加密算法
	既能加密也能解密)
	关键key(密钥)
*/
class DES
{
	//传入参数 加密字符 一个密钥 一个私钥
	public static string EncryptString(string pToEncrypt, string key, string IV)
	{
		//把两个钥匙 密钥和私钥转换为数据处理的字节数组
        Byte[] keyArray = new byte[32];
        keyArray = System.Text.UTF8Encoding.UTF8.GetBytes(key);
        Byte[] ivArray = new byte[32];
        ivArray = System.Text.UTF8Encoding.UTF8.GetBytes(IV);
		//创建DES加密的对象实例化
		DES des=new DESCryptoServiceProvide();
		//加密转换需要密钥和私钥
		ICryptoTransfrom cry= des.CreateEncryptor(keyArray,ivArray);
		MemoryStream Mem=new MemoryStream();
		//把加密后的数据关联到缓冲区
		CryptoStream Crystream1=new CryptoStream(Mem,cry,CryptoStreamMode.Write);
		//创建写入流并写入加密数据
		StreamWriter Stream_wri=new StreamWriter(cry);
		Stream_wri.Write(pToEncrypt);
		Mem.Flush();
		Crystream1.FlushBlock();
		Stream_wri.Flush();
		//取出加密的数据
		byte[] des_byte=Mem.GetBuffer();
		console.writeline("获取到的数据", Conver.ToBase64String(des_byte));
		return Conver.ToBaseString(des_byte);
	}
	public static string decode(string Enc_data,string key,string IV)
	{
		Byte[] keyArray = new byte[32];
        keyArray = System.Text.UTF8Encoding.UTF8.GetBytes(key);
        Byte[] ivArray = new byte[32];
        ivArray = System.Text.UTF8Encoding.UTF8.GetBytes(IV);
		DES des=new DESCryptoServiceProvide();
		Byte[] Enc_buf=Conver.FromBase64String(Enc_data);
		//此处解密转换
		ICryptoTransfrom dec=des.CreateDecode(keyArray,ivArray);
		MemoryStream Mem=new MemoryStream();
		CryptoStream Crystream=new CryptoStream(Mem,dec,CryptoStreamMode.Write);
		
		//将要解码的数据写入流中
		Crystream.Write(Enc_buf,0,Enc.lenth);
		Crystream.FlushBlock();
		//得到解码后的值
		byte[] Mem_buf=Mem.ToArray();
		console.writeline("解码后的值为{0}",Conver.ToBase64String(Mem_buf));
		return Conver.ToBase64String(Mem_buf);
	}
}   
RSA非对称算法





