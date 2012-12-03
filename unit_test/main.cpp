#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "gtest/gtest.h"
//#include <UnitTest++.h>

#include "../histogram.h"

#define TRUE 1
#define FALSE 0

using namespace std;


#include "statistics.h"

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

