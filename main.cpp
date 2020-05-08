#include <iostream>
#include <vector>
#include <conio.h>
#include<curl/curl.h>
#include "histogram.h"
#include "svg.h"

using namespace std;

vector<double> input_numbers(istream& in, size_t count)
{
    vector <double> result(count);
    for (int i=0; i<count; i++)
    {
        in>>result[i];
    }
    return result;

}

Input
read_input(istream& in, bool prompt )
{
    Input Input;
    size_t number_count;

    if (prompt)
    {
        cerr << "Enter number count: ";
        in >> number_count;

        cerr << "Enter numbers: ";
        Input.numbers = input_numbers(in, number_count);

        cerr << "Enter bin count: ";
        in >> Input.bin_count;
    }
    else
    {
        in >> number_count;
        Input.numbers = input_numbers(in, number_count);
        in >> Input.bin_count;
    }
    return Input;
}


vector<size_t>
make_histogram( struct Input Input)
{
    vector<size_t> bins(Input.bin_count, 0);

    double min;
    double max;
    find_minmax(Input.numbers, min, max);
    for(double x: Input.numbers)
    {
        size_t bin_index=(x-min)/(max-min)*Input.bin_count;
        if (bin_index==Input.bin_count)
        {
            bin_index--;
        }
        bins[bin_index]++;
    }
    return bins;
}



int main()
{
    curl_global_init(CURL_GLOBAL_ALL);
    const auto Input=read_input(cin, true);
    const auto bins = make_histogram (Input);
    show_histogram_svg(bins,Input.bin_count);
    return 0;

}
