#include <iostream>
#include <fstream>
#include <istream>
#include <string.h>
#include <stdlib.h>
using namespace std;

void login();
void registration();
void forgot();

main()
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
        main();
        break;
    }
}

void registration()
{

    string regusername, regpassword;
    system("cls");
    cout << "*********** Registration ***********" << endl;
    cout << "Enter username :";
    cin >> regusername;
    cout << "Enter password :";
    cin >> regpassword;

    ofstream reg("database.txt", ios::app);
    reg << regusername << " " << regpassword << endl;
    cout << "Registration successfully\n";
    main();
}

void login()
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
        main();
    }
    else
    {
        int cho;
        cout << "Sorry, Acount not found!\n";
        cout << "Press any key to back to main";
        cin.get();
        cin.get();
        main();
    }
}

void forgot()
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
            cout << "Your password is " << sp;
            cin.get();
            cin.get();
            main();
        }
        else
        {
            cout << "Sorry, your account is not found \n";
            cin.get();
            cin.get();
            main();
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
            main();
        }
        break;
    }
    case 3:
    {
        main();
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