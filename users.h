#include <iostream>
#include <string>
#include <vector>
using namespace std;

void add_user();
void start();
void next();
bool mail_check(string);
bool if_size_0();
void load_to_file();
void find_user(string);
void load_from_file(string);
void name_from_back(string);
string name_surname();
string name();

void operation();

class User
{
  string imie;
  string nazwisko;
  string mail;
  int id;
public:
  
  User(string = "brak", string = "brak", string = "brak", int = 0);
  void print();
  void file();
  bool check_if_data_in_file_exist();
  bool check_if_obj_exist(string);
};