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
    public partial class Form3 : Form
    {
        public Form3()
        {
            InitializeComponent();
        }
        int count;
        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            //对于参数e的使用
            if (e.ClickedItem == 提出ToolStripMenuItem)
            {
                this.Close();
            }
            count++;
        }

        private void 提出ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(MessageBox.Show("确定退出","title",MessageBoxButtons.OKCancel,MessageBoxIcon.Question,MessageBoxDefaultButton.Button1)==System.Windows.Forms.DialogResult.OK)
            this.Close();
        }

        private void Form3_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (e.CloseReason == CloseReason.UserClosing)
            {
                notifyIcon1.BalloonTipTitle = "注意";
                notifyIcon1.BalloonTipText = "双击重新打开我";
                notifyIcon1.ShowBalloonTip(1000);//一秒后逐渐消失
                e.Cancel = true;
                this.Hide();


            }
        }

        private void notifyIcon1_DoubleClick(object sender, EventArgs e)
        {
            
            this.Show();
        }

        private void notifyIcon1_Click(object sender, EventArgs e)
        {
            this.Show();
        }

        private void toolStripStatusLabel1_MouseMove(object sender, MouseEventArgs e)
        {
            toolStripStatusLabel1.Text = e.X.ToString() + "," + e.Y.ToString();

        }

        private void Form3_Load(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = DateTime.Now.ToString();
        }

        int i=0;
        string[] str;
        private void button1_Click(object sender, EventArgs e)
        {
            str = Directory.GetFiles(@"D:\linux--share\QT图片", "*.jpg");
            i--;
            if(i<0)
            {
                i=0;
            }
            this.pictureBox1.Image=Image.FromFile(str[i]);
            
            }

        private void button2_Click(object sender, EventArgs e)
        {
            str= Directory.GetFiles(@"D:\linux--share\QT图片", "*.jpg");
            i++;
            if(i==str.Length)
            {
                i=0;
            }
            this.pictureBox1.Image=Image.FromFile(str[i]);    
        }

        private void button3_Click(object sender, EventArgs e)
        {
            var From4=new Form4();
            From4.Show();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            str = Directory.GetFiles(@"D:\linux--share\QT图片", "*.jpg");
            i++;
            if (i == str.Length)
                i = 0;
            this.pictureBox1.Image = Image.FromFile(str[i]);

        }

        private void button4_Click(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }




    }
}
