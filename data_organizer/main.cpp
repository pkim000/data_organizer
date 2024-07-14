#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // getting file & ticker name data
    string fileName;
    string tickerName;
    
    cout << "Enter file name: ";
    cin >> fileName;
    transform(fileName.begin(), fileName.end(), fileName.begin(), ::toupper);
    tickerName = fileName;
    fileName.append(".csv");
    
    // file reading and writing start
    ifstream rdFile;
    ofstream wrtFile;
    
    rdFile.open(fileName);
    wrtFile.open("revenue_data.csv");
    // opening file test
    if (!rdFile.is_open()){
        cout << "Error opening file" << endl;
    }
    else{
        // writing list of years into file (first 5 from orig file)
        string years;
        string dataMetric;
        
        getline(rdFile, years);
        years.erase(0,4);
        years.insert(0, "Ticker");
        years.erase(31, years.size());
        wrtFile << years << endl;
        
        //writing revenue data into file (past 5 years)
        
        
        
        
        
    }
    rdFile.close();
    wrtFile.close();
    
}
