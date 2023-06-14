#include<iostream>
#include<mysql_driver.h>
#include<mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include<WinSock2.h>

#include<Windows.h>
#include<MSWSock.h>

//#define _WINSOCK_DEPRECATED_NO_WARNINGS
using namespace std;

#pragma comment(lib,"Ws2_32.lib")


bool connectSql()
{
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;


    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "Vision@2026");
    if (con->isValid())
    {
        cout << "Yes";
    }
    con->setSchema("quizapplication");
    stmt = con->createStatement();
    //res = stmt->executeQuery("create table hello(name varchar(20));");

    return true;
}



int main()
{
    connectSql();

    WSADATA wsa;
    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    int c, valread;
    char buffer[1024] = { 0 };
    char message[1024] = { 0 };

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        cout << "Failed. Error Code: " << WSAGetLastError() << endl;
        return 1;
    }

    // Create socket
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        cout << "Could not create socket: " << WSAGetLastError() << endl;
        return 1;
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    // Bind
    int iRes = 0;

    iRes=bind(s, (struct sockaddr*)&server, sizeof(server));

    

  

  /*  if (bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        std::cerr << "Bind failed with error code: " << WSAGetLastError() << std::endl;
        return 1;
    }*/


    // Listen to incoming connections
    listen(s, 3);

    // Accept incoming connections
    std::cout << "Waiting for incoming connections..." << std::endl;
    c = sizeof(struct sockaddr_in);
    if ((new_socket = accept(s, (struct sockaddr*)&client, &c)) == INVALID_SOCKET) {
        std::cerr << "Accept failed with error code: " << WSAGetLastError() << std::endl;
        return 1;
    }
    std::cout << "Connection accepted." << std::endl;

    // Receive data from client
    while (1) {

        valread = recv(new_socket, buffer, 1024, 0);
        if (valread > 0) {
            std::cout << "Client: " << buffer << std::endl;

            std::cout << "Server: ";

            std::cin.getline(message, 1024);
            cin.clear();

            send(new_socket, message, strlen(message), 0);

            if (strcmp(message, "exit") == 0) {
                std::cout << "Exiting..." << std::endl;
                break;
            }
        }
    }

    // Close socket and cleanup
    closesocket(s);
    WSACleanup();
    return 0;





}