#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "bank_data.txt"

struct BankAccount {
    int accountNumber;
    char accountHolder[100];
    float balance;
};

void saveAccount(struct BankAccount *account) {
    FILE *file = fopen(FILENAME, "ab");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fwrite(account, sizeof(struct BankAccount), 1, file);
    fclose(file);
}

void loadAccounts() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    struct BankAccount account;
    while (fread(&account, sizeof(struct BankAccount), 1, file) == 1) {
        printf("Account Number: %d\n", account.accountNumber);
        printf("Account Holder: %s\n", account.accountHolder);
        printf("Balance: %.2f\n", account.balance);
        printf("\n");
    }
    fclose(file);
}

void createAccount() {
    struct BankAccount newAccount;
    printf("Enter Account Number: ");
    scanf("%d", &newAccount.accountNumber);
    printf("Enter Account Holder Name: ");
    scanf("%s", newAccount.accountHolder);
    newAccount.balance = 0.0;
    saveAccount(&newAccount);
    printf("Account created successfully!\n");
}

void deposit() {
    int accountNumber;
    float amount;
    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);
    FILE *file = fopen(FILENAME, "rb+");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    struct BankAccount account;
    int found = 0;
    while (fread(&account, sizeof(struct BankAccount), 1, file) == 1) {
        if (account.accountNumber == accountNumber) {
            found = 1;
            printf("Enter the deposit amount: ");
            scanf("%f", &amount);
            account.balance += amount;
            fseek(file, -sizeof(struct BankAccount), SEEK_CUR);
            fwrite(&account, sizeof(struct BankAccount), 1, file);
            printf("Deposit successful. New balance: %.2f\n", account.balance);
            break;
        }
    }
    fclose(file);
    if (!found) {
        printf("Account not found!\n");
    }
}

// Implement similar functions for withdrawal and balance check 

int main() {
    int choice;
    do {
        printf("\n1. Create Account\n2. Deposit\n3. Withdraw\n4. Check Balance\n5. View All Accounts\n0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            // Implement cases for withdrawal, balance check, and viewing all accounts
            case 5:
                loadAccounts();
                break;
            case 0:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
    return 0;
}
