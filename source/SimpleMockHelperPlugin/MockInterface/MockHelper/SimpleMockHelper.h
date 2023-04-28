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
    
    template<typename ReturnType, class... ArgumentTypes>
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

template<typename ReturnType, class... ArgumentTypes>
ReturnType SimpleMockHelper::ExecuteMockMethod(const std::string& MethodName, ArgumentTypes&&... args) const
{
    void* FunctionHolderAddress = methodToMockMap.find(MethodName)->second;
    
    FunctionHolder<ReturnType(decltype(args)...)>* FunctionHolderPointer = reinterpret_cast<FunctionHolder<ReturnType(decltype(args)...)>*>(FunctionHolderAddress);
    
    return FunctionHolderPointer->function(std::forward<decltype(args)>(args)...);
}

namespace MockedGlobal
{
    extern std::weak_ptr<SimpleMockHelper> GlobalMockHelper;
}

//put here your #endif //TEST_FLAG