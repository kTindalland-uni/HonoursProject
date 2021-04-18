namespace cmdserv {
    class TcpServer {
        public:
            TcpServer();
            ~TcpServer();
            int Listen();

        private:
            int listeningSocket;
    };
}