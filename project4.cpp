#include <iostream>
#include <fstream>
#include "AVLTree.h"
#include <string>
#include <time.h>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]){
    clock_t start, end;
    double duration;
    start = clock();
    
    AVLTree temp;
    int icounter = 0;
    int dcounter = 0;
    int rcounter = 0;
    int placeholder = 0;
    int countitems = 0;
    string ssn;
    char charter;
    string first;
    string last;
    
    fstream input(argv[1]);
    while(!input.eof()){
        input >> charter >> ssn >> first >> last;
        string name = first + " " + last;
        if(charter == 'i'){
            if(temp.insert(ssn, name) == true){
               icounter++;
            }
            
        }
        if(charter == 'd'){
            if(temp.deleteNode(ssn) == true){
                dcounter++;}
        }
        if(charter == 'r'){
            if(temp.find(ssn) == true){
                rcounter++;
            }
        }
    }
    input.close();
    
    countitems = icounter - dcounter;
    end = clock();
    duration = ( end - start ) / (double) CLOCKS_PER_SEC;
    cout << "The Number of Valid Insertation :" << icounter << endl;
    cout << "The Number of Valid Deletion :" << dcounter << endl;
    cout << "The Number of Valid Retrieval :" << rcounter << endl;
    cout << "Items in the tree :" << countitems << endl;
    cout << "height of the tree :" << temp.height(temp.getRoot()) << endl;
    cout << "elapsed time: " << duration << endl;
    
    return 0;
    
    
}
