#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;
int main()
{
  vector<int> nums = {};
  string conversion = "";
  string listahexa={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  int RGB[3]{};
  char check = {};
  cout << "Salir: 'ctrl+c'" << endl;
  cout << "Ejemplo: 255 255 255 => #fffff" << endl;
  while(1){
    cout << "RGB: ";
    while(!(cin >> RGB[0] >> RGB[1] >> RGB[2])){
      cout << "Mira el ejemplo arriba :P :";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    int cociente = 0;
    int resto = 0;
    string resultados = "";
    for(int n : RGB){
      if (n < 16){
        resultados+=listahexa[n];
        continue;
      }
      while(1){
        cociente = n/16;
        resto = n%16;
        nums.push_back(resto);
        if(cociente>16){
          n = cociente;
          continue;
        }
        else{
          nums.push_back(cociente);
          break;
        }
      }
      for (int i = nums.size()-1; i>=0; i--){
        conversion+=listahexa.at(nums.at(i));
      }
      resultados+=conversion;
      conversion = "";
      nums.clear();
    }
    cout << "#" << resultados << endl;
  }

}