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
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }


        private void button2_Click(object sender, EventArgs e)
        {
            var frm = new Form2();
            if (this.uesrname_text.Text == "1" && this.password_text.Text == "1")
            {
                frm.Show(this);
            }
            else
            {
                MessageBox.Show("密码错误","error");
            }
        }

        private void label1_Click_1(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void uesrname_text_TextChanged(object sender, EventArgs e)
        {
            string count;
            count = this.uesrname_text.Text.Count().ToString();
            user_lab.Text = count;
        }

        private void password_text_TextChanged(object sender, EventArgs e)
        {
            string pass_count;
            pass_count = this.password_text.Text.Count().ToString();
            pass_lab.Text = pass_count;
        }

        private void btn_cancle_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void label4_Click(object sender, EventArgs e)
        {
            this.label4.Text = "123";
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
