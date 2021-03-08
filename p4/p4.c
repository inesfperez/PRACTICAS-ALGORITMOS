// Inés Faro Pérez

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

#define K 10000
#define TAM_MAX 1280 //1280

typedef int ** matriz;

/* ===================== Cï¿½DIGO AUXILIAR  ===================== */

void listar_matriz(matriz m, int n){
    int i,j;

    for (i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%3d", m[i][j]);
        }
        printf("\n");
    }
}

void inicializar_semilla(){
    srand(time(NULL));
}

double microsegundos(){
    struct timeval t;

    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;

    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void printTempoPequeno(int p){
    if (p==1) {
        printf("*");
    }else{
        printf(" ");
    }
}
/* ==================== FIN Cï¿½DIGO AUXILIAR ================== */


/* ================== FUNCIONES AUXILIARES MATRIZ ================= */

matriz crearMatriz(int n) {
    int i;
    matriz aux;

    if ((aux = malloc(n*sizeof(int *))) == NULL) {
        return NULL;
    }

    for (i=0; i<n; i++) {
        if ((aux[i] = malloc(n*sizeof(int))) == NULL) {
            return NULL;
        }
    }

    return aux;
}

/* Inicializacion pseudoaleatoria [1..TAM_MAX] de un grafo completo
   no dirigido con n nodos, representado por su matriz de adayencia */
void iniMatriz(matriz m, int n) {
    int i, j;
    for (i=0; i<n; i++) {
        for (j=i+1; j<n; j++) {
            m[i][j] = rand() % TAM_MAX + 1;
        }
    }
    for (i=0; i<n; i++) {
        for (j=0; j<=i; j++) {
            if (i==j) {
                m[i][j] = 0;
            }else{
                m[i][j] = m[j][i];
            }
        }
    }
}

void liberarMatriz(matriz m, int n) {

    int i;

    for (i=0; i<n; i++)
        free(m[i]);
    free(m);
}

/* ================== FIN FUNCIONES AUXILIARES MATRIZ  ================= */


/* ================== DIJKSTRA ================= */

void dijkstra(matriz grafo, matriz distancias, int tam) {
    int n,i,j,min,w,t,v=0;

    int *noVisitados = malloc(tam*sizeof(int));

    for (n=0; n<tam; n++) {

        for (i=0; i<tam; i++) {
            noVisitados[i] = 1;
            distancias[n][i] = grafo[n][i];
        }
        noVisitados[n] = 0;

        for (j = 0; j < (tam-2); j++) {

            min = INT_MAX;
            for (t=0; t<tam; t++) {
                if (noVisitados[t]==1) {
                    if(distancias[n][t]<min) {
                        min = distancias[n][t];
                        v = t;
                    }
                }
            }
            noVisitados[v]=0;

            for(w=0; w<tam; w++) {
                if(noVisitados[w]) {
                    if (distancias[n][w] > (distancias[n][v] + grafo[v][w])) {
                        distancias[n][w] = (distancias[n][v] + grafo[v][w]);
                    }
                }
            }
        }
    }
    free(noVisitados);
}

/* ================== FIN DIJKSTRA ================= */

/* ================== TESTS ================= */
void test_1(){

    matriz grafo = crearMatriz(5);
    matriz distancias = crearMatriz(5);

    grafo[0][0]= 0; grafo[0][1]= 1; grafo[0][2]= 8; grafo[0][3]= 4; grafo[0][4]=7;
    grafo[1][0]= 1; grafo[1][1]= 0; grafo[1][2]= 2; grafo[1][3]= 6; grafo[1][4]=5;
    grafo[2][0]= 8; grafo[2][1]= 2; grafo[2][2]= 0; grafo[2][3]= 9; grafo[2][4]=5;
    grafo[3][0]= 4; grafo[3][1]= 6; grafo[3][2]= 9; grafo[3][3]= 0; grafo[3][4]=3;
    grafo[4][0]= 7; grafo[4][1]= 5; grafo[4][2]= 5; grafo[4][3]= 3; grafo[4][4]=0;
    printf("================== TEST 1 ================\n");
    printf("Matriz adxacencia:\n");
    listar_matriz(grafo,5);

    dijkstra(grafo, distancias, 5);
    printf("Matriz distancias:\n");
    listar_matriz(distancias, 5);
    printf("\n");

    liberarMatriz(grafo, 5);
    liberarMatriz(distancias, 5);
}

void test_2(){

    matriz grafo = crearMatriz(4);
    matriz distancias = crearMatriz(4);

    grafo[0][0]= 0;   grafo[0][1]= 1;   grafo[0][2]= 4;   grafo[0][3]= 7;
    grafo[1][0]= 1;   grafo[1][1]= 0;   grafo[1][2]= 2;   grafo[1][3]= 8;
    grafo[2][0]= 4;   grafo[2][1]= 2;   grafo[2][2]= 0;   grafo[2][3]= 3;
    grafo[3][0]= 7;   grafo[3][1]= 8;   grafo[3][2]= 3;   grafo[3][3]= 0;

    printf("================== TEST 2 ================\n");
    printf("Matriz adxacencia:\n");
    listar_matriz(grafo,4);

    dijkstra(grafo, distancias, 4);
    printf("Matriz distancias:\n");
    listar_matriz(distancias, 4);
    printf("\n");

    liberarMatriz(grafo, 4);
    liberarMatriz(distancias, 4);
}
/* ================== FIN TESTS ================= */


/* ================== COTAS ================= */

void cotas_n2(int n,double cotas[]){

    cotas[0]=pow(n,1.8);
    cotas[1]=pow(n,2);
    cotas[2]=pow(n,2.2);
}

void cotas_n(int n, double cotas[]){

    cotas[0]=pow(n,0.8);
    cotas[1] = n;
    cotas[2]= pow(n,1.2);
}

void cotas_nlogn(int n, double cotas[]){

    cotas[0] = n;
    cotas[1] = n*log(n);
    cotas[2] = pow(n,1.4);
}

void cotas_pers(int n, double cotas[]){

    cotas[0]=pow(n,2.7);
    cotas[1]=pow(n,2.85);
    cotas[2]= pow(n,3.0);
}

/* ================== FIN COTAS ================= */


/* ================== VERIFICACIï¿½N COMPLEXIDADE ================= */

void auxVer(void (*fcotas)(int n,double cotas[])){
    int i,j,l, p=0;
    matriz v = crearMatriz(TAM_MAX);
    matriz d = crearMatriz(TAM_MAX);
    double t,ta,tb,t1,t2, sub, exacta, sobre, cotas[3];
    for (i = 10; i < TAM_MAX+1; i=i*2) {
        iniMatriz(v,i);
        ta = microsegundos();
        dijkstra(v,d,i);
        tb = microsegundos();
        t = tb-ta;
        if(t < 500) {
            ta = microsegundos();
            for(l=0; l<K; l++) {
                iniMatriz(v,i);
                dijkstra(v,d,i);
            }
            tb = microsegundos();
            t1 = tb-ta;
            ta = microsegundos();
            for(j=0; j<K; j++) {
                iniMatriz(v,i);
            }
            tb = microsegundos();
            t2 = tb - ta;
            t = (t1-t2)/K;
            p=1;
        }
        (*fcotas)(i,cotas);
        sub = t/cotas[0];
        exacta = t/cotas[1];
        sobre = t/cotas[2];
        printTempoPequeno(p);
        printf("%6d %15f\t\t %1.8f\t\t %1.8f\t\t %1.8f\n"
               ,i,t,sub,exacta,sobre);
        p=0;
    }
    liberarMatriz(v,TAM_MAX); liberarMatriz(d,TAM_MAX);
}

void verificacionComplexidade(){

    int i;

    printf("\n================= VERIFICACION COMPLEXIDADE ================\n");

    for (i = 0; i < 3; i++) {
        printf("\nDijkstra:\n\n");
        printf("%5s%16s%22s%24s%24s\n"
               ,"n","t(n)","t(n)/n^2.7","t(n)/n^2.85","t(n)/n^3.0");
        auxVer(cotas_pers);
    }
}

/* ================== FIN VERIFICACIï¿½N COMPLEXIDADE ================= */


int main(){
    inicializar_semilla();
    test_1();
    test_2();
    verificacionComplexidade();
    printf("\n");
}