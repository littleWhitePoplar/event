#include<iostream>
#include<thread>
#include"mEvent.h"
using std::thread;

void test()
{
    function<void(int)> slotFun = [](int a){
        std::cout<<a<<"\n";
    };
    mEvent::regSlot<int>("secondSlot",&slotFun);
    mEvent::connect<int>("secondSignal","secondSlot");
    mEvent::emit<int>("secondSignal",1);
}


int main(int argc, char *argv[])
{
    thread th1(test);
    function<void(int)> slotFun = [](int a){
        std::cout<<a<<"\n";
    };
    mEvent::regSlot<int>("firstSlot",&slotFun);
    mEvent::connect<int>("firstSignal","firstSlot");
    mEvent::emit<int>("firstSignal",1);
    th1.join();
    return 0;
}
