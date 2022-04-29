#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <ctime>
#include <windows.h>
#include <sstream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <math.h>
#include <filesystem>
using namespace std;
struct AlmacenarAlarmas{
  string hora;
  string mins;
  string asunto;
};
void Alarma(string hora, string mins, string asunto){
  time_t ahora = time(0);
  string data = ctime(&ahora);
  string* palabra = new string;
  string* nhor = new string;
  string* nmin = new string;
  stringstream ExtFecha(data);
  ShowWindow(GetConsoleWindow(), 0);
  while(1){
    for(int i = 0; i < 5; i++){
      ExtFecha >> *palabra;
      if(i==3){
        *nhor = palabra->substr(0, palabra->find(':'));
        *nmin = palabra->substr(3, palabra->find(':'));
        if(*nhor == hora & *nmin == mins){
          ShowWindow(GetConsoleWindow(), 1);
          while(1){
            SetForegroundWindow(GetConsoleWindow());
            cout << asunto << endl;
            this_thread::sleep_for(chrono::milliseconds(500));
          }
          exit(0);
        }
        this_thread::sleep_for(chrono::seconds(10));
        break;
      }
    }
    time_t ahora = time(0);
    string data = ctime(&ahora);
    ExtFecha = stringstream(data);
  }
}
void AlarmaRapida(int mins, string asunto){
  ShowWindow(GetConsoleWindow(), 0);
  this_thread::sleep_for(chrono::minutes(mins));
  ShowWindow(GetConsoleWindow(), 1);
  while(1){
    SetForegroundWindow(GetConsoleWindow());
    cout << asunto << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
  }
  exit(0);
}
int ConseguirDivisible(int size){
  int pos{};
  for( int i = 9; i > 0 ; i--){
    if(size%i == 0){
      pos = i;
      break;
    } 
  }
  return pos;
}
// 1 => Empujar de path1 a path2
// 0 => Poner alarma
void Libro(int bit, string path1, string path2){
  string* hora = new string;
  string* mins = new string;
  string* asunto = new string;
  vector<AlmacenarAlarmas>* alarmas = new vector<AlmacenarAlarmas>;
  ifstream lista_alarmas(bit ? path1 : path2);
  if(lista_alarmas.is_open()){
    while(!lista_alarmas.eof()){
      lista_alarmas >> *hora >> *mins;
      getline(lista_alarmas, *asunto);
      alarmas->push_back(AlmacenarAlarmas{*hora, *mins, *asunto});
    }
  }
  else{
    cout << "No se ha podido abrir el archivo, saliendo...";
    exit(0);
  }
  lista_alarmas.close();
  delete hora;
  delete mins;
  delete asunto;
  int* pos = new int ; *pos = 0;
  char* coger_respuesta = new char;
  string* check_respuesta = new string;
  int* pag = new int ; *pag = ConseguirDivisible(alarmas->size());
  while(1){
    system("cls");
    for(int i = *pos, j = 1; i<*pos+*pag; i++, j++){
      cout << j << ". " << alarmas->at(i).hora << ":" << alarmas->at(i).mins << " " << alarmas->at(i).asunto << endl;
    }
    cout << "Anterior: 'a'    Siguiente: 'd'      Salir: 'q'    " << "            Pag " << ceil(*pos/ *pag)+1 << " de " << alarmas->size()/ *pag << endl;
    cout << "Opcion: ";
    *coger_respuesta = _getch();
    *check_respuesta = string(1, *coger_respuesta);
    cout << *check_respuesta;
    try{
      stoi(*check_respuesta);
      if(stoi(*check_respuesta) == 0){continue;}
      int* posi = new int ; *posi = *pos+stoi(*check_respuesta)-1 ;
      if(bit){
        ofstream nueva(path2, ios::app);
        if(nueva.is_open()){
          nueva << alarmas->at(*posi).hora << " " << alarmas->at(*posi).mins << alarmas->at(*posi).asunto << endl;
          nueva.close();
          cout << endl << "Alarma " << alarmas->at(*posi).hora << ":" << alarmas->at(*posi).mins << " aniadida a favoritas, pulsa enter para continuar...";
          cin.get();
          continue;
        }else{
        cout << "Hubo algun problema, saliendo...";
        exit(0);
        }
      }else{
        thread(Alarma, alarmas->at(*posi).hora, alarmas->at(*posi).mins, alarmas->at(*posi).asunto).join();
      }
    }catch(...){
      if(*check_respuesta == "a"){
        *pos >= *pag ? *pos-=*pag : *pos = alarmas->size()-*pag;
        continue;
      }
      else if(*check_respuesta == "d"){
        *pos+*pag == alarmas->size() ? *pos=0 : *pos+=*pag;
        continue;
      }
      else if(*check_respuesta == "q"){
        delete pos;
        delete pag;
        delete check_respuesta;
        delete coger_respuesta;
        break;
      }
      else{
        continue;
      }
    }  
  }
} 
void CargarConf(string* path1, string* path2){
  ifstream conf("alarmas_conf.txt");
  if(conf.is_open()){
    conf >> *path1 >> *path2;
  }
}
int main(){
  string path1{};
  string path2{};
  CargarConf(&path1, &path2);
  string* hora = new string;
  string* mins = new string;
  string* asunto = new string;
  char* respuesta = new char;
  char* salir = new char;
  while(1){
    system("cls");
    cout << "Pochoalarmas Gurgui" << endl;
    cout << "1. Nueva alarma" << endl;
    cout << "2. Todas las alarmas" << endl;
    cout << "3. Mis alarmas" << endl;
    cout << "4. Alarma rapida" << endl;
    cout << "5. Configuracion" << endl;
    cout << "0. Salir" << endl;
    *respuesta = _getch();
    if(*respuesta == '1'){
      cout << "-- Introduce la hora hh/mm --" << endl;
      cin >> *hora; 
      cin >> *mins;
      cout << "Asunto => ";
      cin.ignore(10000, '\n');
      getline(cin, *asunto);
      fstream lista_alarmas("alarmas.txt", ios::app);
      if(lista_alarmas.is_open()){
        lista_alarmas << *hora << " " << *mins << " " << *asunto << endl;
      }
      lista_alarmas.close();
      thread(Alarma, *hora, *mins, *asunto).join();
    }else if(*respuesta == '2'){
      Libro(1, path1, path2);
      continue;
    }
    else if(*respuesta == '3'){
      Libro(0, path1, path2);
      continue;
    }
    else if(*respuesta == '4'){
      cout << "Alarma dentro de(minutos) : ";
      cin >> *mins;
      cout << "Asunto: ";
      cin.ignore(10000, '\n');
      getline(cin, *asunto);
      thread(AlarmaRapida, stoi(*mins), *asunto).join();
    }
    else if(*respuesta == '5'){
      string* nuevopath = new string;
      char* rsp = new char;
      cout << endl;
      cout << "1. Path fichero todas alarmas => " << path1 << endl;
      cout << "2. Path fichero mis alarmas => " << path2 << endl;
      cout << "Elige: ";
      *rsp = _getch();
      cout << "Nuevo path: ";
      cin >> *nuevopath;
      ofstream sobreescribir("alarmas_conf.txt");
      *rsp == '1' ? path1 = *nuevopath : path2 = *nuevopath;
      sobreescribir << path1 << endl << path2 << endl;
      delete nuevopath;
      delete rsp;
      continue;
    }
    else if(*respuesta == '0'){
      exit(0);
    }
  }
}
