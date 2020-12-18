/* 
    Name: Nicholas Garcia
    Date: 07-26-2020
    Class: COSC 1437
    Used code created by Bruce Gooch on 7/23/20.
    Also used:
    https://www.geeksforgeeks.org/virtual-function-cpp/
    https://www.tutorialspoint.com/cplusplus/cpp_inheritance.htm
    https://www.youtube.com/watch?v=0BimvRa8s0g
    https://en.cppreference.com/w/cpp/language/switch
*/
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_CHECKS=5;
const double CHARGE=10.0l;

class bankAccount
{
    public:
        bankAccount(string clientName, int newAccountNum, double startBalance)
        {
            accountNumber = newAccountNum;
            name = clientName;
            balance = startBalance;
        }
        //default destructor
        ~bankAccount(void){}
        //accessor function 
        string getname()
        {
            return name;
        }
        //accessor function 
        int getaccountNumber()
        {
            return accountNumber;
        }

        //accessor function 
        double getbalance()
        {
            return balance;
        }

        //defining/updating the deposit function
        void deposit(double amount)
        {
            balance += amount;
            cout << "$" << amount << " has instantly deposited in your account" << endl;
        }
        //virtual function, defined in inherited classes
        virtual void withdraw(double amount) = 0;
        virtual void printStatement() = 0;

        //virtual function ,function will be defined in inherited classes. This function prints.
        virtual void printSummary()
        {
            cout << setw(60) << setfill('-') << "" << setfill(' ') << endl;
            cout << endl << setw(25) << "" << "Account Summary" << endl << endl;
            cout << setw(25) << "Name: " << name << endl;
            cout << setw(25) << "Account Number: " << accountNumber << endl;
            cout << setw(25) << "Current Balance: $" << balance << endl;
        }

    protected:
        //protected data member Name,Account Number, Balance
        string name;
        int accountNumber;
        double balance;
};

class checkingAccount : public bankAccount
{
    public:
        //constructor intialization
        checkingAccount(string clientName, int newAccountNum, double startBalance)
        : bankAccount(clientName, newAccountNum, startBalance)
        {
        }
        //default destructor
        ~checkingAccount(void){}
        virtual void writeCheck(double amount) = 0;
        //defining its own withdraw function 
        void withdraw(double amount)
        {
            if (balance-amount < 0)
            {
                cout << "Declined: broke boy" << endl;
                return;
            }
            if (balance - amount < minimumBalance)
            {
                cout << "Declined: Broke Boy is at a Minimum Balance" << endl;
                return;
            }
            balance -= amount;
        }
        //defining its own printStatement function
        void printStatement()
        {
            printSummary();
            cout << endl << "Checking Account Statement: " << endl << endl;
        }
    protected:
        //protected data members
        double aInterestRate;
        int checksRemaining;
        double minimumBalance;
};

class serviceChargeChecking : public checkingAccount
{
    public:
        //constructor intialization
        serviceChargeChecking(string clientName, int newAccountNum, double startBalance)
        : checkingAccount(clientName,newAccountNum,startBalance)
        {
            aInterestRate = 0; 
            checksRemaining = MAX_CHECKS; 
            minimumBalance = 0; 
        }
        //destructor
        ~serviceChargeChecking(void){}
        //updating the balance by subtracting the ammount of written check
        void writeCheck(double amount)
        {
            if (checksRemaining == 0)
            {
                cout << "Declined: No checks this month broke boy." << endl;
                return;
            }
  
            if (balance - amount < 0)
            {
                cout << "Declined: broke boy." << endl;
                return;
            }
            checksRemaining--;
            balance -= amount;
  
        }
        //defining its own print summary function ,to print the summary of account
        void printSummary()
        {
            bankAccount::printSummary();
            cout << setw(25) << "Checks remaining: " << checksRemaining << endl;
            cout << setw(25) << "Monthly service fee: $" << CHARGE << endl;
            cout << setw(25) << "No interest " << endl;
            cout << setw(25) << "No Minimum Balance " << endl;
            cout << setw(60) << setfill('-') << "" << setfill(' ') << endl;
        }   
};

class noServiceChargeChecking : public checkingAccount
{
    public:
        //constructor intialization
        noServiceChargeChecking(string clientName, int newAccountNum, double startBalance)
        : checkingAccount(clientName,newAccountNum,startBalance)
        {
            aInterestRate = 2.5; // Some interest rate
            checksRemaining = -1; // -1 indicates no limit
            minimumBalance = 750; // Minimum balance
        }
        //default destructor
        ~noServiceChargeChecking(void){}
        //updating the balance by subtracting the ammount of written check
        void writeCheck(double amount)
        {
            if (balance - amount < 0)
            {
                cout << "Declined: broke boy." << endl;
                return;
            }
            balance -= amount; // Assume check is cashed immediately...
        }
        //printing the summary of account
        void printSummary()
        {
            bankAccount::printSummary();
            cout << setw(25) << "Interest rate: " << aInterestRate << "%" << endl;
            cout << setw(25) << "Minimum Balance: $" << minimumBalance << endl;
            cout << setw(25) << "Unlimited checks " << endl;
            cout << setw(25) << "No monthly service fee "<< endl;
            cout << setw(60) << setfill('-') << "" << setfill(' ') << endl;
        }
};

class highInterestChecking : public noServiceChargeChecking
{
    public:
        //constructor intialization
        highInterestChecking(string clientName, int newAccountNum, double startBalance)
        : noServiceChargeChecking(clientName,newAccountNum,startBalance)
        {
            aInterestRate = 5.0; // Higher interest rate
            checksRemaining = -1; // -1 indicates no limit
            minimumBalance = 1500; // Minimum balance
        }
        //default destructor
        ~highInterestChecking(void){}
};

class certificateOfDeposit : public bankAccount
{
    public:
        certificateOfDeposit(string clientName, int newAccountNum,double startBalance, int months)
        : bankAccount(clientName,newAccountNum,startBalance) 
        {
            aMonths = months;
            currentMonth = 1;
            aInterestRate = 4.75;
        }
        //default destructor
        ~certificateOfDeposit(void){}
        //defining its own withdraw function/updating balance by subtraction
        void withdraw(double amount)
        {
            if (balance-amount < 0)
            {
                cout << "Declined: broke boy." << endl;
                return;
            }
            balance -= amount;
        }

        //defining its own print summary function 
        void printSummary()
        {
            bankAccount::printSummary();
            cout << setw(25) << "Interest rate: " << aInterestRate << "%" << endl ;
            cout << setw(25) << "Months: " << aMonths << endl ;
            cout << setw(25) << "Current Month: " << currentMonth << endl;
            cout << endl << setw(60) << setfill('-') << "" << setfill(' ') << endl;
        }
        //printStatement function same as printSummary() except the last additional line
        void printStatement()
        {
            printSummary();
            cout << "Certificate of Deposite Account Statement:" << endl;
        }
    private:
        //private data members
        double aInterestRate;
        int aMonths;
        int currentMonth;
};

class savingsAccount : public bankAccount
{
    public:
        savingsAccount(string clientName, int newAccountNum, double startBalance)
        : bankAccount(clientName,newAccountNum,startBalance)
        {
            aInterestRate = 3.99;
        }
        //destructor
        ~savingsAccount(void){}

        void withdraw(double amount)
        {
            if (balance-amount < 0)
            {
                cout << "Declined: broke boy." << endl;
                return;
            }
            balance -= amount;
        }
        void printSummary()
        {
            bankAccount::printSummary();
            cout << setw(25) << "Interest rate: " << aInterestRate << "%" << endl << endl;
            cout << setw(60) << setfill('-') << "" << setfill(' ') << endl;
        }
        void printStatement()
        {
            printSummary();
            cout << "Savings Account Statement: " << endl;
        }

    protected:
        //protected data member
        double aInterestRate;
};

class highInterestSavings : public savingsAccount
{
    public:
        highInterestSavings(string clientName, int newAccountNum, double startBalance)
        : savingsAccount(clientName,newAccountNum,startBalance)
        {
            minimumBalance = 5000;
        }
        //default destructor
        ~highInterestSavings(void){}
        //defining its own withdraw function
        void withdraw(double amount)
        {
            if (balance - amount < 0)
            {
                cout << "Declined: broke boy" << endl;
                return;
            }
            if (balance - amount < minimumBalance)
            {
                cout << "Declined: Your Broke Self Does Not Meet the Minimum balance" << endl;
                return;
            }
            balance -= amount;
        }
        //defining its own summary function
        void printSummary()
        {
            bankAccount::printSummary();
            cout << setw(25) << "Interest rate: " << aInterestRate << "%" << endl;
            cout << setw(25) << "Minimum Balance: $" << minimumBalance << endl << endl;
            cout << setw(60) << setfill('-') << "" << setfill(' ') << endl;
        }

    protected:
        //protected data member
        double minimumBalance;
};

//functions that will test each account
void callCheckingWithService()
{
    serviceChargeChecking customer("Nick Garcia", 1234, 5000.50);
    char num=0;
    double amount;

    cout << "\t\tYou Selected Checking with Service Charge" << endl << endl;
    cout << "Account Summary:" << endl;
    customer.printSummary();
    cout << endl;
    while (num != 'e')
    {
        cout << "Please select a number:" << endl;
        cout << "1 - Withdrawal" << endl;
        cout << "2 - Deposit" << endl;
        cout << "3 - Summary" << endl;
        cout << "4 - Monthly Summary" << endl;
        cout << "5 - Write a check" << endl;
        cout << "e - Exit" << endl;
        cout << "Enter choice: ";
        cin >> num;
        switch (num)
        {
            case '1':
            cout << "Enter amount: ";
            cin >> amount;
            customer.withdraw(amount);
            break;
            case '2':
            cout << "Enter amount: ";
            cin >> amount;
            customer.deposit(amount);
            break;
            case '3':
            customer.printSummary();
            break;
            case '4':
            customer.printStatement();
            break;
            case '5':
            cout << "Enter amount: ";
            cin >> amount;
            customer.writeCheck(amount);
            break;
            case '6':
            break;
            case 'e':
            break;
            default:
            cout << "Invalid" << endl;
            break;
        }

        customer.printSummary();
        cout << endl;
    }
}

void callCheckingNoService()
{
    noServiceChargeChecking customer("Nick Garcia",1234,5000.50);
    char num=0;
    double amount;
    cout << "\t\tYou Selected Checking without Service Charge" << endl << endl;
    cout << "Account Summary:" << endl;
    customer.printSummary();
    cout << endl;
    while (num != 'e')
    {
        cout << "Please Select a Number:" << endl;
        cout << "1 - Withdrawal" << endl;
        cout << "2 - Deposit" << endl;
        cout << "3 - Summary" << endl;
        cout << "4 - Monthly Summary" << endl;
        cout << "5 - Write a check" << endl;
        cout << "e - Exit" << endl;
        cout << "Enter choice: ";
        cin >> num;
        switch (num)
        {
            case '1':
            cout << "Enter amount: ";
            cin >> amount;
            customer.withdraw(amount);
            break;
            case '2':
            cout << "Enter amount: ";
            cin >> amount;
            customer.deposit(amount);
            break;
            case '3':
            customer.printSummary();
            break;
            case '4':
            customer.printStatement();
            break;
            case '5':
            cout << "Enter amount: ";
            cin >> amount;
            customer.writeCheck(amount);
            break;
            case '6':
            break;
            case 'e':
            break;
            default:
            cout << "Invalid" << endl;
            break;
        }
        customer.printSummary();
        cout << endl;
    }
}
void callCheckingHighInterest()
{
    highInterestChecking customer("Nick Garcia", 1234, 5000.50);
    char num=0;
    double amount;
    cout << "\t\tYou Selected Checking with High Interest" << endl << endl;
    cout << "Account Summary:" << endl;
    customer.printSummary();
    cout << endl;
    while (num != 'e')
    {
        cout << "Please Select a Number:" << endl;
        cout << "1 - Withdrawal" << endl;
        cout << "2 - Deposit" << endl;
        cout << "3 - Summary" << endl;
        cout << "4 - Monthly Summary" << endl;
        cout << "5 - Write a check" << endl;
        cout << "e - Exit" << endl;
        cout << "Enter choice: ";
        cin >> num;
        switch (num)
        {
            case '1':
            cout << "Enter amount: ";
            cin >> amount;
            customer.withdraw(amount);
            break;
            case '2':
            cout << "Enter amount: ";
            cin >> amount;
            customer.deposit(amount);
            break;
            case '3':
            customer.printSummary();
            break;
            case '4':
            customer.printStatement();
            break;
            case '5':
            cout << "Enter amount: ";
            cin >> amount;
            customer.writeCheck(amount);
            break;
            case '6':
            break;
            case 'e':
            break;
            default:
            cout << "Invalid" << endl;
            break;
        }
        customer.printSummary();
        cout << endl;
    }
}
//same as above
void callSavings()
{
    savingsAccount customer("Nick Garcia", 1234,5000.50);
    char num=0;
    double amount;
    cout << "\t\tYou Selected Regular Savings" << endl << endl;
    cout << "Account Summary:" << endl;
    customer.printSummary();
    cout << endl;
    while (num != 'e')
    {
        cout << "Please Select a Number:" << endl;
        cout << "1 - Withdrawal" << endl;
        cout << "2 - Deposit" << endl;
        cout << "3 - Summary" << endl;
        cout << "4 - Monthly Summary" << endl;
        cout << "e - Exit" << endl;
        cout << "Enter choice: ";
        cin >> num;
        switch (num)
        {
            case '1':
            cout << "Enter amount: ";
            cin >> amount;
            customer.withdraw(amount);
            break;
            case '2':
            cout << "Enter amount: ";
            cin >> amount;
            customer.deposit(amount);
            break;
            case '3':
            customer.printSummary();
            break;
            case '4':
            customer.printStatement();
            break;
            case 'e':
            break;
            default:
            cout << "Invalid" << endl;
            break;
        }
        customer.printSummary();
        cout << endl;
    }
}
void callSavingsHighInterest()
{
    highInterestSavings customer("Nick Garcia", 1234, 5000.50);
    char num=0;
    double amount;
    cout << "\t\tYou Selected High Interest Savings" << endl << endl;
    cout << "Account Summary:" << endl;
    customer.printSummary();
    cout << endl;
    while (num != 'e')
    {
        cout << "Please Select a Number:" << endl;
        cout << "1 - Withdrawal" << endl;
        cout << "2 - Deposit" << endl;
        cout << "3 - Summary" << endl;
        cout << "4 - Monthly Summary" << endl;
        cout << "e - Exit" << endl;
        cout << "Enter choice: ";
        cin >> num;
        switch (num)
        {
            case '1':
            cout << "Enter amount: ";
            cin >> amount;
            customer.withdraw(amount);
            break;
            case '2':
            cout << "Enter amount: ";
            cin >> amount;
            customer.deposit(amount);
            break;
            case '3':
            customer.printSummary();
            break;
            case '4':
            customer.printStatement();
            break;
            case 'e':
            break;
            default:
            cout << "Invalid" << endl;
            break;
        }
        customer.printSummary();
        cout << endl;
    }
}
//same as above
void callCertificateOfDeposit()
{
    //acct is object of certificateOfDeposit,values of data member is passed as argument of constructor
    certificateOfDeposit customer("Nick Garcia", 1234,5000.50, 8);
    char num=0;
    double amount;
    cout << "\t\tYou Selected High Interest Savings" << endl << endl;
    cout << "Account Summary" << endl;
    customer.printSummary();
    cout << endl;
    while (num != 'e')
    {
        cout << "Select a transaction:" << endl;
        cout << "1 - Withdrawal" << endl;
        cout << "2 - Deposit" << endl;
        cout << "3 - Summary" << endl;
        cout << "4 - Monthly Summary" << endl;
        cout << "e - Exit Test Suite" << endl;
        cout << "Enter choice: ";
        cin >> num;
        switch (num)
        {
            case '1':
            cout << "Enter amount: ";
            cin >> amount;
            customer.withdraw(amount);
            break;
            case '2':
            cout << "Enter amount: ";
            cin >> amount;
            customer.deposit(amount);
            break;
            case '3':
            customer.printSummary();
            break;
            case '4':
            customer.printStatement();
            break;
            case 'e':
            break;
            default:
            cout << "Invalid" << endl;
            break;
        }
        customer.printSummary();
        cout << endl;
    }
}

//main driver that will call/test functions
int main()
{
    char num;
    cout << "\t\tHowdy! Thanks for letting us hold on to your money!" << endl << endl;
    cout << "Please type a number corresponding to the account you would like to view." << endl;
    cout << "1 - Checking with Service Charge" << endl;
    cout << "2 - Checking without Service Charge" << endl;
    cout << "3 - Checking with High Interest" << endl;
    cout << "4 - Savings Account" << endl;
    cout << "5 - Savings Account with High Interest" << endl;
    cout << "6 - Certificate of Deposit" << endl;
    cout << "Enter choice: ";
    cin >> num;
    switch (num)
        {
            case '1':
            callCheckingWithService();
            break;
            case '2':
            callCheckingNoService();
            break;
            case '3':
            callCheckingHighInterest();
            break;
            case '4':
            callSavings();
            break;
            case '5':
            callSavingsHighInterest();
            break;
            case '6':
            callCertificateOfDeposit();
            break;
            default:
            cout << "Invalid" << endl;
            break;
        }
    return 0;
}

