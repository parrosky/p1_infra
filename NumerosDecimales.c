#include "stdlib.h"
#include "stdio.h"
/*
  Autor: Geovanny González. Dada una cadena binaria pasarla a decimal.
*/

int main(int argc, char* argv[])
{
  unsigned char cadena[9]; 
  printf("Digite una cadena con 1 o 0 con 8 posiciones \n");
  scanf("%s", cadena);
  
  // Valor decimal.
  // Depurado.
  int i = 0; //Indice
  printf("Depuracion de la cadena a valores 1 y 0 \n");
  printf("\n");
  
  for (int i = 0; cadena[i]; i++)
  {
    unsigned char valor = *(cadena + i);
    cadena[i] = (valor == '1') ? 1 : 0;
    printf("Posicion: %d\n", i);
    printf ("Valor puesto: %d\n", cadena[i]);
    //i++;
  }
  
  printf("Impresion final \n");
  printf("\n");
  
  // Valores numericos listos:
  unsigned char valorDecimal = 0;
  int g = 0; //Indice.
  while (g < 8) // Se necesita el tamanio !
  {
   valorDecimal = valorDecimal << 1;
   valorDecimal = valorDecimal | cadena[g];
   printf("Valor de la cadena: %d\n", cadena[g]);
   printf("Valor acumulado: %d\n", valorDecimal);
   g++;
  }
  printf("\n");
  printf("El valor en decimal de la cadena es: %d\n", valorDecimal);
}