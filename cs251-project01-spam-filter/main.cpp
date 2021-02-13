/* Project 1
 * CS 251 - Professor(s) J. Hummel && Shanon Reckinger
 * C++ program to filter email based on spam lists
 * Student: Daniela P. Chavez
 * UIN: 651362773
 * Email *not spam* : dchave29@uic.edu
 * University of Illinois at Chicago
*/

/*
 * *******EXTRACTED FROM THE PROGRAM 1 PDF******** * 
Assignment:
Most email systems automatically filter “spam” into a separate folder. The filtering process
is typically based on a “spam list” that identifies spam when email is loaded into your inbox.
In this assignment I'm going to create a C++ program that is able to load a spam list, display
the contents of a spam list,check a single email address to see if it’s spam, filter an email list
and output the resulting emails to a file.
 */ 


#include <iostream>
#include <fstream>
#include <string>
#include "ourvector.h"
using namespace std;

/*---------------------------------------------------------------------
 * This boolean will be used for my binary seach. Its purpose is to reduce
 * the ammount of steps needed to find a particulat string within the chosen file.
 * In this case, I will be using it to check if a particular email if it would be
 * considered spam or not.
 * 
 * I also want to mention that I used code from last semester, for CS141.
 */
bool binarySearch(ourvector<string> &emailList, string userInput){
    int low = 0;
    int mid;
    int high = emailList.size() - 1;
    int searchResult;
    
    while (low <= high){       //In this part, we will focus on checking the
        mid = (low + high)/2;  //value that is in the middle of the list
        searchResult = userInput.compare(emailList[mid]);
        
        if (searchResult == 0){ //If the value we are looking for is in the middle
            return true;        // of the string, then we will return 'true'
            }                   // and the search ends.
        
        else if (searchResult < 0){ 
            high = mid - 1;     //If we cant find the "email" we need, then we split 
            }                   // the file in two again and continue doing that process
                                // until we find what we need.
        else {
            low = mid + 1;
            }
    } // closing while-loop
    return false;
}//closing binarySearch function

//---------------------------------------------------------------------
/*
 * This is my load function. Its purpose is to 'load' any of the three spamlist
 * files given for this assignment. In this function, I open the spamlist file
 * of the users choice into a vector. After looping though the list, making sure
 * that there are no errors, we push back that information into the vector and 
 * compare it with the next two functions that will check and filter any spam. 
 * Also, everytime we 'load' a spamist, we clear the vector before we reload.
 */
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
//This function will loop through the vector. I decided to use a for loop that
//will increment the value of int i everytime the loop reaches an end. As i
//increments in value, we can print out what is at the vectors position at i.
void displayFile(ourvector<string> &emailList){
    int vectorSize = emailList.size();     // I assigned vectorSize with the number of eements inside of the vector
    for (int i = 0; i < vectorSize; i++){
        cout << emailList.at(i) << endl;   // This prints out every element inside of the vector
    }
    cout << endl;
}

//---------------------------------------------------------------------
/* This boolean functions is what is going to return if the 'email' you want to check
 * is found withing the spam list you loaded eariler. It is designed to use Binary Search
 * to find weather or not the email is spam. 
 */
bool check(ourvector<string> &emailList, string userInput ){   //The parameters of this function are the spamlist & the email we want to check
    string username;
    string domain;
    string updatedUserInput;
    string userInputWithAsteric;
        
    size_t pos = userInput.find("@");       //In this section f the function, I manipulate the given 'email'
    username = userInput.substr(0, pos);    // into the same format the emails are displayed in the spamlist.
    domain = userInput.substr(pos + 1);     // username & domain are sub-strings of the given email by the user.
                                            // username starts from the firs character all the wat to the "@".
    updatedUserInput = domain + ":" + username;  //domain starts from the next caracter after "@".
    userInputWithAsteric = domain + ":*";
        
    if (binarySearch(emailList, updatedUserInput) == true    //If the given email is found in the spamlist, return 'true'.
        || binarySearch(emailList,userInputWithAsteric )){
            return true;
            }
    return false;  //If the email is not found within the spamist, automatically return false.
    cout << endl;
}

//---------------------------------------------------------------------
/* This is my filter function. Probably the trickiest part of the entire program.
 * Its function is to check every single email from an email file the user wants to open.
 * After that fle is open, it loops though the file to see if any of emails are found
 * withing the the spamlist the user loaded eariler.
 * 
 * After the function is done with checking every single email found in the file, comparing
 * it with the given spamlist, it will crate a new file with all the non-spam emails 
 * that were found. However, it wont just be the non-spam emails. It will also contain the 
 * msgID and the subject of such email. 
 */ 
void filter(ourvector<string> &emailList, string userInput, string newFile){
    ifstream inFS;
    string email;
    inFS.open(userInput);  //This opens the email file we want to compare with the spamlist
    int msgID;  // this will be used to extrat the msgID of suche line
    string subject; //this will be used to extract the subect that follows the email
    int numProcessed = 0;   
    int spamProcessed = 0;       //numProcessed & spamProcessed will be the numbers we need to see howmany emails
                                 //we processed and the number of emails that will be found in the new file
    ofstream outfile(newFile);   //This is what we use to create the new file with the non spam emails
    
    //Verifying that the file opens correctly
    if(!inFS.is_open()){
        cout << "**Error, unable to open '" << userInput <<"'"<< endl;
        return;
        } // closing if statement
    
    while (!inFS.eof()){ // This will loop through the file
        inFS >> msgID;   //Extracting msgID from file
        inFS >> email;   //Extracting the email
        getline(inFS, subject); //extracting all that information from the line
        if (!inFS.fail()){  //checking if there are no error within the file
           if (check(emailList, email) == false){ //If the email we are checking is NOT spam
            outfile << msgID << " " << email << subject << endl; //We put the NON-spam emails inside of the new file
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
/* This function is going to be where all the program happens, basically. Its two parameters are going to be
 * the vector we want to use to load any given spamlist, and the input given by the user.
 * This is where all the other functions are going to be called. 
 * This is the only function that will be used inside of main().
 */

void displayOptions( ourvector<string> &myVals, string &userInput1){
    string userInput2;
    string userInput3;
    
    while (true){                                  //I used a while(true) lop to make it endless
        cout << "Enter command or # to exit> ";    // untl the user inputs a "#".
        cin >> userInput1;                         // if a user inputs a "#", then the program stops running.
        
        while (userInput1 != "#") { //Until the user decides to stop the program from running
           
            if (userInput1 == "load"){  //If the user types in the word "load"
                cin >> userInput2;      // then the user is also required to input a second string
                loadFile(myVals,userInput2);  //The user's second sting will be the spamlist that will be loaded into the vector
                break;  //After a function completed loding the spamlist into the vector, we want to go back into the initial part
                }       //of the program, where we can call other functions.
            
            if (userInput1 == "display"){ //If the user inputs "display", no other strings are needed to be input.
                displayFile(myVals);      // It just displays whatever spamlist was recently loaded into the vector.
                break;
                }
            
            if (userInput1 == "check"){                  //if the user inputs "check", then a secod string is required.
                cin >> userInput2;
                if (check(myVals, userInput2) == true) {   // The second string would be the email the user wants to check if its spam or not.
                    cout << userInput2 << " is spam" << endl;  //If the return value is true, the we print "its spam"
                    cout << endl;
                    }
                
                else {
                    cout << userInput2 << " is not spam" << endl;  //if the return value is false, then we print "ot spam"
                    cout << endl;
                    }
                break;
                }
            
            if (userInput1 == "filter"){               //if the user types "filter", then two aditional strings are required
                cin >> userInput2 >> userInput3;
                filter(myVals, userInput2, userInput3);  //The two aditional strings would be the name of the file we inted to open
                cout<< endl;                             // and the name of the new file we intend to create
                break;
                }
            
            else{
                cout << "**invalid command" << endl;  // If the user maes any typo's the program cant recognize, 
                cout << endl;                         // Then ""**invalid command"" would be printed.
                break;
                }

            } // closing while loop
        
    if (userInput1 == "#"){  //If user types "#", then the program stops running.
            return; //returns to main()
            }
        }//closing while(true)
    } // closing function


//---------------------------------------------------------------------
//This contains all the above.
int main(){
    string userInput1;
    ourvector <string> myVals;
    
    cout << "** Welcome to spam filtering app **" << endl;
    cout << endl;

        displayOptions(myVals, userInput1);
        
    return 0;
}
