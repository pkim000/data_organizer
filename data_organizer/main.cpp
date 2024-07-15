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
    if (!rdFile.is_open()) {
        cout << "Error opening file" << endl;
    }
    else{
        // writing list of years into file (first 5 from orig file)
        string years;
        string dataMetric;
        
        getline(rdFile, years);
        years.erase(0,4); //removes "Year"
        years.insert(0, "Ticker"); //replaces it with ticker
        years.erase(31, years.size()); //removes " - 2007"
        wrtFile << years << endl;
        
        //writing revenue data into file (past 5 years)
        string searchValue;
        string compareValue;
        string dataLine;
        long searchLength;
        
        cout << "Enter specific data to find: ";
        cin.ignore();
        getline(cin, searchValue);
        searchLength = searchValue.length(); //assigns length of searched value
        
        while (getline(rdFile, dataLine)) {
            compareValue = dataLine.substr(0, searchLength);
            if (compareValue == searchValue) {
                break;
            }
        }
        dataLine.erase(0, searchLength + 1); //erases the data name
        dataLine.insert(0, tickerName + ","); //adds ticker name to replace the data name
        dataLine.erase(dataLine.length() - 8, dataLine.length()); //removes "-upgrade"
        wrtFile << dataLine << endl;
    }
    rdFile.close();
    wrtFile.close();
}
