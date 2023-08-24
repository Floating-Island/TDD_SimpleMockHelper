#include "SimpleMockHelper.h"

//put here your #if TEST_FLAG

namespace MockedGlobal
{
    std::weak_ptr<SimpleMockHelper> GlobalMockHelper = std::weak_ptr<SimpleMockHelper>();
}

SimpleMockHelper::SimpleMockHelper()
{
    methodToMockMap = std::map<const std::string, void*>();
}

void SimpleMockHelper::RegisterMock(const std::string& MethodName, void* ReplacingFunctionAddress)
{
    methodToMockMap.insert({MethodName, ReplacingFunctionAddress});
}

bool SimpleMockHelper::ContainsMethodToMock(const std::string method) const
{
    return methodToMockMap.count(method) > 0;
}

//put here your #endif //TEST_FLAG