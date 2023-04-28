#include "SimpleMockHelperInterface.h"

//put here your #if TEST_FLAG

SimpleMockHelperInterface::SimpleMockHelperInterface()
{
    MockHelperInstance = std::weak_ptr<SimpleMockHelper>();
}

const std::weak_ptr<SimpleMockHelper> SimpleMockHelperInterface::GetMockHelper()
{
    return MockHelperInstance;
}

void SimpleMockHelperInterface::SetMockHelper(std::weak_ptr<SimpleMockHelper> NewMockHelperInstance)
{
    MockHelperInstance.swap(NewMockHelperInstance);
}

void SimpleMockHelperInterface::SetGlobalMockHelper(std::weak_ptr<SimpleMockHelper> NewGlobalMockHelper)
{
    MockedGlobal::GlobalMockHelper.swap(NewGlobalMockHelper);
}

const std::weak_ptr<SimpleMockHelper> SimpleMockHelperInterface::GlobalMockHelper()
{
    return MockedGlobal::GlobalMockHelper;
}

//put here your #endif //TEST_FLAG