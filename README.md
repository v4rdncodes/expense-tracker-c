# Expense Tracker (C Project)

## Overview

**Expense Tracker** is a simple command-line application written in C that helps users manage their finances. It allows you to create multiple accounts, record and categorize expenses and income, set budgets, and track your progress toward savings goals. All actions are logged for future reference, making it a useful tool for personal finance management.

## Features

- **User Authentication:** Simple login system for security.
- **Account Management:**
  - Create, view, modify (rename or change currency rate), and delete accounts.
  - Support for multiple accounts with different currencies.
- **Transaction Management:**
  - Add, edit, search, and delete transactions.
  - Categorize transactions (e.g., Shopping, Housing, Food & Drinks, etc.) with optional sub-categories.
  - View all transactions or search by category, date, or description.
- **Income Management:** Add income to any account and update balances.
- **Budgeting:**
  - Create, rename, and delete custom categories.
  - Set and display budget limits for each category.
  - Receive warnings when exceeding category budgets.
- **Goal Tracking:**
  - Set a savings goal and track progress.
  - Receive notifications upon reaching your goal.
- **Financial Overview:**
  - Display all accounts and their balances.
  - Show total assets after expenses.
  - View cash flow (total income vs. total expenses).
- **Persistent Logging:** All changes and important actions are saved to `expense_tracker.txt` for record-keeping.

## Menu Options

| Option | Description                        |
|--------|------------------------------------|
| 1      | Create Account                     |
| 2      | Show All Accounts                  |
| 3      | Show Specific Account              |
| 4      | Delete Account                     |
| 5      | Modify Account                     |
| 6      | Add Income                         |
| 7      | Manage Categories                  |
| 8      | Add Transaction                    |
| 9      | Show All Transactions              |
| 10     | Search Transactions                |
| 11     | Delete Transaction by Index        |
| 12     | Delete Transaction by Search       |
| 13     | Set Category Budget                |
| 14     | Show Category Budget               |
| 15     | Show Assets                        |
| 16     | Set Goal                           |
| 17     | Cash Flow                          |
| 18     | Edit Transaction                   |
| 19     | Exit                               |

## Getting Started

1. **Compile the code:**
2. **Run the application:**
3. 3. **Login Credentials (default):**
- Username: `user`
- Password: `password123`

## Notes

- All data is stored in memory during runtime; logs are appended to `expense_tracker.txt`.
- Maximum limits: 50 accounts, 1000 transactions, and 20 categories.
- The application is designed for educational and personal use.

## Authors

- Arnav Goel
- Vardan Srivastava
- Varneet Sharma
- Yash Sharda

*We hope you find this Expense Tracker helpful for managing your finances!*
