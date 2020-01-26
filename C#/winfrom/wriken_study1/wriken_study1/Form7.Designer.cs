namespace wriken_study1
{
    partial class Form7
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
            this.S_Btn = new System.Windows.Forms.Button();
            this.J_Btn = new System.Windows.Forms.Button();
            this.B_Btn = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // S_Btn
            // 
            this.S_Btn.Location = new System.Drawing.Point(475, 276);
            this.S_Btn.Name = "S_Btn";
            this.S_Btn.Size = new System.Drawing.Size(75, 23);
            this.S_Btn.TabIndex = 0;
            this.S_Btn.Text = "石头";
            this.S_Btn.UseVisualStyleBackColor = true;
            this.S_Btn.Click += new System.EventHandler(this.S_Btn_Click);
            // 
            // J_Btn
            // 
            this.J_Btn.Location = new System.Drawing.Point(326, 276);
            this.J_Btn.Name = "J_Btn";
            this.J_Btn.Size = new System.Drawing.Size(75, 23);
            this.J_Btn.TabIndex = 1;
            this.J_Btn.Text = "剪刀";
            this.J_Btn.UseVisualStyleBackColor = true;
            this.J_Btn.Click += new System.EventHandler(this.J_Btn_Click);
            // 
            // B_Btn
            // 
            this.B_Btn.Location = new System.Drawing.Point(176, 276);
            this.B_Btn.Name = "B_Btn";
            this.B_Btn.Size = new System.Drawing.Size(75, 23);
            this.B_Btn.TabIndex = 2;
            this.B_Btn.Text = " 布";
            this.B_Btn.UseVisualStyleBackColor = true;
            this.B_Btn.Click += new System.EventHandler(this.B_Btn_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(153, 65);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(45, 15);
            this.label1.TabIndex = 3;
            this.label1.Text = " 玩家";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(323, 170);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(45, 15);
            this.label2.TabIndex = 4;
            this.label2.Text = " 结果";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(628, 65);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(37, 15);
            this.label3.TabIndex = 5;
            this.label3.Text = "电脑";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(240, 65);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(15, 15);
            this.label4.TabIndex = 6;
            this.label4.Text = " ";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(710, 64);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(0, 15);
            this.label5.TabIndex = 7;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(409, 169);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(0, 15);
            this.label6.TabIndex = 8;
            // 
            // Form7
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(904, 445);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.B_Btn);
            this.Controls.Add(this.J_Btn);
            this.Controls.Add(this.S_Btn);
            this.Name = "Form7";
            this.Text = "Form7";
            this.Load += new System.EventHandler(this.Form6_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button S_Btn;
        private System.Windows.Forms.Button J_Btn;
        private System.Windows.Forms.Button B_Btn;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
    }
}