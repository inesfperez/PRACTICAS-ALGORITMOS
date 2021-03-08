#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define K 1000
/* ===================== ALGORITMOS ORDENACIÃ“N ===================== */

void ord_ins (int v[], int n){

    int i,j,x;

    for (i = 1; i < n; i++ ){

        x = v[i];
        j = i -1;

        while (j>=0 && v[j] > x){

            v[j+1] = v[j];  
            j = j - 1;
        }

        v[j +1] = x;
    }
}

void ord_shell (int v[], int n){

    int incremento = n;
    int i,tmp,j,seguir;


    do{

        incremento = incremento / 2;

        for(i = incremento; i < n; i++ ){

            tmp = v[i];
            j = i;
            seguir = 1;

            while(j-incremento >= 0 && seguir == 1){

                if(tmp < v[j-incremento]){

                    v[j]= v[j-incremento];
                    j = j-incremento;
                }else{

                    seguir = 0;
                }

                v[j] = tmp;
            }
        }    
    }while(incremento != 1);
}

/* =================== FIN ALGORITMOS ORDENACIÃ“N =================== */


/* ===================== CÃ“DIGO AUXILIAR ===================== */

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
}

/* se generan nuÌmeros pseudoaleatorio entre -n y +n */
void aleatorio(int v [], int n) {
    
    int i, m=2*n+1;
    
    for (i=0; i < n; i++){
        
        v[i]=(rand()%m)-n;
    }    
}

void ascendente(int v [], int n) { 

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

double microsegundos() {

    struct timeval t;

    if (gettimeofday(&t, NULL) < 0 )
    	return 0.0;

    return (t.tv_usec + t.tv_sec * 1000000.0);
}
/* ==================== FIN CÃ“DIGO AUXILIAR ================== */

/* =========================== TEST ========================== */

int ordenado(int v[], int n){
    
    int i;
    listar_vector(v,n);

    for(i=0; i< (n-1);i++) {
        
        if (v[i] > v[i+1]){
            
            return 0;
        }

    } 
    return 1;  
}

//Optimizar los test, cÃ³digo repetido
void test1(){
    
    int a[17];

    printf("\n========================= TEST 1 =========================\n");

    printf("InicializaciÃ³n aleatoria\n");
    aleatorio(a,17);
    printf("\n Ordenado? %d\n", ordenado(a,17)); 

    printf("OrdenaciÃ³n por inserciÃ³n\n");
    ord_ins(a,17);
    printf("\n Ordenado? %d\n", ordenado(a,17));  
    
    printf("InicializaciÃ³n descendente\n");
    descendente(a,17);
    printf("\n Ordenado? %d\n", ordenado(a,17)); 

    printf("OrdenaciÃ³n por inserciÃ³n\n");
    ord_ins(a,17);
    printf("\n Ordenado? %d\n", ordenado(a,17));

}


void test2(){
    
    int a[17];

    printf("\n========================= TEST 2 =========================\n");

    printf("InicializaciÃ³n aleatoria\n");
    aleatorio(a,17);
    printf("\n Ordenado? %d\n", ordenado(a,17)); 

    printf("OrdenaciÃ³n por shell\n");
    ord_shell(a,17);
    printf("\n Ordenado? %d\n", ordenado(a,17));  
    
    printf("InicializaciÃ³n descendente\n");
    descendente(a,17);
    printf("\n Ordenado? %d\n", ordenado(a,17)); 

    printf("OrdenaciÃ³n por shell\n");
    ord_shell(a,17);
    printf("\n Ordenado? %d\n", ordenado(a,17));

}

/* ========================= FIN TEST ======================== */

/* ================== VERIFICACIÃ“N COMPLEXIDADE ================= */


void auxVer(void (*f1)(int v[],int n),void(*f2)(int v[],int n),double cotas[]){

    int v[32000],n,i,j,l;
    double t,ta,tb,t1,t2, sub, exacta, sobre;

    /*printf("n\t\tt(n)\t\tt(n)/n^%1.2f\t\tt(n)/n^%1.2f\t\tt(n)/n^%1.2f\n"
	,cotas[0],cotas[1],cotas[2]);*/

    printf("n\t\tt(n)\t\t");
    printf("t(n)/n^%1.2f\t\t",cotas[0]);
    printf("t(n)/n^%1.2f\t\t",cotas[1]);
    printf("t(n)/n^%1.2f\n",cotas[2]);     
    
    for (i = 500; i < 32001; i=i*2){
        n = i;
        (*f2)(v,n);
        ta = microsegundos();
        (*f1)(v,n);
        tb = microsegundos();
        t = tb-ta;
            
            if(t < 500){
                ta = microsegundos();
                for(l=0; l<K; l++){
                    (*f2)(v,n);
                    (*f1)(v,n);
                }
                tb = microsegundos();
                t1 = tb-ta;
                ta = microsegundos();
                for(j=0; j<K; j++){
                    (*f2)(v,n);
                }
                tb = microsegundos();
                t2 = tb - ta;
                t = (t1-t2)/K;
                printf("*");
            }
        
        sub = t/pow(n,cotas[0]);
        exacta = t/pow(n,cotas[1]);
        sobre = t/pow(n,cotas[2]);    
        printf("%d\t\t %f\t %1.8f\t\t %1.8f\t\t %1.8f\n",i,t,sub,exacta,sobre);
    }
}

void verificacionComplexidade(){

    double cota_ins_aleat[3] = {1.8,2.0,2.2};
    double cota_ins_desc[3] = {1.8,2.0,2.2};
    double cota_ins_asc[3] = {0.8,1.0,1.2};
    double cota_shell_aleat[3] = {1,1.2,1.4};
    double cota_shell_desc[3] = {0.9,1.1,1.3};
    double cota_shell_asc[3] = {0.95,1.11,1.3};

    printf("\n================= VERIFICACIÃ“N COMPLEXIDADE ================\n");

    printf("\nOdenaciÃ³n por inserciÃ³n con inicializaciÃ³n aleatorio\n");
    auxVer(ord_ins, aleatorio, cota_ins_aleat);
    printf("\nOdenaciÃ³n por inserciÃ³n con inicializaciÃ³n descendente\n");
    auxVer(ord_ins, descendente, cota_ins_desc);
    printf("\nOdenaciÃ³n por inserciÃ³n con inicializaciÃ³n ascendente\n");
    auxVer(ord_ins,ascendente, cota_ins_asc);
    printf("\nOdenaciÃ³n por shell con inicializaciÃ³n aleatorio\n");
    auxVer(ord_shell,aleatorio, cota_shell_aleat);
    printf("\nOdenaciÃ³n por shell con inicializaciÃ³n descendente\n");
    auxVer(ord_shell, descendente, cota_shell_desc);
    printf("\nOdenaciÃ³n por shell con inicializaciÃ³n ascendente\n");
    auxVer(ord_shell, ascendente, cota_shell_asc);
   
}
/* ================ FIN VERIFICACIÃ“N COMPLEXIDADE =============== */



int main(){
    
    inicializar_semilla();
    test1();
    test2();
    verificacionComplexidade();
    return 0;
}

