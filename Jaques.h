#ifndef __JAQUES__
#define __JAQUES__

#include "Tipos.h"

int jaque_rey(Tablero tablero,Movimiento movimiento)
/*En entrada: Movimento ya validado por las funciones movimiento_pieza
  y proteccion_rey
  En salida:  Devuelve 1 si el REY del color contrario al del movimiento
  queda en jaque*/
{
	  int xini,yini,xfin,yfin,xrey,yrey,i,j;
	  int xini_jaque,yini_jaque;
	  int conta_jaque;
	  Pieza pieza,piezafinal;
	  Movimiento mov_jaque;

/*Asigno posicion de la casilla de salida
  y posicion de la casilla de llegada de la pieza que se va a mover*/
	  xini=movimiento.posini.posx;
	  yini=movimiento.posini.posy;
	  xfin=movimiento.posfin.posx;
	  yfin=movimiento.posfin.posy;

/*Busco posicion del REY del color contrario al del movimiento*/
	  for(i=1;i<=8;i++)
			 for(j=1;j<=8;j++)
					if(tablero[i][j].pieza.clase==rey)
						  if(tablero[i][j].pieza.color!=movimiento.jugador)
						  {xrey=i;yrey=j;
								 i=9;j=9;}

/*Asigno lugar del rey para el final del movimiento de una pieza del color
  del movimiento que pueda hacer un posible jaque al rey del color contrario*/
	  mov_jaque.posfin.posx=xrey;
	  mov_jaque.posfin.posy=yrey;

/*Guardo la pieza movida y la posible pieza comida*/
	  pieza.clase=tablero[xini][yini].pieza.clase;
	  pieza.color=tablero[xini][yini].pieza.color;
	  piezafinal.clase=tablero[xfin][yfin].pieza.clase;
	  piezafinal.color=tablero[xfin][yfin].pieza.color;

/*Quito la pieza movida de su casilla de salida segun fue
  asignado anteriormente debido al argumento de entrada 'movimiento'*/
	  tablero[xini][yini].pieza.clase=vacio;
	  tablero[xini][yini].pieza.color=sincolor;
	  tablero[xfin][yfin].pieza.clase=pieza.clase;
	  tablero[xfin][yfin].pieza.color=pieza.color;

/*Asignar el color del movimiento a la pieza que pueda hacer jaque al rey
  del color opuesto*/
	  mov_jaque.jugador=movimiento.jugador;

/*Verifico si existe jaque tras el movimiento incrementando el contador
  conta_jaque en caso afirmativo, dejandolo a 0 si no existe el jaque*/
	  conta_jaque=0;
	  for(xini_jaque=1;xini_jaque<9;xini_jaque++)
			 for(yini_jaque=1;yini_jaque<9;yini_jaque++)
			 {
					mov_jaque.posini.posx=xini_jaque;
					mov_jaque.posini.posy=yini_jaque;
					if(tablero[xini_jaque][yini_jaque].pieza.clase!=vacio)
						  if(tablero[xini_jaque][yini_jaque].pieza.color==mov_jaque.jugador)
								 if(tablero[xini_jaque][yini_jaque].pieza.clase!=rey)
										if(movimiento_pieza(tablero,mov_jaque))
											  conta_jaque++;
			 }

/*Volver a colocar las piezas en la casilla de inicio y de llegada del
  movimiento */
	  tablero[xini][yini].pieza.clase=pieza.clase;
	  tablero[xini][yini].pieza.color=pieza.color;
	  tablero[xfin][yfin].pieza.clase=piezafinal.clase;
	  tablero[xfin][yfin].pieza.color=piezafinal.color;

/*Devolver 1 si hay jaque*/
	  if(conta_jaque>=1)
			 return 1;
	  else 
			 return 0;
}


int jaque_mate(Tablero tablero,Color color_rey)
/*En entrada un tablero mas el color del rey en jaque
  (a).Miro si el rey puede moverse a su entorno, es decir, si la funcion
  movimiento_rey devuelve 1 para alguna de las celdas del entorno
  (b).Miro si el rey en el tablero puede protegerse del jaque, es decir,
  si la funcion proteccion_rey devuelve 1 para alguna movimiento de
  alguna pieza del color del rey distinta de rey
  En salida:En caso de que escape o protec_rey fueran >0 entonces que
  jaque_mate devuelva 0*/
{
	  int escape;
	  int protec_rey;
	  int i,j;
	  int xrey,yrey;
	  int xini_protec,yini_protec,xfin_protec,yfin_protec;
	  Movimiento mov_rey,mov_protec;

	  escape=protec_rey=0;
/*Busco la posicion del REY del color_rey*/
	  for(i=1;i<=8;i++)
			 for(j=1;j<=8;j++)
					if(tablero[i][j].pieza.clase==rey)
						  if(tablero[i][j].pieza.color==color_rey)
						  {xrey=i;yrey=j;
								 i=9;j=9;}


/*(a).Miro si el rey puede moverse a su entorno, es decir, si la funcion
  movimiento_rey devuelve 1 para alguna de las celdas del entorno*/

	  mov_rey.posini.posx=xrey;
	  mov_rey.posini.posy=yrey;
	  mov_rey.jugador=color_rey;

/*Ocho posibilidades de movimiento para el rey*/
	  mov_rey.posfin.posx=xrey+1;
	  mov_rey.posfin.posy=yrey+1;
	  if(movimiento_rey(tablero,mov_rey))
			 escape++;
	  mov_rey.posfin.posx=xrey+1;
	  mov_rey.posfin.posy=yrey-1;
	  if(movimiento_rey(tablero,mov_rey))
			 escape++;
	  mov_rey.posfin.posx=xrey-1;
	  mov_rey.posfin.posy=yrey+1;
	  if(movimiento_rey(tablero,mov_rey))
			 escape++;
	  mov_rey.posfin.posx=xrey-1;
	  mov_rey.posfin.posy=yrey-1;
	  if(movimiento_rey(tablero,mov_rey))
			 escape++;
	  mov_rey.posfin.posx=xrey+1;
	  mov_rey.posfin.posy=yrey;
	  if(movimiento_rey(tablero,mov_rey))
			 escape++;
	  mov_rey.posfin.posx=xrey-1;
	  mov_rey.posfin.posy=yrey;
	  if(movimiento_rey(tablero,mov_rey))
			 escape++;
	  mov_rey.posfin.posx=xrey;
	  mov_rey.posfin.posy=yrey+1;
	  if(movimiento_rey(tablero,mov_rey))
			 escape++;
	  mov_rey.posfin.posx=xrey;
	  mov_rey.posfin.posy=yrey-1;
	  if(movimiento_rey(tablero,mov_rey))
			 escape++;

/*(b).Miro si el rey en el tablero puede protegerse del jaque, es decir,
  si la funcion proteccion_rey devuelve 1 para alguna movimiento de
  alguna pieza del color del rey distinta de rey*/

	  mov_protec.jugador=color_rey;

	  for(xini_protec=1;xini_protec<=8;xini_protec++)
			 for(yini_protec=1;yini_protec<=8;yini_protec++)
			 {
					if(tablero[xini_protec][yini_protec].pieza.clase!=vacio)
						  if(tablero[xini_protec][yini_protec].pieza.color==color_rey)
						  {
								 mov_protec.posini.posx=xini_protec;
								 mov_protec.posini.posy=yini_protec;
								 for(xfin_protec=1;xfin_protec<9;xfin_protec++)
										for(yfin_protec=1;yfin_protec<9;yfin_protec++)
										{
											  if(tablero[xfin_protec][yfin_protec].pieza.color!=color_rey)
											  {mov_protec.posfin.posx=xfin_protec;
													 mov_protec.posfin.posy=yfin_protec;
													 if(movimiento_pieza(tablero,mov_protec))/*validar movimiento*/
															if(proteccion_rey(tablero,mov_protec))protec_rey++;
											  }
										}
						  }
			 }
	  if(escape==0 && protec_rey==0)return 1; /*JAQUE MATE*/
	  else return 0;
}


#endif
