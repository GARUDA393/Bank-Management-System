#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures for customer and account
typedef struct {
    int customerID;
    char name[50];
    char address[100];
    char phone[15];
    char email[50];
    char password[20]; // Adding password field for customers
} Customer;

typedef struct {
    int accountNumber;
    int customerID;
    float balance;
    char password[20]; // Adding password field for accounts
} Account;

// Define globals
Customer customers[100];
Account accounts[100];
int numCustomers = 0;
int numAccounts = 0;

// Function prototypes
void addCustomer();
void openAccount();
void processTransaction();
int authenticateCustomer(int customerID, char *password);
int authenticateAccount(int accountNumber, char *password);
void encrypt(char *data);
void decrypt(char *data);

// Function to add a new customer
void addCustomer() {
    Customer newCustomer;
    
    printf("Enter customer name: ");
    scanf("%s", newCustomer.name);
    printf("Enter address: ");
    scanf("%s", newCustomer.address);
    printf("Enter phone number: ");
    scanf("%s", newCustomer.phone);
    printf("Enter email: ");
    scanf("%s", newCustomer.email);
    printf("Set password: ");
    scanf("%s", newCustomer.password); // Set password for the customer
    
    encrypt(newCustomer.password); // Encrypt the password before storing
    
    newCustomer.customerID = numCustomers + 1;
    customers[numCustomers++] = newCustomer;
}

// Function to open a new account for an existing customer
void openAccount() {
    int customerID;
    printf("Enter customer ID: ");
    scanf("%d", &customerID);

    Account newAccount;
    newAccount.customerID = customerID;
    newAccount.accountNumber = 1000 + numAccounts + 1;
    newAccount.balance = 0.0;
    printf("Set account password: ");
    scanf("%s", newAccount.password); // Set password for the account
    
    encrypt(newAccount.password); // Encrypt the password before storing
    
    accounts[numAccounts++] = newAccount;
    printf("Account opened successfully with account number: %d\n", newAccount.accountNumber);
}

// Function to process a transaction
void processTransaction() {
    int accountNumber;
    float amount;
    char type[10];
    char password[20];
    
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    printf("Enter account password: ");
    scanf("%s", password);
    
    if (authenticateAccount(accountNumber, password)) {
        printf("Enter transaction type (deposit/withdraw): ");
        scanf("%s", type);
        printf("Enter amount: ");
        scanf("%f", &amount);

        for (int i = 0; i < numAccounts; i++) {
            if (accounts[i].accountNumber == accountNumber) {
                if (strcmp(type, "deposit") == 0) {
                    accounts[i].balance += amount;
                    printf("Deposit successful. New balance: %.2f\n", accounts[i].balance);
                } else if (strcmp(type, "withdraw") == 0) {
                    if (amount <= accounts[i].balance) {
                        accounts[i].balance -= amount;
                        printf("Withdrawal successful. New balance: %.2f\n", accounts[i].balance);
                    } else {
                        printf("Insufficient balance\n");
                    }
                } else {
                    printf("Invalid transaction type\n");
                }
                return;
            }
        }
        printf("Account not found\n");
    } else {
        printf("Authentication failed. Invalid account number or password.\n");
    }
}

// Function to authenticate customer using customer ID and password
int authenticateCustomer(int customerID, char *password) {
    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].customerID == customerID) {
            decrypt(customers[i].password); // Decrypt stored password for comparison
            if (strcmp(customers[i].password, password) == 0) {
                encrypt(customers[i].password); // Re-encrypt the password after comparison
                return 1; // Authentication successful
            }
            encrypt(customers[i].password); // Re-encrypt the password after comparison
            return 0; // Authentication failed
        }
    }
    return 0; // Customer ID not found
}

// Function to authenticate account using account number and password
int authenticateAccount(int accountNumber, char *password) {
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            decrypt(accounts[i].password); // Decrypt stored password for comparison
            if (strcmp(accounts[i].password, password) == 0) {
                encrypt(accounts[i].password); // Re-encrypt the password after comparison
                return 1; // Authentication successful
            }
            encrypt(accounts[i].password); // Re-encrypt the password after comparison
            return 0; // Authentication failed
        }
    }
    return 0; // Account number not found
}

// Function to perform simple encryption
void encrypt(char *data) {
    // This is a placeholder for encryption logic.
    // You should implement a secure encryption algorithm here.
    // For simplicity, this example uses a basic XOR encryption.
    int key = 5;
    for (int i = 0; data[i] != '\0'; ++i) {
        data[i] = data[i] ^ key;
    }
}

// Function to perform simple decryption
void decrypt(char *data) {
    // This is a placeholder for decryption logic.
    // The decryption logic should be the reverse of the encryption logic.
    // For simplicity, this example uses a basic XOR decryption.
    int key = 5;
    for (int i = 0; data[i] != '\0'; ++i) {
        data[i] = data[i] ^ key;
    }
}

// Main function for demonstration
int main() {
    addCustomer();
    openAccount();
    processTransaction();
    return 0;
}
