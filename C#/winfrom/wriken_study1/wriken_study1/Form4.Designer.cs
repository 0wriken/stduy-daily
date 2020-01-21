namespace wriken_study1
{
    partial class Form4
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
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.COB_year = new System.Windows.Forms.ComboBox();
            this.COB_month = new System.Windows.Forms.ComboBox();
            this.COB_days = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.Name_Box = new System.Windows.Forms.ListBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.button3 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(12, 41);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "爱";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(557, 41);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 1;
            this.button2.Text = " 不爱";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.MouseEnter += new System.EventHandler(this.button2_MouseEnter);
            // 
            // COB_year
            // 
            this.COB_year.FormattingEnabled = true;
            this.COB_year.Location = new System.Drawing.Point(10, 195);
            this.COB_year.Name = "COB_year";
            this.COB_year.Size = new System.Drawing.Size(121, 23);
            this.COB_year.TabIndex = 2;
            this.COB_year.SelectedIndexChanged += new System.EventHandler(this.COB_year_SelectedIndexChanged);
            this.COB_year.Click += new System.EventHandler(this.COB_year_Click);
            // 
            // COB_month
            // 
            this.COB_month.FormattingEnabled = true;
            this.COB_month.Location = new System.Drawing.Point(260, 195);
            this.COB_month.Name = "COB_month";
            this.COB_month.Size = new System.Drawing.Size(121, 23);
            this.COB_month.TabIndex = 3;
            this.COB_month.SelectedIndexChanged += new System.EventHandler(this.COB_month_SelectedIndexChanged);
            // 
            // COB_days
            // 
            this.COB_days.FormattingEnabled = true;
            this.COB_days.Location = new System.Drawing.Point(511, 195);
            this.COB_days.Name = "COB_days";
            this.COB_days.Size = new System.Drawing.Size(121, 23);
            this.COB_days.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(12, 108);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(119, 23);
            this.label1.TabIndex = 5;
            this.label1.Text = " 结婚日期";
            // 
            // Name_Box
            // 
            this.Name_Box.FormattingEnabled = true;
            this.Name_Box.ItemHeight = 15;
            this.Name_Box.Location = new System.Drawing.Point(15, 308);
            this.Name_Box.Name = "Name_Box";
            this.Name_Box.Size = new System.Drawing.Size(278, 169);
            this.Name_Box.TabIndex = 6;
            this.Name_Box.DoubleClick += new System.EventHandler(this.Name_Box_DoubleClick);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(395, 308);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(254, 169);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 7;
            this.pictureBox1.TabStop = false;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(260, 108);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(150, 23);
            this.button3.TabIndex = 8;
            this.button3.Text = "音乐播放器";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // Form4
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(792, 516);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.Name_Box);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.COB_days);
            this.Controls.Add(this.COB_month);
            this.Controls.Add(this.COB_year);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Name = "Form4";
            this.Text = "Form4";
            this.Load += new System.EventHandler(this.Form4_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.ComboBox COB_year;
        private System.Windows.Forms.ComboBox COB_month;
        private System.Windows.Forms.ComboBox COB_days;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ListBox Name_Box;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button button3;
    }
}