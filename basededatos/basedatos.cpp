#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <math.h>
using namespace std;
//Supongo que esto no hace falta ni mucho menos, con una estructura sería 
//suficiente para hacerlo, pero me apetecía usar clases :P
class Currentuser{
  protected:
    int privilegios;
  public:
    int id;
    string usuario;
    string pass;
    void set_data(int id, string usuario, string pass, int privilegios){
      this->id = id;
      this->usuario = usuario;
      this->pass = pass;
      this->privilegios = privilegios;
    }
    void Perfil(){
      cout << "Esto esta en construccion" << endl;
      cout << this->usuario << endl;
      cout << this->id << endl;
      cout << this->pass << endl;
      cout << this->privilegios << endl;
      cin.get();
      cin.clear();
      cin.ignore(10000,'\n');
    }
    int check_privs(){
      if(this->privilegios){
        return(1);
      }
      else{
        return(0);
      }
    }
};
int recordar_guardado = 0;
Currentuser currentuser;
struct Persona{
  string dni;
  string nombre;
  string apellido;
  int edad;
  string sexo;
};
struct Contactos{
  vector<Persona> userlist{};
  int contador = 0;
};
void Cabecera(string section){
  system("cls");
  cout << endl << "-------- " << section << " --------" << endl;
  cout << "Introduce 'q' para volver" << endl << endl;
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
  recordar_guardado=1;
}
void BuscarUsuario(Contactos* contacts){
  string* dni = new string;
  *dni = ComprobarDni();
  for(int i = 0; i<contacts->userlist.size(); i++){
    if (contacts->userlist[i].dni == *dni){
      cout << "--Usuario encontrado--" << endl;
      cout << "Nombre   --> " << contacts->userlist[i].nombre << endl;
      cout << "Apellido --> " << contacts->userlist[i].apellido << endl;
      cout << "Edad     --> " << contacts->userlist[i].edad << endl;
      cout << "Sexo     --> " << contacts->userlist[i].sexo << endl;
      cout << "Pulse enter para continuar ..." << endl;
      cin.get();
      cin.clear();
      cin.ignore(10000, '\n');
      delete dni;
      return;
    }
  }
  delete dni;
  cout << "No se ha encontrado ningun usuario con dni: " << *dni << endl;
  cin.get();
  cin.clear();
  cin.ignore(10000, '\n');
}
void EliminarUsuario(Contactos* contacts){
  string* dni = new string;
  *dni = ComprobarDni();
  for(int i = 0; i<contacts->userlist.size(); i++){
    if(contacts->userlist[i].dni == *dni){
      string* respuesta = new string;
      cout << contacts->userlist[i].nombre << " " << contacts->userlist[i].apellido << endl;
      cout << "Eliminar usuario s/n ";
      cin >> *respuesta;
      if( *respuesta == "s" || *respuesta == "si"){
        contacts->userlist.erase(contacts->userlist.begin() + i);
        contacts->contador-=1;
        cout << endl << "-- Usuario eliminado --" << endl;
        recordar_guardado=1;
        cout << "Pulse enter para continuar...";
        delete dni;
        delete respuesta;
        cin.get();
        cin.clear();
        cin.ignore(10000,'\n');
      }
      else{
        delete dni;
        delete respuesta;
        break;
      }
    }
  }
}
void VaciarUsuarios(Contactos* contacts){
  string* respuesta = new string;
  cout << "Vaciar lista de datos? s/n ";
  cin >> *respuesta;
  if (*respuesta == "s" || *respuesta == "si"){
    contacts->userlist.clear();
    contacts->userlist.shrink_to_fit();
    contacts->contador=0;   
    recordar_guardado=1;
    cout << "-- La base de datos ha sido vaciada --" << endl;
  }
  delete respuesta;
}
void VerUsuarios(Contactos* contacts){
  int* cantidad = new int;
  *cantidad = 0;
  string* temp = new string;
  //MEJORAR ESTE DESASTRE
  while(1){
    cout << "Cantidad de usuarios por pag: ";
    *temp = _getch();
    if(*temp == "q" || *temp == "Q"){
      return;
    }else{
      *cantidad = stoi(*temp);
      break;
    }
  }
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
    for(int i = *pos, j = 1 ; i < *max ; i++,j++){
      if (i == contacts->contador){
        break;
      }
      cout << endl << "-- " << j << ". " << contacts->userlist[i].nombre << " " << contacts->userlist[i].apellido << " --" << endl;
      cout << "Dni: " << contacts->userlist[i].dni << endl;
      cout << "Edad: " << contacts->userlist[i].edad << endl;
      cout << "Sexo: " << contacts->userlist[i].sexo << endl;
    }
    cout << endl << "Pagina " << floor(*max/(*cantidad)) << " de " << contacts->contador/(*cantidad) + *unamas << endl << endl;
    cout << "Anterior: 'a'    Siguiente: 'd'      Editar: 'e'        Salir: 'q'       Eliminar: 'x' ";
    *eleccion = _getch();
    if(*eleccion == "a" || *eleccion == "A"){
      if(*pos == 0){continue;}
      *pos = *pos - *cantidad;
      continue;
    }
    else if(*eleccion == "d" || *eleccion == "D"){
      if(*pos == contacts->userlist.size()-1){continue;}
      *pos = *max;
      continue;
    }
    else if(*eleccion == "x" || *eleccion == "X"){
      string* opc = new string;
      int* index = new int;
      cout << endl << "A quien deseas eliminar?";
      cin >> *index;
      if(currentuser.check_privs()){
        //BORRAR USUARIO
        cout << "Vas a eliminar a " << contacts->userlist[*pos+*index-1].nombre << " " << contacts->userlist[*pos+*index-1].apellido << endl;
        cout << "Continuar? s/n ";
        cin >> *opc;
        if(*opc == "s" || *opc == "S"){
          contacts->userlist.erase(contacts->userlist.begin()+(*pos+*index-1));
          delete index;
          delete opc;
          cout << "Usuario eliminado" << endl;
          recordar_guardado = 1;
          cin.get();
          cin.clear();
          cin.ignore(10000, '\n');
          continue;
        }
        else{
          continue;
        }
      }
      else{
        cout << "No tienes privilegios pa" << endl;
        cin.get();
        cin.clear();
        cin.ignore(10000, '\n');
        delete index;
        delete opc;
        continue;
      }
    }
    else if(*eleccion == "e" || *eleccion == "E"){
      int* indice = new int;
      string* rsp = new string;
      string* rsp2 = new string;
      cout << "Elige usuario: ";
      cin >> *indice;
      Cabecera("Editando " + contacts->userlist[*pos+*indice-1].nombre + " " + contacts->userlist[*pos+*indice-1].apellido);
      cout << "1. " << contacts->userlist[*pos+*indice-1].nombre << endl;
      cout << "2. " << contacts->userlist[*pos+*indice-1].apellido << endl;
      cout << "3. " << contacts->userlist[*pos+*indice-1].edad << endl;
      cout << "4. " << contacts->userlist[*pos+*indice-1].sexo << endl;
      while(true){
        cout << "=> ";
        *rsp = _getch();
        if(*rsp == "1"){
          cout << "Nuevo nombre => ";
          cin >> *rsp2;
          contacts->userlist[*pos+*indice-1].nombre = *rsp2;
          recordar_guardado = 1;
        }else if(*rsp == "2"){
          cout << "Nuevo apellido => ";
          cin >> *rsp2;
          contacts->userlist[*pos+*indice-1].apellido = *rsp2;
          recordar_guardado = 1;
        }else if(*rsp == "3"){
          cout << "Nueva edad => ";
          cin >> *rsp2;
          contacts->userlist[*pos+*indice-1].edad = stoi(*rsp2);
          recordar_guardado = 1;
        }else if(*rsp == "4"){
          cout << "Nuevo sexo => ";
          cin >> *rsp2;
          contacts->userlist[*pos+*indice-1].sexo = *rsp2;
          recordar_guardado = 1;
        }else if(*rsp == "q" || *rsp == "Q"){
          delete indice;
          delete rsp;
          delete rsp2;
          break;
        }
      }
      continue;
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
  cout << "Cambios guardados, pulse enter para continuar... ";
  cin.get();
  cin.clear();
  cin.ignore(10000,'\n');
}
int BuscarCopias(string* username){
  ifstream registrados("registrados.txt");
  string* check = new string;
  while(registrados){
    registrados >> *check;
    if(*check == *username){
      cout << "Ya existe una cuenta con ese nombre de usuario :(" << endl;
      return(1);
    }
  }
  delete check;
  return(0);
}
int RegistrarUsuario(){
  int* id = new int;
  *id = 0;
  string* linea = new string;
  ifstream contar_usuarios("registrados.txt");
  if(contar_usuarios){
    while(contar_usuarios){
      getline(contar_usuarios, *linea);
      *id+=1;
    }
  }
  string* username = new string;
  string* susername = new string;
  string* pass = new string;
  string* spass = new string;
  do{
    cout << "Usuario: ";
    cin >> *username;
  }while(BuscarCopias(username));
  do{
    cout << "Repetir usuario: ";
    cin >> *susername;
  }while(*username != *susername);
  cout << endl << "Contrasenia: ";
  cin >> *pass;
  do{
    cout << "Repetir contrasenia: ";
    cin >> *spass;
  }while(*pass != *spass);
  fstream fichero_registrados("registrados.txt", ios::app);
  if(fichero_registrados){
    fichero_registrados << endl << *id << " " << *username << " " << *pass << " " << 0;
    fichero_registrados.close();
    return(1);
  }
  delete id;
  delete username;
  delete susername;
  delete pass;
  delete spass;
  return(0);
}
int IniciarSesion(int* id, string* usuario, string* contra, int* privs){
  int* aidi = new int;
  int* privilegios = new int;
  string* username = new string;
  string* pass = new string;
  string* checkuser = new string;
  string* checkpass = new string;
  cout << "Usuario: ";
  cin >> *username;
  cout << "Contrasenia: ";
  cin >> *pass;
  ifstream check_login("registrados.txt");
  while(check_login){
    check_login >> *aidi >> *checkuser >> *checkpass >> *privilegios;
    if(*checkuser == *username & *checkpass == *pass){
      check_login.close();
      *id = *aidi;
      *usuario = *username;
      *contra = *pass;
      *privs = *privilegios;
      delete aidi;
      delete privilegios;
      delete username;
      delete pass;
      delete checkuser;
      delete checkpass;
      return(1);
    }
  }
  check_login.close();
  cout << "Por favor, revisa las credenciales" << endl;
  cin.get();
  cin.clear();
  cin.ignore(10000,'\n');
  return(0);
}
//HACER CAMBIARDATOS();
int main(){
  int* userid = new int;
  string* username = new string;
  string* pass = new string;
  int* privs = new int;
  //PRIMERO INICIAR SESION
  int* eleccion = new int;
  while(1){
    system("cls");
    cout << "1. Iniciar sesion" << endl;
    cout << "2. Registrarse" << endl;
    cout << "0. Salir" << endl;
    cout << "Opcion: ";
    cin >> *eleccion;
    if (*eleccion == 1){
      if(IniciarSesion(userid, username, pass, privs)){break;}else{continue;}
    }else if(*eleccion == 2){
      if(RegistrarUsuario()){
        cout << "Te has registrado con exito :)" << endl;
        cout <<"Enter para continuar";
        cin.get();
        cin.clear();
        cin.ignore(10000,'\n');
        continue;}
    }else if(*eleccion == 0){
      exit(0);
    }else{
      continue;
    }
  }
  currentuser.set_data(*userid, *username, *pass, *privs);
  delete userid;
  delete username;
  delete pass;
  delete privs;
  delete eleccion;
  //DESPUES LEER DATOS
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
    cout << "**** " << "Bienvenid@ " << currentuser.usuario << " ****" << endl;
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
        GuardarCambios(&contacts);
        continue;
      case '0' :
        if(recordar_guardado){
          string* rsp = new string;
          cout << "Hay cambios sin guardar, quieres guardarlos? s/n: ";
          cin >> *rsp;
          if(*rsp == "s" || *rsp == "si"){
            GuardarCambios(&contacts);
          }
          delete rsp;
        }
        return(0);
        exit(0);
      default :
        break;
    }
  }
}
