#include <iostream>
#include <vector>
#include <conio.h>
#include <curl/curl.h>
#include <sstream>
#include <string>
#include "histogram1.h"
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
size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    const size_t data_size = item_size * item_count;
    const char* new_items = reinterpret_cast<const char*>(items);
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(new_items, data_size);
    return data_size;
}

Input
download(const string& address) {
    stringstream buffer;
curl_global_init(CURL_GLOBAL_ALL);
 CURL *curl = curl_easy_init();
 if(curl) {
CURLcode res;
curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
 res = curl_easy_perform(curl);
  if (res != CURLE_OK)
  {
     cout << curl_easy_strerror(res) << endl;
     exit(1);
  }
  curl_easy_cleanup(curl);}
 return read_input(buffer, false);
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



int main(int argc, char* argv[])
{
    Input input;

    if (argc > 1)
    {
                input = download(argv[1]);
}
        else {
         input = read_input(cin, true);
        }


    const auto bins = make_histogram (input);
    show_histogram_svg(bins,input);
    return 0;

}
