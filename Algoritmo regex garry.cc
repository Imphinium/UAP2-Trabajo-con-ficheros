#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>

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
		string s;

		//smatch es un tipo de dato donde se guardan los resultados de expresiones regulares
		smatch m;

		//regex es un tipo de datos que almacena la expresión regular a ejecutar.
		//Puedes aprender mas sobre expresiones regulares en https://regexr.com/
		regex e("G[A-z]*a(?= |$)");

		//Este bucle se mantiene ejecutandose siempre que queden caracteres
		while (!fichero_lectura.eof()){

			//Esta linea mete el buffer de lectura de datos en un string
			//directamente. Es el analogo de hacer un getline(cin, s)
			//cuando quieres copiar el buffer de entrada a un string directamente
			getline(fichero_lectura, s);

			//Estos couts dan formato y ayudan a dar visibilidad a las partes del algoritmo
			cout << "-----NUEVA LINEA-----" << endl;
			cout << "LINEA:\t\t" << s << endl;

			cout << "PALABRAS:\t";

			//La función regex_search recibe tres argumentos: El string donde buscar,
			//el smatch donde volvar los resultados y la expresión regular que comparar.
			//El siguiente bucle itera mientras que queden coincidencias.
			while (regex_search (s,m,e)) {

				//Este cout imprime la primera coincidencia y le suma un espacio
				cout << m.str() << " ";

				//Esta línea sobreescribe el string original por el sufijo de la coincidencia
				//Para visualizar: Si nuestro string fuera "Me gusta la casa" y la coincidencia
				//fuera "gusta", su prefijo sería " la casa".
				//Hay que tener en cuenta que en este ejemplo solo se guarda el sufijo y 
				//el prefijo se pierde. Si tuvieras un algoritmo que busque 1s y otro que
				//busque 2s, y tu string original es "021102", la primera pasada encontrará
				//dos 1s y dejará string="02", con lo que la segunda solo encontrará un 2,
				//fallando.
				//Es posible arreglar este efecto con m.preffix().str() + m.suffix().str(), creo.
			    s = m.suffix().str();
			}

			cout << endl;

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