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
    void RegisterMock(const std::string& MethodName, void* ReplacingFunctionAddress);
    
    bool ContainsMethodToMock(const std::string method) const;
    
    template<typename ReturnType, typename... ArgumentTypes>
    ReturnType ExecuteMockMethod(const std::string& MethodName, ArgumentTypes&&... args) const;

private:
    std::map<const std::string, void*> methodToMockMap;
};

template<typename ReturnType, typename... ArgumentTypes>
ReturnType SimpleMockHelper::ExecuteMockMethod(const std::string& MethodName, ArgumentTypes&&... ArgumentValues) const
{
    void* ReplacingFunctionAddress = methodToMockMap.find(MethodName)->second;

    std::function<ReturnType(ArgumentTypes...)>* ReplacingFunctionPointer = static_cast<std::function<ReturnType(ArgumentTypes...)>*>(ReplacingFunctionAddress);

    return (*ReplacingFunctionPointer)(ArgumentValues...);
}

namespace MockedGlobal
{
    extern std::weak_ptr<SimpleMockHelper> GlobalMockHelper;
}

//put here your #endif //TEST_FLAG