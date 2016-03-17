using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Net.Sockets;

namespace Worker
{
    class Program
    {
        static void Main(string[] args)
        {
            /*
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
            */

            TcpListener serverSocket = new TcpListener(2439);
            int requestCount = 0;
            TcpClient clientSocket = default(TcpClient);
            serverSocket.Start();
            Console.WriteLine(" >> Server Started");
            clientSocket = serverSocket.AcceptTcpClient();
            Console.WriteLine(" >> Accept connection from client");
            requestCount = 0;
            while ((true))
            {
                try
                {
                    requestCount++;
                    NetworkStream networkStream = clientSocket.GetStream();
                    byte[] bytesFrom = new byte[65536];
                    
                    networkStream.Read(bytesFrom, 0, (int)clientSocket.ReceiveBufferSize); //aqui truena
                    string dataFromClient = System.Text.Encoding.ASCII.GetString(bytesFrom);
                    dataFromClient = dataFromClient.Substring(0, dataFromClient.IndexOf("$"));
                    Console.WriteLine(" >> Data from client - " + dataFromClient);
                    string serverResponse = "A creeper is behind you o.O";
                    Byte[] sendBytes = Encoding.ASCII.GetBytes(serverResponse);
                    networkStream.Write(sendBytes, 0, sendBytes.Length);
                    networkStream.Flush();
                    Console.WriteLine(" >> " + serverResponse);
                }
                catch (Exception ex)
                {
                    Console.WriteLine("tronitos");
                    break;
                }
            }
            clientSocket.Close();
            serverSocket.Stop();
            Console.WriteLine(" >> exit");
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
