#ifndef __EVALUA__
#define __EVALUA__


#include "Tipos.h"
#include "Busqueda.h"

int lugar_variante_maximo(Variantes variantes);
int material_piezas_jugador(Tablero tab,Jugador jugador);
int mov_enrroque(Movimiento mov);
int jaque_rey(Tablero tablero,Movimiento movimiento);


int evalua_variante(Tablero tab,Variante var)
/*En entrada: Tablero,movimiento y una variante.
  En salida:  Devuelve un entero dando una idea de la "bondad" de este
              movimiento
  100 por cada peon
  315 por cada caballo
  330 por cada alfil
  500 por cada torre
  940 por cada reina
  1 punto por cada casilla a la que se puedan mover los alfiles
  1 punto por cada casilla a la que se puedan mover las torres
  De -20 hasta 15 gradualmente por la posición de cada caballo
  (desde un rincon del tablero hasta el centro)
  De -4 a 4 gradualmente por la posicion de la dama desde un rincon
  hasta el centro
  -10 por peon doblado
  -15 por peon aislado
  bonus gradual para la posicion del rey, en la apertura mientras más cerca
  del centro es más malo y en los finales de partida (poco material) al revés.
  50 por un jaque
  80 por enrrocar

Funciones usadas: jaque_rey, jaque_mate, actualizar,movimiento_variantes,
                  numero_variantes_pieza, material_piezas_jugador*/
{
int i,valor_variante,numvar,jaque;
int xini,yini,xfin,yfin;
Variantes variantes;
Pieza piezaini,piezafin,pieza;
Jugador jugador,jug_contra;
Movimiento mov;

/*asinar valor inicial a la variante*/
valor_variante=0;
xini=mov.posini.posx=var.posini.posx;
yini=mov.posini.posy=var.posini.posy;
xfin=mov.posfin.posx=var.posfin.posx;
yfin=mov.posfin.posy=var.posfin.posy;
jugador=var.jugador;
mov.jugador=var.jugador;


/*Guardar la pieza en poscion de salida*/
piezaini.color=tab[xini][yini].pieza.color;
piezaini.clase=tab[xini][yini].pieza.clase;

/*Guardar la pieza existente en posicion de llegada*/
piezafin.color=tab[xfin][yfin].pieza.color;
piezafin.clase=tab[xfin][yfin].pieza.clase;

if(jugador==blanco)jug_contra=negro;
else jug_contra=blanco;

/*Ver si movimiento es de enrroque*/
if(mov_enrroque(mov))return 80;

/*Bonus positivo para la variante que llega a hacer jaque*/
if(jaque_rey(tab,mov))
   {valor_variante=valor_variante+20;
   jaque=1;}

/*Actualizar tab con mov*/
actualizar(tab,mov);

/*Bonus de jaque mate,  requiere de tablero actualizado con rey en jaque*/
if(jaque==1 && jaque_mate(tab,jug_contra))
     {tab[xini][yini].pieza.color=piezaini.color;
      tab[xini][yini].pieza.clase=piezaini.clase;
      tab[xfin][yfin].pieza.color=piezafin.color;
      tab[xfin][yfin].pieza.clase=piezafin.clase;
      return INFINITO;}

/*Bonus por pieza comida*/
if(piezafin.clase==peon)valor_variante=valor_variante+100;
if(piezafin.clase==caballo)valor_variante=valor_variante+315;
if(piezafin.clase==alfil)valor_variante=valor_variante+330;
if(piezafin.clase==torre)valor_variante=valor_variante+500;
if(piezafin.clase==reina)valor_variante=valor_variante+940;

/*Bonus por casillas a las que pueden mover los alfiles*/
numvar=movimiento_variantes(tab,variantes,jugador);
pieza.clase=alfil;
valor_variante=valor_variante+numero_variantes_pieza(pieza,variantes);
/*Bonus por casillas a las que pueden mover las torres*/
pieza.clase=torre;
valor_variante=valor_variante+numero_variantes_pieza(pieza,variantes);



/*Bonus positivo por coronar*/
if(piezaini.clase==peon)
   if(jugador==blanco)
       if(xfin==8)valor_variante=valor_variante+940;
   else
       if(xfin==1)valor_variante=valor_variante+940;

/*Bonus positivo por tener un peón en el centro*/
if(piezaini.clase==peon)
 if(xfin==4 && yfin==4 || xfin==4 && yfin==5 || xfin==5 && yfin==4 || xfin==5 && yfin==5)
      valor_variante=valor_variante+12;


/*Bonus negativo por peon doblado*/
if(piezaini.clase==peon)
   for(i=1;i<=8;i++)/*examinar columna del peon*/
     if(xfin!=i && tab[i][yfin].pieza.clase==peon && tab[i][yfin].pieza.color==jugador)
         valor_variante=valor_variante-10;

/*Bonus negativo por peon aislado*/
i=0;
if(piezaini.clase==peon)
   {
   if(tab[xfin][yfin+1].pieza.clase==vacio)i++;
   else if(tab[xfin][yfin+1].pieza.color==jugador)i++;
   if(tab[xfin+1][yfin+1].pieza.clase==vacio)i++;
   else if(tab[xfin+1][yfin+1].pieza.color!=jugador)i++;
   if(tab[xfin+1][yfin].pieza.clase==vacio)i++;
   else if(tab[xfin+1][yfin].pieza.color!=jugador)i++;
   if(tab[xfin+1][yfin-1].pieza.clase==vacio)i++;
   else if(tab[xfin+1][yfin-1].pieza.color!=jugador)i++;
   if(tab[xfin][yfin-1].pieza.clase==vacio)i++;
   else if(tab[xfin][yfin-1].pieza.color!=jugador)i++;
   if(tab[xfin-1][yfin-1].pieza.clase==vacio)i++;
   else if(tab[xfin-1][yfin-1].pieza.color!=jugador)i++;
   if(tab[xfin-1][yfin].pieza.clase==vacio)i++;
   else if(tab[xfin-1][yfin].pieza.color!=jugador)i++;
   if(tab[xfin-1][yfin+1].pieza.clase==vacio)i++;
   else if(tab[xfin-1][yfin+1].pieza.color!=jugador)i++;
   if(i==8)valor_variante=valor_variante-15;
   }

/*Bonus de la posicion de la reina*/
if(piezaini.clase==reina)
{if(4<=xfin && xfin<=5 && 4<=yfin && yfin<=5)
     valor_variante=valor_variante+4;
else if(3<=xfin && xfin<=6 && 3<=yfin && yfin<=6)
          valor_variante=valor_variante+2;
     else if(2<=xfin && xfin<=7 && 2<=yfin && yfin<=7)
               valor_variante=valor_variante-2;
          else valor_variante=valor_variante-4;}


/*Bonus para el caballo*/
if(piezaini.clase==caballo)
{if(4<=xfin && xfin<=5 && 4<=yfin && yfin<=5)
     valor_variante=valor_variante+15;
else if(3<=xfin && xfin<=6 && 3<=yfin && yfin<=6)
          valor_variante=valor_variante+5;
     else if(2<=xfin && xfin<=7 && 2<=yfin && yfin<=7)
               valor_variante=valor_variante-5;
          else valor_variante=valor_variante-15;}

/*Bonus del rey*/
/*Caso de material mayor 2000*/
if(piezaini.clase==rey)
 if(material_piezas_jugador(tab,jugador)>2000)
  {if(4<=xfin && xfin<=5 && 4<=yfin && yfin<=5)
     valor_variante=valor_variante-8;
   else if(3<=xfin && xfin<=6 && 3<=yfin && yfin<=6)
          valor_variante=valor_variante-5;
     else if(2<=xfin && xfin<=7 && 2<=yfin && yfin<=7)
               valor_variante=valor_variante-3;
   }
 else
    {if(4<=xfin && xfin<=5 && 4<=yfin && yfin<=5)
     valor_variante=valor_variante+8;
     else if(3<=xfin && xfin<=6 && 3<=yfin && yfin<=6)
          valor_variante=valor_variante+5;
     else if(2<=xfin && xfin<=7 && 2<=yfin && yfin<=7)
               valor_variante=valor_variante+3;
    }


/*Restaurar el tablero*/
tab[xini][yini].pieza.color=piezaini.color;
tab[xini][yini].pieza.clase=piezaini.clase;
tab[xfin][yfin].pieza.color=piezafin.color;
tab[xfin][yfin].pieza.clase=piezafin.clase;

return valor_variante;
}


int material_piezas_jugador(Tablero tab,Jugador jugador)
/*En entrada: El tablero y el jugador
En salida:  Vector material indicando el numero de piezas de cada clase
del tablero del color del jugador*/
/*Explorar el tablero e ir colocando cada pieza en su lugar correspondiente
añadiendo uno.Lugar [0] peon, [1] caballo, [2] alfil,[3] torre,[4],
valor del vector segun el operador* siguiente*/
/*En un inicio de partida los vectores seran de la forma (8,2,2,2,1)
Un jugador tendrá VENTAJA DE MATERIAL, cuando el operador* |()| del vector
de piezas sea superior al de su contrincante
operador*:  |(x1,x2,x3,x4,x5)|=x1*100+x2*315+x3*330+x4*500+x5*940
donde x1 varia 0-8, x2,x3,x4 varia entre 0-2 y x5 entre 0-1
Devolviendo operador* al vector y colocar ese número en
la posición piezas[5] del vector piezas*/
{
int i,j;
int material[6];
for(i=0;i<=5;i++)material[i]=0;
for(i=1;i<=8;i++)
   for(j=1;j<=8;j++)
       if(tab[i][j].pieza.clase!=vacio)
         if(tab[i][j].pieza.color==jugador)
           {
           if(tab[i][j].pieza.clase==peon)material[0]++;
           if(tab[i][j].pieza.clase==caballo)material[1]++;
           if(tab[i][j].pieza.clase==alfil)material[2]++;
           if(tab[i][j].pieza.clase==torre)material[3]++;
           if(tab[i][j].pieza.clase==reina)material[4]++;
           }
material[5]=material[0]*100+material[1]*315+material[2]*330+material[3]*500+material[4]*940;
return material[5];
}

#endif


