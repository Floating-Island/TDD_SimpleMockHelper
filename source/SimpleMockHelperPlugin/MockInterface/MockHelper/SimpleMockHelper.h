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
    template<typename ReturnType, typename ClassType, typename... ArgumentTypes>
    void RegisterMock(std::function<ReturnType(ArgumentTypes...)>* ReplacingFunctionAddress, ReturnType (ClassType::*OriginalMethodAddress) (ArgumentTypes...));
    
    bool ContainsMethodToMock(std::string OriginalMethod) const;
    
    template<typename ReturnType, typename ClassType, typename... ArgumentTypes>
    ReturnType ExecuteMockMethod(ReturnType (ClassType::*OriginalMethodAddress) (ArgumentTypes...), ArgumentTypes&&... args) const;

    template <typename T>
    struct MethodTraits;
    
private:
    std::map<std::string, void*> methodToMockMap;
};

// Cambiar key de void* a un string que salga de typeid().name();  std::string methodName = typeid(void (MyClass::*)(int)).name();

template<typename ReturnType, typename ClassType, typename... ArgumentTypes>
void SimpleMockHelper::RegisterMock(std::function<ReturnType(ArgumentTypes...)>* ReplacingFunctionAddress, ReturnType (ClassType::*OriginalMethodAddress) (ArgumentTypes...))
{
    methodToMockMap.insert({typeid(OriginalMethodAddress).name(), ReplacingFunctionAddress});
}

template<typename ReturnType, typename ClassType, typename... ArgumentTypes>
ReturnType SimpleMockHelper::ExecuteMockMethod(ReturnType (ClassType::*OriginalMethodAddress) (ArgumentTypes...), ArgumentTypes&&... ArgumentValues) const
{
    void* ReplacingFunctionAddress = methodToMockMap.find(typeid(OriginalMethodAddress).name())->second;

    std::function<ReturnType(ArgumentTypes...)>* ReplacingFunctionPointer = static_cast<std::function<ReturnType(ArgumentTypes...)>*>(ReplacingFunctionAddress);

    return (*ReplacingFunctionPointer)(ArgumentValues...);
}

template <typename ClassType, typename RetType, typename... Args>
struct SimpleMockHelper::MethodTraits<RetType(ClassType::*)(Args...)> {
    using Class = ClassType;
    using ReturnType = RetType;
    using ArgumentTuple = std::tuple<Args...>;
    static constexpr bool isConst = false;
};

template <typename ClassType, typename RetType, typename... Args>
struct SimpleMockHelper::MethodTraits<RetType(ClassType::*)(Args...) const> {
    using Class = ClassType;
    using ReturnType = RetType;
    using ArgumentTuple = std::tuple<Args...>;
    static constexpr bool isConst = true;
};

namespace MockedGlobal
{
    extern std::weak_ptr<SimpleMockHelper> GlobalMockHelper;
}

//put here your #endif //TEST_FLAG