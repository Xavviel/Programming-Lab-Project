#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

const int MAX_EXPENSE = 100; //The maximum number of expense

//Arrays for storing information 
string expenseName[MAX_EXPENSE];
string expenseCategory[MAX_EXPENSE];
double expenseAmount[MAX_EXPENSE];

//variables
double monthlyBudget = 0;
int expenseCount = 0;

//Set Monthly Budget Function
void setBudget() {
    cout << "\n=======SET MONTHLY BUDGET=======\n";

    cout << "Enter Your Montlhy Budget (In Philippine Peso): ";
    cin >> monthlyBudget;

    cout << "\nMonthly Budget is Added Successfully!\n";
}
//Add Expense Function 
void addExpense() {
    if (expenseCount >= MAX_EXPENSE) {
        cout << "\nExpense Limit is Reached!\n";
        return;
    }

    cout << "\n=======ADD EXPENSE=======\n";

    cout << "Enter Expense Name: ";
    cin.ignore();
    getline(cin, expenseName[expenseCount]);

    cout << "Enter Expense Category: ";
    getline(cin, expenseCategory[expenseCount]);

    cout << "Enter Amount (In Philippine Peso): ";
    cin >> expenseAmount[expenseCount];

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
        cout << "No Expense available to delete.\n";
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
        cout << "\nAre You Sure You Want to Delete this Expense? (Y/N): ";
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
double calculateTotalExpense() {
    double total = 0;

    for (int i = 0; i < expenseCount; i++) {
        total += expenseAmount[i];
    }

    return total;
}

//budget summary
void budgetSummary() {
    double totalExpense, remainingBudget, percentageUsed; //declaration of variables

    totalExpense = calculateTotalExpense();
    remainingBudget = monthlyBudget - totalExpense;

    if (monthlyBudget > 0) {
        percentageUsed = (totalExpense / monthlyBudget) * 100;
    } else {
        percentageUsed = 0;
    }

    cout << "\n=======Budget Summary======\n";

    cout << fixed << setprecision(2);

    cout << "Monthly Budget:PHP " << monthlyBudget <<endl;
    cout << "Total Expense:PHP " << totalExpense <<endl;
    cout << "Remaining Budget:PHP " << remainingBudget <<endl;
    cout << "Budget Used: " << percentageUsed << "%" <<endl;

    cout << "\n===========================\n";

    if (remainingBudget < 0) {
        cout << "WARNING: You have exceeded your budget!\n";
    } else if (percentageUsed >= 80) {
        cout << "WARNING: You have used most of your budget.\n";
    } else {
        cout << "Your spending is still within your budget.\n";
    }
}

int main() {
    int choice;
    char confirmChoice;

    do {
        cout << "\n========BUDGI MAIN MENU========\n";
        cout << "1. Set Monthly Budget\n";
        cout << "2. Add Expense\n";
        cout << "3. View Expense History\n";
        cout << "4. View Budget Summary\n";
        cout << "5. Delete Expense\n";
        cout << "6. Exit\n";
        cout << "==================================\n";

        cout << "Enter your Choice: ";
        cin >> choice;

        switch (choice) {

            case 1: 
               setBudget();
            break; 

            case 2: 
               addExpense();
            break;

            case 3:
               viewExpense();
            break;

            case 4:
               budgetSummary();
            break;

            case 5:
               deleteExpense();
            break;

            case 6:
            cout << "\nThank you for using BudGi Expense Tracker\n";
            return 0;

            default:
            cout << "\nInvalid Choice! Please Select from 1 - 6.\n";
        }

        cout << "\nDo you want to continue? (Y/N): ";
        cin >> confirmChoice;

        while (confirmChoice != 'Y' && confirmChoice != 'y' && confirmChoice != 'N' && confirmChoice != 'n') {
            cout << "Invalid input! Enter Y or N: ";
            cin >> confirmChoice;
        }
    } while (confirmChoice == 'Y' || confirmChoice == 'y');
      cout << "\nThank you for using the Budget Tracker!\n";

    return 0;
}

