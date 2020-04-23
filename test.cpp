#include "histogram.h"

#include <cassert>


#include "histogram.h"

#include <cassert>

void test_same() {
    double min = 0;
    double max = 0;
    find_minmax({-2,-2,-2}, min, max);
    assert(min == -2);
    assert(max == -2);
}

int main() {
    test_positive();
    test_otr();
    test_same();
}
