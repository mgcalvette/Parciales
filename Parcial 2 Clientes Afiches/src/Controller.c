/*
 * Controller.c
 *
 *  Created on: 25 nov. 2020
 *      Author: Gula
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Parser.h"
#include "utn.h"
#include "clientes.h"



int controller_loadFromText(char* path , LinkedList* this)
{
    FILE*pArchivo;
    int retorno=-1;
    if(path != NULL && this != NULL){
        pArchivo=fopen(path,"r");
        if(pArchivo != NULL){
        	parser_ClientesFromText(pArchivo,this);
            fclose(pArchivo);
            retorno=0;
        }else{
            printf("No se pudo abrir el archivo.");
        }
    }
    return retorno;
}



int controller_addClient(LinkedList* clientList)
{
	int retorno=-1;
	char bufferName[50];
	char bufferLastName[50];
	char bufferCuit[50];
	int bufferId;
	Cliente* bufferClient;
	if(clientList!=NULL)
	{
		if( !utn_getString("Ingrese nombre del cliente: ", "\nError!", bufferName, 2, 50) &&
			!utn_getString("Ingrese apellido del cliente: ", "\nError!", bufferLastName, 2, 50) &&
			!utn_getCuit("Ingrese cuit del cliente: ", "\nError!!", bufferCuit, 2, 50))
		{
			if(!controller_isCuitRegistered(clientList, bufferCuit))
			{
				retorno=0;
				bufferId = controller_searchMaxId(clientList);
				printf("\nID para el nuevo cliente: %d", bufferId);
				bufferClient = cliente_newWithParameters(bufferId, bufferName, bufferLastName, bufferCuit);
				ll_add(clientList, bufferClient);
			}
			else
			{
				printf("\nCuit ya registrado");
			}
		}
		else
		{
			printf("\nError al tratar de obtener los datos");
		}
	}
	return retorno;
}




static int controller_isCuitRegistered(LinkedList* clientList, char* cuit)
{
	int retorno=-1;
	Cliente* bufferClient;
	char bufferCuit[50];
	if(clientList!=NULL && cuit!=NULL)
	{
		retorno=0;
		for(int i=0;i<ll_len(clientList);i++)
		{
			bufferClient = ll_get(clientList, i);
			if(bufferClient!=NULL && !cliente_getCuit(bufferClient, bufferCuit))
			{
				if(!strncmp(bufferCuit, cuit,50))
				{
					retorno=1;
				}
			}
		}
	}
	return retorno;
}


static int controller_searchMaxId(LinkedList* clientList)
{
	int retorno=-1;
	int len = ll_len(clientList);
	Cliente* bufferClient;
	int id;
	int maxId;
	if(clientList!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			bufferClient = ll_get(clientList, i);
			if(!cliente_getId(bufferClient, &id))
			{
				if(i==0 || id>maxId)
				{
					maxId = id;
				}
			}
		}
		retorno = maxId+1;
	}
	return retorno;
}

/** \brief Guarda un informe en el archivo informe.csv (modo texto).
 *
 * \param path char* nombre del archivo a cargar
 * \param this LinkedList* puntero a linkedlist
 * \return int 0 todo ok -1 hubo un error
 *
 */

/*int controller_saveAsText(char* path , LinkedList* this)
{
    FILE*pArchivo;
    int retorno=-1;
    if(path != NULL && this != NULL){
        pArchivo=fopen(path,"w");
        if(pArchivo != NULL && !save_EmployeesAsText(pArchivo,this)){
            fclose(pArchivo);
            printf("Guardado exitoso");
            getchar();
            retorno=0;
        }else{
            printf("No se pudo abrir el archivo...");
        }
    }
    return retorno;
}*/
