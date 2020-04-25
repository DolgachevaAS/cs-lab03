#include "histogram.h"
#include <cassert>

void test_bin_nul()
{
  procent(1,0);
}
void test_number_count_nul()
{
procent(0,2);
}

int main() {
   test_bin_nul();
   test_number_count_nul();
}
