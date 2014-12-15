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
    FILE *log = fopen("README.md", "w");
    
    size_t seed = atoi(argv[1]);
    std::vector <std::string> nameOfColumns({"Test #", "# of Queies", "Binomial Heap", "Leftist Heap", "Skew Heap"});
    std::vector <EHeapType> heapTypes({EM_BINOMIAL, EM_LEFTIST, EM_SKEW});
    
    fprintf(log, "Heaps Testing Result\n");
    fprintf(log, "--------------------\n");
    
    for (auto const &s: nameOfColumns)
    {
        fprintf(log, "|%s ", s.c_str());
    }
    fprintf(log, "|\n");
    for (size_t i = 0; i < nameOfColumns.size(); ++i)
    {
        fprintf(log, "|---------");
    }
    fprintf(log, "|\n");
    
    for (int testNumber = 0; testNumber != argc - argumentShift; ++testNumber)
    {
        size_t numberOfQueries = atoi(argv[testNumber + argumentShift]);
        fprintf(log, "|%d", testNumber);
        fprintf(log, "|%zu", numberOfQueries);
        for (size_t i = 0; i != numberOfHeapTypes; ++i)
        {
            TestResults currentResult = randomTest(heapTypes[i], numberOfQueries, seed);
            fprintf(log, "|%.3lf", currentResult.executionTime);
        }
        fprintf(log, "|\n");
    }
    
    fclose(log);
    return 0;
}