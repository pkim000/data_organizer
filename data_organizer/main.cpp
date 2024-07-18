#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream rdFile;
    ofstream wrtFile;
    
    // file creation
    string inputFileName;
    cout << "Enter name of file to write into or name of file to create: ";
    getline(cin, inputFileName);
    inputFileName.append(".csv");
    wrtFile.open(inputFileName, ios::app);
    cout << "Opened " << inputFileName << endl;

    string yesOrNo;
    cout << "Would you like to write years data? (y or n): ";
    getline(cin, yesOrNo);
    
    if (yesOrNo == "y") {
        string yearsDataFile;
        
        cout << "Enter file name that has years data: ";
        getline(cin, yearsDataFile);
        transform(yearsDataFile.begin(), yearsDataFile.end(), yearsDataFile.begin(), ::toupper);
        yearsDataFile.append(".csv");
        
        rdFile.open(yearsDataFile);
        
        // opening file test
        if (!rdFile.is_open()) {
            cout << "Error opening file" << endl;
        }
        // writing list of years into file (first 5 from orig file)
        string years;
        string dataMetric;
        
        getline(rdFile, years);
        years.erase(0,4); //removes "Year"
        years.insert(0, "Ticker"); //replaces it with ticker
        years.erase(31, years.size()); //removes " - 2007"
        wrtFile << years << endl;
        
        cout << "Added years data to user data file" << endl;
        rdFile.close();
    }
    
    bool programStatus = true;

    while (programStatus) {
        // reading and getting data
        string fileName;
        string tickerName;
        
        cout << "Enter file name to collect data from: ";
        getline(cin, fileName);
        transform(fileName.begin(), fileName.end(), fileName.begin(), ::toupper);
        tickerName = fileName;
        fileName.append(".csv");
        
        rdFile.open(fileName);
        
        // opening file test
        if (!rdFile.is_open()) {
            cout << "Error opening file" << endl;
        }
        else{
            
            while (true) {
                //writing revenue data into file (past 5 years)
                string searchValue;
                string compareValue;
                string dataLine;
                long searchLength;
                
                cout << "Enter specific data to find (q = change file, qq = end program): ";
                getline(cin, searchValue);
                
                if (searchValue == "q") {
                    rdFile.close();
                    break;
                }
                else if (searchValue == "qq") {
                    programStatus = false;
                    break;
                }
                else {
                    searchLength = searchValue.length(); //assigns length of searched value
                    
                    while (getline(rdFile, dataLine)) {
                        compareValue = dataLine.substr(0, searchLength);
                        if (compareValue == searchValue) {
                            break;
                        }
                    }
                    if (!rdFile.eof()) {
                        dataLine.erase(0, searchLength + 1); //erases the data name
                        dataLine.insert(0, tickerName + ","); //adds ticker name to replace the data name
                        dataLine.erase(dataLine.length() - 8, dataLine.length()); //removes "-upgrade"
                        wrtFile << dataLine << endl;
                        cout << searchValue << " data written to " << inputFileName
                        << " from " << fileName << endl;
                    }
                    else {
                        cout << "Data value " << searchValue << " not found\n";
                    }
                    
                    rdFile.close();
                    rdFile.open(fileName);
                }
            }
        }
        rdFile.close();
    }
    wrtFile.close();
}
