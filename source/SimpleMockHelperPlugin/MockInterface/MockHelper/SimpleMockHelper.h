#include <iostream>
#include <functional>
#include <map>
#include <memory>
#include <typeinfo>
#include <tuple>
#include <any>

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

    template <typename MethodPointer, typename... ArgumentTypes>
    auto CallExecute(MethodPointer methodPointer, ArgumentTypes&&... ArgumentValues) const;

    template <typename T>
    struct MethodTraits;
    
private:
    std::map<std::string, std::any> methodToMockMap;

    // Method type overloading:

    // Version with 0 arguments and no const:
    template<typename ReturnType, typename ClassType>
    ReturnType ExecuteMockMethod(ReturnType (ClassType::*OriginalMethodAddress) ()) const;

    // Version with 1 or more arguments and no const:
    template<typename ReturnType, typename ClassType, typename... ArgumentTypes>
    ReturnType ExecuteMockMethodWithArguments(ReturnType (ClassType::*OriginalMethodAddress) (ArgumentTypes...), ArgumentTypes&&... ArgumentValues) const;
};


template<typename ReturnType, typename ClassType, typename... ArgumentTypes>
void SimpleMockHelper::RegisterMock(std::function<ReturnType(ArgumentTypes...)>* ReplacingFunctionAddress, ReturnType (ClassType::*OriginalMethodAddress) (ArgumentTypes...))
{
    methodToMockMap.insert({typeid(OriginalMethodAddress).name(), ReplacingFunctionAddress});
}

template <typename ReturnType, typename ClassType>
inline ReturnType SimpleMockHelper::ExecuteMockMethod(ReturnType (ClassType::*OriginalMethodAddress)()) const
{
    std::any ReplacingFunctionAddress = methodToMockMap.find(typeid(OriginalMethodAddress).name())->second;

    std::function<ReturnType()>* ReplacingFunctionPointer = std::any_cast<std::function<ReturnType()>*>(ReplacingFunctionAddress);

    return std::invoke(std::forward<std::function<ReturnType()>*>(ReplacingFunctionPointer));
}

template <typename ReturnType, typename ClassType, typename... ArgumentTypes>
inline ReturnType SimpleMockHelper::ExecuteMockMethodWithArguments(ReturnType (ClassType::*OriginalMethodAddress) (ArgumentTypes...), ArgumentTypes&&... ArgumentValues) const
{
    std::any ReplacingFunctionAddress = methodToMockMap.find(typeid(OriginalMethodAddress).name())->second;

    std::function<ReturnType(ArgumentTypes...)>* ReplacingFunctionPointer = std::any_cast<std::function<ReturnType(ArgumentTypes...)>*>(ReplacingFunctionAddress);

    return std::invoke(std::forward<std::function<ReturnType(ArgumentTypes...)>*>(ReplacingFunctionPointer), std::forward<ArgumentTypes>(ArgumentValues)...);
}

template <typename MethodPointer, typename... ArgumentTypes>
inline auto SimpleMockHelper::CallExecute(MethodPointer methodPointer, ArgumentTypes&&... ArgumentValues) const
{
    using Traits = MethodTraits<MethodPointer>;

    if constexpr (Traits::hasArguments)
    {
        return ExecuteMockMethodWithArguments(methodPointer, std::forward<ArgumentTypes>(ArgumentValues)...);
    }
    else
    {
        return ExecuteMockMethod(methodPointer);
    }
}

template <typename ClassType, typename RetType, typename... Args>
struct SimpleMockHelper::MethodTraits<RetType(ClassType::*)(Args...)> {
    using classType = ClassType;
    using returnType = RetType;
    using argumentTuple = std::tuple<Args...>;
    static constexpr bool isConst = false;
    static constexpr bool hasArguments = sizeof...(Args) > 0;
};

template <typename ClassType, typename RetType, typename... Args>
struct SimpleMockHelper::MethodTraits<RetType(ClassType::*)(Args...) const> {
    using classType = ClassType;
    using returnType = RetType;
    using argumentTuple = std::tuple<Args...>;
    static constexpr bool isConst = true;
    static constexpr bool hasArguments = sizeof...(Args) > 0;
};

namespace MockedGlobal
{
    extern std::weak_ptr<SimpleMockHelper> GlobalMockHelper;
}

//put here your #endif //TEST_FLAG