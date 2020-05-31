#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
struct Input
{
    vector<double> numbers;
    size_t bin_count;
    size_t number_count;
};

struct Option
{
    size_t bins;
    bool right_bins;
    bool instruction;
    char* argv_array;
};

void find_minmax (const vector<double>& numbers, double& min, double& max);

string make_info_text();

#endif // HISTOGRAM_H_INCLUDED

