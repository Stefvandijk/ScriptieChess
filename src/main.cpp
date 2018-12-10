#include <iostream>
#include <vector>

extern "C"{
  #include <sylvan.h>
  #include <lace.h>
}

using namespace std;
using namespace sylvan;
int cnfsize = 0;


int main(int argc, const char *argv[]) {

    int n_workers = 1; // auto-detect
    lace_init(n_workers, 0);
    lace_startup(0, NULL, NULL);
    LACE_ME;

    // use at most 512 MB, nodes:cache ratio 2:1, initial size 1/32 of maximum
    sylvan_set_limits(512*1024*1024, 1, 5);
    sylvan_init_package();
    sylvan_init_mtbdd();
    /* ... do stuff ... */
    sylvan_gc_disable();

    //lddmc_protect()

    MDD db = lddmc_false;

    uint32_t b[65];

    b[0] = 0;
    b[1] = 1;

    lddmc_union_cube(db, b, 65);


    exit(0);  // (faster than "return", which will invoke the destructors)
    //delete cnf;
}
