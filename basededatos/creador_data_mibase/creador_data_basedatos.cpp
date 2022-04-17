#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(){
  vector<string> nombresHombres{"Airan","Juan","Pedro","Carlos","Luis","Borja","Pablo","Gustaf","Hugo","Daniel","Alejandro","Lucas"};
  vector<string> nombresMujeres{"Ana","Carla","Marta","Esperanza","Laura","Carmen","Maria"};
  vector<string> apellidos{"Garcia","Rodriguez","Gonzalez","Fernandez","Martinez","Sanchez","Perez"};
  vector<string> dni{"71677415P","23048429Z","59001042Q","24111421S","70726481D","43694742D","75125781F","14544906M","21726576V","21105929W","63919854W","67274219R","48137324A","37743900A","65014883R","47118252S","21179241J","13734099V","13339141S","74399817S"};
  int* cnt = new int;
  string* nombre = new string;
  cout << "Cantidad: ";
  cin >> *cnt;
  cout << endl << "Nombre fichero: " << endl;
  cin >> *nombre;
  ofstream fichero(*nombre);
  if(fichero){
    for(int i = 0;  i < *cnt ; i++){
      if(i==0){
        fichero  << endl << dni[rand() % dni.size()] << " " << nombresHombres[rand() % nombresHombres.size()] << " " << apellidos[rand() % apellidos.size()] << " " << rand() % 100 << " " << "Hombre" ;
      }
      else{
        if (rand()%2){
          fichero  << endl << dni[rand() % dni.size()] << " " << nombresHombres[rand() % nombresHombres.size()] << " " << apellidos[rand() % apellidos.size()] << " " << rand() % 100 << " " << "Hombre" ;
        }
        else{
          fichero  << endl << dni[rand() % dni.size()] << " " << nombresMujeres[rand() % nombresMujeres.size()] << " " << apellidos[rand() % apellidos.size()] << " " << rand() % 100 << " " << "Mujer" ;
        }
      }
    }
    fichero.close();
    cout << "Fichero creado con exito :)" << endl;
  }
  else{
    cout << "No se ha podido encontrar el fichero " << endl;  
    exit(0);
  }
  delete cnt;
  delete nombre;
}