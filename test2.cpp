#include <iostream>
#include "mEvent.h"

using std::cout;

class Button
{
public:
    void onclick(int value){};
};

class Print
{
private:
//    Button button;
public:
    Print()
    {
//        function<void(int)> signalFun = std::bind(&Button::onclick, button, std::placeholders::_1);
    }
    void print(int value)
    {
        cout << value << "\n";
    }
};

int main(int argc, char *argv[])
{
    Print print;
    Button button;
    function<void(int)> signalFun = std::bind(&Button::onclick, button, std::placeholders::_1);
    function<void(int)> slotFun = std::bind(&Print::print, print, std::placeholders::_1);
    function<void(int)> slotFun3 = std::bind(&Print::print, print, std::placeholders::_1);
    cout<<signalFun.target<void(int)>()<<"\n";
    cout<<slotFun.target<void(int)>()<<"\n";
    cout<<slotFun3.target<void(int)>()<<"\n";
    if(*slotFun.target<void(int)>()==*slotFun3.target<void(int)>())
    {
        cout << "is\n";
    }
    else
    {
        cout << "not\n";
    }
    function<void(int)> slotFun2 = [](int a){
        cout << a << "\n";
    };
    mEvent::connect(&signalFun,&slotFun);
    mEvent::connect(&signalFun,&slotFun2);
    mEvent::emitSignal(&signalFun,123);
    return 0;
}