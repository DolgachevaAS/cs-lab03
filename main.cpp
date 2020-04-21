#include <iostream>
#include <vector>
#include <conio.h>
#include "histogram.h"

using namespace std;
vector<double>
input_numbers (size_t count)
{
    vector <double> result(count);
    for (int i=0; i<count; i++)
    {
        cin>>result[i];
    }
return result;
}
vector<size_t>
make_histogram(const vector <double> &numbers,double &max, double &min, size_t &bin_count)
{
    vector<size_t>bins(bin_count,0); /* массив из индексов корзин */
    for(double x : numbers) /* мы каждому x присваиваем последовательно каждый элемент массива "numbers" */
    {
        size_t bin_index=(size_t)((x-min)*bin_count/(max-min));
        if (bin_index==bin_count) /* индекс корзины "bin_index"*/
        {
            bin_index=bin_index-1; /* нумирация идет с 0*/
        }
        bins[bin_index]++;
    }
    return bins;
}

void svg_text(double left, double baseline, string text)
{
     cout << "<text x='"<<left<<"' y='"<<baseline<<"'>"<<text<<"</text>";
}
void svg_proc(double left, double baseline, string text)
{
     cout << "<text x='"<<left<<"' y='"<<baseline<<"'>"<<text<<"%</text>";
}
void svg_rect(double x, double y, double width, double height,string stroke= "black", string fill= "black")
{
    cout<< "<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height<<"' stroke='red' fill='blue'/>";
}
void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";
}
void show_histogram_svg(const vector<size_t>& bins, size_t &number_count)
{
    const size_t MAX_ASTERISK=30;
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    unsigned max_count=0;
    for (size_t b : bins) /* мы присваиваем значение количества элементов */
    {
        if(max_count<b)
            max_count=b; /* здесь мы ищем максимальное количество элементов в массиве*/
    }
    for (size_t bin : bins)
    {
        size_t height=30;
            if(max_count>MAX_ASTERISK) /* Если количество будет больше 35, то уменьшаем масштаб*/
                height=MAX_ASTERISK*((static_cast<double>(bin))/max_count); /* это для того,чтобы было дробное число , получаем, используя "static_cast<double>"*/
        else
        {
            height=bin;
        }
        height = BLOCK_WIDTH * height;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, height, BIN_HEIGHT, "red", "#aaffaa");
        size_t pr=(size_t)(bin*100/number_count);
        svg_proc(370, top + TEXT_BASELINE, to_string(pr));
        top += BIN_HEIGHT;
    }
    svg_end();
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
    const auto numbers = input_numbers(number_count);/* массив из количества элементов "number_count"*/
    cerr<<"bin_count=";
    cin>> bin_count;
    find_minmax (numbers,max,min);
    const auto bins=make_histogram(numbers,max,min,bin_count);
    show_histogram_svg(bins,number_count);
    return 0;
}
