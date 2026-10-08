#include <cctype>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <limits>
#include <vector>
#include <string>
using namespace std;

const string ClientFile = "Clients.txt";

enum enMainMenuChoices { quickWithdraw = 1, normalWithdraw, deposit, checkBalance, logout };

enum enQuickWithDrawMenuChoices 
    { twenty=1, fifty, oneHundred, TwoHundred, fourHundred, sixHundred, eightHundred, oneThousand, Exit};

struct stClientInfo
{
    string accountNumber;
    string pinCode;
    string clientName;
    string phone;
    double accountBalance;
};

stClientInfo CurrentClient;

void Login();
void ShowMainMenu();
void QuickWithDrawMenu();

vector<string> SplitString(string S1, const string &seperator)
{
    vector<string> vString;

    int pos = 0;
    string partOfString = "";

    while ( (pos = S1.find(seperator)) != string::npos)
    {
        partOfString = S1.substr(0, pos);

        if (partOfString != "")
        {
            vString.push_back(partOfString);
        }

        S1.erase(0, pos + seperator.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}

stClientInfo ConvertClientDataLineToRecord(const string &dataLine)
{
    vector<string> vData = SplitString(dataLine, "/#/");
    stClientInfo client;

    client.accountNumber = vData[0];
    client.pinCode = vData[1];
    client.clientName = vData[2];
    client.phone = vData[3];
    client.accountBalance = stod(vData.at(4));

    return client;
}

vector<stClientInfo> LoadClientDataFromFile(const string &fileName)
{
    vector<stClientInfo> vClientsInfo;

    fstream file;
    file.open(fileName, ios::in);
    
    if (file.is_open())
    {
        string line;

        while(getline(file, line))
        {
            if (line != "")
            {
                vClientsInfo.push_back(ConvertClientDataLineToRecord(line));
            }
        }

        file.close();
    }

    return vClientsInfo;
}

string ConverClinetRecordToLine(const stClientInfo &client, const string &seperator)
{
    string dataLine = "";

    dataLine += client.accountNumber + seperator;
    dataLine += client.pinCode + seperator;
    dataLine += client.clientName + seperator;
    dataLine += client.phone + seperator;
    dataLine += to_string(client.accountBalance);

    return dataLine;
}

void UpdateCientDataInFile(const stClientInfo &client, const string &fileName)
{
    vector<stClientInfo> vClientsInfo = LoadClientDataFromFile(fileName);

    fstream file;
    file.open(fileName, ios::out);

    if (file.is_open())
    {
        for (stClientInfo &C : vClientsInfo)
        {
            if (C.accountNumber == client.accountNumber)
            {
                C.accountNumber = client.accountNumber;
                C.pinCode = client.pinCode;
                C.accountBalance = client.accountBalance;
            }

            file << ConverClinetRecordToLine(C,"/#/") << endl;
        }

        file.close();
    }
}

bool LoadClientData(const string &accountNumber, const string &pinCode , stClientInfo &client)
{
    vector<stClientInfo> vClientsInfo = LoadClientDataFromFile(ClientFile);

    for (stClientInfo &C : vClientsInfo)
    {
        if (C.accountNumber == accountNumber && C.pinCode == pinCode)
        {
            client = C;
            return true;
        }
    }

    return false;
}

int ReadNumber(const string &message)
{
    int userInput;

    while (true) {

        cout << message;
        cin >> userInput;
     
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid Input, Try again." << endl;
            continue;
        }
        
        return userInput;
    }
}

void GoBackToMainMenu()
{
    system("bash -c \"read -n 1 -s -r -p 'Press any key to go back to main menu ...'\"");
    ShowMainMenu();
}

void GoBackToQuickWithDrawMenu()
{
    system("bash -c \"read -n 1 -s -r -p 'Press any key to go back to main menu ...'\"");
    QuickWithDrawMenu();
}

bool Conferm(const string &message)
{
    char yes_no = 'n';

    cout << message;
    cin >> yes_no;

    return (tolower(yes_no) == 'y');
}

void WithDrawAmountFromClient( stClientInfo &client, double amount)
{
    if (client.accountBalance >= amount)
    {
        if (Conferm("\nAre you sure do you want to do this tansaction? (y/n): "))
        {
            client.accountBalance -= amount;            
            UpdateCientDataInFile(CurrentClient, ClientFile);
            
            cout << "\nDone successflly, New balance is: " << client.accountBalance << endl;
        }

        else cout << "\nThe transaction do not happend!" << endl;
    }

    else  
    {
        cout << "\nThe amount exceds you balance, Make another choice." << endl;
    }
}

void PerformQuickWithDrawMenu(enQuickWithDrawMenuChoices userChoice)
{
    switch(userChoice)
    {

        case enQuickWithDrawMenuChoices::twenty:
        {
            WithDrawAmountFromClient(CurrentClient, 20);
            GoBackToMainMenu();
            break;
        }
        
        case enQuickWithDrawMenuChoices::fifty:
        {
            WithDrawAmountFromClient(CurrentClient, 50);
            GoBackToMainMenu();
            break;
        }
        
        case enQuickWithDrawMenuChoices::oneHundred:
        {
            WithDrawAmountFromClient(CurrentClient, 100);
            GoBackToMainMenu();
            break;
        }
        
        case enQuickWithDrawMenuChoices::TwoHundred:
        {
            WithDrawAmountFromClient(CurrentClient, 200);
            GoBackToMainMenu();
            break;
        }
        
        case enQuickWithDrawMenuChoices::fourHundred:
        {
            WithDrawAmountFromClient(CurrentClient, 400);
            GoBackToMainMenu();
            break;
        }
        
        case enQuickWithDrawMenuChoices::sixHundred:
        {
            WithDrawAmountFromClient(CurrentClient, 600);
            GoBackToMainMenu();
            break;
        }
        
        case enQuickWithDrawMenuChoices::eightHundred:
        {
            WithDrawAmountFromClient(CurrentClient, 800);
            GoBackToMainMenu();
            break;
        }
        
        case enQuickWithDrawMenuChoices::oneThousand:
        {
            WithDrawAmountFromClient(CurrentClient, 1000);
            GoBackToMainMenu();
            break;
        }
        
        case enQuickWithDrawMenuChoices::Exit:
        {
            GoBackToMainMenu();
            break;
        }
        
        default:
        {
            cout << "\nInvalid Input, Try Again." << endl;
            GoBackToMainMenu();
            break;
        }
    } 
}

void QuickWithDrawMenu()
{
    system("clear");
    cout << "========================================" << endl;
    cout << "           Quick WithdrawScreen" << endl;
    cout << "========================================" << endl;
    cout << "\t[1] 20 \t\t [2] 50" << endl;
    cout << "\t[3] 100 \t [4] 200" << endl;
    cout << "\t[5] 400 \t [6] 600" << endl;
    cout << "\t[7] 800 \t [8] 1000" << endl;
    cout << "\t[9] Exit" << endl;
    cout << "========================================" << endl;
    cout << "Your Balance is: " << CurrentClient.accountBalance << endl;

    PerformQuickWithDrawMenu(
        (enQuickWithDrawMenuChoices) ReadNumber("Choose what to withdraw from [1] to [8]: "));
}

void NormalWithdrawScreen()
{
    cout << "=========================================" << endl;
    cout << "           Normal Withdraw Screen" << endl;
    cout << "=========================================" << endl;
}

void NormalWithdraw()
{
    NormalWithdrawScreen();
    int amount = 0;

    do {

        amount = ReadNumber("\nEnter number multiple of 5's ? ");

    } while (amount <= 0 || amount % 5 != 0);

    if (CurrentClient.accountBalance >= amount)
    {
        if (Conferm("Are you sure you want to perform this transaction? (y/n): "))
        {
            CurrentClient.accountBalance -= amount;
            UpdateCientDataInFile(CurrentClient, ClientFile);
            
            cout << "\n Done successflly, New balance is: " << CurrentClient.accountBalance << endl;
        }
        
        else cout << "\nThe transaction do not happend!" << endl;
    }
    
    else  cout << "\nThe amount exceeds your balance, Make another choice." << endl;
    
}

void DepositAmountScreen()
{
    cout << "==================================" << endl;
    cout << "          Diposit Screen" << endl;
    cout << "==================================" << endl;
}

void DepositAmount()
{
    DepositAmountScreen();

    int amount = ReadNumber("Enter a positive deposit amount: ");

    if(Conferm("Are you sure do you want to perform this transaction? (y/n): "))
    {
        CurrentClient.accountBalance += amount;
        UpdateCientDataInFile(CurrentClient,ClientFile);
        cout << "\n Done Successflly, New balance is: " << CurrentClient.accountBalance << endl;
    }

    else cout << "Transaction do not happend!" << endl;
}

void CheckBalanceScreen()
{
    cout << "======================================" << endl;
    cout << "         Check balance screen" << endl;
    cout << "======================================" << endl;
}

void CheckBalance()
{
    CheckBalanceScreen();
    cout << "Your balance is: " << CurrentClient.accountBalance << endl << endl;
}

void PerformMainMenu(enMainMenuChoices userChoice)
{
    switch (userChoice)
    {
        case enMainMenuChoices::quickWithdraw:
        {
            system("clear");
            QuickWithDrawMenu();
            GoBackToMainMenu();
            break;    
        }

        case enMainMenuChoices::normalWithdraw:
        {
            system("clear");
            NormalWithdraw();
            GoBackToMainMenu();
            break;    
        }

        case enMainMenuChoices::deposit:
        {
            system("clear");
            DepositAmount();
            GoBackToMainMenu();
            break;    
        }

        case enMainMenuChoices::checkBalance:
        {
            system("clear");
            CheckBalance();
            GoBackToMainMenu();
            break;    
        }

        case enMainMenuChoices::logout:
        {
            Login();
            break;
        }

        default:
        {
            cout << "\nInvalid Input! Try again." << endl;
            GoBackToMainMenu();
        }
    }
}

void ShowMainMenu()
{
    system("clear");
    cout << "========================================" << endl;
    cout << "         ATM Main Menu Screen" << endl;
    cout << "========================================" << endl;
    cout << "\t[1] Quick Withdraw." << endl;
    cout << "\t[2] Normal Withdraw." << endl;
    cout << "\t[3] Deposit." << endl;
    cout << "\t[4] Check Balance." << endl;
    cout << "\t[5] Logout." << endl;
    cout << "========================================" << endl;

    PerformMainMenu((enMainMenuChoices) ReadNumber("Choose what you want to do? [1 to 5]: "));
}

void LogInScreen()
{
    cout << "=================================" << endl;
    cout << "          LogIn Screen" << endl;
    cout << "=================================" << endl;
}

void Login()
{
    bool loadingFaild = false;
    string accountNumber;
    string pinCode;
    
    do 
    {
        system("clear");
        LogInScreen();

        if (loadingFaild)
        {
            cout << "Invalid Account Number / PinCode!" << endl;
        }
 
        cout << "Enter Account Number: ";
        cin >> accountNumber;

        cout << "Enter PinCode: ";
        cin >> pinCode;

        loadingFaild = (!LoadClientData(accountNumber, pinCode,  CurrentClient));

    } while (loadingFaild);

    ShowMainMenu();
}

int main()
{
    Login();

    return 0;
}
