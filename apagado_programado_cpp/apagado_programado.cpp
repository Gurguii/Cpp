#include <iostream>
#include <string>
using namespace std;
int main ()
{
  string base = "shutdown /s /t ";
  int tiempo;
  cout << "Minutos --> ";
  cin >> tiempo;
  cin.get();
  tiempo = tiempo * 60;
  string tiempo_texto = to_string(tiempo);
  string comando = base + tiempo_texto ;
  const char* comandofinal = comando.c_str() ;
  system(comandofinal);
  cout << endl << "Adios :)" << endl;
}