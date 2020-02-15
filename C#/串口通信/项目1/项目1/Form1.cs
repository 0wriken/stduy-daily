using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 项目1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            //开始倒计时，并且显示倒计时数据
            string str1;
            string str = comboBox1.Text;
            str1=str.Substring(0, str.Length-1);
            progressBar1.Maximum = Convert.ToInt32(str1);
            
            //显秒数
            label3.Text =comboBox1.Text;
            progressBar1.Minimum = 0;
            //启动定时器
            this.timer1.Enabled = true;
        }

        private void Form1_LocationChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string str="";
            for(int i=1;i<61;i++)
            {
                str+=i;
                this.comboBox1.Items.Add(str + "秒");
                str = "";
            }
                
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            string str=this.label3.Text;
            string str1=this.comboBox1.Text;
            //显示进度条
            this.progressBar1.Value = Convert.ToInt32(str1.Substring(0, str1.Length - 1)) - Convert.ToInt32(str.Substring(0, str1.Length - 1))+1;
            this.label3.Text = (Convert.ToInt32(str.Substring(0, str.Length - 1)) - 1).ToString() + "秒";
            if(label3.Text=="0秒")
            {
                timer1.Enabled = false;
                MessageBox.Show("定时时间到", "oo");
            }
            
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {


        
  

        }
    }
    }
