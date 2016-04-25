using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data.Entity;
using MySql.Data.MySqlClient;
using System.Threading;

namespace ProyectoFinal
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }


        #region Variables Globales
        MySqlConnection connection = null;
        Main SO = null;
        
        #endregion

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Desarrollado por: \n \"Los majes y anita.\"");
        }


        #region Metodos de la base de datos
        public bool SetConnection()
        {
            string server = "localhost";
            string database = "esquema_so";
            string uid = "root";
            string password = "";
            string connectionString;
            connectionString = "SERVER=" + server + ";" + "DATABASE=" +
            database + ";" + "UID=" + uid + ";" + "PASSWORD=" + password + ";";
            connection = new MySqlConnection(connectionString);
            try
            {
                connection.Open();
                return true;
            }
            catch (MySqlException ex)
            {
                return false;
            }
        }
        public bool insert(string origen, string destino)
        {
            try
            {
                if (SetConnection())
                {
                    string query = @"insert into lista_transaccion (id,origen,destino) values (null,'" + origen + "', '" + destino + "')";
                    MySqlCommand MyCommand2 = new MySqlCommand(query, connection);
                    MySqlDataReader MyReader2;
                    MyReader2 = MyCommand2.ExecuteReader();
                    connection.Close();
                    return true;
                }
                else
                {
                    return false;
                }
            }
            catch (Exception ex)
            {
                connection.Close();
                return false;
            }

        }
        public bool delete(int param)
        {
            try
            {
                if (SetConnection())
                {
                    string query = @"delete from lista_transaccion where id = " + param;
                    MySqlCommand MyCommand2 = new MySqlCommand(query, connection);
                    MySqlDataReader MyReader2;
                    MyReader2 = MyCommand2.ExecuteReader();
                    connection.Close();
                    return true;
                }
                else
                {
                    return false;
                }
            }
            catch (Exception ex)
            {
                connection.Close();
                return false;
            }
        }
        #endregion

        private void tborigen_KeyPress(object sender, KeyPressEventArgs e)
        {
            
        }

        private void tbProductor_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (Char.IsDigit(e.KeyChar))
            {
                e.Handled = false;
            }
            else
            {
                if (Char.IsControl(e.KeyChar))
                {
                    e.Handled = false;
                }
                else
                {
                    e.Handled = true;
                }
            }
        }

        private void tbConsumidor_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (Char.IsDigit(e.KeyChar))
            {
                e.Handled = false;
            }
            else
            {
                if (Char.IsControl(e.KeyChar))
                {
                    e.Handled = false;
                }
                else
                {
                    e.Handled = true;
                }
            }
        }

        private void tbCola_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (Char.IsDigit(e.KeyChar))
            {
                e.Handled = false;
            }
            else
            {
                if (Char.IsControl(e.KeyChar))
                {
                    e.Handled = false;
                }
                else
                {
                    e.Handled = true;
                }
            }
        }

        private void tbcantidad_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (Char.IsDigit(e.KeyChar))
            {
                e.Handled = false;
            }
            else
            {
                if (Char.IsControl(e.KeyChar))
                {
                    e.Handled = false;
                }
                else
                {
                    e.Handled = true;
                }
            }
        }

        private void bAgregarRegistros_Click(object sender, EventArgs e)
        {
            if (!String.IsNullOrWhiteSpace(tbcantidad.Text) && !String.IsNullOrWhiteSpace(tborigen.Text) && !String.IsNullOrWhiteSpace(tbdestino.Text))
            {
                lrespuesta.Visible = false;
                int reg = int.Parse(tbcantidad.Text);
                Thread nuevo = new Thread(() => SO.NuevoRegistro(reg,tborigen.Text, tbdestino.Text));
                nuevo.Start();
            }
            else
            {
                lrespuesta.Visible = true;
                lrespuesta.Text = "No se ha agregado";
            }
        }


        #region Botones
        private void bInicializar_Click(object sender, EventArgs e)
        {
            if (!String.IsNullOrWhiteSpace(tbCola.Text) && !String.IsNullOrWhiteSpace(tbProductor.Text) && !String.IsNullOrWhiteSpace(tbConsumidor.Text))
            {
                int prod = int.Parse(tbProductor.Text);
                int con = int.Parse(tbConsumidor.Text);
                int cola = int.Parse(tbCola.Text);
                SO = new Main(prod, con, cola);
                dgvConsumidor.Rows.Add(con);
                dgvProductor.Rows.Add(prod);
                for (int i = 0; i < prod; i++)
                {
                    Main.Productor.Add(new Hilo());
                }
                for (int i = 0; i < con; i++)
                {
                    Main.Consumidor.Add(new Hilo());
                }
            }
            else
            {
                MessageBox.Show("Complete todos los campos para poder continuar.");
            }
        }
        #endregion



    }
}
