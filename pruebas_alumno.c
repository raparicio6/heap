#include "heap.h"
#include "testing.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int comparar(const void* dato1, const void* dato2){
	int resultado;
	
	if (*(int*)dato1 > *(int*)dato2){
		resultado = 1;	
	}else if(*(int*)dato1 < *(int*)dato2){
		resultado = -1;		
	}else{
		resultado = 0;
	}
	
	return resultado;
}

void pruebas_basicas(){
	puts("PRUEBAS BÁSICAS");
	heap_t* heap = heap_crear(comparar);
	print_test("heap fue creado", heap);
	
	int dato1 = 3;  
    int dato2 = 4;
    int dato3 = 2;
    int dato4 = 7;
    int dato5 = -5;
    int dato6 = 10;
    int dato7 = 15;
    int dato8 = 4;
    
    print_test("encolar dato1", heap_encolar(heap, &dato1));
	print_test("encolar dato2", heap_encolar(heap, &dato2));
	print_test("encolar dato3", heap_encolar(heap, &dato3));
	print_test("encolar dato4", heap_encolar(heap, &dato4));
	print_test("encolar dato5", heap_encolar(heap, &dato5));
	print_test("encolar dato6", heap_encolar(heap, &dato6));
	print_test("encolar dato6", heap_encolar(heap, &dato7));
	print_test("encolar dato6", heap_encolar(heap, &dato8));
		
	heap_destruir(heap, NULL);
	
	puts("PRUEBAS heap_crear_arr");
	
	void* arreglo[2] = {&dato1, &dato2};
	
	heap_t* heap2 = heap_crear_arr(arreglo, 2, comparar);
	
	heap_destruir(heap2, NULL);	
}

void prueba_volumen(size_t largo){
	puts("PRUEBA VOLUMEN");
	heap_t* heap = heap_crear(comparar);
	
	size_t* num;
	bool ok = true;
	
	size_t i;	
	for(i = 0; i < largo ; i++){
		num = malloc(sizeof(size_t));
		*num = rand () % largo;
		ok = heap_encolar(heap, num);
		if (!ok) break;
	}
	
	print_test("Prueba heap encolar muchos elementos", ok);
	print_test("Cantidad elementos igual al largo", heap_cantidad(heap) == largo);
		
	heap_destruir(heap, free);	
}

void pruebas_heap_alumno(void){
	pruebas_basicas();
	prueba_volumen(1000);
		
}




