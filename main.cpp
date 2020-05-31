#include <iostream>
#include <vector>
#include <conio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <sstream>
#include <string>
#include "histogram.h"
#include "svg.h"
#include <cstdio>
#include <windows.h>

using namespace std;

Option arguments(int argc, char* argv[])
{
    Option option_bins;
    option_bins.argv_array=0;
    option_bins.bins=0;
    option_bins.right_bins=false;
    option_bins.instruction=false;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            if (strcmp(argv[i],"-bins") == 0)
            {
                if(i+1<argc)
                {
                    option_bins.bins= atoi(argv[i+1]);
                    if (option_bins.bins)
                    {
                        option_bins.right_bins=true;
                        i++;
                    }
                    else
                    {
                        option_bins.instruction=true;
                    }
                }

                else
                {
                    option_bins.instruction=true;
                }
            }
        }
        else
        {
            option_bins.argv_array=argv[i];
        }
    }
    return option_bins;
}
vector<double>
input_numbers(istream& in,size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}

Input
read_input(istream& in,bool prompt,const Option &option_bins)
{
    Input Input;
    size_t number_count;
    if (option_bins.right_bins)
    {
        cerr << "Enter number count: ";
        in >> Input.number_count;
        cerr << "Enter numbers: ";
        Input.numbers=input_numbers(in, Input.number_count);
        Input.bin_count=option_bins.bins;
        return Input;
    }
    if(prompt)
    {
        cerr << "Enter number count: ";
        in >> number_count;
        cerr << "Enter numbers: ";
        Input.numbers = input_numbers(in, number_count);
        cerr << "Enter column count: ";
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
write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    const size_t data_size = item_size * item_count;
    const char* new_items = reinterpret_cast<const char*>(items);
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(new_items, data_size);
    return data_size;
}

Input
download(const string& address,const Option &option_bins)
{
    stringstream buffer;

    curl_global_init(CURL_GLOBAL_ALL);

    CURL *curl = curl_easy_init();
    if(curl)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if (res)
        {
            cout << curl_easy_strerror(res) << endl;
            exit(1);
        }
    }
    curl_easy_cleanup(curl);
    return read_input(buffer, false, option_bins);
}

vector<size_t> make_histogram( struct Input Input)
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


int
main(int argc, char* argv[])
{
    Input input;
    /* char system_dir[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD Size = sizeof(system_dir);
    GetComputerNameA(system_dir, &Size);
    printf("System name: %s\n", system_dir);
    printf("WindowsVersion  %x\n", GetVersion());
    printf("WindowsVersion  %u\n", GetVersion());
    DWORD mask = 0x0000ffff;
    DWORD mask_major = 0b00000000'00000000'00000000'11111111;
    DWORD info = GetVersion();
    DWORD platform = info >> 16;
    DWORD version = info & mask;
    DWORD version_major = version & mask_major;
    DWORD version_minor = version >> 8;
    printf("decimal Wndowsversion: %u.\n", version);
    printf("hexadecimal Windowsversion: %x.\n", version);
    printf("platform: %u.\n", platform);
    printf("major version: %u.\n", version_major);
    printf("minor version: %u.\n", version_minor);
    if ((info &0x40000000) == 0) {
    DWORD build = platform;
    printf("build: %u.\n", build);
    } */
    Option option_bins=arguments(argc,argv);
    if (option_bins.instruction)
    {
        cerr<<"Enter options that match the condition";
        return 1;
    }
    if (option_bins.argv_array)
    {
        input = download(option_bins.argv_array,option_bins);
    }
    else
    {
        input = read_input(cin, true, option_bins);
    }

    const auto bins = make_histogram(input);
    show_histogram_svg(bins, input.number_count);

    return 0;
}
