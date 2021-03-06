#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

#define K 1000

/* ====================== ALGORITMOS SUMA ====================== */
int sumaSubMax1(int v[], int n) {
	
	int i, j, estaSuma, sumaMax = 0;
	
	for (i = 0; i < n; i++){
		estaSuma = 0;

		for (j = i; j < n; j++) {
			estaSuma = estaSuma + v[j];
			if (estaSuma > sumaMax) {
				sumaMax = estaSuma;
			}
		}
	}
	return sumaMax;
}

int sumaSubMax2(int v[], int n) { 
	
	int i, estaSuma =0 , sumaMax = 0;

	for (i = 0; i < n; i++) {

		estaSuma = estaSuma + v[i];

		if (estaSuma > sumaMax) { 

			sumaMax = estaSuma;
		} else if (estaSuma < 0) {

			estaSuma = 0;
		}
	}

	return sumaMax;
}
/* ==================== FIN ALGORITMOS SUMA ==================== */


/* ====================== CÃ“DIGO AUXILIAR ====================== */

void listar_vector(int v[], int n){

	int i;

	printf("["); 

	for (i = 0; i < n; i++){

		printf("%5d", v[i]); 
	}

	printf("     ]"); 
}

void inicializar_semilla() {
	srand(time(NULL));
	/* se establece la semilla de una nueva serie de enteros pseudo-aleatorios */ 
} 

void aleatorio(int v [], int n) {

	int i, m=2*n+1;
	for (i=0; i < n; i++)
		v[i] = (rand() % m) - n;
	/* se generan nÃºmeros pseudoaleatorio entre -n y +n */
}

double microsegundos() {

	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
	return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}
/* ===================== FIN CÃ“DIGO AUXILIAR =================== */


/* ============================ TEST =========================== */
void testAuxiliar(int v[], int n){

	int suma1, suma2;
	listar_vector(v,n);

	suma1 = sumaSubMax1(v, n);
	suma2 = sumaSubMax2(v, n);
	
	printf("%17d%15d\n",suma1, suma2);
}

void test1() {

	printf("\n========================= TEST 1 =========================\n");
	printf("%38s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
	
	int a[5] = { -9, 2, -5, -4, 6};
	testAuxiliar(a, 5);

	int b[5] = { 4, 0, 9, 2, 5};
	testAuxiliar(b, 5);

	int c[5] = { -2, -1, -9, -7, -1};
	testAuxiliar(c, 5);

	int d[5] = { 9, -2, 1, -7, -8};
	testAuxiliar(d, 5);

	int e[5] = { 15, -2, -5, -4, 16};
	testAuxiliar(e, 5);

	int f[5] = { 7, -5, 6, 7, -7};
	testAuxiliar(f, 5);

	printf("======================== FIN TEST 1 ========================\n");

}

void test2() {

	int a[5], i; 

	printf("\n========================= TEST 2 =========================\n");
	printf("%38s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");

	for(i = 0; i<6; i++){

		aleatorio(a,5);
		testAuxiliar(a, 5);
	}

	printf("======================== FIN TEST 2 ========================\n");

}
/* ========================== FIN TEST ========================= */


/* ================== VERIFICACIÃ“N COMPLEXIDADE ================= */
void auxVerificacion(int v[], int n, int(*f)(int v[], int n), double cotas[]){			

	double t,ta,tb,t1,t2, sub, exacta, sobre;
	aleatorio(v,n);
	ta = microsegundos();
	(*f)(v,n);
	tb = microsegundos();
	t = tb-ta;

	if(t < 500){
		ta = microsegundos();
		for(int i=0; i<K; i++){
			aleatorio(v,n);
			(*f)(v,n);
		}
		tb = microsegundos();
		t1 = tb-ta;
		ta = microsegundos();
		for(int i=0; i<K; i++){
			aleatorio(v,n);
		}
		tb = microsegundos();
		t2 = tb - ta;
		t = (t1-t2)/K;
		printf("*");
	}

	sub = t/pow(n,cotas[0]);
	exacta = t/pow(n,cotas[1]);
	sobre = t/pow(n,cotas[2]);

	printf("%d\t\t %f\t %f\t\t %f\t\t %f\n",n, t, sub, exacta, sobre);
}

void verificacionComplexidade() {

	int g[32000];
	double cotas1[3] = {1.8,2,2.2};
	double cotas2[3] = {0.8,1,1.2};

	printf("\n================= VERIFICACIÃ“N COMPLEXIDADE ================\n");

	printf("\nSumaSubMax1\n");
	printf("n\t\t t(n)\t\t t(n)/n^%.1f\t\tt(n)/n^%.1f\t\tt(n)/n^%.1f\n",
			cotas1[0], cotas1[1], cotas1[2]);	

	for (int i = 500; i < 32001; i=i*2){

		auxVerificacion(g,i,sumaSubMax1,cotas1);
	}

	printf("\nSumaSubMax2\n");
	printf("n\t\t t(n)\t\t t(n)/n^%.1f\t\tt(n)/n^%.1f\t\tt(n)/n^%.1f\n",
			cotas2[0], cotas2[1], cotas2[2]);	

	for (int i = 500; i < 32001; i=i*2){

		auxVerificacion(g,i,sumaSubMax2,cotas2);
	}

	printf("\n============== FIN VERIFICACIÃ“N COMPLEXIDADE ===============\n");

}
/* ================ FIN VERIFICACIÃ“N COMPLEXIDADE =============== */

int main() {

	inicializar_semilla();
	test1();
	test2();
	verificacionComplexidade();
	return 0;
}