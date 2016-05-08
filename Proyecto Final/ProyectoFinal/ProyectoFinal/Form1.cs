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
using Amib.Threading;

namespace ProyectoFinal
{
    public partial class ProductorConsumidor : Form
    {

        public ProductorConsumidor()
        {
            InitializeComponent();
        }

        #region Variables Globales
        //Estados del thread
        const string libre = "Libre";
        const string dormido = "Dormido";
        const string activo = "Procesando";

        //Longitudes de la cola, pool de productores y consumidores
        int cola_long, cola_long_actual, long_prod, long_con;

        //Contador de los errores dados por la base de datos
        int erroresDB = 0;

        //Pool de productores y consumidores
        SmartThreadPool PoolProductores, PoolConsumidores;

        //Banderas de estado sobre producir o consumir
        public bool Produccion, Consumir;

        //Cola
        Queue<NodoCola> FIFO = new Queue<NodoCola>();
        //Cola Stack = new Cola();

        //Exclusión mutua para regiones críticas
        Mutex cerradura = new Mutex();

        #endregion

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Desarrollado por: \n \"Francisco Manjón 1054113 \n Juan Pablo Velásquez 1067813 \n Ana Gloria Ortega1041613 \n Kevynn Villatoro 1011712 \n Julio Mejía 1026111.\"");
        }

        #region Metodos de la base de datos
        /*
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
        }*/
        #endregion

        #region Validacion de textbox de entrada
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

        #endregion

        #region Botones
        private void bInicializar_Click(object sender, EventArgs e)
        {
            if (!String.IsNullOrWhiteSpace(tbCola.Text) && !String.IsNullOrWhiteSpace(tbProductor.Text) && !String.IsNullOrWhiteSpace(tbConsumidor.Text))
            {
                if (SetConnection())
                {
                    long_prod = int.Parse(tbProductor.Text);
                    long_con = int.Parse(tbConsumidor.Text);
                    cola_long = int.Parse(tbCola.Text);
                    cola_long_actual = 0;
                    Produccion = true;
                    Consumir = false;
                    //Inicializan los threadpool          tiempoinactivo, max threads
                    PoolConsumidores = new SmartThreadPool(1, long_con);
                    PoolProductores = new SmartThreadPool(1, long_prod);
                    for (int i = 0; i < long_con; i++)
                    {
                        dgvConsumidor.Rows.Add(i.ToString(), dormido);
                        PoolConsumidores.QueueWorkItem(Consumo);
                    }
                    for (int i = 0; i < long_prod; i++)
                    {
                        dgvProductor.Rows.Add(i.ToString(), "", libre, "");
                    }
                    //Timer de actualizacion en pantalla
                    trefresh.Start();
                    pinicio.Visible = false;
                    ptablas.Visible = true;
                }
                else
                {
                    MessageBox.Show("No hay conexión a la base de datos.");
                }
            }
            else
            {
                MessageBox.Show("Complete todos los campos para poder continuar.");
            }
        }

        private void bAgregarRegistros_Click(object sender, EventArgs e)
        {
            if (!String.IsNullOrWhiteSpace(tbcantidad.Text) && !String.IsNullOrWhiteSpace(tborigen.Text) && !String.IsNullOrWhiteSpace(tbdestino.Text))
            {
                int reg = int.Parse(tbcantidad.Text);
                if (reg > 0)
                {
                    //Prepara el query de ejecucion en un consumidor
                    string query = query = @"insert into lista_transaccion (origen,destino) values ('" + tborigen.Text + "', '" + tbdestino.Text + "')";
                    NodoCola nuevo = new NodoCola(query, reg, tborigen.Text, tbdestino.Text);
                    PoolProductores.QueueWorkItem(Producir, nuevo);
                }
            }
        }

        private void bBorrarRegistros_Click(object sender, EventArgs e)
        {
            if (!String.IsNullOrWhiteSpace(tborigen.Text) && !String.IsNullOrWhiteSpace(tbdestino.Text) && !String.IsNullOrWhiteSpace(tbcantidad.Text))
            {
                string query = @"delete from lista_transaccion where origen = '" + tborigen.Text + "' and destino = '" + tbdestino.Text + "' order by id desc limit 1";
                int reg = int.Parse(tbcantidad.Text);
                if (reg > 0)
                {
                    NodoCola nuevo = new NodoCola(query, reg, tborigen.Text, tbdestino.Text);
                    PoolProductores.QueueWorkItem(Producir, nuevo);
                }
            }
        }
        #endregion

        #region Metodos
        public void Producir(NodoCola nuevo)
        {
            for (int i = 0; i < nuevo.reg; i++)
            {
                nuevo.estado = dormido;
                while (!Produccion) {  }
                cerradura.WaitOne();
                try
                {
                    nuevo.estado = activo;
                    FIFO.Enqueue(nuevo);//insertar en la cola
                    cola_long_actual++;
                    nuevo.ite++;
                    if (cola_long_actual >= cola_long)
                    {
                        Produccion = false;
                        Consumir = true;
                    }
                }
                finally
                {
                    cerradura.ReleaseMutex();
                    System.Threading.Thread.Sleep(10);
                }
            }
        }

        public void Consumo()
        {
            while (!Consumir) { System.Threading.Thread.Sleep(50);/*liberar presion a la form */}
            NodoCola item = null;
            cerradura.WaitOne();
            try
            {
                item = FIFO.Dequeue(); //sacar de la cola
                cola_long_actual--;
                if (cola_long_actual == 0)
                {
                    Consumir = false;
                    Produccion = true;
                }
            }
            finally
            { 
                cerradura.ReleaseMutex();
                cerradura.WaitOne();
                EjectutarQuery(item);
                PoolConsumidores.QueueWorkItem(Consumo); //se vuelve a crear el consumidor
                cerradura.ReleaseMutex();
                System.Threading.Thread.Sleep(30000);
            }
        }

        private void pinicio_Paint(object sender, PaintEventArgs e)
        {

        }

        #endregion

        #region Base de Datos

        MySqlConnection connection = null;

        //Establecer conexion con la base de datos
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

        //Ejectuar query sobre la base de datos
        public void EjectutarQuery(NodoCola query)
        {
            try
            {
                if (SetConnection())
                {
                    //Se da conexión a la base de datos
                    MySqlCommand command = new MySqlCommand(query.sql, connection);
                    command.ExecuteNonQuery();
                    connection.Close();
                }
            }
            catch (Exception ex)
            {
                connection.Close();
                erroresDB++;
            }
        }



        #endregion

        #region Actualizacion de pantalla

        public void ActualizarPantalla()
        {
            //Actualiza errores de la base de datos y el tamaño de cola
            lerroresDB.Text = "Errores DB: " + erroresDB.ToString();
            lcola.Text = "Tamaño cola: " + cola_long_actual.ToString();

            //Actualizar productores
            var productores = PoolProductores.ObtenerThreads();
            for (int i = 0; i < productores.Count; i++)
            {
                dgvProductor.Rows[i].SetValues(i.ToString(), productores[i].origen + ", " + productores[i].destino, productores[i].estado, productores[i].ite + " de " + productores[i].reg);
            }
            //ZzzzzZZZzzzz...
            for (int i = productores.Count; i < long_prod; i++)
            {
                dgvProductor.Rows[i].SetValues(i.ToString(), "", libre, "");
            }
            //Actualizar consumidores
            string estado = "";
            if (Consumir)
            {
                estado = activo;
            }
            else
            {
                estado = dormido;
            }
            //Consumidores activos
            for (int i = 0; i < PoolConsumidores.ActiveThreads; i++)
            {
                dgvConsumidor.Rows[i].SetValues(i.ToString(), estado);
            }
            //Zzz....
            for (int i = PoolConsumidores.ActiveThreads; i < long_con; i++)
            {
                dgvConsumidor.Rows[i].SetValues(i.ToString(), dormido);
            }
        }

        private void trefresh_Tick(object sender, EventArgs e)
        {
            ActualizarPantalla();
        }
        #endregion


    }
    public class NodoCola
    {
        public string estado;
        public int reg, ite;
        public string sql;
        public string origen, destino;
        public NodoCola next, prev;
        public NodoCola(string sql, int reg, string o, string d)
        {
            this.sql = sql;
            this.reg = reg;
            this.ite = 0;
            this.origen = o;
            this.destino = d;
            this.next = this.prev = null;
        }
    }


}
