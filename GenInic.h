#ifndef __GENINIC__
#define __GENINIC__

#include "Tipos.h"

int generar_posicion_inicial(Tablero tablero)
/*
  En entrada:Un 'tablero'
  En salida: Devuelve 'tablero' con la posicion inicial del juego*/
{
	  int i,j;
/*Vaciar de fichas y pintar el tablero con los cuadros blancos y negros*/
	  for(i=0;i<=9;i++)
			 for(j=0;j<=9;j++)
			 {tablero[i][j].pieza.clase=vacio;
					tablero[i][j].pieza.color=sincolor;
					if((i+j)%2==0)tablero[i][j].color=negra;
					else tablero[i][j].color=blanca;
			 }
/*Pintar color de las piezas*/
	  for(i=1;i<=2;i++)
			 for(j=1;j<=8;j++)
					tablero[i][j].pieza.color=blanca;
	  for(i=7;i<=8;i++)
			 for(j=1;j<=8;j++)
					tablero[i][j].pieza.color=negra;

/*Rellenar peones*/
	  for(j=1;j<=8;j++)
	  {
			 tablero[7][j].pieza.clase=peon;
			 tablero[2][j].pieza.clase=peon;
	  }
/*Rellenar caballos*/
	  tablero[1][2].pieza.clase=caballo;
	  tablero[1][7].pieza.clase=caballo;
	  tablero[8][2].pieza.clase=caballo;
	  tablero[8][7].pieza.clase=caballo;
/*Rellanar alfiles*/
	  tablero[1][3].pieza.clase=alfil;
	  tablero[1][6].pieza.clase=alfil;
	  tablero[8][3].pieza.clase=alfil;
	  tablero[8][6].pieza.clase=alfil;
/*Rellanar torres*/
	  tablero[1][1].pieza.clase=torre;
	  tablero[1][8].pieza.clase=torre;
	  tablero[8][1].pieza.clase=torre;
	  tablero[8][8].pieza.clase=torre;
/*Rellanar reinas y reyes*/
	  tablero[1][4].pieza.clase=reina;
	  tablero[1][5].pieza.clase=rey;
	  tablero[8][4].pieza.clase=reina;
	  tablero[8][5].pieza.clase=rey;
	  return 0;
}

int generar_tablero_antiguo(Tablero tablero2,Secuencia sec_blancas,Secuencia sec_negras,Color color_jugador,int anterior)
/*Entrada: Un 'tablero' que representara la jugada anterior, se dan los
vectores de movimiento 'sec_blancas' y 'sec_negras' , y el color del jugador
que acaba de mover.

Salida: El 'tablero' actualizado con los movimientos hasta la jugada
que marque las secuencias almacenadas hasta la jugada 'anterior' */
{
	  int i;
	  generar_posicion_inicial(tablero2);
	  for(i=0;i<=anterior;i++)
     {
			 if(i==anterior && color_jugador==blanco)
					actualizar(tablero2,sec_blancas[i]);
			 else
			 {actualizar(tablero2,sec_blancas[i]);
					actualizar(tablero2,sec_negras[i]);}
     }
	  return 0;
}

#endif

