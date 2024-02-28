#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <string>
#include <fstream>
using namespace std;

string name, status, date;
char start, again;
int deposite, totalDeposite = 0, balance = 0, minimum, maximum, betNumber, betAmmount, withdrawAmmount = 0, remaining;
int random[10];

// This function will display all the rules in start of the game
void rules() {
    cout << "================================================================" << endl;
    cout << "=";
    cout << setw(35) << setfill(' ') << "RULES";
    cout << setw(28) << setfill(' ') << "=" << endl;
    cout << "================================================================" << endl << endl;
    cout << "- The player will Enter his in-game name." << endl << endl;
    cout << "- The player will have to deposite a minimum of 2000$ in his " << endl;
    cout << "  game account in order to play the game." << endl << endl;
    cout << "- The player will be given a minimum and a maximum value and " << endl;
    cout << "  he'll have to choose a random number within the given range." << endl << endl;
    cout << "- The game will decide whether the player won or lost, based " << endl;
    cout << "  on his entered lucky number. " << endl << endl;
    cout << "- The player will be given option of withdrawing his remaining " << endl;
    cout << "  ammount from the game account to his bank account at the end." << endl << endl;
    cout << "- All the data of every game will be saved in result file." << endl << endl;
    cout << "=================================================================" << endl << endl;
}
// This function will check current date and store it in variable
void currentDate() {
    time_t now = time(0);

    struct tm timeinfo; 
    localtime_s(&timeinfo, &now);

    char date_str[11];
    strftime(date_str, sizeof(date_str), "%d/%m/%Y", &timeinfo);

    date = date_str;
}
// This function will ask the user to start the game and return a boolean value based on user's response
bool askStart() {
    cout << "start the game? (Y/N) : ";
    cin >> start;
    cout << endl;

    if (start == 'Y' || start == 'y')
        return true;
    else
        return false;
}
// This function will ask user his in-game name and will greet him
void askName() {
    cout << "Enter your in-game name (3-6 letters): ";
    cin >> name;
    if (name.length() > 6 || name.length() < 3)     // making sure that the entered in-game name has a specific length
    {
        cout << "Invlaid Name!" << endl << endl;
        askName();
    }
    else {
        cout << "Good evening, " << name << "!" << endl << endl;
    }
}
// This function will prompt the user to deposite a specific ammount to his game account
void depositeAmmout() {
    cout << "Enter the ammount you want to deposite in game account in $ (Max 999999): ";
    cin >> deposite;
    if (deposite > 999999)      // Assigning a limit to the deposited ammount for managing indentation in the saved data file
    {
        cout << endl << "Limit exceeded!" << endl;
    }
    else {
        balance += deposite;     // deposited ammount added to game account balance
        totalDeposite += deposite;   // keep the record of total ammount deposited till now
        if (!((deposite + balance) >= 2000)) {   // making sure that user has a minimum of 2000$ in his in-game account
            cout << "You successfuly deposited " << deposite << "$ in your account, " << endl;
            cout << "Your current balance is " << balance << "$, please atleast deposite " << (2000 - balance) << "$ more." << endl << endl;
            depositeAmmout();
        }
        else {
            cout << "You successfuly deposited " << deposite << "$ in your account, " << endl;
            cout << "Your current balance is " << balance << "$." << endl << endl;
        }
    }
}
// This function will create 10 random numbers between 0 and 20 everytime the user play the game
void generateRandomNum() {
    srand(time(0));    // seeding the rand() fucntion so that it gives a different value everytime we run the function
    int N = 20;      // the limit upto which we want the random number to be
    for (int i = 0; i < 10; i++)
    {
        random[i] = rand() % N;   // this will give us random numbers ranging from 0 to 20
    }
}
// This function will find the minimum and maximum number from the created random numbers
void checkMinMax() {
    int min = random[0];
    int max = random[0];
    for (int i = 0; i < 10; i++)
    {
        if (min > random[i])
        {
            min = random[i];
        }
        if (max < random[i])
        {
            max = random[i];
        }
    }

    minimum = min;
    maximum = max;
}
// This function will prompt the user to enter a lucky number between the given range
void askBetNumber() {
    cout << "Enter your lucky number between " << minimum << " and " << maximum << " : ";
    cin >> betNumber;
    
    if (!(betNumber >= minimum && betNumber <= maximum))   // making sure the entered bet number is from the given range
    {
        cout << "Invalid Number!" << endl << "Please, ";
        askBetNumber();
    }
    cout << endl;
}
// This function will prompt the user to enter the ammount he wants to bet on
void askBetAmmount() {
    cout << "Place your bet between (1500$ - " << balance << "$) : ";
    cin >> betAmmount;
    cout << endl;

    if (!(betAmmount >= 1500 && betAmmount <= balance))   // making sure the player doesn't bet anywhere less than 1500 and more than his available balance
    {
        cout << "Invalid ammout!" << endl << "Please, ";
        askBetAmmount();
    }
}
// This function will check whether the player won or not and return a boolean value accordingly 
bool checkWinner() {
    for (int i = 0; i < 10; i++)
    {
        if (random[i] == betNumber && random[i] != minimum && random[i] != maximum)
        {
            return true;
        }
    }
    return false;
}
// This function will ask the user to withdraw ammount from his game account incase of enough balance
void withdraw() {
    if (balance > 0) {
        cout << "Enter the ammount you want to withdraw to your bank account (0 - " << balance << "$) : ";
        cin >> withdrawAmmount;
        cout << endl;
        if (withdrawAmmount > balance || withdrawAmmount <= 0)   // Making sure that the amount user is trying to withdraw is less than or equal to his available balance 
        {
            cout << "Invalid ammount!" << endl << endl;
            withdraw();
        }
        else {
            balance -= withdrawAmmount;
            cout << "----- " << withdrawAmmount << "$ successfully transfered to your bank account -----" << endl;
            cout << "Your remaining balance is " << balance << "$." << endl;
        }
    }
}
// This function will Create a data file and write data in it or it will append data in a the file if It's already present and won't overwrite it so that we have record of all the games played
void saveData() {
    ofstream onfile("results.txt", ios::app);    // opening the file and appending data to it

    if (onfile.is_open()) {
        onfile << " " << setw(7) << setfill(' ') << date << setw(25) << setfill(' ') << name << setw(30) << setfill(' ') << remaining << setw(27) << setfill(' ') << status << setw(7) << setfill(' ') << betAmmount << setw(30) << setfill(' ') << withdrawAmmount << setw(31) << setfill(' ') << balance << endl;

        onfile.close();
    }
}
// This function will ask the user if he want's to continue the game and will progress accordingly
void playAgain() {
        cout << "                   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl << endl;
        if (balance < 2000) {     // assigning a limit of atleast 2000 in-game account balance to continue the game
            cout << "Your Balance is " << balance << "$, which is less than 2000$" << endl;
            cout << "Please deposite more ammount in your account" << endl << endl;
            depositeAmmout();
        }
        else {
            deposite = 0;
        }
        generateRandomNum();      // generate Random number in array
        checkMinMax();            // find the samllest and greatest number from created array
        askBetNumber();           // prompting user to enter his lucky number
        askBetAmmount();          // prompting user to enter the his betting amount
        currentDate();            // finding current date to store in data file

        remaining = balance;      // storing the availble balance to add in data file under the total balance catagorey of the next line
        if (checkWinner())
        {
            system("Color A");
            cout << endl << "===========================================" << endl;
            cout << "-------- Congratulations, You Won! --------" << endl;
            cout << "===========================================" << endl << endl;
            cout << "The lucky Numbers were : ";
            for (int i = 0; i < 10; i++)
            {
                if (random[i] != minimum && random[i] != maximum) {
                    cout << random[i] << " ";
                }
            }
            cout << endl << endl;
            balance += betAmmount;   // adding winning prize to user's in-game account
            cout << "Your Prize has been deposited to your game account" << endl << "Your Current Balance is " << balance << "$" << endl << endl;
            status = "Won";    // declaring the status of game results to store in data file
        }
        else {
            system("Color C");
            cout << endl << "=============================================" << endl;
            cout << "----------------- You Lost! -----------------" << endl;
            cout << "=============================================" << endl << endl;
            cout << "The lucky Numbers were : ";
            for (int i = 0; i < 10; i++)
            {
                if (random[i] != minimum && random[i] != maximum) {
                    cout << random[i] << " ";
                }
            }
            cout << endl << endl;
            balance -= betAmmount;   // cutting the betting ammount from user's in-game account
            cout << "Your current balance is " << balance << "$" << endl << endl;
            status = "Lost";   // declaring the status of game results to store in data file
        }

        cout << endl << "Want to play Again? (Y/N) : ";
        cin >> again;
        cout << endl;

        if (again == 'y' || again == 'Y') {       // storing data first and that start the next game procedure
            system("Color B");
            saveData();
            playAgain();
        }
        else {                                    // allowing user to withdraw ammount form his in-game account then storing the data
            system("Color A");
            withdraw();
            saveData();
            cout << endl << "Good Bye!!!" << endl;
        }
}


int main()
{
    system("Color B");  // light blue text

    rules();    // display the rules on the top

    if (askStart()) {              // Starting the game if player's Enter Option Yes
        cout << "                   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl << endl;
        askName();
        depositeAmmout();
        generateRandomNum();
        checkMinMax();
        askBetNumber();
        askBetAmmount();
        currentDate();


        if (checkWinner())    // announcing the result of the first game
        {
            system("Color A");    // Green text
            cout << endl << "===========================================" << endl;
            cout << "-------- Congratulations, You Won! --------" << endl;
            cout << "===========================================" << endl << endl;
            cout << "The luckey Numbers were : ";
            for (int i = 0; i < 10; i++)
            {
                if (random[i] != minimum && random[i] != maximum) {
                    cout << random[i] << " ";
                }
            }
            cout << endl << endl;
            balance += betAmmount;
            cout << "Your Prize has been deposited to your game account" << endl << "Your Current Balance is " << balance << "$" << endl << endl;
            status = "Won";
        }
        else {
            system("Color C");    // Red text
            cout << endl << "=============================================" << endl;
            cout << "----------------- You Lost! -----------------" << endl;
            cout << "=============================================" << endl << endl;
            cout << "The luckey Numbers were : ";
            for (int i = 0; i < 10; i++)
            {
                if (random[i] != minimum && random[i] != maximum) {
                    cout << random[i] << " ";
                }
            }
            cout << endl << endl;
            balance -= betAmmount;
            cout << "Your current balance is " << balance << "$" << endl << endl;
            status = "Lost";
        }

        ofstream onfile("results.txt", ios::app);     // Storing the header line in the file

        if (onfile.is_open()) {
            onfile << endl << endl << setw(8) << setfill(' ') << "Date" << setw(32) << setfill(' ') << "<Player Name>" << setw(32) << setfill(' ') << "<Total Balance>" << setw(32) << setfill(' ') << "<Last Game Status>" << setw(32) << setfill(' ') << "<Ammount Withdrawn>" << setw(32) << setfill(' ') << "<Remaining Balance>" << endl;
            onfile << setw(170) << setfill('-') << "-" << endl;

            onfile.close();
        }

        cout << endl << "Want to play Again? (Y/N) : ";
        cin >> again;
        cout << endl;

        if (again == 'y' || again == 'Y') {
            system("Color B");    // light blue text
            ofstream onfile("results.txt", ios::app);

            if (onfile.is_open()) {
                onfile << " " << setw(7) << setfill(' ') << date << setw(25) << setfill(' ') << name << setw(30) << setfill(' ') << totalDeposite << setw(27) << setfill(' ') << status << setw(7) << setfill(' ') << betAmmount << setw(30) << setfill(' ') << withdrawAmmount << setw(31) << setfill(' ') << balance << endl;

                onfile.close();
            }

            playAgain();
        }
        else {
            system("Color A");   // Green text
            withdraw();

            ofstream onfile("results.txt", ios::app);

            if (onfile.is_open()) {
                onfile << " " << setw(7) << setfill(' ') << date << setw(25) << setfill(' ') << name << setw(30) << setfill(' ') << totalDeposite << setw(27) << setfill(' ') << status << setw(7) << setfill(' ') << betAmmount << setw(30) << setfill(' ') << withdrawAmmount << setw(31) << setfill(' ') << balance << endl;

                onfile.close();
            }

            cout << endl << "Good Bye!!!" << endl;
        }
    }
}