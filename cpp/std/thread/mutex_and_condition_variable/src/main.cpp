#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex notif_m;
std::condition_variable cv;

bool ready = false;
std::string resource;

void notifier_thread() {
    std::cout << "[*] Notifier Thread: Started" << std::endl;
    std::lock_guard<std::mutex> ul(notif_m);

    // some job before trigger (5 sec)
    std::cout << "[*] Notifier Thread: Writing message..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    resource = "Hello World!";

    std::cout << "[*] Notifier Thread: Sending notification" << std::endl;
    ready = true;
    cv.notify_all();
}

void client_thread() {
    std::cout << "[-] Client Thread: Started" << std::endl;
    std::unique_lock<std::mutex> ul(notif_m);
    // wait until the notifier changes the switch from OFF to ON
    cv.wait(ul, []{ return ready; });

    std::cout << "[-] Client Thread: Notifier wrote the following message: " << resource << std::endl;
}

int main() {

    std::cout << "[+] Main" << std::endl;

    // Start threads
    std::thread t1(notifier_thread);
    std::thread t2(client_thread);

    // Wait for threads to finish
    t1.join();
    t2.join();

    return 0;
}
