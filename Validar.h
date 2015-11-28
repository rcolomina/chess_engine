#ifndef __VALIDAR__
#define __VALIDAR__

#include "Especial.h"

int validar_movimiento(Tablero tab,Movimiento mov)
/*En entrada: El tablero y un movimento
  En salida : Usando las funciones 'movimiento_pieza','movimiento_rey'
              ,'proteccion_rey','mov_enrroque' y 'enrroque' devuelve 1 si
              el movimiento sigue las reglas del juego ,tambien indica mov.
              invalido en el caso de rey desprotegido*/

{
	  if(mov.posini.posx<=8 && mov.posini.posy<=8)
			 if(tab[mov.posini.posx][mov.posini.posy].pieza.clase==rey)
			 {
					/*Movimiento del rey*/
					if(movimiento_rey(tab,mov))
						  return 1;
					else
					{
						  if(mov_enrroque(mov) && enrroque(tab,mov))
								 return 1;
						  else 
								 return 0;
					}
			 }
			 else
			 {
					
					/*Movimiento distinto de rey*/
					if(movimiento_pieza(tab,mov))
					{
						  if(proteccion_rey(tab,mov))
								 return 1;
						  else 
								 return 0;
					}
					else 
						  return 0;
			 }
	  return 0;
}

#endif


