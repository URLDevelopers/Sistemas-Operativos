using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SO_1
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Ingrese un numero: ");
            int k = 0;
            Int32.TryParse(Console.ReadLine(), out k);

            obj1Class[] arr1 = new obj1Class[k];
            obj2Struct[] arr2 = new obj2Struct[k];

            for (int i = 0; i < arr1.Length; i++)
            {
                arr1[i] = new obj1Class();
            }

            Console.ReadLine();
        }
    }

    struct obj2Struct
    {
        int b;
    }

    class obj1Class
    {
        int a;
    }
}
