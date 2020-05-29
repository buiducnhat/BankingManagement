#ifndef HEADER_H_
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;
void drawline(int n, char symbol);
int enter(int minRange, int maxRange, string warning);
void menuDisplay();
void newAccount(vector<account> &accounts);
void depositAmount(vector<account> &accounts);
void withdrawAmount(vector<account> &accounts);
void accountList(vector<account> &accounts);
void deleteAccount(vector<account> &accounts);
void modifyAccount(vector<account> &accounts);
void exitProgram(vector<account> accounts);
void getDataFromFile(vector<account> &accounts);
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
    string infoAnalyze(string name)
    {
        int start = 0;
        for (int i = 0; i < name.size(); i++)
        {
            if (name[i] == ' ' && name[i + 1] != ' ')
            {
                start = i + 1;
                break;
            }
        }
        for (int i = start; i < name.size(); i++)
        {
            if (name[i] == ' ' && name[i + 1] == ' ')
            {
                return name.substr(start, i - start);
            }
        }
        return name;
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
    void readData(FILE *dataFile, int pos)
    {
        fseek(dataFile, pos, SEEK_SET);
        fscanf(dataFile, "%d", &id);
        char c;
        while ((c = fgetc(dataFile)) != '$')
        {
            name += c;
        }
        this->name = infoAnalyze(this->name);
        fscanf(dataFile, "%d", &money);
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
#define HEADER_H_
#endif
