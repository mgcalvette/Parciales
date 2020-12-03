/*
 ============================================================================
 Name        : SegundoParcial.c
 Author      : gula
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Linkedlist.h"
#include "Controller.h"
#include "utn.h"

int main(void) {
	setbuf(stdout,NULL);
	int choosenOption;
	LinkedList* listaCliente = ll_newLinkedList();
	LinkedList* listaVenta = ll_newLinkedList();

	controller_loadClientFromText("clientes.txt", listaCliente);
	controller_loadSellFromText("ventas.txt", listaVenta);
	do
	{
		if(!utn_getMenu(&choosenOption, 2, 1, 8))
		{
			switch(choosenOption)
			{
			case 1:
				if(!controller_addClient(listaCliente))
				{
					printf("\nCliente ingresado correctamente!\n");
				}
			break;
			case 2:
				if(!ll_isEmpty(listaCliente))
				{
					if(!controller_sellPoster(listaCliente, listaVenta))
					{
						printf("\nVenta 'a cobrar' cargada exitosamente\n");
					}
				}
				else
				{
					printf("\nNo hay clientes cargados\n");
				}
			break;
			case 3:
				if(!ll_isEmpty(listaCliente) && !ll_isEmpty(listaVenta))
				{
					if(!controller_modifySell(listaCliente, listaVenta))
					{
						printf("\nVenta modificada exitosamente\n");
					}
				}
				else
				{
					printf("\nNo hay cliente y o ventas cargadas\n");
				}
			break;
			case 4:
				if(!ll_isEmpty(listaCliente) && !ll_isEmpty(listaVenta))
				{
					if(!controller_chargePoster(listaCliente, listaVenta))
					{
						printf("\nVenta cobrada con exito\n");
					}
				}
				else
				{
					printf("\nNo hay cliente o ventas cargadas\n");
				}
			break;
			case 5:
				if(!ll_isEmpty(listaCliente) && !ll_isEmpty(listaVenta))
				{
					if(!controller_saveClientsWithChargedPosters(listaCliente, listaVenta))
					{
						printf("\nArchivo guardado con exito\n");
					}
				}
				else
				{
					printf("\nNo hay cliente o ventas cargadas\n");
				}
			break;
			case 6:
				if(!ll_isEmpty(listaCliente) && !ll_isEmpty(listaVenta))
				{
					if(!controller_saveClientsWithUnchargedPosters(listaCliente, listaVenta))
					{
						printf("\nArchivo guardado con exito\n");
					}
				}
				else
				{
					printf("\nNo hay cliente o ventas cargadas\n");
				}
			break;
			case 7:
				if(!ll_isEmpty(listaCliente) && !ll_isEmpty(listaVenta))
				{
					if(!controller_report(listaCliente, listaVenta))
					{
						printf("\nReportes realizados\n");
					}
				}
			break;
			}
		}
	}while(choosenOption!=8);
	controller_saveClientAsText("clientes.txt", listaCliente);
	controller_saveSellsAsText("ventas.txt", listaVenta);
	printf("Gracias");
	return EXIT_SUCCESS;
}
