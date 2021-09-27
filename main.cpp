#include<stdio.h>
#include<stdlib.h>
#include<math.h>

FILE *filein;

typedef struct matquadrada matquadrada;
struct matquadrada
{
    int n;
    double elem[10][10];
};

void LerMatQuadrada (matquadrada *);
void EscreverMatQuadrada (matquadrada *,int);
matquadrada MenorComplementar (matquadrada *, int, int);
double Det(matquadrada *,int k);
int soma(int );
int mult(int );

int main ()
{
    printf("Calculo de determinante com instrumentacao\n\n");
    matquadrada A;
    LerMatQuadrada (&A);

    int i,j,k;
    for(k=1; k< A.n + 1; k++)
    {
        printf("Matriz com dimensao %d:\n",k);
        EscreverMatQuadrada(&A,k);
        double y = Det(&A,k);
        printf("Valor do determinante: %20.0f\n\n", y);
    }

    printf("Numeros de somas+subtracoes e multiplicacoes:\n\n");
    for(k=1; k< A.n +1; k++)
    {
        printf("Dimensao: %3d %12d somas+subtracoes %8d multiplicacoes\n",k,soma(k),mult(k));
    }

    printf("\n\n");
    system ("pause");
    return 0;
}

void LerMatQuadrada (matquadrada *x)
{
    int i,j;
    filein = fopen ("input.txt", "r");
    x->n  = 10;
    for(i=0; i< x->n ; i++)
    {
        for(j=0; j< x->n ; j++)
        {
            fscanf (filein, "%lf ", &x->elem[i][j]);
        }
    }
}

void EscreverMatQuadrada (matquadrada *x,int k)
{
    int i,j;
    for(i=0; i< k ; i++)
    {
        printf("|");
        for(j=0; j< k ; j++)
        {
            printf(" %5.0lf", x->elem[i][j]);
        }
        printf("|\n");
    }
}

matquadrada MenorComplementar (matquadrada *x, int r, int s)
{
    int i,j;
    matquadrada mc;
    mc.n = x->n -1;
    for(i=0; i< x->n ; i++)
    {
        for(j=0; j< x->n ; j++)
        {
            if(i<r)
            {
                if(j<s)
                {
                    mc.elem[i][j] = x->elem[i][j];
                }
                if(j>s)
                {
                    mc.elem[i][j-1] = x->elem[i][j];
                }
            }
            if(i>r)
            {
                if(j<s)
                {
                    mc.elem[i-1][j] = x->elem[i][j];
                }
                if(j>s)
                {
                    mc.elem[i-1][j-1] = x->elem[i][j];
                }
            }
        }
    }
    return mc;
}

double Det(matquadrada *x, int k)
{
    int i,j;
    matquadrada m;
    m.n = k;
    for(i=0; i< k ; i++)
    {
        for(j=0; j< k ; j++)
        {
            m.elem[i][j] = x->elem[i][j];
        }
    }
    double det=0;
    if(k<1)
    {
        det = -9999999;
        return det;
    }
    if(k == 1)
    {
        det =  m.elem[0][0];
        return det;
    }
    if(k==2)
    {
        det =  m.elem[0][0]*m.elem[1][1] - m.elem[0][1]*m.elem[1][0];
        return det;
    }
    if(k==3)
    {
        det = m.elem[0][0]*m.elem[1][1]*m.elem[2][2] + m.elem[0][2]*m.elem[1][0]*m.elem[2][1]+ m.elem[0][1]*m.elem[1][2]*m.elem[2][0]
              -m.elem[0][2]*m.elem[1][1]*m.elem[2][0] - m.elem[0][0]*m.elem[1][2]*m.elem[2][1] -m.elem[1][0]*m.elem[2][2]*m.elem[0][1];
        return det;
    }
    if(k>3)
    {
        for(j=0; j< x->n  ; j++)
        {
            matquadrada A;
            A = MenorComplementar(&m, 0, j);
            double y = Det(&A,k-1);
            det += pow(-1,j)*m.elem[0][j]*y;
        }
        return det;
    }
}

int soma(int k)
{
    if(k==1)
    {
        return 0;
    }
    if(k==2)
    {
        return 1;
    }
    if(k==3)
    {
        return 5;
    }
    if(k>3)
    {
        return k*(soma(k-1)+1);
    }
}

int mult(int k)
{
    if(k==1)
    {
        return 0;
    }
    if(k==2)
    {
        return 2;
    }
    if(k==3)
    {
        return 12;
    }
    if(k>3)
    {
        return k*(mult(k-1)+1);
    }
}


