#ifndef _FICHEROS_
#define _FICHEROS_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Tipos.h"

int escribir_fichero_tablero(Tablero tab,Jugador jugador,int turno)
/*
En entrada: Un tablero, color del jugador que juega y turno
En salida: una configuración guardad en un fichero de texto
*/
/*Especificaré en el fichero de datos:
 .Celda vacia y con letras las demás piezas
 Además: la cadena "blancas" o "negras"
 y el número de turno*/
{
int i,j;
char car,c;
/*Abrir fichero*/
FILE *tablero;
tablero=fopen("salva.txt","w");


fprintf(tablero,"%s %d",ColorJugador[jugador],turno);
 for(i=8;i>=1;i--)
   {fprintf(tablero,"\n");
   for(j=1;j<=8;j++)
      {
      if(tab[i][j].pieza.clase==vacio)car='.';
      if(tab[i][j].pieza.color==blanca)
          {
          if(tab[i][j].pieza.clase==peon)car='P';
          if(tab[i][j].pieza.clase==caballo)car='C';
          if(tab[i][j].pieza.clase==alfil)car='A';
          if(tab[i][j].pieza.clase==torre)car='T';
          if(tab[i][j].pieza.clase==reina)car='Q';
          if(tab[i][j].pieza.clase==rey)car='R';
          }
      if(tab[i][j].pieza.color==negra)
          {
          if(tab[i][j].pieza.clase==peon)car='p';
          if(tab[i][j].pieza.clase==caballo)car='c';
          if(tab[i][j].pieza.clase==alfil)car='a';
          if(tab[i][j].pieza.clase==torre)car='t';
          if(tab[i][j].pieza.clase==reina)car='q';
          if(tab[i][j].pieza.clase==rey)car='r';
          }
     fprintf(tablero,"%c",car);
     }
  }
/*Cerrar fichero*/
fclose(tablero);
}

/*int leer_fichero_tablero(Tablero tablero) */

#endif
