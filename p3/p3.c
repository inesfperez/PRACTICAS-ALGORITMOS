// Ines Faro Perez : ines.fperez

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define K 1000
#define TAM 256000

typedef struct {
	int vector[TAM];
	int ultimo;
} monticulo;


/* ===================== CÃ“DIGO AUXILIAR  ===================== */

void listar_vector(int v[], int n){
    int i;
    
    printf("["); 
    for (i = 0; i < n; i++){
        printf("%3d", v[i]); 
    }
    printf("  ]\n"); 
}

void inicializar_semilla(){ 
    srand(time(NULL));
}

void aleatorio(int v [], int n){
    int i, m=2*n+1;
    
    for (i=0; i < n; i++){
        v[i]=(rand()%m)-n;
    }    
}

void ascendente(int v [], int n){ 
    int i;
    
    for (i=0; i < n; i++){ 
        v[i] = i;
    }    
}

void descendente(int v[], int n){ 
    int i;

    for (i = 0; i < n ; i++){
        v[i] = n-i;
    }
}

double microsegundos(){
    struct timeval t;

    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;

    return (t.tv_usec + t.tv_sec * 1000000.0);
} 

void printTempoPequeno(int p){
    if (p==1){
        printf("*");
    }else{
        printf(" ");
    }
}

/* ==================== FIN CÃ“DIGO AUXILIAR ================== */


/* ================== FUNCIONES AUXILIARES MONTÃCULOS ================= */

void hundir(monticulo *m, int i){

    int filloEsq, filloDer, j, temporal;

    do{
        filloEsq = 2*i+1;
        filloDer = 2*i+2;
        j=i;

        if (filloDer <= m->ultimo && m->vector[filloDer] < m->vector[i]){
            i = filloDer;
        }
        
        if (filloEsq <= m->ultimo && m->vector[filloEsq] < m->vector[i]){
            i = filloEsq;
        }

        temporal = m->vector[j];
        m->vector[j] = m->vector[i];
        m->vector[i] = temporal;
    } while (j!=i);
}

void crearMonticulo(int v [], int n, monticulo *m){
	int i;

    for(i = 0; i<n; i++){
        m->vector[i] = v[i];
    }
    
    m->ultimo = n-1;
  
    for(i = (n-1)/2;i>=0;i--){
        hundir(m,i);
    }
}

int consultarMenor(const monticulo *m){
    return m->vector[0];
}

int monticuloVacio(monticulo *m){
	return m->ultimo < 0;
}

void quitarMenor(monticulo *m){
    
    if (monticuloVacio(m)){
        printf("error\n");
    }else{
        m->vector[0] = m->vector[m->ultimo];
        m->ultimo = m->ultimo - 1;
        if (m->ultimo > 0){
            hundir(m,0);
        }
    }
}

/* ================== FIN FUNCIONES AUXILIARES MONTÃCULOS  ================= */


/* ================== ORDENACIÃ“N MONTÃCULOS ================= */

void ordMonticulo(int v[], int n){
	monticulo m;
	int i;

	crearMonticulo(v, n, &m);
		
    for(i = 0; i < n; i++){
        v[i] = consultarMenor(&m);
        quitarMenor(&m);
    }
}

/* ================== FIN ORDENACIÃ“N MONTÃCULOS ================= */


/* ================== TESTS ================= */

void test_crear(){
    monticulo m;
    int vector[] = {1,6,3,8,4,9};
    
    printf("================== TEST CREAR ================\n");
    printf("Vector inicial: \n");
    listar_vector(vector, 6);

    printf("MontÃ­culo esperado:\n[  1  4  3  8  6  9  ]\n");

    printf("MontÃ­culo creado:\n");
    crearMonticulo(vector,6,&m);
    listar_vector(m.vector, 6);
    printf("\n");
}

void test_quitar(){
    monticulo m;
    int vector[] = {1,6,3,8,4,9};

    printf("================== TEST QUITAR ================\n");
    printf("Vector inicial: \n");
    listar_vector(vector, 6);
    
    printf("MontÃ­culo esperado:\n[  3  4  9  8  6  ]\n");
    
    printf("MontÃ­culo sen o menor:\n");
    quitarMenor(&m);
    listar_vector(m.vector, m.ultimo+1);
    printf("\n");

}

void test_ordenar(){
    int vector[] = {1,6,3,8,4,9};
    
    printf("================== TEST CREAR ================\n");
    printf("Vector inicial: \n");
    listar_vector(vector, 6);

    printf("MontÃ­culo esperado:\n[  1  3  4  6  8  9  ]\n");

    printf("MontÃ­culo ordenado:\n");
    ordMonticulo(vector,6);
    listar_vector(vector, 6);
    printf("\n");

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

/* ================== FIN COTAS ================= */


/* ================== VERIFICACIÃ“N COMPLEXIDADE ================= */

void auxVer(void(*ord)(int v[],int n),
            void(*ini)(int v[],int n),
            void(*fcotas)(int n,double cotas[])){ 

    int v[32000],i,j,l, p=0;
    double t,ta,tb,t1,t2, sub, exacta, sobre, cotas[3];
    for (i = 500; i < 32001; i=i*2){
        (*ini)(v,i);
        ta = microsegundos();
        (*ord)(v,i);
        tb = microsegundos();
        t = tb-ta;
            if(t < 500){
                ta = microsegundos();
                for(l=0; l<K; l++){
                    (*ini)(v,i);
                    (*ord)(v,i);
                }
                tb = microsegundos();
                t1 = tb-ta;
                ta = microsegundos();
                for(j=0; j<K; j++){
                    (*ini)(v,i);
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
}

void auxVerCrearMont(){ 
    monticulo m;
    int v[32000],i,j,l,p=0;
    double t,ta,tb,t1,t2, sub, exacta, sobre;
    for (i = 500; i < 32001; i=i*2){
        ascendente(v,i);
        ta = microsegundos();
        crearMonticulo(v,i,&m);
        tb = microsegundos();
        t = tb-ta;
            if(t < 500){
                ta = microsegundos();
                for(l=0; l<K; l++){
                  ascendente(v,i);
                    crearMonticulo(v,i,&m);
                }
                tb = microsegundos();
                t1 = tb-ta;
                ta = microsegundos();
                for(j=0; j<K; j++){
                    ascendente(v,i);
                }
                tb = microsegundos();
                t2 = tb - ta;
                t = (t1-t2)/K;
                p=1;
            }
    
        sub = t/pow(i,0.8);
        exacta = t/i;
        sobre = t/pow(i,1.2);    
        printTempoPequeno(p);
        printf("%6d %15f\t\t %1.8f\t\t %1.8f\t\t %1.8f\n"
               ,i,t,sub,exacta,sobre);
        p=0;
    }
}

void verificacionComplexidade(){

    printf("\n================= VERIFICACIÃ“N COMPLEXIDADE ================\n");

    printf("\nCrear montÃ­culo con inicializaciÃ³n ascendente\n\n");
    printf("%5s%16s%22s%22s%26s\n"
           ,"n","t(n)","t(n)/n^0.8","t(n)/n","t(n)/n^1.2");   
    auxVerCrearMont();
    
    printf("\nOdenaciÃ³n montÃ­culos con inicializaciÃ³n aleatoria\n\n");
    printf("%5s%16s%20s%28s%22s\n"
           ,"n","t(n)","t(n)/n","t(n)/n*log(n)","t(n)/n^1.4"); 
    auxVer(ordMonticulo, aleatorio, cotas_nlogn);
 
    printf("\nOdenaciÃ³n montÃ­culos con inicializaciÃ³n descendente\n\n");
    printf("%5s%16s%20s%28s%22s\n"
           ,"n","t(n)","t(n)/n","t(n)/n*log(n)","t(n)/n^1.4");  
    auxVer(ordMonticulo, descendente, cotas_nlogn);
    
    printf("\nOdenaciÃ³n montÃ­culos con inicializaciÃ³n ascendente\n\n");
    printf("%5s%16s%20s%28s%22s\n"
           ,"n","t(n)","t(n)/n","t(n)/n*log(n)","t(n)/n^1.4");     
    auxVer(ordMonticulo,ascendente, cotas_nlogn);
}    

/* ================== FIN VERIFICACIÃ“N COMPLEXIDADE ================= */


int main(){
    inicializar_semilla();
    test_crear();
    test_quitar();
    test_ordenar();;
    verificacionComplexidade();
    printf("\n");
}