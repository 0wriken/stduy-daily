namespace wriken_study1
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.btn_cancle = new System.Windows.Forms.Button();
            this.btn_sure = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.uesrname_text = new System.Windows.Forms.TextBox();
            this.password_text = new System.Windows.Forms.TextBox();
            this.pass_lab = new System.Windows.Forms.Label();
            this.user_lab = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // btn_cancle
            // 
            this.btn_cancle.Location = new System.Drawing.Point(212, 324);
            this.btn_cancle.Name = "btn_cancle";
            this.btn_cancle.Size = new System.Drawing.Size(75, 23);
            this.btn_cancle.TabIndex = 1;
            this.btn_cancle.Text = "取消";
            this.btn_cancle.UseVisualStyleBackColor = true;
            this.btn_cancle.Click += new System.EventHandler(this.btn_cancle_Click);
            // 
            // btn_sure
            // 
            this.btn_sure.Location = new System.Drawing.Point(94, 324);
            this.btn_sure.Name = "btn_sure";
            this.btn_sure.Size = new System.Drawing.Size(75, 23);
            this.btn_sure.TabIndex = 2;
            this.btn_sure.Text = "确定";
            this.btn_sure.UseVisualStyleBackColor = true;
            this.btn_sure.Click += new System.EventHandler(this.button2_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(52, 218);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(75, 15);
            this.label1.TabIndex = 3;
            this.label1.Text = "用户名 ：";
            this.label1.Click += new System.EventHandler(this.label1_Click_1);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(55, 256);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(60, 15);
            this.label2.TabIndex = 4;
            this.label2.Text = "密码 ：";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // uesrname_text
            // 
            this.uesrname_text.Location = new System.Drawing.Point(119, 215);
            this.uesrname_text.Name = "uesrname_text";
            this.uesrname_text.PasswordChar = 'e';
            this.uesrname_text.Size = new System.Drawing.Size(194, 25);
            this.uesrname_text.TabIndex = 5;
            this.uesrname_text.TextChanged += new System.EventHandler(this.uesrname_text_TextChanged);
            // 
            // password_text
            // 
            this.password_text.Location = new System.Drawing.Point(119, 253);
            this.password_text.Name = "password_text";
            this.password_text.PasswordChar = '*';
            this.password_text.Size = new System.Drawing.Size(194, 25);
            this.password_text.TabIndex = 6;
            this.password_text.TextChanged += new System.EventHandler(this.password_text_TextChanged);
            // 
            // pass_lab
            // 
            this.pass_lab.Location = new System.Drawing.Point(319, 253);
            this.pass_lab.Name = "pass_lab";
            this.pass_lab.Size = new System.Drawing.Size(100, 23);
            this.pass_lab.TabIndex = 7;
            this.pass_lab.Click += new System.EventHandler(this.label3_Click);
            // 
            // user_lab
            // 
            this.user_lab.Location = new System.Drawing.Point(319, 217);
            this.user_lab.Name = "user_lab";
            this.user_lab.Size = new System.Drawing.Size(100, 23);
            this.user_lab.TabIndex = 8;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(119, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(194, 173);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 9;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.UseWaitCursor = true;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(280, 433);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(55, 15);
            this.label3.TabIndex = 10;
            this.label3.Text = "label3";
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(12, 12);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(87, 124);
            this.label4.TabIndex = 11;
            this.label4.Click += new System.EventHandler(this.label4_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(431, 388);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.user_lab);
            this.Controls.Add(this.pass_lab);
            this.Controls.Add(this.password_text);
            this.Controls.Add(this.uesrname_text);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btn_sure);
            this.Controls.Add(this.btn_cancle);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_cancle;
        private System.Windows.Forms.Button btn_sure;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox uesrname_text;
        private System.Windows.Forms.TextBox password_text;
        private System.Windows.Forms.Label pass_lab;
        private System.Windows.Forms.Label user_lab;
        private System.Windows.Forms.PictureBox pictureBox1;
        public System.Windows.Forms.Label label3;
        public System.Windows.Forms.Label label4;
    }
}

