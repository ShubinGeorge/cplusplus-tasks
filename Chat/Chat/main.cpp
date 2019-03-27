#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <future>
#include <winsock2.h>
#include <ws2tcpip.h>


#pragma comment(lib, "ws2_32.lib")


std::string EncodeString(const std::string& string_to_encode);
std::string DecodeString(const std::string& string_to_decode);

void InitWinSockLibrary();
SOCKET GetNewSocket();

void InitSocketForReading(SOCKET& socket_for_reading, const int my_port);
void RecieveAndPrintMessages(const int my_port, std::ostream& out_stream);

void InitSocketForWriting(
    SOCKET& socket_for_writing,
    const std::string& remote_ip_address, const int remote_port
);
void ReadAndSendMessages(
    std::istream& in_stream,
    const std::string& remote_ip_address, const int remote_port
);

int GetPort(std::istream& in_stream);
std::string GetIPAddress(std::istream& in_stream);

void ExitProgram(const int error_code);


std::string EncodeString(const std::string& string_to_encode)
{
    std::string encoded_string = string_to_encode;
    for (int i = 0; i < encoded_string.size(); i++)
    {
       encoded_string[i] += (i + 1);
    }
    return encoded_string;
}


std::string DecodeString(const std::string& string_to_decode)
{
    std::string decoded_string = string_to_decode;
    for (int i = 0; i < decoded_string.size(); i++)
    {
        decoded_string[i] -= (i + 1);
    }
    return decoded_string;
}


void InitWinSockLibrary()
{
    WSAData wsa_data = {};

    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
    {
        std::cerr << "*** Failed to initialise winsock library ***";
        std::cerr << std::endl;
        ExitProgram(1);
    }
}



SOCKET GetNewSocket()
{
    SOCKET new_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (new_socket == INVALID_SOCKET)
    {
        const int last_error_code = WSAGetLastError();
        std::cerr << "*** Could not create socket: " << last_error_code
                  << " ***" << std::endl;
        ExitProgram(last_error_code);
    }

    return new_socket;
}



void InitSocketForReading(SOCKET& socket_for_reading, const int my_port)
{
    assert(socket_for_reading);
    assert(my_port >= 1024);

    struct sockaddr_in socket_info = {};
    int socket_info_size = sizeof(socket_info);
    socket_info.sin_family = AF_INET;
    socket_info.sin_addr.s_addr = INADDR_ANY;
    socket_info.sin_port = htons(my_port);

    if (bind(socket_for_reading, (SOCKADDR*)&socket_info, socket_info_size) == SOCKET_ERROR)
    {
        const int last_error_code = WSAGetLastError();
        std::cerr << "*** bind failed with error code: " << last_error_code
                  << " ***" << std::endl;
        ExitProgram(last_error_code);
    }

    // Listening to incoming connections
    listen(socket_for_reading, SOMAXCONN);
    socket_for_reading = accept(socket_for_reading, (SOCKADDR*)&socket_info, &socket_info_size);
    if (socket_for_reading == INVALID_SOCKET)
    {
        const int last_error_code = WSAGetLastError();
        std::cerr << "*** accept failed with error code : " << last_error_code
                  << " ***" << std::endl;
        ExitProgram(last_error_code);
    }
}



void RecieveAndPrintMessages(const int my_port, std::ostream& out_stream)
{
    assert(my_port >= 1024);

    SOCKET socket_for_reading = GetNewSocket();
    InitSocketForReading(socket_for_reading, my_port);

    const int buf_size = 4096;
    char recieved_message_buf[buf_size] = {};
    for (;;)
    {
        const DWORD recieved_message_size = recv(
            socket_for_reading, recieved_message_buf, buf_size, 0
        );

        if (recieved_message_size == SOCKET_ERROR)
        {
            if (WSAGetLastError() == WSAECONNABORTED)
            {
                out_stream << "*** Connection aborted ***" << std::endl;
            }
            else
            {
                std::cerr << "*** recv failed: " << WSAGetLastError()
                          << " ***" << std::endl;
            }
            break;
        }

        std::string message;
        for (int i = 0; i < recieved_message_size; i++)
        {
            message.push_back(recieved_message_buf[i]);
        }

        out_stream << "Remote person: ";
        out_stream << DecodeString(message);
        out_stream << std::endl;

    }

    if (WSAGetLastError() == WSAECONNRESET)
    {
        out_stream << "*** remote disconnected ***" << std::endl;
    }

    closesocket(socket_for_reading);
}



void InitSocketForWriting(
    SOCKET& socket_for_writing,
    const std::string& remote_ip_address, const int remote_port)
{
    assert(socket_for_writing);
    assert(remote_port >= 1024);

    struct sockaddr_in remote_info = {};
    //remote_info.sin_addr.s_addr = inet_addr(remote_ip_address.c_str());
    inet_pton(AF_INET, remote_ip_address.c_str(), &(remote_info.sin_addr));
    remote_info.sin_family = AF_INET;
    remote_info.sin_port = htons(remote_port);

    while (connect(socket_for_writing, (SOCKADDR*)&remote_info, sizeof(remote_info)) < 0)
    {
        Sleep(100);  // sleep for 100ms
    }
}



void ReadAndSendMessages(
    std::istream& in_stream,
    const std::string& remote_ip_address, const int remote_port)
{
    assert(remote_port >= 1024);

    SOCKET socket_for_writing = GetNewSocket();

    // Connect to a person which you would like to speak with
    std::cerr << "*** Connecting to " << remote_ip_address.c_str()
              << ":" << remote_port << " ... ***" << std::endl;
    InitSocketForWriting(socket_for_writing, remote_ip_address, remote_port);
    std::cerr << "*** Connection established ***\n";
    std::cerr << "******************************\n" << std::endl;

    // Reading messages for sending and send them
    for (std::string line;;)
    {
        std::getline(in_stream, line);
        const int line_size = (int)line.size();
        const int max_line_size = 100;
        if (line_size > max_line_size || line_size < 0)
        {
            std::cerr << "*** Too long message. Try again. ***" << std::endl;
        }

        else if (send(socket_for_writing, EncodeString(line).c_str(), line_size, 0) < 0)
        {
            std::cerr << "*** send failed: " << WSAGetLastError()
                      << " ***" << std::endl;
            break;
        }
    }

    closesocket(socket_for_writing);
}



int GetPort(std::istream& in_stream)
{
    const int min_port = 1024;
    const int max_port = 65535;

    int port = 0;
    in_stream >> port;

    if (in_stream.fail() || port < min_port || port > max_port)
    {
        std::cerr << "*** Failed to read a port number. "
                  << "You should input a number between "
                  << min_port << " and " << max_port
                  << ".***" << std::endl;
        ExitProgram(1);
    }

    return port;
}



std::string GetIPAddress(std::istream& in_stream)
{
    std::string ip_address;
    in_stream >> ip_address;

    if (in_stream.fail())
    {
        std::cerr << "*** Could not read IP-address. ***" << std::endl;
        ExitProgram(1);
    }

    struct sockaddr_in sa = {};
    if (inet_pton(AF_INET, ip_address.c_str(), &(sa.sin_addr)) == 0)
    {
        std::cerr << "*** Format of IP-address is invalid. ***" << std::endl;
        ExitProgram(1);
    }
    
    return ip_address;
}



void ExitProgram(const int error_code)
{
    std::cerr << "*** Exiting program with status code = " << error_code
              << " ***" << std::endl;
    WSACleanup();
    ExitProcess(error_code);
}



int main()
{
    // Initialise winsock library
    InitWinSockLibrary();

    // Get port number for incoming messages
    std::cout << "Type your port number: ";
    const int my_port = GetPort(std::cin);

    // Run asynchronous recieving messages
    std::future<void> reciever_future = std::async(
        std::launch::async,
        RecieveAndPrintMessages, my_port, std::ref(std::cout)
    );

    // Get IP-address and port number of a remote person
    std::cout << "Type IP-address which you would like to connect to: ";
    std::string remote_ip_address = GetIPAddress(std::cin);
    std::cout << "Type port number which you would like to connect to: ";
    const int remote_port = GetPort(std::cin);

    ReadAndSendMessages(std::cin, remote_ip_address, remote_port);
    //reciever_future.get();

    std::cout << "*** Shutting down ... ***" << std::endl;
    WSACleanup();
    return 0;
}
