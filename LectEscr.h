#ifndef __LECTESCR__
#define __LECTESCR__

int lee_pos(Secuencia sec,int turno)
/*En entrada:El turno turno
  En salida: Secuencia con las posiciones de inicio y llegada de un
  movimiento para el turno k*/
{
	  int x,y;
	  printf("\n<Pos inicial> :Fila/Colum->");
	  scanf("%d %d",&x,&y);
	  if(1<=x && x<=8 && 1<=y && y<=8)
	  {sec[turno].posini.posx=x;
			 sec[turno].posini.posy=y;}
	  else   {sec[turno].posini.posx=0;
			 sec[turno].posini.posy=0;}
	  printf("<Pos final>  :Fila/Colum->");
	  scanf("%d %d",&x,&y);
	  if(1<=x && x<=8 && 1<=y && y<=8)
	  {sec[turno].posfin.posx=x;
			 sec[turno].posfin.posy=y;}
	  else  {sec[turno].posfin.posx=0;
			 sec[turno].posfin.posy=0;}
}

#endif


