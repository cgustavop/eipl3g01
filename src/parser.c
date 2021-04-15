/**
 * @file Funcão que diz respeito ao parser
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stack.h"


// gcc -std=gnu11 -Wall -Weval_longtra -pedantic-errors -O parser.c -lm

/**
 * \brief Esta é a função que vai fazer o parse de uma linha
 * 
 * Analisa a linha de teval_longto inserida e faz a sua separação em operadores e operandos consoante espaços, tabs ou mudanças de linhas.
 * Interpreta cada token e executa a sua função no conto da linguagem.
 *
 * 
 * @param line A linha que foi lida e da qual se vai fazer o parse
 * @param token Operadores contidos na linha
 * @param sobra Vai guardando elementos da stack que não sofreram nenhuma transformação
 * @val_i 
 * @param ascii_c Usado no operando de conversão ASCII
 * @returns O tamanho da stack resultante
 */


void parse(char *line) {
    Stack stack = create_stack(10240);

    char *delims = " \t\n";

    for (char *token = strtok(line, delims); token != NULL; token = strtok(NULL, delims)) {
         //char *sobra;
         //long val_i = strtol(token, &sobra, 10);

        // void push(Stack stack, const enum stack_type type, ...)
        // void pop(Stack stack, void *p)

        // vars novas
        int val_int, val_int2;
        char val_char, val_char2; 
        long val_long, val_long2;     
        double val_double,  val_double2; 
        void *val_pointer;
        
        /*      
       
        // checks de tipos do top
        // copiar para os casos necessários

        if ((top_type(stack)) == (STACK_CHAR)){
            stack->top = check1;
        } else if ((top_type(stack)) == (STACK_LONG)){
            stack->top = check2;
        } else if ((top_type(stack)) == (STACK_DOUBLE)){
            stack->top = check3;
        } else if ((top_type(stack)) == (STACK_STRING)){
            stack->top = check4;
        } else stack->top = check2; // default é int

        */
        switch (token[0]){ 

        // operações básicas

            case '+':
                switch (top_type(stack)){
                    case (STACK_INT):
                        pop(stack, &val_int);
                        pop(stack, &val_int2);
                        val_int2 += val_int;
                        push(stack, STACK_INT, val_int2);
                        break;

                    case (STACK_LONG):
                        pop(stack, &val_long);
                        pop(stack, &val_long2);
                        val_long2 += val_long;
                        push(stack, STACK_LONG, val_long2);
                        break;

                    case (STACK_DOUBLE):
                        pop(stack, &val_double);
                        pop(stack, &val_double2);
                        val_double2 += val_double;
                        push(stack, STACK_DOUBLE, val_double2);
                        break;

                    case (STACK_CHAR):
                        pop(stack, &val_char);
                        pop(stack, &val_char2);
                        val_char2 += val_char;
                        push(stack, STACK_CHAR, val_char2);
                        break;

                    case (STACK_STRING):
                        push(stack, STACK_STRING, val_pointer);
                        break;

                }
                break;

            case '-': 
                switch (top_type(stack)){
                    case (STACK_INT):
                        pop(stack, &val_int);
                        pop(stack, &val_int2);
                        val_int2 -= val_int;
                        push(stack, STACK_INT, val_int2);
                        break;

                    case (STACK_LONG):
                        pop(stack, &val_long);
                        pop(stack, &val_long2);
                        val_long2 -= val_long;
                        push(stack, STACK_LONG, val_long2);
                        break;

                    case (STACK_DOUBLE):
                        pop(stack, &val_double);
                        pop(stack, &val_double2);
                        val_double2 -= val_double;
                        push(stack, STACK_DOUBLE, val_double2);
                        break;

                    case (STACK_CHAR):
                        pop(stack, &val_char);
                        pop(stack, &val_char2);
                        val_char2 -= val_char;
                        push(stack, STACK_CHAR, val_char2);
                        break;

                    case (STACK_STRING):
                        push(stack, STACK_STRING, val_pointer);
                        break;

                }
                break;

             case '*': 
                switch (top_type(stack)){
                    case (STACK_INT):
                        pop(stack, &val_int);
                        pop(stack, &val_int2);
                        val_int2 *= val_int;
                        push(stack, STACK_INT, val_int2);
                        break;

                    case (STACK_LONG):
                        pop(stack, &val_long);
                        pop(stack, &val_long2);
                        val_long2 *= val_long;
                        push(stack, STACK_LONG, val_long2);
                        break;

                    case (STACK_DOUBLE):
                        pop(stack, &val_double);
                        pop(stack, &val_double2);
                        val_double2 *= val_double;
                        push(stack, STACK_DOUBLE, val_double2);
                        break;

                    case (STACK_CHAR):
                        pop(stack, &val_char);
                        pop(stack, &val_char2);
                        val_char2 *= val_char;
                        push(stack, STACK_CHAR, val_char2);
                        break;

                    case (STACK_STRING):
                        push(stack, STACK_STRING, val_pointer);
                        break;

                }
                break;

            case '/': 
                switch (top_type(stack)){
                    case (STACK_INT):
                        pop(stack, &val_int);
                        pop(stack, &val_int2);
                        val_int2 /= val_int;
                        push(stack, STACK_INT, val_int2);
                        break;

                    case (STACK_LONG):
                        pop(stack, &val_long);
                        pop(stack, &val_long2);
                        val_long2 /= val_long;
                        push(stack, STACK_LONG, val_long2);
                        break;

                    case (STACK_DOUBLE):
                        pop(stack, &val_double);
                        pop(stack, &val_double2);
                        val_double2 /= val_double;
                        push(stack, STACK_DOUBLE, val_double2);
                        break;

                    case (STACK_CHAR):
                        pop(stack, &val_char);
                        pop(stack, &val_char2);
                        val_char2 /= val_char;
                        push(stack, STACK_CHAR, val_char2);
                        break;

                    case (STACK_STRING):
                        push(stack, STACK_STRING, val_pointer);
                        break;

                }
                break;

        // incrementação e decrementação

            case '(': 
                switch (top_type(stack)){
                    case (STACK_INT):
                        pop(stack, &val_int);
                        pop(stack, &val_int2);
                        val_int2 += 1;
                        push(stack, STACK_INT, val_int2);
                        break;

                    case (STACK_LONG):
                        pop(stack, &val_long);
                        pop(stack, &val_long2);
                        val_long2 += 1;
                        push(stack, STACK_LONG, val_long2);
                        break;

                    case (STACK_DOUBLE):
                        pop(stack, &val_double);
                        pop(stack, &val_double2);
                        val_double2 += 1;
                        push(stack, STACK_DOUBLE, val_double2);
                        break;

                    case (STACK_CHAR):
                        pop(stack, &val_char);
                        pop(stack, &val_char2);
                        val_char2 += 1;
                        push(stack, STACK_CHAR, val_char2);
                        break;

                    case (STACK_STRING):
                        push(stack, STACK_STRING, val_pointer);
                        break;
                }
                break;

            case ')': 
                switch (top_type(stack)){
                    case (STACK_INT):
                        pop(stack, &val_int);
                        pop(stack, &val_int2);
                        val_int2 -= 1;
                        push(stack, STACK_INT, val_int2);
                        break;

                    case (STACK_LONG):
                        pop(stack, &val_long);
                        pop(stack, &val_long2);
                        val_long2 -= 1;
                        push(stack, STACK_LONG, val_long2);
                        break;

                    case (STACK_DOUBLE):
                        pop(stack, &val_double);
                        pop(stack, &val_double2);
                        val_double2 -= 1;
                        push(stack, STACK_DOUBLE, val_double2);
                        break;

                    case (STACK_CHAR):
                        pop(stack, &val_char);
                        pop(stack, &val_char2);
                        val_char2 -= 1;
                        push(stack, STACK_CHAR, val_char2);
                        break;

                    case (STACK_STRING):
                        push(stack, STACK_STRING, val_pointer);
                        break;

                }
                break;

        // módulo e exponenciação

            case '%': 
                switch (top_type(stack)){
                    case (STACK_INT):
                        pop(stack, &val_int);
                        pop(stack, &val_int2);
                        val_int2 %= val_int;
                        push(stack, STACK_INT, val_int2);
                        break;

                    case (STACK_LONG):
                        pop(stack, &val_long);
                        pop(stack, &val_long2);
                        val_long2 %= val_long;
                        push(stack, STACK_LONG, val_long2);
                        break;

                    case (STACK_DOUBLE): // não faz double
                        break;

                    case (STACK_CHAR):
                        pop(stack, &val_char);
                        pop(stack, &val_char2);
                        val_char2 %= val_char;
                        push(stack, STACK_CHAR, val_char2);
                        break;

                    case (STACK_STRING):
                        push(stack, STACK_STRING, val_pointer);
                        break;

                }
                break;

            case '#': 
                switch (top_type(stack)){
                    case (STACK_INT):
                        pop(stack, &val_int);
                        pop(stack, &val_int2);
                        val_int2 = pow(val_int2,val_int);
                        push(stack, STACK_INT, val_int2);
                        break;

                    case (STACK_LONG):
                        pop(stack, &val_long);
                        pop(stack, &val_long2);
                        val_long2 = pow(val_long2,val_long);
                        push(stack, STACK_LONG, val_long2);
                        break;

                    case (STACK_DOUBLE): // não faz double
                        break;

                    case (STACK_CHAR):
                        pop(stack, &val_char);
                        pop(stack, &val_char2);
                        val_char2 = pow(val_char2,val_char);
                        push(stack, STACK_CHAR, val_char2);
                        break;

                    case (STACK_STRING):
                        push(stack, STACK_STRING, val_pointer);
                        break;


                }
                break;

        // tabelas de verdades e bits oriented

            case '&': 
                switch (top_type(stack)){
                    case (STACK_INT):
                        pop(stack, &val_int);
                        pop(stack, &val_int2);
                        val_int2 &= val_int;
                        push(stack, STACK_INT, val_int2);
                        break;

                    case (STACK_LONG):
                        pop(stack, &val_long);
                        pop(stack, &val_long2);
                        val_long2 &= val_long;
                        push(stack, STACK_LONG, val_long2);
                        break;

                    case (STACK_DOUBLE): // não faz double
                        break;

                    case (STACK_CHAR):
                        pop(stack, &val_char);
                        pop(stack, &val_char2);
                        val_char2 &= val_char;
                        push(stack, STACK_CHAR, val_char2);
                        break;

                    case (STACK_STRING):
                        push(stack, STACK_STRING, val_pointer);
                        break;

                }
                break;

            case '|':
                switch (top_type(stack)){
                    case (STACK_INT):
                        pop(stack, &val_int);
                        pop(stack, &val_int2);
                        val_int2 |= val_int;
                        push(stack, STACK_INT, val_int2);
                        break;

                    case (STACK_LONG):
                        pop(stack, &val_long);
                        pop(stack, &val_long2);
                        val_long2 |= val_long;
                        push(stack, STACK_LONG, val_long2);
                        break;

                    case (STACK_DOUBLE): // não faz double
                        break;

                    case (STACK_CHAR):
                        pop(stack, &val_char);
                        pop(stack, &val_char2);
                        val_char2 |= val_char;
                        push(stack, STACK_CHAR, val_char2);
                        break;

                    case (STACK_STRING):
                        push(stack, STACK_STRING, val_pointer);
                        break;

                }
                break;

            case '^': 
                switch (top_type(stack)){
                    case (STACK_INT):
                        pop(stack, &val_int);
                        pop(stack, &val_int2);
                        val_int2 ^= val_int;
                        push(stack, STACK_INT, val_int2);
                        break;

                    case (STACK_LONG):
                        pop(stack, &val_long);
                        pop(stack, &val_long2);
                        val_long2 ^= val_long;
                        push(stack, STACK_LONG, val_long2);
                        break;

                    case (STACK_DOUBLE): // não faz double
                        break;

                    case (STACK_CHAR):
                        pop(stack, &val_char);
                        pop(stack, &val_char2);
                        val_char2 ^= val_char;
                        push(stack, STACK_CHAR, val_char2);
                        break;

                    case (STACK_STRING):
                        push(stack, STACK_STRING, val_pointer);
                        break;

                }
                break;
            
            case '~': 
                switch (top_type(stack)){
                    case (STACK_INT):
                        pop(stack, &val_int);
                        val_int = (~val_int);
                        push(stack, STACK_INT, val_int);
                        break;

                    case (STACK_LONG):
                        pop(stack, &val_long);
                        val_long = (~val_long);
                        push(stack, STACK_LONG, val_long);
                        break;

                    case (STACK_DOUBLE): // não faz double
                        break;

                    case (STACK_CHAR):
                        pop(stack, &val_char);
                        val_char = (~val_char);
                        push(stack, STACK_CHAR, val_char);
                        break;

                    case (STACK_STRING):
                        push(stack, STACK_STRING, val_pointer);
                        break;

                }
                break;      
        
            // conversões do topo da stack || incompleto
            
            case 'i' : // Converter o topo da stack num inteiro
                switch (top_type(stack)){
                    case (STACK_INT):
                        pop(stack, &val_int);
                        val_int = (int)(val_int);
                        push(stack, STACK_INT, val_int);
                        break;

                    case (STACK_LONG):
                        pop(stack, &val_long);
                        val_long = (int)(val_long);
                        push(stack, STACK_INT, val_long);
                        break;

                    case (STACK_DOUBLE):
                        pop(stack, &val_double);
                        val_double = (int)(val_int);
                        push(stack, STACK_INT, val_double);
                        break;

                    case (STACK_CHAR):
                        pop(stack, &val_char);
                        val_char = (int)(val_char);
                        push(stack, STACK_INT, val_char);
                        break;

                    case (STACK_STRING):
                        push(stack, STACK_STRING, val_pointer);
                        break;

                }
                break; 

            case 'f' : // Converter o topo da stack num double
                switch (top_type(stack)){
                    case (STACK_INT):
                        pop(stack, &val_int);
                        val_int = (double)(val_int);
                        push(stack, STACK_DOUBLE, val_int);
                        break;

                    case (STACK_LONG):
                        pop(stack, &val_long);
                        val_long = (double)(val_long);
                        push(stack, STACK_DOUBLE, val_long);
                        break;

                    case (STACK_DOUBLE):
                        pop(stack, &val_double);
                        val_double = (double)(val_int);
                        push(stack, STACK_DOUBLE, val_double);
                        break;

                    case (STACK_CHAR):
                        pop(stack, &val_char);
                        val_char = (double)(val_char);
                        push(stack, STACK_DOUBLE, val_char);
                        break;

                    case (STACK_STRING):
                        push(stack, STACK_STRING, val_pointer);
                        break;
                }
                break; 


            case 'c' : // Converter o topo da stack para caracter (ascii)
                switch (top_type(stack)){
                    case (STACK_INT):
                        pop(stack, &val_int);
                        val_int = (char)(val_int);
                        push(stack, STACK_CHAR, val_int);
                        break;

                    case (STACK_LONG):
                        pop(stack, &val_long);
                        val_long = (char)(val_long);
                        push(stack, STACK_CHAR, val_long);
                        break;

                    case (STACK_DOUBLE): // não faz double
                        break;

                    case (STACK_CHAR):
                        pop(stack, &val_char);
                        val_char = (char)(val_char);
                        push(stack, STACK_CHAR, val_char);
                        break;

                    case (STACK_STRING):
                        push(stack, STACK_STRING, val_pointer);
                        break;

                }
                break;
            
            // ler linhas e imprimir linhas || incompleto

            case 'l' : // ler linha abaixo
                //fgets();
                // ..
                break;

            case 't' : // ler todas as linhas guião 3/4
                //fgets();
                //..
                break;
            /*
                case '@' : // Rodar os 3 elementos no topo da stack (inc, apenas feito para 3 longs)
                    pop(stack, &val_int);
                    pop(stack, &val_int2);
                    pop(stack, &val_int3);

                    push(stack, STACK_INT, val_int);
                    push(stack, STACK_INT, val_int3);
                    push(stack, STACK_INT, val_int2);             
                    break;
               
                case 'p' : // printar topo || guião 3/4
                    if ((top_type(stack)) == (STACK_CHAR)){
                        pop(stack, &Outop2);
                        push(stack, STACK_CHAR, Outop2);
                    } else if ((top_type(stack)) == (STACK_LONG)){
                        pop(stack, &Outop3);
                        push(stack, STACK_LONG, Outop3);
                    } else if ((top_type(stack)) == (STACK_DOUBLE)){
                        pop(stack, &Outop4);
                        push(stack, STACK_DOUBLE, Outop4);
                    //} else if ((top_type(stack)) == (STACK_STRING)){
                    //    pop(stack, &Outop);
                    //    push(stack, STACK_STRING, Outop);
                    } else {
                        pop(stack, &Outop);
                        push(stack, STACK_LONG, Outop);
                    }
                    break;

                

                case ';' : // Pop
                    if ((top_type(stack)) == (STACK_CHAR)){
                        pop(stack, &Outop2);
                    } else if ((top_type(stack)) == (STACK_LONG)){
                        pop(stack, &Outop3);
                    } else if ((top_type(stack)) == (STACK_DOUBLE)){
                        pop(stack, &Outop4); 
                    } else
                        pop(stack, &Outop);
                
                    break;

                case '_' : // Duplicar
                    if ((top_type(stack)) == (STACK_CHAR)){
                        pop(stack, &Outop);
                        push(stack, STACK_CHAR, Outop);
                        push(stack, STACK_CHAR, Outop);
                    } else if ((top_type(stack)) == (STACK_LONG)){
                        pop(stack, &Outop);
                        push(stack, STACK_LONG, Outop);
                        push(stack, STACK_LONG, Outop);
                    } else if ((top_type(stack)) == (STACK_DOUBLE)){
                        pop(stack, &Outop);
                        push(stack, STACK_DOUBLE, Outop);
                        push(stack, STACK_DOUBLE, Outop);  
                    } else if ((top_type(stack)) == (STACK_STRING)){
                        pop(stack, &Outop);
                        push(stack, STACK_STRING, Outop);
                        push(stack, STACK_STRING, Outop);
                    } else { 
                        pop(stack, &Outop);
                        push(stack, STACK_LONG, Outop);
                        push(stack, STACK_LONG, Outop);
                    }

                    break; */
                /*
                case '$' : // Copia n-ésimo elemento para o topo da stack, 0 é o topo da stack (inc feito somente para long)
                    int i, n;

                    pop(stack, &val_long);
                    pop(stack, &val_long2);
                    push(stack, STACK_LONG, val_long);
                    push(stack, STACK_LONG, val_long2);

                    for(i=val_long2;i<0;i--){
                       n = Outop;
                       Outop--;                  
                    }

                    pop(stack, &n);
                    push(stack, STACK_LONG, n);
                    break;
           
                case '\\n': // Trocar os dois elementos do topo da stack (inc, apenas feito para 2 longs)
                    pop(stack, &val_long);
                    pop(stack, &val_long2);
                    push(stack, STACK_LONG,val_long);
                    push(stack, STACK_LONG,val_long2);
                    break;
                */
            // caso default

        }
    print_stack(stack);
    stack_size(stack);

}
