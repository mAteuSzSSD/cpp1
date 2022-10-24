#include <iostream>
#include "users.h"
#include <vector>
#include <string>
#include <fstream>
using namespace std;

vector<User> users;

int d = 0;
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

void start(int o)
{
    if (o == 0)
    {
    cout << "1. dodaj nowego uzytkownika \n";
    cout << "2. wyswietl dane uzytkownika \n";
    cout << "3. zapisz do pliku \n";
    cout << "4. wyswietl dane uzytkownika z pliku \n";
    cout << "5. zakoncz \n";
    
    }
    else
    {
        cout << "podaj numer kolejnej operacji \n";
    }
}

void find_user(string im)
{
    for(int i = 0; i < 1; i++)
    {
        if (users.size() == 0)
        {
            cout << "brak uzytkownikow \n";
            break;
        }
        for (int z = 0; z < users.size(); z++)
        {
            if (users[z].check_if_obj_exist(im) == true)
            {
                users[z].print();
            }
        }
    }
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

void load_to_file() //poprawic wczytywanie bo wszystkie dane zawsze sie wczytuja
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

void operation()
{
    int licz = 0;
    int a;
    string i_n;
    while(true)
    {
        start(licz);
        cin >> a;
        switch(a)
        {
            case 1:
                add_user();
                break;
            case 2:
                cout << "podaj imie i nazwisko(jan_nowak) \n";
                cin >> i_n;
                find_user(i_n);
                break;
            case 3:
                load_to_file();
                break;
            case 4:
                cout << "podaj imie i nazwisko(jan_nowak) \n";
                cin >> i_n;
                load_from_file(i_n);
                break;
            case 5:
                exit(0);
            default:
                cout << "niepoprawna liczba";
        }
        licz++;
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
                break;
            case 3:
                i = 0;
                break;
        }
        if (o == imie + nazwisko)
        {
            x.close();
            return true;
        }
        i++;
    }
    x.close();
    return false;
}