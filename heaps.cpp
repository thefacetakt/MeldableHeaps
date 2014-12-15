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
    FILE *log = fopen("log.html", "w");
    
    size_t seed = atoi(argv[1]);
    std::vector <std::string> nameOfColumns({"Test #", "# of Queies", "Binomial Heap", "Leftist Heap", "Skew Heap"});
    std::vector <EHeapType> heapTypes({EM_BINOMIAL, EM_LEFTIST, EM_SKEW});
    
    
    
    fprintf(log, "<html>\n");
    fprintf(log, "\t<head>\n");
    fprintf(log, "\t\t<style>\n");
    fprintf(log, "\t\t\ttd\n");
    fprintf(log, "\t\t\t{\n");
    fprintf(log, "\t\t\t\tborder: 2px dotted black;\n");
    fprintf(log, "\t\t\t}\n");
    fprintf(log, "\t\t\ttable\n");
    fprintf(log, "\t\t\t{\n");
    fprintf(log, "\t\t\t\tborder-collapse: collapse;\n");
    fprintf(log, "\t\t\t}\n");
    fprintf(log, "\t\t</style>\n");
    fprintf(log, "\t\t<title>\n");
    fprintf(log, "\t\t\tHeaps Testing\n");
    fprintf(log, "\t\t</title>\n");
    fprintf(log, "\t</head>\n");
    fprintf(log, "\t<body>\n");
    fprintf(log, "\t\t<h2>\n");
    fprintf(log, "\t\t\tHeaps Testing Results\n");
    fprintf(log, "\t\t</h2>\n");
    fprintf(log, "\t\t<table>\n");
    fprintf(log, "\t\t\t<tr>\n");
    
    for (auto const &s: nameOfColumns)
    {
        fprintf(log, "\t\t\t\t<td>\n");
        fprintf(log, "\t\t\t\t\t%s\n", s.c_str());
        fprintf(log, "\t\t\t\t</td>\n");
    }
    fprintf(log, "\t\t\t</tr>\n");
    for (int testNumber = 0; testNumber != argc - argumentShift; ++testNumber)
    {
        size_t numberOfQueries = atoi(argv[testNumber + argumentShift]);
        fprintf(log, "\t\t\t<tr>\n");
        fprintf(log, "\t\t\t\t<td>\n");
        fprintf(log, "\t\t\t\t\t%d\n", testNumber);
        fprintf(log, "\t\t\t\t</td>\n");
        fprintf(log, "\t\t\t\t<td>\n");
        fprintf(log, "\t\t\t\t\t%zu\n", numberOfQueries);
        fprintf(log, "\t\t\t\t</td>\n");
        for (size_t i = 0; i != numberOfHeapTypes; ++i)
        {
            TestResults currentResult = randomTest(heapTypes[i], numberOfQueries, seed);
            fprintf(log, "\t\t\t\t<td>\n");
            fprintf(log, "\t\t\t\t\t%.3lf\n", currentResult.executionTime);
            fprintf(log, "\t\t\t\t</td>\n");
        }
        fprintf(log, "\t\t\t</tr>\n");
    }
    
    
    fprintf(log, "\t\t</table>\n");
    fprintf(log, "\t</body>\n");
    fprintf(log, "</html>\n");
    fclose(log);
    system("google-chrome log.html");
    return 0;
}