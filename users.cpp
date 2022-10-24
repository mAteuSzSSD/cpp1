#include <iostream>
#include "users.h"
#include <vector>
#include <string>
#include <fstream>
using namespace std;

vector<User> users;

int d = 0; //add_user()
void add_user()
{
    string a, b, c;
    
    cout << "podaj imie: "; cin >> a;
    cout << "podaj nazwisko: "; cin >> b;
    cout << "podaj mail: "; cin >> c;
    while(true)
    {
        if (mail_check(c) == false)
        {
            cout << "nieprawidlowy mail, podaj jeszcze raz: "; cin >> c;
        }
        else
        {
            break;
        }
    }
    User u1(a, b, c, d);
    users.push_back(u1);
    d++;
}

void start()
{
    cout << "1. dodaj nowego uzytkownika \n";
    cout << "2. wyswietl dane uzytkownika \n";
    cout << "3. zapisz do pliku \n";
    cout << "4. wyswietl dane uzytkownika z pliku \n";
    cout << "5. imie od tylu \n";
    cout << "6. zakoncz \n";
    cout << "------------------------------------------------ \n";
}

void next()
{
    cout << "podaj numer nastepnej operacji \n";
}

bool if_size_0()
{
    if (users.size() == 0)
    {
        cout << "brak uzytkownikow \n";
        return false;
    }
    else
    {
        return true;
    }
}

void find_user(string im)
{
    
    if (users.size() == 0)
    {
        cout << "brak uzytkownikow \n";
        goto end;
    }
    for (int z = 0; z < users.size(); z++)
    {
        if (users[z].check_if_obj_exist(im) == true)
        {
            users[z].print();
        }
    }
    end:
    {};
}

bool mail_check(string x)
{
    int l;
    int z = 0;
    for(int i = 0; i < x.size(); i++)
    {
        if (x[i] == '@')
        {
            z++;
            l = i;
        }
        if (z == 2)
        {
            break;
        }
    }
    switch(z)
    {
        case 0:
            return false;
        case 1:
            break;
        case 2:
            return false;
    }
    if(x[0] == '@' or x[1] == '@' or x[x.size() - 1] == '@' or x[x.size() - 2] == '@'
        or x[0] == '.' or x[x.size() - 1] == '.' or x[l - 1] == '.' or x[l + 1] == '.')
        {
            return false;
        }
        return true;
}

void load_to_file()
{
    for(int i = 0; i < users.size(); i++)
    {
        if(users[i].check_if_data_in_file_exist() == true)
        {
            cout << "uzytkownik juz istnieje \n";
            users[i].print();
        }
        else
        {
            users[i].file();
        }
    }
}

//load from file chyba do poprawy
//jakies dziwne rzeczy sie tu wydarzyly
//chociaz moze nie?

void load_from_file(string y)
{
   fstream x;
   x.open("/home/mateuszs/Pulpit/cpp/project/project_cpp/data_base.txt", ios::in);
   string linia;
   string i, n;
   int l = 1;
   while(getline(x, linia))
   {
       switch(l)
       {
        case 1:
            i = linia;
            break;
        case 2:
            n = linia;
            if(i + '_' + n == y)
            {
                cout << "imie: " << i << endl;
                cout << "nazwisko: " << n << endl;
                getline(x, linia);
                cout << "mail: " << linia << endl;
                x.close();
                goto end;
            }
                break;
        case 3:
            l = 0;
       }
       l++;
   }
   x.close();
   cout << "nie znaleziono uzytkownika \n";
   end:
   {}
}

void name_from_back(string x)
{
    for(int i = x.size() - 1; i >= 0; i --)
    {
        cout << x[i];
    }
    cout << endl;
}

string name_surname()
{
    string x;
    cout << "podaj imie i nazwisko(jan_nowak) \n"; cin >> x;
    return x;
}

string name()
{
    string x;
    cout << "podaj imie \n"; cin >> x;
    return x;
}

void operation()
{
    int a;
    string i_n;
    start();
    while(true)
    {
        cin >> a;
        switch(a)
        {
            case 1:
                add_user();
                break;
            case 2:
                if(if_size_0() == true)
                {
                    i_n = name_surname();
                    find_user(i_n);
                    break;
                }
                else
                {
                    break;
                }
            case 3:
                load_to_file();
                break;
            case 4:
                i_n = name_surname();
                load_from_file(i_n);
                break;
            case 5:
                i_n = name();
                name_from_back(i_n);
                break;
            case 6:
                exit(0);
            default:
                cout << "niepoprawna liczba \n";
                break;
        }
        next();
    }
}

// metody -------------------------------------------------

User::User(string i, string n, string e, int li)
{
    imie = i;
    nazwisko = n;
    mail = e;
    id = li;
}

void User::print()
{
    cout << "imie: " << imie << endl;
    cout << "nazwisko: " << nazwisko << endl;
    cout << "mail: " << mail << endl;
    cout << "index: " << id << endl;
}

bool User::check_if_obj_exist(string x)
{
    if (users.size() == 0)
    {
        cout << "brak uzytkownikow";
        return false;
    }
    if (imie + "_" + nazwisko == x)
    {
        return true;
    }
    else
    {
        cout << "nie znaleziono uzytkownika \n";
        return false;
    }
}

void User::file()
{
    fstream x;
    x.open("/home/mateuszs/Pulpit/cpp/project/project_cpp/data_base.txt", ios::out | ios::app);
    x << imie << endl;
    x << nazwisko << endl;
    x << mail << endl;
    x.close();
}

bool User::check_if_data_in_file_exist()
{
    fstream x;
    x.open("/home/mateuszs/Pulpit/cpp/project/project_cpp/data_base.txt", ios::in);
    string linia;
    string o = "";
    int i = 1;
    while(getline(x, linia))
    {
        switch(i)
        {
            case 1:
                o += linia;
                break;
            case 2:
                o += linia;
                if (o == imie + nazwisko)
                {
                    x.close();
                    return true;
                }
                o = "";
                break;
            case 3:
                i = 0;
                break;
        }
        i++;
    }
    x.close();
    return false;
}