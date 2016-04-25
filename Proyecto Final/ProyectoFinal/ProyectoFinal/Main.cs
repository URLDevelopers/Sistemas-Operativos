using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProyectoFinal
{
    class Main
    {

        public int Long_Productor, Long_Consumidor, Long_Cola;
        public static List<Hilo> Productor = new List<Hilo>(), Consumidor = new List<Hilo>();

        const string libre = "Libre";
        const string dormido = "Dormido";
        const string activo = "Procesando";
        const string nuevo = "Nuevo";

        public Main(int prod, int con, int cola)
        {
            this.Long_Productor = prod;
            this.Long_Consumidor = con;
            this.Long_Cola = cola;
        }


        public int NuevoRegistro(int reg, string origen, string destino)
        {
            while(true)
            {
                for (int i = 0; i < Long_Productor; i++)
                {
                    if (Productor[i].status == libre)
                    {
                        Productor[i].status = nuevo;
                        Productor[i].reg = reg;
                        Productor[i].origen = origen;
                        Productor[i].destino = destino;
                        return 1;
                    }
                }
            }
        }

    }

    class Hilo
    {
        public int reg;
        public string status;
        public int id;
        public string origen, destino;
        
        public Hilo()
        {
            this.reg = this.id = 0;
            this.status = "";
            this.origen = "";
            this.destino = "";
        }
    }

    class Worker
    {

    }

}
