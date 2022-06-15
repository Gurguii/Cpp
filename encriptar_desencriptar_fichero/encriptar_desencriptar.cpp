#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
using namespace std;
class encriptar_desencriptar{
  char filename[20],ofilename[20], ch; // Nombre del fichero a encriptar/desencriptar y variable que almacenará cada uno de los caracteres para encriptar/desencriptar
  int* opt = new int; // Puntero que almacenará la opción del usuario en Menu()
  int* key = new int; // Puntero que almacenará la clave de encriptación / desencriptación
  public:
    // El constructor llamará a la función Menu
    encriptar_desencriptar(){
      this->Menu();
    }
    // Función que encripta los datos !requiere una clave(introducida por el usuario)
    void Encriptar(){
      cout << "Nombre del fichero a encriptar: ";
      cin >> filename;
      cout << "Fichero de salida: ";
      cin >> ofilename;
      cout << "Clave de encriptación: ";
      cin >> *key;
      ifstream leer(filename);
      ofstream grabar(ofilename);
      if (!leer){
        cout << "Hubo algún problema abriendo el fichero " << filename << " para lectura" << endl;
        exit(0);
      }
      if (!grabar){
        cout << "Hubo algún problema abriendo el fichero " << ofilename << " para escritura" << endl;
        exit(0);
      }
      while(leer>>noskipws>>ch){
        ch+=*key;
        grabar<<ch;
      }
      leer.close();
      grabar.close();
      cout << "Todo listo" << endl;
      exit(0);
    }
    // Función que desencripta los datos !requiere la clave utilizada para su encriptación
    void Desencriptar(){
      cout << "Nombre del fichero a desencriptar: ";
      cin >> filename;
      cout << endl << "Fichero de salida: ";
      cin >> ofilename;
      cout << "Clave de encriptación: ";
      cin >> *key;
      ifstream leer(filename);
      ofstream grabar(ofilename);
      if(!leer){
        cout << "Hubo algún problema abriendo el fichero " << filename << " para lectura" << endl;
        exit(0);
      }
      if(!grabar){
        cout << "Hubo algún problema abriendo el fichero " << ofilename << " para escritura" << endl;
      }
 
      while (leer>>noskipws>>ch){
        ch-=*key;
        grabar<<ch;
      }
    }
    void Menu(){
      while (1){
        system("cls");
        cout << "~ Encriptar & Desencriptar ~" << endl;
        cout << "1. Encriptar" << endl;
        cout << "2. Desencriptar" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> *opt;
        if (*opt == 1){
          this->Encriptar();
          continue;
        }
        if (*opt == 2){
          this->Desencriptar();
          continue;
        }
        if (*opt == 0){
          cout << "[!] Saliendo " << endl;
          exit(0);
        }
        else{
          continue;
        }
      }
    }
};
int main(){
  // Creamos instancia de la clase 'encriptar_desencriptar' que tiene todas las funciones que ofrece el programa
  encriptar_desencriptar user;
}
