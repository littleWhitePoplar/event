#include<iostream>
#include<thread>
#include"mEvent.h"
using std::thread;

void test()
{
    function<void(int)> slotFun = [](int a){
        std::cout<<a<<"\n";
    };
    mEvent::connect("secondSignal","secondSlot",&slotFun);
    mEvent::emit("secondSignal",1);
}


int main(int argc, char *argv[])
{
    thread th1(test);
    function<void(int)> slotFun = [](int a){
        std::cout<<a<<"\n";
    };
    mEvent::connect("firstSignal","firstSlot",&slotFun);
    mEvent::emit("firstSignal",1);
    th1.join();
    return 0;
}
