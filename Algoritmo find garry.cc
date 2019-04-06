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
		string s;

		//Este bucle se mantiene ejecutandose siempre que queden caracteres
		while (!fichero_lectura.eof()){

			//Esta linea mete el buffer de lectura de datos en un string
			//directamente. Es el analogo de hacer un getline(cin, s)
			//cuando quieres copiar el buffer de entrada a un string directamente
			getline(fichero_lectura, s);

			//Estos couts dan formato y ayudan a dar visibilidad a las partes del algoritmo
			cout << "-----NUEVA LINEA-----" << endl;
			cout << "LINEA ORIGINAL:\t\t" << s << endl;

			while(s.find("G") != string::npos){
						//Aqui se asignan las posiciones de la 'G' y la 'a' que se están buscando
						//Para la G es simple, ya que al querer que sea inclusivo no se modifica
						//Para que la a sea inclusiva hay que sumarle una posición
						int pos_G = s.find("G");
						int pos_a = s.find("a")+1;

						//Esta linea puede llevar a confusión. Este if es una prueba que comprueba si
						//la letra siguiente a la a es un espacio, para comprobar si es una palabra.
						//En caso de que no fuera una palabra, la omitiría y seguiría con el algoritmo
						//¿Porque la variable pos_a marca aqui la posición _siguiente_ a la 'a',
						//y en el substr marca la posición de la 'a'? Esto es debido a que el metodo
						//at trata pos_a como una posicion de array y el método substr empieza a
						//contar en uno. Para visualizarlo: substr Guerra    at Guerra
						//                                         1234567      0123456
						if(s.at(pos_a) != ' '){
							s = s.substr(pos_a+1);
							continue;
						}
						
						//Este cout imprimir un sub string del string original, cortando por las
						//posiciones que nosotros queremos. En este caso, las de los carácteres
						//'G' y 'a'. Pongamos que nuestra linea es "Guerra Goma". En este caso, 
						//pos_G = 0 y pos_a = 6.
						cout << "PALABRA ENTRE G y a:\t" << s.substr( pos_G, pos_a ) << endl;
			
						//Una vez acabamos de trabajar con el string, podemos seguir con las siguientes
						//palabras del string, "cortando" la parte que ya no nos interesa de este.
						//En este caso en concreto, sabemos que las palabras van seguidas por un espacio
						//y ya que no lo vamos a usar en el siguiente paso bien podríamos borrarlo
						s = s.substr(pos_a+1);
						
						cout << "PALABRAS RESTANTES:\t" << s << endl;
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