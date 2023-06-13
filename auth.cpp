#include <iostream>
#include <fstream>
#include <istream>
#include <string.h>
#include <stdlib.h>
using namespace std;

class auth
{
private :
    string username;
    string password;
    string secretcode;
public:
    void menu();
    void login();
    void registration();
    void forgot();
    void changepassword();
};

void auth:: menu()
{

    int choice;
    cout << "*************** MENU ***************\n";
    cout << "1.Login";
    cout << "\n2.Register";
    cout << "\n3.Forgot password";
    cout << "\nEnter you choice :";
    cin >> choice;

    switch (choice)
    {
    case 1:
        login();
        break;
    case 2:
        registration();
        break;
    case 3:
        forgot();
        break;
    default:
        cout << " Sorry, wrong choice selected\n";
        cout << "Press any key";
        cin.get();
        cin.get();
        system("cls");
        menu();
        break;
    }
}

void auth::registration()
{

    string regusername, regpassword, secretcode;
    system("cls");
    cout << "*********** Registration ***********" << endl;
    cout << "Enter username :";
    cin >> regusername;
    cout << "Enter password :";
    cin >> regpassword;
    cout << "Enter secret code :" << endl;
    cout << "*When you forget to remind your password, you can reset your password with secret code" << endl;
    cin >> secretcode;

    ofstream reg("database.txt", ios::app);
    reg << regusername << " " << regpassword << " " << secretcode << endl;
    cout << "Registration successfully\n";
    menu();
}

void auth::login()
{
    int exist;
    string username, password, u, p;
    system("cls");
    cout << "*********** LOGIN ***********" << endl;
    cout << "Enter username :";
    cin >> username;
    cout << "Enter password :";
    cin >> password;

    ifstream input("database.txt");

    while (input >> u >> p)
    {
        if (u == username && p == password)
        {
            exist = 1;
        }
    }
    input.close();
    if (exist == 1)
    {
        cout << "Hello " << username << "\nWe're glad that you're here\n";
        cin.get();
        cin.get();
        menu();
    }
    else
    {
        int cho;
        cout << "Sorry, Acount not found!\n";
        cout << "Press any key to back to main";
        cin.get();
        cin.get();
        login();
    }
}

void auth::forgot()
{
    int ch;
    system("cls");
    cout << "*********** Forgot Account ***********" << endl;
    cout << "1.Search your account by username";
    cout << "\n2.Search your account by password";
    cout << "\n3.Main Menu";
    cout << "\n Enter your choice :";
    cin >> ch;
    switch (ch)
    {
    case 1:
    {
        int ex = 0;
        string searchuser, su, sp;
        cout << "Enter your remembered username :";
        cin >> searchuser;

        ifstream searchu("database.txt");
        while (searchu >> su >> sp)
        {
            if (su == searchuser)
            {
                ex = 1;
                break;
            }
        }
        searchu.close();
        if (ex == 1)
        {
            cout << "Your account found \n";
            cin.get();
            cin.get();
            changepassword();
        }
        else
        {
            cout << "Sorry, your account is not found \n";
            cin.get();
            cin.get();
            forgot();
        }
        break;
    }
    case 2:
    {
        int exi = 0;
        string searchpass, su2, sp2;
        cout << "Enter the remembered password: ";
        cin >> searchpass;

        ifstream searchp("database.txt");
        while (searchp >> su2 >> sp2)
        {
            if (sp2 == searchpass)
            {
                exi = 1;
                break;
            }
        }
        searchp.close();
        if (exi == 1)
        {
            cout << "Your account found \n";
            cout << "Your username is " << su2 << endl;
            cout << "Your password is " << sp2;
            cin.get();
            cin.get();
            forgot();
        }
        else
        {
            cout << "Sorry, your account is not found \n";
            cin.get();
            cin.get();
            forgot();
        }
        break;
    }
    case 3:
    {
        menu();
        break;
    }
    default:
    {
        cout << "You have given a wrong choice. Press a key to try again.";
        cin.get();
        cin.get();
        forgot();
        break;
    }
    }
}

void auth::changepassword()
{
    int ex = 0;
    string secretcode, sc;
    cout << "Enter your secret code :" << endl;
    cin >> secretcode;
    fstream input("database.txt");
    while (input >> sc)
    {
        if (sc == secretcode)
        {
            ex = 1;
            break;
        }
    }

    input.close();
    if (ex == 1)
    {
        fstream data, data1;
        string newPassword, newUsername, newSecretCode;
        cout << "Your secretcode found \n";
        data.open("database.txt", ios::in);

        if (!data)
        {
            cout << "Error opening files!";
        }
        else
        {
            data1.open("database1.txt", ios::app | ios::out);
            data >> username, password, newSecretCode;
            while (!data.eof())
            {
                if(sc == secretcode)
                {
                    cout << "Enter your new username :" << endl;
                    cin >> username;
                    cout << "Enter your new password :" << endl;
                    cin >> newPassword;
                    cout << "Enter your new secretcode :" << endl;
                    cin >> secretcode;
                    data1 << " " << username << " " << newPassword << " " << newSecretCode << "\n";
                    cout << "Account updated sucessfully." << endl;
                }else{
                    data1 << " " << username << " " << password << " " << secretcode << "\n";
                }
                data >> username, password, secretcode;
            }
            data.close();
            data1.close();

            remove("database.txt");
            rename("database1.txt", "database.txt");
        }
    }
    else
    {
        cout << "Sorry, your secret code is not found \n";
        cin.get();
        cin.get();
        changepassword();
    }
}

int main()
{
    auth s;
    s.menu();
}