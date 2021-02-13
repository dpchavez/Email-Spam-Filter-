/* Project 1
 * CS 251 - Professor J. Hummel
 * Email Filter
 * 
 * Student: Daniela P. Chavez
 * UIN: 
*/


#include <iostream>
#include <fstream>
#include <string>
#include "ourvector.h"
using namespace std;

//---------------------------------------------------------------------
bool binarySearch(ourvector<string> &emailList, string userInput){
    int low = 0;
    int mid;
    int high = emailList.size() - 1;
    int searchResult;
    
    while (low <= high){
        mid = (low + high)/2;
        searchResult = userInput.compare(emailList[mid]);
        
        if (searchResult == 0){
            return true;
            }
        
        else if (searchResult < 0){
            high = mid - 1;
            }
        
        else {
            low = mid + 1;
            }
    } // closing while-loop
    return false;
}//closing binarySearch function

//---------------------------------------------------------------------
//this function is to load the chosen file by the user
void loadFile(ourvector<string> &emailList, string userInput){
    

    ifstream inFS;
    
    inFS.open(userInput);  //File chosen by the user will be open
    
    //Verifying that the file opens correctly
    if(!inFS.is_open()){
        cout << "**Error, unable to open '" << userInput << "'"<<endl;
        cout << endl;
        return;
        } // closing if statement
    else {
        cout << "Loading '"<< userInput << "'"<<endl;
        }
    emailList.clear();
    
    while (!inFS.eof()){    //while the file hasnt reached the end
        string word;
        inFS >> word;
        if (!inFS.fail()){              // if the file doesnt contain any error
            emailList.push_back(word); //then add words into vector 
            }  //closing if-statement
        } //closing while-loop
    
    int vectorSize = emailList.size();
    cout << "# of spam entries: " << vectorSize << endl;
    
    inFS.close(); //closing file
    cout << endl;
} // closing void loadFile(vector<string> &emailList, string userInput)


//---------------------------------------------------------------------
void displayFile(ourvector<string> &emailList){
    int vectorSize = emailList.size();
    for (int i = 0; i < vectorSize; i++){
        cout << emailList.at(i) << endl;
    }
    cout << endl;
}

//---------------------------------------------------------------------

bool check(ourvector<string> &emailList, string userInput ){
    string username;
    string domain;
    string updatedUserInput;
    string userInputWithAsteric;
        
    size_t pos = userInput.find("@");
    username = userInput.substr(0, pos);
    domain = userInput.substr(pos + 1);
    
    updatedUserInput = domain + ":" + username;
    userInputWithAsteric = domain + ":*";
        
    if (binarySearch(emailList, updatedUserInput) == true 
        || binarySearch(emailList,userInputWithAsteric )){
            return true;
            }
    return false;
    cout << endl;
}

//---------------------------------------------------------------------

void filter(ourvector<string> &emailList, string userInput, string newFile){
    ifstream inFS;
    string email;
    inFS.open(userInput);
    int msgID;
    string subject;
    int numProcessed = 0;
    int spamProcessed = 0;
    
    ofstream outfile(newFile);
    
    //Verifying that the file opens correctly
    if(!inFS.is_open()){
        cout << "**Error, unable to open '" << userInput <<"'"<< endl;
        return;
        } // closing if statement
    
    while (!inFS.eof()){
        inFS >> msgID;
        inFS >> email;
        getline(inFS, subject);
        if (!inFS.fail()){
           if (check(emailList, email) == false){
            outfile << msgID << " " << email << subject << endl;
            spamProcessed++;
                }
           numProcessed++;
            } 
        }
        
    outfile.close();
    cout << "# emails processed: " << numProcessed << endl;
    cout << "# non-spam emails:  " << spamProcessed << endl;
}

//---------------------------------------------------------------------

void displayOptions( ourvector<string> &myVals, string &userInput1){
    string userInput2;
    string userInput3;
    
    while (true){
        cout << "Enter command or # to exit> ";
        cin >> userInput1;
        
        while (userInput1 != "#"){
           
            if (userInput1 == "load"){
                cin >> userInput2;
                loadFile(myVals,userInput2);
                break;
                }
            
            if (userInput1 == "display"){
                displayFile(myVals);
                break;
                }
            
            if (userInput1 == "check"){
                cin >> userInput2;
                if (check(myVals, userInput2) == true) {
                    cout << userInput2 << " is spam" << endl;
                    cout << endl;
                    }
                
                else {
                    cout << userInput2 << " is not spam" << endl;
                    cout << endl;
                    }
                break;
                }
            
            if (userInput1 == "filter"){
                cin >> userInput2 >> userInput3;
                filter(myVals, userInput2, userInput3);
                cout<< endl;
                break;
                }
            
            else{
                cout << "**invalid command" << endl;
                cout << endl;
                break;
                }

            } // closing while loop
        
    if (userInput1 == "#"){
            return;
            }
        }
}

//---------------------------------------------------------------------
int main(){
    string userInput1;
    ourvector <string> myVals;
    
    cout << "** Welcome to spam filtering app **" << endl;
    cout << endl;

        displayOptions(myVals, userInput1);
        
    return 0;
}
