/**
 * @file logics.c
 * @brief Ficheiro com funções relativas a operações lógicas
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "logics.h"
#include "stack.h"
/**
 * @brief E lógico entre dois elementos da stack
 *
 * Inicializada com o token "&"
 */
void E(STACK *s){ // E "&"
      
    DATA x = pop(s);
    DATA y = pop(s);
    
    if(has_type(x, 1) && has_type(y, 1)){
        push_LONG(s, y.LONG & x.LONG);
    }
}
/**
 * @brief OU lógico entre dois elementos da stack
 *
 * Inicializada com o token "|"
 */
void ou(STACK *s){ // OU "|"
      
    DATA x = pop(s);
    DATA y = pop(s);
    
    if(has_type(x, 1) && has_type(y, 1)){
        push_LONG(s, y.LONG | x.LONG);
    }
}
/**
 * @brief OU Exclusivo (aka XOR) entre dois elementos da stack
 *
 * Inicializada com o token "^"
 */
void xor(STACK *s){ // XOR "^"
      
    DATA x = pop(s);
    DATA y = pop(s);
    
    if(has_type(x, 1) && has_type(y, 1)){
        push_LONG(s, y.LONG ^ x.LONG);
    }
}
/**
 * @brief Negação de um elemento da stack
 *
 * Inicializada com o token "~"
 */
void not(STACK *s){ // NOT "~"
    DATA x = pop(s);

    if(has_type(x, 1)){
        push_LONG(s, (~x.LONG));
    }
}
/**
 * @brief Teste de igualdade entre os 2 elementos no topo da stack
 *
 * Inicializada com o token "="
 */
void igual(STACK *s){
    DATA x = pop(s);
    DATA y = pop(s);

    if(has_type(x, 1) && has_type(y, 1)){
        if (x.LONG == y.LONG)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);

    } else if (has_type(x, 2) && has_type(y, 2)){
        if (x.DOUBLE == y.DOUBLE)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);
    
    } else if(has_type(x, 2) && has_type(y, 1)){
        if ((fmod(x.DOUBLE,1) == 0) && ((long)x.DOUBLE == y.LONG))
            push_LONG(s, 1);
        else
            push_LONG(s, 0);
    
    }else if(has_type(y, 2) && has_type(x, 1)){
        if ((fmod(y.DOUBLE,1) == 0) && (x.LONG == (long)y.DOUBLE))
            push_LONG(s, 1);
        else
            push_LONG(s, 0);
    
    } else if (has_type(x, 4) && has_type(y, 4)){
        if (x.CHAR == y.CHAR)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);

    } else if (has_type(x, 8) && has_type(y, 8)){
        if (strcmp(x.STRING,y.STRING) == 0)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);
    } else
        push_LONG(s, 0);
}
/**
 * @brief Verifica se o 2º elemento no topo da stack é menor que o 1º  elemento no topo da stack
 *
 * Inicializada com o token "<"
 */
void menor(STACK *s){ // <
    DATA x = pop(s);
    DATA y = pop(s);

    if (has_type(x, 1) && has_type(y, 1)){
        if (y.LONG < x.LONG)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);

    } else if (has_type(x, 1) && has_type(y, 2)){
        if (y.DOUBLE < x.LONG)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);

    } else if (has_type(x, 2) && has_type(y, 2)){
        if (y.DOUBLE < x.DOUBLE)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);

    } else if (has_type(x, 2) && has_type(y, 1)){
        if (y.LONG < x.DOUBLE)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);

    } else if (has_type(x, 1) && has_type(y, 4)){
        char a = x.LONG;
        if (y.CHAR < a)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);

    } else if (has_type(x, 4) && has_type(y, 1)){
        char a = y.LONG;
        if (a < x.CHAR)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);

    } else if (has_type(x, 4) && has_type(y, 4)){
        if (y.CHAR < x.CHAR)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);
    
    } else if (has_type(x, 4) && has_type(y, 8)){
        if ((char)(strlen(y.STRING)) < x.CHAR )
            push_LONG(s, 1);
        else 
            push_LONG(s, 0);
          
    } else if (has_type(x, 8) && has_type(y, 8)){
        if (strlen(y.STRING) < strlen(x.STRING)) 
            push_LONG(s, 1);
        else
            push_LONG(s ,0);

    } else if (has_type(x, 8) && has_type(y, 4)){
        if ( (y.CHAR) < (char)(strlen(x.STRING)) )
            push_LONG(s, 1);
        else
            push_LONG(s, 0);

    }
}
/**
 * @brief Verifica se o 2º elemento no topo da stack é maior que o 1º  elemento no topo da stack
 *
 * Inicializada com o token ">"
 */
void maior(STACK *s){ // >
    DATA x = pop(s);
    DATA y = pop(s);

    if (has_type(x, 1) && has_type(y, 1)){
        if (y.LONG > x.LONG)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);

    } else if (has_type(x, 1) && has_type(y, 2)){
        if (y.DOUBLE > x.LONG)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);

    } else if (has_type(x, 2) && has_type(y, 2)){
        if (y.DOUBLE > x.DOUBLE)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);

    } else if (has_type(x, 2) && has_type(y, 1)){
        if (y.LONG > x.DOUBLE)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);

    } else if (has_type(x, 4) && has_type(y, 4)){
        if (y.CHAR > x.CHAR)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);
    
    } else if (has_type(x, 4) && has_type(y, 8)){
        if ((char)(strlen(y.STRING)) > x.CHAR )
            push_LONG(s, 1);
        else 
            push_LONG(s, 0);
          
    } else if (has_type(x, 8) && has_type(y, 8)){
        if (strlen(y.STRING) > strlen(x.STRING)) 
            push_LONG(s, 1);
        else
            push_LONG(s ,0);

    } else if (has_type(x, 8) && has_type(y, 4)){
        if ( (y.CHAR) > (char)(strlen(x.STRING)) )
            push_LONG(s, 1);
        else
            push_LONG(s, 0);

    }
}
/**
 * @brief Negação do elemento no topo da stack
 *
 * Inicializada com o token "!"
 */
void nono(STACK *s){ // !
    DATA x = pop(s);

    if (has_type(x, 1)) {
        if (x.LONG == 0)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);

    } else if (has_type(x, 2)) {
        if (x.DOUBLE == 0)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);

    } else if (has_type(x, 4)) {
        if (x.CHAR == (char)0)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);

    } else if (has_type(x, 8)){
        if (strcmp(x.STRING,"0") == 0)
            push_LONG(s, 1);
        else
            push_LONG(s, 0);
    }
}
/**
 * @brief E lógico entre dois elementos da stack
 *
 * Inicializada com o token "e&"
 */
void eE(STACK *s){
    DATA x = pop(s);
    DATA y = pop(s);

    if (has_type(y, 1) && y.LONG == 0)
        push_LONG(s, 0);
    else if (has_type(x, 1) && x.LONG == 0)
        push_LONG(s, 0);

    else if (has_type(x, 1) && has_type(y, 1)){
        if (y.LONG > x.LONG)
            push_LONG(s, y.LONG);
        else
            push_LONG(s, x.LONG);

    } else if (has_type(x, 1) && has_type(y, 2)){
        if (y.DOUBLE > x.LONG)
            push_DOUBLE(s, y.DOUBLE);
        else
            push_LONG(s, x.LONG);

    } else if (has_type(x, 2) && has_type(y, 2)){
        if (y.DOUBLE > x.DOUBLE)
            push_DOUBLE(s, y.DOUBLE);
        else
            push_DOUBLE(s, x.DOUBLE);

    } else if (has_type(x, 2) && has_type(y, 1)){
        if (y.LONG > x.DOUBLE)
            push_LONG(s, y.LONG);
        else
            push_DOUBLE(s, x.DOUBLE);

    } else if (has_type(x, 4) && has_type(y, 4)){
        if (y.CHAR > x.CHAR)
            push_CHAR(s, y.CHAR);
        else
            push_CHAR(s, x.CHAR);
    
    } else if (has_type(x, 4) && has_type(y, 8)){
        if ((char)(strlen(y.STRING)) > x.CHAR )
            push_STRING(s, y.STRING);
        else 
            push_CHAR(s, x.CHAR);
          
    } else if (has_type(x, 8) && has_type(y, 8)){
        if (strlen(y.STRING) > strlen(x.STRING)) 
            push_STRING(s, y.STRING);
        else
            push_STRING(s , x.STRING);

    } else if (has_type(x, 8) && has_type(y, 4)){
        if ( (y.CHAR) > (char)(strlen(x.STRING)) )
            push_CHAR(s, y.CHAR);
        else
            push_STRING(s, x.STRING);

    } else {
        if(has_type(y, 1))
            push_LONG(s, y.LONG);
        else if(has_type(y, 2))
            push_DOUBLE(s, y.DOUBLE);
        else if(has_type(y, 4))
            push_CHAR(s, y.CHAR);
        else if(has_type(y, 8))
            push_STRING(s, y.STRING); 
    }

}
/**
 * @brief OU lógico entre dois elementos da stack
 *
 * Inicializada com o token "e|"
 */
void eOU(STACK *s){
    DATA x = pop(s);
    DATA y = pop(s);

    if (has_type(y, 1) && y.LONG == 0 && has_type(x, 1) && x.LONG == 0)
        push_LONG(s, 0);
    else if (has_type(y, 1) && y.LONG == 0){
        if(has_type(x, 1))
            push_LONG(s, x.LONG);
        else if(has_type(x, 2))
            push_DOUBLE(s, x.DOUBLE);
        else if(has_type(x, 4))
            push_CHAR(s, x.CHAR);
        else if(has_type(x, 8))
            push_STRING(s, x.STRING);
    }
    else if (has_type(x, 1) && x.LONG == 0){
        if(has_type(y, 1))
            push_LONG(s, y.LONG);
        else if(has_type(y, 2))
            push_DOUBLE(s, y.DOUBLE);
        else if(has_type(y, 4))
            push_CHAR(s, y.CHAR);
        else if(has_type(y, 8))
            push_STRING(s, y.STRING);
    }
    else {
       if(has_type(y, 1))
            push_LONG(s, y.LONG);
        else if(has_type(y, 2))
            push_DOUBLE(s, y.DOUBLE);
        else if(has_type(y, 4))
            push_CHAR(s, y.CHAR);
        else if(has_type(y, 8))
            push_STRING(s, y.STRING); 
    }

}
/**
 * @brief Coloca o menor de 2 valores no topo da stack
 *
 * Inicializada com o token "e<"
 */
void emenor(STACK *s){
    DATA x = pop(s);
    DATA y = pop(s);

    if (has_type(x, 1) && has_type(y, 1)){
        if (y.LONG < x.LONG)
            push_LONG(s, y.LONG);
        else
            push_LONG(s, x.LONG);

    } else if (has_type(x, 1) && has_type(y, 2)){
        if (y.DOUBLE < x.LONG)
            push_DOUBLE(s, y.DOUBLE);
        else
            push_LONG(s, x.LONG);

    } else if (has_type(x, 2) && has_type(y, 2)){
        if (y.DOUBLE < x.DOUBLE)
            push_DOUBLE(s, y.DOUBLE);
        else
            push_DOUBLE(s, x.DOUBLE);

    } else if (has_type(x, 2) && has_type(y, 1)){
        if (y.LONG < x.DOUBLE)
            push_LONG(s, y.LONG);
        else
            push_DOUBLE(s, x.DOUBLE);

    } else if (has_type(x, 4) && has_type(y, 4)){
        if (y.CHAR < x.CHAR)
            push_CHAR(s, y.CHAR);
        else
            push_CHAR(s, x.CHAR);
    
    } else if (has_type(x, 4) && has_type(y, 8)){
        if ((char)(strlen(y.STRING)) < x.CHAR )
            push_STRING(s, y.STRING);
        else 
            push_CHAR(s, x.CHAR);
          
    } else if (has_type(x, 8) && has_type(y, 8)){
        if (strlen(y.STRING) < strlen(x.STRING)) 
            push_STRING(s, y.STRING);
        else
            push_STRING(s , x.STRING);

    } else if (has_type(x, 8) && has_type(y, 4)){
        if ( (y.CHAR) < (char)(strlen(x.STRING)) )
            push_CHAR(s, y.CHAR);
        else
            push_STRING(s, x.STRING);

    }
}
/**
 * @brief Coloca o maior de 2 valores no topo da stack
 *
 * Inicializada com o token "e>"
 */
void emaior(STACK *s){
    DATA x = pop(s);
    DATA y = pop(s);

    if (has_type(x, 1) && has_type(y, 1)){
        if (y.LONG > x.LONG)
            push_LONG(s, y.LONG);
        else
            push_LONG(s, x.LONG);

    } else if (has_type(x, 1) && has_type(y, 2)){
        if (y.DOUBLE > x.LONG)
            push_DOUBLE(s, y.DOUBLE);
        else
            push_LONG(s, x.LONG);

    } else if (has_type(x, 2) && has_type(y, 2)){
        if (y.DOUBLE > x.DOUBLE)
            push_DOUBLE(s, y.DOUBLE);
        else
            push_DOUBLE(s, x.DOUBLE);

    } else if (has_type(x, 2) && has_type(y, 1)){
        if (y.LONG > x.DOUBLE)
            push_LONG(s, y.LONG);
        else
            push_DOUBLE(s, x.DOUBLE);

    } else if (has_type(x, 4) && has_type(y, 4)){
        if (y.CHAR > x.CHAR)
            push_CHAR(s, y.CHAR);
        else
            push_CHAR(s, x.CHAR);
    
    } else if (has_type(x, 4) && has_type(y, 8)){
        if ((char)(strlen(y.STRING)) > x.CHAR )
            push_STRING(s, y.STRING);
        else 
            push_CHAR(s, x.CHAR);
          
    } else if (has_type(x, 8) && has_type(y, 8)){
        if (strlen(y.STRING) > strlen(x.STRING)) 
            push_STRING(s, y.STRING);
        else
            push_STRING(s , x.STRING);

    } else if (has_type(x, 8) && has_type(y, 4)){
        if ( (y.CHAR) > (char)(strlen(x.STRING)) )
            push_CHAR(s, y.CHAR);
        else
            push_STRING(s, x.STRING);

    }
}
