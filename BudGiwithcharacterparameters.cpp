#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Function declaration
void setBudget();
void addBalance();
void addExpense();
void viewExpense();
double calculateTotalExpense();
void budgetSummary();

const int MAX_EXPENSE = 100;

// Variable declaration
int expenseCount = 0;
double monthlyBudget = 0;

struct balance {
    double inputBalance = 0;
    double balance = 0;
    double remainingBalance = 0;
};

balance entry;

struct expense {
    string expenseName;
    string expenseCategory;
    double expenseAmount;
};

expense record[MAX_EXPENSE];

int main() {
    int choice;

    cout << fixed << setprecision(2);

    do {
        cout << "\n===================================\n";
        cout << "          BudGi MAIN MENU";
        cout << "\n===================================\n";
        cout << "1. Set Budget\n";
        cout << "2. Add Balance\n";
        cout << "3. Add Expense\n";
        cout << "4. View Expense History\n";
        cout << "5. View Budget Summary\n";
        cout << "6. Exit\n";
        cout << "-----------------------------------\n";

        cout << "Enter your Choice: ";
        cin >> choice;

        while (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "\nInvalid Input! Please Enter Numbers Only!\n";
            cout << "Enter your Choice: ";
            cin >> choice;
        }

        switch (choice) {

            case 1:
                setBudget();
                break;

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
                cout << "\nThank you for using BudGi Expense Tracker!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
                cout << "Please Select from choices 1 - 6.\n";
        }

    } while (choice != 6);

    return 0;
}

// Set Monthly Budget Function
void setBudget() {
    cout << "\n======= SET MONTHLY BUDGET ========\n";

    cout << "Enter your Monthly Budget: PHP ";
    cin >> monthlyBudget;

    while (cin.fail() || monthlyBudget <= 0) {

        if (cin.fail()) {
            cout << "\nInvalid Input! Please Enter Numbers Only!\n";
        } else {
            cout << "\nInvalid Amount! Please Try Again!\n";
        }

        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Enter your Monthly Budget: PHP ";
        cin >> monthlyBudget;
    }

    cout << "\nMonthly Budget is Successfully Added!\n";
}

// Add Balance Function
void addBalance() {
    cout << "\n========== ADD BALANCE ==========\n";

    cout << "Enter the Amount: PHP ";
    cin >> entry.inputBalance;

    while (cin.fail() || entry.inputBalance <= 0) {

        if (cin.fail()) {
            cout << "\nInvalid Input! Please Enter Numbers Only!\n";
        } else {
            cout << "\nEnter a Valid Amount. Please Try Again!\n";
        }

        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Enter the Amount: PHP ";
        cin >> entry.inputBalance;
    }

    entry.balance += entry.inputBalance;
    entry.remainingBalance = entry.balance - calculateTotalExpense();

    cout << "\nBalance Added Successfully!\n";
    cout << "\nCurrent Balance: PHP " << entry.remainingBalance << endl;
}

// Add Expense Function
void addExpense() {
    if (expenseCount >= MAX_EXPENSE) {
        cout << "\nExpense Limit is Reached!\n";
        return;
    }

    entry.remainingBalance = entry.balance - calculateTotalExpense();

    if (entry.remainingBalance <= 0) {
        cout << "\n========== ADD BALANCE ===========\n";
        cout << "Add a balance first!\n";
        return;
    }

    cout << "\n============ ADD EXPENSE ===========\n";

    cin.ignore(1000, '\n');

    cout << "\nEnter Expense Name: ";
    getline(cin, record[expenseCount].expenseName);

    cout << "Enter Expense Category: ";
    getline(cin, record[expenseCount].expenseCategory);

    cout << "Enter Expense Amount: PHP ";
    cin >> record[expenseCount].expenseAmount;

    while (cin.fail() ||
           record[expenseCount].expenseAmount <= 0 ||
           record[expenseCount].expenseAmount > entry.remainingBalance) {

        if (cin.fail()) {
            cout << "\nInvalid Input! Please Enter Numbers Only!\n";
        }
        else if (record[expenseCount].expenseAmount <= 0) {
            cout << "\nEnter a Valid Amount! Please Try Again.\n";
        }
        else {
            cout << "\nInsufficient Balance!\n";
        }

        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Enter Expense Amount: PHP ";
        cin >> record[expenseCount].expenseAmount;
    }

    expenseCount++;

    entry.remainingBalance = entry.balance - calculateTotalExpense();

    cout << "\nExpense is Added Successfully!\n";
}

// View Expense History Function
void viewExpense() {
    cout << "\n=============== EXPENSE HISTORY ===============\n";

    if (expenseCount == 0) {
        cout << "No Expense is Recorded!\n";
        return;
    }

    cout << left << setw(5) << "No."
         << setw(15) << "Expense Name"
         << setw(15) << "Category"
         << setw(15) << "Amount (PHP)" << endl;

    for (int i = 0; i < expenseCount; i++) {
        cout << left << setw(5) << (i + 1)
             << setw(15) << record[i].expenseName
             << setw(15) << record[i].expenseCategory
             << setw(15) << record[i].expenseAmount << endl;
    }
}

// Calculate Total Expense Function
double calculateTotalExpense() {
    double total = 0;

    for (int i = 0; i < expenseCount; i++) {
        total += record[i].expenseAmount;
    }

    return total;
}

// Budget Summary Function
void budgetSummary() {
    double totalExpense, remainingBudget, percentageUsed;

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

    cout << left << setw(19) << "Percentage Used"
         << ": % " << right << setw(12) << percentageUsed << '\n';

    cout << "\n------------------------------------\n";

    if (monthlyBudget <= 0) {
        cout << "No budget yet set.\n";
    }
    else if (remainingBudget < 0) {
        cout << "WARNING: You have exceeded your budget!\n";
    }
    else if (percentageUsed >= 80) {
        cout << "WARNING: You have used most of your budget.\n";
    }
    else {
        cout << "Your spending is still within your budget.\n";
    }
}
