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

#define SIMPLEMOCKING_GLOBAL_EXECUTEMOCKED(ReturnType, ClassMethodName, ...)    \
/* put here your #if TEST_FLAG */   \
const std::weak_ptr<SimpleMockHelper> GlobalMockHelperInstance = SimpleMockHelperInterface::GlobalMockHelper();    \
if(!GlobalMockHelperInstance.expired() && GlobalMockHelperInstance.lock()->ContainsMethodToMock(ClassMethodName))    \
{   \
    return GlobalMockHelperInstance.lock()->ExecuteMockMethod<ReturnType>(ClassMethodName, ##__VA_ARGS__);    \
}/* add here a \ if you put your #if TEST_FLAG like the comment above */
//put here your #endif //TEST_FLAG

#define SIMPLEMOCKING_EXECUTEMOCKED(ReturnType, ClassMethodName, ...)    \
/* put here your #if TEST_FLAG */   \
const std::weak_ptr<SimpleMockHelper> MockHelperInstance = GetMockHelper();    \
if(!MockHelperInstance.expired() && MockHelperInstance.lock()->ContainsMethodToMock(ClassMethodName))    \
{   \
    return MockHelperInstance.lock()->ExecuteMockMethod<ReturnType>(ClassMethodName, ##__VA_ARGS__);    \
}/* add here a \ if you put your #if TEST_FLAG like the comment above */
//put here your #endif //TEST_FLAG