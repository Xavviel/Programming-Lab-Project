#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

//function decleration
void setBudget();
void addBalance();
void addExpense();
void viewExpense();
double calculateTotalExpense();
void budgetSummary();

const int MAX_EXPENSE = 100; //Maximum value or input allowed for the user to make.

int expenseCount = 0; //variable decleration
double monthlyBudget = 0;

struct balance { //balance structure 
    double inputBalance = 0;
    double balance = 0;
    double remainingBalance = 0;
};

balance Balance;

struct expense { //expense structure 
    string expenseName;
    string expenseCategory;
    double expenseAmount;
};

expense Expenses [MAX_EXPENSE]; //to call the data types be stored in the Max Expense declaration.


int main() {
    int choice;

    do {
        cout << "\n===============================\n";
        cout << "          BudGi MAIN MENU        ";
        cout << "\n===============================\n";
        cout << "1. Set Budget\n";
        cout << "2. Add Balance\n";
        cout << "3. Add Expense\n";
        cout << "4. View Expense History\n";
        cout << "5. View Budget Summary\n";
        cout << "6. Exit\n";
        cout << "==================================\n";

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
            cout << "\nInvalid Choice! Please Select from choices 1 - 6.\n"; //if user tries to input numbers greater than 5
        }

        
    } while (choice != 6);

    return 0;
}

void setBudget() {
    cout << "\n========== SET MONTHLY BUDGET ==========\n";
    
    cout << "Enter your Monthly Budget: PHP "; //user sets the monthly budget.
    cin >> monthlyBudget;

    while (monthlyBudget <= 0) { //if user adds a negative or zero number it will result to let the user set the balance again.
        cout << "Invalid Amount! Please Try Again!";

        cout << "Enter your Monthly Budget: PHP ";
        cin >> monthlyBudget;
    }

    cout << "\nMonthly Budget is Successfully Added!\n"; //exit message if user correctly set budget.

    return;
}

void addBalance() {
    cout << "\n========== ADD BALANCE ==========\n";

    cout << "\nEnter the Amount: PHP "; //User adds a balance
    cin >> Balance.inputBalance;

    while (Balance.inputBalance <= 0) {
        cout << "Enter a Valid Amount. Please Try Again!" << endl; //if user tries to add a negative or zero balance.
    }

    Balance.balance += Balance.inputBalance; //process to get the balance of the user 
    Balance.remainingBalance = Balance.balance - calculateTotalExpense(); //remaining balance of the user process. calls the function calculateTotalExpnse as it has all the expenses the user made. 

    cout << "\nBalance Added Successfully!\n"; //exit message if user adds a balance 

    cout << "\nCurrent Balance: PHP " << Balance.remainingBalance << fixed << setprecision(2) <<endl; //current balance of the user
}

void addExpense() {
    if (expenseCount >= MAX_EXPENSE) {
        cout << "\nExpense Limit is Reached!\n"; //if expense exceeds 100. display message.
        return;
    }

    cout << "\n=========== ADD EXPENSE ==========\n";

    cin.ignore();

    cout << "\nEnter Expense Name: ";
    getline (cin, Expenses[expenseCount].expenseName);
    
    cout << "Enter Expense Category: ";
    getline (cin, Expenses[expenseCount].expenseCategory);

    cout << "Enter Expense Amount: PHP ";
    cin >> Expenses[expenseCount].expenseAmount;

    expenseCount++;

    cout << "\nExpense is Added Successfully!\n"; //exit message if user is done adding an expense

    return;
}

void viewExpense() {
    cout << "\n=============== EXPENSE HISTORY ===============\n";

    if (expenseCount == 0) {
        cout << "\nNo Expense is Recorded!\n";
        return;
    }

    cout << fixed << setprecision(2);

    cout << left << setw(5) << "No."
         << setw(20) << "Expense Name"
         << setw(20) << "Category"
         << setw(15) << "Amount (PHP)" << endl;

    cout << "============================================================\n";

    for (int i = 0; i < expenseCount; i++) {
        cout << left << setw(5) << i + 1
             << setw(20) << Expenses[i].expenseName
             << setw(20) << Expenses[i].expenseCategory
             << setw(15) << Expenses[i].expenseAmount << endl;
    }
}

double calculateTotalExpense() {
    double total = 0;

    for (int i = 0; i < expenseCount; i++) {
        total += Expenses[i].expenseAmount; //process to get the total expense.
    }

    return total;
}

void budgetSummary() {
    double totalExpense, remainingBudget, percentageUsed; //declaration of variables

    totalExpense = calculateTotalExpense();
    remainingBudget = monthlyBudget - totalExpense;
    Balance.remainingBalance = Balance.balance - totalExpense;

    if (monthlyBudget > 0) {
        percentageUsed = (totalExpense / monthlyBudget) * 100;
    } else {
        percentageUsed = 0;
    }

    cout << "\n========== BUDGET SUMMARY ==========\n";

    cout << fixed << setprecision(2);

    cout << "\nMonthly Budget: PHP " << monthlyBudget <<endl;
    cout << "\nTotal Expense: PHP " << totalExpense <<endl;
    cout << "\nRemaining Budget: PHP " << remainingBudget <<endl;
    cout << "\nWallet Balance: PHP " << Balance.remainingBalance <<endl;
    cout << "\nBudget Used: " << percentageUsed << "%" <<endl;

    cout << "\n=====================================\n";

    if (remainingBudget < 0) {
        cout << "WARNING: You have exceeded your budget!\n";
    } else if (percentageUsed >= 80) {
        cout << "WARNING: You have used most of your budget.\n";
    } else {
        cout << "Your spending is still within your budget.\n";
    }
}
