#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

//declare all functions.
void setBudget();
void addBalance ();
void addExpense ();
void viewExpense ();
double calculateTotalExpense ();
void budgetSummary ();

const int MAX_EXPENSE = 100; //Maximum value or input allowed for the user to make.


int expenseCount = 0; //declare that expense count is equal to zero. 
double monthlyBudget = 0;
double walletBalance = 0;

struct balance {
    double inputBalance = 0;
    double balance = 0;
    double remainingBalance = 0;
};

balance Balance;

struct expense { //to make all data types be more orgainzed and in just one structure. 
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
               setBudget();

            case 2: 
               addBalance();
            break; 

            case 3: 
               addExpense();
            break;

            case 4:
               viewExpense();
            break;

            case 5:
               budgetSummary();
            break;

            case 6:
            cout << "\nThank you for using BudGi Expense Tracker\n";
            return 0;

            default:
            cout << "\nInvalid Choice! Please Select from choices 1 - 5.\n";
        }

        
    } while (choice != 5);

    return 0;
}

void setBudget () {
    cout << "\n========== SET MONTHLY BUDGET ==========\n";
    
    cout << "Enter your Monthly Budget:PHP ";
    cin >> monthlyBudget;

    cout << "\nMonthly Budget is Successfully Added!\n";

    return;
}

void addBalance () {
    cout << "\n========== ADD BALANCE ==========\n";
    
    cout << "Current Balance: PHP " << fixed << setprecision(2) <<endl;
    cin >> Balance.remainingBalance;

    cout << "\nEnter the Amount: ";
    cin >> Balance.inputBalance;

    while (Balance.inputBalance <= 0) {
        cout << "Enter a Valid Amount. Please Try Again!" << endl;
    }

    Balance.balance += Balance.inputBalance;
    Balance.remainingBalance = Balance.balance - calculateTotalExpense();

    cout << "\nBalance Added Successfully!\n";
    cout << "Balance: PHP " << fixed << setprecision(2) <<endl;
    cin >> Balance.remainingBalance;
}

void addExpense () {
    if (expenseCount >= MAX_EXPENSE) {
        cout << "\nExpense Limit is Reached!\n";
        return;
    }

    cout << "\n=========== ADD EXPENSE ==========\n";

    cout << "\nEnter Expense Name: ";
    getline (cin, Expenses[expenseCount].expenseName);
    
    cout << "Enter Expense Category: ";
    getline (cin, Expenses[expenseCount].expenseCategory);

    cout << "Enter Expense Amount:PHP ";
    cin >> Expenses[expenseCount].expenseAmount;

    expenseCount++;

    cout << "\nExpense is Added Successfully!\n";

    return;
}

void viewExpense () {
    cout << "\n========== Expense History ==========\n";

    if (expenseCount == 0) {
        cout << "\nNo Expense is Recorded\n";

        return;
    }

    for (int i = 0; i < expenseCount; i++) {
        cout << "\nExpense #" << i + 1 <<endl;
        cout << "\nName: " << Expenses[i].expenseName <<endl;
        cout << "\nCategory: " << Expenses[i].expenseCategory <<endl;
        cout << "\nAmount: PHP " << Expenses[i].expenseAmount << fixed << setprecision(2) <<endl;
    }
}

double calculateTotalExpense() {
    double total = 0;

    for (int i = 0; i < expenseCount; i++) {
        total += Expenses[i].expenseAmount;
    }

    return total;
}

void budgetSummary () {
    double totalExpense, remainingBudget, percentageUsed; //declaration of variables

    totalExpense = calculateTotalExpense();
    remainingBudget = monthlyBudget - totalExpense;

    if (monthlyBudget > 0) {
        percentageUsed = (totalExpense / monthlyBudget) * 100;
    } else {
        percentageUsed = 0;
    }

    cout << "\n========== BUDGET SUMMARY ==========\n";

    cout << fixed << setprecision(2);

    cout << "Monthly Budget: PHP " << monthlyBudget <<endl;
    cout << "Total Expense: PHP " << totalExpense <<endl;
    cout << "Remaining Budget: PHP " << remainingBudget <<endl;
    cout << "Budget Used: " << percentageUsed << "%" <<endl;

    cout << "\n=====================================\n";

    if (remainingBudget < 0) {
        cout << "WARNING: You have exceeded your budget!\n";
    } else if (percentageUsed >= 80) {
        cout << "WARNING: You have used most of your budget.\n";
    } else {
        cout << "Your spending is still within your budget.\n";
    }
}
