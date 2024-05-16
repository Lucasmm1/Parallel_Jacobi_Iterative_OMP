/*
######################################################
# - Caíque Honorio Cardoso 			- NºUSP: 8910222  #
# - Erika Hortência Pereira Cardoso - NºUSP: 10696830 #
# - Gabriel Cazzini Cardoso 		- NºUSP: 12547771 #
# - Lucas Machado Marinho 			- NºUSP: 11916645 #
#######################################################
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#define e 0.0000001

//função para criar valores pseudoaleatorios para a diagonal
long double geraDiagonal(int seed){
    return (seed*13+355);
}

//função para criar valores pseudoaleatorios para o restante da matriz
long double geraNumeros(int seed){
    return seed-20; 
}

//função para criar valores pseudoaleatorios para o vetor B
int geraB(int seed){
    return (13*seed + 7) % 1031;
}

int main(int argc, char *argv[]){
    int seed, semente, n, i, j, k = 0;
    long double erro = 1, soma, erroParcial;
    double wtime1, wtime2;

    //Inicia a contagem de tempo
    wtime1 = omp_get_wtime();

    n = atoi(argv[1]);
    seed = atoi(argv[2]);

    srand(seed);

    //alocação de memória para a Matriz A, Vetor B e o Vetor X;
    long double** A = (long double**)calloc(n, sizeof(long double*));
    for(i=0; i<n; i++){
        A[i] = (long double*)calloc(n, sizeof(long double));
    }

    long double* B = (long double*)calloc(n, sizeof(long double));

    long double* X_atual = (long double*)calloc(n, sizeof(long double));
    long double* X_anterior = (long double*)calloc(n, sizeof(long double));

    //Inicializa as matrizes
    for(i=0;i<n;i++){
        semente = rand() % 100;
        for(j=0; j<n; j++){
            if(i==j){
                A[i][j] = geraDiagonal(semente);
            }else{
                A[i][j] = geraNumeros(semente);
            }
        }
    }

    for(i=0;i<n;i++){
        B[i] = geraB(semente);
        semente = rand() % 100;
    }

    for(i=0;i<n;i++){
        X_atual[i] = 0;
        X_anterior[i] = 0;
    }

    k = 0;
    while(erro > e){
        erroParcial = 0;
        erro = 0;

        //Número máximo de iterações
        if(k>200){
            break;
        }

        //Começa as iterações
        for(i=0;i<n;i++){
            soma=0;
            for(j=0;j<n;j++){
                if(i!=j){
                    soma += (A[i][j]/A[i][i])*X_anterior[j];
                }   
            }
            soma += (B[i]/A[i][i]);
            X_atual[i] = soma;
            //printf("X%d = %Lf ; ",i,X_atual[i]);
        }
        //printf("\n");

        //Calcula o erro
        for(i=0;i<n;i++){
            erroParcial = fabs(X_atual[i] - X_anterior[i]);
            if(erroParcial>erro){
                erro = erroParcial;
            }
            X_anterior[i] = X_atual[i];
        }

        k++;
    }

    //Término da contagem de tempo
    wtime1 = omp_get_wtime() - wtime1;

    //liberando memória
    for(i=0; i<n; i++){
        free(A[i]);
    }
    free(A);
    free(B);
    free(X_anterior);
    free(X_atual);

    printf("O tempo foi de: %lf\n", (wtime1));

    return 0;
}