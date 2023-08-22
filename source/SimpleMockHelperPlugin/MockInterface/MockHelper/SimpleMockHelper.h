#include <iostream>
#include <functional>
#include <map>
#include <memory>
#include <typeinfo>

//put here your #if TEST_FLAG

//the contents of this file should be used only in the class tests

class SimpleMockHelper
{
public:
    SimpleMockHelper();
    
    //you should use this only in tests
    void RegisterMock(const std::string& MethodName, void* FunctionHolderAddress);
    
    
    bool ContainsMethodToMock(const std::string method) const;
    
    template<typename ReturnType, typename... ArgumentTypes>
    ReturnType ExecuteMockMethod(const std::string& MethodName, ArgumentTypes&&... args) const;

private:
    std::map<const std::string, void*> methodToMockMap;
};

template<typename FunctionSignature>
struct FunctionHolder
{
    std::function<FunctionSignature> function;
    
    FunctionHolder(std::function<FunctionSignature> afunctionToHold)
    {
        function = afunctionToHold;
    }
};

//there was no problem before with: class... ArgumentTypes instead of typename... ArgumentTypes
template<typename ReturnType, typename... ArgumentTypes>
ReturnType SimpleMockHelper::ExecuteMockMethod(const std::string& MethodName, ArgumentTypes&&... ArgumentValues) const
{
    void* FunctionHolderAddress = methodToMockMap.find(MethodName)->second;
    
    std::cout << "last stop, get the address of found void*: " << FunctionHolderAddress << std::endl;

    FunctionHolder<ReturnType(ArgumentTypes...)>* FunctionHolderPointer = reinterpret_cast<FunctionHolder<ReturnType(ArgumentTypes...)>*>(FunctionHolderAddress);
    
    std::cout << "last stop, get the address of found recasted function: " << FunctionHolderPointer << std::endl;

    return FunctionHolderPointer->function(ArgumentValues...);
}

namespace MockedGlobal
{
    extern std::weak_ptr<SimpleMockHelper> GlobalMockHelper;
}

//put here your #endif //TEST_FLAG