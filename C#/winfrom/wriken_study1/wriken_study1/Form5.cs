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
using System.Media;
namespace wriken_study1
{
    public partial class Form5 : Form
    {
        public Form5()
        {
            InitializeComponent();
        }
        List<string> list = new List<string>();
        private void Form5_Load(object sender, EventArgs e)
        {
            int index=0;
            string []str= Directory.GetFiles(@"G:\music");
            for(int i=0;i<str.Length;i++)
            {
                index= str[i].LastIndexOf("\\");
                this.listBox1.Items.Add(str[i].Substring(index+1));
                list.Add(str[i]);
            }
             
        }
        //当选项改变时
        SoundPlayer sp = new SoundPlayer();
        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            
            sp.SoundLocation = list[listBox1.SelectedIndex];

        }
        int a = 0;
        private void pre_Btn_Click(object sender, EventArgs e)
        {
            a = listBox1.SelectedIndex;
            a--;
            if (a < 0)
            {
                a = list.Count-1;
            }
            sp.SoundLocation = list[a];
            listBox1.SelectedIndex = a;

        }

        private void next_Btn_Click(object sender, EventArgs e)
        {
            a = listBox1.SelectedIndex;
            a++;
            if (a >= list.Count)
            {
                a = 0;
            }
            sp.SoundLocation = list[a];
            listBox1.SelectedIndex = a;
        }
    }
}
