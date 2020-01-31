using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        int i = 0;
        private void button1_Click(object sender, EventArgs e)
        {
            Graphics g = this.CreateGraphics();
            Point p1 = new Point(100, 200);
            Pen p3 = new Pen(color: System.Drawing.Color.Blue);
            Point p2 = new Point(600, 700);
            g.DrawLine(p3, p1, p2);
            i++;
            label2.Text = i.ToString();


        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            Graphics g = this.CreateGraphics();
            string s = "Wriken is best";
            Point p1 = new Point(100, 200);
            g.DrawString(s, new Font("微软雅黑", 20, FontStyle.Bold), Brushes.Yellow, p1);

        }

        private void button5_Click(object sender, EventArgs e)
        {
            Point p1 = new Point(100, 200);
            Point p2 = new Point(200, 300);
            Point p3 = new Point(300, 400);
            Point p4 = new Point(400, 500);
            Point p5 = new Point(500, 600);
            Point p6 = new Point(600, 700);
            Point p7 = new Point(700, 800);
            Point[] p = { p1, p2, p3, p4, p5, p6, p7 };
            Graphics g = this.CreateGraphics();
            Pen pe = new Pen(Color.Red);
            g.DrawLines(pe, p);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Point p1 = new Point(50, 50);
            Rectangle r = new Rectangle(p1, new Size(60, 80));
            Graphics g = this.CreateGraphics();
            g.DrawRectangle(new Pen(Color.Pink), r);

        }

        private void button4_Click(object sender, EventArgs e)
        {
            Point p1 = new Point(50, 50);
            Rectangle r = new Rectangle(p1, new Size(60, 80));
            Graphics g = this.CreateGraphics();
            g.DrawRectangle(new Pen(Color.Pink), r);
            g.FillRectangle(Brushes.Pink, r);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            Bitmap bmp=new Bitmap(200,300) ;


            Graphics g = Graphics.FromImage(bmp);
            Random r = new Random();
            string str = "";
            for (int i = 0; i < 5; i++)
            {
                str += r.Next(0, 10); 
            }
            string []Fonttyle={"微软雅黑","楷体 ","隶书 ","仿宋","华文行云"};
            FontStyle []F1={FontStyle.Bold,FontStyle.Italic,FontStyle.Regular,FontStyle.Strikeout,FontStyle.Underline};
            Brush []B={Brushes.Pink,Brushes.Blue,Brushes.Red,Brushes.Yellow,Brushes.Black};
            for(i=0;i<5;i++)
            {
               g.DrawString(str[i].ToString(), new Font(Fonttyle[i], 18,F1[i]), B[i], new Point(i*30));
            }
            for (i = 0; i < 20; i++)
            {
                g.DrawLine(new Pen(Color.Cyan), new Point(r.Next(0, bmp.Width)), new Point(r.Next(0,bmp.Height)));
            }
            for (i = 0; i < 50; i++)
            {
                bmp.SetPixel(r.Next(0, bmp.Width), r.Next(0,bmp.Height),Color.Cyan);
            }
            pictureBox1.Image = bmp;
    }
    }
}
