#include "tests.hpp"
#include "heaps.hpp"

#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>

using namespace NMeldableHeapsTests;

const size_t numberOfHeapTypes = 3;
const int argumentShift = 2;
int main(int argc, char **argv)
{
    freopen("log.html", "w", stdout);
    
    size_t seed = atoi(argv[1]);
    std::vector <std::string> nameOfColumns({"Test #", "Binomial Heap", "Leftist Heap", "Skew Heap"});
    std::vector <EHeapType> heapTypes({EM_BINOMIAL, EM_LEFTIST, EM_SKEW});
    
    
    
    printf("<html>\n");
    printf("\t<head>\n");
    printf("\t\t<title>\n");
    printf("\t\t\tHeaps Testing\n");
    printf("\t\t</title>\n");
    printf("\t</head>\n");
    printf("\t<body>\n");
    printf("\t\t<h6>\n");
    printf("\t\t\tHeaps Testing Results\n");
    printf("\t\t</h6>\n");
    printf("\t\t<table>\n");
    printf("\t\t\t<tr>\n");
    for (auto const &s: nameOfColumns)
    {
        printf("\t\t\t\t<td>\n");
        printf("%s", s.c_str());
        printf("\t\t\t\t</td>\n");
    }
    printf("\t\t\t</tr>\n");
    for (int testNumber = 0; testNumber != argc - argumentShift; ++testNumber)
    {
        size_t numberOfQueries = atoi(argv[testNumber + argumentShift]);
        printf("\t\t\t<tr>\n");
        printf("\t\t\t\t<td>\n");
        printf("\t\t\t\t\t%d\n", testNumber);
        printf("\t\t\t\t</td>\n");
        for (size_t i = 0; i != numberOfHeapTypes; ++i)
        {
            TestResults currentResult = randomTest(heapTypes[i], numberOfQueries, seed);
            printf("\t\t\t\t<td>\n");
            printf("\t\t\t\t\t%.10lf\n", currentResult.executionTime);
            printf("\t\t\t\t</td>\n");
        }
        printf("\t\t\t</tr>\n");
    }
    
    
    printf("\t\t</table>\n");
    printf("\t</body>\n");
    printf("</html>\n");
    return 0;
}