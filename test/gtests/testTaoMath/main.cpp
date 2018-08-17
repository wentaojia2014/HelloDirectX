#include <gtest/gtest.h>
#ifdef _WINDOWS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
int main(int argc, char** argv)
{
#ifdef _WINDOWS
    _CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}