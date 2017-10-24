#include "utility/concurrent_deque.hpp"
#include <thread>
#include <iostream>
#include <chrono>
#include<cstdio>

concurrent_deque<int> dueue(5);
void Produce()
{
    for (int i = 0; i < 15; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        dueue.push_back(i);
        printf("thread %d put(%d)\n", std::this_thread::get_id(), i);
    }
}

void Consume()
{
    int x = 0;

    for (int i = 0; i < 5; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        dueue.pop_front(x);
        printf("thread %d take(%d)\n", std::this_thread::get_id(), x);
    }
}

int main(void)
{
    std::thread producer(Produce);
    std::thread consumer1(Consume);
    std::thread consumer2(Consume);
    std::thread consumer3(Consume);
    producer.join();
    consumer1.join();
    consumer2.join();
    consumer3.join();
    
    return 0;
}