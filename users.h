#include <iostream>
#include <string>
#include <vector>
using namespace std;

void add_user();
void start(int o);
bool mail_check(string);
void load_to_file();
void find_user(string);
void load_from_file(string);

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