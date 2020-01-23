// Необходимые зависимости
using System;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace test_eth
{
    class Program
    {
        // Порт и ip-адрес сервера
        const int port = 8005;
        const string ip = "172.18.159.30";

        static void Main(string[] args)
        {
            // Адрес для запуска сокета
            IPEndPoint ipPoint = new IPEndPoint(IPAddress.Parse(ip), port);

            // Создание сокета
            Socket listenSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                // Связывание сокета с точкой приема данных
                listenSocket.Bind(ipPoint);

                // Начало ожидания сообщений с установкой максимального количества одновременных подключений
                listenSocket.Listen(10);

                Console.WriteLine("Сервер запущен. Ожидание подключений...");

                while (true)
                {
                    Socket handler = listenSocket.Accept();
                    // Для полученного сообщения
                    StringBuilder builder = new StringBuilder();
                    int bytes = 0; // Для хранения количества полученных байтов
                    byte[] data = new byte[256]; // Буфер для приема данных

                    do
                    {
                        // Чтение данных с учетом кодировки клиента (ASCII у Arduino)
                        bytes = handler.Receive(data);
                        builder.Append(Encoding.ASCII.GetString(data, 0, bytes));
                    }
                    while (handler.Available > 0);
                    // Вывод полученных данных
                    Console.WriteLine(DateTime.Now.ToShortTimeString() + ": " + builder.ToString());

                    // Отправка ответа
                    string message = "Hi from server";
                    data = Encoding.ASCII.GetBytes(message);
                    handler.Send(data);

                    // Закрытие сокета
                    handler.Shutdown(SocketShutdown.Both);
                    handler.Close();
                }
            }
            catch (Exception ex)
            {
                // В случае ошибки вывод информации о ней
                Console.WriteLine(ex.Message);
            }
        }
    }
}
