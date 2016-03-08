using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace Worker
{
    class Program
    {
        static void Main(string[] args)
        {
            Worker workerobject = new Worker();
            Thread workerThread = new Thread(workerobject.DoWork);

            workerThread.Start();
            Console.WriteLine("main thread: Starting worker thread...");
            while (!workerThread.IsAlive) ;

            Thread.Sleep(1000);
            workerobject.RequestStop();
            workerThread.Join();
            Console.WriteLine("main thread: Worker thread has terminated.");
            Console.ReadLine();
        }
    }

    public class Worker
    {
        private volatile bool _shouldStop;
        public void DoWork()
        {
            while(!_shouldStop)
            {
                Console.WriteLine("worker thread: working...");
            }
            Console.WriteLine("worker thread: terminating gracefully");
        }
        public void RequestStop()
        {
            _shouldStop = true;
        }
    }

}
