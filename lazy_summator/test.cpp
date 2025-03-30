#include <iostream>
#include <vector>
#include <chrono>
#include "lazy_summator.hpp"

int main() {
    srand(time(0));

    std::vector<std::vector<int>> a(5, std::vector<int>(5));
    std::vector<std::vector<int>> b(5, std::vector<int>(5));

    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 5; j++) {
            a[i][j] = rand() % 50;
            b[i][j] = rand() % 50;
        }
    }

    Add<int> c(a, b);

    std::cout << "Matrix A:" << std::endl;
    for (const auto& row : a) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Matrix B:" << std::endl;
    for (const auto& row : b) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    auto start_for_matrix=std::chrono::high_resolution_clock::now();
    std::cout << "Matrix C (A + B):" << std::endl;
    c.print();
    auto end_for_matrix=std::chrono::high_resolution_clock::now();
    auto duration_for_matrixes=std::chrono::duration_cast<std::chrono::microseconds>(end_for_matrix-start_for_matrix).count();
    std::cout<<"Time cost for matrix sum is: "<<duration_for_matrixes<<std::endl;
    
    auto start_for_index=std::chrono::high_resolution_clock::now();
    auto end_for_index=std::chrono::high_resolution_clock::now();
    auto duration_for_index=std::chrono::duration_cast<std::chrono::microseconds>(end_for_index-start_for_index).count();
    std::cout << "Element at [2][2] in Matrix C: " << c[2][2] << std::endl;
    std::cout<<"Time cost for index sum is: "<<duration_for_index<<std::endl;

    return 0;
}
