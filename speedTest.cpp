#include <iostream> 
#include <fstream>
#include <chrono>
#include <random>
#include <iomanip>

#include "BinarySearchTree.h"

int generateRandomdata(BinarySearchTree<int>&, std::vector<int>&, size_t); 
void my_improved_sort(std::vector<int>&);
void unSort(std::vector<int>&); 
void binarySearch(std::vector<int>, int);

int main() {
    std::ofstream outFile("data.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "File failed" << std::endl; 
    }

    size_t SIZE = 12; 

    BinarySearchTree<int> bst1;
    std::vector<int> vec;

    const int NUM_RUNS = 10; 
    std::cout << "Starting Test";
    for (size_t size = 1000; size <= 25000; size += 1000) {
        double totalTime1 = 0.0;
        double totalTime2 = 0.0;
        double averageTime1 = 0.0;
        double averageTime2 = 0.0; 
        bool found = false; 
        
        std::cout << "|";

        //time algorithm
        for (int i = 0; i < NUM_RUNS; i++) {
            std::cout << "-";
            int target = generateRandomdata(bst1, vec, size); 
            my_improved_sort(vec);
            unSort(vec); 
            auto start1 = std::chrono::high_resolution_clock::now();
            found = bst1.search(target); 
            auto stop1 = std::chrono::high_resolution_clock::now();
            auto start2 = std::chrono::high_resolution_clock::now();
            my_improved_sort(vec); 
            binarySearch(vec, target); 
            auto stop2 = std::chrono::high_resolution_clock::now();

            totalTime1 += std::chrono::duration<double, std::milli>(stop1 - start1).count();
            totalTime2 += std::chrono::duration<double, std::milli>(stop2 - start2).count();
            std::cout << "-";
            unSort(vec); 
        }

        std::cout << "|";

        averageTime1 = totalTime1 / NUM_RUNS;
        averageTime2 = totalTime2 / NUM_RUNS; 

        auto now = std::chrono::system_clock::now();               // chrono time point
        std::time_t t = std::chrono::system_clock::to_time_t(now); // convert for formatting
        std::tm local = *std::localtime(&t);

        //outFile << "Size: " << size << "| BST Time: " << averageTime1 << " | " << "Binary Search Time: " << averageTime2 << std::endl; 
        outFile << averageTime1 << std::endl; 
    }
    std::cout << "COMPLETE!\nCHECK OUTPUT FILE data.txt\n\n";
    auto now = std::chrono::system_clock::now();               // chrono time point
    std::time_t t = std::chrono::system_clock::to_time_t(now); // convert for formatting
    std::tm local = *std::localtime(&t);
    outFile << "--- Added: " << std::put_time(&local, "%Y-%m-%d %H:%M:%S") << " ---\n";
    outFile << std::endl << std::endl;
    
}

int generateRandomdata(BinarySearchTree<int>& tree, std::vector<int>& v, size_t size) {
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> filler(1, static_cast<int>(10 * size));

    tree.clear(); 
    v.clear(); 

    for (size_t i = 0; i < size; i++) {
        int num = filler(gen); 
        tree.insert(num); 
        v.push_back(num);  
    }
    std::uniform_int_distribution<int> picker(0, static_cast<int>(size - 1));  

    return v[picker(gen)]; 
    
}

void my_improved_sort(std::vector<int>& arr) {

    for (size_t i = 1; i < arr.size(); i++) {
        int key = arr[i];
        
        //binary search for the insertion point
        size_t left = 0; 
        size_t right = i; 
        while (left < right) {
            int mid = (left + right) / 2;
            if (key >= arr[mid]) {
                left = mid + 1;
            } else right = mid; 
        } //location = left
        //shift right by one then insert
        
        for (size_t j = i; j > left; j--) {
            arr[j] = arr[j - 1];
        }
        arr[left] = key;       
    }    
}

void unSort(std::vector<int>& v) {
    size_t size = v.size();
    for (size_t i = 0; i < size / 2; i++) {
        std::swap(v[i], v[size - 1]);
        i++;
    } 
    for (size_t i = 0; i < size / 2; i++) {
        std::swap(v[i], v[size - 1]);
        
    } 
}

void binarySearch(std::vector<int> v, int target){
    size_t size = v.size(); 
    size_t left = 0;
    size_t right = size - 1;
    size_t location = -1; 

    while (left < right) {
        int mid = (left + right) / 2; 
        if (target > v[mid]) {
            left = mid + 1; 
        } else if (target < v[mid]) {
            right = mid;
        }else {
            location = mid; 
            break; 
        }
    }
}