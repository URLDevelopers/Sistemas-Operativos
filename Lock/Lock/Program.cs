using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace Lock
{
    class Program
    {
        static void Main(string[] args)
        {
            for (int i = 0; i < 10; i++)
            {
                lista.Add(i);
            }

            Thread t1 = new Thread(() => Program.Metodo(1));
            Thread t2 = new Thread(() => Program.Metodo(2));
            Thread t3 = new Thread(() => Program.Metodo(3));
            t1.Start();
            t2.Start();
            t3.Start();
            while(true)
            {

            }
        }


        static List<int> lista = new List<int>();
        
        public static void Metodo(int x)
        {
            while (true)
            {
                lock (lista)
                {
                    if (lista.Count > 0)
                    {
                        Console.WriteLine(x.ToString() + ". " + lista.First());
                        lista.RemoveAt(0);
                    }
                    else
                    {
                        break;
                    }
                }
                Thread.Sleep(1000);
            }
            Console.WriteLine("thread" + x.ToString() + "finish");
        }

    }
}
