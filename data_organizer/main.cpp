#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream rdFile;
    ofstream wrtFile;
    
    // file opening/creating
    string inputFileName;
    cout << "Enter name of file to write into or name of file to create: ";
    getline(cin, inputFileName);
    inputFileName.append(".csv");
    wrtFile.open(inputFileName, ios::app);
    cout << "Opened " << inputFileName << endl;

    //Writing years data into file
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
        
        if (!rdFile.is_open()) {
            cout << "Error opening file" << endl;
        }
        else {
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
    }
    
    //Writing finanical data into file
    bool programStatus = true;

    //gets file name to collect data from, continues to loop unless user quits program
    while (programStatus) {
        string fileName;
        string tickerName;
        
        cout << "Enter file name to collect data from (enter 'q' to end program): ";
        getline(cin, fileName);
        transform(fileName.begin(), fileName.end(), fileName.begin(), ::toupper);
        tickerName = fileName;
        fileName.append(".csv");
        rdFile.open(fileName);
        
        if (!rdFile.is_open()) {
            cout << "Error opening file" << endl;
        }
        else{
            //searches for data in data file, loops until user ends prog or changes file
            while (true) {
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
                    searchLength = searchValue.length();
                    //searches through file to find searchvalue, breaks early if found
                    while (getline(rdFile, dataLine)) {
                        compareValue = dataLine.substr(0, searchLength);
                        if (compareValue == searchValue) {
                            break;
                        }
                    }
                    //if doesn't return true then search value found & writes data into file
                    if (!rdFile.eof()) {
                        dataLine.erase(0, searchLength + 1); //erases data name
                        dataLine.insert(0, tickerName + ","); //replaces w/ ticker
                        dataLine.erase(dataLine.length() - 8, dataLine.length()); //erases ",upgrade"
                        //dataLine.erase(searchLength, dataLine.find(",", searchLength));
                        wrtFile << dataLine << endl;
                        cout << searchValue << " data written to " << inputFileName
                        << " from " << fileName << endl;
                    }
                    //if eof is true then has not found the search value in the data file
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
