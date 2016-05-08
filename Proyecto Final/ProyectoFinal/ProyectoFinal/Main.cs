using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using MySql.Data.MySqlClient;
using System.Windows.Forms;
using Amib.Threading;

namespace ProyectoFinal
{
    class Main
    {
        /*MySqlConnection connection = null;
        public int Long_Productor, Long_Consumidor, Long_Cola, long_prod_ac, long_con_ac, long_col_ac;
        
        const string libre = "Libre";
        const string dormido = "Dormido";
        const string activo = "Procesando";

        public static Nodo HeadProductor, HeadConsumidor, TailProductor, TailConsumidor;
        public NodoCola Head, Tail;

        public static bool Produccion, Consumir;

        public static List<Nodo> ListProductor = new List<Nodo>(), ListConsumidor = new List<Nodo>();

        bool SemfBinCol = false;
        bool SemfBinProd = false;
        bool SemfBinCon = false;

        public Main(int prod, int con, int cola)
        {
            this.Long_Productor = prod;
            this.Long_Consumidor = con;
            this.Long_Cola = cola;
            HeadConsumidor = null;
            HeadProductor = null;
            TailConsumidor = null;
            TailProductor = null;
            this.long_col_ac = 0;
            this.long_con_ac = 0;
            this.long_prod_ac = 0;
            Produccion = false;
            Consumir = false;
        }

        public bool NuevoProductor(int reg, string origen, string destino, int tipo)
        {
            string query = "";
            if (tipo == 0)
            {
                query = @"insert into lista_transaccion (origen,destino) values ('" + origen + "', '" + destino + "')";
            }
            else
            {
                query = @"delete from lista_transaccion where origen = " + origen + " and destino = " + destino;
            }
            NodoCola par = new NodoCola(query);
            while (true)
            {
                Nodo iterador = HeadProductor;
                while (iterador != null)
                {
                    if (iterador.metodo == null)
                    {
                        if (tipo == 0) //Productor
                        {
                            iterador.metodo = new Thread(() => InsertCola(reg, query, iterador.id));
                            ModifiyProductor(iterador.id, 0, "Thread " + iterador.id.ToString() + " (" + origen + "-" + destino + ")");
                            ModifiyProductor(iterador.id, 1, dormido);
                            ModifiyProductor(iterador.id, 2, "0 de " + reg.ToString());
                            while (!Produccion) { }
                            ModifiyProductor(iterador.id, 1, activo);
                            iterador.metodo.Start();
                        }
                        else //Consumidor
                        {
                            iterador.metodo = new Thread(() => InsertCola(1, query, iterador.id));
                            ModifyConsumidor(iterador.id, 0, "Thread " + iterador.id.ToString() + " (" + origen + "-" + destino + ")");
                            ModifyConsumidor(iterador.id, 1, dormido);
                        }
                        return true;
                    }
                    iterador = iterador.next;
                }
                return false;
            }
        }

        /*public bool InsertCola(int reg, string query, int id)
        {
            int i = 0;
            NodoCola nuevo;
            while (i < reg)
            {
                if (long_col_ac < Long_Cola)
                {
                    nuevo = new NodoCola(query);
                    while (SemfBinProd) { }
                    SemfBinProd = true;
                    if (Head == null)
                    {
                        Head = nuevo;
                        Tail = nuevo;
                    }
                    else
                    {
                        nuevo.next = Head;
                        Head.prev = nuevo;
                        Head = nuevo;
                    }
                    long_col_ac++;
                    ModifiyProductor(id, 2, (i + 1).ToString() + " de " + reg.ToString());
                    i++;
                    SemfBinProd = false;
                }
            }
            return true;
        }

        public void VerificarProductores()
        {
            while (true)
            {
                while (!Produccion) { }
                Nodo iterador = HeadProductor;
                while (iterador.next != null)
                {
                    if (iterador.metodo != null)
                    {
                        if (iterador.metodo.ThreadState == ThreadState.Stopped)
                        {
                            iterador.metodo = null;
                            ModifiyProductor(iterador.id, 0, "Thread " + iterador.id.ToString());
                            ModifiyProductor(iterador.id, 1, libre);
                            ModifiyProductor(iterador.id, 2, "");
                        }
                    }
                    iterador = iterador.next;
                }
            }
        }

        public void EjecutarConsumidores()
        {
            Thread SacarColaT = null;
            Thread VerificarC = null;
            while (true)
            {
                if (SacarColaT == null && VerificarC == null)
                {
                    SacarColaT = new Thread(() => ObtenerNodoCola());
                    VerificarC = new Thread(() => VerificarConsumidores());
                }
                while (!Consumir)
                {
                    if (SacarColaT.ThreadState == ThreadState.Running)
                    {
                        SacarColaT.Suspend();
                        VerificarC.Suspend();
                    }
                }
                if (SacarColaT.ThreadState == ThreadState.Unstarted)
                {
                    SacarColaT.Start();
                    VerificarC.Start();
                }
                if (SacarColaT.ThreadState == ThreadState.Suspended)
                {
                    SacarColaT.Resume();
                    VerificarC.Resume();
                }
            }
            //Ejecutar consumiores
        }

        public void VerificarConsumidores()
        {
            while (true)
            {
                while (!Consumir) { }
                Nodo iterador = HeadConsumidor;
                while (iterador.next != null)
                {
                    if (iterador.metodo != null)
                    {
                        if (iterador.metodo.ThreadState == ThreadState.Stopped)
                        {
                            iterador.metodo = null;
                            ModifyConsumidor(iterador.id, 1, libre);
                        }
                    }
                    iterador = iterador.next;
                }
            }
        }

        public void ObtenerNodoCola()
        {
            while (true)
            {
                //Sacar de la cola
                while (SemfBinCol) { }
                SemfBinCol = true;
                NodoCola sacar = Tail;
                if (Tail == Head)
                {
                    Tail = Head = null;
                }
                else
                {
                    Tail = Tail.prev;
                    Tail.next = null;
                }
                SemfBinCol = false;
                if (sacar != null)
                {
                    while (SemfBinCon) { }
                    SemfBinCon = true;
                    Nodo iterador = HeadConsumidor;
                    while (iterador != null)
                    {
                        if (iterador.metodo == null)
                        {
                            iterador.metodo = new Thread(() => EjectutarQuery(sacar.sql));
                            iterador.metodo.Start();
                        }
                    }
                    SemfBinCon = false;
                }

            }
        }

        public bool EjectutarQuery(string query)
        {
            try
            {
                if (SetConnection())
                {
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

        public void DormirProductores()
        {
            while (SemfBinProd) { }
            SemfBinProd = true;
            Nodo iterador = HeadProductor;
            while (iterador.next != null)
            {
                if (iterador.metodo != null)
                {
                    if (iterador.metodo.IsAlive)
                    {
                        iterador.metodo.Suspend();
                        ModifiyProductor(iterador.id, 1, dormido);
                    }
                }
                iterador = iterador.next;
            }
            SemfBinProd = false;
        }

        delegate void DataTable(int r, int c, string v);

        public void ModifiyProductor(int r, int c, string v)
        {
            Form1.formulario.dgvProductor.BeginInvoke(new DataTable(CambioProductor), r, c, v);
        }

        public void ModifyConsumidor(int r, int c, string v)
        {
            Form1.formulario.dgvConsumidor.BeginInvoke(new DataTable(CambioConsumidor), r, c, v);
        }

        public void CambioProductor(int r, int c, string v)
        {
            Form1.formulario.dgvProductor.Rows[r].Cells[c].Value = v;
        }

        public void CambioConsumidor(int r, int c, string v)
        {
            Form1.formulario.dgvConsumidor.Rows[r].Cells[c].Value = v;
        }

        public void DespertarProductores()
        {
            while (SemfBinProd) { }
            SemfBinProd = true;
            Nodo iterador = HeadProductor;
            while (iterador.next != null)
            {
                if (iterador.metodo != null)
                {
                    if (iterador.metodo.ThreadState == ThreadState.Suspended)
                    {
                        iterador.metodo.Resume();
                        ModifiyProductor(iterador.id, 1, activo);
                    }
                }
                iterador = iterador.next;
            }
            SemfBinProd = false;
        }

        public void DormirConsumidores()
        {
            while (SemfBinCon) { }
            SemfBinCon = true;
            Nodo iterador = HeadConsumidor;
            while (iterador.next != null)
            {
                if (iterador.metodo != null)
                {
                    if (iterador.metodo.IsAlive)
                    {
                        iterador.metodo.Suspend();
                        ModifyConsumidor(iterador.id, 1, dormido);
                    }
                }
                iterador = iterador.next;
            }
            SemfBinCon = false;
        }

        public void DespertarConsumidores()
        {
            while (SemfBinCon) { }
            SemfBinCon = true;
            Nodo iterador = HeadConsumidor;
            while (iterador.next != null)
            {
                if (iterador.metodo != null)
                {
                    if (iterador.metodo.ThreadState == ThreadState.Suspended)
                    {
                        iterador.metodo.Resume();
                        ModifyConsumidor(iterador.id, 1, activo);
                    }
                }
                iterador = iterador.next;
            }
            SemfBinCon = false;
        }

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

        Mutex cerradura = new Mutex();
        Queue<int> x = new Queue<int>();
        */


    }
}


    class Nodo
    {
        public Nodo next, prev;
        public int id;
        public Thread metodo;
        public Nodo(int id)
        {
            this.next = null;
            this.prev = null;
            this.id = id;
            this.metodo = null;
        }
    }


    


