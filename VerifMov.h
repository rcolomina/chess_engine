#ifndef __AJEDREZ__
#define __AJEDREZ__

int movimiento_rey(Tablero tablero,Movimiento movimiento)
/*
  En entrada: Tablero y un movimiento de rey
  En salida: Devuelve si es válido tal movimiento

  Verifica si el movimiento de rey es válido
  devolviendo 1 si es posible*/
/*Usa funcion 'movimiento_pieza' y 'enrroque'*/
{
	  int xini,yini,xfin,yfin,i,r;
	  int xini_jaque,yini_jaque;
	  int conta_jaque;
	  Pieza pieza;
	  Color color;
	  Movimiento mov_jaque;

/*Coordenadas de llegada y salida del movimiento a realizar*/
	  xini=movimiento.posini.posx;
	  yini=movimiento.posini.posy;
	  xfin=movimiento.posfin.posx;
	  yfin=movimiento.posfin.posy;

/*Verificar limites de definicion*/
	  if(xini<1 || xini>8 || yini<0 || yini>8)return 0;
	  if(xfin<1 || xfin>8 || yfin<0 || yfin>8)return 0;

/*Impedir mover a la misma posicion*/
	  if(xini==xfin && yini==yfin)return 0;

/*Verificar si hay pieza en la posicion de inicio*/
	  if(tablero[xini][yini].pieza.clase==vacio)return 0;

/*Verificar que se va a mover una pieza del color del jugador*/
	  if(tablero[xini][yini].pieza.color!=movimiento.jugador)return 0;

/*Verificar no mover a lugar que ocupe una pieza del mismo jugador que mueve*/
	  if(tablero[xfin][yfin].pieza.color==movimiento.jugador)return 0;



/*Iniciar a cero el contador de jaques en el lugar de llegada*/
	  conta_jaque=0;

/*Guardar pieza que haya en posicion de llegada, quitar rey de casilla
  de salida y colocar el rey del color del movimiento en casilla de llegada*/
	  tablero[xini][yini].pieza.clase=vacio;
	  pieza.color=tablero[xfin][yfin].pieza.color;
	  pieza.clase=tablero[xfin][yfin].pieza.clase;
	  tablero[xfin][yfin].pieza.color=movimiento.jugador;
	  tablero[xfin][yfin].pieza.clase=rey;

/*Ver si existe peon que pueda comerse al rey en posicion de llegada*/
	  if(movimiento.jugador==blanco)
	  {
			 if(tablero[xfin+1][yfin+1].pieza.color==negra)
					if(tablero[xfin+1][yfin+1].pieza.clase==peon)
						  conta_jaque++;
			 if(tablero[xfin+1][yfin-1].pieza.color==negra)
					if(tablero[xfin+1][yfin-1].pieza.clase==peon)
						  conta_jaque++;
	  }
	  else
	  {
			 if(tablero[xfin-1][yfin+1].pieza.color==blanca)
					if(tablero[xfin-1][yfin+1].pieza.clase==peon)conta_jaque++;
			 if(tablero[xfin-1][yfin-1].pieza.color==blanca)
					if(tablero[xfin-1][yfin-1].pieza.clase==peon)conta_jaque++;
	  }

/*Verificar si existe rey contrario en un entorno de 1 de la posicion final*/
	  r=0;
	  if(tablero[xfin+1][yfin+1].pieza.clase==rey)
			 if(tablero[xfin+1][yfin+1].pieza.color!=movimiento.jugador)r++;
	  if(tablero[xfin+1][yfin].pieza.clase==rey)
			 if(tablero[xfin+1][yfin].pieza.color!=movimiento.jugador)r++;
	  if(tablero[xfin+1][yfin-1].pieza.clase==rey)
			 if(tablero[xfin+1][yfin-1].pieza.color!=movimiento.jugador)r++;
	  if(tablero[xfin][yfin+1].pieza.clase==rey)
			 if(tablero[xfin][yfin+1].pieza.color!=movimiento.jugador)r++;
	  if(tablero[xfin][yfin-1].pieza.clase==rey)
			 if(tablero[xfin][yfin-1].pieza.color!=movimiento.jugador)r++;
	  if(tablero[xfin-1][yfin+1].pieza.clase==rey)
			 if(tablero[xfin-1][yfin+1].pieza.color!=movimiento.jugador)r++;
	  if(tablero[xfin-1][yfin].pieza.clase==rey)
			 if(tablero[xfin-1][yfin].pieza.color!=movimiento.jugador)r++;
	  if(tablero[xfin-1][yfin-1].pieza.clase==rey)
			 if(tablero[xfin-1][yfin-1].pieza.color!=movimiento.jugador)r++;
	  if(r>0)
	  {
			 /*Restaurar pieza que habia en el lugar de llegada*/
			 tablero[xfin][yfin].pieza.clase=pieza.clase;
			 tablero[xfin][yfin].pieza.color=pieza.color;
			 /*Restaurar rey en posicion de salida*/
			 tablero[xini][yini].pieza.clase=rey;
			 return 0;
	  }

/*Posible jaque de pieza !=peon  y de color distinto de rey
  que pueda llegar a pos de llegada del rey*/
	  mov_jaque.posfin.posx=xfin;
	  mov_jaque.posfin.posy=yfin;
	  if(movimiento.jugador==negro)mov_jaque.jugador=blanco;
	  else mov_jaque.jugador=negro;

	  for(xini_jaque=1;xini_jaque<9;xini_jaque++)
			 for(yini_jaque=1;yini_jaque<9;yini_jaque++)
			 {
					mov_jaque.posini.posx=xini_jaque;
					mov_jaque.posini.posy=yini_jaque;
					if(tablero[xini_jaque][yini_jaque].pieza.clase!=peon)
						  if(tablero[xini_jaque][yini_jaque].pieza.color!=movimiento.jugador)
								 if(movimiento_pieza(tablero,mov_jaque))conta_jaque++;
			 }

/*Restaurar rey a su casilla de salida*/
	  tablero[xini][yini].pieza.clase=rey;
/*Restaurar pieza en la posicion de llegada*/
	  tablero[xfin][yfin].pieza.clase=pieza.clase;
	  tablero[xfin][yfin].pieza.color=pieza.color;

/*Devolver 0 si hay jaque en casilla de llegada*/
	  if(conta_jaque>0) return 0;



/*Verificacion movimiento REY una vez casilla llegada este libre de jaque*/
	  if(xini+1==xfin && yini-1==yfin)return 1;
	  else  if(xini+1==xfin && yini==yfin)return 1;
	  else  if(xini+1==xfin && yini+1==yfin)return 1;
	  else  if(xini==xfin && yini-1==yfin)return 1;
	  else  if(xini==xfin && yini+1==yfin)return 1;
	  else  if(xini-1==xfin && yini==yfin)return 1;
	  else  if(xini-1==xfin && yini-1==yfin)return 1;
	  else  if(xini-1==xfin && yini+1==yfin)return 1;
	  else  return 0;
}


int movimiento_pieza(Tablero tablero,Movimiento movimiento)
/*Verifica si la clase de movimiento distinta de rey dentro del tablero es válido
  necesita tener construidos los tipos Movimiento y Tablero
  Devolviendo 1 si es posible y 0 en caso contrario*/
{
	  int xini,yini,xfin,yfin,i;
	  xini=movimiento.posini.posx;
	  yini=movimiento.posini.posy;
	  xfin=movimiento.posfin.posx;
	  yfin=movimiento.posfin.posy;

/*Verificar limites de definicion*/
	  if(xini<1 || xini>8 || yini<0 || yini>8)return 0;
	  if(xfin<1 || xfin>8 || yfin<0 || yfin>8)return 0;

/*Impedir mover a la misma posicion*/
	  if(xini==xfin && yini==yfin)return 0;

/*Verificar si hay pieza en la posicion de inicio*/
	  if(tablero[xini][yini].pieza.clase==vacio)return 0;

/*Verificar que se va a mover una pieza del color del jugador*/
	  if(tablero[xini][yini].pieza.color!=movimiento.jugador)return 0;

/*Verificar no mover a lugar que ocupe una pieza del mismo jugador que mueve*/
	  if(tablero[xfin][yfin].pieza.color==movimiento.jugador)return 0;

/*Verificacion para el movimiento del REY*/
	  if(tablero[xini][yini].pieza.clase==rey);


/*Verificacion del movimiento del PEON*/
	  if(tablero[xini][yini].pieza.clase==peon)
	  {if(tablero[xini][yini].pieza.color==blanca)
			 {
					if(tablero[xfin][yfin].pieza.clase!=vacio)
						  if(xfin==xini+1 && yfin==yini-1)return 1;
						  else if(xfin==xini+1 && yfin==yini+1)return 1;
						  else return 0;
					if(tablero[xfin][yfin].pieza.clase==vacio)
						  if(xfin==xini+1 && yfin==yini)return 1;
						  else if(xini==2 && xfin==4 && yini==yfin)
								 if(tablero[3][yfin].pieza.clase==vacio)return 1;
								 else return 0;
			 }
			 if(tablero[xini][yini].pieza.color==negra)
			 {
					if(tablero[xfin][yfin].pieza.clase!=vacio)
						  if(xfin==xini-1 && yfin==yini-1)return 1;
						  else if(xfin==xini-1 && yfin==yini+1)return 1;
						  else return 0;
					if(tablero[xfin][yfin].pieza.clase==vacio)
						  if(xfin==xini-1 && yfin==yini)return 1;
						  else if(xini==7 && xfin==5 && yini==yfin)
								 if(tablero[6][yfin].pieza.clase==vacio)return 1;
								 else return 0;
			 }
	  }


/*Verificacion del movimiento del CABALLO*/
	  if(tablero[xini][yini].pieza.clase==caballo)
			 if(xfin==xini+2 && yfin==yini+1)return 1;
			 else if(xfin==xini+1 && yfin==yini+2)return 1;
			 else if(xfin==xini-1 && yfin==yini+2)return 1;
			 else if(xfin==xini-2 && yfin==yini+1)return 1;
			 else if(xfin==xini-2 && yfin==yini-1)return 1;
			 else if(xfin==xini-1 && yfin==yini-2)return 1;
			 else if(xfin==xini+1 && yfin==yini-2)return 1;
			 else if(xfin==xini+2 && yfin==yini-1)return 1;
			 else return 0;


/*Verificacion para el movimiento del ALFIL*/
	  if(tablero[xini][yini].pieza.clase==alfil)
     {
			 if(tablero[xfin][yfin].pieza.clase!=vacio)
			 { if(abs(xfin-xini)==abs(yfin-yini))
					{
						  /*4 casos diagonales*/
						  if(xfin>xini && yfin>yini)
						  {i=1; /*Contamos el numero de casillas vacias intermendias*/
								 while(xini+i<9 && yini+i<9 && tablero[xini+i][yini+i].pieza.clase==vacio)i++;
								 if(xini+i==xfin)return 1;}
						  if(xfin>xini && yfin<yini)
						  {i=1; /*Contamos el numero de casillas vacias intermendias*/
								 while(xini+i<9 && yini-i>0 && tablero[xini+i][yini-i].pieza.clase==vacio)i++;
								 if(xini+i==xfin)return 1;}
						  if(xfin<xini && yfin>yini)
						  {i=1; /*Contamos el numero de casillas vacias intermendias*/
								 while(xini-i>0 && yini+i<9 && tablero[xini-i][yini+i].pieza.clase==vacio)i++;
								 if(xini-i==xfin)return 1;}
						  if(xfin<xini && yfin<yini)
						  {i=1;  /*Contamos el numero de casillas vacias intermendias*/
								 while(xini-i>0 && yini-i>0 && tablero[xini-i][yini-i].pieza.clase==vacio)i++;
								 if(xini-i==xfin)return 1;}
					}
			 }
			 if(tablero[xfin][yfin].pieza.clase==vacio)
			 {
					if(abs(xfin-xini)==abs(yfin-yini))
					{
						  /*4 casos diagonales*/
						  if(xfin>xini && yfin>yini)
						  {i=1; /*Contamos el numero de casillas vacias intermendias*/
								 while(xini+i<9 && yini+i<9 && i<abs(xfin-xini) && tablero[xini+i][yini+i].pieza.clase==vacio)i++;
								 if(xini+i==xfin)return 1;}
						  if(xfin>xini && yfin<yini)
						  {i=1; /*Contamos el numero de casillas vacias intermendias*/
								 while(xini+i<9 && yini-i>0 && i<abs(xfin-xini) && tablero[xini+i][yini-i].pieza.clase==vacio)i++;
								 if(xini+i==xfin)return 1;}
						  if(xfin<xini && yfin>yini)
						  {i=1; /*Contamos el numero de casillas vacias intermendias*/
								 while(xini-i>0 && yini+i<9 && i<abs(xfin-xini) && tablero[xini-i][yini+i].pieza.clase==vacio)i++;
								 if(xini-i==xfin)return 1;}
						  if(xfin<xini && yfin<yini)
						  {i=1; /*Contamos el numero de casillas vacias intermendias*/
								 while(xini-i>0 && yini-i>0 && i<abs(xfin-xini) && tablero[xini-i][yini-i].pieza.clase==vacio)i++;
								 if(xini-i==xfin)return 1;}
					}
			 }
     }

/*Verificacion para el movimiento de la TORRE*/
	  if(tablero[xini][yini].pieza.clase==torre)
	  {
			 if(tablero[xfin][yfin].pieza.clase!=vacio)
			 {
					if(xini==xfin)
					{
						  if(yini<yfin)
						  {i=1;
								 while(tablero[xini][yini+i].pieza.clase==vacio)i++;
								 if(yini+i==yfin)return 1;}
						  else
						  {i=1;
								 while(tablero[xini][yini-i].pieza.clase==vacio)i++;
								 if(yini-i==yfin)return 1;}
					}
					if(yini==yfin)
					{
						  if(xini<xfin)
						  {i=1;
								 while(i<abs(xini-xfin) && tablero[xini+i][yini].pieza.clase==vacio)i++;
								 if(xini+i==xfin)return 1;}
						  else
						  {i=1;
								 while(i<abs(xini-xfin) && tablero[xini-i][yini].pieza.clase==vacio)i++;
								 if(xini-i==xfin)return 1;}
					}
			 }
			 if(tablero[xfin][yfin].pieza.clase==vacio)
			 {
					if(xini==xfin)
					{if(yini<yfin)
						  {i=1;
								 while(yini+i<yfin && tablero[xini][yini+i].pieza.clase==vacio)i++;
								 if(yini+i==yfin)return 1;}
						  else
						  {i=1;
								 while(yini-i>yfin && tablero[xini][yini-i].pieza.clase==vacio)i++;
								 if(yini-i==yfin)return 1;}
					}
					if(yini==yfin)
					{if(xini<xfin)
						  {i=1;
								 while(xini+i<xfin && tablero[xini+i][yini].pieza.clase==vacio)i++;
								 if(xini+i==xfin)return 1;}
						  else
						  {i=1;
								 while(xini-i>xfin && tablero[xini-i][yini].pieza.clase==vacio)i++;
								 if(xini-i==xfin)return 1;}
					}
			 }
	  }


/*Verificacion para el movimiento de la REINA*/
	  if(tablero[xini][yini].pieza.clase==reina)
     {
			 if(tablero[xfin][yfin].pieza.clase!=vacio)
			 {
					/*Casos diagonales*/
					if(abs(xfin-xini)==abs(yfin-yini))
					{
						  if(xfin>xini && yfin>yini)
						  {
								 i=1; /*Contamos el numero de casillas vacias intermendias*/
								 while(xini+i<9 && yini+i<9 && tablero[xini+i][yini+i].pieza.clase==vacio)
										i++;
								 if(xini+i==xfin)
										return 1;
						  }
						  if(xfin>xini && yfin<yini)
						  {i=1; /*Contamos el numero de casillas vacias intermendias*/
								 while(xini+i<9 && yini-i>0 && tablero[xini+i][yini-i].pieza.clase==vacio)i++;
								 if(xini+i==xfin)return 1;}
						  if(xfin<xini && yfin>yini)
						  {i=1; /*Contamos el numero de casillas vacias intermendias*/
								 while(xini-i>0 && yini+i<9 && tablero[xini-i][yini+i].pieza.clase==vacio)i++;
								 if(xini-i==xfin)return 1;}
						  if(xfin<xini && yfin<yini)
						  {i=1;  /*Contamos el numero de casillas vacias intermendias*/
								 while(xini-i>0 && yini-i>0 && tablero[xini-i][yini-i].pieza.clase==vacio)i++;
								 if(xini-i==xfin)return 1;}
					}
					/*Casos vertical y horizontal*/
					if(xini==xfin)
					{
						  if(yini<yfin)
						  {i=1;
								 while(tablero[xini][yini+i].pieza.clase==vacio)i++;
								 if(yini+i==yfin)return 1;
						  }
						  else
						  {i=1;
								 while(tablero[xini][yini-i].pieza.clase==vacio)i++;
								 if(yini-i==yfin)return 1;
						  }
					}
					if(yini==yfin)
					{
						  if(xini<xfin)
						  {i=1;
								 while(i<abs(xini-xfin) && tablero[xini+i][yini].pieza.clase==vacio)i++;
								 if(xini+i==xfin)return 1;}
						  else
						  {i=1;
								 while(i<abs(xini-xfin) && tablero[xini-i][yini].pieza.clase==vacio)i++;
								 if(xini-i==xfin)return 1;}
					}
			 }

			 if(tablero[xfin][yfin].pieza.clase==vacio)
			 {
					if(abs(xfin-xini)==abs(yfin-yini))
					{
						  /*Casos diagonales*/
						  if(xfin>xini && yfin>yini)
						  {i=1; /*Contamos el numero de casillas vacias intermendias*/
								 while(xini+i<9 && yini+i<9 && i<abs(xfin-xini) && tablero[xini+i][yini+i].pieza.clase==vacio)i++;
								 if(xini+i==xfin)return 1;}
						  if(xfin>xini && yfin<yini)
						  {i=1; /*Contamos el numero de casillas vacias intermendias*/
								 while(xini+i<9 && yini-i>0 && i<abs(xfin-xini) && tablero[xini+i][yini-i].pieza.clase==vacio)i++;
								 if(xini+i==xfin)return 1;}
						  if(xfin<xini && yfin>yini)
						  {i=1; /*Contamos el numero de casillas vacias intermendias*/
								 while(xini-i>0 && yini+i<9 && i<abs(xfin-xini) && tablero[xini-i][yini+i].pieza.clase==vacio)i++;
								 if(xini-i==xfin)return 1;}
						  if(xfin<xini && yfin<yini)
						  {i=1; /*Contamos el numero de casillas vacias intermendias*/
								 while(xini-i>0 && yini-i>0 && i<abs(xfin-xini) && tablero[xini-i][yini-i].pieza.clase==vacio)i++;
								 if(xini-i==xfin)return 1;}
					}
					/*Casos vertical y horizontal*/
					if(xini==xfin)
					{
						  if(yini<yfin)
						  {i=1;
								 while(yini+i<yfin && tablero[xini][yini+i].pieza.clase==vacio)i++;
								 if(yini+i==yfin)return 1;}
						  else
						  {i=1;
								 while(yini-i>yfin && tablero[xini][yini-i].pieza.clase==vacio)i++;
								 if(yini-i==yfin)return 1;}
					}
					if(yini==yfin)
					{
						  if(xini<xfin)
						  {i=1;
								 while(xini+i<xfin && tablero[xini+i][yini].pieza.clase==vacio)i++;
								 if(xini+i==xfin)return 1;}
						  else
						  {i=1;
								 while(xini-i>xfin && tablero[xini-i][yini].pieza.clase==vacio)i++;
								 if(xini-i==xfin)return 1;}
					}
			 }
	  }

	  return 0;
}

int proteccion_rey(Tablero tablero,Movimiento movimiento)
/*En entrada: Movimento distinto del de un REY ya verificada su validez
  por la funcion movimiento_pieza
  En salida: Devuelve 1 si el REY del color del movimiento
  NO queda en jaque tras el movimiento,
  es decir, devuelve 1 si el rey esta protegido*/
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

/*Busco posicion del REY del color del movimiento*/
	  for(i=1;i<=8;i++)
			 for(j=1;j<=8;j++)
					if(tablero[i][j].pieza.clase==rey)
						  if(tablero[i][j].pieza.color==movimiento.jugador)
						  {xrey=i;yrey=j;
								 i=9;j=9;}

/*Asigno lugar del rey para el final del movimiento de una pieza que pueda hacer
  un posible jaque al rey*/
	  mov_jaque.posfin.posx=xrey;
	  mov_jaque.posfin.posy=yrey;

/*Guardo la pieza que se va a mover y la pieza comida*/
	  pieza.clase=tablero[xini][yini].pieza.clase;
	  pieza.color=tablero[xini][yini].pieza.color;
	  piezafinal.clase=tablero[xfin][yfin].pieza.clase;
	  piezafinal.color=tablero[xfin][yfin].pieza.color;

/*Quito la pieza que se va a mover de su casilla de salida segun fue
  asignado anteriormente debido al argumento de entrada 'movimiento'*/
	  tablero[xini][yini].pieza.clase=vacio;
	  tablero[xini][yini].pieza.color=sincolor;
	  tablero[xfin][yfin].pieza.clase=pieza.clase;
	  tablero[xfin][yfin].pieza.color=pieza.color;

/*Asignar color contrario al movimiento de la pieza que pueda hacer jaque*/
	  if(movimiento.jugador==blanco)
			 mov_jaque.jugador=negro;
	  else 
			 mov_jaque.jugador=blanco;

/*Verifico si existe jaque tras el movimiento incrementando el conta_jaque
  en caso afirmativo, dejandolo a 0 si no existe el jaque*/
	  conta_jaque=0;
	  for(xini_jaque=1;xini_jaque<9;xini_jaque++)
			 for(yini_jaque=1;yini_jaque<9;yini_jaque++)
			 {
					mov_jaque.posini.posx=xini_jaque;
					mov_jaque.posini.posy=yini_jaque;
					if(tablero[xini_jaque][yini_jaque].pieza.clase!=vacio)
						  if(tablero[xini_jaque][yini_jaque].pieza.clase!=rey)
								 if(tablero[xini_jaque][yini_jaque].pieza.color==mov_jaque.jugador)
										if(movimiento_pieza(tablero,mov_jaque))
											  conta_jaque++;
			 }

/*Volver a colocar las piezas en la casilla de inicio y de llegada del
  movimiento */
	  tablero[xini][yini].pieza.clase=pieza.clase;
	  tablero[xini][yini].pieza.color=pieza.color;
	  tablero[xfin][yfin].pieza.clase=piezafinal.clase;
	  tablero[xfin][yfin].pieza.color=piezafinal.color;

/*Devolver 1 si no hay jaque*/
	  if(conta_jaque==0)
			 return 1;
	  else 
			 return 0;
}

#endif


