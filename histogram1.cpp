
#include<vector>
#include <iostream>
#include"histogram.h"
using namespace std;

size_t procent(size_t number_count,size_t bin)
{

    size_t proc=(bin*100)/number_count;

    return proc;
}
