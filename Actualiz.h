#ifndef _ACTUALIZAR_
#define _ACTUALIZAR_

#include "Tipos.h"
#include "Especial.h"

int actualizar(Tablero tab,Movimiento mov)
/*Genera nuevo estado del tablero despues de la verificacion del
  movimiento por la funcion validar_movimiento a partir del tablero
  y el movimiento*/
{
	  int xini,yini,xfin,yfin,fila;
	  xini=mov.posini.posx;
	  yini=mov.posini.posy;
	  xfin=mov.posfin.posx;
	  yfin=mov.posfin.posy;

/*Cambiar "pieza por pieza"*/
	  tab[xfin][yfin].pieza.clase=tab[xini][yini].pieza.clase;
	  tab[xfin][yfin].pieza.color=tab[xini][yini].pieza.color;
/*Vacia el lugar de procedencia de la pieza*/
	  tab[xini][yini].pieza.clase=vacio;
	  tab[xini][yini].pieza.color=sincolor;

/*Coronar*/
	  if(tab[xfin][yfin].pieza.clase==peon)
	  {
			 if(mov.jugador==blanco && xfin==8)
					tab[xfin][yfin].pieza.clase=reina;
			 if(mov.jugador==negro && xfin==1)
					tab[xfin][yfin].pieza.clase=reina;
	  }

/*Enrrocar si es un movimiento de rey para enrroque*/
	  if(tab[xfin][yfin].pieza.clase==rey && mov_enrroque(mov))
	  {
			 if(mov.jugador==blanco)
					fila=1;
			 else 
					fila=8;

			 if(mov.posfin.posy==3)
					/*actualizar enrroque a izquierda*/
			 { 
					tab[fila][1].pieza.clase=vacio;
					tab[fila][1].pieza.color=sincolor;

					tab[fila][4].pieza.clase=torre;
					tab[fila][4].pieza.color=mov.jugador;
          }
			 else
          {
					tab[fila][8].pieza.clase=vacio;
					tab[fila][8].pieza.color=sincolor;

					tab[fila][6].pieza.clase=torre;
					tab[fila][6].pieza.color=mov.jugador;
          }
	  }
}



int actualizar1(Tablero tab,Variante var)
/*Genera nuevo estado del tablero despues de la verificacion de
la variante por la funcion validar_movimiento a partir del tablero
y el movimiento*/
{
int xini,yini,xfin,yfin,fila;
xini=var.posini.posx;
yini=var.posini.posy;
xfin=var.posfin.posx;
yfin=var.posfin.posy;

/*Cambiar "pieza por pieza"*/
tab[xfin][yfin].pieza.clase=tab[xini][yini].pieza.clase;
tab[xfin][yfin].pieza.color=tab[xini][yini].pieza.color;
/*Vacia el lugar de procedencia de la pieza*/
tab[xini][yini].pieza.clase=vacio;
tab[xini][yini].pieza.color=sincolor;


/*Coronar*/
if(tab[xfin][yfin].pieza.clase==peon)
  {
   if(var.jugador==blanco && xfin==8)
      {tab[xfin][yfin].pieza.clase=reina;
       tab[xfin][yfin].pieza.color=blanca;}
   if(var.jugador==negro && xfin==1)
      {tab[xfin][yfin].pieza.clase=reina;
       tab[xfin][yfin].pieza.color=negra;}
  }


/*Enrrocar si es un movimiento de rey para enrroque*/
if(tab[xfin][yfin].pieza.clase==rey && mov_enrroque1(var))
    {
     if(var.jugador==blanco)fila=1;
     else fila=8;

     if(var.posfin.posy==3)
         /*actualizar enrroque a izquierda*/
         { tab[fila][1].pieza.clase=vacio;
           tab[fila][1].pieza.color=sincolor;
           tab[fila][4].pieza.clase=torre;
           tab[fila][4].pieza.color=var.jugador;
          }
      else
          {tab[fila][8].pieza.clase=vacio;
           tab[fila][8].pieza.color=sincolor;
           tab[fila][6].pieza.clase=torre;
           tab[fila][6].pieza.color=var.jugador;
          }
    }
}

#endif


