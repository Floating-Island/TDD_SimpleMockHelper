#include "SimpleMockHelper.h"

//put here your #if TEST_FLAG

namespace MockedGlobal
{
    std::weak_ptr<SimpleMockHelper> GlobalMockHelper = std::weak_ptr<SimpleMockHelper>();
}

SimpleMockHelper::SimpleMockHelper()
{
    methodToMockMap = std::map<std::string, void*>();
}

bool SimpleMockHelper::ContainsMethodToMock(std::string OriginalMethod) const
{
    return methodToMockMap.count(OriginalMethod) > 0;
}

//put here your #endif //TEST_FLAG