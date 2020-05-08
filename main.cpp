#include <iostream>
#include <vector>
#include <conio.h>
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
vector<size_t> make_histogram(const vector <double> &numbers,double &max, double &min, size_t &bin_count)
{
    vector<size_t>bins(bin_count,0);
    for(double x : numbers)
    {
        size_t bin_index=(size_t)((x-min)*bin_count/(max-min));
        if (bin_index==bin_count)
        {
            bin_index=bin_index-1;
        }
        bins[bin_index]++;
    }
    return bins;
}



int main()
{
    double left;
    double baseline;
    string text;
    size_t number_count, bin_count;
    double max=0, min=0;
    cerr<<"number_count=";
    cin>>number_count;
    cerr<<"Enter number count: "<<"\n";
    const auto numbers = input_numbers(cin,number_count);
    cerr<<"bin_count=";
    cin>> bin_count;
    find_minmax(numbers,max,min);
    const auto bins=make_histogram(numbers,max,min,bin_count);
    show_histogram_svg(bins,number_count);
    return 0;
}
