#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <math.h>
 
using namespace std;
struct Persona{
  string dni;
  string nombre;
  string apellido;
  int edad;
  string sexo;
};
struct Contactos{
  vector<Persona> userlist{};
  //No se si renta más meter este contador o hacer userlist.size()
  //Tampoco estoy seguro si renta más crear solo el vector ya que la única forma que he descubierto probando sería pasando todo el vector, y no sólo una address.
  //Intenté crear un vector: vector<Persona> userlist{}; y pasando el address &userlist no me dejaba acceder a las posiciones despues de hacer algunos userlist.push_back() por eso lo de la linea anterior
  int contador = 0;
};
void Cabecera(string section){
  system("cls");
  cout << endl << "-------- " << section << " --------" << endl;
  cout << "Introduce 'q' para volver al menu principal" << endl << endl;
}
string ComprobarDni(){
  char letras[23] = {'T','R','W','A','G','M','Y','F','P','D','X','B','N','J','Z','S','Q','V','H','L','C','K','E'};
  string dni{};
  int* numero = new int;
  char* letra = new char;
  while (true){
    cout << "Dni: ";
    cin >> dni;
    if (dni == "q" || dni == "Q"){
      return("q");
    }
    *numero = stoi(dni.substr(0,8));
    *letra = dni.at(dni.size()-1);
    if ( letras[*numero%23] == char(toupper(*letra)) ){
      delete numero;
      delete letra;
      return(dni);
    }
    else{
      cout << "Introduce un DNI real makinote" << endl;
      continue;
    }
  }
}
string CogerSexo(){
  string* sexo = new string;
  while(true){
    cout << "Sexo H/M : ";
    cin >> *sexo;
    cin.get();
    if ( *sexo == "H" || *sexo == "h" ){
      delete sexo;
      return(string("Hombre"));
    }
    else if ( *sexo == "M" || *sexo == "m" ){
      delete sexo;
      return(string("Mujer"));
    }
    else{
      cout << "M/m = mujer  H/h = hombre" << endl;
    }
    continue;
  }
}
void NuevoUsuario(Contactos* contacts){
  string nombre;
  string apellido;
  int edad;
  string dni = ComprobarDni();
  if (dni == "q"){
    return;
  }
  cout << "Nombre: ";
  cin >> nombre;
  if (nombre == "q" || nombre == "Q"){
    return;
  }
  cout << "Apellido: ";
  cin >> apellido;
  if (apellido == "q" || apellido == "Q"){
    return;
  }
  cout << "Edad: ";
  cin >> edad;
  if (to_string(edad) == "q" || to_string(edad) == "Q"){
    return;
  }
  string sexo = CogerSexo();
  contacts->userlist.push_back(Persona{dni, nombre, apellido, edad, sexo});
  contacts->contador+=1;
}
void BuscarUsuario(Contactos* contacts){
  string* dni = new string;
  *dni = ComprobarDni();
  for(int i = 0; i<contacts->userlist.size(); i++){
    if (contacts->userlist[i].dni == *dni){
      cout << "* Usuario encontrado *" << endl;
      cout << "Nombre   --> " << contacts->userlist[i].nombre << endl;
      cout << "Apellido --> " << contacts->userlist[i].apellido << endl;
      cout << "Edad     --> " << contacts->userlist[i].edad << endl;
      cout << "Sexo     --> " << contacts->userlist[i].sexo << endl;
      system("pause");
    }
  }
  delete dni;
}
void EliminarUsuario(Contactos* contacts){
  string* dni = new string;
  *dni = ComprobarDni();
  for(int i = 0; i<contacts->userlist.size(); i++){
    if(contacts->userlist[i].dni == *dni){
      string* respuesta = new string;
      cout << contacts->userlist[i].nombre << " " << contacts->userlist[i].apellido << endl;
      cout << "* Eliminar usuario? s/n *" << endl;
      cin >> *respuesta;
      if( *respuesta == "s" || *respuesta == "si"){
        contacts->userlist.erase(contacts->userlist.begin() + i);
        contacts->contador-=1;
        delete dni;
        cout << endl << " * Usuario eliminado * " << endl;
        system("pause");
      }
      else{
        delete dni;
        break;
      }
    }
  }
}
void VaciarUsuarios(Contactos* contacts){
  cout << "* Vaciar lista de datos? s/n *" << endl; 
  string* respuesta = new string;
  cin >> *respuesta;
  if (*respuesta == "s" || *respuesta == "si"){
    contacts->userlist.clear();
    contacts->userlist.shrink_to_fit();
    contacts->contador=0;   
    cout << "* La base de datos ha sido vaciada *" << endl;
  }
  system("pause");
}
void VerUsuarios(Contactos* contacts){
  int* cantidad = new int;
  *cantidad = 0;
  cout << "Cantidad de usuarios por pagina: ";
  cin >> *cantidad;
  int* unamas = new int;
  if (contacts->contador % *cantidad != 0){
    *unamas = 1;
  }
  else{
    *unamas = 0;
  }
  int* pos = new int;
  *pos = 0;
  string* eleccion = new string;
  int* max = new int;
  while(*pos >= 0 & *pos < contacts->contador+*unamas){
    *max = *pos + *cantidad;
    system("cls");
    for(int i = *pos ; i < *max ; i++){
      if (i == contacts->contador){
        break;
      }
      cout << endl << "-- " << contacts->userlist[i].nombre << " " << contacts->userlist[i].apellido << " --" << endl;
      cout << "Dni: " << contacts->userlist[i].dni << endl;
      cout << "Edad: " << contacts->userlist[i].edad << endl;
      cout << "Sexo: " << contacts->userlist[i].sexo << endl;
    }
    cout << endl << "Pagina " << floor(*max/(*cantidad)) << " de " << contacts->contador/(*cantidad) + *unamas << endl << endl;
    cout << "Anterior: 'a'    Siguiente: 'd'      Editar: 'e'        Salir: 'q'";

    *eleccion = _getch();
    if(*eleccion == "a" || *eleccion == "A"){
      *pos = *pos - *cantidad;
      continue;
    }
    else if(*eleccion == "d" || *eleccion == "D"){
      *pos = *max;
      continue;
    }
    else if(*eleccion == "e" || *eleccion == "E"){
      string* respuesta1 = new string;
      string* respuesta2 = new string;
      system("cls");
      Cabecera("Editar");
      cout << endl << "Usuarios: " << endl;
      for(int i = *pos, j = 1; i < *max ; i++,j++){
        cout << j << " " << contacts->userlist[i].nombre << " " << contacts->userlist[i].apellido << endl;
      }
      cout << "Opcion: " << endl;
      *respuesta1 = _getch();
      for (int i = 0; i<*cantidad;i++){
        if(*respuesta1 == to_string(i+1)){
          cout << "1. " << contacts->userlist[*pos+(stoi(*respuesta1)-1)].nombre << endl;
          cout << "2. " << contacts->userlist[*pos+(stoi(*respuesta1)-1)].apellido << endl;
          cout << "3. " << contacts->userlist[*pos+(stoi(*respuesta1)-1)].edad << endl;
          cout << "4. " << contacts->userlist[*pos+(stoi(*respuesta1)-1)].sexo << endl;
          cout << "Opcion: " << endl;
          *respuesta2 = _getch();
          while(true){
            if(*respuesta2 == "1"){
              cout << "Cambiar nombre: ";
              cin >> *respuesta2;
              cout << endl << "Nuevo nombre: " << *respuesta2 << endl;
              contacts->userlist[*pos+(stoi(*respuesta1)-1)].nombre = *respuesta2;
              break;
            }else if(*respuesta2 == "2"){
              cout << "Cambiar apellido: ";
              cin >> *respuesta2;
              cout << endl << "Nuevo apellido: " << *respuesta2 << endl;
              contacts->userlist[*pos+(stoi(*respuesta1)-1)].apellido = *respuesta2;
              break;
            }else if(*respuesta2 == "3"){
              cout << "Cambiar edad: ";
              cin >> *respuesta2;
              cout << endl << "Nueva edad: " << *respuesta2 << endl;
              contacts->userlist[*pos+(stoi(*respuesta1)-1)].edad = stoi(*respuesta2);
              break;
            }else if(*respuesta2 == "4"){
              cout << "Cambiar sexo: ";
              cin >> *respuesta2;
              cout << endl << "Nuevo sexo: " << *respuesta2 << endl;
              contacts->userlist[*pos+(stoi(*respuesta1)-1)].sexo = *respuesta2;
              break;
            }else{
              cout << "????" << endl;
              continue;
            }
          }
          cout << "Usuario modificado con exito :) " << endl;
          delete respuesta1;
          delete respuesta2;
        }
      }
    }
    else if(*eleccion == "q" || *eleccion == "Q"){
      break;
    }
  }
  delete max;
  delete pos;
  delete eleccion;
  delete unamas;
  delete cantidad;
}
void GuardarCambios(Contactos* contacts){
  ofstream fichero("data.txt");
  if (fichero){
    for(int i = 0; i<contacts->userlist.size() ; i++){
      fichero << contacts->userlist[i].dni << " " << contacts->userlist[i].nombre << " " << contacts->userlist[i].apellido << " " << contacts->userlist[i].edad << " " << contacts->userlist[i].sexo << endl;
    }
    fichero.close();
  }
  else{
    cout << "No se ha podido abrir el fichero 'data.txt' " << endl;
    exit(0);
  }
  cout << "* Cambios guardados *" << endl;
  system("pause");
}

//HACER CAMBIARDATOS();
int main(){
  Contactos contacts;
  Persona* leerUsuario = new Persona;
  ifstream data("data.txt");
  if(data){
    while(data){
      data >> leerUsuario->dni >> leerUsuario->nombre >> leerUsuario->apellido >> leerUsuario->edad >> leerUsuario->sexo;
      contacts.userlist.push_back(*leerUsuario);
    }
    delete leerUsuario;
    contacts.userlist.pop_back();
    contacts.contador=contacts.userlist.size();
    data.close();
  }
  else{
    cout << "No se ha podido encontrar el fichero 'data.txt' " << endl;
    exit(0);
  }
  int opcion{};
  while(true){
    system("cls");
    cout << "**** Base de datos ****" << endl;
    cout << "Usuarios totales: " << contacts.contador << endl;
    cout << "1. Nuevo usuario" << endl;
    cout << "2. Buscar usuario" << endl;
    cout << "3. Eliminar usuario" << endl;
    cout << "4. Vaciar usuarios" << endl;
    cout << "5. Ver usuarios" << endl;
    cout << "6. Guardar cambios" << endl;
    cout << "0. Salir" << endl;
    cout << "Opcion: ";
    opcion = getch();
    cout << endl;
    switch (char(opcion)){
      case '1' :
        Cabecera("Nuevo usuario");
        NuevoUsuario(&contacts);
        continue;
      case '2' :
        Cabecera("Buscar usuario");
        BuscarUsuario(&contacts);
        continue;
      case '3' :
        Cabecera("Eliminar usuario");
        EliminarUsuario(&contacts);
        continue;
      case '4' :
        Cabecera("Vaciar usuarios");
        VaciarUsuarios(&contacts);
        continue;
      case '5' :
        Cabecera("Ver usuarios");
        VerUsuarios(&contacts);
        continue;
      case '6' :
        Cabecera("Guardar cambios");
        GuardarCambios(&contacts);
        continue;
      case '0' :
        return(0);
        exit(0);
      default:
        break;
    }
  }
}
