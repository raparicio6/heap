#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "heap.h"

#define TAMANIO_INICIAL 35
#define CANT_A_MODIFICAR 2

/* Definición del struct heap.
 */
 
struct heap{
	size_t cant;
	void** datos;
	size_t tamanio_arreglo;
	cmp_func_t funcion_comparacion;
};


/* *****************************************************************
 *                    PRIMITIVAS DEL HEAP
 * *****************************************************************/

heap_t *heap_crear(cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if(!heap)
		return NULL;
	
	heap->datos = malloc(sizeof(void*) * TAMANIO_INICIAL);
	if(!heap->datos){
		free(heap);
		return NULL;		
	}
	
	heap->tamanio_arreglo = TAMANIO_INICIAL;	
	heap->cant = 0;
	heap->funcion_comparacion = cmp;
	
	return heap;
}

//Intercambia dos valores en un arreglo.
void swap (void** datos, size_t posicion, size_t pos_padre){
	void* auxiliar = datos[pos_padre];
	datos[pos_padre] = datos[posicion];
	datos[posicion] = auxiliar;
}

size_t heap_cantidad(const heap_t *heap){
	return heap->cant;	
}

bool heap_esta_vacio(const heap_t *heap){
	return (heap->cant == 0);	
}

void *heap_ver_max(const heap_t *heap){
	if (!heap_esta_vacio(heap))	
		return (heap->datos[0]);	
		
	return NULL;
}

//Dado un arreglo y una posicion le aplica upheap al elemento en esa posicion
//en el arreglo.
void upheap(void** datos, void* dato, size_t posicion, cmp_func_t cmp){
	if (posicion == 0)
		return;
		
	size_t pos_padre = (posicion-1) / 2;
	
	int resultado = cmp(datos[posicion],datos[pos_padre]);
	
	if (resultado > 0){ // el primer paramétro es más grande
		swap(datos, posicion, pos_padre);
		upheap(datos, dato, pos_padre, cmp);		
	}	
}

bool heap_encolar(heap_t *heap, void *elem){
	if (!elem)
		return false;
	
	if (heap->cant == heap->tamanio_arreglo){ // redimensión para arriba
		void** datos_nuevo = realloc(heap->datos, sizeof(void*) * heap->tamanio_arreglo * CANT_A_MODIFICAR);
		if (!datos_nuevo)
			return false;
		heap->datos = datos_nuevo;
		heap->tamanio_arreglo = heap->tamanio_arreglo * CANT_A_MODIFICAR;		
	}
	
	heap->datos[heap->cant] = elem;
	upheap(heap->datos, elem, heap->cant, heap->funcion_comparacion);	
	
	heap->cant++;
	
	
	for (int i = 0; i < heap->cant; i++){
		printf("Posicion %d: %d \n", i, *(int*)heap->datos[i]);		
	}
	puts("Heap terminado");
	
	return true;	
}

//Dado un arreglo y una posicion aplica downheap al elemento en esa posicion
//en el arreglo.
void downheap(void **datos, size_t cant, size_t pos, cmp_func_t cmp){
	if(pos >= cant){
		return;
	}
	size_t pos_h_izq = pos*2+1;
	size_t pos_h_der = pos*2+2;
	size_t pos_mayor = pos;
	if((pos_h_izq < cant) && (cmp(datos[pos], datos[pos_h_izq]) < 0)){
		pos_mayor = pos_h_izq;
	}
	if((pos_h_der < cant) && (cmp(datos[pos_mayor], datos[pos_h_der]) < 0)){
		pos_mayor = pos_h_der;
	}
	if(pos_mayor != pos){
		swap(datos, pos, pos_mayor);
		downheap(datos, cant, pos_mayor, cmp);
	}
}

void *heap_desencolar(heap_t *heap){
	if(heap_esta_vacio(heap)){
		return NULL;
	}
	void *dato = heap->datos[0];
	heap->datos[0] = heap->datos[heap->cant-1];
	heap->cant--;
	downheap(heap->datos, heap->cant, 0, heap->funcion_comparacion);
	
	//redimensionar
	if((heap->cant == heap->cant/4) && (heap->cant > TAMANIO_INICIAL)){
		void** datos_nuevo = realloc(heap->datos, (heap->tamanio_arreglo/2) * sizeof(void*));
		if(!datos_nuevo){return false;}
		heap->datos = datos_nuevo;
		heap->tamanio_arreglo = heap->tamanio_arreglo/2;
	}
	
	return dato;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	if (destruir_elemento){
		for (size_t i = 0; i < heap->cant; i++){
			destruir_elemento(heap->datos[i]);			
		}		
	}
	
	free(heap->datos);
	free(heap);	
}

//Dado un arreglo le aplica heapify dejandolo ordenado en forma de heap.
void heapify(void** arreglo, void* dato, size_t posicion, cmp_func_t cmp){
	if (posicion < 0)
		return;
		
	size_t pos_hijo_izq = 2 * posicion + 1;
	size_t pos_hijo_der = 2 * posicion + 2;
		
	if (arreglo[posicion] < arreglo[pos_hijo_izq] || arreglo[posicion] < arreglo[pos_hijo_der]){
		/*if (arreglo[pos_hijo_izq] > arreglo[pos_hijo_der]){ // determino cual de los dos hijos es mayor
			downheap(arreglo, pos_hijo_izq
		}else{			
			downheap(arreglo, pos_hijo_der
		}  creo que no hace falta esto, va dentro del downheap */ 
		
		//downheap(arreglo, arreglo[posicion], posicion, cmp);	comento esta linea para que compile pero sí va!!!
	}
	
	posicion--;
	heapify(arreglo, arreglo[posicion], posicion, cmp);
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
	// tal vez haya que hacer caso borde con cant = 2, chequear luego de terminar por completo la función
	// depende de como se haga el ordenamiento
	size_t ult_pos_no_hoja = (cant-1) / 2 - 1;
	heapify(elementos, elementos[ult_pos_no_hoja], ult_pos_no_hoja, cmp);
	// ya está hecho heap, falta ordenarlo 
		
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){ //no terminado
    heap_t* heap = heap_crear(cmp);
	if (!heap)
		return NULL;
	if(n == 0){return heap;}
	//size_t pos = (n-1)/2-1;
	//heapify(arreglo, arreglo[pos], pos, n, cmp);
	
	heap_encolar(heap, arreglo[0]);
	for(size_t i = 0; i < n; i++){
		if(i*2+1 < n){
			heap_encolar(heap, arreglo[i*2+1]);
		}
		if(i*2+2 < n){
			heap_encolar(heap, arreglo[i*2+2]);
		}
	}
	return heap;
}
