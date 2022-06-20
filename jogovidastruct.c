#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#ifdef _WIN32
#include <Windows.h>
#define LIMPA "cls"
#else
#include <unistd.h>
#define LIMPA "clear"
#endif

#define ORG 'X'
#define VAZ '.'
#define TAM 101


typedef struct tab
{
  char nomeJogo[TAM];
  int ciclosVida;
  int dim1, dim2;
  char **m;			//AtenC'C#o! Essa matriz terC! que ser alocada dinamicamente
//para que a funcao que inicializa possa funcionar
} Tab;

char **alocaMatriz (Tab *j);
void desalocaMatriz (Tab *j);
void desalocaMatrizSimples (Tab *j, char**m);
void limpaMatriz (Tab * j);
void imprimeMatriz (Tab * j);


int contaVizinhos (Tab *j, int i, int k, char **mAnt);
void atualizaMat (Tab *j, char **mAnt);


void inicBlinker (Tab *j);
void inicBloco (Tab *j);
void inicSapo (Tab *j);
void inicGlider (Tab *j);
void inicLWSS (Tab *j);


void menuInicJogo (Tab * j);
void jogaJogoVida (Tab * j);



int
main ()
{

  ;
  Tab j;
  int nL = 10, nC = 10, nCiclos = 10, parar = 0;
  alocaMatriz (&j);


  while (parar != 1)
    {
      printf ("Escolha como quer comecar \n");

      printf ("Insira o tamanho da matriz \n");
      scanf ("%d", &j.dim1);
      j.dim2 = j.dim1;



      printf ("Insira o nB: de Ciclos: \n");
      scanf ("%d", &j.ciclosVida);

      menuInicJogo (&j);
      jogaJogoVida (&j);
      desalocaMatriz (&j);

      printf ("\nDeseja continuar? Insira 1 para parar: \n");
      scanf ("%d", &parar);
    }
}





char **
alocaMatriz (Tab *j)
{
  char **mat;
  int i;

  mat = malloc (j->dim1 * sizeof (char *));

  for (i = 0; i < j->dim1; i++)
    mat[i] = malloc (j->dim2 * sizeof (char));

  return mat;
}

void
desalocaMatriz (Tab *j)
{
  int i;
  for (i = 0; i < j->dim1; i++)
    free (j->m[i]);
  free (j->m);

}

void 
desalocaMatrizSimples (Tab *j, char **m)
{
  int i;
  for (i = 0; i < j->dim1; i++)
    free (m[i]);
  free (m);

}


void
limpaMatriz (Tab * j)
{
  int i, k;
  for (i = 0; i < j->dim1; i++)
    for (k = 0; k < j->dim2 ; k++)
      j->m[i][k] = VAZ;
}

void
imprimeMatriz (Tab * j)
{
  int i;
  int k;

  for (i = 0; i < j->dim1; i++)
    {
      printf ("\n");

      for (k = 0; k < j->dim2; k++)
	printf ("%c", j->m[i][k]);
    }
  printf ("\n\n");
}

void
copiaMatriz (Tab *j, char **m)
{
  int i;
  int k;

  for (i = 0; i < j->dim1; i++)
    for (k = 0; k < j->dim2; k++)
      m[i][k] = j->m[i][k];
}

int
contaVizinhos (Tab *j, int i, int k, char **mAnt)
{
  int a, b, vivos = 0;

  {
    for (a = i - 1; a <= i + 1; a++)
      {
	for (b = k - 1; b <= k + 1; b++)
	  {
	    if (a >= 0 && b >= 0 && a <= (j->dim1 - 1) && b <= (j->dim2 - 1))
	      {
		if (mAnt[a][b] == ORG)
		  vivos++;
	      }
	  }
      }
  }
  return vivos;
}


void atualizaMat (Tab *j, char **mAnt)
{

  int i, k, vivos;
  char cel;

  for (i = 0; i < j->dim1; i++)
    {
      for (k = 0; k < j->dim2; k++)
	{
	  vivos = contaVizinhos (j, i, k, mAnt);
	  cel = mAnt[i][k];
	  if (cel == ORG)
	    vivos--;
	  if (cel == ORG && vivos == 2)
	    cel = ORG;
	  else if (cel == ORG && vivos == 3)
	    cel = ORG;
	  else if (cel == ORG && vivos > 3)
	    cel = VAZ;
	  else if (cel == ORG && vivos < 2)
	    cel = VAZ;
	  else if (cel == VAZ && vivos == 3)
	    cel = ORG;
	 j->m[i][k] = cel;
	}
    }
}




void
inicBlinker (Tab *j)
{
  char padrao[1][3] = { {ORG, ORG, ORG} };
  int i, k, xInic = j->dim1 / 2, yInic = j->dim2 / 2;

  limpaMatriz (j);

  for (i = 0; i < 1; i++)
    for (k = 0; k < 3; k++)
      j->m[xInic + i][yInic + k] = padrao[i][k];
}

void
inicBloco (Tab *j)
{
  char padrao[2][2] = { {ORG, ORG}, {ORG, ORG} };
  int i, k, xInic = j->dim1 / 2, yInic = j->dim2 / 2;


  limpaMatriz (j);


  for (i = 0; i < 2; i++)
    for (k = 0; k < 2; k++)
      j->m[xInic + i][yInic + k] = padrao[i][k];
}


void
inicSapo (Tab *j)
{

  char padrao[2][4] = { {VAZ, ORG, ORG, ORG}, {ORG, ORG, ORG, VAZ} };
  int i, k, xInic = j->dim1 / 2, yInic = j->dim2 / 2;

  limpaMatriz (j);


  for (i = 0; i < 2; i++)
    for (k = 0; k < 4; k++)
      j->m[xInic + i][yInic + k] = padrao[i][k];

}

void
inicGlider (Tab *j)
{
  char padrao[3][3] = { {ORG, ORG, ORG}, {ORG, VAZ, VAZ}, {VAZ, ORG, VAZ} };
  int i, k, xInic, yInic;

  limpaMatriz (j);

  xInic = j->dim1 - 4;
  yInic = j->dim2 - 4;

  for (i = 0; i < 3; i++)
    for (k = 0; k < 3; k++)
      j->m[xInic + i][yInic + k] = padrao[i][k];
}

void
inicLWSS (Tab *j)
{

  char padrao[4][5] =
    { {VAZ, ORG, VAZ, VAZ, ORG}, {ORG, VAZ, VAZ, VAZ, VAZ}, {ORG, VAZ, VAZ,
							     VAZ, ORG}, {ORG,
									 ORG,
									 ORG,
									 ORG,
									 VAZ}
  };
  int i, k, xInic, yInic;

  limpaMatriz (j);

  xInic = j->dim1 - 5;
  yInic = j->dim2 - 6;

  for (i = 0; i < 4; i++)
    for (k = 0; k < 5; k++)
      j->m[xInic + i][yInic + k] = padrao[i][k];

}



void
menuInicJogo (Tab * j)
{
  int opcao;

  printf
    ("(1)Bloco\n(2)Blinker\n(3)Sapo\n(4)Glider\n(5)LWSS\nEntre com a opcao: ");
  scanf ("%d", &opcao);
  switch (opcao)
    {
    case 1:
    strcpy(j->nomeJogo , "jogoBloco");
      inicBloco (j);
      break;
    case 2:
      strcpy(j->nomeJogo, "jogoBlinker");
      inicBlinker (j);
      break;

    case 3:
      strcpy(j->nomeJogo , "jogoSapo");
      inicSapo (j);
      break;

    case 4:
      strcpy(j->nomeJogo , "jogoGlider");
      inicGlider (j);
      break;

    case 5:
      strcpy(j->nomeJogo , "jogoLWSS");
      inicLWSS (j);
      break;
    }

  imprimeMatriz (j);

  printf
    ("Se inicializacao correta digite qualquer tecla para iniciar o jogo...");
  while (getchar () != '\n');
  getchar ();
}



void
jogaJogoVida (Tab *j)
{
  char **mAnt;
  int c, i, a, pollingDelay = 1000;


  system ("clear");
  imprimeMatriz (j);

#ifdef _WIN32
  Sleep (pollingDelay);
#else
  usleep (pollingDelay * 1000);	// sleep for 100 milliSeconds */
#endif


  mAnt = alocaMatriz (j);

  for (c = 1; c <= j->ciclosVida; c++)
    {
      copiaMatriz (j, mAnt);
      atualizaMat (j, mAnt);
      system ("clear");
      imprimeMatriz (j);
      printf ("\n");
      // getchar();
#ifdef _WIN32
      Sleep (pollingDelay);
#else
      usleep (pollingDelay * 1000);	// sleep for 100 milliSeconds */
#endif
    }
  desalocaMatrizSimples (j, mAnt);

}
