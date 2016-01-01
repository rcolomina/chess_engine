#ifndef __BUSQUEDA__
#define __BUSQUEDA__

#include "Evalua.h"

int evalua_variante(Tablero tab,Variante var);
int exp_j_cj(Tablero tab,Variantes var,Jugador jug);
int maxima(Variantes variantes);

int movimiento_variantes(Tablero tab,Variantes variantes,Jugador jugador)
/*
En entrada:El tablero y un vector para guardar las variantes posibles en una jugada
En salida: Devuelve vector variantes que dara los movimientos posibles
           para el jugador y el numero de variantes*/
/*no modifica el tablero*/
{
	  int xini,yini,xfin,yfin,numvar;
	  Movimiento mov_valido;
	  Pieza pieza;
	  mov_valido.jugador=jugador;
	  numvar=0;

/*Buscar todas las posibles jugadas válidas para el jugador descartando
  las imposibles por medio de la funcion validar_movimiento*/
	  for(xini=1;xini<=8;xini++)
			 for(yini=1;yini<=8;yini++)
			 {
					mov_valido.posini.posx=xini;
					mov_valido.posini.posy=yini;
					if(tab[xini][yini].pieza.color==jugador)
						  for(xfin=1;xfin<=8;xfin++)
								 for(yfin=1;yfin<=8;yfin++)
								 {
										if(tab[xfin][yfin].pieza.color==jugador)
											  yfin++;
										mov_valido.posfin.posx=xfin;
										mov_valido.posfin.posy=yfin;
										if(validar_movimiento(tab,mov_valido))
										{
											  variantes[numvar].jugador=jugador;
											  variantes[numvar].posini.posx=xini;
											  variantes[numvar].posini.posy=yini;
											  variantes[numvar].posfin.posx=xfin;
											  variantes[numvar].posfin.posy=yfin;
											  variantes[numvar].piezini.clase=tab[xini][yini].pieza.clase;
											  variantes[numvar].piezini.color=tab[xini][yini].pieza.color;
											  variantes[numvar].piezfin.clase=tab[xfin][yfin].pieza.clase;
											  variantes[numvar].piezfin.color=tab[xfin][yfin].pieza.color;
											  numvar++;
										}
								 }
			 }
	  variantes[numvar].piezini.clase=vacio; /*indica final del vector variantes*/
	  return numvar;
}

int asigna_valor_variantes(Tablero tab,Variantes vars)
/*En entrada: Vector variantes actualizado con la funcion
              movimiento_variantes
  En salida: Vector variantes actualizado su valor por la funcion
             evaluar_variante*/
/*Usa la funcion 'evalua_variante'*/
{
	  int i;
	  i=0;
	  while(i<MAX && vars[i].piezini.clase!=vacio)
	  {
			 vars[i].valor=evalua_variante(tab,vars[i]);
			 i++;
	  }
	  vars[i].piezini.clase=vacio;
}

int numero_variantes_pieza(Pieza pieza,Variantes variantes)
/*En entrada: Clase de pieza y las posibles variantes
  En salida: Variantes de las piezas en concreto y numero de variantes
             Devolviendo 0 si la pieza esta bloqueada*/
{
	  int i,r;
	  r=i=0;
	  while(i<MAX && variantes[i].piezini.clase!=vacio)
     {
			 if(variantes[i].piezini.clase==pieza.clase)
					r++;
			 i++;
	  }
	  return r;
}


int lugar_variante_maximo(Variantes variantes)
/*En entrada: Variantes
  En salida:  Devuelve el lugar del maximo*/
{
	  int i,lug,maximo;
	  i=0;
	  maximo=maxima(variantes);
	  while(i<MAX && variantes[i].piezini.clase!=vacio)
	  {if(variantes[i].valor==maximo)lug=i;
			 i++;
	  }
	  return lug;
}

int maxima(Variantes variantes)
/*En entrada: Variantes
  En salida:  Devuelve el valor maximo de la variante del vector*/
{
	  int i,max;
	  max=variantes[0].valor;
	  i=0;
	  while(i<MAX && variantes[i].piezini.clase!=vacio)
	  {
			 if(variantes[i].valor>=max)
			   max=variantes[i].valor;
			 i++;
	  }
	  return max;
}

int informe_variantes(Variantes variantes)
{
	  int xini,yini,xfin,yfin,i;
	  int marcas[MAX];
	  Pieza pieza;
	  Movimiento mov;
	  mov.jugador=variantes[0].jugador;
	  i=0;
	  while(variantes[i].piezini.clase!=vacio )
	  {xini=variantes[i].posini.posx;
			 yini=variantes[i].posini.posy;
			 xfin=variantes[i].posfin.posx;
			 yfin=variantes[i].posfin.posy;
			 mov.posini.posx=xini;mov.posini.posy=yini;
			 mov.posfin.posx=xfin;mov.posfin.posy=yfin;
			 pieza.clase=variantes[i].piezini.clase;
			 printf("$%d$",i);
			 printf("(%s)",TipoPiezasBlancas[pieza.clase]);
			 printf("(%d)",variantes[i].valor);
			 printf("<%d%d-%d%d>",xini,yini,xfin,yfin);
			 i++;}
	  return 0;
}


int exploracion_basica(Tablero tab,Variantes var,Jugador jug)
/*En entrada: El tablero con la variante y el jugador
  En salida : Devuelve el numero de variante decidida por el
  criterio de la función exp_j_cj*/
{
	  movimiento_variantes(tab,var,jug);
	  asigna_valor_variantes(tab,var);
	  return exp_j_cj(tab,var,jug);
}


int exp_j_cj(Tablero tab,Variantes var,Jugador jug)
/*En entrada: Un tablero, jugador, conjunto de variantes iniciales de jugador
  para el tablero ¡YA! calculadas  con sus valores iniciales
  En salida:  Devuelve el nodo_padre mejor siguiendo el criterio
  jugada, contrajugada con el puntaje de 'evalua'
  no modifica tab ni var.*/
{
	  int i,j,bonus,maximo,nodo_padre,trayec;
	  Tablero tab1;
	  Variantes var1;
	  Jugador jug_contra;
	  if(jug==blanco)
			 jug_contra=negro;
	  else 
			 jug_contra=blanco;
	  maximo=-INFINITO;
/*Examinamos todos los nodos padre*/
	  trayec=0;
	  printf("\nPensando:");
	  while(trayec<MAX && var[trayec].piezini.clase!=vacio )
	  {
			 for(i=0;i<=9;i++)
					for(j=0;j<=9;j++)
						  tab1[i][j]=tab[i][j];/*copia de tab*/

			 bonus=var[trayec].valor;                     /*JUGADOR_BONUS0*/
			 actualizar1(tab1,var[trayec]);

			 movimiento_variantes(tab1,var1,jug_contra);  /*CONTRARIO_VARIANTES1*/
			 asigna_valor_variantes(tab1,var1);

			 bonus=bonus-maxima(var1);                    /*CONTRARIO_BONUS1*/
			 if(maximo<=bonus)
			 {
					maximo=bonus;
					nodo_padre=trayec;
			 }
			 trayec++;
			 printf(".");
	  }
	  return nodo_padre;
}

#endif






