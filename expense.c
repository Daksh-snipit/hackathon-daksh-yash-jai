#include <stdio.h>
#include <string.h>

#define MAX_EXPENSES 100
#define CATEGORY_COUNT 5


struct Expense {
    char description[50];
    float amount;
    int category;
};


void clearInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}


void displayCategories() {
    printf("\nExpense Categories:\n");
    printf("1. Food\n");
    printf("2. Travel\n");
    printf("3. Books\n");
    printf("4. Entertainment\n");
    printf("5. Other\n");
}


void addExpense(struct Expense expenses[], int *count) {
    if (*count >= MAX_EXPENSES) {
        printf("\nExpense limit reached!\n");
        return;
    }

    printf("\nEnter expense description: ");
    scanf(" %49[^\n]", expenses[*count].description);

    printf("Enter amount: ");
    while (scanf("%f", &expenses[*count].amount) != 1 ||
           expenses[*count].amount <= 0) {
        printf("Invalid amount. Enter a positive number: ");
        clearInputBuffer();
    }

    displayCategories();

    printf("Enter category number (1-5): ");
    while (scanf("%d", &expenses[*count].category) != 1 ||
           expenses[*count].category < 1 ||
           expenses[*count].category > 5) {
        printf("Invalid category. Enter a number from 1 to 5: ");
        clearInputBuffer();
    }

    (*count)++;
    printf("\nExpense added successfully!\n");
}


void viewExpenses(struct Expense expenses[], int count) {
    int i;

    if (count == 0) {
        printf("\nNo expenses recorded yet.\n");
        return;
    }

    printf("\n========== ALL EXPENSES ==========\n");

    for (i = 0; i < count; i++) {
        printf("\nExpense %d\n", i + 1);
        printf("Description : %s\n", expenses[i].description);
        printf("Amount      : Rs. %.2f\n", expenses[i].amount);

        printf("Category    : ");
        switch (expenses[i].category) {
            case 1:
                printf("Food\n");
                break;

            case 2:
                printf("Travel\n");
                break;

            case 3:
                printf("Books\n");
                break;

            case 4:
                printf("Entertainment\n");
                break;

            case 5:
                printf("Other\n");
                break;
        }
    }
}


void showSummary(struct Expense expenses[], int count, float budget) {
    float categoryTotal[CATEGORY_COUNT] = {0};
    float total = 0;
    float remaining;
    int i;
    int highestCategory = 0;

    if (count == 0) {
        printf("\nNo expenses recorded yet.\n");
        return;
    }

    for (i = 0; i < count; i++) {
        total = total + expenses[i].amount;

        categoryTotal[expenses[i].category - 1] =
            categoryTotal[expenses[i].category - 1] + expenses[i].amount;
    }

    remaining = budget - total;

    
    for (i = 1; i < CATEGORY_COUNT; i++) {
        if (categoryTotal[i] > categoryTotal[highestCategory]) {
            highestCategory = i;
        }
    }

    printf("\n========== EXPENSE SUMMARY ==========\n");
    printf("Monthly Budget    : Rs. %.2f\n", budget);
    printf("Total Spending    : Rs. %.2f\n", total);
    printf("Remaining Budget  : Rs. %.2f\n", remaining);

    printf("\nCategory-wise Spending:\n");
    printf("Food              : Rs. %.2f\n", categoryTotal[0]);
    printf("Travel            : Rs. %.2f\n", categoryTotal[1]);
    printf("Books             : Rs. %.2f\n", categoryTotal[2]);
    printf("Entertainment     : Rs. %.2f\n", categoryTotal[3]);
    printf("Other             : Rs. %.2f\n", categoryTotal[4]);

    printf("\nHighest Expenditure : ");

    switch (highestCategory) {
        case 0:
            printf("Food\n");
            break;

        case 1:
            printf("Travel\n");
            break;

        case 2:
            printf("Books\n");
            break;

        case 3:
            printf("Entertainment\n");
            break;

        case 4:
            printf("Other\n");
            break;
    }

    if (total > budget) {
        printf("\nWARNING: You have exceeded your monthly budget!\n");
        printf("Amount exceeded: Rs. %.2f\n", total - budget);
    }
    else if (total == budget) {
        printf("\nYour entire monthly budget has been used.\n");
    }
    else {
        printf("\nYou are within your monthly budget.\n");
    }
}


int main() {

    struct Expense expenses[MAX_EXPENSES];

    int expenseCount = 0;
    int choice;
    float budget;

    printf("========================================\n");
    printf("       PERSONAL EXPENSE TRACKER\n");
    printf("========================================\n");

   
    printf("\nEnter your monthly budget: ");

    while (scanf("%f", &budget) != 1 || budget <= 0) {
        printf("Invalid budget. Enter a positive number: ");
        clearInputBuffer();
    }

    do {

        printf("\n\n========== MAIN MENU ==========\n");
        printf("1. Add Expense\n");
        printf("2. View All Expenses\n");
        printf("3. View Expense Summary\n");
        printf("4. View Categories\n");
        printf("5. Exit\n");
        printf("===============================\n");

        printf("Enter your choice: ");

        while (scanf("%d", &choice) != 1 ||
               choice < 1 ||
               choice > 5) {

            printf("Invalid choice. Enter a number from 1 to 5: ");
            clearInputBuffer();
        }

        switch (choice) {

            case 1:
                addExpense(expenses, &expenseCount);
                break;

            case 2:
                viewExpenses(expenses, expenseCount);
                break;

            case 3:
                showSummary(expenses, expenseCount, budget);
                break;

            case 4:
                displayCategories();
                break;

            case 5:
                printf("\nThank you for using Personal Expense Tracker!\n");
                break;
        }

    } while (choice != 5);

    return 0;
}
