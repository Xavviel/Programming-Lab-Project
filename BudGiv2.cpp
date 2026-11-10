#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

//declare all functions.
void setBudget ();
void addExpense ();
void viewExpense ();
void budgetSummary ();

const int MAX_EXPENSE = 100; //Maximum value or input allowed for the user to make.

int expenseCount = 0; //declare that expense count is equal to zero. 
double monthlyBudget = 0;

struct expense { //to make all data types be more orgainzed and in just one structure. 
    string expenseName;
    string expenseCategory;
    double expenseAmount;
};

expense Expenses [MAX_EXPENSE]; //to call the data types be stored in the Max Expense declaration.


int main() {
    int choice;
    char confirmChoice;

    do {
        cout << "\n===============================\n";
        cout << "          BudGi MAIN MENU        ";
        cout << "\n===============================\n";
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
            cout << "\nThank you for using BudGi Expense Tracker\n";
            return 0;

            default:
            cout << "\nInvalid Choice! Please Select from choices 1 - 5.\n";
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

void setBudget () {
    cout << "\n========== SET MONTHLY BUDGET ==========\n";
    
    cout << "Enter your Monthly Budget:PHP ";
    cin >> monthlyBudget;

    cout << "\nMonthly Budget is Successfully Added!\n";

    return;
}

void addExpense () {
    if (expenseCount >= MAX_EXPENSE) {
        cout << "\nExpense Limit is Reached!\n";
        return;
    }

    cout << "\n=========== ADD EXPENSE ==========\n";

    cout << "\nEnter Expense Name: ";
    getline (cin, Expenses[expenseCount].expenseName);
    
    cout << "\nEnter Expense Category: ";
    getline (cin, Expenses[expenseCount].expenseCategory);

    cout << "\nEnter Expense Amount:PHP ";
    cin >> Expenses[expenseCount].expenseAmount;

    expenseCount++;

    cout << "\nExpense is Added Successfully!\n";

    return;
}

void viewExpense () {
    

}
