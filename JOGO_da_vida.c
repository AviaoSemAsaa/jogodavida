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


void limpaMatriz(char **m, int nL, int nC)
{
    int i,j;
    for(i=0;i<nL;i++)
     for(j=0;j<nC;j++)
        m[i][j]=VAZ;
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

char **alocaMatriz(nL, nC)
{
  char **mat ;
  int i, j ;


  mat = malloc (nL * sizeof (char*)) ;


  for (i=0; i < nL; i++)
    mat[i] = malloc (nC * sizeof (char));

  return mat;
}

void desalocaMatriz(char **mAnt, int nL)
{
  int i;
    for (i=0; i < nL; i++)
     free (mAnt[i]);
  free (mAnt);

}

void imprimeMatriz(char **mat, int nL, int nC)
{
  int i; int j;
  
  for(i=0;i<nL;i++)
    	for(j=0;j<nC;j++)
        printf("%c", mat[i][j]);
}

int contaVizinhos(int nL, int nC, int j, int i, char **mAnt)
{
  int vivos = 0;
  int a, b, x, y;
  char c;

    for (y = -1; y <= 1; y++)
    {
      for (x = -1; x <= 1; x++)
      {
        c = mAnt[i+x][j+y];
        if (c == ORG)
          vivos++;
      }
    }
  return vivos;
}

void copiaMatriz(char **mAnt, char **mAtual, int nL,int nC)
{
  int i; int j;
  
  for(i=0;i<nL;i++)
    	for(j=0;j<nC;j++)
        mAnt[i][j] = mAtual[i][j];
} 

void atualizaMat(char **mAtual, char **mAnt, int nL, int nC)
{
  int i, j, vivos;
  char cel;
  
    for ( i = 0; i <= nL; i++)
    {
      for (j = 0; j <= nC; j++)
      {
        vivos = contaVizinhos(nC, nL, j, i, mAnt);
        cel = mAnt[i][j];
        if (cel == ORG)
          vivos--;
        if (vivos < 2)
          mAtual[i][j] = VAZ;
        else if ((vivos == 2 || vivos == 3) && cel == ORG)
          mAtual[i][j] = ORG;
        else if ((vivos > 3) && cel == ORG)
          mAtual[i][j] = VAZ;
        else if (vivos == 0 && cel == VAZ)
          mAtual[i][j] = ORG;
        else
          mAtual[i][j] = mAnt [i][j];
          
      }
    }
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
}


void jogaJogoVida(char **mAtual, int nL, int nC, int nCiclos)
{
  char **mAnt;
  int c, i;

  
  system("cls");
  imprimeMatriz(mAtual,nL,nC); 
  
  for (i=0; i < 100; i++);

  mAnt = alocaMatriz(nL,nC);

  for(c=1;c<=nCiclos;c++)
  {
        copiaMatriz(mAnt,mAtual,nL,nC);
        atualizaMat(mAtual,mAnt,nL,nC);
        system("cls");
        imprimeMatriz(mAtual,nL,nC);
        // getchar();
       for (i=0; i < 100; i++);
  }
  desalocaMatriz(mAnt,nL);

}

int main ()
{
  char **mat;
  int nL=20,nC=20,nCiclos=20;
   mat = alocaMatriz(nL, nC);

  printf("Escolha como quer começar: \n");
  menuInicJogo(mat, nL, nC);
  jogaJogoVida(mat, nL, nC, nCiclos);

  desalocaMatriz(mat,nL);
}