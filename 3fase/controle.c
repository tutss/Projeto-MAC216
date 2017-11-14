#include <stdio.h>
#include "controle.h"

FILE *display;
Robot rb[10];

/*void anda(int ri) {
  Robot r = rb[ri];

  if (r.pi == 14) r.vi = -1;
  if (r.pi == 0)  r.vi =  1;

  if (r.pj == 14) r.vj = -1;
  if (r.pj == 0)  r.vj =  1;

  r.i = r.pi + r.vi;
  r.j = r.pj + r.vj;
  rb[ri] = r;
  mostra(ri);
}*/

// termina de escrever o txt da arena e começa a mostrá-la e receber comandos
// pelo protocolo estabelecido na comunicação entre controle.c e apres
void inicializaGraf()
{
  //int t; 						/* tempo */
  // pipe direto para o programa apres
  display = popen("python apres", "w");

}

// substitui (oi,oj) por (di,dj). Ou seja, as antigas coordenadas de destino
// do robô agora são as de origem, pois ele foi para a célula (di,dj)
void atualiza(int index) {
  Robot r = rb[index];
  r.oi = r.di;
  r.oj = r.dj;
  rb[index] = r;
}

/***********************
* A função desenha célula recebe os argumentos px, py e terreno (inteiro) de
* uma célula e envia essas informações para o programa apres
***********************/
void desenhaCelula (int px, int py, int terreno)
{
  // envia para apres a instrução d_cel, as coordenadas (px,py) e o tipo de terreno
  fprintf(display, "d_cel %d %d %d\n", px, py, terreno);
  fflush(display);
}

void desenhaBase (int x, int y, int exercito)
{
  fprintf(display, "base flag%d.png %d %d\n", exercito, x, y);
  fflush(display);
}

void colocaCristal (int x, int y, int n)
{
  fprintf(display, "cristal %d %d %d\n", x, y, n);
  fflush(display);
}

/*
Inicializa a sprite (a imagem) do robô no programa apres, que é responsável por
exibir a arena. O que esse método faz é simplesmente mandar uma instrução ao
programa apres que faça a imagem do robô ser adicionada na lista "robs" do programa
em python. Depois, chama o método mostra para que o robô seja movido para a posição
i j dada como parâmetro
*/
void desenhaRobo (int exercito, int index, int i, int j)
{


  if (exercito == 0)
    fprintf(display, "rob ra.png\n");
  else
    fprintf(display, "rob rb.png\n");
  fflush(display);
  rb[index].exercito = exercito;
  // o robô começa fora da arena
  rb[index].oi = -1;
  rb[index].oj = -1;
  // o robô tem sua célula de destino definida pelos parâmetros i,j
  rb[index].di = i;
  rb[index].dj = j;
  // a função 'mostra' enviará para a interface visual a instrução para "Movimentar"
  // o novo robô da posição (-1,-1) para a posição (i,j)
  mostra(index);
}

// mostra na arena o robô colocado em index
void mostra(int index) {
  // display: ri oi oj di dj (o: origem) (d: destino) (i,j): coordenadas
  fprintf(display, "%d %d %d %d %d\n",
		  index, rb[index].oi, rb[index].oj, rb[index].di, rb[index].dj);
  fflush(display);
  // substitui (oi,oj) por (di,dj). Ou seja, as antigas coordenadas de destino
  // do robô agora são as de origem, pois ele foi para a célula (di,dj)
  atualiza(index);
}

void acabaDesenho () {
  pclose(display);
}

// move o robô no index dado para a posição (di, dj)
void moveRobo (int index, int di, int dj){
  // recupera o robô em index
  Robot r = rb[index];
  // muda as coordenadas de seu destino
  r.di = di;
  r.dj = dj;
  rb[index] = r;
  // envia para a interface visual a instrução para movê-lo
  mostra(index);
}
/*
void NovoRoboDesenho (int time){
  if(time == 1)
    fprintf(display, "rob GILEAD_A.png\n");
  else
    fprintf(display, "rob GILEAD_B.png\n");
}*/

/* Programa simples para mostrar como controlar a arena */
/*int main() {
  int t; 						/* tempo */
  // pipe direto para o programa apres
  /*display = popen("python apres", "w");


  rb[0].pi =  6;
  rb[0].pj = 14;
  rb[0].vi = -1;
  rb[0].vj =  1;

  rb[1].pi = 10;
  rb[1].pj = 11;
  rb[1].vi =  1;
  rb[1].vj = -1;

  if (display == NULL) {
	fprintf(stderr,"Não encontrei o programa de exibição\n");
	return 1;
  }

  /* cria dois robôs
  fprintf(display, "rob GILEAD_A.png\nrob GILEAD_B.png\n");


  for (t=0; t < 10; t++) {
	anda(0);
	anda(1);
	mostra(0);
	mostra(1);
	fflush(display);
  }
   pclose(display)
}*/
