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
    public partial class Form7 : Form
    {
        public Form7()
        {
            InitializeComponent();
        }

        player p=new player();
        computer c =new computer();
        judger j=new judger();
        private void Form6_Load(object sender, EventArgs e)
        {

        }
        private void label1_Click(object sender, EventArgs e)
        {
            
        }

        private void S_Btn_Click(object sender, EventArgs e)
        {
            label4.Text="石头";
            j.get_end( p.user_get("石头"),c.com_get() );
            label5.Text=c.message;
            label6.Text=j.mes_end;
        }

        private void J_Btn_Click(object sender, EventArgs e)
        {
            label4.Text="剪刀";
            j.get_end( p.user_get("剪刀"),c.com_get() );
            label5.Text=c.message;
            label6.Text=j.mes_end;
        }

        private void B_Btn_Click(object sender, EventArgs e)
        {
            label4.Text="布";
            j.get_end( p.user_get("布"),c.com_get() );
            label5.Text=c.message;
            label6.Text=j.mes_end;

        }
    }
}
