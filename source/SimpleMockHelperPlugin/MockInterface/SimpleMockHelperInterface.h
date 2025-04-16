#include "MockHelper/SimpleMockHelper.h"

class SimpleMockHelperInterface
{
//put here your #if TEST_FLAG

public:
    SimpleMockHelperInterface();
    
    const std::weak_ptr<SimpleMockHelper> GetMockHelper();
    
    void SetMockHelper(std::weak_ptr<SimpleMockHelper> NewMockHelperInstance);
    
    static void SetGlobalMockHelper(std::weak_ptr<SimpleMockHelper> NewGlobalMockHelper);
    
    static const std::weak_ptr<SimpleMockHelper> GlobalMockHelper();

private:
    std::weak_ptr<SimpleMockHelper> MockHelperInstance;

//put here your #endif //TEST_FLAG
};


//these macros should be used only in the class to test

#define SIMPLEMOCKING_GLOBAL_EXECUTEMOCKED(ClassMethodAddress, ...)    \
/* put here your #if TEST_FLAG */   \
const std::weak_ptr<SimpleMockHelper> GlobalMockHelperInstance = SimpleMockHelperInterface::GlobalMockHelper();    \
if(!GlobalMockHelperInstance.expired() && GlobalMockHelperInstance.lock()->ContainsMethodToMock(typeid(ClassMethodAddress).name()))    \
{   \
    return GlobalMockHelperInstance.lock()->ExecuteMockMethod(ClassMethodAddress, ##__VA_ARGS__);    \
}/* add here a \ if you put your #if TEST_FLAG like the comment above */
//put here your #endif //TEST_FLAG

#define SIMPLEMOCKING_EXECUTEMOCKED(ClassMethodAddress, ...)    \
/* put here your #if TEST_FLAG */   \
const std::weak_ptr<SimpleMockHelper> MockHelperInstance = GetMockHelper();    \
if(!MockHelperInstance.expired() && MockHelperInstance.lock()->ContainsMethodToMock(typeid(ClassMethodAddress).name()))    \
{   \
    return MockHelperInstance.lock()->ExecuteMockMethod(ClassMethodAddress, ##__VA_ARGS__);    \
}/* add here a \ if you put your #if TEST_FLAG like the comment above */
//put here your #endif //TEST_FLAG