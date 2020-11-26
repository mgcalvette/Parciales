/*
 ============================================================================
 Name        : menu.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Parser.h"
#include "utn.h"
#include "clientes.h"
#include "controller.h"

void main_menu(int* option);

int main(void)
{
	setbuf(stdout, NULL);
    int option;
    LinkedList* listaClientes;
    int flagTexto=0;
    do{
        main_menu(&option);

        listaClientes = ll_newLinkedList();
        controller_loadFromText("Data.csv",listaClientes);
        printf("\nLos datos fueron cargados correctamente..");

        switch(option)
        {
            case 1:

                 break;
            case 2:
                break;
        }
    }while(option != );

    return 0;
}

void main_menu(int* option){
    printf("\n****************************************************\nMenu:\n\
1. Agregar cliente (modo texto).\n\
2. Salir\n\
*****************************************************/\n");
    utn_getEntero(option,3,"INGRESE UNA OPCION :  ","Error...Ingrese una opion valida",1,3);
}
