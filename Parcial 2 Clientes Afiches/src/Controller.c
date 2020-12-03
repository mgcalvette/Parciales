#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cliente.h"
#include "Venta.h"
#include "Linkedlist.h"
#include "parser.h"
#include "utn.h"
#include "Controller.h"
#define BUFFER_SIZE 4096

static int controller_searchMaxId(LinkedList* clientList);
static int controller_isCuitRegistered(LinkedList* clientList, char* cuit);
static int controller_findByClientId(LinkedList* clientList, int id, int* index);
static int controller_searchMaxIdSells(LinkedList* sellList);
static int controller_findByIdSells(LinkedList* sellList, int id, int* index);
static int controller_clientMaxPosterQty(LinkedList* clientList, LinkedList* sellList);
static int controller_clientMinPosterQty(LinkedList* clientList, LinkedList* sellList);
static int controller_sellMaxPosterQty(LinkedList* clientList, LinkedList* sellList);

static int controller_findByIdGen(LinkedList* list, int (*pFunc)(void*,int*), int id, int* index);

int controller_loadClientFromText(char* path, LinkedList* clientList)
{
	int retornar=-1;
	FILE* pFile;
	if(path!=NULL && clientList!=NULL)
	{

		pFile = fopen(path, "r");
		if(pFile!=NULL && !parser_clientFromText(pFile, clientList))
		{
			retornar=0;
		}
		else
		{
			printf("\nEl archivo no existe");
		}
		fclose(pFile);
	}
    return retornar;
}

int controller_loadSellFromText(char* path, LinkedList* sellList)
{
	int retornar=-1;
	FILE* pFile;
	if(path!=NULL && sellList!=NULL)
	{

		pFile = fopen(path, "r");
		if(pFile!=NULL && !parser_sellFromText(pFile, sellList))
		{
			retornar=0;
		}
		else
		{
			printf("\nEl archivo no existe");
		}
		fclose(pFile);
	}
    return retornar;
}
//agregar cliente
int controller_addClient(LinkedList* clientList)
{
	int retornar=-1;
	char bufferName[NAME_SIZE];
	char bufferLastName[NAME_SIZE];
	char bufferCuit[CUIT_SIZE];
	int bufferId;
	Cliente* bufferClient;
	if(clientList!=NULL)
	{
		if( !utn_getString("Nombre del cliente: ", "\nERROR!", bufferName, 2, NAME_SIZE) &&
			!utn_getString("Apellido del cliente: ", "\nERROR!", bufferLastName, 2, NAME_SIZE) &&
			!utn_getCuit("Cuit del cliente: ", "\nERROR!", bufferCuit, 2, CUIT_SIZE))
		{
			if(!controller_isCuitRegistered(clientList, bufferCuit))
			{
				retornar=0;
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
	return retornar;
}
//vender afiche
int controller_sellPoster(LinkedList* clientList, LinkedList* sellList)
{
	int retornar=-1;
	int bufferIdClient;
	int bufferIdSell;
	int index;
	int bufferPosterQty;
	char bufferFileName[POSTER_SIZE];
	int bufferZone;
	Venta* bufferSell;
	if(clientList!=NULL)
	{
		if( !controller_print(clientList, cliente_print) && !utn_getInt("\nIngrese el ID del cliente: ", "\nERROR!", &bufferIdClient, 2, 1, 999999) &&
			!controller_findByIdGen(clientList, cliente_getId, bufferIdClient, &index))
		{
			if( !utn_getInt("\nIngrese la cantidad de afiches a vender: ", "\nERROR!", &bufferPosterQty, 2, 1, 99999) &&
				!utn_getStringAlphanumeric("\nIngrese el nombre del archivo: ", "\nERROR!", bufferFileName, 2, POSTER_SIZE) &&
				!utn_getInt("\nIngrese la zona donde se ubicaran los afiches: \n1)CABA\n2)ZONA SUR\n3)ZONA OESTE", "\nERROR!", &bufferZone, 2, 1, 3))
			{
				retornar=0;
				bufferIdSell = controller_searchMaxIdSells(sellList);
				printf("\nID para la venta: %d", bufferIdSell);
				bufferSell = venta_newWithParameters(bufferIdClient, bufferIdSell, bufferPosterQty, bufferFileName, bufferZone, 0);
				ll_add(sellList, bufferSell);
			}
			else
			{
				printf("\nError en la obtencion de datos");
			}
		}
		else
		{
			printf("\nID cliente no existente");
		}
	}
	return retornar;
}

int controller_modifySell(LinkedList* clientList, LinkedList* sellList)
{
	int retornar=-1;
	LinkedList* bufferSellList;
	int bufferId;
	int indexSell;
	int indexClient;
	Cliente* bufferClient;
	Venta* bufferSell;
	int choosenOption;
	int bufferInt;
	char bufferString[POSTER_SIZE];
	if(clientList!=NULL && sellList!=NULL)
	{
		bufferSellList = ll_cloneFilter(sellList, venta_isSold);
		if( !controller_print(bufferSellList, venta_print) && !utn_getInt("\nIngrese el ID de la venta a modificar: ", "\nERROR!", &bufferId, 2, 1, 99999) &&
			!controller_findByIdSells(sellList, bufferId, &indexSell))
		{
			bufferSell = ll_get(sellList, indexSell);
			if(venta_isSold(bufferSell) && !venta_getClientId(bufferSell, &bufferId) && !controller_findByClientId(clientList, bufferId, &indexClient))
			{
				bufferClient = ll_get(clientList, indexClient);
				cliente_print(bufferClient);
				if( !utn_getInt("\n\nIngrese el campo a modificar:\n1)Cantidad de afiches\n2)Nombre del archivo\n3)Zona\n4)Volver atras\n> > OPCION: ", "\nERROR!", &choosenOption, 2, 1, 4))
				{
					switch(choosenOption)
					{
						case 1:
							if( !utn_getInt("\nIngrese la nueva cantidad de afiches: ", "\nERROR!", &bufferInt, 2, 1, 999999) && !venta_setPosterQty(bufferSell, bufferInt))
							{
								ll_set(sellList, indexSell, bufferSell);
								retornar=0;
							}
						break;
						case 2:
							if( !utn_getStringAlphanumeric("\nIngrese el nuevo nombre del archivo: ", "\nERROR!", bufferString, 2, POSTER_SIZE) &&
								!venta_setFileName(bufferSell, bufferString))
							{
								ll_set(sellList, indexSell, bufferSell);
								retornar=0;
							}
						break;
						case 3:
							if( !utn_getInt("\nIngrese la nueva zona: ", "\nERROR!", &bufferInt, 2, 1, 3) && !venta_setZone(bufferSell, bufferInt))
							{
								ll_set(sellList, indexSell, bufferSell);
								retornar=0;
							}
						break;
					}
				}
			}
			else
			{
				printf("\nID de venta 'a cobrar' no encontrado!\n");
			}
		}
		else
		{
			printf("\nID no encontrado!\n");
		}
	}
	return retornar;
}

int controller_chargePoster(LinkedList* clientList, LinkedList* sellList)
{
	int retornar=-1;
		LinkedList* bufferSellList;
		int bufferId;
		int indexSell;
		int indexClient;
		Cliente* bufferClient;
		Venta* bufferSell;
		int bufferInt;
		if(clientList!=NULL && sellList!=NULL)
		{
			bufferSellList = ll_cloneFilter(sellList, venta_isSold);
			if( !controller_print(bufferSellList, venta_print) && !utn_getInt("\nIngrese el ID de la venta a cobrar: ", "\nERROR!", &bufferId, 2, 1, 99999) &&
				!controller_findByIdSells(sellList, bufferId, &indexSell))
			{
				bufferSell = ll_get(sellList, indexSell);
				if(venta_isSold(bufferSell) && !venta_getClientId(bufferSell, &bufferId) && !controller_findByClientId(clientList, bufferId, &indexClient))
				{
					bufferClient = ll_get(clientList, indexClient);
					cliente_print(bufferClient);
					if( !utn_getInt("\n\nDesea cobrar esta venta?\nPresione 1 para cobrar o 2 para volver atras: ", "\nERROR!", &bufferInt, 2, 1, 2) &&
						bufferInt==1 && !venta_setState(bufferSell, 1))
					{
						ll_set(sellList, indexSell, bufferSell);
						retornar=0;
					}
					else
					{
						printf("\nVenta NO cobrada\n");
					}
				}
				else
				{
					printf("\nID no encontrado!\n");
				}
			}
			else
			{
				printf("\nID no encontrado!\n");
			}
		}
		return retornar;
}

int controller_saveClientsWithUnchargedPosters(LinkedList* clientList, LinkedList* sellList)
{
	int retornar=-1;
	Cliente* bufferClient;
	FILE* pFile;
	LinkedList* bufferSellList;
	int counter;
	int bufferId;
	char bufferName[NAME_SIZE];
	char bufferLastName[NAME_SIZE];
	char bufferCuit[CUIT_SIZE];
	if(clientList!=NULL && sellList!=NULL)
	{
		bufferSellList = ll_cloneFilter(sellList, venta_isSold);
		pFile = fopen("a_cobrar.txt", "w");
		if(pFile!=NULL)
		{
			fprintf(pFile, "id,nombre,apellido,cuit,ventas_a_cobrar\n");
			for(int i=0;i<ll_len(clientList);i++)
			{
				bufferClient = ll_get(clientList, i);
				if( !cliente_getId(bufferClient, &bufferId) && !cliente_getName(bufferClient, bufferName) &&
					!cliente_getLastName(bufferClient, bufferLastName) && !cliente_getCuit(bufferClient, bufferCuit))
				{
					if(!ll_reduceInt(bufferSellList, venta_sameId, bufferId ,&counter) && counter!=0)
					{
						fprintf(pFile, "%d,%s,%s,%s,%d\n", bufferId, bufferName, bufferLastName, bufferCuit, counter);
					}
				}
			}
		}
		retornar=0;
		fclose(pFile);
	}
	return retornar;
}

int controller_saveClientsWithChargedPosters(LinkedList* clientList, LinkedList* sellList)
{
	int retornar=-1;
	Cliente* bufferClient;
	FILE* pFile;
	LinkedList* bufferSellList;
	int counter;
	int bufferId;
	char bufferName[NAME_SIZE];
	char bufferLastName[NAME_SIZE];
	char bufferCuit[CUIT_SIZE];
	if(clientList!=NULL && sellList!=NULL)
	{
		bufferSellList = ll_cloneFilter(sellList, venta_isNotSold);
		pFile = fopen("cobrados.txt", "w");
		if(pFile!=NULL)
		{
			fprintf(pFile, "id,nombre,apellido,cuit,ventas_cobradas\n");
			for(int i=0;i<ll_len(clientList);i++)
			{
				bufferClient = ll_get(clientList, i);
				if( !cliente_getId(bufferClient, &bufferId) && !cliente_getName(bufferClient, bufferName) &&
					!cliente_getLastName(bufferClient, bufferLastName) && !cliente_getCuit(bufferClient, bufferCuit))
				{
					if(!ll_reduceInt(bufferSellList, venta_sameId, bufferId ,&counter) && counter!=0)
					{
						fprintf(pFile, "%d,%s,%s,%s,%d\n", bufferId, bufferName, bufferLastName, bufferCuit, counter);
					}
				}
			}
		}
		retornar=0;
		fclose(pFile);
	}
	return retornar;
}

int controller_report(LinkedList* clientList, LinkedList* sellList)
{
	int retornar=-1;
	int choosenOption;
	LinkedList* bufferSellList = ll_cloneFilter(sellList, venta_isNotSold);
	if(clientList!=NULL && sellList!=NULL)
	{
		if( !utn_getInt("\nIngrese una opcion:\n"
						"1-Cliente al que se le ha vendido la MAYOR cantidad de afiches\n"
						"2-Cliente al que se le ha vendido la MENOR cantidad de afiches\n"
						"3-Id cliente con mas afiches vendidos\n"
						"4-Volver.\n\n> > Opcion: ",
						"\nERROR!", &choosenOption, 2, 1, 4))
		{
			switch(choosenOption)
			{
			case 1:
				if(!controller_clientMaxPosterQty(clientList, bufferSellList))
				{
					retornar=0;
				}
			break;
			case 2:
				if(!controller_clientMinPosterQty(clientList, bufferSellList))
				{
					retornar=0;
				}
			break;
			case 3:
				if(!controller_sellMaxPosterQty(clientList, bufferSellList))
				{
					retornar=0;
				}
			break;
			}
		}
	}
	return retornar;
}

static int controller_clientMaxPosterQty(LinkedList* clientList, LinkedList* sellList)
{
	int retornar=-1;
	int maxQty;
	int currentCounter;
	int bufferClientId;
	Cliente* bufferClient;
	if(clientList!=NULL && sellList!=NULL)
	{
		retornar=0;
		for(int i=0;i<ll_len(clientList);i++)
		{
			bufferClient = ll_get(clientList, i);
			if(bufferClient!=NULL && !cliente_getId(bufferClient, &bufferClientId) && !ll_reduceInt(sellList, venta_sameId, bufferClientId, &currentCounter))
			{
				if(i==0 || maxQty<currentCounter)
				{
					maxQty = currentCounter;
				}
			}
		}
		printf("\nEl/los cliente/s con mas afiches es/son: \n");
		for(int i=0;i<ll_len(clientList);i++)
		{
			bufferClient = ll_get(clientList, i);
			if(bufferClient!=NULL && !cliente_getId(bufferClient, &bufferClientId) && !ll_reduceInt(sellList, venta_sameId, bufferClientId, &currentCounter))
			{
				if(currentCounter == maxQty)
				{
					cliente_print(bufferClient);
				}
			}
		}
	}
	return retornar;
}

static int controller_clientMinPosterQty(LinkedList* clientList, LinkedList* sellList)
{
	int retornar=-1;
	int minQty;
	int currentCounter;
	int bufferClientId;
	Cliente* bufferClient;
	if(clientList!=NULL && sellList!=NULL)
	{
		retornar=0;
		for(int i=0;i<ll_len(clientList);i++)
		{
			bufferClient = ll_get(clientList, i);
			if(bufferClient!=NULL && !cliente_getId(bufferClient, &bufferClientId) && !ll_reduceInt(sellList, venta_sameId, bufferClientId, &currentCounter))
			{
				if(i==0 || minQty>currentCounter)
				{
					minQty = currentCounter;
				}
			}
		}
		printf("\nEl/los cliente/s con menos afiches es/son: \n");
		for(int i=0;i<ll_len(clientList);i++)
		{
			bufferClient = ll_get(clientList, i);
			if(bufferClient!=NULL && !cliente_getId(bufferClient, &bufferClientId) && !ll_reduceInt(sellList, venta_sameId, bufferClientId, &currentCounter))
			{
				if(currentCounter == minQty)
				{
					cliente_print(bufferClient);
				}
			}
		}
	}
	return retornar;
}

static int controller_sellMaxPosterQty(LinkedList* clientList, LinkedList* sellList)
{
	int retornar=-1;
	int bufferPosterQty;
	int maxPosterQty;
	int bufferIdSell;
	int bufferIdClient;
	int clientIndex;
	char bufferCuit[CUIT_SIZE];
	Venta* bufferSell;
	Cliente* bufferClient;
	if(clientList!=NULL && sellList!=NULL)
	{
		retornar=0;
		for(int i=0;i<ll_len(sellList);i++)
		{
			bufferSell = ll_get(sellList, i);
			if(bufferSell!=NULL && !venta_getPosterQty(bufferSell, &bufferPosterQty))
			{
				if(i==0 || maxPosterQty<bufferPosterQty)
				{
					maxPosterQty=bufferPosterQty;
				}
			}
		}
		printf("\nLa/las venta/s con mas afiches vendidos es/son: \n");
		for(int i=0;i<ll_len(sellList);i++)
		{
			bufferSell = ll_get(sellList, i);
			if(bufferSell!=NULL && !venta_getPosterQty(bufferSell, &bufferPosterQty))
			{
				if( bufferPosterQty==maxPosterQty && !venta_getClientId(bufferSell, &bufferIdClient) &&
					!venta_getSellId(bufferSell, &bufferIdSell)  && !controller_findByClientId(clientList, bufferIdClient, &clientIndex))
				{
					bufferClient = ll_get(clientList, clientIndex);
					if(bufferClient!=NULL && !cliente_getCuit(bufferClient, bufferCuit))
					{
						printf("\nID venta: %d - Cuit cliente: %s", bufferIdSell, bufferCuit);
					}
				}
			}
		}
	}
	return retornar;
}

/** \brief Busca en la lista de empleados el maximo id y retorna ese valor + 1
 * \param pArrayListEmployee LinkedList*: Puntero a la LinkedList
 * \return el valor del maximo id encontrado + 1 o (-1) si algo salio mal
 */
static int controller_searchMaxId(LinkedList* clientList)
{
	int retornar=-1;
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
		retornar = maxId+1;
	}
	return retornar;
}

static int controller_searchMaxIdSells(LinkedList* sellList)
{
	int retornar=-1;
	int len = ll_len(sellList);
	Venta* bufferSell;
	int id;
	int maxId;
	if(sellList!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			bufferSell = ll_get(sellList, i);
			if(!venta_getSellId(bufferSell, &id))
			{
				if(i==0 || id>maxId)
				{
					maxId = id;
				}
			}
		}
		retornar = maxId+1;
	}
	return retornar;
}

static int controller_findByIdGen(LinkedList* list, int (*pFunc)(void*,int*), int id, int* index)
{
	int retornar=-1;
	int len = ll_len(list);
	int bufferId;
	void* bufferEntity;
	if(list!=NULL && id>0 && index!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			bufferEntity = ll_get(list, i);
			if(!pFunc(bufferEntity, &bufferId) && bufferId == id)
			{
				retornar = 0;
				*index = i;
				break;
			}
		}
	}
	return retornar;
}

static int controller_findByClientId(LinkedList* clientList, int id, int* index)
{
	int retornar=-1;
	int len = ll_len(clientList);
	int bufferId;
	Cliente* bufferClient;
	if(clientList!=NULL && id>0 && index!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			bufferClient = ll_get(clientList, i);
			if(!cliente_getId(bufferClient, &bufferId) && bufferId == id)
			{
				retornar = 0;
				*index = i;
				break;
			}
		}
	}
	return retornar;
}

static int controller_findByIdSells(LinkedList* sellList, int id, int* index)
{
	int retornar=-1;
	int len = ll_len(sellList);
	int bufferId;
	Venta* bufferSell;
	if(sellList!=NULL && id>0 && index!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			bufferSell = ll_get(sellList, i);
			if(!venta_getSellId(bufferSell, &bufferId) && bufferId == id)
			{
				retornar = 0;
				*index = i;
				break;
			}
		}
	}
	return retornar;
}

static int controller_isCuitRegistered(LinkedList* clientList, char* cuit)
{
	int retornar=-1;
	Cliente* bufferClient;
	char bufferCuit[CUIT_SIZE];
	if(clientList!=NULL && cuit!=NULL)
	{
		retornar=0;
		for(int i=0;i<ll_len(clientList);i++)
		{
			bufferClient = ll_get(clientList, i);
			if(bufferClient!=NULL && !cliente_getCuit(bufferClient, bufferCuit))
			{
				if(!strncmp(bufferCuit, cuit,CUIT_SIZE))
				{
					retornar=1;
				}
			}
		}
	}
	return retornar;
}

int controller_print(LinkedList* clientList, int (*pFunc)(void*))
{
	int retornar=-1;
	if(clientList!=NULL && pFunc!=NULL)
	{
		retornar=0;
		ll_map(clientList, pFunc);
		printf("\n---------------------------------------------------------------------\n");
	}
	return retornar;
}

int controller_saveClientAsText(char* path, LinkedList* clientList)
{
	int retornar=-1;
	FILE* pFile;
	Cliente* bufferClient;
	int bufferId;
	char bufferName[NAME_SIZE];
	char bufferLastName[NAME_SIZE];
	char bufferCuit[CUIT_SIZE];
	if(path!=NULL && clientList!=NULL)
	{
		pFile = fopen(path, "w");
		if(pFile!=NULL)
		{
			fprintf(pFile, "id,nombre,apellido,cuit\n");
			retornar=0;
			for(int i=0;i<ll_len(clientList);i++)
			{
				bufferClient = ll_get(clientList, i);
				if(bufferClient!=NULL)
				{
					if( !cliente_getId(bufferClient, &bufferId) && !cliente_getName(bufferClient, bufferName) &&
						!cliente_getLastName(bufferClient, bufferLastName) && !cliente_getCuit(bufferClient, bufferCuit))
					{
						fprintf(pFile, "%d,%s,%s,%s\n",bufferId, bufferName, bufferLastName, bufferCuit);

					}

				}
			}

		}
		fclose(pFile);
	}
	return retornar;
}

int controller_saveSellsAsText(char* path, LinkedList* sellList)
{
	int retornar=-1;
	FILE* pFile;
	Venta* bufferSell;
	int bufferIdSell;
	int bufferIdClient;
	int bufferPosterQty;
	char bufferFileName[POSTER_SIZE];
	int bufferZone;
	int bufferState;
	if(path!=NULL && sellList!=NULL)
	{
		pFile = fopen(path, "w");
		if(pFile!=NULL)
		{
			fprintf(pFile, "id_venta,id_cliente,cantidad_afiches,nombre_archivo,zona,estado\n");
			retornar=0;
			for(int i=0;i<ll_len(sellList);i++)
			{
				bufferSell = ll_get(sellList, i);
				if( !venta_getSellId(bufferSell, &bufferIdSell) && !venta_getClientId(bufferSell, &bufferIdClient) && !venta_getPosterQty(bufferSell, &bufferPosterQty) &&
					!venta_getFileName(bufferSell, bufferFileName) && !venta_getZone(bufferSell, &bufferZone) && !venta_getState(bufferSell, &bufferState))
				{
					fprintf(pFile, "%d,%d,%d,%s,%d,%d\n",bufferIdSell,bufferIdClient,bufferPosterQty,bufferFileName,bufferZone,bufferState);
				}
			}
		}
		fclose(pFile);
	}
	return retornar;
}
