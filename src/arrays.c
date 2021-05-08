/**
 * @file logics.c
 * @brief Ficheiro com funções relativas a operações com arrays
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "logics.h"
#include "stack.h"
#include "eval.h"


/**
 * @brief Função que inverte um array
 *
 * Objetivo de auxiliar outras funções que necessitem inverter um array
 *
*/
void inverteArray(STACK *input, STACK *output) { // função auxiliar para inverter um array

    while(input->n_elems > 0){
    DATA x = pop(input);
                            // case quando x é long
            switch(x.type){                                     
                case 1 :                                        
                push_LONG(output, x.LONG);
                break;

                case 2 :                                        
                push_DOUBLE(output, x.DOUBLE);
                break;

                case 4 :                                                                              
                push_CHAR(output, x.CHAR);
                break;

                case 8 :                                        
                push_STRING(output, x.STRING);
                break;

                case 16 :
                push_ARRAY(output, x.ARRAY);                                   
                break;

                case 32 :
                break;
            }
    }
}

/**
 * @brief Função que concatena duas strings
 *
 * Obtendo duas arrays, ou seja duas stacks copia a segunda array e a primeira, invertendo ao fim a primeira array
 *
*/
void concatenar(STACK *pri, STACK *sec){

	STACK *aux = new_stack();

	while(sec->n_elems > 0){
	DATA x = pop(sec);
                            
            switch(x.type){                                     
                case 1 :                       // case quando x é long                                   
                push_LONG(aux, x.LONG);
                break;

                case 2 :                                        
                push_DOUBLE(aux, x.DOUBLE);
                break;

                case 4 :                                                                              
                push_CHAR(aux, x.CHAR);
                break;

                case 8 :                                        
                push_STRING(aux, x.STRING);
                break;

                case 16 :
                push_ARRAY(aux, x.ARRAY);                                   
                break;

                case 32 :
                break;
            }
    }

    inverteArray(aux, pri);
    free(aux);     
}

/**
 * @brief Função range ","
 *
 * Caso seja long fará um array com todos os longs entre 0 e x, não inclusivé (range semelhante ao de Python)
 * Caso seja um array devolve o tamanho do array, ou seja, a quantidade de elementos existentes dentro do array
 *
*/
void range(STACK *s){
    DATA x = pop(s);
    STACK *array = new_stack();
    long i;


    switch(x.type){
        case 1 :
            for (i = 0;i<x.LONG;i++) {
                push_LONG(array, i);
            }
                push_ARRAY(s, array);

            break;

        case 2 :
            break;

        case 4 :
            break;

        case 8 :
            push_LONG(s, strlen(x.STRING));
            break;

        case 16 :              
            push_LONG(s, x.ARRAY->n_elems);
            break;

                case 32 :
                break;
    }
}

/**
 * @brief Função auxiliar para a função do operador S/
 *
 * Separa a string por whitespaces
 *
*/
void whiteSpaces(STACK *stack, char *string) {
    
    char *delims = " \t\n";
    char *cpy = strdup(string);
    STACK *array = new_stack();
                
    for (char *token = strtok(cpy, delims); token != NULL; token = strtok(NULL, delims)) {
            char *aspeado = malloc(sizeof(char)*strlen(string));
            memset(aspeado, '\0', strlen(aspeado));
            memset(aspeado, '\"', 1);
            strcat(strcat(aspeado, token), "\"");
            push_STRING(array, aspeado);
        //push_STRING(array, token);
            
    }
    
    push_ARRAY(stack, array);
}

/**
 * @brief Função auxiliar para a função do operador S/
 *
 * Separa a string por whitespaces caso, o topo da stack seja string
 *
*/
void sspace(STACK *s){
    DATA x = pop(s);

    switch(x.type){
        case 1 :
            break;

        case 2 :
            break;

        case 4 :
            break;

        case 8 :
            whiteSpaces(s, x.STRING);            
            break;

        case 16 :
            break;

                case 32 :
                break;
    }
}

/**
 * @brief Função auxiliar para a função do operador N/
 *
 * Separa a string por newlines
 *
*/
void newLines(STACK *stack, char *string) {

    char *delims = "\n";
    char *cpy = strdup(string);
    STACK *array = new_stack();
                
    for (char *token = strtok(cpy, delims); token != NULL; token = strtok(NULL, delims)) {
            push_STRING(array, token);
    }
    
    push_ARRAY(stack, array);
}

/**
 * @brief Função do operador N/
 *
 * Separa a string por newlines caso o topo da stack seja string
 *
*/
void nspace(STACK *s){
    DATA x = pop(s);

    switch(x.type){
        case 1 :
            break;

        case 2 :
            break;

        case 4 :
            break;

        case 8 :
            newLines(s, x.STRING);
            break;

        case 16 :
            break;

                case 32 :
                break;
    
    }
}

/**
 * @brief Função "=" para arrays 
 *
 * Percorre o array em busca de uma array incluida ou igual à outra
 *
*/
void seek(long n, STACK *array, STACK *stack) {

    STACK arraycpy = *array;
    
    DATA nelem; long i = 0;
    long ne = array->n_elems - n;

    while(i < ne) {
        nelem = pop(&arraycpy); 
        i++;
    }

    switch(nelem.type){
        case 1 :
            push_LONG(stack, nelem.LONG);
            break;

        case 2 :
            push_DOUBLE(stack, nelem.DOUBLE);
            break;

        case 4 :
            push_CHAR(stack, nelem.CHAR);
            break;

        case 8 :
            push_STRING(stack, nelem.STRING);
            break;

        case 16 :
            push_ARRAY(stack, nelem.ARRAY);
            break;

                case 32 :
                break;
    
    }
}

/**
 * @brief Função "=" para strings
 *
 * Percorre a string em busca de uma string incluida ou igual à outra
 *
*/
void seeknstring(long n, char *string, STACK *stack) {

    char *ch = strndup(string + n, 1);
    push_STRING(stack, ch);
    
}

/**
 * @brief Função "<" para arrays 
 *
 * Retira do array os elementos menores do que n valor dado ao longo que percorre o array
 *
*/
void takeXstart(long n, STACK *array) { // n <

    long vezes = (array->n_elems) - n;

    for(long i = 0; i < vezes; i++) {
        pop(array);
    }
}

/**
 * @brief Função ">" para arrays 
 *
 * Retira do array os elementos maiores do que n valor dado enquanto que percorre o array invertendo-a ao fim para obter a stack na mesma ordem
 * 
 * @returns Faz return da stack
*/
STACK *takeXend(long n, STACK *array) { // n >

    STACK *store = new_stack();
    STACK *aux = new_stack();

    for(long i = 0; i < n; i++) {
        
        DATA z = pop(array);

        switch (z.type) {

            case 1 :
                push_LONG(aux, z.LONG);
                break;

            case 2 :
                push_DOUBLE(aux, z.DOUBLE);
                break;

            case 4 :
                push_CHAR(aux, z.CHAR);
                break;

            case 8 :
                push_STRING(aux, z.STRING);
                break;

            case 16 :
                push_ARRAY(aux, z.ARRAY);
                break;

                case 32 :
                break;
        }
    }

    inverteArray(aux, store);
    free(aux); 
    return store;
}

/**
 * @brief Função "*" para arrays 
 *
 * Função que concatena n vezes arrays
 *
*/
void concatvar(STACK *s, long i){
    
    STACK *aux = new_stack();
    STACK aux2 = *s;
    i--;

    while(i > 0){

        aux2 = *s;

        concatenar(aux,&aux2);
        
        i--;
    }

    concatenar(s,aux);
}

/**
 * @brief Função "*" para arrays 
 *
 * Função que concatena n vezes strings
 *
*/
void concatvarstr(char *string, long n) {

    char *copia = strdup(string);

    for(long i = 1; i < n; i++) {

        strcat(string, copia);
    }
}

/**
 * @brief Função "+" para strings
 *
 * Função que concatena strings
 *
 * @returns String concatenada não alterando as originais
*/
char *concatstr(char *dest, char *src) {    // devolve as strings concatenadas sem alterar as originais

    long dsize = sizeof(char)*(strlen(dest)+strlen(src));
    char *d = malloc(dsize);
    
    strncpy (d, dest, dsize - 1);
    d[dsize - 1] = '\0';
    size_t n = strlen (d);
    strncat (d, src, dsize - n);
    
    return d;
}

/**
 * @brief Função que remove o ultimo elemento de um array
 *
 * Função "(" para arrays
 *
*/
void removeUltArray(STACK *stack, STACK *array) {
    
    STACK copia = *array;
    STACK *store = new_stack();
    STACK *store2 = new_stack();

    inverteArray(&copia, store);
    inverteArray(store, store2);

    DATA z = pop(store2);
    push_ARRAY(stack, store2);
    
    switch (z.type) {

            case 1 :
                push_LONG(stack, z.LONG);
                break;

            case 2 :
                push_DOUBLE(stack, z.DOUBLE);
                break;

            case 4 :
                push_CHAR(stack, z.CHAR);
                break;

            case 8 :
                push_STRING(stack, z.STRING);
                break;

            case 16 :
                push_ARRAY(stack, z.ARRAY);
                break;

            case 32 :
                break;
        }
}

/**
 * @brief Função que remove o primeiro elemento de um array
 *
 * Função ")" para arrays
 *
*/
void removePrimArray(STACK *stack, STACK *array) {

    STACK copia = *array;
    STACK *store = new_stack();
    STACK *store2 = new_stack();

    inverteArray(&copia, store);

    DATA z = pop(store);

    inverteArray(store, store2);

    push_ARRAY(stack, store2);

    switch (z.type) {

            case 1 :
                push_LONG(stack, z.LONG);
                break;

            case 2 :
                push_DOUBLE(stack, z.DOUBLE);
                break;

            case 4 :
                push_CHAR(stack, z.CHAR);
                break;

            case 8 :
                push_STRING(stack, z.STRING);
                break;

            case 16 :
                push_ARRAY(stack, z.ARRAY);
                break;

            case 32 :
                break;
        }

}

/**
 * @brief Função que transforma um long num array com um elemento
 *
 * Função que concatena um long a um array vazio 
 *
*/
void concatSTART(DATA elem, STACK* array) { // transforma um long num array com um elemento

    STACK *store = new_stack();
    inverteArray(array, store);

    switch (elem.type) {

            case 1 :
                push_LONG(store, elem.LONG);
                break;

            case 2 :
                push_DOUBLE(store, elem.DOUBLE);
                break;

            case 4 :
                push_CHAR(store, elem.CHAR);
                break;

            case 8 :
                push_STRING(store, elem.STRING);
                break;

            case 16 :
                push_ARRAY(store, elem.ARRAY);
                break;

            case 32 :
                break;
    }

    inverteArray(store, array);
}

<<<<<<< HEAD
/**
 * @brief Função que concatena um elemento de tipo DATA no array
 *
 * Concatena um elemento dado como input em um array
 *
 * @return Faz return à string do array mais o elemento concatenado
*/
=======
void concatEND(DATA elem, STACK* array) { // transforma um long num array com um elemento

    switch (elem.type) {

            case 1 :
                push_LONG(array, elem.LONG);
                break;

            case 2 :
                push_DOUBLE(array, elem.DOUBLE);
                break;

            case 4 :
                push_CHAR(array, elem.CHAR);
                break;

            case 8 :
                push_STRING(array, elem.STRING);
                break;

            case 16 :
                push_ARRAY(array, elem.ARRAY);
                break;

            case 32 :
                break;
        }
}

>>>>>>> 618f59dc37240838aa51246e629db9f242be4390
char *concatAny(DATA elem, char *string) {

    long tamanho = sizeof(char)*(strlen(string)+2);
    char *caratere = malloc(tamanho);
    caratere[tamanho - 1] = '\0';

    switch (elem.type) {

            case 1 :
                caratere[0] = (char)elem.LONG;
                break;

            case 2 :
                caratere[0] = (char)elem.DOUBLE;
                break;

            case 4 :
                caratere[0] = elem.CHAR;
                break;

            case 8 :
                break;

            case 16 :
                break;

            case 32 :
                break;
        }

    strcat(caratere, string);
    return caratere;

}

/**
 * @brief Função que procura substring numa string
 *
 * Percorre a string procurando uma substring de tamanho n
 *
 * @return return = -1 case não exista, caso contrário devolve o indice da substring na string
*/
long strsearch(char *sub, char *string) {
    
    long n = strlen(sub);
    long index = -1;

    for(long i = 0; strcmp(string + i + n - 1, "\0") != 0 ; i++) {
        if (strcmp(strndup(string + i, n), sub) == 0) {
            index = i;
            break;
        }
    }
    
    return index;
}

/**
 * @brief Função que procura um array dentro de um array
 *
 * Percorre o array até encontrar o segundo array, vai printando como string as várias vezes em que o array aparece no input
 * 
*/
void subarray(STACK *stack, char *sub, char *string) {
    
    char *delims = sub;
    char *cpy = strdup(string);
    STACK *array = new_stack();
                
    for (char *token = strtok(cpy, delims); token != NULL; token = strtok(NULL, delims)) {
            push_STRING(array, token);
    }
    
    push_ARRAY(stack, array);
}

// FUNÇÕES LIGADAS A BLOCOS

char *DATAtoSTR(DATA elem) {

    char *string = malloc(sizeof(char)*10240);
    memset(string, '\0', strlen(string));   

    switch (elem.type) {

            case 1 :
                sprintf(string, "%ld", elem.LONG);
                break;

            case 2 :
                sprintf(string, "%f", elem.DOUBLE);
                break;

            case 4 :
                string[0] = elem.CHAR;
                break;

            case 8 :
                string = strdup(elem.STRING);
                break;

            case 16 :
                break;

            case 32 :
                string = strdup(elem.BLOCO);
                break;
        }

    return string;
}

void aplica(STACK *stack, DATA bloco, DATA *vars) {

    DATA elem = pop(stack);
 
    eval(strcat(DATAtoSTR(elem), strndup(bloco.BLOCO + 1, strlen(bloco.BLOCO) - 1)), stack, vars);

}

void map(STACK *stack, DATA bloco, STACK *array, DATA *vars) {


    char *cpy = strdup(bloco.BLOCO); //cópia do bloco
    
    STACK copia = *array;
    STACK *store = new_stack();
    inverteArray(&copia, store);

    long vezes = array->n_elems;

    for (long i = vezes; i > 0; i--){

        DATA elem = pop(store);
        eval(strcat(DATAtoSTR(elem), strndup(cpy + 1, strlen(cpy) - 1)), stack, vars);
        cpy = strdup(bloco.BLOCO);
    }

}

STACK *sortArray (STACK *array) {             // organiza um array de forma crescente

    STACK *sorted = new_stack();            // onde iremos guardar o array rdenado
    STACK cpy = *sorted;                    // cópia do array ordenado para comparar os elementos que lá estão

    DATA a = pop(array);    
    push_LONG(sorted, a.LONG);

    long nelems = array->n_elems;
    
    for (long i = nelems; i > 0; i--) {
        
        cpy = *sorted;
        DATA x = pop(array);
        DATA y = pop(&cpy);

        if (x.LONG < y.LONG) {              // se o que está no array ordenado é maior do que o novo elemento

            y = pop(sorted);                //dá o pop "real" do elemento maior
            push_LONG(sorted, x.LONG);      //insere o novo elemento menor
            push_LONG(sorted, y.LONG);      //coloca o maior de volta ao topo

        } else push_LONG(sorted, x.LONG);    //se o que está no array já é menor do que o que queremos inserir então só insere

    }

    return sorted;

}

void ordena(STACK *stack, DATA bloco, DATA *vars) {

    DATA elem = pop(stack);
    STACK *mapped = new_stack();    // array resultante do map do bloco com o array


    switch (elem.type) {

            case 16:
                map(mapped, bloco, elem.ARRAY, vars);
                push_ARRAY(stack, sortArray(mapped));
                break;

            default:
            break;
        }
}
