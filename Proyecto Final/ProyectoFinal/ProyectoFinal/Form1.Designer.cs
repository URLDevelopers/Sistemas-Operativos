namespace ProyectoFinal
{
    partial class ProductorConsumidor
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
            this.OD = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Status = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Registros = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dgvConsumidor = new System.Windows.Forms.DataGridView();
            this.dataGridViewTextBoxColumn1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dataGridViewTextBoxColumn2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.label4 = new System.Windows.Forms.Label();
            this.lconsumidor = new System.Windows.Forms.Label();
            this.tbCola = new System.Windows.Forms.TextBox();
            this.tbConsumidor = new System.Windows.Forms.TextBox();
            this.tbProductor = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.bInicializar = new System.Windows.Forms.Button();
            this.ptablas = new System.Windows.Forms.Panel();
            this.lerroresDB = new System.Windows.Forms.Label();
            this.lcola = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.pinicio = new System.Windows.Forms.Panel();
            this.trefresh = new System.Windows.Forms.Timer(this.components);
            this.menu.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvProductor)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvConsumidor)).BeginInit();
            this.ptablas.SuspendLayout();
            this.pinicio.SuspendLayout();
            this.SuspendLayout();
            // 
            // menu
            // 
            this.menu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1});
            this.menu.Location = new System.Drawing.Point(0, 0);
            this.menu.Name = "menu";
            this.menu.Size = new System.Drawing.Size(705, 24);
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
            this.bAgregarRegistros.Location = new System.Drawing.Point(8, 71);
            this.bAgregarRegistros.Name = "bAgregarRegistros";
            this.bAgregarRegistros.Size = new System.Drawing.Size(190, 23);
            this.bAgregarRegistros.TabIndex = 1;
            this.bAgregarRegistros.Text = "Agregar registros";
            this.bAgregarRegistros.UseVisualStyleBackColor = true;
            this.bAgregarRegistros.Click += new System.EventHandler(this.bAgregarRegistros_Click);
            // 
            // bBorrarRegistros
            // 
            this.bBorrarRegistros.Location = new System.Drawing.Point(8, 100);
            this.bBorrarRegistros.Name = "bBorrarRegistros";
            this.bBorrarRegistros.Size = new System.Drawing.Size(190, 23);
            this.bBorrarRegistros.TabIndex = 2;
            this.bBorrarRegistros.Text = "Borrar registros";
            this.bBorrarRegistros.UseVisualStyleBackColor = true;
            this.bBorrarRegistros.Click += new System.EventHandler(this.bBorrarRegistros_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(5, 29);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(38, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Origen";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(72, 29);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(43, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Destino";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(137, 29);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(49, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Cantidad";
            // 
            // tborigen
            // 
            this.tborigen.Location = new System.Drawing.Point(8, 45);
            this.tborigen.MaxLength = 5;
            this.tborigen.Name = "tborigen";
            this.tborigen.Size = new System.Drawing.Size(59, 21);
            this.tborigen.TabIndex = 6;
            this.tborigen.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tborigen_KeyPress);
            // 
            // tbdestino
            // 
            this.tbdestino.Location = new System.Drawing.Point(75, 45);
            this.tbdestino.MaxLength = 5;
            this.tbdestino.Name = "tbdestino";
            this.tbdestino.Size = new System.Drawing.Size(59, 21);
            this.tbdestino.TabIndex = 7;
            // 
            // tbcantidad
            // 
            this.tbcantidad.Location = new System.Drawing.Point(140, 45);
            this.tbcantidad.Name = "tbcantidad";
            this.tbcantidad.Size = new System.Drawing.Size(58, 21);
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
            this.OD,
            this.Status,
            this.Registros});
            this.dgvProductor.Location = new System.Drawing.Point(214, 29);
            this.dgvProductor.Name = "dgvProductor";
            this.dgvProductor.ReadOnly = true;
            this.dgvProductor.RowHeadersVisible = false;
            this.dgvProductor.Size = new System.Drawing.Size(309, 225);
            this.dgvProductor.TabIndex = 9;
            // 
            // Thread
            // 
            this.Thread.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.AllCells;
            this.Thread.HeaderText = "Thread";
            this.Thread.Name = "Thread";
            this.Thread.ReadOnly = true;
            this.Thread.Width = 65;
            // 
            // OD
            // 
            this.OD.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.AllCells;
            this.OD.HeaderText = "Origen,Destino";
            this.OD.Name = "OD";
            this.OD.ReadOnly = true;
            this.OD.Width = 102;
            // 
            // Status
            // 
            this.Status.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.AllCells;
            this.Status.HeaderText = "Status";
            this.Status.Name = "Status";
            this.Status.ReadOnly = true;
            this.Status.Width = 62;
            // 
            // Registros
            // 
            this.Registros.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.AllCells;
            this.Registros.HeaderText = "Registros";
            this.Registros.Name = "Registros";
            this.Registros.ReadOnly = true;
            this.Registros.Width = 76;
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
            this.dataGridViewTextBoxColumn2});
            this.dgvConsumidor.Location = new System.Drawing.Point(529, 29);
            this.dgvConsumidor.Name = "dgvConsumidor";
            this.dgvConsumidor.ReadOnly = true;
            this.dgvConsumidor.RowHeadersVisible = false;
            this.dgvConsumidor.Size = new System.Drawing.Size(135, 225);
            this.dgvConsumidor.TabIndex = 10;
            // 
            // dataGridViewTextBoxColumn1
            // 
            this.dataGridViewTextBoxColumn1.HeaderText = "Thread";
            this.dataGridViewTextBoxColumn1.Name = "dataGridViewTextBoxColumn1";
            this.dataGridViewTextBoxColumn1.ReadOnly = true;
            this.dataGridViewTextBoxColumn1.Width = 65;
            // 
            // dataGridViewTextBoxColumn2
            // 
            this.dataGridViewTextBoxColumn2.HeaderText = "Status";
            this.dataGridViewTextBoxColumn2.Name = "dataGridViewTextBoxColumn2";
            this.dataGridViewTextBoxColumn2.ReadOnly = true;
            this.dataGridViewTextBoxColumn2.Width = 62;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Calibri", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(327, 12);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(62, 15);
            this.label4.TabIndex = 11;
            this.label4.Text = "Productor";
            // 
            // lconsumidor
            // 
            this.lconsumidor.AutoSize = true;
            this.lconsumidor.Font = new System.Drawing.Font("Calibri", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lconsumidor.Location = new System.Drawing.Point(559, 12);
            this.lconsumidor.Name = "lconsumidor";
            this.lconsumidor.Size = new System.Drawing.Size(74, 15);
            this.lconsumidor.TabIndex = 12;
            this.lconsumidor.Text = "Consumidor";
            // 
            // tbCola
            // 
            this.tbCola.Location = new System.Drawing.Point(12, 107);
            this.tbCola.Name = "tbCola";
            this.tbCola.Size = new System.Drawing.Size(114, 21);
            this.tbCola.TabIndex = 18;
            this.tbCola.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbCola_KeyPress);
            // 
            // tbConsumidor
            // 
            this.tbConsumidor.Location = new System.Drawing.Point(12, 67);
            this.tbConsumidor.Name = "tbConsumidor";
            this.tbConsumidor.Size = new System.Drawing.Size(114, 21);
            this.tbConsumidor.TabIndex = 17;
            this.tbConsumidor.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbConsumidor_KeyPress);
            // 
            // tbProductor
            // 
            this.tbProductor.Location = new System.Drawing.Point(12, 27);
            this.tbProductor.Name = "tbProductor";
            this.tbProductor.Size = new System.Drawing.Size(114, 21);
            this.tbProductor.TabIndex = 16;
            this.tbProductor.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.tbProductor_KeyPress);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(9, 91);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(67, 13);
            this.label5.TabIndex = 15;
            this.label5.Text = "Tamaño Cola";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(9, 51);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(117, 13);
            this.label6.TabIndex = 14;
            this.label6.Text = "Parámetro Consumidor";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(9, 11);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(107, 13);
            this.label7.TabIndex = 13;
            this.label7.Text = "Parámetro Productor";
            // 
            // bInicializar
            // 
            this.bInicializar.Location = new System.Drawing.Point(13, 134);
            this.bInicializar.Name = "bInicializar";
            this.bInicializar.Size = new System.Drawing.Size(113, 23);
            this.bInicializar.TabIndex = 19;
            this.bInicializar.Text = "Inicializar variables";
            this.bInicializar.UseVisualStyleBackColor = true;
            this.bInicializar.Click += new System.EventHandler(this.bInicializar_Click);
            // 
            // ptablas
            // 
            this.ptablas.Controls.Add(this.lerroresDB);
            this.ptablas.Controls.Add(this.lcola);
            this.ptablas.Controls.Add(this.label8);
            this.ptablas.Controls.Add(this.label4);
            this.ptablas.Controls.Add(this.dgvProductor);
            this.ptablas.Controls.Add(this.bBorrarRegistros);
            this.ptablas.Controls.Add(this.tbcantidad);
            this.ptablas.Controls.Add(this.bAgregarRegistros);
            this.ptablas.Controls.Add(this.dgvConsumidor);
            this.ptablas.Controls.Add(this.label3);
            this.ptablas.Controls.Add(this.tbdestino);
            this.ptablas.Controls.Add(this.tborigen);
            this.ptablas.Controls.Add(this.lconsumidor);
            this.ptablas.Controls.Add(this.label1);
            this.ptablas.Controls.Add(this.label2);
            this.ptablas.Location = new System.Drawing.Point(4, 36);
            this.ptablas.Name = "ptablas";
            this.ptablas.Size = new System.Drawing.Size(690, 262);
            this.ptablas.TabIndex = 24;
            this.ptablas.Visible = false;
            // 
            // lerroresDB
            // 
            this.lerroresDB.AutoSize = true;
            this.lerroresDB.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lerroresDB.Location = new System.Drawing.Point(11, 163);
            this.lerroresDB.Name = "lerroresDB";
            this.lerroresDB.Size = new System.Drawing.Size(99, 19);
            this.lerroresDB.TabIndex = 26;
            this.lerroresDB.Text = "Errores BDD: ";
            this.lerroresDB.Visible = false;
            // 
            // lcola
            // 
            this.lcola.AutoSize = true;
            this.lcola.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lcola.Location = new System.Drawing.Point(11, 134);
            this.lcola.Name = "lcola";
            this.lcola.Size = new System.Drawing.Size(100, 19);
            this.lcola.TabIndex = 24;
            this.lcola.Text = "Tamaño Cola:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(6, 9);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(189, 19);
            this.label8.TabIndex = 22;
            this.label8.Text = "Agregar y eliminar registros";
            // 
            // pinicio
            // 
            this.pinicio.Controls.Add(this.label7);
            this.pinicio.Controls.Add(this.label6);
            this.pinicio.Controls.Add(this.label5);
            this.pinicio.Controls.Add(this.tbProductor);
            this.pinicio.Controls.Add(this.tbConsumidor);
            this.pinicio.Controls.Add(this.bInicializar);
            this.pinicio.Controls.Add(this.tbCola);
            this.pinicio.Location = new System.Drawing.Point(300, 71);
            this.pinicio.Name = "pinicio";
            this.pinicio.Size = new System.Drawing.Size(147, 171);
            this.pinicio.TabIndex = 25;
            this.pinicio.Paint += new System.Windows.Forms.PaintEventHandler(this.pinicio_Paint);
            // 
            // trefresh
            // 
            this.trefresh.Tick += new System.EventHandler(this.trefresh_Tick);
            // 
            // ProductorConsumidor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(705, 306);
            this.Controls.Add(this.pinicio);
            this.Controls.Add(this.ptablas);
            this.Controls.Add(this.menu);
            this.Font = new System.Drawing.Font("Calibri", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MainMenuStrip = this.menu;
            this.Name = "ProductorConsumidor";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Productor Consumidor";
            this.menu.ResumeLayout(false);
            this.menu.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvProductor)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvConsumidor)).EndInit();
            this.ptablas.ResumeLayout(false);
            this.ptablas.PerformLayout();
            this.pinicio.ResumeLayout(false);
            this.pinicio.PerformLayout();
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
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label lconsumidor;
        private System.Windows.Forms.TextBox tbCola;
        private System.Windows.Forms.TextBox tbConsumidor;
        private System.Windows.Forms.TextBox tbProductor;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button bInicializar;
        private System.Windows.Forms.Panel ptablas;
        public System.Windows.Forms.DataGridView dgvProductor;
        public System.Windows.Forms.DataGridView dgvConsumidor;
        private System.Windows.Forms.Panel pinicio;
        private System.Windows.Forms.DataGridViewTextBoxColumn Thread;
        private System.Windows.Forms.DataGridViewTextBoxColumn OD;
        private System.Windows.Forms.DataGridViewTextBoxColumn Status;
        private System.Windows.Forms.DataGridViewTextBoxColumn Registros;
        private System.Windows.Forms.Label lcola;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Timer trefresh;
        private System.Windows.Forms.Label lerroresDB;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn1;
        private System.Windows.Forms.DataGridViewTextBoxColumn dataGridViewTextBoxColumn2;
    }
}

