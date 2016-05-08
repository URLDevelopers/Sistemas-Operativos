using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace ProyectoFinal
{
    class Cola
    {
        
        public int Count;
        NodoCola Head, Tail;
        Mutex ex = new Mutex();

        public Cola()
        {
            this.Head = null;
            this.Tail = null;
            this.Count = 0;
        }

        public void Push(NodoCola nuevo)
        {
            if (this.Head == null)
            {
                this.Head = nuevo;
                this.Tail = nuevo;
            }
            else
            {
                this.Head.prev = nuevo;
                nuevo.next = this.Head;
                this.Head = nuevo;
            }
            Count++;
        }

        public NodoCola Pop()
        {
            ex.WaitOne();
            if (Count == 0)
            {
                return null;
            }
            if (this.Head == this.Tail)
            {
                NodoCola nodo = this.Tail;
                this.Head = null;
                this.Tail = null;
                this.Count--;
                return nodo;
            }
            else
            {
                NodoCola nodo = this.Tail;
                this.Tail = this.Tail.prev;
                this.Tail.next = null;
                this.Count--;
                return nodo;
            }
            
        }

    }



}
