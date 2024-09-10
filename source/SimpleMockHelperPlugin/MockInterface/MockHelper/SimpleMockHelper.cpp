#include "SimpleMockHelper.h"

//put here your #if TEST_FLAG

namespace MockedGlobal
{
    std::weak_ptr<SimpleMockHelper> GlobalMockHelper = std::weak_ptr<SimpleMockHelper>();
}

SimpleMockHelper::SimpleMockHelper()
{
    methodToMockMap = std::map<void*, void*>();
}

bool SimpleMockHelper::ContainsMethodToMock(void* method) const
{
    return methodToMockMap.count(method) > 0;
}

//put here your #endif //TEST_FLAG