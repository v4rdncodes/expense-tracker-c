#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX_ACCOUNTS 50
#define MAX_TRANSACTIONS 1000
#define MAX_CATEGORIES 20
#define MAX_DESC_LENGTH 100
#define MAX_CATEGORY_LENGTH 50
#define MAX_NAME_LENGTH 50
#define MAX_BUDGET 1000000

// Structure for account
typedef struct
{
    char name[MAX_NAME_LENGTH];
    double balance;
    double currency_rate;
} Account;

// Structure for transaction
typedef struct
{
    char category[MAX_CATEGORY_LENGTH];
    char sub_category[MAX_CATEGORY_LENGTH];
    double amount;
    char description[MAX_DESC_LENGTH];
    char date[MAX_DESC_LENGTH]; 
} Transaction;

// Union for categories and subcategories 
typedef union
{
    char category_name[MAX_CATEGORY_LENGTH];
    char sub_category_name[MAX_CATEGORY_LENGTH];
} CategoryUnion;


// Main arrays for accounts, transactions, and categories
Account accounts[MAX_ACCOUNTS];
Transaction transactions[MAX_TRANSACTIONS];
CategoryUnion categories[MAX_CATEGORIES];

// Budget limits 
double category_budgets[MAX_CATEGORIES];

// Function Prototypes
void welcomeMessage();
void createAccount();
void showAllAccounts();
void showSpecificAccount();
void deleteAccount();
void modifyAccount();
void addIncome();
void manageCategory();
void addTransaction();
void showAllTransactions();
void searchTransaction();
void deleteTransaction();
void deleteTransactionBySearch();
void setCategoryBudget();
void showCategoryBudget();
void showAssets();
void setGoal();
void showCashFlow();
void editTransaction();
void displayTaskSuccess(const char *task);
void writeToFile(const char *message);
int accountCount = 0;
int transactionCount = 0;
int categoryCount = 0;


void welcomeMessage()
{
    printf("\n");
    printf("=================   HELLO   =======================\n");
    printf("                     AND                           \n");
    printf("        Welcome to the Expense Tracker!            \n");
    printf("\n");
}

// Task Success
void displayTaskSuccess(const char *task)
{
    printf("\nTask completed successfully: %s\n", task);
}

// Function for writing formatted data to a file
// file handelling

void writeToFile(const char *message)
{
    FILE *file = fopen("expense_tracker.txt", "a"); 
    if (file == NULL)
    {
        printf("Error: Could not open file.\n");
        return;
    }

    fprintf(file, "%s\n", message); 
    fclose(file);                   
}

//
// User login function
// for security

void userLogin()
{
    char username[MAX_NAME_LENGTH], password[MAX_DESC_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

   

    if (strcmp(username, "user") == 0 && strcmp(password, "password123") == 0)
    {
        printf("Login successful!\n");
    }
    else
    {
        printf("Invalid username or password.\n");
        exit(0);
    }
}

// Create Account
// add amount in the account also in any currency
// User can create multiple accounts here

void createAccount()
{
    if (accountCount >= MAX_ACCOUNTS)
    {
        printf("Error: Cannot create more accounts. Maximum reached.\n");
        return;
    }

    printf("Enter account name: ");
    scanf("%s", accounts[accountCount].name);
    accounts[accountCount].balance = 0.0;
    accounts[accountCount].currency_rate = 1.0; 

   
    FILE *file = fopen("expense_tracker.txt", "a");
    if (file == NULL)
    {
        printf("Error: Could not open file.\n");
        return;
    }
    fprintf(file, "Account Created: Name=%s, Balance=%.2f, CurrencyRate=%.2f\n",
            accounts[accountCount].name, accounts[accountCount].balance, accounts[accountCount].currency_rate);
    fclose(file); 

    accountCount++;
    displayTaskSuccess("Account created");
}

// Delete Account
// this is to delete an account by searching it via its name
// it shifts the account by deleting specific account

void deleteAccount()
{
    char accountName[MAX_NAME_LENGTH];
    printf("Enter the name of the account to delete: ");
    scanf("%s", accountName);

    for (int i = 0; i < accountCount; i++)
    {

        if (strcmp(accounts[i].name, accountName) == 0)
        {

            // Shift all accounts after the deleted one

            for (int j = i; j < accountCount - 1; j++)
            {

                accounts[j] = accounts[j + 1];
            }

            accountCount--;
            
            FILE *file = fopen("expense_tracker.txt", "a");  
            if (file != NULL)
            {
                fprintf(file, "Account Deleted: Name=%s\n", accountName);  
                fclose(file); 
            }
            else
            {
                printf("Error: Could not open the file to log deletion.\n");
            }
            displayTaskSuccess("Account deleted");
            return;
        }
    }
    printf("Error: Account not found.....\n");
    printf("Please Check again......\n");
}

// Modify Account
// To rename account or make changes to specific account
// User can serch account by name
// To Change currency rates

void modifyAccount()
{
    char accountName[MAX_NAME_LENGTH];
    printf("Enter the name of the account to modify: ");
    scanf("%s", accountName);

    for (int i = 0; i < accountCount; i++)
    {
        if (strcmp(accounts[i].name, accountName) == 0)
        {
            printf("What would you like to do.....\n");
            printf("1. Rename Account\n");
            printf("2. Change Currency Rate\n");
            printf("Select an option: ");
            int choice;
            scanf("%d", &choice);

            if (choice == 1)
            {
                
                char newAccountName[MAX_NAME_LENGTH];
                printf("Enter the new name for the account: ");
                scanf("%s", newAccountName);
                strcpy(accounts[i].name, newAccountName);  

            
                FILE *file = fopen("expense_tracker.txt", "a"); 
                if (file != NULL)
                {
                    fprintf(file, "Account Renamed: OldName=%s, NewName=%s\n", accountName, newAccountName); 
                    fclose(file); 
                }
                else
                {
                    printf("Error: Could not open file to log renaming.\n");
                }

                displayTaskSuccess("Your Account has been renamed");
            }
            else if (choice == 2)
            {
               
                double newCurrencyRate;
                printf("Enter the new currency rate: ");
                scanf("%lf", &newCurrencyRate);
                accounts[i].currency_rate = newCurrencyRate;  // Update the currency rate

              
                FILE *file = fopen("expense_tracker.txt", "a");  
                if (file != NULL)
                {
                    fprintf(file, "Currency Rate Updated: Account=%s, NewRate=%.2f\n", accountName, newCurrencyRate);  
                    fclose(file);  
                }
                else
                {
                    printf("Error: Could not open file to log currency rate update.\n");
                }

                displayTaskSuccess("Currency rate updated");
            }
            else
            {
                printf("Error: Invalid choice.\n");
                printf("Select 1 or 2\n");
            }
            return;
        }
    }

    printf("Error: Account not found.\n");
    printf("Please Check again......\n");
}

// Show All Accounts
// User can check all details of all accounts

void showAllAccounts()
{

    printf("\nAll Accounts:\n");
    for (int i = 0; i < accountCount; i++)
    {

        printf("%d. Account Name: %s | Balance: %.2f INR | Currency Rate: %.2f\n",
               i + 1, accounts[i].name, accounts[i].balance, accounts[i].currency_rate);
    }
}

// Add transaction
// User can add its transaction
// select account from which money is debited
// input details like date, amount, category
// it has option to write description about the transaction

void addTransaction()
{
    if (accountCount == 0)
    {
        printf("Error: No accounts found....... \n");
        printf("Please create an account before adding a transaction.\n");
        return;
    }

    char accountName[MAX_NAME_LENGTH];
    char description[MAX_DESC_LENGTH];
    char date[MAX_DESC_LENGTH];
    double amount;
    int accountIndex = -1;
    int categoryChoice;
    char subCategory[MAX_CATEGORY_LENGTH];

    // Display available categories to select
    // these are predefined categories

    printf("Select a category for the transaction:\n");

    printf("1. SHOPPING\n");

    printf("2. HOUSING\n");

    printf("3. TRANSPORTATION\n");

    printf("4. INVESTMENT\n");

    printf("5. INCOME\n");

    printf("6. ENTERTAINMENT\n");

    printf("7. VEHICLE\n");

    printf("8. FOOD & DRINKS\n");

    printf("Enter the number corresponding to the category: ");

    scanf("%d", &categoryChoice);

    if (categoryChoice < 1 || categoryChoice > 8)
    {
        printf("Error: Invalid category choice.\n");
        return;
    }

    const char *categories[] = {
        "SHOPPING", "HOUSING", "TRANSPORTATION", "INVESTMENT",
        "INCOME", "ENTERTAINMENT", "VEHICLE", "FOOD_DRINKS"};

    // Set category for the transaction
    strcpy(transactions[transactionCount].category, categories[categoryChoice - 1]);

    printf("Enter sub-category (optional): ");
    scanf(" %[^\n]%*c", subCategory); 
    strcpy(transactions[transactionCount].sub_category, subCategory);

    // Proceed with rest of the transaction details
    printf("Enter account name: ");
    scanf("%s", accountName);

    // Check if the account exists
    for (int i = 0; i < accountCount; i++)
    {
        if (strcmp(accounts[i].name, accountName) == 0)
        {
            accountIndex = i;
            break;
        }
    }

    if (accountIndex == -1)
    {
        printf("Error: Account not found. Please check the account name.\n");
        return;
    }

    printf("Enter amount: ");
    scanf("%lf", &amount);

    if (amount <= 0)
    {
        printf("Error: Amount must be positive.\n");
        return;
    }

    printf("Enter description: ");
    scanf(" %[^\n]%*c", description); 

    printf("Enter date (yyyy-mm-dd): ");
    scanf("%s", date);

    // deduct the amount from the account balance

    if (accounts[accountIndex].balance >= amount)
    {
        accounts[accountIndex].balance -= amount;
    }
    else
    {
        printf("Error: Insufficient balance in the account.\n");
        return;
    }

    // add the transaction

    strcpy(transactions[transactionCount].category, categories[categoryChoice - 1]);
    strcpy(transactions[transactionCount].sub_category, subCategory);
    transactions[transactionCount].amount = amount;
    strcpy(transactions[transactionCount].description, description);
    strcpy(transactions[transactionCount].date, date);

    transactionCount++;
    displayTaskSuccess("Transaction added");


    printf("Updated balance for account '%s': %.2f INR\n", accounts[accountIndex].name, accounts[accountIndex].balance);

   
    FILE *file = fopen("expense_tracker.txt", "a");
    if (file == NULL)
    {
        printf("Error: Could not open file.\n");
        return;
    }
    fprintf(file, "Transaction Added: Date=%s, Category=%s, Sub-category=%s, Amount=%.2f, Description=%s\n",
            date, categories[categoryChoice - 1], subCategory, amount, description);
    fclose(file);

    displayTaskSuccess("Transaction added");
    printf("Updated balance for account '%s': %.2f INR\n", accounts[accountIndex].name, accounts[accountIndex].balance);
}

// Show All Transactions
// It shows all the transaction with details

void showAllTransactions()
{

    printf("\nAll Transactions:\n");
    for (int i = 0; i < transactionCount; i++)
    {

        printf("%d. Date: %s | Category: %s | Sub-category: %s | Amount: %.2f | Description: %s\n",
               i + 1, transactions[i].date, transactions[i].category, transactions[i].sub_category,
               transactions[i].amount, transactions[i].description);
    }
}

// Add Income to an Account
// Add income in the specific account

void addIncome()
{

    char accountName[MAX_NAME_LENGTH];
    double incomeAmount;
    int accountIndex = -1;

    printf("Enter account name to add income: ");
    scanf("%s", accountName);

    // To Check if the account exists

    for (int i = 0; i < accountCount; i++)
    {
        if (strcmp(accounts[i].name, accountName) == 0)
        {
            accountIndex = i;
            break;
        }
    }

    if (accountIndex == -1)
    {
        printf("Error: Account not found.......\n Please check the account name.\n");
        return;
    }

    printf("Enter income amount: ");
    scanf("%lf", &incomeAmount);

    // To Add the income to the account balance

    accounts[accountIndex].balance += incomeAmount;
    displayTaskSuccess("Income added to account");

   
    FILE *file = fopen("expense_tracker.txt", "a");
    if (file == NULL)
    {
        printf("Error: Could not open file.\n");
        return;
    }
    fprintf(file, "Income Added: Account=%s, Amount=%.2f\n", accounts[accountIndex].name, incomeAmount);
    fclose(file);

    displayTaskSuccess("Income added to account");
    printf("Updated balance for account '%s': %.2f INR\n", accounts[accountIndex].name, accounts[accountIndex].balance);



    printf("Updated balance for account '%s': %.2f INR\n", accounts[accountIndex].name, accounts[accountIndex].balance);
}

// To show assests
// It shows net money available

void showAssets()
{

    double totalAssets = 0.0;

    for (int i = 0; i < accountCount; i++)
    {
        totalAssets += accounts[i].balance;
    }

    for (int i = 0; i < transactionCount; i++)
    {
        totalAssets -= transactions[i].amount; 
    }

    printf("Total Assets (after subtracting transactions): %.2f INR\n", totalAssets);
}

// to show specific accounts by name
// search via name of account

void showSpecificAccount()
{

    char accountName[MAX_NAME_LENGTH];
    int accountIndex = -1;

    printf("Enter account name to display: ");
    scanf("%s", accountName);

    for (int i = 0; i < accountCount; i++)
    {
        if (strcmp(accounts[i].name, accountName) == 0)
        {
            accountIndex = i;
            break;
        }
    }

    if (accountIndex == -1)
    {
        printf("Error: Account not found.\n");
    }
    else
    {

        printf("\nAccount Name: %s | Balance: %.2f INR | Currency Rate: %.2f\n",
               accounts[accountIndex].name, accounts[accountIndex].balance, accounts[accountIndex].currency_rate);
    }
}

// Set a Budget for Categories
// Make budget of different categories

void setCategoryBudget()
{
    char category[MAX_CATEGORY_LENGTH];
    double budgetAmount;

    printf("Enter category to set budget: ");
    scanf("%s", category);

    printf("Enter budget amount: ");
    scanf("%lf", &budgetAmount);


    for (int i = 0; i < categoryCount; i++)
    {
        if (strcmp(categories[i].category_name, category) == 0)
        {
            category_budgets[i] = budgetAmount;

            
            FILE *file = fopen("expense_tracker.txt", "a");  
            if (file != NULL)
            {
                fprintf(file, "Category Budget Set: Category=%s, Budget=%.2f INR\n", category, budgetAmount); 
                fclose(file);  
            }
            else
            {
                printf("Error: Could not open file to log budget setting.\n");
            }

            printf("Budget set for category '%s' as %.2f INR\n", category, budgetAmount);
            return;
        }
    }
    printf("Category not found.\n");
}
void checkCategoryBudget(int categoryIndex, double amountSpent)
{
    if (category_budgets[categoryIndex] > 0 && amountSpent > category_budgets[categoryIndex])
    {
        printf("Warning: You have exceeded the budget for this category!\n");

        
        FILE *file = fopen("expense_tracker.txt", "a");  
        if (file != NULL)
        {
            fprintf(file, "Warning: Budget Exceeded for Category=%d, AmountSpent=%.2f, Budget=%.2f\n",
                    categoryIndex, amountSpent, category_budgets[categoryIndex]); 
            fclose(file);  
        }
        else
        {
            printf("Error: Could not open file to log budget warning.\n");
        }
    }
}


// search transaction
// Search Transaction via date category or description

void searchTransaction()
{

    char searchTerm[MAX_DESC_LENGTH];
    int found = 0;

    printf("Enter search term (category, date, or description): ");
    scanf(" %[^\n]%*c", searchTerm); 

    printf("\nSearch Results:\n");
    for (int i = 0; i < transactionCount; i++)
    {

        if (strstr(transactions[i].category, searchTerm) != NULL ||
            strstr(transactions[i].date, searchTerm) != NULL ||
            strstr(transactions[i].description, searchTerm) != NULL)
        {
            printf("%d. Date: %s | Category: %s | Sub-category: %s | Amount: %.2f | Description: %s\n",
                   i + 1, transactions[i].date, transactions[i].category, transactions[i].sub_category,
                   transactions[i].amount, transactions[i].description);
            found = 1;
        }
    }

    if (!found)
    {

        printf("No transactions found matching the search term '%s'.\n", searchTerm);
    }
}

// Show Category Budget
// it shows budget set for categories

void showCategoryBudget()
{

    char category[MAX_CATEGORY_LENGTH];
    printf("Enter category to show budget: ");
    scanf("%s", category);

    for (int i = 0; i < categoryCount; i++)
    {
        if (strcmp(categories[i].category_name, category) == 0)
        {
            printf("Budget for category %s: %.2f\n", category, category_budgets[i]);
            return;
        }
    }
    printf("Error: Category not found.\n");
}

// Goal
// to define goal to save specific amount
// alert the user when goal is completed

double goalAmount = 0.0;
double currentSavings = 0.0;

void setGoal()
{
    printf("Enter the amount you need to save: ");
    scanf("%lf", &goalAmount);
    printf("Goal of %.2f INR set.\n", goalAmount);

   
    FILE *file = fopen("expense_tracker.txt", "a");  
    if (file != NULL)
    {
        fprintf(file, "Savings Goal Set: GoalAmount=%.2f INR\n", goalAmount);  
        fclose(file);  
    }
    else
    {
        printf("Error: Could not open file to log goal setting.\n");
    }
}

void addToGoal()
{
    double amount;
    printf("Enter the amount to add to your savings goal: ");
    scanf("%lf", &amount);

    currentSavings += amount;

  
    FILE *file = fopen("expense_tracker.txt", "a");  
    if (file != NULL)
    {
        fprintf(file, "Amount Added to Goal: Amount=%.2f INR, CurrentSavings=%.2f INR\n", amount, currentSavings);  
        fclose(file);  
    }
    else
    {
        printf("Error: Could not open file to log amount added.\n");
    }

   
    if (currentSavings >= goalAmount)
    {
        printf("Congratulations! You have reached your savings goal!\n");

      
        file = fopen("expense_tracker.txt", "a");  
        if (file != NULL)
        {
            fprintf(file, "Savings Goal Reached: TotalSavings=%.2f INR, GoalAmount=%.2f INR\n", currentSavings, goalAmount);  
            fclose(file);  
        }
        else
        {
            printf("Error: Could not open file to log goal completion.\n");
        }
    }
    else
    {
        printf("Current savings towards goal: %.2f INR\n", currentSavings);
    }
}


// Cash flow
// it shows total income vs total expenses

void showCashFlow()
{

    double totalIncome = 0.0;
    double totalExpenses = 0.0;

    for (int i = 0; i < transactionCount; i++)
    {
        if (strcmp(transactions[i].category, "Income") == 0)
        {
            totalIncome += transactions[i].amount;
        }
        else
        {
            totalExpenses += transactions[i].amount;
        }
    }

    printf("Total Income: %.2f INR\n", totalIncome);
    printf("Total Expenses: %.2f INR\n", totalExpenses);
}

// Delete Transaction
// To delete any transaction by its index
// here indexing starts from 1 for ease

void deleteTransaction()
{
    int transactionIndex;
    printf("Enter transaction index to delete: ");
    scanf("%d", &transactionIndex);

    if (transactionIndex >= 1 && transactionIndex <= transactionCount)
    {
        
        FILE *file = fopen("expense_tracker.txt", "a");  
        if (file != NULL)
        {
            fprintf(file, "Transaction Deleted: Index=%d, Date=%s, Category=%s, Amount=%.2f, Description=%s\n",
                    transactionIndex, transactions[transactionIndex - 1].date,
                    transactions[transactionIndex - 1].category,
                    transactions[transactionIndex - 1].amount,
                    transactions[transactionIndex - 1].description);  
            fclose(file);  
        }
        else
        {
            printf("Error: Could not open file to log transaction deletion.\n");
        }

        
        for (int i = transactionIndex - 1; i < transactionCount - 1; i++)
        {
            transactions[i] = transactions[i + 1];
        }
        transactionCount--;

        displayTaskSuccess("Transaction deleted");
    }
    else
    {
        printf("Error: Invalid transaction index.\n");
    }
}


// Delete Transaction
// by searching via Category , Date or Description

void deleteTransactionBySearch()
{
    char searchTerm[MAX_DESC_LENGTH];
    int foundIndexes[MAX_TRANSACTIONS];
    int foundCount = 0;

    printf("Enter search term (category, date, or description): ");
    scanf(" %[^\n]%*c", searchTerm); 

    printf("\nMatching Transactions:\n");
    for (int i = 0; i < transactionCount; i++)
    {

        if (strstr(transactions[i].category, searchTerm) != NULL ||

            strstr(transactions[i].sub_category, searchTerm) != NULL ||

            strstr(transactions[i].description, searchTerm) != NULL ||

            strstr(transactions[i].date, searchTerm) != NULL)
        {
            printf("%d. Date: %s | Category: %s | Sub-category: %s | Amount: %.2f | Description: %s\n",
                   foundCount + 1, transactions[i].date, transactions[i].category, transactions[i].sub_category,
                   transactions[i].amount, transactions[i].description);
            foundIndexes[foundCount] = i; 
            foundCount++;
        }
    }

    if (foundCount == 0)
    {
        printf("No matching transactions found.\n");
        return;
    }

    printf("\nEnter the number of the transaction to delete (1 to %d): ", foundCount);
    int deleteIndex;
    scanf("%d", &deleteIndex);

    if (deleteIndex >= 1 && deleteIndex <= foundCount)
    {
        //  deleteIndex to the actual transaction index

        int transactionIndex = foundIndexes[deleteIndex - 1];
        for (int i = transactionIndex; i < transactionCount - 1; i++)
        {
            transactions[i] = transactions[i + 1];
        }
        transactionCount--;
        displayTaskSuccess("Transaction deleted");
    }
    else
    {
        printf("Error: Invalid choice.\n");
    }
}


//Edit Transaction
// to edit details of transaction

void editTransaction()
{
    int transactionIndex;
    printf("Enter the transaction index to edit: ");
    scanf("%d", &transactionIndex);

    if (transactionIndex >= 1 && transactionIndex <= transactionCount)
    {
        printf("Edit details for transaction %d:\n", transactionIndex);
        printf("Enter new amount: ");
        scanf("%lf", &transactions[transactionIndex - 1].amount);
        printf("Enter new description: ");
        scanf(" %[^\n]%*c", transactions[transactionIndex - 1].description);

        
        FILE *file = fopen("expense_tracker.txt", "a");  
        if (file != NULL)
        {
            fprintf(file, "Transaction Edited: Index=%d, NewAmount=%.2f, NewDescription=%s\n",
                    transactionIndex, transactions[transactionIndex - 1].amount, transactions[transactionIndex - 1].description);  
            fclose(file); 
        }
        else
        {
            printf("Error: Could not open file to log transaction edit.\n");
        }

        printf("Transaction edited successfully.\n");
    }
    else
    {
        printf("Error: Invalid transaction index.\n");
    }
}





// Manage Categories
// Create, Rename, Delete

void manageCategory()
{
    int choice;
    printf("\n1. Create Category\n ");
    printf("\n2. Rename Category\n ");
    printf("\n3. Delete Category\n ");
    printf("\nChoose any one option\n");

    scanf("%d", &choice);

    if (choice == 1)
    {
        if (categoryCount >= MAX_CATEGORIES)
        {
            printf("Error: Cannot create more categories. Maximum reached.\n");
            return;
        }
        printf("Enter category name to create: ");
        scanf("%s", categories[categoryCount].category_name);
        category_budgets[categoryCount] = 0.0;
        categoryCount++;
        displayTaskSuccess("Category created");
    }
    else if (choice == 2)
    {

        char oldCategory[MAX_CATEGORY_LENGTH], newCategory[MAX_CATEGORY_LENGTH];
        printf("Enter old category name: ");
        scanf("%s", oldCategory);
        printf("Enter new category name: ");
        scanf("%s", newCategory);

        for (int i = 0; i < categoryCount; i++)
        {
            if (strcmp(categories[i].category_name, oldCategory) == 0)
            {
                strcpy(categories[i].category_name, newCategory);
                displayTaskSuccess("Category renamed");
                return;
            }
        }
        printf("Error: Category not found.\n");
    }
    else if (choice == 3)
    {

        char category[MAX_CATEGORY_LENGTH];
        printf("Enter category name to delete: ");
        scanf("%s", category);

        for (int i = 0; i < categoryCount; i++)
        {
            if (strcmp(categories[i].category_name, category) == 0)
            {
                for (int j = i; j < categoryCount - 1; j++)
                {
                    categories[j] = categories[j + 1];
                }
                categoryCount--;
                displayTaskSuccess("Category deleted");
                return;
            }
        }
        printf("Error: Category not found.\n");
    }
    else
    {
        printf("Error: Invalid choice.\n");
    }
}

// Main Menu
// Interface
void mainMenu()
{
    int choice;

    while (1)
    {

        printf("===============================================\n");
        
        printf("==                                           ==\n");
        
        printf("==       Welcome to the Expense Tracker      ==\n");
        
        printf("==             Application $$$               ==\n");
        
        printf("==                                           ==\n");
        
        printf("===============================================\n");
        
        printf("\n");
        
        printf("-------------------------------------------------\n");
        
        printf("-------------------------------------------------\n");
        
        printf("-------------------------------------------------\n");
        
        printf("Track your spending, analyze your habits, and\n");
        
        printf("make informed financial decisions easily.\n");
        
        printf("-------------------------------------------------\n");
        
        printf("-------------------------------------------------\n");
        
        printf("-------------------------------------------------\n");
        
        printf("\n");
        
        printf("Here's what you can do:\n");
        
        printf("\n");
        
        printf("1. Add your daily expenses.\n");
        
        printf("\n");
        
        printf("2. View your total spending.\n");
        
        printf("\n");
        
        printf("3. Analyze trends and keep track of your budget.\n");
        
        printf("\n");
        
        printf("Let's begin managing your finances today!\n");
        
        printf("-------------------------------------------------\n");
        
        printf("-------------------------------------------------\n");

        printf("1. Create Account\n");

        printf("2. Show All Accounts\n");

        printf("3. Show Specific Account\n");

        printf("4. Delete Account\n");

        printf("5. Modify Account\n");

        printf("6. Add Income\n");

        printf("7. Manage Categories\n");

        printf("8. Add Transaction\n");

        printf("9. Show All Transactions\n");

        printf("10. Search Transactions\n");

        printf("11. Delete Transaction by Index\n");

        printf("12. Delete Transaction by Search\n");

        printf("13. Set Category Budget\n");

        printf("14. Show Category Budget\n");

        printf("15. Show assests\n");

        printf("16. Set Goal\n");

        printf("17. Cash Flow\n");

        printf("18. Edit Transaction\n");

        

        printf("19. Exit\n");

        printf("Choose an option: ");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createAccount();
            break;

        case 2:
            showAllAccounts();
            break;

        case 3:
            showSpecificAccount();
            break;

        case 4:
            deleteAccount();
            break;

        case 5:
            modifyAccount();
            break;

        case 6:
            addIncome();
            break;

        case 7:
            manageCategory();
            break;

        case 8:
            addTransaction();
            break;

        case 9:
            showAllTransactions();
            break;

        case 10:
            searchTransaction();
            break;

        case 11:
            deleteTransaction();
            break;

        case 12:
            deleteTransactionBySearch();
            break;

        case 13:
            setCategoryBudget();
            break;

        case 14:
            showCategoryBudget();
            break;

        case 15:
            showAssets();
            break;

        case 16:
            setGoal();
            break;

        case 17:
            showCashFlow();
            break;

        case 18:
            editTransaction();
            break;

        

        case 19:
            printf("Exiting Expense Tracker. Goodbye!\n");
            printf("\nThank you\n");
            printf("\nTHIS CODE IS MADE BY...\n");
            printf("\n1. ARNAV GOEL\n");
            printf("\n2. VARDAN SRIVASTAVA\n");
            printf("\n3. VARNEET SHARMA\n");
            printf("\n4. YASH SHARDA\n");
            printf("\nWE HOPE YOU LIKED OUR EXPENSE TRACKER APPLICATION\n");

            return;
        default:

            printf("Error: Invalid option. Please try again.\n");
        }
    }
}

int main()
{
    userLogin();
    welcomeMessage();
    mainMenu();
    return 0;
}