#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <math.h>

using namespace std;

const int MAX_EXPENSE = 100; //The maximum number of expense

//Arrays for storing information 
string expenseName[MAX_EXPENSE];
string expenseCategory[MAX_EXPENSE];
string expenseAmount[MAX_EXPENSE];

//variables
double monthlyBudget = 0;
int expenseCount = 0;

//Set Monthly Budget Function
void setBudget () {
    cout << "\n=======SET MONTHLY BUDGET=======\n";

    cout << "Enter Your Montlhy Budget (In Philippine Peso): ";
    cin >> monthlyBudget;

    cout << "\nMonthly Budget is Added Successfully!\n";
}
//Add Expense Function 
void addExpense () {
    if (expenseCount >= MAX_EXPENSE) {
        cout << "\nExpense Storage is Full!\n";
        return;
    }

    cout << "\n=======ADD EXPENSE=======\n";

    cout << "Enter Expense Name: ";
    cin.ignore();
    getline(cin, expenseName[expenseCount]);

    cout << "Enter Expense Category: ";
    getline(cin, expenseCategory[expenseCount]);

    cout << "Enter Amount (In Philippine Peso): ";
    getline(cin, expenseAmount[expenseCount]);

    expenseCount++;

    cout << "\nExpense is Added Successfully!\n";
}

//View All Expense Function
void viewExpense () {

    int i = 0;

    cout << "\n=======EXPENSE HISTORY=======";

    if (expenseCount == 0) {

        cout << "\nNo Expense is Recorded!\n";
        return;
    }

    for (i = 0; i < expenseCount; i++) {
        cout << "\nExpense #" << i + 1 <<endl;
        cout << "Name: " << expenseName[i] <<endl;
        cout << "Category: " << expenseCategory[i] <<endl;
        cout << "Amount (In Philippine Peso): " << fixed << setprecision(2) << expenseAmount[i] <<endl;
    }
}

void deleteExpense() {
    string deleteName;
    int index = -1;
    char confirm;

    cout << "\n=======DELETE EXPENSE=======\n";

    if (expenseCount == 0) {
        cout << "No expenses available to delete.\n";
        return;
    }

    cout << "Enter Expense Name to Delete: ";
    cin.ignore();
    getline(cin, deleteName);

    // Search for the expense
    for (int i = 0; i < expenseCount; i++) {
        if (expenseName[i] == deleteName) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "\nExpense Not Found!\n";
        return;
    }

    // Display the expense found
    cout << "\nExpense Found!\n";
    cout << "Name: " << expenseName[index] <<endl;
    cout << "Category: " << expenseCategory[index] <<endl;
    cout << "Amount: PHP " << expenseAmount[index] <<endl;

    // Confirmation
    do
    {
        cout << "\nAre You Sure You Qant to Delete this Expense? (Y/N): ";
        cin >> confirm;

        if (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n') {
            cout << "Invalid Input! Please Enter (Y/N)\n";
        }

    } while (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n');

    // Delete the expense
    if (confirm == 'Y' || confirm == 'y') {
        for (int i = index; i < expenseCount - 1; i++) {
            expenseName[i] = expenseName[i + 1];
            expenseCategory[i] = expenseCategory[i + 1];
            expenseAmount[i] = expenseAmount[i + 1];
        }

        expenseCount--;
        cout << "\nExpense Successfully Deleted!\n";
    } else {
        cout << "\nDeletion Cancelled!\n";
    }
}


//Calculating Total Expense
double calulationtotalExpense () {
    double total = 0;
    double Total;

    for (int i = 0; i < expenseCount; i++) {
        total = total + expenseAmount[i];
    }

    return total;
}

