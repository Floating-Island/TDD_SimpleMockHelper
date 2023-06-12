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
    
};








//add

class AdditionTest : public testing::TestWithParam<std::tuple<int, int, int>>
{
    //int   , int   , int
    //augend, addend, expectedSum
};

INSTANTIATE_TEST_SUITE_P(
    ParametrizedAdditionTestGroup,
    AdditionTest,
    ::testing::Values(
        std::make_tuple(6, 4, 10),
        std::make_tuple(-2, 3, 1),
        std::make_tuple(9, -17, -8),
        std::make_tuple(23, 24, 47)));

TEST_P(AdditionTest, AdditionReturnsSum)
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



    int augend = std::get<0>(GetParam());
    int addend = std::get<1>(GetParam());
    int expectedSum = std::get<2>(GetParam());
    EXPECT_TRUE(expectedSum == expectedSum);
}

//mul

class MultiplicationTest : public testing::TestWithParam<std::tuple<int, int, int>>
{
    //int   , int   , int
    //multiplier, multiplicand, expectedProduct
};

INSTANTIATE_TEST_SUITE_P(
    ParametrizedMultiplicationTestGroup,
    MultiplicationTest,
    ::testing::Values(
        std::make_tuple(8, 8, 64),
        std::make_tuple(-2, 3, -6),
        std::make_tuple(2, 4, 8),
        std::make_tuple(3, 7, 21)));

TEST_P(MultiplicationTest, MultiplicationReturnsProduct)
{
    int multiplier = std::get<0>(GetParam());
    int multiplicand = std::get<1>(GetParam());
    int expectedProduct = std::get<2>(GetParam());

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
    }

    std::cout << "GlobalMockHelper status (out of shared pointer scope): " << ((MockedGlobal::GlobalMockHelper.use_count() == 0) ? "expired" : "still in use") << std::endl;

    std::cout << "execute OriginalOutput on something (global mock should be expired): " << something.OriginalOutput() << std::endl;



    EXPECT_TRUE(expectedProduct == expectedProduct);
}
