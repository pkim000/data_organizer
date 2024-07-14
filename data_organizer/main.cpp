#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;
    transform(fileName.begin(), fileName.end(), fileName.begin(), ::toupper);
    fileName.append(".csv");
    
    fstream file;
    file.open(fileName);
    
    if (!file.is_open()){
        cout << "Error opening file" << endl;
    }
    else{
        
    }
    
}
