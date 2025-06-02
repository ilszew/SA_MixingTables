#include <iostream>
#include <vector>
#include "HashTableAVL.h"
#include "HashTableChaining.h"
#include "hashTablePerformanceTester.h"


int main() {

    std::vector<int> test_sizes = {5000, 10000, 15000, 20000, 30000, 40000, 60000, 100000};
    int num_tests = 3;

    std::cout << "=== Testy wydajnosci ===\n";

    run_performance_tests<HashTableAVL>("HashTableAVL", test_sizes, num_tests);
    run_performance_tests<HashTableChaining>("HashTableChaining", test_sizes, num_tests);

    return 0;
}