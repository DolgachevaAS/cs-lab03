#include <iostream>
#include <vector>
#include <conio.h>
#include "histogram.h"
#include "svg.h"

using namespace std;

struct Input {
    vector<double> numbers;
    size_t bin_count;
};

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
    Input data;

    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

     cerr<<"bin_count=";
     size_t bin_count;
     in>> bin_count;
  double max=0, min=0;
 find_minmax(data.numbers,max,min);
    return data;
}


vector<size_t> make_histogram (size_t count,const vector<double>& numbers)
{ double min=0;
double max=0;
find_minmax(numbers,min,max);
vector<size_t> bins(count);
for (double number : numbers) {
size_t bin = (size_t)((number - min) / (max - min) * count);
if (bin == count)
{
bin--;
}
bins[bin]++;
}
return bins;
}



int main()
{
    double left;
    double baseline;
    string text;
    size_t number_count, bin_count;

    Input data=read_input(cin);

    const auto bins=make_histogram(data.bin_count,data.numbers);
    show_histogram_svg(bins,data.bin_count);
    return 0;}



