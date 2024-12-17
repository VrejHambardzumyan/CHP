#include "UDPSocket.h"
#include <iostream>
#include <cstring>
#include <thread>               // Add this for std::thread
#include <mutex>                // Add this for std::mutex and std::lock_guard
#include <condition_variable>   // Add this for std::condition_variable
#include <atomic>               // Add this for std::atomic
#include <chrono>               // Add this for std::chrono

using namespace std;

class ThreadSafeUDPClient {
private:
    UDPSocket client_sock;
    struct sockaddr_in si_other;
    int slen;
    
    // Synchronization primitives
    mutex mtx;
    condition_variable cv;
    atomic<bool> response_received{false};
    
    char buf[BUFLEN];
    
    // Receiving thread function
    void receive_thread() {
        while (true) {
            memset(buf, '\0', BUFLEN);
            
            // Receive datagram
            client_sock.RecvDatagram(buf, BUFLEN, (struct sockaddr*)&si_other, &slen);
            
            // Lock and notify that response is received
            {
                lock_guard<mutex> lock(mtx);
                response_received = true;
            }
            
            // Notify waiting thread
            cv.notify_one();
            
            // Print server reply
            cout << "\nServer reply: " << buf << endl;
        }
    }

public:
    ThreadSafeUDPClient(const char* srv_ip = SERVER, unsigned short srv_port = PORT) {
        // Initialize socket address
        memset((char*)&si_other, 0, sizeof(si_other));
        si_other.sin_family = AF_INET;
        si_other.sin_port = htons(srv_port);
        si_other.sin_addr.S_un.S_addr = inet_addr(srv_ip);
        slen = sizeof(si_other);

        cout << "Server addr=" << srv_ip << " port=" << srv_port << endl;
    }

    void start() {
        // Start receive thread
        thread receive_th(&ThreadSafeUDPClient::receive_thread, this);
        receive_th.detach();

        // Main sending loop
        char message[BUFLEN];
        while (true) {
            // Get user input
            cout << "\nEnter message: ";
            cin.getline(message, BUFLEN);

            // Reset response flag
            response_received = false;

            // Send datagram
            client_sock.SendDatagram(message, strlen(message), 
                                     (struct sockaddr*)&si_other, slen);

            // Wait for response with timeout
            {
                unique_lock<mutex> lock(mtx);
                if (!cv.wait_for(lock, chrono::seconds(5), 
                    [this]{ return response_received.load(); })) {
                    // Timeout occurred
                    cerr << "No response received within 5 seconds." << endl;
                }
            }
        }
    }

    // Optional: Command-line argument constructor
    static void run_with_args(int argc, char* argv[]) {
        if (argc == 1) {
            // Default server
            ThreadSafeUDPClient client;
            client.start();
        } else if (argc == 2) {
            // Custom port
            ThreadSafeUDPClient client(SERVER, atoi(argv[1]));
            client.start();
        } else {
            // Custom IP and port
            ThreadSafeUDPClient client(argv[1], atoi(argv[2]));
            client.start();
        }
    }
};

int main(int argc, char* argv[]) {
    ThreadSafeUDPClient::run_with_args(argc, argv);

}
