#ifndef __ESPECIAL__
#define __ESPECIAL__

#include "Tipos.h"
#include "Cabfunc.h"

int mov_enrroque1(Variante var)
/*En entrada: Variante con movimiento del rey
  En salida: Devuelve 1 si el movimiento del rey es para enrroque*/
{
if(var.jugador==blanco)
  {if(var.posini.posx==1 && var.posini.posy==5 && var.posfin.posx==1)
    if(var.posfin.posy==3 || var.posfin.posy==7)return 1;}
else
  {if(var.posini.posx==8  && var.posini.posy==5 && var.posfin.posx==8)
    if(var.posfin.posy==3 || var.posfin.posy==7)return 1;}
return 0;
}

int mov_enrroque(Movimiento mov)
/*En entrada: Movimiento con movimiento del rey
  En salida: Devuelve 1 si el movimiento del rey es para enrroque*/
{
	  if(mov.jugador==blanco)
	  {
			 if(mov.posini.posx==1 && mov.posini.posy==5 && mov.posfin.posx==1)
					if(mov.posfin.posy==3 || mov.posfin.posy==7)
						  return 1;
	  }
	  else
	  {
			 if(mov.posini.posx==8  && mov.posini.posy==5 && mov.posfin.posx==8)
					if(mov.posfin.posy==3 || mov.posfin.posy==7)
						  return 1;
	  }
	  return 0;
}

int enrroque(Tablero tab,Movimiento mov)
/*
Se usa la funcion 'movimiento_pieza' en esta funcion y
los tipos definidos por el usuario 'Tablero'
En entrada: Tablero indicando el estado del juego,
            movimiento del rey para enrroque
En salida: Devuelve 1 si el enrroque es posible, 0 en caso contrario*/
/*Hay que examinar que no se cumple al menos una de tres
hay jaque en alguna pieza del enrroque
o bien si torre o rey se han movido
o bien hay una pieza entre rey y torre*/
{
	  int i,fila,xini,yini,xfin,yfin;
	  Movimiento mov1;   /*movimiento del enemigo*/

	  if(mov.jugador==blanco)
	  {
			 mov1.jugador=negro;fila=1;
	  }
	  else
	  {
			 mov1.jugador=blanco;fila=8;
	  }

/*Verificar los token's*/
	  if(mov.jugador==blanco && mov.posfin.posy==3 && token_blancas_enrroque_iz==0)return 0;
	  if(mov.jugador==blanco && mov.posfin.posy==7 && token_blancas_enrroque_id==0)return 0;
	  if(mov.jugador==negro && mov.posfin.posy==3 && token_negras_enrroque_iz==0)return 0;
	  if(mov.jugador==negro && mov.posfin.posy==7 && token_negras_enrroque_id==0)return 0;

/*enrroque a derecha*/
	  if(mov.posfin.posy==7)
	  {
			 /*Ver si hay torre con la que enrrocarse*/
			 if(tab[fila][8].pieza.clase!=torre && tab[fila][1].pieza.color!=mov.jugador)
					return 0;

			 /*ver si hay intermedio vacio*/
			 if(tab[fila][6].pieza.clase!=vacio)return 0;
			 if(tab[fila][7].pieza.clase!=vacio)return 0;

			 /*ver si hay jaque en los lugares por los que pasa el rey para enrrocarse*/
			 tab[fila][6].pieza.clase=rey;tab[fila][6].pieza.color=mov.jugador;
			 tab[fila][7].pieza.clase=rey;tab[fila][7].pieza.color=mov.jugador;
			 for(xini=1;xini<=8;xini++)
					for(yini=1;yini<=8;yini++)
					{
						  mov1.posini.posx=xini;
						  mov1.posini.posy=yini;
						  /*tres casos:por donde pasa el rey*/
						  if(tab[xini][yini].pieza.color==mov1.jugador)
						  {
								 mov1.posfin.posx=fila;
								 mov1.posfin.posy=5;
								 if(movimiento_pieza(tab,mov1))
								 {tab[fila][6].pieza.clase=vacio;tab[fila][6].pieza.color=sincolor;
										tab[fila][7].pieza.clase=vacio;tab[fila][7].pieza.color=sincolor;
										return 0;}
								 mov1.posfin.posy=6;
								 if(movimiento_pieza(tab,mov1))
								 {tab[fila][6].pieza.clase=vacio;tab[fila][6].pieza.color=sincolor;
										tab[fila][7].pieza.clase=vacio;tab[fila][7].pieza.color=sincolor;
										return 0;}
								 mov1.posfin.posy=7;
								 if(movimiento_pieza(tab,mov1))
								 {tab[fila][6].pieza.clase=vacio;tab[fila][6].pieza.color=sincolor;
										tab[fila][7].pieza.clase=vacio;tab[fila][7].pieza.color=sincolor;
										return 0;}
						  }
					}
			 tab[fila][6].pieza.clase=vacio;tab[fila][6].pieza.color=sincolor;
			 tab[fila][7].pieza.clase=vacio;tab[fila][7].pieza.color=sincolor;
			 return 1;
	  }
/*enrroque a izquierda*/
	  else
	  {
			 /*Ver si hay torre con la que enrrocarse*/
			 if(tab[fila][1].pieza.clase!=torre && tab[fila][1].pieza.color!=mov.jugador)
					return 0;

			 /*ver si hay intermedio vacio*/
			 if(tab[fila][2].pieza.clase!=vacio)return 0;
			 if(tab[fila][3].pieza.clase!=vacio)return 0;
			 if(tab[fila][4].pieza.clase!=vacio)return 0;

			 /*ver si hay jaque en los lugares por los que pasa el rey para enrrocarse*/
			 tab[fila][2].pieza.clase=rey;tab[fila][2].pieza.color=mov.jugador;
			 tab[fila][3].pieza.clase=rey;tab[fila][3].pieza.color=mov.jugador;
			 tab[fila][4].pieza.clase=rey;tab[fila][4].pieza.color=mov.jugador;
			 for(xini=1;xini<=8;xini++)
					for(yini=1;yini<=8;yini++)
					{
						  mov1.posini.posx=xini;
						  mov1.posini.posy=yini;
						  /*cuatro casos:por donde pasa el rey*/
						  if(tab[xini][yini].pieza.color==mov1.jugador)
						  {
								 mov1.posfin.posx=fila;
								 mov1.posfin.posy=2;
								 if(movimiento_pieza(tab,mov1))
								 {tab[fila][2].pieza.clase=vacio;tab[fila][2].pieza.color=sincolor;
										tab[fila][3].pieza.clase=vacio;tab[fila][3].pieza.color=sincolor;
										tab[fila][4].pieza.clase=vacio;tab[fila][4].pieza.color=sincolor;
										return 0;
								 }
								 mov1.posfin.posy=3;
								 if(movimiento_pieza(tab,mov1))
								 {
										tab[fila][2].pieza.clase=vacio;tab[fila][2].pieza.color=sincolor;
										tab[fila][3].pieza.clase=vacio;tab[fila][3].pieza.color=sincolor;
										tab[fila][4].pieza.clase=vacio;tab[fila][4].pieza.color=sincolor;
										return 0;
								 }
								 mov1.posfin.posy=4;
								 if(movimiento_pieza(tab,mov1))
								 {
										tab[fila][2].pieza.clase=vacio;tab[fila][2].pieza.color=sincolor;
										tab[fila][3].pieza.clase=vacio;tab[fila][3].pieza.color=sincolor;
										tab[fila][4].pieza.clase=vacio;tab[fila][4].pieza.color=sincolor;
										return 0;}
						  }
					}
			 tab[fila][2].pieza.clase=vacio;tab[fila][2].pieza.color=sincolor;
			 tab[fila][3].pieza.clase=vacio;tab[fila][3].pieza.color=sincolor;
			 tab[fila][4].pieza.clase=vacio;tab[fila][4].pieza.color=sincolor;
			 return 1;
	  }
}

void modificar_token_enrroque(Movimiento mov)
/*En entrada: Un movimiento
  En salida:  Token's externos que permiten el enrroque modificados*/
{
	  if(mov.posini.posx==1)
	  {if(mov.posini.posy==5)  /*rey blanco movido*/
			 {token_blancas_enrroque_iz=0;token_blancas_enrroque_id=0;}

			 if(mov.posini.posy==1) /*torre izd. blanc. movida*/
					token_blancas_enrroque_iz=0;
			 if(mov.posini.posy==8)  /*rey dcha. blanc. movida*/
					token_blancas_enrroque_id=0;
	  }
	  if(mov.posini.posx==8)
	  {
			 if(mov.posini.posy==5)  /*rey negro movido*/
			 {
					token_negras_enrroque_iz=0;token_negras_enrroque_id=0;
			 }

			 if(mov.posini.posx==8 && mov.posini.posy==1)  /*torre izd. negra movida*/
					token_negras_enrroque_iz=0;
			 if(mov.posini.posx==8 && mov.posini.posy==8)  /*rey dcha. negra movida*/
					token_negras_enrroque_id=0;
	  }
}

#endif

