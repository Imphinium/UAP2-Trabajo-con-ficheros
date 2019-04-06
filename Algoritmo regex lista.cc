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
const char nombre[] = "lista.txt";

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
		//Ten en cuenta que en c++, \* significa "literal *". En regex \( significa
		//"literal (". Y cuando juntas los dos tienes que escribir \\( para que
		//c++ lea "literal \(" y el motor de regex lea "literal (".
		regex exp_tipo("\\(([A-z].*)\\)");
		regex exp_nombre(" - ([A-z].*)");

		//Este bucle se mantiene ejecutandose siempre que queden caracteres
		while (!fichero_lectura.eof()){

			//Esta linea mete el buffer de lectura de datos en un string
			//directamente. Es el analogo de hacer un getline(cin, s)
			//cuando quieres copiar el buffer de entrada a un string directamente
			getline(fichero_lectura, s);

			//Estos couts dan formato y ayudan a dar visibilidad a las partes del algoritmo
			cout << "-----NUEVA LINEA-----" << endl;
			cout << "LINEA:\t\t" << s << endl;

			//La función regex_search recibe tres argumentos: Elk string donde buscar,
			//el smatch donde volvar los resultados y la expresión regular
			//que comparar. Este primero busca "Cualquier cosa dentro de paréntesis" y
			//"de las cosas dentro de paréntesis, las letras" (según la expresión
			//regular exp_tipo). Por ejemplo, si nuestro s = "(CASA) - Moncloa", resulta en
			//0 = "(CASA)" y 1 = "CASA". A nosotros nos interesa el segundo, así que extraemos
			//el string en la posición 1 a la hora de imprimirlo
			regex_search(s,m,exp_tipo);
			cout << "TIPO:\t\t" << m.str(1) << endl;

			//Este segundo regex utiliza mas o menos los mismos términos
			regex_search(s,m,exp_nombre);
			cout << "NOMBRE:\t\t" << m.str(1) << endl;

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