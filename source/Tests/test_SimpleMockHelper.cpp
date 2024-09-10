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
        SIMPLEMOCKING_EXECUTEMOCKED(std::string, &ClassName::OriginalMethod)
        return "It's the original!";
    }
    
    std::string OriginalOutput()
    {
        SIMPLEMOCKING_GLOBAL_EXECUTEMOCKED(std::string, &ClassName::OriginalOutput)
        return "the original output";
    } 

    int ReturnsZero()
    {
        SIMPLEMOCKING_GLOBAL_EXECUTEMOCKED(int, &ClassName::ReturnsZero)
        return 0;
    }

    int TreeBranch(std::string name, int leaf)
    {
        SIMPLEMOCKING_GLOBAL_EXECUTEMOCKED(int, &ClassName::TreeBranch, name, leaf)
        return 0;
    }

    std::string BranchNames(int leaf)
    {
        SIMPLEMOCKING_GLOBAL_EXECUTEMOCKED(std::string, &ClassName::BranchNames, leaf)
        return "A Branch Name";
    }  
};








//implement inteface

TEST(InterfaceImplementationTest, CheckOriginalMethodMock)
{
    ClassName something = ClassName();

    std::cout << "execute OriginalMethod on something (supposedly not mocked): " << something.OriginalMethod() << std::endl;

    std::cout << "setting MockHelperInstance in something..." << std::endl;


    std::shared_ptr<SimpleMockHelper> aMockerHelper = std::make_shared<SimpleMockHelper>();
    something.SetMockHelper(aMockerHelper);


    std::function<std::string()> MockedOriginalMethodFunction = std::function<std::string()> ([]() -> std::string {return std::string("templated method!");});

    aMockerHelper->RegisterMock(&MockedOriginalMethodFunction, &ClassName::OriginalMethod);


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
        SimpleMockHelperInterface::SetGlobalMockHelper(aGlobalMockerHelper);
        

        std::function<std::string()> MockedOriginalMethodFunction = std::function<std::string()> ([]() -> std::string {return std::string("the mocked output!");});

        aGlobalMockerHelper->RegisterMock(&MockedOriginalMethodFunction, &ClassName::OriginalOutput);
        

        std::cout << "execute OriginalOutput on something (global mock should be in use now): " << something.OriginalOutput() << std::endl;
        
        std::cout << "GlobalMockHelper status: " << ((MockedGlobal::GlobalMockHelper.use_count() == 0) ? "expired" : "still in use") << std::endl;

        EXPECT_TRUE(something.OriginalOutput() == std::string("the mocked output!"));
    }

    std::cout << "GlobalMockHelper status (out of shared pointer scope): " << ((MockedGlobal::GlobalMockHelper.use_count() == 0) ? "expired" : "still in use") << std::endl;

    std::cout << "execute OriginalOutput on something (global mock should be expired): " << something.OriginalOutput() << std::endl;

    EXPECT_TRUE(something.OriginalOutput() == std::string("the original output"));
}

TEST(GlobalMockerDifferentSignaturesTest, CheckOriginalOutputMock)
{
    ClassName something = ClassName();

    std::shared_ptr<SimpleMockHelper> aGlobalMockerHelper = std::make_shared<SimpleMockHelper>();
    SimpleMockHelperInterface::SetGlobalMockHelper(aGlobalMockerHelper);
    

    std::function<std::string()> MockedOriginalOutputFunction = std::function<std::string()> ([]() -> std::string {return std::string("the mocked output!");});
    
    aGlobalMockerHelper->RegisterMock(&MockedOriginalOutputFunction, &ClassName::OriginalOutput);

    EXPECT_TRUE(something.OriginalOutput() == std::string("the mocked output!"));


    std::function<int()> MockedReturnsZeroFunction = std::function<int()> ([]() -> int {return 2;});

    aGlobalMockerHelper->RegisterMock(&MockedReturnsZeroFunction, &ClassName::ReturnsZero);

    EXPECT_TRUE(something.ReturnsZero() != 0);
}

TEST(GlobalMockerDifferentSignaturesSecondTryTest, CheckOriginalOutputMock)
{
    ClassName something = ClassName();

    std::shared_ptr<SimpleMockHelper> aGlobalMockerHelper = std::make_shared<SimpleMockHelper>();
    SimpleMockHelperInterface::SetGlobalMockHelper(aGlobalMockerHelper);
    

    std::function<int(std::string, int)> MockedTreeBranchFunction = std::function<int(std::string, int)> ([](std::string, int) -> int {return 5;});
    
    aGlobalMockerHelper->RegisterMock(&MockedTreeBranchFunction, &ClassName::TreeBranch);

    EXPECT_TRUE(something.TreeBranch(std::string("RockyLeaf"), 3) == 5);

    int captureWith2 = 2;
    std::function<std::string(int)> MockedBranchNamesFunction = std::function<std::string(int)> ([captureWith2](int) -> std::string {std::cout << captureWith2 << std::endl; return std::string("AnotherBranchName");});
    
    aGlobalMockerHelper->RegisterMock(&MockedBranchNamesFunction, &ClassName::BranchNames);

    EXPECT_TRUE(something.BranchNames(2) == std::string("AnotherBranchName"));
}