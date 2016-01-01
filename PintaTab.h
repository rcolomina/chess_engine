#ifndef __PINTATAB__
#define __PINTATAB__

#include <stdio.h>

#include "Tipos.h"

int pintar_tablero(Tablero tablero)
/*Pintamos el tablero segun el estado del 'tablero'*/
{
int i,j;
printf("\n         ");
for(j=1;j<=8;j++)printf("-----");

printf("---");

 for(i=8;i>0;i--)
   {
   printf("\n       %d |",i);
   for(j=1;j<=24;j++)
      {
      if(i%2==0)
       {
        if((j-1)%6==0)printf("  ");
        if((j-3)%6==0)printf("  ");
        if((j-4)%6==0)printf("[ ");
        if((j-0)%6==0)printf(" ]");
        if((j-2)%3==0)
         {if(tablero[i][(j-2)/3+1].pieza.color==blanca)
           printf("%s",TipoPiezasBlancas[tablero[i][(j-2)/3+1].pieza.clase]);
          else
           printf("%s",TipoPiezasNegras[tablero[i][(j-2)/3+1].pieza.clase]);}
       }
      else
        {
        if((j-1+3)%6==0)printf("  ");
        if((j-3+3)%6==0)printf("  ");
        if((j-4+3)%6==0)printf("[ ");
        if((j-0+3)%6==0)printf(" ]");
        if((j-2)%3==0)
          {if(tablero[i][(j-2)/3+1].pieza.color==blanca)
             printf("%s",TipoPiezasBlancas[tablero[i][(j-2)/3+1].pieza.clase]);
           else
             printf("%s",TipoPiezasNegras[tablero[i][(j-2)/3+1].pieza.clase]);
          }
        }
     }
     printf(" | ");
   }
printf("\n         ");for(j=1;j<=8;j++)printf("-----");printf("---");
printf("\n          ");for(j=0;j<8;j++){printf("  %d  ",j+1);
                               /*printf("  %s    ",FilaTablero[j]);*/}
return 0;
}

#endif
