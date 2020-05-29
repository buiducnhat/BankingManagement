#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

void drawline(int n, char symbol);
int enter(int minRange, int maxRange, string warning);

class account
{
private:
    string name;
    int id;
    int money;

public:
    void inData(int id)
    {
        this->id = id;
        getchar();
        cout << "Enter your name: ";
        getline(cin, this->name);
        for (int i = 0; i < this->name.length(); i++)
        {
            this->name[i] = toupper(this->name[i]);
        }
        cout << "Enter your first balance: ";
        cin >> money;
    }
    int getID()
    {
        return this->id;
    }
    void changeID()
    {
        this->id--;
    }
    int getBalance()
    {
        return this->money;
    }
    void outData()
    {
        printf("%-10d%-30s$%-15d\n", this->id, this->name.c_str(), this->money);
    }
    void readData(string s)
    {
        this->id = (int)(s[0] - '0');
        for (int i = 10; i < 40; i++)
        {
            if (s[i] == ' ' && s[i + 1] == ' ')
            {
                this->name = s.substr(10, i - 10);
                break;
            }
        }
        this->money = stoi(s.substr(41, 15));
    }
    void writeData(FILE *dataFile)
    {
        fprintf(dataFile, "%-10d%-30s$%-15d\n", this->id, this->name.c_str(), this->money);
    }
    void modify()
    {
        getchar();
        cout << "Enter new name: ";
        getline(cin, this->name);
        for (int i = 0; i < this->name.length(); i++)
        {
            this->name[i] = toupper(this->name[i]);
        }
    }
    void deposit(int amount)
    {
        this->money += amount;
    }
    void withdraw(int amount)
    {
        this->money -= amount;
    }
};
void drawline(int number, char symbol)
{
    for (int i = 0; i < number; i++)
    {
        cout << symbol;
    }
}
int enter(int minRange, int maxRange, string warning)
{
    int x;
    do
    {
        cin >> x;
        if (x < minRange || x > maxRange)
        {
            cout << warning;
        }
    } while (x < minRange || x > maxRange);
}
void menuDisplay()
{
    system("cls");
    drawline(80, '=');
    cout << "\n";
    cout << "**";
    drawline(28, '_');
    cout << "BANKING MANAGEMENT SYSTEM";
    drawline(23, '_');
    cout << "**";
    cout << endl;
    cout << "**\t\t\t\t1. NEW ACCOUNT\t\t\t\t      **\n";
    cout << "**\t\t\t\t2. DEPOSIT AMOUNT\t\t\t      **\n";
    cout << "**\t\t\t\t3. WITHDRAW AMOUNT\t\t\t      **\n";
    cout << "**\t\t\t\t4. ALL ACCOUNT LIST\t\t\t      **\n";
    cout << "**\t\t\t\t5. CLOSE AN ACCOUNT\t\t\t      **\n";
    cout << "**\t\t\t\t6. MODIFY AN ACCOUNT\t\t\t      **\n";
    cout << "**\t\t\t\t7. EXIT\t\t\t\t\t      **\n";
    drawline(80, '=');
    cout << "\n";
}
void newAccount(vector<account> &accounts)
{
    system("cls");
    drawline(30, '=');
    cout << " CREATING AN ACCOUNT ";
    drawline(29, '=');
    cout << "\n\n";
    account x;
    x.inData(accounts.size() + 1);
    accounts.push_back(x);
    cout << "Creat account successfully!\n";
}
void depositAmount(vector<account> &accounts)
{
    system("cls");
    drawline(20, '=');
    cout << " DEPOSITTING AMOUNT TO ACCOUNT ";
    drawline(20, '=');
    cout << endl;
    int id, amount;
    cout << "Enter ID of account need depositting: ";
    id = enter(1, accounts.size(), "Invalid ID, please enter again: ");
    cout << "Enter amount to deposit: ";
    cin >> amount;
    accounts[id - 1].deposit(amount);
    cout << "Deposit amount to account ID " << id << "successfully!\n";
}
void withdrawAmount(vector<account> &accounts)
{
    system("cls");
    drawline(20, '=');
    cout << " WITHDRAWING AMOUNT OF ACCOUNT ";
    drawline(20, '=');
    cout << endl;
    int id, amount;
    cout << "Enter ID of account need withdrawing: ";
    id = enter(1, accounts.size(), "Invalid ID, please enter again: ");
    cout << "Enter amount to withdraw: ";
    amount = enter(1, accounts[id - 1].getBalance(), "The amount must be greater or equal to 1 and less or equal to this balance!\n");
    accounts[id - 1].withdraw(amount);
    cout << "Withdraw amount of account ID " << id << " successfully!\n";
}
void accountList(vector<account> &accounts)
{
    system("cls");
    drawline(27, '=');
    cout << " ALL ACCOUNT HOLDER LIST ";
    drawline(28, '=');
    cout << "\n\n";
    printf("%-10s%-30s%-15s\n\n", "ID", "NAME", "BALANCE");
    for (auto x : accounts)
    {
        x.outData();
    }
}
void deleteAccount(vector<account> &accounts)
{
    system("CLS");
    if (accounts.size() == 0)
    {
        return;
    }
    drawline(20, '=');
    cout << " CLOSING AN ACCOUNT ";
    drawline(20, '=');
    cout << "\n\n";
    int id;
    cout << "Enter ID of account need closing: ";
    id = enter(1, accounts.size(), "Invalid ID, please enter again: ");
    accounts.erase(accounts.begin() + id - 1);
    for (int i = id - 1; i < accounts.size(); i++)
    {
        accounts[i].changeID();
    }
    cout << "Close account ID " << id << " successfully!\n";
}

void modifyAccount(vector<account> &accounts)
{
    system("cls");
    drawline(29, '=');
    cout << " MODIFYING AN ACCOUNT ";
    drawline(29, '=');
    cout << "\n\n";
    int id;
    cout << "Enter the ID of account need modifying: ";
    id = enter(1, accounts.size(), "Invalid ID! Please enter again: ");
    accounts[id - 1].modify();
    cout << "Modify Account ID " << id << " successfully!\n";
}
void exitProgram(vector<account> accounts)
{
    FILE *dataFile = fopen("account.dat", "w+");
    for (auto x : accounts)
    {
        x.writeData(dataFile);
    }
    system("cls");
    cout << "====== MADE BY BUI DUC NHAT FROM HUST =====\n";
    cout << "EXITING PROGRAM....\n";
    system("pause");
}
void getDataFromFile(vector<account> &accounts)
{
    FILE *dataFile = fopen("account.dat", "r");
    char temp[255];
    account x;
    while (fgets(temp, 255, dataFile) != NULL)
    {
        string s = temp;
        x.readData(s);
        accounts.push_back(x);
    }
}
int main()
{
    int choice = 0;
    vector<account> accounts;
    getDataFromFile(accounts);
    do
    {
        menuDisplay();
        cout << "Enter number (1 - 7) to select: ";
        choice = enter(1, 7, "Please enter valid value: ");
        switch (choice)
        {
        case 1:
            newAccount(accounts);
            cin.ignore();
            cin.get();
            break;
        case 2:
            depositAmount(accounts);
            cin.ignore();
            cin.get();
            break;
        case 3:
            withdrawAmount(accounts);
            cin.ignore();
            cin.get();
            break;
        case 4:
            accountList(accounts);
            cin.ignore();
            cin.get();
            break;
        case 5:
            deleteAccount(accounts);
            cin.ignore();
            cin.get();
            break;
        case 6:
            modifyAccount(accounts);
            cin.get();
            break;
        case 7:
            exitProgram(accounts);
            break;
        default:
            exitProgram(accounts);
        }
    } while (choice != 7);
    return 0;
}
