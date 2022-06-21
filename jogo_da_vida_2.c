
#include <stdio.h>
#include <stdlib.h>
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

char **alocaMatriz(int nL,int nC);
void desalocaMatriz(char **mAnt, int nL);
void limpaMatriz(char **m, int nL, int nC);
void imprimeMatriz(char **mat, int nL, int nC);


int contaVizinhos(int nL, int nC, int j, int i, char **mAnt);
void atualizaMat(char **mAtual, char **mAnt, int nL, int nC);


void inicBlinker(char **m, int nL, int nC);
void inicBloco(char **m, int nL, int nC);
void inicSapo(char **m, int nL, int nC);
void inicGlider(char **m, int nL, int nC);
void inicLWSS(char **m, int nL, int nC);


void menuInicJogo(char **mat, int nL, int nC);
void jogaJogoVida(char **mAtual, int nL, int nC, int nCiclos);



int main ()
{
  char **mat;
  int nL=10, nC=10, nCiclos=10 , parar = 0;
   mat = alocaMatriz(nL, nC);

	
	while (parar != 1){
        printf("Escolha como quer começar \n");
		
	    printf("Insira o tamanho da matriz \n");
	    scanf("%d", &nL);
	    nC = nL;
    


	    printf("Insira o nº de Ciclos: \n");
	    scanf("%d", &nCiclos);	
		
        menuInicJogo(mat, nL, nC);
        jogaJogoVida(mat, nL, nC, nCiclos);
        desalocaMatriz(mat,nL);
	
	    printf("\nDeseja continuar? Insira 1 para parar: \n");
	    scanf("%d", &parar);  
	}
}





char **alocaMatriz(int nL, int nC)
{
  char **mat ;
  int i;

  mat = malloc (nL * sizeof (char*)) ;

  for (i=0; i < nL; i++)
     mat[i] = malloc (nC * sizeof (char)) ;

  return mat;
}

void desalocaMatriz(char **mAnt, int nL)
{
  int i;
    for (i=0; i < nL; i++)
     free (mAnt[i]);
  free (mAnt);

}


void limpaMatriz(char **m, int nL, int nC)
{
    int i,j;
    for(i=0;i<nL;i++)
     for(j=0;j<nC;j++)
        m[i][j]=VAZ;
}

void imprimeMatriz(char **mat, int nL, int nC)
{
  int i; int j;

  for(i=0;i<nL;i++){
        printf("\n");

        for(j=0;j<nC;j++)
            printf("%c", mat[i][j]);
  }
  printf("\n\n");
}

void copiaMatriz(char **mAnt, char **mAtual, int nL,int nC)
{
  int i; int j;
  
  for(i=0;i<nL;i++)
    	for(j=0;j<nC;j++)
        mAnt[i][j] = mAtual[i][j];
} 
int contaVizinhos(int i, int j, int nC, int nL, char **mAnt)
{
  int a, b, vivos=0;

  {
      for(a = i-1; a <= i+1; a++)
      {
        for(b = j-1; b <= j+1; b++)
            {
                if (a >= 0 && b >= 0 && a <= (nL-1) && b <= (nC -1))
                {
                    if(mAnt[a][b]==ORG)
                    vivos++;
                }
              }  
            }
      }   
  }
    return vivos;

}

void atualizaMat(char **mAtual, char **mAnt, int nL, int nC)
{
  
  int i, j, vivos;
  char cel;
  
    for ( i = 0; i < nL; i++)
    {
      for (j = 0; j < nC; j++)
      {
        vivos = contaVizinhos(i, j, nC, nL, mAnt);
        cel = mAnt[i][j];
        if (cel == ORG)
          vivos--;
        if (cel == ORG  && vivos == 2)
          cel = ORG;
        else if(cel == ORG  && vivos == 3)
          cel = ORG;
        else if (cel == ORG && vivos > 3)
          cel = VAZ;
        else if (cel == ORG && vivos < 2)
          cel = VAZ;
        else if (cel == VAZ && vivos == 3)
          cel = ORG;
        mAtual[i][j] = cel;
      }
    }
}




void inicBlinker(char **m, int nL, int nC)
{
  char padrao[1][3]={{ORG,ORG,ORG}};
  int i,j, xInic=nL/2, yInic=nC/2;

  limpaMatriz(m,nL,nC);

 for(i=0;i<1;i++)
    for(j=0;j<3;j++)
      m[xInic+i][yInic+j]=padrao[i][j];
}

void inicBloco(char **m, int nL, int nC)
{
 char padrao[2][2]={{ORG,ORG},{ORG,ORG}};
  int i,j,xInic=nL/2, yInic=nC/2;


 limpaMatriz(m,nL,nC);


 for(i=0;i<2;i++)
    for(j=0;j<2;j++)
      m[xInic+i][yInic+j]=padrao[i][j];
}


void inicSapo(char **m, int nL, int nC)
{

 char padrao[2][4]={{VAZ,ORG,ORG,ORG},{ORG,ORG,ORG,VAZ}};
  int i,j,xInic=nL/2, yInic=nC/2;

  limpaMatriz(m,nL,nC);


   for(i=0;i<2;i++)
      for(j=0;j<4;j++)
      m[xInic+i][yInic+j]=padrao[i][j];

}

void inicGlider(char **m, int nL, int nC)
{
char padrao[3][3]={{ORG,ORG,ORG},{ORG,VAZ,VAZ},{VAZ,ORG,VAZ}};
 int i,j,xInic,yInic;

 limpaMatriz(m,nL,nC);

 xInic=nL-4;
 yInic=nC-4;

 for(i=0;i<3;i++)
    for(j=0;j<3;j++)
      m[xInic+i][yInic+j]=padrao[i][j];
}

void inicLWSS(char **m, int nL, int nC)
{
	
char padrao[4][5]={{VAZ,ORG,VAZ,VAZ,ORG},{ORG,VAZ,VAZ,VAZ,VAZ},{ORG,VAZ,VAZ,VAZ,ORG},{ORG,ORG,ORG,ORG,VAZ}};
 int i,j,xInic,yInic;

 limpaMatriz(m,nL,nC);

 xInic=nL-5;
 yInic=nC-6;

 for(i=0;i<4;i++)
    for(j=0;j<5;j++)
      m[xInic+i][yInic+j]=padrao[i][j];

}



void menuInicJogo(char **mat, int nL, int nC)
{
    int opcao;

   printf("(1)Bloco\n(2)Blinker\n(3)Sapo\n(4)Glider\n(5)LWSS\nEntre com a opcao: ");
   scanf("%d",&opcao);
   switch(opcao)
   {
     case 1:   inicBloco(mat,nL,nC); break;
     case 2:   inicBlinker(mat,nL,nC); break;
     case 3:   inicSapo(mat,nL,nC); break;
     case 4:   inicGlider(mat,nL,nC); break;
     case 5:   inicLWSS(mat,nL,nC); break;
   }

  imprimeMatriz(mat,nL,nC);

  printf("Se inicializacao correta digite qualquer tecla para iniciar o jogo..."); while(getchar()!='\n'); getchar();
}



void jogaJogoVida(char **mAtual, int nL, int nC, int nCiclos)
{
  char **mAnt;
  int c, i, a, pollingDelay = 1000;

  
  system("clear");
  imprimeMatriz(mAtual,nL,nC); 
  
  #ifdef _WIN32
  Sleep(pollingDelay);
  #else
  usleep(pollingDelay*1000);  // sleep for 100 milliSeconds */
  #endif


  mAnt = alocaMatriz(nL,nC);

  for(c=1;c<=nCiclos;c++)
  {
        copiaMatriz(mAnt,mAtual,nL,nC);
        atualizaMat(mAtual,mAnt,nL,nC);
        system("clear");
        imprimeMatriz(mAtual,nL,nC);
        printf("\n");
        // getchar();
       	#ifdef _WIN32
  			Sleep(pollingDelay);
  			#else
  			usleep(pollingDelay*1000);  // sleep for 100 milliSeconds */
  			#endif
  }
  desalocaMatriz(mAnt,nL);

}

