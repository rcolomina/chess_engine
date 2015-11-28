#ifndef __TIPOS__
#define __TIPOS__

#define MAX 150
#define NUM 10
#define INFINITO 50000

typedef enum{vacio,peon,caballo,alfil,torre,reina,rey}TipoPieza;
char *ClasePieza[]={"VACIO","PEON","CABALLO","ALFIL","TORRE","REINA","REY"};
char *TipoPiezasBlancas[]={" ","P","C","A","T","Q","R"};
char *TipoPiezasNegras[]={" ","p","c","a","t","q","r"};

typedef enum{blanca,negra,sincolor}Color;
char *ColorPieza[]={"BLANCA","NEGRA","SINCOLOR"};

typedef enum{blanco,negro}Jugador;
char *ColorJugador[]={"BLANCO","NEGRO"};

typedef enum{A,B,C,D,E,F,G,H}Fila;
char *FilaTablero[]={"A","B","C","D","E","F","G","H"};

typedef struct {
        int posx; /*Marca las filas*/
        int posy; /*Marca las columnas*/
        }Posicion;

typedef struct {
        Color color;                 /*Caracteristicas de una pieza*/
        TipoPieza clase;
        Posicion pos;
        }Pieza;

typedef struct{
        Posicion posini;         /*Caracterizacion de un movimiento*/
        Posicion posfin;
        Jugador jugador;      /*Color de las piezas del jugador que mueve*/
        }Movimiento;

typedef struct{
        Pieza pieza;               /*Caracteristicas de una celda*/
        Color color;
        }Celda;

typedef struct{
        Posicion posini;
        Posicion posfin;
        Pieza piezini;
        Pieza piezfin;
        Jugador jugador;
        int valor;
        }Variante;

typedef Celda Tablero[NUM][NUM];   /*Array bidimensional de celdas*/
typedef Movimiento Secuencia[MAX]; /*Array unidim. de movimientos*/
typedef Variante Variantes[MAX];   /*Array unidim. de variantes*/

#endif
