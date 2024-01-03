#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
// creating customer class
class Customer
{
protected: // so that these can be inherited
    int customerId;
    string name;

public:
    Customer() {} // default constructor
    Customer(int id, string name)
    {
        customerId = id;
        this->name = name;
    }
    // functions of this class
    int getcId()
    {
        return customerId;
    }

    string getName()
    {
        return name;
    }
};
// creating account class inherited from customer class
class Account : public Customer
{
protected:
    int accountId, amount, pin;

public:
    Account() {} // default constructor
    Account(int id, int amount, int pin)
    {
        accountId = id;
        this->pin = pin;
        this->amount = amount;
    }
    // functions of this class
    void deposit(int money)
    {
        amount += money;
    }

    void withdraw(int money)
    {
        if (amount < money)
        {
            cout << "Insufficient balance" << endl<<endl;
        }
        else
        {
            amount -= money;
        }
    }

    int getPin()
    {
        return pin;
    }

    int getAmount()
    {
        return amount;
    }

    int getdId()
    {
        return accountId;
    }
};
// creating transaction clSS
class transaction
{
    Account *srcAccount, *destAccount;

public:
    transaction() {}
    transaction(Account *acc1, Account *acc2)
    {
        srcAccount = acc1;
        destAccount = acc2;
    }
    // functions of the class
    void transfer(int money)
    {
        srcAccount->withdraw(money); // withdraws from source account
        destAccount->deposit(money); // deposits in destination account
    }
};
// creating linked list class
class LinkedList
{
    int data;
    LinkedList *next;

public:
    LinkedList() {}
    LinkedList(int x)
    {
        data = x;
        this->next = NULL;
    }
    void traversal()
    {
        if (next == NULL)
        {
            cout << "No transactions done" << endl<<endl;
        }
        else
        {
            LinkedList *temp = this->next;
            while (temp != NULL)
            {
                cout << temp->data << "  ";
                temp = temp->next;
            }
            cout << endl<<endl;
        }
    }
    void join(int x)
    {
        LinkedList *temp = this;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        LinkedList *newTransaction = new LinkedList(x);
        temp->next = newTransaction;
    }
};
// creating bank services class
class BankingService
{
    vector<Customer> customers;      // stores list of customers
    vector<Account> accounts;        // stores list of accounts
    vector<LinkedList> transactions; // stores list of all the transactions
public:
    // functions of the class
    void createAcc()
    {
        // taking input of name
        string name;
        cout << "Enter your name: ";
        getline(cin, name);
        // taking input of amount
        int amount;
        cout << "Enter the amount you want to create your account with: ";
        cin >> amount;
        // assigning the ids
        int cId = customers.size() + 1;
        int aId = accounts.size() + 1;
        // taking input of password
        int pin;
        cout << "Enter the pin you want to create for this account:";
        cin >> pin;
        Customer c(cId, name);
        Account a(aId, amount, pin);
        customers.push_back(c); // pushing the new customer in its respective vector
        accounts.push_back(a);  // pushing the new account in its respective vector
        LinkedList head(aId);   // making head of the linked list as account's Id and chaining the transactions done to this so we can access the transactions done if an accounts id is given
        transactions.push_back(head);
        cout << "Than you for creating the account!" << endl;
        cout << "Here are your account details:" << endl;
        cout << "Customer ID: " << c.getcId() << endl;
        cout << "Name: " << c.getName() << endl;
        cout << "Account ID: " << a.getdId() << endl;
        cout << "Balance: " << a.getAmount() << endl<<endl;
    }
    // overloading createAcc function
    void createAcc(string name, int amount, int pin); // defined after the class

    void performDeposit()
    {
        int aId;
        cout << "Enter account id: ";
        cin >> aId;
        int mony;
        cout << "Enter amount you want to deposit: ";
        cin >> mony;
        int n = aId - 1;
        int size = accounts.size();
        if (n < size)
        { // to check if the account exists
            // updating transactions for account
            Account *acc = &accounts[n];
            acc->deposit(mony);
            transactions[n].join(mony);
            cout<<"Transaction Successful"<<endl<<endl;
        }
        else
        {
            cout << "Account doesn't exist" << endl<<endl;
            ;
        }
    }
    // overloading performDeposit function
    void performDeposit(int aId, int mony);// defined after the class

    void performWithdrawl()
    {
        int aId;
        cout << "Enter account id: ";
        cin >> aId;
        int mony;
        cout << "Enter amount you want to withdraw: ";
        cin >> mony;
        int n = aId - 1;
        int size = accounts.size();
        if (n < size)
        { // to check if the account exists
            for (int i = 2; i >= 0; i--)
            { // for max number of attempts is 3
                // taking input of the pin
                int pin;
                cout << "Enter pin of your account: ";
                cin >> pin;
                Account *acc = &accounts[n];
                if (acc->getPin() == pin)
                { // if the pin entered is correct
                    acc->withdraw(mony);
                    // updating transactions for account
                    int x = 0 - mony;
                    transactions[n].join(x);
                    cout<<"Transaction successful"<<endl<<endl;
                    break;
                }
                else
                {
                    cout << "Incorrect Pin" << endl;
                    cout << i << " "
                        << "attempts left" << endl;
                    if (i == 0)
                    {
                        cout << "Maximum attempts reached. Transaction cancelled." << endl<<endl;
                    }
                    else
                    {
                        cout << "try again:" << endl;
                    }
                }
            }
        }
        else
        {
            cout << "Account doesn't exist" << endl<<endl;
        }
    }

    void performWithdrawl(int aId, int mony, int pin); // defined after the class

    void performTransaction()
    {
        int srcAccId, destAccId, mony;
        cout << "Enter your account id: ";
        cin >> srcAccId;
        cout << "Enter the id of the account you want to transfer: ";
        cin >> destAccId;
        cout << "Enter amount you want to transfer: ";
        cin >> mony;
        int n1 = srcAccId - 1;
        int n2 = destAccId - 1;
        int size = accounts.size();
        if (n1 < size && n2 < size)
        { // to check if the accounts exists
            Account *sAcc = &accounts[n1];
            Account *dAcc = &accounts[n2];
            int amount = sAcc->getAmount();
            if (amount >= mony)
            {
                transaction t(sAcc, dAcc);
                for (int i = 2; i >= 0; i--)
                { // for max number of attempts is 3
                    // taking input of the pin
                    int pin;
                    cout << "Enter your pin: ";
                    cin >> pin;
                    if (sAcc->getPin() == pin)
                    { // to check if the pin entered is correct
                        t.transfer(mony);
                        // updating transactions for source account
                        transactions[n2].join(mony);
                        // updating transactions for destination account
                        int x = 0 - mony;
                        transactions[n1].join(x);
                        cout<<"Transaction successful"<<endl<<endl;
                        break;
                    }
                    else
                    {
                        cout << "Incorrect Pin" << endl;
                        cout << i << " "
                            << "attempts left" << endl;
                        if (i == 0)
                        {
                            cout << "Maximum attempts reached. Transaction cancelled." << endl<<endl;
                        }
                        else
                        {
                            cout << "try again:" << endl;
                        }
                    }
                }
            }
            else
            {
                cout << "Insufficient Balance" << endl<<endl;
            }
        }
        else
        {
            cout << "Account doesn't exist" << endl<<endl;
        }
    }

    void performTransaction(int srcAccId, int destAccId, int mony, int pin); // defined after the class

    void checkDetails()
    {
        int Id;
        cout << "Enter your customer Id: ";
        cin >> Id;
        int n = Id - 1;
        int size = customers.size();
        if (n < size)
        {
            Customer c = customers[n];
            Account d = accounts[n]; // because number of customers and account is same
            for (int i = 2; i >= 0; i--)
            { // for max number of attempts is 3
                // taking input of the pin
                int pin;
                cout << "Enter your pin: ";
                cin >> pin;
                if (d.getPin() == pin)
                {
                    cout << "Customer ID: " << c.getcId() << endl;
                    cout << "Name: " << c.getName() << endl;
                    cout << "Account ID: " << d.getdId() << endl;
                    cout << "Balance: " << d.getAmount() << endl<<endl;
                    break;
                }
                else
                {
                    cout << "Incorrect Pin" << endl;
                    cout << i << " "
                        << "attempts left" << endl;
                    if (i == 0)
                    {
                        cout << "Maximum attempts reached. Transaction cancelled." << endl<<endl;
                    }
                    else
                    {
                        cout << "try again:" << endl;
                    }
                }
            }
        }
        else
        {
            cout << "Account does not exist" << endl<<endl;
        }
    }

    void checkDetails(int Id, int pin);// defined after the class

    void checkTransactions()
    {
        int aId;
        cout << "Enter your account Id: ";
        cin >> aId;
        int n = aId - 1;
        int size = customers.size();
        if (n < size)
        {
            for (int i = 2; i >= 0; i--)
            { // for max number of attempts is 3
              // taking input of the pin
                Account d = accounts[n];
                // taking input of the pin
                int pin;
                cout << "Enter your pin: ";
                cin >> pin;
                if (d.getPin() == pin)
                {
                    cout << "Transactions: ";
                    LinkedList *head = &transactions[n];
                    head->traversal();
                    break;
                }
                else
                {
                    cout << "Incorrect Pin" << endl;
                    cout << i << " "
                        << "attempts left" << endl;
                    if (i == 0)
                    {
                        cout << "Maximum attempts reached. Transaction cancelled." << endl<<endl;
                    }
                    else
                    {
                        cout << "try again:" << endl;
                    }
                }
            }
        }
        else
        {
            cout << "Account does not exist" << endl<<endl;
        }
    }

    void checkTransactions(int aId, int pin);
};

void BankingService::createAcc(string name, int amount, int pin)
{
    int cId = customers.size() + 1;
    int aId = accounts.size() + 1;
    Customer c(cId, name);
    Account a(aId, amount, pin);
    customers.push_back(c); // pushing the new customer in its respective vector
    accounts.push_back(a);  // pushing the new account in its respective vector
    LinkedList head(aId);   // making head of the linked list as account's Id and chaining the transactions done to this so we can access the transactions done if an accounts id is given
    transactions.push_back(head);
    cout << "Than you for creating the account!" << endl;
    cout << "Here are your account details:" << endl;
    cout << "Customer ID: " << c.getcId() << endl;
    cout << "Name: " << c.getName() << endl;
    cout << "Account ID: " << a.getdId() << endl;
    cout << "Balance: " << a.getAmount() << endl<<endl;
}

void BankingService::performDeposit(int aId, int mony)
{
    int n = aId - 1;
    int size = accounts.size();
    if (n < size)
    { // to check if the account exists
        // updating transactions for account
        Account *acc = &accounts[n];
        acc->deposit(mony);
        transactions[n].join(mony);
        cout<<"Transaction successful"<<endl<<endl;
    }
    else
    {
        cout << "Account doesn't exist" << endl<<endl;
    }
}

void BankingService::performWithdrawl(int aId, int mony, int pin)
{
    int n = aId - 1;
    int size = accounts.size();
    if (n < size)
    { // to check if the account exists
        Account *acc = &accounts[n];
        if (acc->getPin() == pin)
        { // if the pin entered is correct
            acc->withdraw(mony);
            // updating transactions for account
            int x = 0 - mony;
            transactions[n].join(x);
            cout<<"Transaction successful "<<endl<<endl;
        }
        else
        {
            cout << "Incorrect Pin" << endl<<endl;
        }
    }
    else
    {
        cout << "Account doesn't exist" << endl<<endl;
    }
}

void BankingService::performTransaction(int srcAccId, int destAccId, int mony, int pin)
{
    int n1 = srcAccId - 1;
    int n2 = destAccId - 1;
    int size = accounts.size();
    if (n1 < size && n2 < size)
    { // to check if the accounts exists
        Account *sAcc = &accounts[n1];
        Account *dAcc = &accounts[n2];
        int amount = sAcc->getAmount();
        if (amount >= mony)
        {
            transaction t(sAcc, dAcc);
            if (sAcc->getPin() == pin)
            { // to check if the pin entered is correct
                t.transfer(mony);
                // updating transactions for source account
                transactions[n2].join(mony);
                // updating transactions for destination account
                int x = 0 - mony;
                transactions[n1].join(x);
                cout<<"Transaction successful"<<endl<<endl;
            }
            else
            {
                cout << "Incorrect Pin" << endl<<endl;
            }
        }
        else
        {
            cout << "Insufficient Balance" << endl<<endl;
        }
    }
    else
    {
        cout << "Account doesn't exist" << endl<<endl;
    }
}

void BankingService::checkDetails(int Id, int pin)
{
    int n = Id - 1;
    int size = customers.size();
    if (n < size)
    { // to check if the account exists
        Customer c = customers[n];
        Account d = accounts[n]; // because number of customers and account is sa
        if (d.getPin() == pin)
        {
            cout << "Customer ID: " << c.getcId() << endl;
            cout << "Name: " << c.getName() << endl;
            cout << "Account ID: " << d.getdId() << endl;
            cout << "Balance: " << d.getAmount() << endl;
            cout<<endl<<endl;
        }
        else
        {
            cout << "Incorrect Pin" << endl<<endl;
        }
    }
    else
    {
        cout << "Account does not exist" << endl<<endl;
    }
}

void BankingService::checkTransactions(int aId, int pin)
{
    int n = aId - 1;
    int size = customers.size();
    if (n < size)
    {
        Account d = accounts[n];
        if (d.getPin() == pin)
        {
            cout << "Transactions: ";
            LinkedList *head = &transactions[n];
            head->traversal();
        }
        else
        {
            cout << "Incorrect Pin" << endl<<endl;
        }
    }
    else
    {
        cout << "Account does not exist" << endl<<endl;
    }
}

int main()
{
    BankingService b;
    // creating accounts using parameters
    b.createAcc("Arjun Kumar", 174500, 1234);
    b.createAcc("Anant Kaushik", 1892560, 1234);
    b.createAcc("Timothy", 1894570, 1234);
    b.createAcc("Sara", 102570, 1234);
    // performing functions of banking service

    b.performDeposit(1, 20000);
    b.performWithdrawl(3, 60000, 1234);
    b.performDeposit(5, 600000);
    b.checkTransactions(3, 1234);
    b.performTransaction(2, 3, 4000000, 1234);
    b.performDeposit(6,80000);
    b.createAcc("Arnav",86468,1234);
    b.performDeposit(4,4000);
    b.checkDetails(2,1234);
    b.performTransaction(3,1,3569,1234);
    b.performDeposit(2,3000);
    b.performWithdrawl(2,40000,1234);
    b.performTransaction(2,3,3000,1234);
    b.performTransaction(3,4,20000,1234);
    b.checkTransactions(2,1234);
    b.checkDetails(2,1234);
    b.checkTransactions(3,1234);
    b.checkDetails(3,1234);


    // asking user about the the banking service he/she wants to chose
    int n;
    cout << "Services: " << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Transfer Money" << endl;
    cout << "5. Check Details of the account" << endl;
    cout << "6. Check transactions of the account" << endl;
    cout << endl;
    cout << "Enter the service number: ";
    cin >> n;
    switch (n)
    {
    case 1:
    {
        b.createAcc();
        break;
    }
    case 2:
    {
        b.performDeposit();
        break;
    }
    case 3:
    {
        b.performWithdrawl();
        break;
    }
    case 4:
    {
        b.performTransaction();
        break;
    }
    case 5:
    {
        b.checkDetails();
        break;
    }
    case 6:
    {
        b.checkTransactions();
        break;
    }
    }
}