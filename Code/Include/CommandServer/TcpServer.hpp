namespace cmdserv {
    class TcpServer {
        public:
            TcpServer();
            ~TcpServer();
            int Listen();
            void EchoTest(int clientSocket);

        private:
            int listeningSocket;
    };
}