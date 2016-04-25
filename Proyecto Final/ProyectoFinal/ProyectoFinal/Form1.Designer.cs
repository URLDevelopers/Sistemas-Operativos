namespace ProyectoFinal
{
    partial class Form1
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
            this.menu = new System.Windows.Forms.MenuStrip();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.bAgregarRegistros = new System.Windows.Forms.Button();
            this.bBorrarRegistros = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.tborigen = new System.Windows.Forms.TextBox();
            this.tbdestino = new System.Windows.Forms.TextBox();
            this.tbcantidad = new System.Windows.Forms.TextBox();
            this.dgvProductor = new System.Windows.Forms.DataGridView();
            this.Thread = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Status = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Registros = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dgvConsumidor = new System.Windows.Forms.DataGridView();
            this.dataGridViewTextBoxColumn1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.label4 = new System.Windows.Forms.Label();
            this.lconsumidor = new System.Windows.Forms.Label();
            this.tbCola = new System.Windows.Forms.TextBox();
            this.tbConsumidor = new System.Windows.Forms.TextBox();
            this.tbProductor = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.bInicializar = new System.Windows.Forms.Button();
            this.lrespuesta = new System.Windows.Forms.Label();
            this.menu.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvProductor)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvConsumidor)).BeginInit();
            this.SuspendLayout();
            // 
            // menu
            // 
            this.menu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1});
            this.menu.Location = new System.Drawing.Point(0, 0);
            this.menu.Name = "menu";
            this.menu.Size = new System.Drawing.Size(797, 24);
            this.menu.TabIndex = 0;
            this.menu.Text = "menuStrip1";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(24, 20);
            this.toolStripMenuItem1.Text = "?";
            this.toolStripMenuItem1.Click += new System.EventHandler(this.toolStripMenuItem1_Click);
            // 
            // bAgregarRegistros
            // 
            this.bAgregarRegistros.Location = new System.Drawing.Point(15, 194);
            this.bAgregarRegistros.Name = "bAgregarRegistros";
            this.bAgregarRegistros.Size = new System.Drawing.Size(119, 23);
            this.bAgregarRegistros.TabIndex = 1;
            this.bAgregarRegistros.Text = "Agregar registros";
            this.bAgregarRegistros.UseVisualStyleBackColor = true;
            this.bAgregarRegistros.Click += new System.EventHandler(this.bAgregarRegistros_Click);
            // 
            // bBorrarRegistros
            // 
            this.bBorrarRegistros.Location = new System.Drawing.Point(15, 253);
            this.bBorrarRegistros.Name = "bBorrarRegistros";
            this.bBorrarRegistros.Size = new System.Drawing.Size(119, 23);
            this.bBorrarRegistros.TabIndex = 2;
            this.bBorrarRegistros.Text = "Borrar registros";
            this.bBorrarRegistros.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 38);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(38, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Origen";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 88);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(43, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Destino";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 138);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(49, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Cantidad";
            // 
            // tborigen
            // 
            this.tborigen.Location = new System.Drawing.Point(15, 54);
            this.tborigen.MaxLength = 5;
            this.tborigen.Name = "tborigen";
            this.tborigen.Size = new System.Drawing.Size(119, 20);
            this.tborigen.TabIndex = 6;
            this.tborigen.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tborigen_KeyPress);
            // 
            // tbdestino
            // 
            this.tbdestino.Location = new System.Drawing.Point(15, 104);
            this.tbdestino.MaxLength = 5;
            this.tbdestino.Name = "tbdestino";
            this.tbdestino.Size = new System.Drawing.Size(119, 20);
            this.tbdestino.TabIndex = 7;
            // 
            // tbcantidad
            // 
            this.tbcantidad.Location = new System.Drawing.Point(15, 154);
            this.tbcantidad.Name = "tbcantidad";
            this.tbcantidad.Size = new System.Drawing.Size(119, 20);
            this.tbcantidad.TabIndex = 8;
            this.tbcantidad.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbcantidad_KeyPress);
            // 
            // dgvProductor
            // 
            this.dgvProductor.AllowUserToAddRows = false;
            this.dgvProductor.AllowUserToDeleteRows = false;
            this.dgvProductor.AllowUserToResizeColumns = false;
            this.dgvProductor.AllowUserToResizeRows = false;
            this.dgvProductor.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dgvProductor.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            this.dgvProductor.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvProductor.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Thread,
            this.Status,
            this.Registros});
            this.dgvProductor.Location = new System.Drawing.Point(169, 58);
            this.dgvProductor.Name = "dgvProductor";
            this.dgvProductor.ReadOnly = true;
            this.dgvProductor.RowHeadersVisible = false;
            this.dgvProductor.Size = new System.Drawing.Size(239, 150);
            this.dgvProductor.TabIndex = 9;
            // 
            // Thread
            // 
            this.Thread.HeaderText = "Thread";
            this.Thread.Name = "Thread";
            this.Thread.ReadOnly = true;
            this.Thread.Width = 66;
            // 
            // Status
            // 
            this.Status.HeaderText = "Status";
            this.Status.Name = "Status";
            this.Status.ReadOnly = true;
            this.Status.Width = 62;
            // 
            // Registros
            // 
            this.Registros.HeaderText = "Registros Creados";
            this.Registros.Name = "Registros";
            this.Registros.ReadOnly = true;
            this.Registros.Width = 108;
            // 
            // dgvConsumidor
            // 
            this.dgvConsumidor.AllowUserToAddRows = false;
            this.dgvConsumidor.AllowUserToDeleteRows = false;
            this.dgvConsumidor.AllowUserToResizeColumns = false;
            this.dgvConsumidor.AllowUserToResizeRows = false;
            this.dgvConsumidor.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.AllCells;
            this.dgvConsumidor.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            this.dgvConsumidor.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvConsumidor.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.dataGridViewTextBoxColumn1,
            this.dataGridViewTextBoxColumn2,
            this.dataGridViewTextBoxColumn3});
            this.dgvConsumidor.Location = new System.Drawing.Point(414, 58);
            this.dgvConsumidor.Name = "dgvConsumidor";
            this.dgvConsumidor.ReadOnly = true;
            this.dgvConsumidor.RowHeadersVisible = false;
            this.dgvConsumidor.Size = new System.Drawing.Size(240, 150);
            this.dgvConsumidor.TabIndex = 10;
            // 
            // dataGridViewTextBoxColumn1
            // 
            this.dataGridViewTextBoxColumn1.HeaderText = "Thread";
            this.dataGridViewTextBoxColumn1.Name = "dataGridViewTextBoxColumn1";
            this.dataGridViewTextBoxColumn1.ReadOnly = true;
            this.dataGridViewTextBoxColumn1.Width = 66;
            // 
            // dataGridViewTextBoxColumn2
            // 
            this.dataGridViewTextBoxColumn2.HeaderText = "Status";
            this.dataGridViewTextBoxColumn2.Name = "dataGridViewTextBoxColumn2";
            this.dataGridViewTextBoxColumn2.ReadOnly = true;
            this.dataGridViewTextBoxColumn2.Width = 62;
            // 
            // dataGridViewTextBoxColumn3
            // 
            this.dataGridViewTextBoxColumn3.HeaderText = "Registros Creados";
            this.dataGridViewTextBoxColumn3.Name = "dataGridViewTextBoxColumn3";
            this.dataGridViewTextBoxColumn3.ReadOnly = true;
            this.dataGridViewTextBoxColumn3.Width = 108;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(172, 38);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 13);
            this.label4.TabIndex = 11;
            this.label4.Text = "Productor";
            // 
            // lconsumidor
            // 
            this.lconsumidor.AutoSize = true;
            this.lconsumidor.Location = new System.Drawing.Point(411, 38);
            this.lconsumidor.Name = "lconsumidor";
            this.lconsumidor.Size = new System.Drawing.Size(62, 13);
            this.lconsumidor.TabIndex = 12;
            this.lconsumidor.Text = "Consumidor";
            // 
            // tbCola
            // 
            this.tbCola.Location = new System.Drawing.Point(427, 239);
            this.tbCola.Name = "tbCola";
            this.tbCola.Size = new System.Drawing.Size(119, 20);
            this.tbCola.TabIndex = 18;
            this.tbCola.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbCola_KeyPress);
            // 
            // tbConsumidor
            // 
            this.tbConsumidor.Location = new System.Drawing.Point(299, 239);
            this.tbConsumidor.Name = "tbConsumidor";
            this.tbConsumidor.Size = new System.Drawing.Size(119, 20);
            this.tbConsumidor.TabIndex = 17;
            this.tbConsumidor.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbConsumidor_KeyPress);
            // 
            // tbProductor
            // 
            this.tbProductor.Location = new System.Drawing.Point(169, 239);
            this.tbProductor.Name = "tbProductor";
            this.tbProductor.Size = new System.Drawing.Size(119, 20);
            this.tbProductor.TabIndex = 16;
            this.tbProductor.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbProductor_KeyPress);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(424, 223);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(70, 13);
            this.label5.TabIndex = 15;
            this.label5.Text = "Tamaño Cola";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(296, 223);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(113, 13);
            this.label6.TabIndex = 14;
            this.label6.Text = "Parámetro Consumidor";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(166, 223);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(104, 13);
            this.label7.TabIndex = 13;
            this.label7.Text = "Parámetro Productor";
            // 
            // bInicializar
            // 
            this.bInicializar.Location = new System.Drawing.Point(169, 275);
            this.bInicializar.Name = "bInicializar";
            this.bInicializar.Size = new System.Drawing.Size(119, 23);
            this.bInicializar.TabIndex = 19;
            this.bInicializar.Text = "Inicializar variables";
            this.bInicializar.UseVisualStyleBackColor = true;
            this.bInicializar.Click += new System.EventHandler(this.bInicializar_Click);
            // 
            // lrespuesta
            // 
            this.lrespuesta.AutoSize = true;
            this.lrespuesta.Location = new System.Drawing.Point(15, 223);
            this.lrespuesta.Name = "lrespuesta";
            this.lrespuesta.Size = new System.Drawing.Size(13, 13);
            this.lrespuesta.TabIndex = 20;
            this.lrespuesta.Text = "--";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(797, 367);
            this.Controls.Add(this.lrespuesta);
            this.Controls.Add(this.bInicializar);
            this.Controls.Add(this.tbCola);
            this.Controls.Add(this.tbConsumidor);
            this.Controls.Add(this.tbProductor);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.lconsumidor);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.dgvConsumidor);
            this.Controls.Add(this.dgvProductor);
            this.Controls.Add(this.tbcantidad);
            this.Controls.Add(this.tbdestino);
            this.Controls.Add(this.tborigen);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.bBorrarRegistros);
            this.Controls.Add(this.bAgregarRegistros);
            this.Controls.Add(this.menu);
            this.MainMenuStrip = this.menu;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Productor Consumidor";
            this.menu.ResumeLayout(false);
            this.menu.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvProductor)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvConsumidor)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menu;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.Button bAgregarRegistros;
        private System.Windows.Forms.Button bBorrarRegistros;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox tborigen;
        private System.Windows.Forms.TextBox tbdestino;
        private System.Windows.Forms.TextBox tbcantidad;
        private System.Windows.Forms.DataGridView dgvProductor;
        private System.Windows.Forms.DataGridViewTextBoxColumn Thread;
        private System.Windows.Forms.DataGridViewTextBoxColumn Status;
        private System.Windows.Forms.DataGridViewTextBoxColumn Registros;
        private System.Windows.Forms.DataGridView dgvConsumidor;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn1;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn2;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label lconsumidor;
        private System.Windows.Forms.TextBox tbCola;
        private System.Windows.Forms.TextBox tbConsumidor;
        private System.Windows.Forms.TextBox tbProductor;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button bInicializar;
        private System.Windows.Forms.Label lrespuesta;
    }
}

