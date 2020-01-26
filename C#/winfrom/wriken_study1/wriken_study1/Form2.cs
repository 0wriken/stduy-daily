using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace wriken_study1
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            var from3=new Form3();
            var from1 = this.Owner as Form1;
            if(from1==null)
            {
                MessageBox.Show("转换失败","error");
                return ;
            }
            //Owner转换为owner
            from1.label4.Text = "开启身份验证";
            from3.Show();
        }
        private void Form2_Load(object sender, EventArgs e)
        {
            var form6 = new Form6();
            form6.Show();
        }


        private void timer1_Tick(object sender, EventArgs e)
        {
            
            this.label2.Text = this.label2.Text.Substring(this.label2.Text.Length - 1) + this.label2.Text.Substring(0, this.label2.Text.Length-1);
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
        int flag=0;
        int time_flag = 0;
        private void dou_Btn_Click(object sender, EventArgs e)
        {
            if (flag == 0)
            {
                (this.Owner as Form1).label4.Text = "开始抖动的道路";
                this.timer2.Enabled = true;
                flag = 1;
            }
            else
            {
                (this.Owner as Form1).label4.Text = "恢复正常";
                this.timer2.Enabled = false;
                flag = 0;
            }
        }
        private void timer2_Tick(object sender, EventArgs e)
        {
            Point p = new Point(65, 65);
            Point p1 = new Point(50, 50);
            if (time_flag == 0)
            {
                this.Location = p;
                time_flag = 1;
            }
            else
            {
                this.Location = p1;
                time_flag = 0;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            var form6 = new Form6();
            form6.Show();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            var form7 = new Form7();
            form7.Show();
        }
    }
}
