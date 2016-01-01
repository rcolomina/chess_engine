/**************************  EL JUEGO DE AJEDREZ  *****************************/
/*****************************  Rubén Colomina  *******************************/
/*****************************  Miguel Alvarez  *******************************/
/*************************  Fecha inicio: 6/03/2003  **************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*Indicara 1 si el enrroque es posible*/
int token_blancas_enrroque_iz=1,token_negras_enrroque_iz=1;
int token_blancas_enrroque_id=1,token_negras_enrroque_id=1;

#include "Tipos.h"

/*
int validar_movimiento(Tablero tablero,Movimiento movimiento);
int actualizar(Tablero tablero,Movimiento movimiento);
int lee_pos(Secuencia secuencia,int k);
int imprime_pos(Secuencia secuencia,int k);
int ver_anterior(Secuencia sec_Blancas,Secuencia sec_Negras,int k);
int generar_posicion_inicial(Tablero tablero);
int generar_tablero_antiguo(Tablero tablero2,Secuencia sec_blancas,Secuencia sec_negras,int anterior);
int pintar_tablero(Tablero tablero);
int movimiento_rey(Tablero tablero,Movimiento movimiento);
int movimiento_pieza(Tablero tablero,Movimiento movimiento);
int proteccion_rey(Tablero tablero,Movimiento movimiento);
int jaque_rey(Tablero tablero,Movimiento movimiento);
int jaque_mate(Tablero tablero,Color color_rey);
*/


#include "Actualiz.h"
#include "VerifMov.h"
#include "Jaques.h"
#include "PintaTab.h"
#include "GenInic.h"
#include "Validar.h"
#include "Especial.h"
#include "Evalua.h"
#include "Busqueda.h"
#include "LectEscr.h"
#include "Ficheros.h"

int main()
{
/*Declaración de variables*/
int i,j,n,log,mate,color_jugador,bonus,nodo_padre;
int turno_anterior,turno_actual; /*Indica los turnos*/
int p1,p2;                       /*Clase de jugador*/
float seed;                      /*Semilla de aleatoriedad*/
char car;                        /*Indica opcion en menu*/
Tablero tablero,tablero2;        /*Indica estado del tablero actual y anterior*/
Movimiento mov;                  /*Indica el movimiento en cada jugada*/
Secuencia sec_blancas,sec_negras;/*Guarda jugadas de blancas y negras*/
Variantes variantes,var_max;


/*Genera posicion inicial del tablero*/
generar_posicion_inicial(tablero);

/*Inicializar semilla de aleatoriedad para las aperturas*/
seed=clock();
srand(seed);

/*Inicializar marcador de turno y variables de almacenaje de jugadas*/
turno_actual=0;
for(j=0;j<MAX;j++)
  {
  sec_blancas[j].posini.posx=0;sec_negras[j].posini.posx=0;
  sec_blancas[j].posini.posy=0;sec_negras[j].posini.posy=0;
  sec_blancas[j].posfin.posx=0;sec_negras[j].posfin.posx=0;
  sec_blancas[j].posfin.posy=0;sec_negras[j].posfin.posy=0;
  }



/*Secuencia principal*/
do{printf("\n-------------------------------------------------------------");

   /*Inicio del juego*/
    if(turno_actual==0){
       printf("\n********************EL JUEGO DEL AJEDREZ***********************");
       printf("\nElige jugadores:\n");
       printf("\nBlancas: (1) Humano  (2) Ordenador:");scanf("%d",&p1);
       printf("\nNegras : (1) Humano  (2) Ordenador:");scanf("%d",&p2);
                       }

    /*Juegan las blancas*/
    printf("\nINICIO TURNO (%d)",turno_actual);
    printf("\n//////////////////Juegan Blancas//////////////////");
    pintar_tablero(tablero);

    if(p1==2)
        {
        if(turno_actual==0)
           {/*elegir al azar una apertura para el ordenador*/
            movimiento_variantes(tablero,variantes,blanco);
            if(rand()%2)
					  nodo_padre=(2*(rand()%2))+11;
            else 
					  nodo_padre=((rand()%2))+1;
            }
        else
				 nodo_padre=exploracion_basica(tablero,variantes,blanco);
        /*Asignar jugada decidida por el ordenador*/
        sec_blancas[turno_actual].posini.posx=variantes[nodo_padre].posini.posx;
        sec_blancas[turno_actual].posini.posy=variantes[nodo_padre].posini.posy;
        sec_blancas[turno_actual].posfin.posx=variantes[nodo_padre].posfin.posx;
        sec_blancas[turno_actual].posfin.posy=variantes[nodo_padre].posfin.posy;
        }

    do{
        /*Lee y guarda jugada en secuencia de blancas*/
        if(p1==1)
				 lee_pos(sec_blancas,turno_actual);

        /*Actualizar variable mov */
        mov.posini.posx=sec_blancas[turno_actual].posini.posx;
        mov.posini.posy=sec_blancas[turno_actual].posini.posy;
        mov.posfin.posx=sec_blancas[turno_actual].posfin.posx;
        mov.posfin.posy=sec_blancas[turno_actual].posfin.posy;
        mov.jugador=blanco;

        /*Validar el movimiento*/
        if(validar_movimiento(tablero,mov))
				 log=1;
        else 
				 log=0;

        if(log==0)
              {
              /*Informar sobre movimiento imposible*/
              printf("\nMovimiento invalido");
              printf("--Intentalo de nuevo");
              printf("\n//////////////////Juegan Blancas//////////////////");
              pintar_tablero(tablero);
              }
        else
              {
              /*Ver si hay jaque con tal movimiento*/
              if(jaque_rey(tablero,mov))
                  {
                   actualizar(tablero,mov);
                   pintar_tablero(tablero);
                   printf("\nJAQUE AL REY NEGRO!!!");
                   mate=jaque_mate(tablero,negro);
						}
              else
                   actualizar(tablero,mov);
              break;
              }
     }while(log==0);

   /*Modificar token's para los posibles enrroques*/
   if(mov_enrroque(mov))
		  modificar_token_enrroque(mov);

  /*Ver si hay jaque mate ,terminar juego*/
   if(mate==1)
	{
		  printf("\nJAQUE MATE!!! -  GANAN BLANCAS");
		  pintar_tablero(tablero);
		  escribir_fichero_tablero(tablero,blanco,turno_actual);
		  getchar();
		  getchar();
	 }
    if(mate==1)
			break;

    /*Juegan las negras*/
    printf("\n\n///////////////Juegan Negras/////////////////");
    pintar_tablero(tablero);

    /*Asignar jugada decidida por el ordenador*/
	 if(p2==2)
	 {
			if(turno_actual==0)
			{/*Elegir apertura para el ordenador*/
				  movimiento_variantes(tablero,variantes,negro);
				  if(tablero[4][4].pieza.clase==peon)
						 nodo_padre=6;
				  else if(tablero[4][5].pieza.clase==peon)
						 nodo_padre=8; /*abiertas*/
				  else 
						 nodo_padre=exploracion_basica(tablero,variantes,negro);
			}
			else
				  nodo_padre=exploracion_basica(tablero,variantes,negro);

			sec_negras[turno_actual].posini.posx=variantes[nodo_padre].posini.posx;
			sec_negras[turno_actual].posini.posy=variantes[nodo_padre].posini.posy;
			sec_negras[turno_actual].posfin.posx=variantes[nodo_padre].posfin.posx;
			sec_negras[turno_actual].posfin.posy=variantes[nodo_padre].posfin.posy;
	 }

    do{
        /*Lee y guarda jugada*/
        if(p2==1)
				 lee_pos(sec_negras,turno_actual);

        /*Actualizar movimiento*/
        mov.posini.posx=sec_negras[turno_actual].posini.posx;
        mov.posini.posy=sec_negras[turno_actual].posini.posy;
        mov.posfin.posx=sec_negras[turno_actual].posfin.posx;
        mov.posfin.posy=sec_negras[turno_actual].posfin.posy;
        mov.jugador=negro;

        if(validar_movimiento(tablero,mov))
				 log=1;
        else 
				 log=0;
        if(log==0)
                {
                /*Informar sobre movimiento imposible*/
                printf("\nMovimiento invalido");
                printf("--Intentalo de nuevo");
                printf("\n/////////////////Juegan Negras/////////////////");
                pintar_tablero(tablero);}
        else
                {
                /*Ver si hay jaque con tal movimiento*/
                if(jaque_rey(tablero,mov))
					 {
							actualizar(tablero,mov);
							pintar_tablero(tablero);
							printf("\nJAQUE AL REY BLANCO!!!");
							mate=jaque_mate(tablero,blanco); 
					 }
                else
							actualizar(tablero,mov);
                break;
                }
     }while(log==0);

  /*Modificar token's para los posibles enrroques*/
  if(mov_enrroque(mov))
		 modificar_token_enrroque(mov);

  /*Ver si hay jaque mate*/
  if(mate==1)
  {
		 printf("\nJAQUE MATE!!! -  GANAN NEGRAS");
		 pintar_tablero(tablero);
		 escribir_fichero_tablero(tablero,negro,turno_actual);
		 getchar();getchar();
  }

  if(mate==1)
		 break;

  /*MENU PRINCIPAL*/
   pintar_tablero(tablero);
   printf("\n\nJUEGO EN TURNO %d",turno_actual);
   printf("\n\n---------------------------------------------");
   printf("\n\n*********************MENU DE JUEGO****************************");
   printf("\n-----------------------Nueva partida-----------------Pulsa (n)");
   printf("\n---------------------Ver turno anterior--------------Pulsa (v)");
   printf("\n---------------------Salvar partida------------------Pulsa (w)");
   printf("\n--------------------Salir del programa---------------Pulsa (q)");
   printf("\n----------------------Turno siguiente----------------Pulsa (s)\n");
   car=getchar();car=getchar();

	if(car=='v' || car=='V')
   {
		  printf("\nDame el turno anterior:(menor que %d)",turno_actual);scanf("%d",&turno_anterior);
		  printf("\nQue jugador quieres? Blanco(0) o Negro(1):");scanf("%d",&color_jugador);
		  printf("\n<<ESTADO DEL TABLERO TRAS EL TURNO (%d) PARA JUGADOR %s >>",turno_anterior,ColorJugador[color_jugador]);
		  generar_tablero_antiguo(tablero2,sec_blancas,sec_negras,color_jugador,turno_anterior);
		  pintar_tablero(tablero2);
		  getchar();getchar();
   }
	if(car=='w' || car=='W')
   {
		  printf("\nGuarda turno:(menor o igual que %d)",turno_actual);scanf("%d",&turno_anterior);
		  printf("\nDel jugador: Blanco(0) o Negro(1):");scanf("%d",&color_jugador);
		  generar_tablero_antiguo(tablero2,sec_blancas,sec_negras,color_jugador,turno_anterior);
		  escribir_fichero_tablero(tablero2,color_jugador,turno_anterior);
		  printf("\nFICHERO GUARDADO");
   }
	if(car=='n' || car=='N')
	{
		  turno_actual=-1;
		  generar_posicion_inicial(tablero);
	}
	
	if(car=='q' || car=='Q')
		  break;
	/*Pasar al turno siguiente*/
	turno_actual++;

}while(car!='q' && car!='Q');


 return 0;
 
}

