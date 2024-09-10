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
    template<typename ReturnType, typename... ArgumentTypes>
    void RegisterMock(std::function<ReturnType(ArgumentTypes...)>& ReplacingFunctionAddress, ReturnType (&OriginalMethodAddress) (ArgumentTypes...));
    
    bool ContainsMethodToMock(void* OriginalMethodAddress) const;
    
    template<typename ReturnType, typename... ArgumentTypes>
    ReturnType ExecuteMockMethod(ReturnType (&OriginalMethodAddress) (ArgumentTypes...), ArgumentTypes&&... args) const;

private:
    std::map<void*, void*> methodToMockMap;
};


template<typename ReturnType, typename... ArgumentTypes>
void SimpleMockHelper::RegisterMock(std::function<ReturnType(ArgumentTypes...)>& ReplacingFunctionAddress, ReturnType (&OriginalMethodAddress) (ArgumentTypes...))
{
    methodToMockMap.insert({(void*)OriginalMethodAddress, ReplacingFunctionAddress});
}

template<typename ReturnType, typename... ArgumentTypes>
ReturnType SimpleMockHelper::ExecuteMockMethod(ReturnType (&OriginalMethodAddress) (ArgumentTypes...), ArgumentTypes&&... ArgumentValues) const
{
    void* ReplacingFunctionAddress = methodToMockMap.find((void*)OriginalMethodAddress)->second;

    std::function<ReturnType(ArgumentTypes...)>* ReplacingFunctionPointer = static_cast<std::function<ReturnType(ArgumentTypes...)>*>(ReplacingFunctionAddress);

    return (*ReplacingFunctionPointer)(ArgumentValues...);
}

namespace MockedGlobal
{
    extern std::weak_ptr<SimpleMockHelper> GlobalMockHelper;
}

//put here your #endif //TEST_FLAG