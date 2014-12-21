#include "tests.hpp"
#include "heaps.hpp"

#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>

using namespace NMeldableHeapsTests;

const size_t numberOfHeapTypes = 3;
const size_t argumentShift = 2;

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
    
    std::vector <size_t> testsWithBadResults;
    
    for (size_t testNumber = 0; testNumber != static_cast<size_t> (argc - argumentShift); ++testNumber)
    {
        size_t numberOfQueries = atoi(argv[testNumber + argumentShift]);
        fprintf(log, "|%zu", testNumber);
        fprintf(log, "|%zu", numberOfQueries);
        
        TestResults previousResult;
        
        for (size_t i = 0; i != numberOfHeapTypes; ++i)
        {
            TestResults currentResult = randomTest(heapTypes[i], numberOfQueries, seed ^ testNumber);
            fprintf(log, "|%.3lf", currentResult.executionTime);
            
            if (i && previousResult.responces != currentResult.responces)
            {
                testsWithBadResults.push_back(testNumber);
            }
            
            previousResult = currentResult;
        }
        fprintf(log, "|");
        fprintf(log, "\n");
        
    }
    
    if (testsWithBadResults.size())
    {
        fprintf(log, "While testing, something wrong happened on these tests:\n");
        for (auto const &testNumber: testsWithBadResults)
        {
            fprintf(log, "%zu ", testNumber);
        }
        fprintf(log, "\n");
    }
    else
    {
        fprintf(log, "Everything went fine\n");
    }
    
    fclose(log);
    return 0;
}