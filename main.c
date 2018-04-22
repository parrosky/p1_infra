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
unsigned char longitud (unsigned char * caracteres);

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
	unsigned char tamanioCadena = longitud(s); // Obtener el tamaño de la cadena ingresada.
	caracteresAValor(s); // Pasa la cadena de caracteres para que sea transformada de valores ASCII a 1 y 0 numerico.
	unsigned char * indiceIteracion = V + accesoByte; //Variable para iterar mas comodamente !

	//Luego de tener las posiciones en las cuales se debe escribir se procede a realizar la escritura.
	unsigned char indiceProcesado = 0; //Indices procesados de la cadena de caracteres!
	unsigned char valorActual = 0; // Valor actual que se toma de el vector.	
	unsigned char mascara = 0; //Mascara con los bits necesarios.
	unsigned char modular = 0; //Valores del modulo donde se inicia la cadena de caracteres!

	while (indiceProcesado < tamanioCadena) // Hay mas de un caracter para procesar. OJO: De momento queda en CICLO INFINITO ! No reduzco el tamaño ! Att: Geovanny.
	{
    valorActual = 0; // Reasigna y deja en limpio para trabajar con la posicion del vector V necesaria.
    mascara = 0; //Deja en limpio la mascara.
    modular = 0; //Espacios que se deben avanzar a nivel de bits.
    
		if (indiceProcesado == 0) // Si hay mas de 8 se necesitan 2 posiciones. Idea! Correr a izquierda y derecha para limpiar espacios necesarios. Con Mascara asignarlos con OR. Quitar los pedazos asignados
		//Hasta que se termine de consumir la cadena. 
		{
				valorActual = *(indiceIteracion); //Primera posición de los 3.
				modular = 8 - accesoSiguientes; //Posiciones que se deben tomar de la cadena de acuerdo de donde se inicia.
				mascara = generarMascara(indiceProcesado, modular, s); //Genera la mascara necesaria!
				valorActual = valorActual >> modular; // Limpia las casilla necesarias para guardar los valores en la mascara.
				valorActual = valorActual << modular;
				valorActual = valorActual | mascara; //Guarda con OR los valores en la mascara del valor actual.
				*(indiceIteracion) = valorActual; //Guarda y reemplaza en el primer byte del char con el resultado listo
				indiceProcesado += modular; //Cuenta lo que se ha procesado de la cadena en esta operacion.
		}
		
		else // Se debe escribir en el siguiente byte
		{
		  valorActual = *(++indiceIteracion); //Obtiene el siguiente byte.
		  
		  if (tamanioCadena - indiceProcesado >= 8) //Aun falta procesar enteramente 8 posiciones. tamanioCadena - indiceProcesado = Lo que falta de la cadena por procesar!
		  {
		    valorActual = generarMascara(indiceProcesado, indiceProcesado + 8, s); // Reemplaza todo el valor con los siguientes 8 digitos binarios.
		    *(indiceIteracion) = valorActual; //Reeemplaza todo el valor en el vector V.
		    indiceProcesado += 8; //Cuenta las 8 casillas que han sido procesadas de la cadena de entrada S.
		  }
		  
		  else // Faltan por procesar menos de 8 posiciones de la cadena.
		  {
		    unsigned char faltante = tamanioCadena - indiceProcesado;
		    valorActual = valorActual << faltante; //Limpia a la izquierda los faltantes.
		    valorActual = valorActual >> faltante;
		    mascara = generarMascara(indiceProcesado, indiceProcesado + faltante, s); //Mascara para los faltantes
		    mascara = mascara << (8 - faltante); //Desplaza a donde es necesaria la mascara.
		    valorActual = valorActual | mascara; //Guarda los valores.
		    *(indiceIteracion) = valorActual; //Guarda en V.
		    indiceProcesado += faltante; //Guarda el numero de elementos procesados de la cadena s en esta operacion.
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

/*
	Permite conocer la longitud de una cadena de caracteres dada.
	@pre Los valores de la cadena de caracteres 1 y 0 deben estar representados en ASCII
	@return Longitud de la cadena.
*/

unsigned char longitud (unsigned char * caracteres)
{
	unsigned char i = 0; //Indice para iterar en la cadena.
	while(caracteres[i])
	{
		i++;
	}
	return i; 
}