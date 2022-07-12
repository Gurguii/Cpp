#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <sstream>
#include <filesystem>
using namespace std;
/*
  '<cstdio> Functions'
  Supongo que esto no hace falta ni mucho menos, con una estructura sería 
  suficiente para hacerlo, pero me apetecía usar clases :P
  También podía prescindir de la función de clase check_privs(); y hacer la variable privilegios pública, pero me apetece probar cosas
  Seguro que hay muchas más cosas mejorables :)
*/
int recordar_guardado = 0;
int usuarios_registrados = 0;
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
class Currentuser{
  struct SolicitudDeAmistad{
    string emisor;
    string mensaje;
  };
  protected:
    int privilegios;
    int cambiosUser = 0;
    string prevusername;
    vector<string> amigos{};
    vector<SolicitudDeAmistad> solicitudes{};
  public:
    string nickname;
    string usuario;
    string pass;
    string mail;
    string estatura;
    string peso;
    void set_data(string* nickname, string* usuario, string* pass, int* privilegios, string* mail, string* estatura, string* peso){
      this->nickname = *nickname; 
      this->usuario = *usuario;
      this->pass = *pass;
      this->privilegios = *privilegios;
      this->mail = *mail;
      this->estatura = *estatura;
      this->peso = *peso;
      this->prevusername = *usuario;
    }
    void CabeceraPerfil(){
      system("cls");
      cout << "****************************" << endl;
      cout << "*****    MI PERFIL    ******" << endl;
      cout << "****************************" << endl;
      cout << "Nick: " << nickname << endl;
      cout <<  "----------------------------" << endl;
      cout << "Usuario: " << usuario << endl;
      cout <<  "----------------------------" << endl;
      cout << "Privilegios: ";
      this->privilegios ? cout << "Si tienes" << endl : cout << "No tienes" << endl;
      cout <<  "----------------------------" << endl;
      cout << "Mail: ";
      this->mail == "''" ? cout << "No establecido" << endl : cout << this->mail << endl;
      cout <<  "----------------------------" << endl;
      cout << "Estatura(m): ";
      this->estatura == "''" ? cout << "No establecida" << endl : cout << "Estatura: " << this->estatura << " m" << endl;
      cout <<  "----------------------------" << endl;
      cout << "Peso(kg): ";
      this->peso == "''" ? cout << "No establecido" << endl : cout << "Peso: " << this->peso << " kg" << endl;
      cout <<  "----------------------------" << endl;
      cout << endl << endl;
    }
    void Perfil(){
      string* respuesta = new string;
      while(1){
        CabeceraPerfil();
        cout << "****************************";
        cout << endl << "          Ajustes         " << endl;
        cout << "****************************" << endl;
        cout << "**** 1. Eliminar cuenta ****" << endl;
        cout << "**** 2. Editar perfil   ****" << endl;
        cout << "**** 3. Guardar cambios ****" << endl;
        cout << "**** 4. Social          ****" << endl;
        cout << "**** 0. Salir           ****" << endl;
        cout << "****************************" << endl;
        cout << "Que quieres hacer? => ";
        cin >> *respuesta;
        if(*respuesta == "0"){
          if(cambiosUser){
            string *respuesta = new string;
            cout << "Hay datos de tu perfil sin guardar, desea guardarlos? s/n ";
            cin >> *respuesta;
            if(*respuesta == "s" || *respuesta == "S"){
              delete respuesta;
              this->GuardarCambios();
              exit(0);
            }
            else{
              cout << endl << "Hasta otra :)" << endl;
              delete respuesta;
              return;
            }
          }
          cout << endl << "Hasta otra :)" << endl;
          return;
        }
        else if(*respuesta == "1"){
          delete respuesta;
          this->EliminarCuenta();
          exit(0);
        }else if(*respuesta == "2"){
          this->EditarPerfil();
          continue;
        }else if(*respuesta == "3"){
          this->GuardarCambios();
          continue;
        }else if(*respuesta == "4"){
          this->Social();
          continue;
        }else{
          continue;
        }
        delete respuesta;
        return;
      }
   }

    void Social(){
      while(1){
        CabeceraPerfil();
        cout << "****************************" << endl;
        cout << "            Social          " << endl;
        cout << "****************************" << endl;
        cout << "**** 1. Aniadir amigo   ****" << endl;
        this->solicitudes.size() ? cout << "*** 2.Ver solicitudes(" << this->solicitudes.size() << ") ***" << endl : cout << "**** 2. Ver solicitudes ****" << endl;
        cout << "**** 3. Lista de amigos ****" << endl;
        cout << "**** 4. Eliminar amigo  ****" << endl;
        cout << "**** 0. Salir           ****" << endl;
        cout << "****************************" << endl;
        cout << "Opcion => ";
        string* respuesta = new string;
        cin >> *respuesta;
        if(*respuesta == "0"){
          delete respuesta;
          return;
        }else if(*respuesta == "1"){
          delete respuesta;
          AddUser();
          Perfil();
        }else if(*respuesta == "2"){
          int* num = new int;
          string* resp = new string;
          if(solicitudes.size() == 0){
            cout << "No tienes solicitudes :( ";
            cin.get();
            cin.clear();
            cin.ignore(10000,'\n');
            continue;
          }
          cout << "Mis solicitudes" << endl;
          cout << "   Nick" << "          Mensaje" << endl;
          for(int i = 0, j = 1; i < solicitudes.size(); i++, j++){
            cout << j << ". " << solicitudes[i].emisor << "       " << solicitudes[i].mensaje << endl;
          }
          cout << "0. Salir" << endl;
          cout << "Solicitud => ";
          cin >> *num;
          if(*num == 0){
            return;
          }
          cout << "Aceptar s/n: ";
          cin >> *resp;
          if(*resp == "s" || *resp == "S"){
            this->amigos.push_back(solicitudes[*num-1].emisor);
            cout << "Solicitud aceptada";
            cin.get();
            cin.clear();
            cin.ignore(10000, '\n');
            this->solicitudes.erase(this->solicitudes.begin()+*num-1);
            ActualizarFicheroAmigos(&this->solicitudes[*num-1].emisor, 0);
            LimpiarSolicitud(&solicitudes[*num-1].emisor);
            continue;
          }else if(*resp == "n" || *resp == "N"){
            cout << "Solicitud rechazada";
            this->solicitudes.erase(this->solicitudes.begin()+*num-1);
            LimpiarSolicitud(&solicitudes[*num-1].emisor);
            cin.get();
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
          }
          delete num;
          delete resp;
          delete respuesta;
        }else if(*respuesta == "3"){
          cout << "Lista de amigos" << endl;
          for(string amigo : this->amigos){
            cout << amigo << endl;
          }
          cin.get();
          cin.clear();
          cin.ignore(10000, '\n');
          continue;
        }else if(*respuesta == "4"){
          string* nick = new string;
          cout << "Amigo a eliminar: ";
          cin >> *nick;
          cin.clear();
          cin.ignore(10000, '\n');
          ActualizarFicheroAmigos(nick, 1);
          for(int i = 0; i < this->amigos.size() ; i++){
            if(this->amigos[i] == *nick){
              this->amigos.erase(this->amigos.begin()+i);
            }
          }
          cout << "Has eliminado a " << *nick << " de tu lista de amigos" << endl;
          cin.get();
          cin.clear();
          cin.ignore(10000, '\n');
          continue;
        }
      }
    }
    void LimpiarSolicitud(string* nick){
      ofstream temporal("temporal.txt");
      ifstream leer("solicitudes.txt");
      string* linea = new string;
      string* emisor = new string;
      string* receptor = new string;
      if(leer.is_open()){
        while(getline(leer, *linea)){
          stringstream(*linea) >> *receptor >> *emisor;
          if(*receptor == this->nickname & *emisor == *nick){
            continue;
          }
          temporal << *linea << endl;
        }
      }
      temporal.close();
      leer.close();
      remove("solicitudes.txt");
      rename("temporal.txt", "solicitudes.txt");
      delete linea;
      delete emisor;
      delete receptor;
    }
    void CargarListaAmigos(){
      string* checknick = new string;
      string* linea = new string;
      string* amigo = new string;
      ifstream leer("amigos.txt");
      if(leer.is_open()){
        while(!leer.eof()){
          leer >> *checknick;
          if(getline(leer, *linea)){
            stringstream ss(*linea);
            if(*checknick == this->nickname){
              while(ss >> *amigo){
                cout << *amigo << endl;
                this->amigos.push_back(*amigo);
              }
            }
          }
        }
      }
      leer.close();
      delete checknick;
      delete linea;
      delete amigo;
    }
    void ActualizarFicheroAmigos(string* enviadordepeticion, int borrar){
      string* line = new string;
      string* nickn = new string;
      string* amigos = new string;
      ifstream leer("amigos.txt");
      ofstream temporal("temporal.txt");
      if(leer.is_open() & temporal.is_open()){
        while(getline(leer, *line)){
          stringstream lineasion(*line);
          lineasion >> *nickn;
          if(*nickn == this->nickname){
            if(borrar){
              while(lineasion >> *nickn){
                if(*nickn == *enviadordepeticion){
                  continue;
                }
                *amigos += " ";
                *amigos += *nickn;
              } 
              temporal << this->nickname << *amigos << endl;
            }else{
              temporal << *line << " " << *enviadordepeticion << endl;
            }
          }else if(*nickn == *enviadordepeticion){
            if(borrar){
              while(lineasion >> *nickn){
                if(*nickn == this->nickname){
                  continue;
                }
                *amigos += " ";
                *amigos += *nickn;
              }
              temporal << *enviadordepeticion << *amigos << endl;
            }else{
              temporal << *line << " " << this->nickname << endl;
            }
          }else{
            temporal << *line << endl;
          }
        }
      }
      delete line;
      delete nickn;
      delete amigos;
      leer.close();
      temporal.close();
      remove("amigos.txt");
      rename("temporal.txt","amigos.txt");
    }
    void ContarSolicitudes(){
      string* linea = new string;
      string* nick = new string;
      string* emisor = new string;
      string* mensaje = new string;
      ifstream solicitudes("solicitudes.txt");
      if(solicitudes.is_open()){
        while(getline(solicitudes, *linea)){
          stringstream(*linea) >> *nick >> *emisor >> *mensaje;
          if(*nick == this->nickname){
            this->solicitudes.push_back(SolicitudDeAmistad{*emisor, *mensaje});
          }
        }
        solicitudes.close();
        delete linea;
        delete nick;
        delete emisor;
        delete mensaje;
      }else{
        cout << "No se ha podido abrir el fichero" << endl;
        exit(0);
      }
    }
    void CheckSolicitudRepetida(string* nick){
      string* line = new string;
      string* word1 = new string;
      string* word2 = new string;
      ifstream checkSolicitud("solicitudes.txt");
      while(!checkSolicitud.eof()){
        if(!checkSolicitud.good()){break;}
        checkSolicitud >> *word1 >> *word2;
        if(*word1 == *nick & *word2 == this->nickname){
          cout << "Ya has mandado una solicitud a " << *nick << ", espera que responda...";
          checkSolicitud.close();
          delete line;
          delete word1;
          delete word2;
          cin.get();
          cin.clear();
          cin.ignore(10000, '\n');
          Perfil();
        }
      }
      delete line;
      delete word1;
      delete word2;
    }
    void CheckAlreadyAgregado(string* nick){
      for(string amigo : this->amigos){
        if(amigo == *nick){
          cout << "Ya tienes a " << *nick << " agregad@ cabesa de webo";
          cin.get();
          cin.clear();
          cin.ignore(10000,'\n');
          Perfil();
        }
      }
    }
    void AddUser(){
      string* nick = new string;
      cout << "Nickname del usuario => ";
      cin >> *nick;
      CheckSolicitudRepetida(nick);
      CheckAlreadyAgregado(nick);
      string* linea = new string;
      string* checknick = new string;
      string* mensaje = new string;
      int* sent = new int{0};
      ifstream fichero("amigos.txt");
      if(fichero.is_open()){
        while(getline(fichero, *linea)){
          stringstream(*linea) >> *checknick;
          if(*checknick == *nick){
            cout << "Aniade un mensaje: ";
            cin.clear();
            cin.ignore(10000, '\n');
            getline(cin, *mensaje);
            fstream solicitudes("solicitudes.txt",ios::app);
            if(solicitudes.is_open()){
              solicitudes << *nick << " " << this->nickname << " " << *mensaje << endl;
              solicitudes.close();
              return;
            }else{
              cout << "No se pudo abrir el fichero" << endl;
              exit(0);
            }
          }
        }
        cout << "No se ha encontrado ningún usuario con ese nombre :( " << endl;
        cin.get();
        cin.clear();
        cin.ignore(10000, '\n');
      }
      delete nick;
      delete linea;
      delete checknick;
      delete mensaje;
      delete sent;
      Perfil();
    }
    void GuardarCambios(){
      string* linea = new string;
      string* user = new string;
      ifstream leer("registrados.txt");
      ofstream grabar("temp.txt");
      if (leer.is_open()){
        while(!leer.eof()){
          getline(leer, *linea);
          stringstream(*linea) >> *user;
          if(*user == this->usuario){
            grabar << *user << " " << this->pass << " " << this->nickname << " " << this->privilegios << " " << this->mail << " " << this->estatura << " " << this->peso << endl;
            continue;
          }
          grabar << *linea << endl;
        }
      }
      leer.close();
      grabar.close();
      remove("registrados.txt");
      rename("temp.txt","registrados.txt");
      delete linea;
      delete user;
    }
    void EditarPerfil(){
      int* respuesta1 = new int;
      string* respuesta2 = new string;
      while(1){
        system("cls");
        cout << "*****************************" << endl;
        cout << "******* EDITAR PERFIL *******" << endl;
        cout << "*****************************" << endl;
        cout << "******  1. Nick        ******" << endl;
        cout << "******  2. Usuario     ******" << endl;
        cout << "******  3. Contrasenia ******" << endl;
        cout << "******  4. Email       ******" << endl;
        cout << "******  5. Estatura    ******" << endl;
        cout << "******  6. Peso        ******" << endl;
        cout << "******  0. Salir       ******" << endl;
        cout << "*****************************" << endl;
        cout << "Cambiar => ";
        *respuesta1 = _getch();
        switch(char(*respuesta1)){
          case '0':
            delete respuesta1;
            delete respuesta2;
            return;
          case '1':
            cout << " Nuevo nickname => ";
            cin >> *respuesta2;
            nickname = *respuesta2;
            cambiosUser = 1;
            continue;
          case '2':
            cout << " Nuevo usuario => ";
            cin >> *respuesta2;
            prevusername = usuario;
            usuario = *respuesta2;
            cambiosUser = 1;
            continue;
          case '3':
            {
              string* checkpass = new string;
              cout << " Introduce actual contrasenia => ";
              cin >> *respuesta2;
              if(*respuesta2 == pass){
                cout << endl << "Nueva contrasenia: ";
                cin >> *respuesta2;
                pass = *respuesta2;
                cout << endl << "Repite: ";
                cin >> *checkpass;
                if(*respuesta2 == *checkpass){
                  pass = *respuesta2;
                  delete respuesta1;
                  delete respuesta2;
                  delete checkpass;
                  cambiosUser = 1;
                  cout << "Listo :)";
                  cin.get();
                  cin.clear();
                  cin.ignore(10000, '\n');
                }
              }
            }
            continue;
          case '4':
            mail == "''" ? cout << "Establece tu mail: " : cout << "Nuevo mail: ";
            cin >> this->mail;
            cambiosUser = 1;
            continue;
          case '5':
            estatura == "''" ? cout << "Establece tu estatura: " : cout << "Nueva estatura: ";
            cin >> this->estatura;
            cambiosUser = 1;
            continue;
          case '6':
            peso == "''" ? cout << "Establece tu peso: " : cout << "Nuevo peso";
            cin >> this->peso;
            cambiosUser = 1;
            continue;
          default:
            delete respuesta1;
            delete respuesta2;
            return;
        }
      } 
    }
    void EliminarCuenta(){
      string* respuesta = new string;
      cout << "No hay forma de deshacer esta decision, continuar s/n ";
      cin >> *respuesta;
      if(*respuesta != "s" & *respuesta != "S"){
        Perfil();
      }
      string* linea = new string;
      string* palabras = new string;
      ifstream fichero("registrados.txt");
      ofstream temp("temp.txt");
      if(fichero.is_open()){
        while(getline(fichero, *linea)){
          if(!fichero.good()){break;}
          stringstream(*linea) >> *palabras;
          if(*palabras == this->usuario){
            continue;
          }
          temp << *linea << endl;
        }
      }
      fichero.close();
      temp.close();
      remove("registrados.txt");
      rename("temp.txt", "registrados.txt");
      cout << "Adios :(" << endl;
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
Currentuser currentuser;
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
    *letra = dni[dni.size()-1];
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
  string* nombre = new string;
  string* apellido = new string;
  int* edad = new int;
  string* dni = new string;
  *dni = ComprobarDni();
  if (*dni == "q"){
    return;
  }
  cout << "Nombre: ";
  cin >> *nombre;
  if (*nombre == "q" || *nombre == "Q"){
    return;
  }
  cout << "Apellido: ";
  cin >> *apellido;
  if (*apellido == "q" || *apellido == "Q"){
    return;
  }
  cout << "Edad: ";
  cin >> *edad;
  if (to_string(*edad) == "q" || to_string(*edad) == "Q"){
    return;
  }
  string* sexo = new string;
  *sexo = CogerSexo();
  contacts->userlist.push_back(Persona{*dni, *nombre, *apellido, *edad, *sexo});
  contacts->contador+=1;
  recordar_guardado=1;
  delete nombre;
  delete apellido;
  delete edad;
  delete dni;
  delete sexo;
}
void BuscarUsuario(Contactos* contacts){
  string* dni = new string;
  *dni = ComprobarDni();
  for(Persona usuario : contacts->userlist){
    if (usuario.dni == *dni){
      cout << "--Usuario encontrado--" << endl;
      cout << "Nombre   --> " << usuario.nombre << endl;
      cout << "Apellido --> " << usuario.apellido << endl;
      cout << "Edad     --> " << usuario.edad << endl;
      cout << "Sexo     --> " << usuario.sexo << endl;
      cout << "Pulse enter para continuar ..." << endl;
      cin.get();
      cin.clear();
      cin.ignore(10000, '\n');
      delete dni;
      return;
    }
  }
  delete dni;
  return;
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
    cout << endl << "Pagina " << floor(*max/ *cantidad ) << " de " << contacts->contador/ *cantidad + *unamas << endl << endl;
    cout << "Anterior: 'a'    Siguiente: 'd'      Editar: 'e'        Salir: 'q'       Eliminar: 'x' ";
    *eleccion = _getch();
    if(*eleccion == "a" || *eleccion == "A"){
      if(*pos == 0){
        *pos = contacts->userlist.size() - *cantidad + 1;
        continue;}
      *pos = *pos - *cantidad;
      continue;
    }
    else if(*eleccion == "d" || *eleccion == "D"){
      if(*max >= contacts->userlist.size()){
        *pos = 0;
        continue;}
      *pos = *max;
      continue;
    }
    else if(*eleccion == "x" || *eleccion == "X"){
      string* opc = new string;
      int* index = new int;
      cout << endl << "Usuario a eliminar => ";
      cin >> *index;
      if(currentuser.check_privs()){
        //BORRAR USUARIO
        cout << "Vas a eliminar a " << contacts->userlist[*pos+*index-1].nombre << " " << contacts->userlist[*pos+*index-1].apellido << endl;
        cout << "Continuar s/n ";
        cin >> *opc;
        if(*opc == "s" || *opc == "S"){
          contacts->userlist.erase(contacts->userlist.begin()+(*pos+*index-1));
          contacts->contador-=1;
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
        cout << "No tienes privilegios nene" << endl;
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
      cout << endl << "Elige usuario: ";
      cin >> *indice;
      int* userpos = new int;
      *userpos = *pos + *indice - 1;
      while(true){
        Cabecera("Editando " + contacts->userlist[*userpos].nombre + " " + contacts->userlist[*userpos].apellido);
        cout << "1. " << contacts->userlist[*userpos].nombre << endl;
        cout << "2. " << contacts->userlist[*userpos].apellido << endl;
        cout << "3. " << contacts->userlist[*userpos].edad << endl;
        cout << "4. " << contacts->userlist[*userpos].sexo << endl;
        cout << "=> ";
        *rsp = _getch();
        if(*rsp == "1"){
          cout << "Nuevo nombre => ";
          cin >> *rsp2;
          contacts->userlist[*userpos].nombre = *rsp2;
          recordar_guardado = 1;
        }else if(*rsp == "2"){
          cout << "Nuevo apellido => ";
          cin >> *rsp2;
          contacts->userlist[*userpos].apellido = *rsp2;
          recordar_guardado = 1;
        }else if(*rsp == "3"){
          cout << "Nueva edad => ";
          cin >> *rsp2;
          contacts->userlist[*userpos].edad = stoi(*rsp2);
          recordar_guardado = 1;
        }else if(*rsp == "4"){
          cout << "Nuevo sexo => ";
          cin >> *rsp2;
          contacts->userlist[*userpos].sexo = *rsp2;
          recordar_guardado = 1;
        }else if(*rsp == "q" || *rsp == "Q"){
          delete indice;
          delete rsp;
          delete rsp2;
          delete userpos;
          break;
        }
        else{continue;}
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
  ifstream fichero("data.txt");
  ofstream fichero2("temp.txt");
  if (fichero.good()){
    for(int i = 0; i<contacts->userlist.size() ; i++){
      fichero2 << contacts->userlist[i].dni << " " << contacts->userlist[i].nombre << " " << contacts->userlist[i].apellido << " " << contacts->userlist[i].edad << " " << contacts->userlist[i].sexo << endl;
    }
    fichero.close();
    fichero2.close();
    remove("data.txt");
    rename("temp.txt","data.txt");
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
    }else{continue;}
  }
  delete check;
  return(0);
}
int RegistrarUsuario(){
  string* linea = new string;
  string* username = new string;
  string* susername = new string;
  string* pass = new string;
  string* spass = new string;
  string* nickname = new string;
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
  cout << "Nickname: ";
  cin >> *nickname;
  fstream fichero_registrados("registrados.txt", ios::app);
  fstream fichero_amigos("amigos.txt", ios::app);
  if(fichero_registrados){
    fichero_registrados << endl << *username << " " << *pass << " " << *nickname << " " << 0 << " " << "''" << " " << "''" << " " << "''";
    fichero_registrados.close();
    if(fichero_amigos){
      fichero_amigos << endl << *nickname;
      fichero_amigos.close();
    }
    return(1);
  }
  delete nickname;
  delete username;
  delete susername;
  delete pass;
  delete spass;
  return(0);
}
int IniciarSesion(string* nickname, string* usuario, string* contra, int* privs, string* mail, string* altura, string* peso){
  string* username = new string;
  string* pass = new string;
  string* checkuser = new string;
  string* checkpass = new string;
  string* linea = new string;
  cout << "Usuario: ";
  cin >> *username;
  cout << "Contrasenia: ";
  cin >> *pass;
  ifstream check_login("registrados.txt");
  if(check_login.is_open()){
    while(!check_login.eof()){
      check_login >> *checkuser >> *checkpass;
      getline(check_login, *linea);
      if(*checkuser == *username & *checkpass == *pass){
        check_login.close();
        *usuario = *checkuser;
        *contra = *checkpass;
        stringstream(*linea) >> *nickname >> *privs >> *mail >> *altura >> *peso ;
        delete username;
        delete pass;
        delete checkuser;
        delete checkpass;
        delete linea;
        return(1);
      }
    }
  }

  check_login.close();
  cout << "Por favor, revisa las credenciales" << endl;
  cin.get();
  cin.clear();
  cin.ignore(10000,'\n');
  return(0);
}
void IniciarSesion(){
  string* nickname = new string;
  string* username = new string;
  string* pass = new string;
  string* mail = new string;
  string* altura = new string;
  string* peso = new string;
  int* privs = new int;
  int* eleccion = new int;
  while(1){
    system("cls");
    cout << "*****************************" << endl;
    cout << "******* Base de datos *******" << endl;
    cout << "*****************************" << endl;
    cout << "**** 1. Iniciar sesion   ****" << endl;
    cout << "**** 2. Registrarse      ****" << endl;
    cout << "**** 0. Salir            ****" << endl;
    cout << "*****************************" << endl;
    cout << "Opcion: ";
    cin >> *eleccion;
    if (*eleccion == 1){
      if(IniciarSesion(nickname, username, pass, privs, mail, altura, peso)){break;}else{continue;}
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
  currentuser.set_data(nickname, username, pass, privs, mail, altura, peso);
  delete altura;
  delete mail;
  delete peso;
  delete nickname;
  delete username;
  delete pass;
  delete privs;
  delete eleccion;
}
void ComprobarCrearFicheros(){
  string ficheros[] = {"data.txt","amigos.txt","registrados.txt","solicitudes.txt"};
  for(string nombre : ficheros){
    if(!filesystem::exists(nombre)){
      ofstream nuevo(nombre);
      if(nuevo){
        nuevo.close();
      }else{
        cout << "No se pudo crear el fichero " << nombre << endl;
        exit(0);
      }
    }
  }
}
int main(){
  ComprobarCrearFicheros();
  IniciarSesion();
  int* registrados = new int;
  *registrados = 0;
  string* linea = new string;
  ifstream ContarUsuarios("registrados.txt");
  if(ContarUsuarios.is_open()){
    while(getline(ContarUsuarios,*linea)){
      *registrados += 1;
    }
  }
  usuarios_registrados = (*registrados-1);
  delete registrados;
  currentuser.ContarSolicitudes();
  currentuser.CargarListaAmigos();
  Contactos contacts;
  Persona* leerUsuario = new Persona;
  ifstream data("data.txt");
  if(data.is_open()){
    while(!data.eof()){
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
    cout << "********************************" << endl;
    cout << "        " << "Bienvenid@ " << currentuser.nickname << endl;
    cout << "********************************" << endl;
    cout << "****   1. Nuevo usuario     ****" << endl;
    cout << "****   2. Buscar usuario    ****" << endl;
    cout << "****   3. Eliminar usuario  ****" << endl;
    cout << "****   4. Vaciar usuarios   ****" << endl;
    cout << "****   5. Ver usuarios      ****" << endl;
    cout << "****   6. Guardar cambios   ****" << endl;
    cout << "****   7. Mi perfil         ****" << endl;
    cout << "****   8. Cerrar sesion     ****" << endl;
    cout << "****   0. Salir             ****" << endl;
    cout << "********************************" << endl;
    cout << "Usuarios registrados: " << usuarios_registrados << endl;
    cout << "Clientes: " << contacts.contador << endl;
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
      case '7' :
        currentuser.Perfil();
        continue;
      case '8' :
        IniciarSesion();
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
