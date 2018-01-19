#include <iostream>
#include <map>
#include <future>
#include <thread>
#include <fstream>
#include <string>
#include <mutex>
#include <chrono>
#include <vector>
#include <algorithm>
#include <condition_variable>
std::mutex m, m1, m2, m3;
std::condition_variable cv;
int main() {
    int a = 0, b = 0, count = 0;
    std::vector<std::future<int>> futures;
    std::vector<std::packaged_task<int()>> tasks;
    std::vector<std::thread> thread_pool;
    //int i = -1;
    for (int j = 0; j < 2; ++j) {
        thread_pool.emplace_back([&](){
            //m2.lock();
            //std::cout << "thread from pool #" << std::this_thread::get_id() << std::endl << std::flush;
            //m2.unlock();
            std::packaged_task<int()> task;
            while (tasks.size() > 0) {
                //++i;
                {
                    std::unique_lock<std::mutex> lock(m);
                    cv.wait(lock, [&](){return tasks.size() > 0;});
                    task = std::move(tasks.back());
                    tasks.pop_back();
                }
                task();
                m2.lock();
                std::cout << "counter" << std::endl;
                m2.unlock();
                //lock.unlock();
                //cv.notify_one();
            }
        });
    }
    std::thread printer([&](){
        //m2.lock();
        //std::cout << "printing thread #" << std::this_thread::get_id() << std::endl << std::flush;
        //m2.unlock();
        int j = -1;
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [&](){return futures.size() > 0;});
        while (j < (int) futures.size()) {
            ++j;
            if (j < (int) futures.size()) {
                m2.lock();
                std::cout << futures[j].get() << std::endl << std::flush;
                m2.unlock();
            }
        }
    });
    while (std::cin >> a >> b) {
        ++count;
        //m2.lock();
        //std::cout << "main thread reader #" << std::this_thread::get_id() << std::endl << std::flush;
        //m2.unlock();
        auto task = std::packaged_task<int()>([=](){return a + b;});
        {
            futures.emplace_back(tasks.back().get_future());
            {
                std::lock_guard<std::mutex> lock(m);
                tasks.emplace_back(std::move(task));
                cv.notify_all();
            }
        }
    }
    cv.notify_all();
    m2.lock();
    std::cout << "ready" << std::endl;
    std::cout << "sizeof tasks " << tasks.size() << std::endl;
    std::cout << "sizeof futures " << futures.size() << std::endl;
    m2.unlock();
    for (int j = 0; j < 2; ++j) {
        thread_pool[j].join();
    }
    printer.join();
}