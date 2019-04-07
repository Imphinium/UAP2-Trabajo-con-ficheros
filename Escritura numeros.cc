#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

//Esta linea declara el nombre del archivo que se a a abrir.
//Se puede declarar estaticamente o leer desde el buffer de entraga,
//pero hay que tener en cuenta que el metodo open()
//solo trabaja con variables de tipo char[], y no aceptara strings
const char nombre[] = "numeros.txt";

int main(int argc, char const *argv[])
{
	//Esta variable almacena el archivo una vez leido
	ofstream fichero_escritura;

	//El metodo open se encarga de abrir el archivo. Toma como argumentos
	//el nombre del archivo a abrir y el metodo de apertura (en este caso, out)
	fichero_escritura.open(nombre, ios::out);

	if (fichero_escritura.is_open()){
		//Este bloque se ejecuta en caso de que el fichero haya sigo abierto
		string s;

		for (int i = 0; i < 100; i++){
			fichero_escritura << i << "\n";
		}

	} else {
		//Este bloque se ejecuta en caso de que el fichero no se pueda abrir
		//Es recomendable manejar la excepcion de algun modo
		cout << "ERROR: NO SE HA PODIDO ABRIR EL ARCHIVO" << endl
				<< "ACABANDO EJECUCION" << endl;
	}

	//El metodo close cierra el archivo. Es importante cerrar el archivo
	//para eitar maluso del disco duroy corrupciones. Este metodo
	//se llama automaticamente al acabar el programa. Aun asi
	//es recomendable llamarlo manualmente
	fichero_escritura.close();
	return 0;
}