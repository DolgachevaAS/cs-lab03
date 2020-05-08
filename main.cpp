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

Input
read_input(istream& in) {
    Input Input;

    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    cerr << "Enter numbers: ";
    Input.numbers = input_numbers(in, number_count);

     cerr<<"bin_count=";
     size_t bin_count;
     in>> bin_count;
  double max=0, min=0;
 find_minmax(Input.numbers,max,min);
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
const auto Input=read_input(cin);
const auto bins = make_histogram (Input);
show_histogram_svg(bins,Input.bin_count);
return 0;

}
