#include <iostream>
#include <string>
#include <vector>
#include <fstream>
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
string ComprobarDni(){
  char letras[23] = {'T','R','W','A','G','M','Y','F','P','D','X','B','N','J','Z','S','Q','V','H','L','C','K','E'};
  string* dni = new string;
  int* numero = new int;
  char* letra = new char;
  while (true){
    cout << "Dni: ";
    cin >> *dni;
    *numero = stoi(dni->substr(0,8));
    *letra = dni->at(dni->size()-1);
    if ( letras[*numero%23] == char(toupper(*letra)) ){
      delete numero;
      delete letra;
      return(*dni);
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
auto CogerInput(){
  string nombre;
  string apellido;
  int edad;
  string dni = ComprobarDni();
  cout << "Nombre: ";
  cin >> nombre;
  cout << "Apellido: ";
  cin >> apellido;
  cout << "Edad: ";
  cin >> edad;
  string sexo = CogerSexo();
  cin.get();
  return(Persona{dni, nombre, apellido, edad, sexo});
}
void NuevoUsuario(Contactos* contacts){
  contacts->userlist.push_back(CogerInput());
  contacts->contador+=1;
}
void BuscarUsuario(Contactos* contacts){
  string* buscar;
  cout << "Introduce dni: " << endl;
  cin>>*buscar;
  for(int i = 0; i<contacts->userlist.size(); i++){
    if (contacts->userlist[i].dni == *buscar){
      cout << "* Usuario encontrado *" << endl;
      cout << "Nombre   --> " << contacts->userlist[i].nombre << endl;
      cout << "Apellido --> " << contacts->userlist[i].apellido << endl;
      cout << "Edad     --> " << contacts->userlist[i].edad << endl;
      cout << "Sexo     --> " << contacts->userlist[i].sexo << endl;
    }
  }
  delete buscar;
  system("pause");
}
void EliminarUsuario(Contactos* contacts){
  string dni;
  cout << "Introduce dni del usuario: ";
  cin >> dni;
  for(int i = 0; i<contacts->userlist.size(); i++){
    if(contacts->userlist[i].dni == dni){
      string* respuesta;
      cout << contacts->userlist[i].nombre << " " << contacts->userlist[i].apellido << endl;
      cout << "* Eliminar usuario? s/n *" << endl;
      cin >> *respuesta;
      if( *respuesta == "s" || *respuesta == "si"){
        contacts->userlist.erase(contacts->userlist.begin() + i);
        contacts->contador-=1;
        cout << endl << " * Usuario eliminado exitosamente * " << endl;
        system("pause");
      }
      else{
        break;
      }
    }
  }
}
void VaciarUsuarios(Contactos* contacts){
  cout << "* Una vez se vacie la base de datos, no podra recuperarse la informacion de los usuarios *" << endl;
  cout << "* Vaciar lista de datos? s/n *" << endl; 
  string* respuesta;
  cin >> *respuesta;
  if (*respuesta == "s" || *respuesta == "si"){
    contacts->userlist.clear();
    contacts->userlist.shrink_to_fit();
    contacts->contador=0;   
    cout << "* La base de datos ha sido vaciada con exito *" << endl;
  }
  delete respuesta;
  system("pause");
}
void VerUsuarios(Contactos* contacts){
  int cantidad;
  string respuesta;
  cout << "Usuarios por pagina: " << endl;
  cin >> cantidad;
  system("cls");
  for(int i = 1; i<=contacts->userlist.size() ; i++){
    cout << "*" << contacts->userlist[i-1].nombre << " " << contacts->userlist[i-1].apellido << "*" << endl << endl;
    cout << "DNI --> " << contacts->userlist[i-1].dni << endl;
    cout << "Edad --> " << contacts->userlist[i-1].edad << endl;
    cout << "Sexo --> " << contacts->userlist[i-1].sexo << endl << endl;
    if (i%cantidad == 0){
      cout << "pag " << i/cantidad << " de " << contacts->userlist.size()/cantidad << endl << endl;
      cout << "Continuar... s/n";
      cin >> respuesta;
      if (respuesta == "s" || respuesta == "si"){
        system("cls");
        continue;
      }
      else{
        break;
      }
    }
  }
  system("pause");
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
    cin >> opcion ; 
    switch (opcion){
      case 1:
        NuevoUsuario(&contacts);
        continue;
      case 2:
        BuscarUsuario(&contacts);
        continue;
      case 3:
        EliminarUsuario(&contacts);
        continue;
      case 4:
        VaciarUsuarios(&contacts);
        continue;
      case 5:
        VerUsuarios(&contacts);
        continue;
      case 6:
        GuardarCambios(&contacts);
        continue;
      case 0:
        return(0);
        exit(0);
      default:
        break;
    }
  }
}
