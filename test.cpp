#include "utility/concurrent_deque.hpp"
#include <thread>
#include <iostream>
#include <chrono>
#include<cstdio>
#include<random>

concurrent_deque<int> dueue(5);
void Produce()
{
    for (int i = 0; i < 15; ++i)
    {
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(500,1000);
        int dice_roll = distribution(generator); 
        std::this_thread::sleep_for(std::chrono::milliseconds
            (dice_roll));
        dueue.push_back(i);
        printf("thread %d put(%d)\n", std::this_thread::get_id(), i);
    }
}

void Consume()
{
    int x = 0;

    for (int i = 0; i < 10; ++i)
    {
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(500,1000);
        int dice_roll = distribution(generator); 
        std::this_thread::sleep_for(std::chrono::milliseconds
            (dice_roll));
        dueue.pop_front(x);
        printf("thread %d take(%d)\n", std::this_thread::get_id(), x);
    }
}

int main(void)
{
    std::thread producer1(Produce);
    std::thread producer2(Produce);
    std::thread producer3(Produce);
    std::thread producer4(Produce);
    std::thread consumer1(Consume);
    std::thread consumer2(Consume);
    std::thread consumer3(Consume);
    std::thread consumer4(Consume);
    std::thread consumer5(Consume);
    std::thread consumer6(Consume);
    producer1.join();
    producer2.join();
    producer3.join();
    producer4.join();
    consumer1.join();
    consumer2.join();
    consumer3.join();
    consumer4.join();
    consumer5.join();
    consumer6.join();
    
    return 0;
}