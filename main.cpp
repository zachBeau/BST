#include <iostream>
#include <fstream> 
#include <string> 
#include <random>
#include "BinarySearchTree.h"

using std::cout, std::cin, std::endl, std::string;

void display(int&);
void menu(); 
template <typename T>
void randomTree(BinarySearchTree<T>&, int); 

int main() {

    string input = " ";    
    bool whileTrue = true; 

    BinarySearchTree<int> bst; 

    while(whileTrue) {
        
        //menu prints
        menu(); 
        cout << endl; 

        //get menu input (number)
        cout << "Menu Selection:\t";
        getline(cin, input);

        cout << string(50, '\n');
        cout << "Menu Selction:\t" << input << endl; 
        
        switch (stoi(input)) {
            case 1: 
                bst.clear(); 
                cout << "Enter number, type 'q' to exit" << endl; 
                getline(cin, input); 
                while (input != "q") {               
                    cout << "insert(" << input << ")\n";
                    bst.insert(stoi(input)); 
                    getline(cin, input); 
                }
                break;
            case 2: {
                bst.clear();
                cout << "How many elements in the tree?\t";
                getline(cin, input); 
                cout << endl;
                randomTree(bst, stoi(input)); 
                break; 
            }
            case 3: 
                bst.print();
                break;
            case 4: 
                cout << "Tree height is " << bst.height() << " nodes.\n";
                break;
            case 5: 
                cout << "Tree size is " << bst.size() << " total nodes.\n";
                break;
            case 6: 
                cout << "Leaf count is " << bst.leafCount() << " total leaves\n";
                break;
            case 7: { //braces required here because of creation of outFile.
                        //Braces are required to control the scope of any variable created in a switch statement 
                string fileName = "file.txt";
                cout << "File Name: ";
                getline(cin, fileName); 
                cout << endl; 
                fileName += ".txt";
                //1. open file
                std::ofstream outFile(fileName, std::ios::app);
                //2. check for succesfule opening
                if (!outFile.is_open()) {
                    std::cerr << "File failed to open\n";
                    break; 
                }
                //3. print data to file
                bst.print(outFile); 
                //4. close file
                outFile.close(); 
                cout << "file succesfully written";
                break;
            }
            case 0: 
                cout << "Binary Search Tree operations ended";
                whileTrue = false; 
                return 1;
            default:
                std::cerr << "Unknown error or input\n";
                break; 

        }
    }

}

void display(int& data) {
    cout << data << " "; 
}

void menu() {
    cout << endl << string(12, '=') << "MENU" << string(12, '=') << endl; 
    cout << "1. Create Binary Search Tree\n2. Create random binary search tree\n3. Print Binary Search Tree to Screen\n"
        << "4. Find Height\n5. Find Size\n6. Find Leaf Count\n7. Export to file\n0. Exit";
    cout << endl << string(28, '=') << endl; 
}

template <typename T> 
void randomTree(BinarySearchTree<T>& tree, int nodeCount) {
    cout << "Creating a tree with random numbers.... " << endl; 
    std::random_device rand;
    std::mt19937 gen(rand()); 
    std::uniform_int_distribution<> dis(1, 25);

    for (int i = 0; i < nodeCount; i++) {
        tree.insert(dis(gen)); 
    }
    cout << "Tree created" << endl;
    //bst.print();  
}