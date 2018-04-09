/*
	PROYECTO 1 FUNDAMENTOS DE INFRAESTRUCTURA TECNOL�GICA
	Geovanny Andrés González - 201719528 - ga.gonzalezr
	Juan Felipe Parra - 201714259 - jf.parrac
	Vilma Tirado Gómez - 201632317 - vm.tirado
*/

#include "stdlib.h"
#include "stdio.h"

void escribir(unsigned char *V, unsigned char *s, int p);
void leer(unsigned char *V, unsigned char *s, int p, int l);

int main(int argc, char* argv[])
{
	// Variables
	int op;
	int l, p;
	unsigned char *V;
	unsigned char *s;

	// Inicialización
	V = (unsigned char*) calloc(100, sizeof(char));
	s = (unsigned char*) calloc(17, sizeof(char));

	// Mensaje inicial
	printf("PROYECTO 1 - INFRATEC");

	// Loop hasta terminar
	op = 3;
	while (op != 0)
	{
		// Se pregunta al usuario cual opcion desea realizar
		printf("\n\n* Indique la modalidad\n\t0: Terminar\n\t1: Escribir\n\t2: Leer\n\n");
		printf("Modalidad: ");
		scanf("%d", &op);

		// Escribir
		if (op == 1)
		{
			printf("Acción %d: Escribir\n\n",op);

			// Se reciben los valores de s y p
			printf("Escriba s: ");
			scanf("%s", s);
			printf("Escriba p: ");
			scanf("%d", &p);

			// Se escribe s desde el bit p de V
			escribir(V, s, p);
			printf("\nSe escribió s desde el bit p de V.\n");
		}
		// Leer
		else if (op == 2)
		{
			printf("Acción %d: Leer\n\n",op);

			// Se reciben los valores de l y p
			printf("Escriba l: ");
			scanf("%d", &l);
			printf("Escriba p: ");
			scanf("%d", &p);

			// Se leen l bits de V desde la posición p y se escriben como chars en s
			leer(V, s, p, l);
			printf("Se leyeron los siguientes bits: %s\n", s);
		}
		// Invalido
		else if (op != 0)
		{
			printf("Opción invalida.\n");
		}
	}

	// Terminar
	printf("\nPrograma terminado.\n");
	return 0;
}

/*
	Procedimiento que escribe s empezando en el bit p de V
*/

void escribir(unsigned char *V, unsigned char *s, int p)
{
	//TODO: DESARROLLAR COMPLETAMENTE ESTE PROCEDIMIENTO
	
	unsigned short accesoByte = 0; // Numero entero para conocer cuantos bytes enteros se deben reescribir, cuantas posiciones completas del vector de char.
	unsigned short accesoSiguientes = 0; // En caso de que el modulo 8 (1 byte) de p no sea cero. Son las posiciones siguientes de la siguiente posicion que se deben
											 // reescribir.

	accesoByte = p / 8; // Posiciones del vector char a escribir.
	accesoSiguientes = p % 8; //Bits desde el cual se comienza a escribir en el vector.

	//Luego de tener las posiciones en las cuales se debe escribir se procede a realizar la escritura.
	unsigned char iArreglo = *(V + accesoByte); //Toma el valor del vector sobre el cual se debe realizar la escritura.
	unsigned char iSiguiente = *(V + accesoByte + 1); // Acceso a posicion + 1 del vector char.
	unsigned char iSiguiente2 = *(V + accesoByte + 2); // Acceso a posicion + 2 del vector char.
	unsigned char tamanioCadena = sizeof(s) / 4; // Obtener el tamaño de la cadena ingresada.
	unsigned char tamanioActual = tamanioCadena; //Longitud procesada de la cadena.

	while (tamanioActual > 1) // Hay mas de un caracter para procesar.
	{
						
		if (tamanioCadena > 8) // Si hay mas de 8 se necesitan 2 posiciones. Idea! Correr a izquierda y derecha para limpiar espacios necesarios. Con Mascara asignarlos con OR. Quitar los pedazos asignados
		//Hasta que se termine de consumir la cadena. 
		{
			if (accesoSiguiente != 0)
			{
				// Corre los espacios y limpia los sectores necesarios.
				iArreglo = iArreglo >> (8 - accesoSiguiente);
				iArreglo = iArreglo << (8 - accesoSiguiente);
				
				//Genera la mascara.
				unsigned char mascara = 0; // Mascara a nivel de bits de 0b00000000.				
			}		
		}	
	}	
}

/*
	Procedimiento que lee l bits de V desde la posición p y los escribe
	como chars en s
*/
void leer(unsigned char *V, unsigned char *s, int p, int l)
{
	//TODO: DESARROLLAR COMPLETAMENTE ESTE PROCEDIMIENTO
}
