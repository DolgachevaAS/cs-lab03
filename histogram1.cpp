#include"histogram.h"
#include<vector>
#include <iostream>
#include"histogram1.h"
using namespace std;

size_t procent( size_t number_count, size_t bin)
{
    size_t  proc=0;
    if (number_count!=0)
    {
        proc=(bin*100)/number_count;
    }
    return proc;
}
