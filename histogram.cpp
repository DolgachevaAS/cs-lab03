#include<vector>
#include <iostream>
#include "histogram.h"
#include <windows.h>
#include <string>
#include <sstream>
using namespace std;
void find_minmax (const vector<double>& numbers, double& min, double& max)
{
    if (numbers.size() != 0)
    {
        min = numbers[0];
        max = numbers[0];
        for (double number : numbers)
        {
            if (number < min)
            {
                min = number;
            }
            if (number > max)
            {
                max = number;
            }
        }
    }
}

string make_info_text()
{
    stringstream buffer;

    DWORD mask = 0x0000ffff;
    DWORD mask_major = 0b00000000'00000000'00000000'11111111;
    DWORD info = GetVersion();
    DWORD platform = info >> 16;
    DWORD version = info & mask;
    DWORD version_major = version & mask_major;
    DWORD version_minor = version >> 8;

    if ((info & 0x40000000) == 0)
    {
        DWORD build = platform;
        buffer << "Windows v" << version_major << "." << version_minor << "(build " << build << ")\n";
    }

    char computer_dir[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computer_dir);
    GetComputerNameA(computer_dir, &size);
    buffer << "Computer name: " << computer_dir << "\n";

    return buffer.str();
}

