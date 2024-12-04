//--------------------------------------------------------------------------- Header files --------------------------------------------------------------------
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <windows.h>
#include <conio.h>

using namespace std;
struct student
{
    string name;
    string fatherName;
    int marks;
    string CNIC;
    string phoneNo;
    bool flag;
};
struct rooms
{
    int achieveRoom;
    bool roomFlag;
};
struct accounts
{
    string userName;
    string password;
    bool accountFlag;
};
struct dues
{
    double HosteliteDues;
    bool assignDues;
    bool duesFlag;
};
struct complains
{
    string complain;
    bool cmpFlag;
};

//--------------------------------------------------------------------Functions ---------------------------------------------------------
void header();      // Display HMS
void admin();       // Display Administrator
void admin1();      // Display Manage record
void admin2();      // Display Accounts
void admin3();      // Display  lists
void applyHostel(); // Display  Apply hostel veiw
void userMenu();    // Display  hostelite

//--------------------Manage Records--> functions------
void addRecord(student addStudent[], int &addCounter, int &MAX_AddSIZE, int apCounter);
void deleteRecord(student addStudent[], rooms assignRoom[], accounts accountsAssign[], int &MAX_AddSIZE, int removeRecord, int &addCounter, int &Rcounter, int &uCounter);
void updateRecord(student addStudent[], int addCounter, rooms assignRoom[], int editRecord, int Rcounter, int MAX_AddSIZE);
void RoomAssign(rooms assignRoom[], student addStudent[], student applyStudent[], int addCounter, int &Rcounter, int &apCounter, int &MAX_AddSIZE);
//-------------Accounts ---->Fumctions--------------
void CreatAccount(accounts accountsAssign[], rooms assignRoom[], int &uCounter, int addCounter, int Rcounter, int UpdateAccount, int &MAX_AddSIZE);
void deleteAccount(accounts accountsAssign[], rooms assignRoom[], student addStudent[], int &MAX_AddSIZE, int removeAccount, int &uCounter, int addCounter, int Rcounter);
void updateAccount(accounts accountsAssign[], rooms assignRoom[], int UpdateAccount, int &uCounter, int addCounter, int &MAX_AddSIZE, int Rcounter);
//--------------Lists ----->Functions-------------
void viewHosteliteApplications(student applyStudent[], int apCounter, int &MAX_ApplySize);
void currentRecordList(rooms assignRoom[], student addStudent[], dues duesOfstudent[], int addCounter, int MAX_AddSIZE);
// Apply for hostel ---> functions-----------
void HostelInformation();
void applyHostelApplication(student applyStudent[], int &apCounter, int MAX_ApplySize);
// Hostelite------>Functions-----------
void veiwStatus(accounts accountsAssign[], rooms assignRoom[], student addStudent[], dues duesOfstudent[], string pwd, string user, int addCounter, int &MAX_AddSIZE);
void payDues(accounts accountsAssign[], rooms assignRoom[], dues duesOfstudent[], double payment, student addStudent[], string pwd, string user, int addCounter, int &MAX_AddSIZE);
void saveCurrentRecordList(rooms assignRoom[], student addStudent[], dues duesOfstudent[], int addCounter, int MAX_AddSIZE);
void loadData(rooms assignRoom[], student addStudent[], int MAX_AddSIZE, dues duesOfstudent[], int &addCounter, int &Rcounter);
void applylistDataRecord(student applyStudent[], int apCounter, int MAX_ApplySize);
void loadapplylistDataRecord(student applyStudent[], int &apCounter, int MAX_ApplySize);
void loadAccountsRecord(accounts accountsAssign[], complains stComplain[], int MAX_AddSIZE, int &uCounter, int &cmpCounter);
void saveAccountsRecord(accounts accountsAssign[], complains stComplain[], int MAX_AddSIZE, int uCounter, int cmpCounter);

//-----------input validation for Student Name & Father Nmae------------
bool isAlphabet(string name)
{
    for (char c : name)
    {
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) && (c != ' ' || !((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z'))))
        { // allow alphabets and spaces and first character must be alphabet
            return false;
        }
    }
    return true;
}

//-----------input validation for Student Marks-----------
bool validMarks(int Marks)
{

    if (!(Marks >= 0 && Marks <= 400))
    { // allow alphabets and spaces
        return false;
    }

    return true;
}

//-----------input validation for Studrnt CNIC------------
bool checkValidCNIC(string Cnic)
{
    int digitCounter = 0;

    for (char c : Cnic)
    {
        if ((c >= '0' && c <= '9') && Cnic[0] == '3')
        {
            digitCounter++; // Count digits
        }
        else
        {
            return false; // Invalid character found
        }
    }

    // check the cnic contain  13 digits
    return digitCounter == 13;
}
//-----------input validation for Student Phone Number------------
bool checkValidContact(string phoneNo)
{
    int digitCounter = 0;

    for (char c : phoneNo)
    {
        if ((c >= '0' && c <= '9') && phoneNo[0] == '0' && phoneNo[1] == '3')
        {
            digitCounter++; // count digits
        }
        else
        {
            return false; // Invalid character found
        }
    }

    // check the phone no contain  11 digits
    return digitCounter == 11;
}
// This function is for colour the text on console
void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void initializeAddSt(student addStudent[], int size)
{
    for (int i = 0; i < size; i++)
    {
        addStudent[i] = {"nv", "nv", 0, "nv", "nv", false};
    }
}
void initializeApplySt(student applyStudent[], int size)
{
    for (int i = 0; i < size; i++)
    {
        applyStudent[i] = {"nv", "nv", 0, "nv", "nv", false};
    }
}
void initializeRoomAssign(rooms assignRoom[], int size)
{
    for (int i = 0; i < size; i++)
    {
        assignRoom[i] = {0, false};
    }
}
void initializeAccountsSt(accounts accountsAssign[], int size)
{
    for (int i = 0; i < size; i++)
    {
        accountsAssign[i] = {"nv", "nv", false};
    }
}
void initializeduesOfSt(dues duesOfstudent[], int size)
{
    for (int i = 0; i < size; i++)
    {
        duesOfstudent[i] = {0.0, false, false};
    }
}
void initializeComplainOfSt(complains stComplain[], int size)
{
    for (int i = 0; i < size; i++)
    {
        stComplain[i] = {"nv", false};
    }
}

//----------------------! Main Function !------------
int main()
{
    // ---------------------------daclaration ----------------------
    system("cls");
    int MAX_AddSIZE = 100;
    int MAX_ApplySize = 100;
    student addStudent[MAX_AddSIZE];
    student applyStudent[MAX_ApplySize];
    rooms assignRoom[MAX_AddSIZE];
    accounts accountsAssign[MAX_AddSIZE];
    dues duesOfstudent[MAX_AddSIZE];
    complains stComplain[MAX_AddSIZE];

    initializeAddSt(addStudent, MAX_AddSIZE);
    initializeApplySt(applyStudent, MAX_ApplySize);
    initializeRoomAssign(assignRoom, MAX_AddSIZE);
    initializeAccountsSt(accountsAssign, MAX_AddSIZE);
    initializeduesOfSt(duesOfstudent, MAX_AddSIZE);

    ofstream currentRlist;
    ifstream currentRlistIn;

    int option = 0; // for selecting the switches menu
    string user = "nv";
    string pwd = "nv";
    int editRecord = 0;
    int removeRecord = 0;
    int paymentRecord = 0;
    int removeAccount = 0;
    int UpdateAccount = 0;
    int loggedInUserType = -20; // 1 for seneior wardon , 2 for apply for hostel ,3 for user
    int apCounter = 0;          // apply student counter
    int addCounter = 0;         // add student counter
    int Rcounter = 0;           // Room assign counter
    int uCounter = 0;           // username counter
    int cmpCounter = 0;         // complain counter
    int sortingTemp = 0;        // sorting Data variable
    double payment = 0.0;       // pay hostel dues
    int complainLength = 60;    // complain submission length

    int hostelFee = 0; // hostel fee
    int extraCharges = 0;
    bool roomFound = false; // temporary flag for finding room
    bool ispresent = true;
    cout.unsetf(ios::left);
    cout.unsetf(ios::right);
    loadapplylistDataRecord(applyStudent, apCounter, MAX_ApplySize);
    loadData(assignRoom, addStudent, MAX_AddSIZE, duesOfstudent, addCounter, Rcounter);
    loadAccountsRecord(accountsAssign, stComplain, MAX_AddSIZE, uCounter, cmpCounter);

    do
    {
        // system("cls");
        header();
        setColor(14);
        cout << endl;
        cout << left << setw(30) << "\t\t\t\t\t\tChoose the desired option\n";
        cout << endl;
        //----------------main menu of HMS---------
        cout << endl;
        cout << left << setw(5) << ""
             << setw(30) << "\t\t\t\t\t\t1. Administrator Login" << setw(30) << "2. Apply for Hostel" << endl
             << endl;
        cout << left << setw(5) << ""
             << setw(30) << "\t\t\t\t\t\t3. Hostelite  Login" << setw(30) << "0. Exit" << endl;
        cout << endl;
        cout << "\t\t\t\t\t\t---------------------------------------------------------------------------" << endl;
        cout << endl;

        cout.unsetf(ios::left);
        cout.unsetf(ios::right);

        cout << "\t\t\t\t\t\t\t\t" << "\tChoose an option (0-3): ";

        while (true)
        {
            cin >> option;

            // Check if the input is valid
            if (cin.fail())
            {
                cin.clear();           // Clear the error
                cin.ignore(255, '\n'); // remove invalid input
                cout << "\t\t\t\t\t\t\t\tInvalid input!! Please enter a number between 0 and 3.\n";
            }
            else if (option < 0 || option > 3)
            {
                cout << "\t\t\t\t\t\t\t\tOption out of range! Please enter a number between 0 and 3.\n";
            }
            else
            {
                // correct  input
                break;
            }
        }

        cout << endl;
        cout << endl;

        // this switch for username or password
        switch (option)
        {
            // for senior warden
        case 1:
            cout << "\t\t\t\t\t\t Enter the username : ";
            cin >> user;
            cout << "\t\t\t\t\t\t Enter the password : ";
            cin >> pwd;
            if (user == "Admin" && pwd == "123")
            {
                loggedInUserType = 1;
            }
            else
            {
                loggedInUserType = -20;
            }
            break;

        case 2:
            //----------- FOR hostel apply
            if (option == 2)
            {
                loggedInUserType = 2;
            }
            else
            {
                loggedInUserType = -20;
            }
            break;

        case 3:
            // -----------For hostelite
            cout << "\t\t\t\t\t\t Enter the username : ";
            cin >> user;
            cout << "\t\t\t\t\t\t Enter the password : ";
            cin >> pwd;

            for (int k = 0; k < MAX_AddSIZE; k++)
            {
                if (accountsAssign[k].userName == user && accountsAssign[k].password == pwd && accountsAssign[k].accountFlag == true)
                {

                    loggedInUserType = 3;
                    ispresent = false;
                    break;
                }
            }
            if (ispresent)
            {
                loggedInUserType = -20;
            }
            break;

        case 0:
            loggedInUserType = -30;
            setColor(2);
            cout << "\t------------------------------- Thank you for choosing our system!---------------------------";
            break;
        default:
            setColor(4);
            cout << "\t\t\t\t\t Invalid option............ ";
            Sleep(300);
            break;
        }
        if (loggedInUserType == 1) // seneior warden access
        {
            do
            {
                cout << endl;
                system("cls");
                header();

                admin();
                cout << endl;

                cout << "\t\t\t\t\t\t\t\t" << "\tChoose an option (0-4): ";

                while (true)
                {
                    cin >> option;

                    // Check if the input is valid
                    if (cin.fail())
                    {
                        cin.clear();           // Clear the error
                        cin.ignore(255, '\n'); // remove invalid input
                        cout << "\t\t\t\t\t\t\t\tInvalid input!! Please enter a number between 0 and 4.\n";
                    }
                    else if (option < 0 || option > 4)
                    {
                        cout << "\t\t\t\t\t\t\t\tOption out of range! Please enter a number between 0 and 4.\n";
                    }
                    else
                    {
                        // correct  input
                        break;
                    }
                }

                cout.unsetf(ios::left);
                cout.unsetf(ios::right);

                switch (option)
                {
                case 1:
                    do
                    {
                        cout << endl; // Manage Records
                        system("cls");
                        header();

                        admin1();
                        cout << endl;
                        cout << "\t\t\t\t\t\t\t\t" << "\tChoose an option (0-4): ";

                        while (true)
                        {
                            cin >> option;

                            // Check if the input is valid
                            if (cin.fail())
                            {
                                cin.clear();           // Clear the error
                                cin.ignore(255, '\n'); // remove invalid input
                                cout << "\t\t\t\t\t\t\t\tInvalid input! Please enter a number between 0 and 4.\n";
                            }
                            else if (option < 0 || option > 4)
                            {
                                cout << "\t\t\t\t\t\t\t\tOption out of range! Please enter a number between 0 and 4.\n";
                            }
                            else
                            {
                                // correct  input
                                break;
                            }
                        }
                        cout.unsetf(ios::left);
                        cout.unsetf(ios::right);

                        switch (option)
                        {
                        case 1:
                            cout << endl;
                            // --------------Function call for adding record -----------
                            addRecord(addStudent, addCounter, MAX_AddSIZE, apCounter);

                            Sleep(1000);
                            system("cls");

                            break;
                        case 2:
                            cout << endl;
                            // --------------Function call for Assigning room servant and room -----------

                            RoomAssign(assignRoom, addStudent, applyStudent, addCounter, Rcounter, apCounter, MAX_AddSIZE);

                            Sleep(1000);
                            system("cls");

                            break;
                        case 3:
                            cout << endl;
                            // --------------Function call for Deleting  record -----------
                            deleteRecord(addStudent, assignRoom, accountsAssign, MAX_AddSIZE, removeRecord, addCounter, Rcounter, uCounter);

                            Sleep(1000);
                            system("cls");
                            break;
                        case 4:
                            //-------Function call for Updating record -----------
                            cout << endl;
                            updateRecord(addStudent, addCounter, assignRoom, editRecord, Rcounter, MAX_AddSIZE);

                            Sleep(1000);
                            system("cls");
                            break;
                            cout << endl;

                        case 0:
                            cout << "\t\t\t\t\t------------------------->Administrator is exit in Manage record " << endl;
                            Sleep(1000);
                            system("cls");

                            break;

                        default:
                            cout << "\t\t\t\t\t\t\t\t\t-----------------> Invalid option ";
                            Sleep(1000);
                            system("cls");
                            break;
                        }
                    } while (option != 0);
                    option = -1; //----------! this statment is to make sure. that do not exit from outer loop !-----------

                    break;
                case 2:
                    do
                    {
                        // --------------------Accounts-----------------
                        system("cls");
                        header();
                        admin2();
                        cout << endl;
                        cout << "\t\t\t\t\t\t\t\t" << "\tChoose an option (0-3): ";

                        while (true)
                        {
                            cin >> option;

                            // Check if the input is valid
                            if (cin.fail())
                            {
                                cin.clear();           // Clear the error
                                cin.ignore(255, '\n'); // remove invalid input
                                cout << "\t\t\t\t\t\t\t\tInvalid input! Please enter a number between 0 and 3.\n";
                            }
                            else if (option < 0 || option > 3)
                            {
                                cout << "\t\t\t\t\t\t\t\tOption out of range! Please enter a number between 0 and 3.\n";
                            }
                            else
                            {
                                // correct  input
                                break;
                            }
                        }

                        cout.unsetf(ios::left);
                        cout.unsetf(ios::right);

                        switch (option)
                        {
                        case 1:
                            cout << endl;
                            // --------------Function call for Creating accounts -----------

                            CreatAccount(accountsAssign, assignRoom, uCounter, addCounter, Rcounter, UpdateAccount, MAX_AddSIZE);

                            break;
                        case 2:
                            cout << endl;
                            // --------------Function call for Deleting accounts -----------
                            deleteAccount(accountsAssign, assignRoom, addStudent, MAX_AddSIZE, removeAccount, uCounter, addCounter, Rcounter);

                            break;
                        case 3:
                            cout << endl;
                            // --------------Function call for updating accounts -----------
                            updateAccount(accountsAssign, assignRoom, UpdateAccount, uCounter, addCounter, MAX_AddSIZE, Rcounter);

                            break;

                        case 0:
                            cout << "\t\t\t----------------------------->Administrator is exit in Accounts " << endl;
                            Sleep(1000);
                            system("cls");

                            break;

                        default:
                            cout << "\t\t\t\t\t\t\t\t\t-----------------> Invalid option ";
                            Sleep(1000);
                            system("cls");
                            break;
                        }
                    } while (option != 0);
                    option = -1; //----------! this statment is to make sure0. that do not exit from outer loop !-----------

                    break;
                case 3:
                    do
                    {
                        // --------------------Lists
                        system("cls");
                        header();
                        admin3();
                        cout << endl;
                        cout << "\t\t\t\t\t\t\t\t" << "\tChoose an option (0-3): ";

                        while (true)
                        {
                            cin >> option;

                            // Check if the input is valid
                            if (cin.fail())
                            {
                                cin.clear();           // Clear the error
                                cin.ignore(255, '\n'); // remove invalid input
                                cout << "\t\t\t\t\t\t\t\tInvalid input! Please enter a number between 0 and 3.\n";
                            }
                            else if (option < 0 || option > 3)
                            {
                                cout << "\t\t\t\t\t\t\t\tOption out of range! Please enter a number between 0 and 3.\n";
                            }
                            else
                            {
                                // correct  input
                                break;
                            }
                        }
                        cout.unsetf(ios::left);
                        cout.unsetf(ios::right);

                        switch (option)
                        {
                        case 1:
                            cout << endl;
                            // --------------Function call for view Hostelite Applications -----------
                            viewHosteliteApplications(applyStudent, apCounter, MAX_ApplySize);

                            break;
                        case 2:
                            cout << endl;
                            // --------------Function call for  current Record List -----------
                            currentRecordList(assignRoom, addStudent, duesOfstudent, addCounter, MAX_AddSIZE);

                            break;
                        case 3:
                            system("cls");
                            header();
                            admin3();
                            if (cmpCounter == 0)
                            {
                                cout << "\t\t\t\t\t\tNo Complain was submitted yet......" << endl;
                                break;
                            }
                            for (int i = 0; i < MAX_AddSIZE; i++)
                            {
                                if (stComplain[i].cmpFlag)
                                {
                                    cout << "\t\t\t\t\t\t\t\t" << accountsAssign[i].userName << "  CAN submit the complain:  " << stComplain[i].complain << endl;
                                }
                            }
                            cout << endl;
                            cout << "\t\t\t\t\t\t\t\t -------------> Hostelite " << endl;
                            cout << "\t\t\t\t\t\t\t\tKindly press any key...";
                            getch();
                            break;
                        case 0:
                            cout << "\t\t\t\t\t\t\t\t----------------------------->Administrator is exit in Lists.... " << endl;
                            Sleep(1000);
                            system("cls");

                            break;

                        default:
                            cout << "\t\t\t\t\t\t\t\t\t-----------------> Invalid option ";
                            Sleep(1000);
                            system("cls");
                            break;
                        }
                    } while (option != 0);
                    option = -1; //----------! this statment is to make sure0. that do not exit from outer loop !-----------

                    break;
                case 4:
                    // ----------------------------------Pay Dues---------------------
                    system("cls");
                    header();
                    cout << endl;
                    cout << endl;
                    cout << "\t\t\t\t\t\t\t\tEnter the Room no for student dues : ";
                    while (true)
                    {
                        cin >> paymentRecord;
                        if (cin.fail())
                        {
                            cin.clear();           // Clear the error
                            cin.ignore(255, '\n'); // remove invalid input
                            cout << "\t\t\t\t\t\t\t\tInvalid input!! Please enter a numeric value:";
                            continue;
                        }
                        if (paymentRecord >= 1 && paymentRecord < MAX_AddSIZE) // enter room no in the given range
                        {
                            break;
                        }
                        else
                        {
                            cout << "\n\t\t\t\t\t\t\t\tInvalid room no . Enter the Room no again : ";
                        }
                    }

                    roomFound = false; // check the room was found  if it true then the desired room is ocuupied

                    for (int k = 0; k < MAX_AddSIZE; k++)
                    {
                        if (assignRoom[k].achieveRoom == paymentRecord) // only the given room student  deposite the dues
                        {
                            roomFound = true;
                            if (assignRoom[k].roomFlag)
                            {
                                cout << "\t\t\t\t\t\t\t\tKindly enter the dues according to the respective Room no : ";
                                while (true)
                                {
                                    cin >> hostelFee;
                                    if (cin.fail())
                                    {
                                        cin.clear();           // Clear the error
                                        cin.ignore(255, '\n'); // remove invalid input
                                        cout << "\t\t\t\t\t\t\t\tInvalid dues! Please Enter the dues again: \n";
                                    } // input the hostel fee
                                    if (hostelFee >= 6000 && hostelFee <= 15000) // enter the dues in the respective range
                                    {
                                        break;
                                    }
                                    else
                                    {
                                        cout << "\t\t\t\t\t\t\t\tEnter the dues according to the range(6000 to 15000) : ";
                                    }
                                }
                                cout << "\t\t\t\t\t\t\t\tKindly enter the other charges : "; // enter the extra dues of the hostile
                                while (true)
                                {
                                    cin >> extraCharges;
                                    if (cin.fail())
                                    {
                                        cin.clear();           // Clear the error
                                        cin.ignore(255, '\n'); // remove invalid input
                                        cout << "\t\t\t\t\t\t\t\tInvalid dues! Please Enter the dues again: \n";
                                    }
                                    if (extraCharges >= 500 && extraCharges <= 5000) // validity for extra charges
                                    {
                                        break;
                                    }
                                    else
                                    {
                                        cout << "\t\t\t\t\tEnter the extra charges according to the range(500 to 5000) : ";
                                    }
                                }

                                duesOfstudent[k].HosteliteDues = hostelFee + extraCharges; //  total dues of the hostelite
                                duesOfstudent[k].assignDues = true;
                                break;
                            }
                            else
                            {
                                cout << "\t\t\t\t\t\t\t\tRoom was not occupied......." << endl;
                            }
                        }
                    }
                    if (!roomFound)
                    {
                        cout << "\t\t\t\t\t\t\t\tRoom number not found or not assigned yet." << endl;
                    }
                    Sleep(1000);

                    break;
                case 0:
                    cout << "\t\t\t\t\t\t------------------->Administrator is exit in dues phase " << endl;
                    Sleep(1000);
                    system("cls");

                    break;

                default:
                    cout << "\t\t\t\t\t\t\t\t\t-----------------> Invalid option ";
                    Sleep(1000);
                    system("cls");
                    break;
                }
            } while (option != 0);
            option = -1; //----------! this statment is to make sure0. that do not exit from outer loop !-----------
        }
        else if (loggedInUserType == 2) // Applicants can access the this block
        {
            do
            {
                system("cls");
                header();
                applyHostel(); // -----------Display Apply for Hostel----------
                cout << endl;
                cout << "\t\t\t\t\t\t\t\t" << "\tChoose an option (0-3): ";

                while (true)
                {
                    cin >> option;

                    // Check if the input is valid
                    if (cin.fail())
                    {
                        cin.clear();           // Clear the error
                        cin.ignore(255, '\n'); // remove invalid input
                        cout << "\t\t\t\t\t\t\t\tInvalid input! Please enter a number between 0 and 3.\n";
                    }
                    else if (option < 0 || option > 3)
                    {
                        cout << "\t\t\t\t\t\t\t\tOption out of range! Please enter a number between 0 and 3.\n";
                    }
                    else
                    {
                        // correct  input
                        break;
                    }
                }
                cout.unsetf(ios::left);
                cout.unsetf(ios::right);

                switch (option)
                {
                case 1:
                    cout << endl;
                    // --------------Function call for Veiw the Hostel information -----------

                    HostelInformation();
                    break;
                case 2:
                    cout << endl;
                    // --------------Function call for Applicants can apply for Hostel-----------

                    applyHostelApplication(applyStudent, apCounter, MAX_ApplySize);

                    break;
                case 3:
                    // --------------Function call for view Hostelite Applications -----------

                    viewHosteliteApplications(applyStudent, apCounter, MAX_ApplySize);
                    Sleep(2000);

                    break;

                case 0:
                    cout << "\t\t\t\t\t----------------------> Applicants Exit the Apply body " << endl;
                    Sleep(1000);
                    system("cls");
                    break;

                default:
                    cout << "\t\t\t\t\t\t\t\t\t-----------------> Invalid option ";
                    Sleep(1000);
                    system("cls");
                    break;
                }

            } while (option != 0);
            option = -1; //----------! this statment is to make sure that do not exit from outer loop !-----------
        }
        else if (loggedInUserType == 3) // User access
        {
            do
            {
                system("cls");
                header();
                userMenu(); // Display the Hostelite on screen
                cout << "\t\t\t\t\t\t\t\t" << "\tChoose an option (0-3): ";

                while (true)
                {
                    cin >> option;

                    // Check if the input is valid
                    if (cin.fail())
                    {
                        cin.clear();           // Clear the error
                        cin.ignore(255, '\n'); // remove invalid input
                        cout << "\t\t\t\t\t\t\t\tInvalid input! Please enter a number between 0 and 3.\n";
                    }
                    else if (option < 0 || option > 3)
                    {
                        cout << "\t\t\t\t\t\t\t\tOption out of range! Please enter a number between 0 and 3.\n";
                    }
                    else
                    {
                        // correct  input
                        break;
                    }
                }

                cout.unsetf(ios::left);
                cout.unsetf(ios::right);

                switch (option)
                {
                case 1:
                    cout << endl;
                    // --------------Function call for Hostelilte can veiw status-----------
                    veiwStatus(accountsAssign, assignRoom, addStudent, duesOfstudent, pwd, user, addCounter, MAX_AddSIZE);

                    break;
                case 2:
                    for (int i = 0; i < MAX_AddSIZE; i++)
                    {
                        if (accountsAssign[i].userName == user && accountsAssign[i].password == pwd || accountsAssign[i].accountFlag == true)
                        {

                            if (accountsAssign[i].accountFlag == true)
                            {
                                while (true)
                                {
                                    cout << "\t\t\t\t\tKindly enter your complain in more precise form : ";
                                    cin.ignore();
                                    getline(cin, stComplain[i].complain);
                                    if ((stComplain[i].complain).length() <= complainLength)
                                    {
                                        stComplain[i].cmpFlag = true;
                                        cmpCounter++;
                                        cout << "\t\t\t\t\t\t Your complain is submitted........" << endl;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    Sleep(1000);
                    break;
                case 3:
                    cout << endl;
                    // --------------Function call forHostelilte can pay their dues-----------
                    payDues(accountsAssign, assignRoom, duesOfstudent, payment, addStudent, pwd, user, addCounter, MAX_AddSIZE);

                    break;

                case 0:

                    cout << "\t\t\t\t\t\t----------------------> Hostelite is logged out" << endl;
                    Sleep(1000);
                    system("cls");
                    break;

                default:
                    cout << "\t\t\t\t\t\t\t\t\t-----------------> Invalid option ";
                    Sleep(1000);
                    system("cls");
                    break;
                }
            } while (option != 0);
            option = -1; //----------! this statment is to make sure that do not exit from outer loop !-----------
        }
        else if (loggedInUserType == -20) // invalid entry !!!!!!!
        {
            cout << "You have entered invalid Credentials!!!" << endl;
            Sleep(1000);
        }
    } while (option != 0);
    applylistDataRecord(applyStudent, apCounter, MAX_ApplySize);
    saveCurrentRecordList(assignRoom, addStudent, duesOfstudent, addCounter, MAX_AddSIZE);
    saveAccountsRecord(accountsAssign, stComplain, MAX_AddSIZE, uCounter, cmpCounter);
}
//------------------------------------ End of main function----------------------<

// ----------------Display header menu ----------------------!
void header()

{
    setColor(11);
    cout << endl;
    cout << right << setw(70) << "\t\t\t\t\t\t\t /$$   /$$ /$$      /$$  /$$$$$$  \n";
    cout << right << setw(70) << "\t\t\t\t\t\t\t| $$  | $$| $$$    /$$$ /$$__  $$\n";
    cout << right << setw(70) << "\t\t\t\t\t\t\t| $$  | $$| $$$$  /$$$$| $$  \\__/ \n";
    cout << right << setw(70) << "\t\t\t\t\t\t\t| $$$$$$$$| $$ $$/$$ $$|  $$$$$$  \n";
    cout << right << setw(70) << "\t\t\t\t\t\t\t| $$__  $$| $$  $$$| $$ \\____  $$\n";
    cout << right << setw(70) << "\t\t\t\t\t\t\t| $$  | $$| $$\\  $ | $$ /$$  \\ $$\n";
    cout << right << setw(70) << "\t\t\t\t\t\t\t| $$  | $$| $$ \\/  | $$|  $$$$$$/\n";
    cout << right << setw(70) << "\t\t\t\t\t\t\t|__/  |__/|__/     |__/ \\______/ \n";
    cout << right << setw(70) << "\t\t\t\t\t\t                                 \n";
    cout << right << setw(70) << "\t\t\t\t\t\t ****************************************************************************************************\n";
    cout << right << setw(70) << "\t\t\t\t\t\t ***************************-----!```HOSTEL MANAGMENT SYSTEM```!-----********************************\n";
    cout << right << setw(70) << "\t\t\t\t\t\t ****************************************************************************************************\n";
    setColor(7);
}

// --------------------This Function is defined for Manage Record  Display on screen

void admin1()
{
    setColor(4);

    cout << "\t\t\t\t\t -------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t                                                    Manage Record                                          " << endl;
    cout << "\t\t\t\t\t -------------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t"
            "---------! Pick the option that best suits your needs.---------!"
         << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t"
            "\t Manage Record"
         << endl;
    cout << "\t\t\t\t\t\t\t\t------------------------------------------------------------" << endl;

    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 1. Add Record" << endl;
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 2. RoomaAssign " << endl;
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 3. Delete Record" << endl;
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 4. Update Record" << endl;
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 0.Exit" << endl;

    cout << "\t\t\t\t\t\t\t\t------------------------------------------------------------" << endl;
}

// --------------------This Function is defined for Administrator Display on screen

void admin()
{
    setColor(12);

    cout << "\t\t\t\t\t -------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t                                                    Administrator                                          " << endl;
    cout << "\t\t\t\t\t -------------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t"
            "---------! Pick the option that best suits your needs.---------!"
         << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t"
            "\tHostelite System - Information & Assignment Menu"
         << endl;
    cout << "\t\t\t\t\t\t\t\t------------------------------------------------------------" << endl;

    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 1. Manage Record..." << endl;
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 2. Accounts... " << endl;
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 3. Lists..." << endl;
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 4. Payment info..." << endl;
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 0.Logout..." << endl;

    cout << "\t\t\t\t\t\t\t\t------------------------------------------------------------" << endl;
}

// --------------------This Function is defined for  Accounts...  Display on screen

void admin2()
{
    setColor(3);

    cout << "\t\t\t\t\t -------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t                                                    Accounts...                                          " << endl;
    cout << "\t\t\t\t\t -------------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t"
            "---------! Pick the option that best suits your needs.---------!"
         << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t"
            "\t Accounts..."
         << endl;
    cout << "\t\t\t\t\t\t\t\t------------------------------------------------------------" << endl;

    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 1. Create Account" << endl;
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 2. Delete Account" << endl;
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 3. Update Account" << endl;
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 0.Exit" << endl;

    cout << "\t\t\t\t\t\t\t\t------------------------------------------------------------" << endl;
}

// --------------------This Function is defined for Lists   Display on screen

void admin3()
{
    setColor(10);

    cout << "\t\t\t\t\t -------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t                                                    Lists...                                          " << endl;
    cout << "\t\t\t\t\t -------------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t"
            "---------! Pick the option that best suits your needs.---------!"
         << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t"
            "\tLists..."
         << endl;
    cout << "\t\t\t\t\t\t\t\t------------------------------------------------------------" << endl;

    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 1.Veiw Applicant list " << endl;
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 2. Veiw Current list " << endl;
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 3. Veiw General info.." << endl;
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 0.Exit" << endl;

    cout << "\t\t\t\t\t\t\t\t------------------------------------------------------------" << endl;
}

// --------------------This Function is defined for  Apply for Hostel Display on screen

void applyHostel()
{

    cout << "\t\t\t\t\t -------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t                                                Apply for Hostel                                         " << endl;
    cout << "\t\t\t\t\t -------------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t"
            "--------- Pick the option that best suits your needs.---------!"
         << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t" << left << setw(30) << " 1.Veiw Hostel information . " << endl;
    cout << "\t\t\t\t\t\t" << left << setw(30) << " 2.Registration " << endl;
    cout << "\t\t\t\t\t\t" << left << setw(30) << " 3.Veiw Application " << endl;
    cout << "\t\t\t\t\t\t" << left << setw(30) << " 0.exit." << endl;
}

// --------------------This Function is defined for  Hostelite Display on screen

void userMenu()
{

    cout << "\t\t\t\t\t -------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t                                               Hostelite                                       " << endl;
    cout << "\t\t\t\t\t -------------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t" << "---------! Pick the option that best suits your needs.---------!" << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 1.View status . " << endl;
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 2.Complaints . " << endl;
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 3.Pay dues . " << endl;
    cout << "\t\t\t\t\t\t\t\t" << left << setw(30) << " 0.exit ." << endl;
}

// --------------------This Function is defined for  Add record in the system.....

void addRecord(student addStudent[], int &addCounter, int &MAX_AddSIZE, int apCounter)
{
    bool isadded = false;
    if (apCounter == 0) // Check Applicants can apply for hostel
    {
        cout << "\t\t\t\t\t\t\t\tNo application is submit yet !! " << endl;
        return;
    }
    if (addCounter >= MAX_AddSIZE) //  check if Applicants reaches the total size of apply counter
    {
        cout << "\t\t\t\t\t\t No more students are added ! Rooms are full." << endl;
        return;
    }
    cin.ignore(255, '\n');
    for (int i = 0; i < MAX_AddSIZE; i++)
    {
        if (addStudent[i].name == "nv" && addStudent[i].fatherName == "nv" && addStudent[i].marks == 0 && addStudent[i].CNIC == "nv" && addStudent[i].phoneNo == "nv" && addStudent[i].flag == false)
        {
            cout << "\t\t\t\t\t\t\tKindly enter your Name: ";
            while (true)
            {
                getline(cin, addStudent[i].name); // Get the full name input

                // Check if the input is valid
                if (isAlphabet(addStudent[i].name))
                {
                    break; // Input is valid, exit the loop
                }
                else
                {
                    cout << "\t\t\t\t\t\t\tInvalid name. Please enter alphabetic characters only in name: ";
                }
            }

            cout << "\t\t\t\t\t\t\tKindly enter your Father Name: ";

            while (true)
            {
                getline(cin, addStudent[i].fatherName);

                if (isAlphabet(addStudent[i].fatherName))
                {
                    break;
                }
                else
                {
                    cout << "\t\t\t\t\t\tInvalid name. Please enter alphabetic characters only in name: ";
                }
            }

            cout << "\t\t\t\t\t\t\tKindly enter your marks: ";

            while (true)
            {
                cin >> addStudent[i].marks;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(255, '\n');
                    cout << "\t\t\t\t\t\t\tInvalid input!!.Kindly enter the numeric value(0 to 400):";
                    continue;
                }

                if (validMarks(addStudent[i].marks))
                {
                    break;
                }
                else
                {
                    cout << "\t\t\t\t\t\tInvalid name. Please enter marks in the given range(0 to 400) : ";
                }
            }
            cin.ignore();

            cout << "\t\t\t\t\t\t\tKindly enter your CNIC : ";

            while (true)
            {
                getline(cin, addStudent[i].CNIC);

                if (checkValidCNIC(addStudent[i].CNIC))
                {
                    break;
                }
                else
                {
                    cout << "\t\t\t\t\t\t\tInvalid CNIC! Please ensure it contains exactly 13 digits : ";
                }
            }

            cout << "\t\t\t\t\t\t\tKindly enter your phone number: ";

            while (true)
            {
                getline(cin, addStudent[i].phoneNo);

                if (checkValidContact(addStudent[i].phoneNo))
                {
                    break;
                }
                else
                {
                    cout << "\t\t\t\t\t\t\tInvalid phone no ! Please ensure it contains exactly 11 digits : ";
                }
            }
            addStudent[i].flag = true; // Administrator add the record
            isadded = true;
        }

        addCounter++;
        if (isadded)
        {
            cout << "Student added successfully!!" << endl;
            break;
        }
    }
}

// --------------------This Function is defined for  Delete record in the system.....

void viewHosteliteApplications(student applyStudent[], int apCounter, int &MAX_ApplySize)
{
    system("cls");
    header();
    if (apCounter == 0)
    {

        cout << "\t\t\t\t\t\t\tNo applications submitted yet." << endl;
        return;
    }

    cout << "************************************************************************************************************************************************************************************************************" << endl;
    cout << left << setw(30) << "Name" << left << setw(30) << "Father Name" << left << setw(30) << "Marks (Ecat)" << left << setw(30) << "CNIC" << left << setw(30) << "Contact NO" << endl;
    cout << "************************************************************************************************************************************************************************************************************" << endl;
    for (int i = 0; i < apCounter - 1; i++) // sorting the data in increasing order
    {
        for (int j = i + 1; j < apCounter; j++)
        {
            if (applyStudent[i].name != "nv")
            {
                if (applyStudent[j].marks > applyStudent[i].marks)
                {
                    student sortingTemp = applyStudent[j];
                    applyStudent[j] = applyStudent[i];
                    applyStudent[i] = sortingTemp;
                }
            }
        }
    }

    for (int j = 0; j < apCounter; j++)
    {
        if (applyStudent[j].flag == true && applyStudent[j].name != "nv" && applyStudent[j].fatherName != "nv" && applyStudent[j].CNIC != "nv" && applyStudent[j].phoneNo != "nv" && applyStudent[j].marks != 0) // Display only valid   entries
        {
            cout << left << setw(30) << applyStudent[j].name << left << setw(30)
                 << applyStudent[j].fatherName << left << setw(30) << applyStudent[j].marks
                 << left << setw(30) << applyStudent[j].CNIC << left << setw(30)
                 << applyStudent[j].phoneNo << endl;
        }
    }
    cout << "\t\t\t\t\t\t\t\tKindly press any key...";
    getch();
}

// --------------------This Function is defined for Applicants can view Hostel Information.....

void HostelInformation()
{
    system("cls");
    header();
    cout << endl;
    setColor(13);
    while (true)
    {

        int info = 1;
        cout << "\t\t\t\t\t\t\tHostel Setup for 50 Students:" << endl;
        cout << "\t\t\t\t\t\t\t--------------------------------------------------" << endl;
        cout << "\t\t\t\t\t\t\t1. Total of 50 rooms for 50 students." << endl;
        cout << "\t\t\t\t\t\t\t2. Each room servant is assigned to one room." << endl;
        cout << "\t\t\t\t\t\t\t3. Room Features:" << endl;
        cout << "\t\t\t\t\t\t\t   -> 1 fan and 2 bulbs for lighting." << endl;
        cout << "\t\t\t\t\t\t\t   -> Attached washroom shared between two rooms." << endl;
        cout << "\t\t\t\t\t\t\t   -> 1 cubet (small wardrobe) for storage." << endl;
        cout << "\t\t\t\t\t\t\t4. Common Amenities:" << endl;
        cout << "\t\t\t\t\t\t\t   -> Small playground for recreational activities." << endl;
        cout << "\t\t\t\t\t\t\t   -> TV room for entertainment and relaxation." << endl;
        cout << "\t\t\t\t\t\t\t5. Security:" << endl;
        cout << "\t\t\t\t\t\t\t   -> security guard for safety and surveillance." << endl;
        cout << "\t\t\t\t\t\t\t6. Each room is equipped with 1 bed for each student." << endl;
        cout << "\t\t\t\t\t\t\t7. Rooms are airy and well-ventilated for comfort." << endl;
        cout << "\t\t\t\t\t\t\t--------------------------------------------------" << endl;
        cout << "\t\t\t\t\t\t\tThe hostel provides a comfortable and engaging living space for all students." << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;

        while (true)
        {
            cout << "\t\t\t\t\t\t\tIf you read the information then " << endl;
            cout << "\t\t\t\t\t\t\t Enter 0 for exit : ";
            cin >> info;
            // Check if the input is valid
            if (cin.fail())
            {
                cin.clear();           // Clear the error
                cin.ignore(255, '\n'); // remove invalid input
                cout << "\t\t\t\t\t\tInvalid input! Please enter  0 for exit.\n";
            }
            else if (info < 0 || info > 0)
            {
                cout << "\t\t\t\t\t\tOption out of range! Please enter  0 for exit.\n";
            }
            else
            {
                // correct  input
                break;
            }
        }
        break; // break the outer loop...
    }
}

// --------------------This Function is defined for  applicants apply Hostel Application....

void applyHostelApplication(student applyStudent[], int &apCounter, int MAX_ApplySize)
{
    bool isApply = false;
    if (apCounter >= MAX_ApplySize)
    {
        cout << "\t\t\t\t\t\t\tNo more students can apply ! Applicants are full." << endl;
        return;
    }
    cin.ignore();

    // same validation as in adding phase
    for (int i = 0; i < MAX_ApplySize; i++)
    {
        if (applyStudent[i].name == "nv" && applyStudent[i].fatherName == "nv" && applyStudent[i].marks == 0 && applyStudent[i].CNIC == "nv" && applyStudent[i].phoneNo == "nv")
        {
            cout << "\t\t\t\t\t\t\tKindly enter your Name: ";
            while (true)
            {
                getline(cin, applyStudent[i].name); // Get the full name input

                // Check if the input is valid
                if (isAlphabet(applyStudent[i].name))
                {
                    break; // Input is valid, exit the loop
                }
                else
                {
                    cout << "\t\t\t\t\t\t\tInvalid name. Please enter alphabetic characters only in name: ";
                }
            }

            cout << "\t\t\t\t\t\t\tKindly enter your Father Name: ";

            while (true)
            {
                getline(cin, applyStudent[i].fatherName);

                if (isAlphabet(applyStudent[i].fatherName))
                {
                    break;
                }
                else
                {
                    cout << "\t\t\t\t\t\tInvalid name. Please enter alphabetic characters only in name: ";
                }
            }

            cout << "\t\t\t\t\t\t\tKindly enter your marks: ";

            while (true)
            {
                cin >> applyStudent[i].marks;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(255, '\n');
                    cout << "\t\t\t\t\t\t\tInvalid input!!.Kindly enter the numeric value(0 to 400):";
                    continue;
                }

                if (validMarks(applyStudent[i].marks))
                {
                    break;
                }
                else
                {
                    cout << "\t\t\t\t\t\tInvalid name. Please enter marks in the given range(0 to 400) : ";
                }
            }
            cin.ignore();

            cout << "\t\t\t\t\t\t\tKindly enter your CNIC : ";

            while (true)
            {
                getline(cin, applyStudent[i].CNIC);

                if (checkValidCNIC(applyStudent[i].CNIC))
                {
                    break;
                }
                else
                {
                    cout << "\t\t\t\t\t\t\tInvalid CNIC! Please ensure it contains exactly 13 digits : ";
                }
            }

            cout << "\t\t\t\t\t\t\tKindly enter your phone number: ";

            while (true)
            {
                getline(cin, applyStudent[i].phoneNo);

                if (checkValidContact(applyStudent[i].phoneNo))
                {
                    break;
                }
                else
                {
                    cout << "\t\t\t\t\t\t\tInvalid phone no ! Please ensure it contains exactly 11 digits : ";
                }
            }
            applyStudent[i].flag = true; // applicant can apply for hostel
            isApply = true;
            cout << "-\t\t\t\t\t\t\t------------->Application for hostel is submitted" << endl;
        }
        apCounter++;
        if (isApply)
        {
            break;
        }
    }
}

// --------------------This Function is defined for  Assigning the room & room servant....

void RoomAssign(rooms assignRoom[], student addStudent[], student applyStudent[], int addCounter, int &Rcounter, int &apCounter, int &MAX_AddSIZE)
{
    bool isRoomAssign = false;
    bool isOccured = true;
    if (Rcounter >= MAX_AddSIZE)
    {
        cout << "\t\t\t\t\t\t\tNo more rooms available for assignment." << endl;
        return;
    }

    for (int j = 0; j < MAX_AddSIZE; j++)
    {
        if (j == addCounter - 1 || assignRoom[j].roomFlag == false) // Process only desired records
        {
            cout << "\t\t\t\t\t\t\tAssign the room to Hostelite: ";

            while (true)
            {
                isOccured = true;
                cin >> assignRoom[j].achieveRoom;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(255, '\n');
                    cout << "\t\t\t\t\t\tInvalid Room no ##.kindly enter (1--100): ";
                }
                else if (assignRoom[j].achieveRoom < 1 || assignRoom[j].achieveRoom > MAX_AddSIZE)
                {
                    cout << "\t\t\t\t\t\tInvalid Room no ##.kindly enter (1--100): ";
                }

                for (int i = 0; i < MAX_AddSIZE; i++)
                {
                    if (assignRoom[i].achieveRoom == assignRoom[j].achieveRoom && i != j)
                    {
                        isOccured = false;
                        break;
                    }
                }
                if (isOccured)
                {
                    break;
                }
                else
                {
                    cout << "\t\t\t\t\t\t\tRoom already Assign!! kindly Assign other one: ";
                }
            }
            assignRoom[j].roomFlag = true;
            isRoomAssign = true;
            applyStudent[j].flag = false; // Mark the record as processed
            apCounter--;
        }
        Rcounter++;
        if (isRoomAssign)
        {
            break;
        }
    }
}

// --------------------This Function is defined for veiw current Record List....

void currentRecordList(rooms assignRoom[], student addStudent[], dues duesOfstudent[], int addCounter, int MAX_AddSIZE)
{
    system("cls");
    header();
    if (addCounter == 0)
    {
        cout << "\t\t\t\t\t\t\tNo applications submitted yet." << endl;
        return;
    }

    cout << "************************************************************************************************************************************************************************************************************" << endl;
    cout << left << setw(10) << "Room no" << left << setw(30) << "Name" << left << setw(30) << "Father Name" << left << setw(30) << "Marks (Ecat)" << left << setw(30) << "CNIC" << left << setw(25) << "Contact NO" << left << setw(30) << " HosteliteDues" << endl;
    cout << "************************************************************************************************************************************************************************************************************" << endl;

    for (int j = 0; j < MAX_AddSIZE; j++)
    {
        if (addStudent[j].name != "nv" && addStudent[j].fatherName != "nv" && addStudent[j].CNIC != "nv" && addStudent[j].phoneNo != "nv" && addStudent[j].marks != 0) // check if hosteelite rocord is added then display its record
        {
            cout << left << setw(10) << assignRoom[j].achieveRoom << left << setw(30) << addStudent[j].name << left << setw(30)
                 << addStudent[j].fatherName << left << setw(30) << addStudent[j].marks
                 << left << setw(30) << addStudent[j].CNIC << left << setw(30)
                 << addStudent[j].phoneNo << left << setw(30) << duesOfstudent[j].HosteliteDues << endl;
        }
    }
    cout << "\t\t\t\t\t\t\t\tKindly press any key...";
    getch();
}
void loadData(rooms assignRoom[], student addStudent[], int MAX_AddSIZE, dues duesOfstudent[], int &addCounter, int &Rcounter)
{
    ifstream currentRlistIn;
    currentRlistIn.open("CurrentRecord.txt");

    if (!currentRlistIn)
    {
        cout << "File does not exits!";
        return;
    }
    int i = 0;
    while (i < MAX_AddSIZE && !currentRlistIn.eof())
    {
        currentRlistIn >> assignRoom[i].achieveRoom;
        currentRlistIn.ignore();
        getline(currentRlistIn, addStudent[i].name, ',');
        getline(currentRlistIn, addStudent[i].fatherName, ',');
        currentRlistIn >> addStudent[i].marks;
        currentRlistIn.ignore();
        getline(currentRlistIn, addStudent[i].CNIC, ',');

        getline(currentRlistIn, addStudent[i].phoneNo, ',');
        currentRlistIn >> duesOfstudent[i].HosteliteDues;

        assignRoom[i].roomFlag = true;
        addStudent[i].flag = true;
        i++;
    }

    addCounter = i;
    Rcounter = i;
    currentRlistIn.close();
}
void saveCurrentRecordList(rooms assignRoom[], student addStudent[], dues duesOfstudent[], int addCounter, int MAX_AddSIZE)
{
    ofstream currentRlist;
    currentRlist.open("CurrentRecord.txt");
    if (!currentRlist)
    {
        cout << "\t\t\t\t\t\t\tFile does not exits!";
        return;
    }
    for (int j = 0; j < MAX_AddSIZE; j++)
    {
        if (addStudent[j].name != "nv") // check if hosteelite rocord is added then display its record
        {
            currentRlist << assignRoom[j].achieveRoom << "," << addStudent[j].name << ","
                         << addStudent[j].fatherName << "," << addStudent[j].marks
                         << "," << addStudent[j].CNIC << ","
                         << addStudent[j].phoneNo << "," << duesOfstudent[j].HosteliteDues << endl;
        }
    }
    currentRlist.close();
}

// --------------------This Function is defined for Updating record ....

void updateRecord(student addStudent[], int addCounter, rooms assignRoom[], int editRecord, int Rcounter, int MAX_AddSIZE)
{
    bool isUpdated = false;
    if (addCounter == 0)
    {
        cout << "\t\t\t\t\t\t\tKindly add the applicant record before Update Record!! " << endl;
        return;
    }
    if (Rcounter >= 0)
    {
        cout << "\t\t\t\t\t\t\tEnter the Room number to edit/update: ";

        while (true)
        {

            // cout << "Assign the room to Hostelite: ";
            cin >> editRecord;
            if (cin.fail()) // input validation
            {
                cin.clear();
                cin.ignore(255, '\n');
                cout << "\t\t\t\t\t\t\tInvalid Room no ##.kindly enter (1--100): ";
            }
            else if (editRecord < 1 || editRecord > MAX_AddSIZE)
            {
                cout << "\t\t\t\t\t\t\tInvalid Room no ##.kindly enter (1--100): ";
            }
            else
            {
                // valid input
                break;
            }
        }
    }

    for (int i = 0; i < MAX_AddSIZE; i++)
    {
        if ((assignRoom[i].achieveRoom == editRecord)) // check if updating record occupied room
        {
            cin.ignore();

            cout << "\t\t\t\t\t\t\tKindly enter your Name: ";
            while (true)
            {
                getline(cin, addStudent[i].name); // Get the full name input

                // Check if the input is valid
                if (isAlphabet(addStudent[i].name))
                {
                    break; // Input is valid, exit the loop
                }
                else
                {
                    cout << "\t\t\t\t\t\t\tInvalid name. Please enter alphabetic characters only in name: ";
                }
            }

            cout << "\t\t\t\t\t\t\tKindly enter your Father Name: ";

            while (true)
            {
                getline(cin, addStudent[i].fatherName);

                if (isAlphabet(addStudent[i].fatherName))
                {
                    break;
                }
                else
                {
                    cout << "\t\t\t\t\t\tInvalid name. Please enter alphabetic characters only in name: ";
                }
            }

            cout << "\t\t\t\t\t\t\tKindly enter your marks: ";

            while (true)
            {
                cin >> addStudent[i].marks;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(255, '\n');
                    cout << "\t\t\t\t\t\t\tInvalid input!!.Kindly enter the numeric value(0 to 400):";
                    continue;
                }

                if (validMarks(addStudent[i].marks))
                {
                    break;
                }
                else
                {
                    cout << "\t\t\t\t\t\tInvalid name. Please enter marks in the given range(0 to 400) : ";
                }
            }
            cin.ignore();

            cout << "\t\t\t\t\t\t\tKindly enter your CNIC : ";

            while (true)
            {
                getline(cin, addStudent[i].CNIC);

                if (checkValidCNIC(addStudent[i].CNIC))
                {
                    break;
                }
                else
                {
                    cout << "\t\t\t\t\t\t\tInvalid CNIC! Please ensure it contains exactly 13 digits : ";
                }
            }

            cout << "\t\t\t\t\t\t\tKindly enter your phone number: ";

            while (true)
            {
                getline(cin, addStudent[i].phoneNo);

                if (checkValidContact(addStudent[i].phoneNo))
                {
                    break;
                }
                else
                {
                    cout << "\t\t\t\t\t\t\tInvalid phone no ! Please ensure it contains exactly 11 digits : ";
                }
            }
            isUpdated = true;
            cout << "\t\t\t\t\t....................User Update Successfully!" << endl;
            break;
        }
    }
    if (!isUpdated)
    {
        cout << "\t\t\t\t\t......................This Room no does not exist!!!" << endl;
    }
}

// --------------------This Function is defined for Deleting record ....

void deleteRecord(student addStudent[], rooms assignRoom[], accounts accountsAssign[], int &MAX_AddSIZE, int removeRecord, int &addCounter, int &Rcounter, int &uCounter)
{
    bool isDelete = false;

    if (addCounter == 0)
    {
        cout << "\t\t\t\t\t\tKindly add the applicant record before DeleteRecord!! " << endl;
        return;
    }
    while (true)
    {

        if (Rcounter > 0)
        {
            cout << "\t\t\t\t\t\t\tEnter the Room number to Delete: ";
        }
        else
        {
            cout << "Kindly add the applicant record before Deleting Record!! " << endl;
            return;
        }
        cin >> removeRecord;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(255, '\n');
            cout << "\t\t\t\t\t\t\tInvalid Room no ##.kindly enter (1--100): ";
        }
        else if (removeRecord < 1 || removeRecord > MAX_AddSIZE)
        {
            cout << "\t\t\t\t\t\t\tInvalid Room no ##.kindly enter (1--100): ";
        }
        else
        {
            // valid room
            break;
        }
    }

    for (int i = 0; i < MAX_AddSIZE; i++)
    {
        if ((assignRoom[i].achieveRoom == removeRecord))
        {
            // the desire slot epmty
            addStudent[i].name = "nv";
            addStudent[i].fatherName = "nv";
            addStudent[i].marks = 0;
            addStudent[i].CNIC = "nv";
            addStudent[i].phoneNo = "nv";
            addStudent[i].flag = false;
            assignRoom[i].roomFlag = false;
            accountsAssign[i].userName = "nv";
            accountsAssign[i].password = "nv";
            accountsAssign[i].accountFlag = false;
            uCounter--;
            Rcounter--;
            addCounter--;

            isDelete = true;
            cout << "\t\t\t\t\t\t\tRecord deleted successfully!" << endl;
            break;
        }
    }
    if (!isDelete)
    {
        cout << " \t\t\t\t\t\t\tThe record of this Room no does not Exist !!" << endl;
    }
}

// --------------------This Function is defined for Creating account ....

void CreatAccount(accounts accountsAssign[], rooms assignRoom[], int &uCounter, int addCounter, int Rcounter, int UpdateAccount, int &MAX_AddSIZE)
{
    bool isAccountCreate = false;
    if (addCounter == 0) // check creating account only added hostelite
    {
        cout << "\t\t\t\t\t\t\tKindly add the applicant record before creating Account!! " << endl;
        return;
    }

    cin.ignore();
    cout << "\t\t\t\t\t\t\tEnter the Room number to create account: ";

    while (true)
    {

        if (Rcounter > 0)
        {

            cin >> UpdateAccount;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(255, '\n');
                cout << "\t\t\t\t\t\t\tInvalid Room no ##.kindly enter (1--100): ";
            }
            else if (UpdateAccount < 1 || UpdateAccount > MAX_AddSIZE)
            {
                cout << "\t\t\t\t\t\t\tInvalid Room no ##.kindly enter (1--100): ";
            }
            else
            {
                break;
            }
        }
        else
        {
            cout << "\t\t\t\t\t\t\tKindly assign the room  before create  Record!! " << endl;
            return;
        }
    }
    for (int i = 0; i < MAX_AddSIZE; i++)
    {
        if (assignRoom[i].achieveRoom == UpdateAccount && accountsAssign[i].userName == "nv" && accountsAssign[i].password == "nv" && accountsAssign[i].accountFlag == false)
        {
            cout << "\t\t\t\t\t\t\tEnter username: ";
            cin >> accountsAssign[i].userName;
            cout << "\t\t\t\t\t\t\tEnter Password: ";
            cin >> accountsAssign[i].password;
            accountsAssign[i].accountFlag = true;
            isAccountCreate = true;

            cout << "\t\t\t\t\t\t\tHostelite account created Successfully!....." << endl;
        }
        uCounter++;
        if (isAccountCreate)
        {
            break;
        }
    }
}

// --------------------This Function is defined for Deleting Account ....

void deleteAccount(accounts accountsAssign[], rooms assignRoom[], student addStudent[], int &MAX_AddSIZE, int removeAccount, int &uCounter, int addCounter, int Rcounter)
{
    bool isDelateAccount = false;

    while (true)
    { // input validation

        if (Rcounter == 0)
        {
            cout << "\t\t\t\t\t\t\tEnter the Room number to Delete account: ";
        }
        else
        {
            cout << "Kindly assign the room  before Deleting  Account!! " << endl;
            return;
        }
        cin >> removeAccount;

        if (cin.fail())
        { // input validation
            cin.clear();
            cin.ignore(255, '\n');
            cout << "\t\t\t\t\t\t\tInvalid Room no ##.kindly enter (1--100): ";
        }
        else if (removeAccount < 1 || removeAccount > MAX_AddSIZE)
        {
            cout << "\t\t\t\t\t\t\tInvalid Room no ##.kindly enter (1--100): ";
        }
        else
        {
            break;
        }
    }

    for (int i = 0; i < MAX_AddSIZE; i++)
    {
        if (assignRoom[i].achieveRoom == removeAccount && assignRoom[i].roomFlag) // check if deleting accout occupied room
        {
            accountsAssign[i].userName = "nv";
            accountsAssign[i].password = "nv";
            accountsAssign[i].accountFlag = false;
            isDelateAccount = true;

            uCounter--; // decrease the value of counter
            cout << "\t\t\t\t\t\t\tAccount deleted successfully!........." << endl;
            break;
        }
        else
        {
            cout << " \t\t\t\t\t\t\tThe Account of this Room no is not Exist !!" << endl;
            return;
        }
    }

    if (!isDelateAccount)
    {
        if (addCounter == 0)
        {
            cout << "\t\t\t\t\t\t\tKindly add the applicant record before Deleting Account!! " << endl;
            return;
        }
    }
}

// --------------------This Function is defined for Updating Account ....

void updateAccount(accounts accountsAssign[], rooms assignRoom[], int UpdateAccount, int &uCounter, int addCounter, int &MAX_AddSIZE, int Rcounter)
{
    if (addCounter == 0)
    {
        cout << "\t\t\t\t\t\t\tKindly add the applicant record before Update Account!! " << endl;
        return;
    }

    cout << "\t\t\t\t\t\t\tEnter the Room number to Update account: ";

    while (true)
    {

        if (Rcounter > 0)
        {

            cin >> UpdateAccount;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(255, '\n');
                cout << "\t\t\t\t\t\t\tInvalid Room no ##.kindly enter (1--100): ";
            }
            else if (UpdateAccount < 1 || UpdateAccount > MAX_AddSIZE)
            {
                cout << "\t\t\t\t\t\t\tInvalid Room no ##.kindly enter (1--100): ";
            }
            else
            {
                break;
            }
        }
        else
        {
            cout << "\t\t\t\t\t\t\tKindly assign the room  before Update Record!! " << endl;
            return;
        }
    }

    for (int i = 0; i < MAX_AddSIZE; i++)
    {
        if (assignRoom[i].achieveRoom == UpdateAccount && (accountsAssign[i].accountFlag && assignRoom[i].roomFlag)) // check if updating accout occupied room
        {
            cout << "\t\t\t\t\t\t\tEnter new  username : ";
            cin >> accountsAssign[i].userName;
            cout << "\t\t\t\t\t\t\tEnter new Password : ";
            cin >> accountsAssign[i].password;
            break;
        }
        else
        {
            cout << " \t\t\t\t\t\t\tThe Account of this Room no is not Exist !!" << endl;
            return;
        }
    }
}

// --------------------This Function is defined for hostelite can veiw Status ....

void veiwStatus(accounts accountsAssign[], rooms assignRoom[], student addStudent[], dues duesOfstudent[], string pwd, string user, int addCounter, int &MAX_AddSIZE)
{

    cout << "************************************************************************************************************************************************************************************************************" << endl;
    cout << left << setw(10) << "Room no" << left << setw(30) << "Name" << left << setw(30) << "Father Name" << left << setw(30) << "Marks (Ecat)" << left << setw(30) << "CNIC" << left << setw(30) << "Contact NO" << left << setw(30) << " HosteliteDues" << endl;

    cout << "************************************************************************************************************************************************************************************************************" << endl;
    for (int j = 0; j < MAX_AddSIZE; j++)
    {
        if (accountsAssign[j].userName == user && accountsAssign[j].password == pwd)
        {
            accountsAssign[j].accountFlag = true;
            if (accountsAssign[j].accountFlag == true) // check if the user login the account exist in the system

            {
                cout << left << setw(10) << assignRoom[j].achieveRoom << left << setw(30) << addStudent[j].name << left << setw(30)
                     << addStudent[j].fatherName << left << setw(30) << addStudent[j].marks
                     << left << setw(30) << addStudent[j].CNIC << left << setw(30)
                     << addStudent[j].phoneNo << left << setw(30) << duesOfstudent[j].HosteliteDues << endl;
            }
        }
    }
    cout << "\t\t\t\t\t\t\t\tKindly press any key...";
    getch();
}

// --------------------This Function is defined for hostelite can pay their dues ....

void payDues(accounts accountsAssign[], rooms assignRoom[], dues duesOfstudent[], double payment, student addStudent[], string pwd, string user, int addCounter, int &MAX_AddSIZE)
{

    for (int j = 0; j < MAX_AddSIZE; j++)
    {
        if (accountsAssign[j].userName == user && accountsAssign[j].password == pwd)
        {
            accountsAssign[j].accountFlag = true;
            if (accountsAssign[j].accountFlag == true && duesOfstudent[j].assignDues == true)
            {
                cout << "\t\t\t\t\t\t\t\t\tUser Name      : " << accountsAssign[j].userName << endl
                     << "\t\t\t\t\t\t\t\t\tRoom no   : " << assignRoom[j].achieveRoom << endl
                     << "\t\t\t\t\t\t\t\t\tYour Dues : " << duesOfstudent[j].HosteliteDues << endl;
                if (duesOfstudent[j].HosteliteDues == 0)
                {
                    cout << "\t\t\t\t\t\t\tYou have no pending dues .Thank you!!!" << endl;
                    return;
                }
                cout << "\t\t\t\t\t\t\t\tKindly enter your dues : ";

                while (true)
                {

                    cin >> payment;

                    // Check if the input is valid
                    if (cin.fail())
                    {
                        cin.clear();           // Clear the error
                        cin.ignore(255, '\n'); // remove invalid input
                        cout << "\t\t\t\t\t\t\t\tInvalid input! Please enter correct dues: ";
                    }
                    else if (payment != duesOfstudent[j].HosteliteDues)
                    {
                        cout << "\t\t\t\t\t\t\t\tOption out of range! Please enter correct dues: ";
                    }
                    else
                    {
                        // correct  input
                        break;
                    }
                }

                duesOfstudent[j].HosteliteDues -= payment; // generating the remaining dues
                duesOfstudent[j].duesFlag = true;

                cout << "\t\t\t\t\t\t\t\t\tPayment successful! You have paid " << payment << endl;
                cout << "\t\t\t\t\t\t\t\t\tRemaining dues: " << duesOfstudent[j].HosteliteDues << endl;

                cout << "\n\t\t\t\t\t\t\t\t\tThank you for your payment!" << endl;
                break;
            }
        }
        else
        {
            cout << "\t\t\t\t\t\t\tSeneior wardon does not assign the dues.";
            break;
        }
    }
}
//-----------------------------save the applicant data----------------------------
void applylistDataRecord(student applyStudent[], int apCounter, int MAX_ApplySize)
{
    ofstream applyListData;
    applyListData.open("applylist.txt");
    if (!applyListData)
    {
        cout << "File does not exits!";
        return;
    }

    for (int j = 0; j < MAX_ApplySize; j++)
    {
        if (applyStudent[j].name != "nv" && applyStudent[j].fatherName != "nv" && applyStudent[j].marks != 0 && applyStudent[j].CNIC != "nv" && applyStudent[j].phoneNo != "nv") // Display only valid   entries
        {
            applyListData << applyStudent[j].name << "," << applyStudent[j].fatherName << "," << applyStudent[j].marks
                          << "," << applyStudent[j].CNIC << "," << applyStudent[j].phoneNo << endl;
        }
    }
    applyListData.close();
}
// --------------------------Load the applicant data----------------------------
void loadapplylistDataRecord(student applyStudent[], int &apCounter, int MAX_ApplySize)
{
    ifstream applyListDataIn;
    applyListDataIn.open("applylist.txt");

    if (!applyListDataIn)
    {
        cout << "\t\t\t\t\t\t\tFile does not exits!";
        return;
    }
    int i = 0;
    while (i < MAX_ApplySize && !applyListDataIn.eof())
    {

        getline(applyListDataIn, applyStudent[i].name, ',');
        getline(applyListDataIn, applyStudent[i].fatherName, ',');
        applyListDataIn >> applyStudent[i].marks;
        applyListDataIn.ignore();
        getline(applyListDataIn, applyStudent[i].CNIC, ',');

        getline(applyListDataIn, applyStudent[i].phoneNo, ',');
        applyStudent[i].flag = true;
        i++;
    }
    apCounter = i; // no of applicants
    applyListDataIn.close();
}
//-----------------------------save the accounts and complain data----------------------------

void saveAccountsRecord(accounts accountsAssign[], complains stComplain[], int MAX_AddSIZE, int uCounter, int cmpCounter)
{
    ofstream accountsOut;
    accountsOut.open("account.txt");

    if (!accountsOut)
    {
        cout << "\t\t\t\t\t\t\tFile does not exits!";
        return;
    }
    for (int i = 0; i < MAX_AddSIZE; i++)
    {
        if (accountsAssign[i].userName != "nv" && accountsAssign[i].password != "nv" && stComplain[i].complain != "nv")
        {
            accountsOut << accountsAssign[i].userName << "," << accountsAssign[i].password << "," << stComplain[i].complain << endl;
        }
    }
    accountsOut.close();
}
//-----------------------------Load the  acounts and complains data----------------------------

void loadAccountsRecord(accounts accountsAssign[], complains stComplain[], int MAX_AddSIZE, int &uCounter, int &cmpCounter)
{
    ifstream accountsIn;
    accountsIn.open("account.txt");

    if (!accountsIn)
    {
        cout << "\t\t\t\t\t\t\tFile does not exits!";
        return;
    }
    int i = 0;
    while (i < MAX_AddSIZE && !accountsIn.eof())
    {

        getline(accountsIn, accountsAssign[i].userName, ',');
        getline(accountsIn, accountsAssign[i].password, ',');
        getline(accountsIn, stComplain[i].complain, ',');

        accountsAssign[i].accountFlag = true;
        stComplain[i].cmpFlag = true;
        i++;
    }
    uCounter = i;   // number of user accounts
    cmpCounter = i; // number of complain
    accountsIn.close();
}
