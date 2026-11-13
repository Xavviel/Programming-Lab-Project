#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//function declaration
void setBudget();
void addBalance();
void addExpense();
void viewExpense();
double calculateTotalExpense();
void budgetSummary();

const int MAX_EXPENSE = 100; //Maximum value or input allowed for the user to make.

//variable decleration
int expenseCount = 0; 
double monthlyBudget = 0;

struct balance { //balance structure 
    double inputBalance = 0;
    double balance = 0;
    double remainingBalance = 0;
};

balance entry;

struct expense { //expense structure 
    string expenseName;
    string expenseCategory;
    double expenseAmount;
};

expense record [MAX_EXPENSE]; //to call the data types be stored in the Max Expense declaration.


int main() {
    int choice;

    cout << fixed << setprecision(2);

    do {
        cout << "\n===================================\n";
        cout << "          BudGi MAIN MENU        ";
        cout << "\n===================================\n";
        cout << "1. Set Budget\n";
        cout << "2. Add Balance\n";
        cout << "3. Add Expense\n";
        cout << "4. View Expense History\n";
        cout << "5. View Budget Summary\n";
        cout << "6. Exit";
        cout << "\n-----------------------------------\n";

        cout << "Enter your Choice: ";
        cin >> choice;

        switch (choice) {

            case 1: 
               setBudget(); //call function 1
            break;

            case 2: 
               addBalance(); //call function 2
            break; 

            case 3: 
               addExpense(); //call function 3
            break;

            case 4:
               viewExpense(); //call function 4
            break;

            case 5:
               budgetSummary(); //call function 5
            break;

            case 6:
            cout << "\nThank you for using BudGi Expense Tracker\n"; //exit message
            return 0;

            default:
            cout << "\nInvalid Choice!\nPlease Select from choices 1 - 6.\n"; //if user tries to input numbers greater than 5
        }

    } while (choice != 6);

    return 0;
}

void setBudget() {
    cout << "\n======= SET MONTHLY BUDGET ========"<<endl;
    cout << "Enter your Monthly Budget: PHP "; //user sets the monthly budget.
    cin >> monthlyBudget;

    while (monthlyBudget <= 0) { //if user adds a negative or zero number it will result to let the user set the balance again.
        cout << "Invalid Amount! Please Try Again!\n";
        cout << "\nEnter your Monthly Budget: PHP ";
        cin >> monthlyBudget;
    }
    cout << "\nMonthly Budget is Successfully Added!\n"; //exit message if user correctly set budget.
    return;
}

void addBalance() {
    cout << "\n========== ADD BALANCE ==========" << endl;

    cout << "Enter the Amount: PHP "; //User adds a balance
    cin >> entry.inputBalance;

    while (entry.inputBalance <= 0) {
        cout << "\nEnter a Valid Amount. Please Try Again!" << endl; //if user tries to add a negative or zero balance.
        
        cout << "Enter the Amount: PHP "; //User adds a balance
        cin >> entry.inputBalance;
    }

    entry.balance += entry.inputBalance; //process to get the balance of the user 
    entry.remainingBalance = entry.balance - calculateTotalExpense(); //remaining balance of the user process. calls the function calculateTotalExpnse as it has all the expenses the user made. 

    cout << "\nBalance Added Successfully!\n"; //exit message if user adds a balance 

    cout << "\nCurrent Balance: PHP " << entry.remainingBalance <<endl; //current balance of the user
}

void addExpense() {
    double totalExpense, remainingBudget; //declaration of variables

    totalExpense = calculateTotalExpense();
    entry.remainingBalance = entry.balance - totalExpense;

    if (expenseCount >= MAX_EXPENSE) {
        cout << "\nExpense Limit is Reached!\n"; //if expense exceeds 100. display message.
        
        return;
    }

    if (entry.remainingBalance == 0){
        cout << "\n========== ADD BALANCE ===========\n";
       
        cout << "Add a balance first!" << endl;

        return;
    }
    cout << "\n============ ADD EXPENSE ===========\n";
     
    cin.ignore();

    cout << "\nEnter Expense Name: ";
    getline (cin, record[expenseCount].expenseName);

    cout << "Enter Expense Category: ";
    getline (cin, record[expenseCount].expenseCategory);

    cout << "Enter Expense Amount: PHP ";
    cin >> record[expenseCount].expenseAmount;

    while (record[expenseCount].expenseAmount <= 0 || record[expenseCount].expenseAmount > entry.remainingBalance){
        
        if (record[expenseCount].expenseAmount <= 0) { 
            cout << "\nEnter a valid amount. Please try again." << endl;
            
            cout << "Enter Expense Amount: PHP ";  
            cin >> record[expenseCount].expenseAmount;

	    } else if (record[expenseCount].expenseAmount > entry.remainingBalance) {
            cout << "\nInsufficient Balance" << endl;
            
            cout << "Enter Expense Amount: PHP ";
            cin >> record[expenseCount].expenseAmount;
        }
    }

    expenseCount++;

    entry.remainingBalance = entry.balance - calculateTotalExpense();
    
    cout << "\nExpense is Added Successfully!\n"; //exit message if user is done adding an expense
    
    return;
}

void viewExpense() {
    cout << "\n=============== EXPENSE HISTORY ===============\n";

    if (expenseCount == 0) {
        cout << "No Expense is Recorded!\n";
        return;
    }

    cout << left << setw(5) << "No."
         << setw(15) << "Expense Name"
         << setw(10) << "Category"
         << setw(15) << "Amount (PHP)" << endl;


    for (int i = 0; i < expenseCount; i++) {
        cout << left << setw(5) << (i + 1)
             << setw(15) << record[i].expenseName
             << setw(10) << record[i].expenseCategory
             << setw(15) << record[i].expenseAmount << endl;
    }
}

double calculateTotalExpense() {
    double total = 0;

    for (int i = 0; i < expenseCount; i++) {
        total += record[i].expenseAmount; //process to get the total expense.
    }
    return total;
}

void budgetSummary() {
    double totalExpense, remainingBudget, percentageUsed; //declaration of variables

    totalExpense = calculateTotalExpense();
    remainingBudget = monthlyBudget - totalExpense;
    entry.remainingBalance = entry.balance - totalExpense;

    if (monthlyBudget > 0) {
        percentageUsed = (totalExpense / monthlyBudget) * 100;
    } else {
        percentageUsed = 0;
    }

    cout << "\n========== BUDGET SUMMARY ==========\n";

    cout << left << setw(19) << "Monthly Budget"
         << ": PHP " << right << setw(10) << monthlyBudget << '\n';
    cout << left << setw(19) << "Total Expenses"
         << ": PHP " << right << setw(10) << totalExpense << '\n';
    cout << left << setw(19) << "Remaining Budget"
         << ": PHP " << right << setw(10) << remainingBudget << '\n';
    cout << left << setw(19) << "Wallet Balance"
         << ": PHP " << right << setw(10) << entry.remainingBalance << '\n';
    cout << left << setw(19) << "Precentage Used"
         << ": % " << right << setw(10) << percentageUsed << '\n';
    cout << "\n------------------------------------\n";

    if (monthlyBudget <= 0) {
    cout << "No budget yet set.\n";
    } else if (remainingBudget < 0) {
        cout << "WARNING: You have exceeded your budget!\n";
    } else if (percentageUsed >= 80) {
        cout << "WARNING: You have used most of your budget.\n";
    } else {
        cout << "Your spending is still within your budget.\n";
    }
}
