#include <vector>
#include <functional>
#include <map>
using std::function;
using std::make_pair;
using std::map;
using std::vector;
using std::multimap;
/*
    *todo
    *尝试是否可以做成异步
    *加上时钟
    *出现的问题：不同类调用同一个类的函数会emit不一样的signal
*/
template <typename ... Args>
class MEvent
{
private:
    multimap<int, int> signalFunToSlotFun;
    vector<function<void(Args...)> *> pointerToFuns;
    // 查找元素的位置，返回-1代表未找到
    int findPos(function<void(Args...)> *signalFun)
    {
        int signalPos = 0;
        for(auto iter : pointerToFuns)
        {
            if(iter==signalFun)
            {
                break;
            }
            signalPos++;
        }
        if(signalPos>=pointerToFuns.size())
        {
            return -1;
        }
        return signalPos;
    }
public:
    MEvent()
    {
    }
    void addEvent(function<void(Args...)> *signalFun, function<void(Args...)> *slotFun)
    {
        // 查找信号函数的位置。如果不存在将该信号函数加入数组中。
        int pos = findPos(signalFun);
        std::cout<<"pos : "<<pos<<"\n";
        int signalFunPos=0;
        if(pos == -1)
        {
            pointerToFuns.push_back(signalFun);
            signalFunPos = pointerToFuns.size() - 1;
        }
        else
        {
            signalFunPos = pos;
        }
        pointerToFuns.push_back(slotFun);
        int slotFunPos = pointerToFuns.size() - 1;
        // 添加信号和槽的映射关系
        signalFunToSlotFun.insert(make_pair(signalFunPos,slotFunPos));
    }
    void emitSignal(function<void(Args...)> *signalFun,Args... args)
    {
        //查找信号的位置，如果未找到，则抛出异常
        int signalPos = findPos(signalFun);
        if(signalPos == -1)
        {
            throw "signal not found!";
        }
        // 根据映射关系调用槽函数
        for(auto iter = signalFunToSlotFun.begin();iter!=signalFunToSlotFun.end();iter++)
        {
            if(iter->first==signalPos)
            {
                (*pointerToFuns[iter->second])(args...);
            }
        }
    }

};

namespace mEvent
{
    template<typename... Args>
    MEvent<Args...> mEvent;

    template<typename... Args>
    void connect(function<void(Args...)> *signalFun,function<void(Args...)> *slotFun)
    {
        mEvent<Args...>.addEvent(signalFun,slotFun);
    }

    template<typename... Args>
    void emitSignal(function<void(Args...)> *signalFun,Args... args)
    {
        mEvent<Args...>.emitSignal(signalFun,args...);
    }
};