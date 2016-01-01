#ifndef __CABFUNC__
#define __CABFUNC__

int validar_movimiento(Tablero tablero,Movimiento movimiento);
int actualizar(Tablero tablero,Movimiento movimiento);
int lee_pos(Secuencia secuencia,int k);
int imprime_pos(Secuencia secuencia,int k);
int ver_anterior(Secuencia sec_Blancas,Secuencia sec_Negras,int k);
int generar_posicion_inicial(Tablero tablero);
//int generar_tablero_antiguo(Tablero tablero2,Secuencia sec_blancas,Secuencia sec_negras,int anterior);
int pintar_tablero(Tablero tablero);
int movimiento_rey(Tablero tablero,Movimiento movimiento);
int movimiento_pieza(Tablero tablero,Movimiento movimiento);
int proteccion_rey(Tablero tablero,Movimiento movimiento);
int jaque_rey(Tablero tablero,Movimiento movimiento);
int jaque_mate(Tablero tablero,Color color_rey);

#endif
