namespace wriken_study1
{
    partial class Form6
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form6));
            this.music_player = new AxWMPLib.AxWindowsMediaPlayer();
            this.play_BTN = new System.Windows.Forms.Button();
            this.pre_Btn = new System.Windows.Forms.Button();
            this.next_BTN = new System.Windows.Forms.Button();
            this.show_Btn = new System.Windows.Forms.Button();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.删除ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)(this.music_player)).BeginInit();
            this.contextMenuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // music_player
            // 
            this.music_player.AllowDrop = true;
            this.music_player.Enabled = true;
            this.music_player.Location = new System.Drawing.Point(1, -1);
            this.music_player.Name = "music_player";
            this.music_player.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("music_player.OcxState")));
            this.music_player.Size = new System.Drawing.Size(522, 376);
            this.music_player.TabIndex = 0;
            this.music_player.PlayStateChange += new AxWMPLib._WMPOCXEvents_PlayStateChangeEventHandler(this.music_player_PlayStateChange);
            // 
            // play_BTN
            // 
            this.play_BTN.Location = new System.Drawing.Point(13, 505);
            this.play_BTN.Name = "play_BTN";
            this.play_BTN.Size = new System.Drawing.Size(94, 23);
            this.play_BTN.TabIndex = 1;
            this.play_BTN.Text = "播放";
            this.play_BTN.UseVisualStyleBackColor = true;
            this.play_BTN.Click += new System.EventHandler(this.play_BTN_Click);
            // 
            // pre_Btn
            // 
            this.pre_Btn.Location = new System.Drawing.Point(130, 504);
            this.pre_Btn.Name = "pre_Btn";
            this.pre_Btn.Size = new System.Drawing.Size(75, 23);
            this.pre_Btn.TabIndex = 2;
            this.pre_Btn.Text = " 上一首";
            this.pre_Btn.UseVisualStyleBackColor = true;
            this.pre_Btn.Click += new System.EventHandler(this.pre_Btn_Click);
            // 
            // next_BTN
            // 
            this.next_BTN.Location = new System.Drawing.Point(248, 503);
            this.next_BTN.Name = "next_BTN";
            this.next_BTN.Size = new System.Drawing.Size(75, 23);
            this.next_BTN.TabIndex = 3;
            this.next_BTN.Text = " 下一首";
            this.next_BTN.UseVisualStyleBackColor = true;
            this.next_BTN.Click += new System.EventHandler(this.next_BTN_Click);
            // 
            // show_Btn
            // 
            this.show_Btn.Location = new System.Drawing.Point(387, 503);
            this.show_Btn.Name = "show_Btn";
            this.show_Btn.Size = new System.Drawing.Size(75, 23);
            this.show_Btn.TabIndex = 4;
            this.show_Btn.Text = " 打开";
            this.show_Btn.UseVisualStyleBackColor = true;
            this.show_Btn.Click += new System.EventHandler(this.show_Btn_Click);
            // 
            // listBox1
            // 
            this.listBox1.ContextMenuStrip = this.contextMenuStrip1;
            this.listBox1.FormattingEnabled = true;
            this.listBox1.ItemHeight = 15;
            this.listBox1.Location = new System.Drawing.Point(746, 12);
            this.listBox1.Name = "listBox1";
            this.listBox1.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
            this.listBox1.Size = new System.Drawing.Size(204, 349);
            this.listBox1.TabIndex = 5;
            this.listBox1.SelectedIndexChanged += new System.EventHandler(this.listBox1_SelectedIndexChanged);
            this.listBox1.DoubleClick += new System.EventHandler(this.listBox1_DoubleClick);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.删除ToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(176, 56);
            // 
            // 删除ToolStripMenuItem
            // 
            this.删除ToolStripMenuItem.Name = "删除ToolStripMenuItem";
            this.删除ToolStripMenuItem.Size = new System.Drawing.Size(175, 24);
            this.删除ToolStripMenuItem.Text = "删除(&D)";
            this.删除ToolStripMenuItem.Click += new System.EventHandler(this.删除ToolStripMenuItem_Click);
            // 
            // Form6
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1114, 623);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.show_Btn);
            this.Controls.Add(this.next_BTN);
            this.Controls.Add(this.pre_Btn);
            this.Controls.Add(this.play_BTN);
            this.Controls.Add(this.music_player);
            this.Name = "Form6";
            this.Text = "Form6";
            this.Load += new System.EventHandler(this.Form6_Load);
            ((System.ComponentModel.ISupportInitialize)(this.music_player)).EndInit();
            this.contextMenuStrip1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private AxWMPLib.AxWindowsMediaPlayer music_player;
        private System.Windows.Forms.Button play_BTN;
        private System.Windows.Forms.Button pre_Btn;
        private System.Windows.Forms.Button next_BTN;
        private System.Windows.Forms.Button show_Btn;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 删除ToolStripMenuItem;
    }
}