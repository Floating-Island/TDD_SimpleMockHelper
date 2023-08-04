#include <gtest/gtest.h>
#include <tuple>

#include "SimpleMockHelperPlugin/SimpleMockHelperInclude.h"




class ClassName : public SimpleMockHelperInterface
{
public:
    std::string methodName(){
        return std::string(__func__);
    }
    
    std::string ClassNameName(){
        return std::string(typeid(*this).name());
    }
    
    std::string ClassMethodName()
    {
        return std::string(ClassNameName()).append("::").append(methodName());
    }
    
    
    std::string OriginalMethod()
    {
        SIMPLEMOCKING_EXECUTEMOCKED(std::string, MockedMethodNames::ClassNameOriginalMethod)
        return "It's the original!";
    }
    
    std::string OriginalOutput()
    {
        SIMPLEMOCKING_GLOBAL_EXECUTEMOCKED(std::string, MockedMethodNames::ClassNameOriginalOutput)
        return "the original output";
    } 

    int ReturnsZero()
    {
        SIMPLEMOCKING_GLOBAL_EXECUTEMOCKED(int, MockedMethodNames::ClassNameReturnsZero)
        return 0;
    }  
};








//implement inteface

TEST(InterfaceImplementationTest, CheckOriginalMethodMock)
{
    ClassName something = ClassName();

    std::cout << "execute OriginalMethod on something (supposedly not mocked): " << something.OriginalMethod() << std::endl;

    std::cout << "setting MockHelperInstance in something..." << std::endl;

    std::shared_ptr<SimpleMockHelper> aMockerHelper = std::make_shared<SimpleMockHelper>();

    std::function<std::string()> lambdaHolder = std::function<std::string()> ([]() -> std::string {return std::string("templated method!");});

    FunctionHolder<std::string()> MockedMethodHolder = FunctionHolder<std::string()>(lambdaHolder);

    aMockerHelper->RegisterMock(MockedMethodNames::ClassNameOriginalMethod, &MockedMethodHolder);

    something.SetMockHelper(aMockerHelper);

    std::cout << "execute OriginalMethod on something (supposedly mocked): " << something.OriginalMethod() << std::endl;

    EXPECT_TRUE(something.OriginalMethod() == std::string("templated method!"));
}

//global mock

TEST(GlobalMockerTest, CheckOriginalOutputMock)
{
    ClassName something = ClassName();

    std::cout << "execute OriginalMethod on something (out of shared pointer scope, so not mocked): " << something.OriginalMethod() << std::endl;
    
    {    
        std::cout << "GlobalMockHelper status: " << ((MockedGlobal::GlobalMockHelper.use_count() == 0) ? "expired" : "still in use") << std::endl;
        
        std::cout << "execute OriginalOutput on something (global mock should be expired): " << something.OriginalOutput() << std::endl;
        
        std::cout << "setting new GlobalMockHelper..." << std::endl;
        
        std::shared_ptr<SimpleMockHelper> aGlobalMockerHelper = std::make_shared<SimpleMockHelper>();
        
        std::function<std::string()> lambdaHolder2 = std::function<std::string()> ([]() -> std::string {return std::string("the mocked output!");});
        
        FunctionHolder<std::string()> MockedMethodHolder2 = FunctionHolder<std::string()>(lambdaHolder2);
        
        aGlobalMockerHelper->RegisterMock(MockedMethodNames::ClassNameOriginalOutput, &MockedMethodHolder2);
        
        SimpleMockHelperInterface::SetGlobalMockHelper(aGlobalMockerHelper);
        
        std::cout << "execute OriginalOutput on something (global mock should be in use now): " << something.OriginalOutput() << std::endl;
        
        std::cout << "GlobalMockHelper status: " << ((MockedGlobal::GlobalMockHelper.use_count() == 0) ? "expired" : "still in use") << std::endl;

        EXPECT_TRUE(something.OriginalOutput() == std::string("the mocked output!"));
    }

    std::cout << "GlobalMockHelper status (out of shared pointer scope): " << ((MockedGlobal::GlobalMockHelper.use_count() == 0) ? "expired" : "still in use") << std::endl;

    std::cout << "execute OriginalOutput on something (global mock should be expired): " << something.OriginalOutput() << std::endl;

    EXPECT_TRUE(something.OriginalOutput() == std::string("the original output"));
}

//global mock

TEST(GlobalMockerDifferentSignaturesTest, CheckOriginalOutputMock)
{
    ClassName something = ClassName();

    std::cout << "execute OriginalMethod on something (out of shared pointer scope, so not mocked): " << something.OriginalMethod() << std::endl;
    
    {    
        std::cout << "GlobalMockHelper status: " << ((MockedGlobal::GlobalMockHelper.use_count() == 0) ? "expired" : "still in use") << std::endl;
        
        std::cout << "execute OriginalOutput on something (global mock should be expired): " << something.OriginalOutput() << std::endl;
        
        std::cout << "setting new GlobalMockHelper..." << std::endl;
        
        std::shared_ptr<SimpleMockHelper> aGlobalMockerHelper = std::make_shared<SimpleMockHelper>();
        SimpleMockHelperInterface::SetGlobalMockHelper(aGlobalMockerHelper);
        

        std::function<std::string()> lambdaHolder2 = std::function<std::string()> ([]() -> std::string {return std::string("the mocked output!");});
        
        FunctionHolder<std::string()> MockedMethodHolder2 = FunctionHolder<std::string()>(lambdaHolder2);
        
        aGlobalMockerHelper->RegisterMock(MockedMethodNames::ClassNameOriginalOutput, &MockedMethodHolder2);
        
        
        std::cout << "execute OriginalOutput on something (global mock should be in use now): " << something.OriginalOutput() << std::endl;
        
        std::cout << "GlobalMockHelper status: " << ((MockedGlobal::GlobalMockHelper.use_count() == 0) ? "expired" : "still in use") << std::endl;

        //EXPECT_TRUE(something.OriginalOutput() == std::string("the mocked output!"));




        std::function<int()> lambdaHolder3 = std::function<int()> ([]() -> int {return 2;});
        
        FunctionHolder<int()> MockedMethodHolder3 = FunctionHolder<int()>(lambdaHolder3);
        
        aGlobalMockerHelper->RegisterMock(MockedMethodNames::ClassNameReturnsZero, &MockedMethodHolder3);
        
        
        std::cout << "execute ReturnsZero on something (global mock should be in use now): " << something.ReturnsZero() << std::endl;
        
        std::cout << "GlobalMockHelper status: " << ((MockedGlobal::GlobalMockHelper.use_count() == 0) ? "expired" : "still in use") << std::endl;

        EXPECT_TRUE(something.ReturnsZero() != 0);
    }

    std::cout << "GlobalMockHelper status (out of shared pointer scope): " << ((MockedGlobal::GlobalMockHelper.use_count() == 0) ? "expired" : "still in use") << std::endl;

    std::cout << "execute OriginalOutput on something (global mock should be expired): " << something.OriginalOutput() << std::endl;

    EXPECT_TRUE(something.OriginalOutput() == std::string("the original output"));
}