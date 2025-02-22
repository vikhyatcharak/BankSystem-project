Bank System
  - The Bank System is a C++ banking system implementing object-oriented programming (OOP) principles and dynamic memory allocation for efficient transaction management.
  - 
Features
 - Customer Management - Store and retrieve customer details.
 - Account Handling - Deposit, withdraw, and transfer money securely.
 - Transaction History - Track transactions using linked lists.
 - Secure Authentication - Password-protected accounts.
 - 
Technologies Used
 - C++ - Core programming language.
 - OOP Concepts - Encapsulation, inheritance, and polymorphism.
 - Linked Lists - Efficiently manage transaction records.
 - Dynamic Memory Allocation - Handle variable-size data structures.
 - 
Project Structure

  - Customer
    -- Variables: customerId, name
    -- Functions: getId(), getName()
    
  -Account
    -- Variables: accountId, amount, password
    -- Functions: deposit(money), withdraw(money), getAmount(), getPass(), getId()
    
  -Transaction
    -- Variables: srcAccount, destAccount
    -- Functions: transfer(money)
    
  - Banking Service (Uses Linked List for tracking)
    -- Variables: customers, accounts, transactions
    
Functions:

  - createAccount(name, amount, password)
  - performDeposit(accountId, money)
  - performWithdrawal(accountId, money)
  - performTransactions(srcAccountId, destAccountId, money, password)
  - checkDetails(customerId)
  - checkTransactions(customerId)
