#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

//Esta linea declara el nombre del archivo que se a a abrir.
//Se puede declarar estaticamente o leer desde el buffer de entraga,
//pero hay que tener en cuenta que el metodo open()
//solo trabaja con variables de tipo char[], y no aceptara strings
const char nombre[] = "garry.txt";

int main(int argc, char const *argv[])
{
	//Esta variable almacena el archivo una vez leido
	ifstream fichero_lectura;

	//El metodo open se encarga de abrir el archivo. Toma como argumentos
	//el nombre del archivo a abrir y el metodo de apertura (en este caso, in)
	fichero_lectura.open(nombre, ios::in);

	if (fichero_lectura.is_open()){
		//Este bloque se ejecuta en caso de que el fichero haya sigo abierto
		char c;
		int modo = 0;
		string palabra;
		vector <string> palabras;

		//Este bucle se mantiene ejecutandose siempre que queden caracteres
		while (!fichero_lectura.eof()){
			//Esta instruccion especifica coger un caracter del archivo a la vez.
			//fichero_lectura es una variable que funciona como un buffer,
			//simiar a trabajar con cout o cin. Es posible usar los operadores
			//>> o <<, pero estos ignoran espacios en blanco y saltos de linea
			fichero_lectura.get(c);

			//Esta parte del algoritmo recibe las letras y decide que hacer con ellas
			switch(modo){
				//El caso 0, el inicial, espera una G/g, la mete en la palabra y cambia de modo
				case 0:
				if(toupper(c)=='G'){
					palabra = "";
					palabra += c;
					modo = 1;
				}
				break;

				//El caso 1 va metiendo letras a la palabra hasta que encuentra una A/a
				//Sin embargo si encuentra un espacio cancela el proceso hasta la siguiente G
				case 1:
				palabra += c;
				if(toupper(c)=='A'){
					palabras.push_back(palabra);
					modo = 0;
				} else if (c == ' '){
					modo = 0;
				}
				break;
			}

		}

		//Este pequeño bloque imprime todas las palabras grabadas
		for(unsigned int i = 0; i < palabras.size(); i++){
			cout << palabras.at(i) << ':';
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
	fichero_lectura.close();
	return 0;
}