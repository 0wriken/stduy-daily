using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
namespace wriken_study1
{
    public partial class Form4 : Form
    {
        public Form4()
        {
            InitializeComponent();
        }
        List<string> list;
        private void Form4_Load(object sender, EventArgs e)
        {
            string[] str = Directory.GetFiles(@"D:\linux--share\QT图片");
            list =new List<string>();
            for (int i = 0; i < str.Length; i++)
            {
                int index =str[i].LastIndexOf("\\");
                string vam = str[i].Substring(index + 1);
                list.Add(str[i]);
                this.Name_Box.Items.Add(vam);
            }
        }

        private void button2_MouseEnter(object sender, EventArgs e)
        {
            int lenth = this.ClientSize .Height;
            int widght = this.ClientSize.Width;
            Random r = new Random();
            int x = r.Next(0, lenth-button2.Height +1);
            int y = r.Next(0, widght - button2.Width + 1);
            Point p=new Point(x,y);
            button2.Location = p;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("thank your love", "right");
        }

        private void COB_year_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.COB_month.Items.Clear();
            for (int i = 1; i < 13; i++)
            {
                this.COB_month.Items.Add(i + "月");
            }
        }

        private void COB_year_Click(object sender, EventArgs e)
        {
            for (int i = DateTime.Now.Year; i > 1980; i--)
            {
                this.COB_year.Items.Add(i+"年");
            }

        }

        private void COB_month_SelectedIndexChanged(object sender, EventArgs e)
        {
            int days = 0;
            int year=Convert.ToInt32((COB_year.Text).Split(new char[]{'年'},StringSplitOptions.RemoveEmptyEntries)[0]);
            int month=Convert.ToInt32((COB_month.Text).Split(new char[]{'月'},StringSplitOptions.RemoveEmptyEntries)[0]);
            if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
            {
                if (month == 2)
                {
                    days = 28;
                }
            }
                //非闰年情况
            else
            {
                switch (month)
                {
                    case 2:
                        days = 29;
                        break ;
                    case 4:
                    case 6:
                    case 9:
                    case 11:
                        days = 30;
                        break;
                    default :
                        days = 31;
                        break;
                }
            }
            for (int i = 1; i <=days; i++)
            {
                COB_days.Items.Add(i+"日");
            }
        }

        private void Name_Box_DoubleClick(object sender, EventArgs e)
        {
            //MessageBox.Show(list.[Name_Box.SelectedIndex]);
            this.pictureBox1.Image=Image.FromFile (list[Name_Box.SelectedIndex]);


        }

        private void button3_Click(object sender, EventArgs e)
        {
            var form5 = new Form5();
            form5.Show();
        }

           

    }
}
