#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <ctime>
#include <windows.h>
using namespace std;
void Contador(int n){
  int s{0};
  this_thread::sleep_for(chrono::minutes(n));
  while(1){
    ShowWindow(GetConsoleWindow(), 1);
    cout << "ES LA HORA MAIK WASOUSKI" << endl;
    cout << "Posponer(minutos, letra para sair) => ";
    cin >> s;
    if(!s){exit(0);}
    ShowWindow(GetConsoleWindow(), 0);
    this_thread::sleep_for(chrono::minutes(s));
  }
}
int main(){
  int n{};
  time_t ahora = time(0);
  string hora_actual = ctime(&ahora);
  cout << hora_actual;
  cout << "Minutos para alarma => ";
  cin >> n;
  ShowWindow (GetConsoleWindow(), 0);
  thread(Contador, n).join();
}
