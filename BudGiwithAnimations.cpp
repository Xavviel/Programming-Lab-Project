/****************************************************************
AI MADE ANIMATIONS
************************************************************/
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <thread>
#include <chrono>
#include <limits>

using namespace std;

const int MAX_EXPENSE = 100;

// Arrays for storing information
string expenseName[MAX_EXPENSE];
string expenseCategory[MAX_EXPENSE];
double expenseAmount[MAX_EXPENSE];

// Variables
double monthlyBudget = 0;
int expenseCount = 0;


// ========== ANIMATION FUNCTIONS ==========

// Typing Animation
void typingAnimation(string text, int speed = 25) {
    for (int i = 0; i < text.length(); i++) {
        cout << text[i] << flush;
        this_thread::sleep_for(chrono::milliseconds(speed));
    }
    cout << endl;
}

// Loading Animation
void loadingAnimation() {
    cout << "\nProcessing";

    for (int i = 0; i < 3; i++) {
        this_thread::sleep_for(chrono::milliseconds(350));
        cout << "." << flush;
    }

    cout << endl;
}

// Startup Progress Bar
void progressBar() {
    cout << "\nStarting BudGi...\n";

    for (int i = 0; i <= 20; i++) {
        cout << "\r[";

        for (int j = 0; j < 20; j++) {
            if (j < i) {
                cout << "#";
            } else {
                cout << "-";
            }
        }

        cout << "] " << i * 5 << "%" << flush;

        this_thread::sleep_for(chrono::milliseconds(60));
    }

    cout << "\n";
}

// Clear Screen
void clearScreen() {
    cout << "\033[2J\033[H" << flush;
}

// Budget Usage Bar
void budgetBar(double percentage) {
    int filled = static_cast<int>(percentage / 5);

    if (filled > 20) {
        filled = 20;
    }

    if (filled < 0) {
        filled = 0;
    }

    cout << "\nBudget Usage: [";

    for (int i = 0; i < 20; i++) {
        if (i < filled) {
            cout << "#";
        } else {
            cout << "-";
        }
    }

    cout << "] " << fixed << setprecision(2)
         << percentage << "%\n";
}


// ========== SET MONTHLY BUDGET ==========

void setBudget() {
    cout << "\n======= SET MONTHLY BUDGET =======\n";

    cout << "Enter Your Monthly Budget (In Philippine Peso): ";
    cin >> monthlyBudget;

    loadingAnimation();
    typingAnimation("Monthly Budget is Added Successfully!");
}


// ========== ADD EXPENSE ==========

void addExpense() {
    if (expenseCount >= MAX_EXPENSE) {
        cout << "\nExpense Limit is Reached!\n";
        return;
    }

    cout << "\n======= ADD EXPENSE =======\n";

    cout << "Enter Expense Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, expenseName[expenseCount]);

    cout << "Enter Expense Category: ";
    getline(cin, expenseCategory[expenseCount]);

    cout << "Enter Amount (In Philippine Peso): ";
    cin >> expenseAmount[expenseCount];

    expenseCount++;

    loadingAnimation();
    typingAnimation("Expense is Added Successfully!");
}


// ========== VIEW EXPENSE HISTORY ==========

void viewExpense() {
    cout << "\n======= EXPENSE HISTORY =======\n";

    if (expenseCount == 0) {
        cout << "\nNo Expense is Recorded!\n";
        return;
    }

    for (int i = 0; i < expenseCount; i++) {
        cout << "\nExpense #" << i + 1 << endl;
        cout << "Name: " << expenseName[i] << endl;
        cout << "Category: " << expenseCategory[i] << endl;
        cout << "Amount (In Philippine Peso): PHP "
             << fixed << setprecision(2)
             << expenseAmount[i] << endl;
    }
}


// ========== DELETE EXPENSE ==========

void deleteExpense() {
    string deleteName;
    int index = -1;
    char confirm;

    cout << "\n======= DELETE EXPENSE =======\n";

    if (expenseCount == 0) {
        cout << "No Expense available to delete.\n";
        return;
    }

    cout << "Enter Expense Name to Delete: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    cout << "Name: " << expenseName[index] << endl;
    cout << "Category: " << expenseCategory[index] << endl;
    cout << "Amount: PHP " << fixed << setprecision(2)
         << expenseAmount[index] << endl;

    // Confirmation
    do {
        cout << "\nAre You Sure You Want to Delete this Expense? (Y/N): ";
        cin >> confirm;

        if (confirm != 'Y' && confirm != 'y' &&
            confirm != 'N' && confirm != 'n') {
            cout << "Invalid Input! Please Enter (Y/N)\n";
        }

    } while (confirm != 'Y' && confirm != 'y' &&
             confirm != 'N' && confirm != 'n');

    // Delete the expense
    if (confirm == 'Y' || confirm == 'y') {
        for (int i = index; i < expenseCount - 1; i++) {
            expenseName[i] = expenseName[i + 1];
            expenseCategory[i] = expenseCategory[i + 1];
            expenseAmount[i] = expenseAmount[i + 1];
        }

        expenseCount--;

        loadingAnimation();
        typingAnimation("Expense Successfully Deleted!");
    } else {
        cout << "\nDeletion Cancelled!\n";
    }
}


// ========== CALCULATE TOTAL EXPENSE ==========

double calculateTotalExpense() {
    double total = 0;

    for (int i = 0; i < expenseCount; i++) {
        total += expenseAmount[i];
    }

    return total;
}


// ========== BUDGET SUMMARY ==========

void budgetSummary() {
    double totalExpense, remainingBudget, percentageUsed;

    totalExpense = calculateTotalExpense();
    remainingBudget = monthlyBudget - totalExpense;

    if (monthlyBudget > 0) {
        percentageUsed = (totalExpense / monthlyBudget) * 100;
    } else {
        percentageUsed = 0;
    }

    cout << "\n======= BUDGET SUMMARY =======\n";

    cout << fixed << setprecision(2);

    cout << "Monthly Budget: PHP " << monthlyBudget << endl;
    cout << "Total Expense: PHP " << totalExpense << endl;
    cout << "Remaining Budget: PHP " << remainingBudget << endl;
    cout << "Budget Used: " << percentageUsed << "%" << endl;

    budgetBar(percentageUsed);

    cout << "\n==============================\n";

    if (remainingBudget < 0) {
        cout << "WARNING: You have exceeded your budget!\n";
    } else if (percentageUsed >= 80) {
        cout << "WARNING: You have used most of your budget.\n";
    } else {
        cout << "Your spending is still within your budget.\n";
    }
}


// ========== MAIN FUNCTION ==========

int main() {
    int choice;
    char confirmChoice;

    // Welcome Animation
    typingAnimation("Welcome to BudGi!", 70);
    typingAnimation("Your Budget Buddy, One Expense at a Time!", 30);
    progressBar();

    this_thread::sleep_for(chrono::milliseconds(600));

    do {
        clearScreen();

        cout << "\n==================================\n";
        cout << "         BUDGI MAIN MENU\n";
        cout << "==================================\n";
        cout << "1. Set Monthly Budget\n";
        cout << "2. Add Expense\n";
        cout << "3. View Expense History\n";
        cout << "4. View Budget Summary\n";
        cout << "5. Delete Expense\n";
        cout << "6. Exit\n";
        cout << "==================================\n";

        cout << "Enter your Choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid Input! Please enter a number.\n";
        } else {
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
                    typingAnimation("\nThank you for using BudGi Expense Tracker!", 40);
                    return 0;

                default:
                    cout << "\nInvalid Choice! Please Select from 1 - 6.\n";
            }
        }

        cout << "\nDo you want to continue? (Y/N): ";
        cin >> confirmChoice;

        while (confirmChoice != 'Y' && confirmChoice != 'y' &&
               confirmChoice != 'N' && confirmChoice != 'n') {
            cout << "Invalid input! Enter Y or N: ";
            cin >> confirmChoice;
        }

    } while (confirmChoice == 'Y' || confirmChoice == 'y');

    typingAnimation("\nThank you for using BudGi Expense Tracker!", 40);

    return 0;
}
