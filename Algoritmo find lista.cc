#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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


		//Este bucle se mantiene ejecutandose siempre que queden caracteres
		while (!fichero_lectura.eof()){

			//Esta linea mete el buffer de lectura de datos en un string
			//directamente. Es el analogo de hacer un getline(cin, s)
			//cuando quieres copiar el buffer de entrada a un string directamente
			getline(fichero_lectura, s);

			//Estos couts dan formato y ayudan a dar visibilidad a las partes del algoritmo
			cout << "-----NUEVA LINEA-----" << endl;
			cout << "LINEA ORIGINAL:\t\t\t" << s << endl;

			//Este cout imprime las posiciones del primer y segundo paréntesis en la linea
			//Estas son las posiciones numericas empezando desde 0
			cout << "POSICION DE PARENTESIS:\t\t" << s.find("(") << '-' << s.find(")") << endl;
			int par_ini = s.find("(");
			int par_fin = s.find(")");
			
			//Este cout imprimir un sub string del string original, cortando por las
			//posiciones que nosotros queremos. En este caso, las de los carácteres
			//'(' e ')'. Pongamos que nuestra linea es "(HOLA) - AAA". En este caso, 
			// par_ini = 0 y par_fin = 4. Si hiciéramos el substring tal cual, qudaría
			//"(HOLA". Esto es debido a que el primer ca´racter es inclusivo. La solucion es
			//simplemente sumarle 1- Si hacemos substr(1,4) quedaría "HOLA)".
			//Se presenta otro problema, que el segundo argumento no es una posición
			//absoluta en el string, sino relativa al primer argumento. La solución entonces
			//es restarle 1 al segundo número. Ahora si, substr(1,3) nos da "HOLA"
			cout << "PALABRA ENTRE PARENTESIS:\t" << s.substr( par_ini+1, par_fin-1) << endl;

			//Una vez acabamos de trabajar con los parentesis, podemos seguir con la
			//siguiente parte del string, "cortando" la parte que ya no nos interesa de este.
			//En este caso en concreto, " - " tampoco nos interesa, así que cortaremos desde
			//"- ", y le sumaremos 2 para que sea inclusivo
			s = s.substr(s.find("- ")+2);

			//Podemos seguir trabajando con el string a partir de aqui. Si nuestra línea fuera
			//"(HOLA) - (ADIOS) - PEPINO", una vez acabamos quedará "(ADIOS) - PEPINO"
			//Este string aún es susteptible a recortes. Podríais, por ejemplo, tener este string
			//en un while que vaya iterando mientras queden carácteres '(' en la línea
			//PISTA: if(s.find('(') != std::string::npos) {}
			cout << "LINEA TRAS GUION Y ESPACIO:\t" << s << endl;
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