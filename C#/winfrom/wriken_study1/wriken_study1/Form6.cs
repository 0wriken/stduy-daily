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
    public partial class Form6 : Form
    {
        public Form6()
        {
            InitializeComponent();
        }

        List<string> list = new List<string>();
        private void Form6_Load(object sender, EventArgs e)
        {
            
        }

        private void show_Btn_Click(object sender, EventArgs e)
        {
            OpenFileDialog file = new OpenFileDialog();
            file.Filter = "音乐文件|*.wav|所有文件|*.*";
            file.Title = "Music_play";
            file.Multiselect=true;
            file.InitialDirectory=@"G:\music1";
            file.ShowDialog();
            int index = 0;
            string[] str = file.FileNames;
            for (int i = 0; i < str.Length; i++)
            {
                index = str[i].LastIndexOf("\\");
                listBox1.Items.Add(str[i].Substring(index + 1));
                list.Add(str[i]);
            }
            if (listBox1.SelectedIndex != -1)
            {
                music_player.URL = list[listBox1.SelectedIndex];
                music_player.Ctlcontrols.play();
            }
        }

        private void play_BTN_Click(object sender, EventArgs e)
        {
            if(listBox1.SelectedIndex==-1)
            {
                MessageBox.Show("请选择音乐文件","错误提示");
                return ;   
            }
            if (play_BTN.Text == "播放")
            {
                music_player.Ctlcontrols.play();
                play_BTN.Text = "暂停";
            }
            else if (play_BTN.Text == "暂停")
            {
                music_player.Ctlcontrols.pause();
                play_BTN.Text = "播放";
            }
        }

        private void listBox1_DoubleClick(object sender, EventArgs e)
        {
            music_player.URL = list[listBox1.SelectedIndex];
            music_player.Ctlcontrols.play();
            play_BTN.Text = "暂停";
        }

        private void pre_Btn_Click(object sender, EventArgs e)
        {
            
            int s_index = listBox1.SelectedIndex;
            listBox1.SelectedItems.Clear();
            s_index--;
            if (s_index <0)
            {
                s_index =list.Count-1;
            }
            listBox1.SelectedIndex = s_index;
            music_player.URL = list[s_index];
            play_BTN.Text = "暂停";
        }

        private void next_BTN_Click(object sender, EventArgs e)
        {
            
            int s_index = listBox1.SelectedIndex;
            s_index++;
            listBox1.SelectedItems.Clear();
            if (s_index == list.Count)
            {
                s_index = 0;
            }
            listBox1.SelectedIndex = s_index;
            music_player.URL = list[s_index];
            play_BTN.Text = "暂停";

        }
            
        private void 删除ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //选中的删除个数
            int index = 0;
            int number = listBox1.SelectedItems.Count;
            for (int i = 0; i < number; i++)
            {
                //当前删除文件正在播放自动往下遍历
                if (list[listBox1.SelectedIndex] == music_player.URL)
                {
                    index = listBox1.SelectedIndex;
                    index++;
                    if(index==listBox1.Items.Count)
                    {
                        index=0;   
                    } 
                    listBox1.SelectedIndex=index;
                    music_player.URL=list[index];
                    music_player.Ctlcontrols.play(); 
                }
                list.RemoveAt(listBox1.SelectedIndex);
                listBox1.Items.RemoveAt(listBox1.SelectedIndex);   
            }
        }
        int music_flag = 0;
        private void music_player_PlayStateChange(object sender, AxWMPLib._WMPOCXEvents_PlayStateChangeEvent e)
        {
            //Ready Playing Pause Ended Stop transition
            if (music_player.playState == WMPLib.WMPPlayState.wmppsMediaEnded)
            {
                int index = listBox1.SelectedIndex;
                index++;
                if (index == listBox1.Items.Count)
                {
                    index = 0;
                }
                listBox1.SelectedItems.Clear();
                listBox1.SelectedIndex = index;
                
                //MessageBox.Show(list[index],"music");
                music_player.URL = list[index];
            }
            if(music_player.playState== WMPLib.WMPPlayState.wmppsReady)
            {
                try
                {
                    music_player.Ctlcontrols.play();   

                }
                catch
                {

                }
            }
            if(music_player.playState  == WMPLib.WMPPlayState.wmppsPlaying )
            {
                play_BTN.Text = "暂停";
            }
            if (music_player.playState == WMPLib.WMPPlayState.wmppsPaused)
            {
                play_BTN.Text = "播放";
            }

        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            //当删除干净时
            if (listBox1.SelectedItems.Count == 0)
            {
                //MessageBox.Show("清空", "rigtht");
                music_player.Ctlcontrols.stop();
                this.pre_Btn.Enabled = false;
                this.next_BTN.Enabled = false;
                play_BTN.Text = "播放";
            }
            else
            {
                this.pre_Btn.Enabled = true;
                this.next_BTN.Enabled =true;
            }
        }
    }
}
