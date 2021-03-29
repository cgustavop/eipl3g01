/**
 * @file Funcão que diz respeito ao parser
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stack.c"

// gcc -std=gnu11 -Wall -Wextra -pedantic-errors -O parser.c -lm

/**
 * \brief Esta é a função que vai fazer o parse de uma linha
 *
 * @param line A linha que foi lida e da qual se vai fazer o parse
 * @returns O tamanho da stack que foi criada
 */

int parse(char *line) {

    char *delims = " \t\n";

    for (char *token = strtok(line, delims); token != NULL; token = strtok(NULL, delims)) {
        char *sobra;
        long Y; long X;
        long val_i = strtol(token, &sobra, 10);
        char ascii_c;

        switch (token[0]){ 

        // operações básicas

            case '+': 
                Y = pop();
                X = pop();
                push(X += Y);
                break;

            case '-': 
                Y = pop();
                X = pop();
                push(X -= Y);
                break;

            case '*': 
                Y = pop();
                X = pop();
                push(X *= Y);
                break;

            case '/': 
                Y = pop();
                X = pop();
                push(X /= Y);
                break;

        // incrementação e decrementação

            case '(': 
                Y = pop();
                push(Y -= 1);
                break;

            case ')': 
                Y = pop();
                push(Y += 1);
                break;

        // módulo e exponenciação

            case '%': 
                Y = pop();
                X = pop();
                push(X %= Y);
                break;

            case '#': 
                Y = pop();
                X = pop();
                push(pow(X,Y));
                break;

        // tabelas de verdades e bits oriented

            case '&': 
                Y = pop();
                X = pop();
                push(X &= Y);
                break;

            case '|':
                Y = pop();
                X = pop();
                push(X |= Y);
                break;

            case '^': 
                Y = pop();
                X = pop();
                push(X ^= Y);
                break;
            
            case '~': 
                Y = pop();
                push((~ Y));
                break;       

        // conversões do topo da stack || incompleto

            case 'i' : // converter em int
                Y = pop();
                // ...
                push();
                break;

            case 'f' : // converter em double
                Y = pop();
                // ...
                push();
                break;

            case 's' : // converter em string
                Y = pop();
                // ...
                push();
                break; 

            case 'c': // converter em char (ASCII)
                Y = pop();
                ascii_c = Y;
                push(ascii_c);
                break;

        // ler linhas e imprimir linhas || incompleto

            case 'l' : // ler linha abaixo
                fgets();
                break;

            case 't' : // ler todas as linhas guião 3/4
                fgets();
                break;

            case 'p' : // printar topo guião 3/4

                push();
                break;

        // caso default

            default :
                push(val_i);

        }
    }

    print_stack();
    return stack_size();
}