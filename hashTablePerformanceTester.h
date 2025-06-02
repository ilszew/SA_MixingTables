#ifndef HASH_TABLE_PERFORMANCE_TESTER_H
#define HASH_TABLE_PERFORMANCE_TESTER_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>
#include "randomGenerator.h"
#include "timer.h"

struct HashTablePerformanceResults {
    double insert_time;
    double remove_time;
    double find_time;
    int size;
};

template <typename HTType>
class HashTablePerformanceTester {
private:
    RandomGenerator rng;

public:
    explicit HashTablePerformanceTester(unsigned int seed = 12345) : rng(0, INT_MAX, seed) {}

    HashTablePerformanceResults test_performance(int size) {
        HashTablePerformanceResults results{};
        results.size = size;
        Timer timer;

        std::vector<std::pair<int, int>> elements(size);
        for (int i = 0; i < size; ++i) {
            elements[i] = {rng.getRandomInt(1, size * 10), rng.getRandomInt(1, 1000)};
        }

        {
            HTType ht;
            timer.startTimer();
            for (const auto& elem : elements) {
                ht.insert(elem.first, elem.second);
            }
            results.insert_time = timer.stopTimer();
        }

        HTType ht;
        for (const auto& elem : elements) {
            ht.insert(elem.first, elem.second);
        }

        {
            timer.startTimer();
            for (int i = 0; i < size; ++i) {
                int value;
                ht.find(elements[i].first, value);
            }
            results.find_time = timer.stopTimer();
        }

        {
            HTType local_ht = ht;
            timer.startTimer();
            for (const auto& elem : elements) {
                local_ht.remove(elem.first);
            }
            results.remove_time = timer.stopTimer();
        }

        return results;
    }
};

template <typename HTType>
void run_performance_tests(const std::string& hash_table_name,
                           const std::vector<int>& test_sizes,
                           int num_tests) {
    std::cout << "\nTesty dla " << hash_table_name << "\n";
    std::cout << std::string(60, '-') << "\n";

    std::vector<HashTablePerformanceResults> all_results;
    const auto& default_seeds = RandomGenerator::getDefaultSeeds();

    for (int size : test_sizes) {
        std::vector<HashTablePerformanceResults> size_results;

        for (int test = 0; test < num_tests; ++test) {
            unsigned int seed = default_seeds[test % default_seeds.size()];
            HashTablePerformanceTester<HTType> tester(seed);
            size_results.push_back(tester.test_performance(size));
        }

        HashTablePerformanceResults avg_result{};
        avg_result.size = size;
        for (const auto& result : size_results) {
            avg_result.insert_time += result.insert_time;
            avg_result.remove_time += result.remove_time;
            avg_result.find_time += result.find_time;
        }

        avg_result.insert_time /= num_tests;
        avg_result.remove_time /= num_tests;
        avg_result.find_time /= num_tests;

        all_results.push_back(avg_result);

        std::cout << "Rozmiar: " << std::setw(6) << size
                  << " | Insert: " << std::setw(8) << std::fixed << std::setprecision(2) << avg_result.insert_time
                  << " ms | Remove: " << std::setw(8) << avg_result.remove_time
                  << " ms | Find: " << std::setw(8) << avg_result.find_time << " ms\n";
    }
}

#endif