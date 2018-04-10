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

/**
	=== Metodos auxiliares para realizar algunas partes de los procedimientos ===.
*/

unsigned char generarMascara(unsigned char posInicial, unsigned char posFinal, unsigned char * valores);
void caracteresAValor(unsigned char * caracteres);

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
	caracteresAValor(s); // Pasa la cadena de caracteres para que sea transformada de valores ASCII a 1 y 0 numerico.

	//Luego de tener las posiciones en las cuales se debe escribir se procede a realizar la escritura.
	unsigned char iArreglo = *(V + accesoByte); //Toma el valor del vector sobre el cual se debe realizar la escritura.
	unsigned char iSiguiente = *(V + accesoByte + 1); // Acceso a posicion + 1 del vector char.
	unsigned char iSiguiente2 = *(V + accesoByte + 2); // Acceso a posicion + 2 del vector char.
	unsigned char indiceProcesado = 0; //Indices procesados de la cadena de caracteres!
	unsigned char tamanioCadena = sizeof(s) / 4; // Obtener el tamaño de la cadena ingresada.	

	while (tamanioActual > 1) // Hay mas de un caracter para procesar. OJO: De momento queda en CICLO INFINITO ! No reduzco el tamaño ! Att: Geovanny.
	{

		if (tamanioCadena > 8) // Si hay mas de 8 se necesitan 2 posiciones. Idea! Correr a izquierda y derecha para limpiar espacios necesarios. Con Mascara asignarlos con OR. Quitar los pedazos asignados
		//Hasta que se termine de consumir la cadena. 
		{
				// Corre los espacios y limpia los sectores necesarios.
				iArreglo = iArreglo >> (8 - accesoSiguiente); // Estaba en 8 - accesoS.
				iArreglo = iArreglo << (8 - accesoSiguiente);

				//Genera la mascara.				
				unsigned char mascara = generarMascara(indiceProcesado, 8 - accesoSiguiente, s); //Genera la mascara con los valores 1 y 0 numericos.
				iArreglo = iArreglo | mascara; //Agrega los nuevlos valores a la mascara.				
				indiceProcesado = 8 - accesoSiguientes; // Se avanza al siguiente indice de la cadena que falte por leer.
				//Escritura segundo char.
				iSiguiente = generarMascara(indiceProcesado, indiceProcesado + 8, s); //Como se debe reemplazar completamente el valor se pone
																			//a la mascara a que genere los valores completos de la cadena.
				indiceProcesado += 8; // Se avanza al siguiente indice de la cadena que falte por leer.		
				//Escritura 3er char.
				iSiguiente2 = iSiguiente2 << (16 - indiceProcesado); //Elimina del inicio las posiciones necesarias.
				iSiguiente2 = iSiguiente2 >> (16 - indiceProcesado);

				mascara = generarMascara(indiceProcesado, 16, s); //Obtiene la mascara con los valores faltantes.
				mascara = mascara << (16 - indiceProcesado); //Corre los valores para que queden al inicio.

				// Escribe.
				iSiguiente2 = iSiguiente2 | mascara; 

				// Se actualizan los valores!
				*(V + accesoByte) = iArreglo;
				*(V + accesoByte + 1) = iSiguiente;
				*(V + accesoByte + 2) = iSiguiente2;
			
				//Termina proceso :)
				return;
			}	

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

/*
	Permite generar una mascara con los bits deseados a "pegar" en los char.
	@param valores: Son los valores 1 o 0 que se van a agregar a la mascara.
	@return Una mascara con los valores deseados incluidos.
*/

unsigned char generarMascara(unsigned char posInicial, unsigned char posFinal, unsigned char * valores)
{
	unsigned char mascara = 0; // Valor inicial de la mascara en binario. 00000000.
	unsigned char indice = posInicial; // Indice para iterar sobre el arreglo de caracteres.
	while (indice < posFinal) 
	{
		mascara = mascara << 1; // Desplaza a la izquiera esperando el siguiente bit.
		mascara = mascara | valores[indice]; //Pega el bit 1 o 0 a la mascara.		
		indice++;
	}

	return mascara; //Retorna la mascara con los bits añadidos.
}

/*
	Permite generar una mascara con los bits deseados a "pegar" en los char.
	@param caracteres: Son los caracteres recibidos en la cadena de entrada ingresada por el usuario.
	@return Un apuntador a la primera posicion del arreglo con los caracteres traducidos de ASCII a valores 1 o 0.
*/

void caracteresAValor(unsigned char * caracteres) // Verificar si el paso por parametro se puede en C !
{
	unsigned char i = 0; //Variable para el indice.
	while (caracteres[i])
	{
		unsigned char valorPosicion = *(caracteres + i); //Reemplaza por valores numericos.
		caracteres[i] = (valorPosicion == '1') ? 1 : 0;
		i++;
	}
}