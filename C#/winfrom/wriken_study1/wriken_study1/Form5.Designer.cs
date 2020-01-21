namespace wriken_study1
{
    partial class Form5
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
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.pre_Btn = new System.Windows.Forms.Button();
            this.next_Btn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.ItemHeight = 15;
            this.listBox1.Location = new System.Drawing.Point(59, 44);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(319, 304);
            this.listBox1.TabIndex = 0;
            this.listBox1.SelectedIndexChanged += new System.EventHandler(this.listBox1_SelectedIndexChanged);
            // 
            // pre_Btn
            // 
            this.pre_Btn.Location = new System.Drawing.Point(478, 44);
            this.pre_Btn.Name = "pre_Btn";
            this.pre_Btn.Size = new System.Drawing.Size(75, 23);
            this.pre_Btn.TabIndex = 1;
            this.pre_Btn.Text = " 上一首";
            this.pre_Btn.UseVisualStyleBackColor = true;
            this.pre_Btn.Click += new System.EventHandler(this.pre_Btn_Click);
            // 
            // next_Btn
            // 
            this.next_Btn.Location = new System.Drawing.Point(478, 132);
            this.next_Btn.Name = "next_Btn";
            this.next_Btn.Size = new System.Drawing.Size(75, 23);
            this.next_Btn.TabIndex = 2;
            this.next_Btn.Text = " 下一首";
            this.next_Btn.UseVisualStyleBackColor = true;
            this.next_Btn.Click += new System.EventHandler(this.next_Btn_Click);
            // 
            // Form5
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(627, 441);
            this.Controls.Add(this.next_Btn);
            this.Controls.Add(this.pre_Btn);
            this.Controls.Add(this.listBox1);
            this.Name = "Form5";
            this.Text = "Form5";
            this.Load += new System.EventHandler(this.Form5_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Button pre_Btn;
        private System.Windows.Forms.Button next_Btn;
    }
}