
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


int main()
{
    /* initialize random seed: */
    srand(time(NULL));

    int d1 = 1, d2 = 10, d3 = 20, d4 = 30;
    int night1 = rand() % (d2 - d1 + 1) + d1;
    int night2 = rand() % (d3 - d2 + 1) + d2;
    int night3 = rand() % (d4 - d3 + 1) + d3;

    std::cout << "Code nights of this month: " << night1 << ", " << night2 << ", " << night3 << "!" << std::endl;
}