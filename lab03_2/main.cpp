#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include "svg.h"
#include <cstdio>
#include <windows.h>
using namespace std;






vector<double> input_numbers(const size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }

    return result;
}



vector<size_t> make_histogram(const vector<double>& numbers, const size_t count)
{
    vector<size_t> result(count);
    double min;
    double max;
    find_minmax(numbers, min, max);
    for (double number : numbers)
    {
        size_t bin = (size_t)((number - min) / (max - min) * count);
        if (bin == count)
        {
            bin--;
        }
        result[bin]++;
    }

    return result;
}

void show_histogram_text(vector<size_t> bins)
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (size_t bin : bins)
    {
        if (bin < 100)
        {
            cout << ' ';
        }
        if (bin < 10)
        {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed)
        {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        for (size_t i = 0; i < height; i++)
        {
            cout << '*';
        }
        cout << '\n';
    }

}


int main()
{
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

    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count);


    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;


    const auto bins = make_histogram(numbers, bin_count);


    show_histogram_svg(bins);

    return 0;
}
