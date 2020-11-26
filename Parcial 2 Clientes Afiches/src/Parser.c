/*
 * Parser.c
 *
 *  Created on: 25 nov. 2020
 *      Author: Gula
 */
#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"
#include "LinkedList.h"
#include "clientes.h"



/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
*
 * \param path FILE* puntero al archivo a leer
 * \param pArrayListEmployee LinkedList* puntero a linkedlist
 * \return int 0 todo bien -1 error al guardar
 *
 */
int parser_ClientesFromText(FILE* pFile , LinkedList* this)
{
	int retorno=-1;
		char bufferId[500];
		char bufferNombre[1200];
		char bufferApellido[1200];
		char bufferCuit[1200];
		int flagOnce=0;
		Cliente* pClientes;

		if(pFile != NULL && this != NULL){
			retorno=0;
			do{
				if(!flagOnce){
					fscanf(pFile, "%[^,],%[^,],%[^,],%[^,]%[^\n]\n",bufferId,bufferNombre,bufferApellido,bufferCuit);
					flagOnce=1;
				}
				fscanf(pFile, "%[^,],%[^,],%[^,],%[^,]%[^\n]\n",bufferId,bufferNombre,bufferApellido,bufferCuit);
				pClientes=clientes_newConParametros(bufferId,bufferNombre,bufferApellido,bufferCuit);
				if(pClientes!=NULL){
					ll_add(this,pClientes);
				}else{
					printf("%s,%s,%s,%s\n",bufferId,bufferNombre,bufferApellido,bufferCuit);
					getchar();
				}
			}while(!feof(pFile));
		}
		return retorno;
}



