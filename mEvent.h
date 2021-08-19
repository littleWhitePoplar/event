#include <map>
#include <functional>
#include <string>
using std::function;
using std::make_pair;
using std::map;
using std::multimap;
using std::string;

template <typename... Args>
class MEvent final
{
private:
    map<string, function<void(Args...)> *> slots;
    multimap<string, string> signalToSlot;
public:
    void regSlot(const string &slotName, function<void(Args...)> *slot)
    {
        // 如果槽名称重复，抛出异常
        auto iter = slots.find(slotName);
        if (iter != slots.end())
        {
            string errorContent = "slot name repeat,name: " + slotName;
            std::runtime_error runErr(errorContent);
            throw runErr;
        }
        slots.insert(make_pair(slotName, slot));
    }
    void connect(const string &signalName, const string &slotName)
    {
        // 如果该连接存在，抛出异常
        auto iter = signalToSlot.find(signalName);
        if (iter != signalToSlot.end() && iter->second == slotName)
        {
            string errorContent = "connect repeat,signal name: " + signalName + ", slot name : " + slotName;
            std::runtime_error runErr(errorContent);
            throw runErr;
        }
        signalToSlot.insert(make_pair(signalName, slotName));
    }
    void emit(const string &signalName, Args... args)
    {
        // 找出所有与该信号连接的槽，调用他们
        for (auto iter : signalToSlot)
        {
            if (iter.first == signalName)
            {
                (*slots[iter.second])(args...);
            }
        }
    }
};

namespace mEvent
{
    template<typename... Args>
    MEvent<Args...> mEvent;

    template<typename... Args>
    void connect(const string &signalName, const string &slotName,function<void(Args...)> *slot)
    {
        mEvent<Args...>.regSlot(slotName,slot);
        mEvent<Args...>.connect(signalName,slotName);
    }

    template<typename... Args>
    void emit(const string &signalName, Args... args)
    {
        mEvent<Args...>.emit(signalName,args...);
    }
}
