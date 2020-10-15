/*
 * clientes.c
 *
 *  Created on: 9 oct. 2020
 *      Author: Gula
 */

#include "clientes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "publicacion.h"




static int cli_buscarIndiceVacio(Cliente* pBuffer,int limite,int*indice);

int cli_inicializarArray(Cliente* pBuffer,int limite){
    int i;
    int retorno=-1;
    if(pBuffer!=NULL && limite>0){
        retorno=0;
        for(i=0;i<limite;i++){
            pBuffer[i].isEmpty=1;
        }
    }
    return retorno;
}
int cli_alta(Cliente* pBuffer,int id,int limite,char* nombre,char* apellido,char*cuit){
    int indice;
    int retorno=-1;
    if(pBuffer!=NULL && limite>0 && apellido!=NULL && nombre !=NULL && cuit != NULL){
        retorno=0;
        if(cli_buscarIndiceVacio(pBuffer,limite,&indice)==0){
            pBuffer[indice].idCliente=id;
            pBuffer[indice].isEmpty=0;
            strcpy(pBuffer[indice].apellido,apellido);
            strcpy(pBuffer[indice].nombre,nombre);
            strcpy(pBuffer[indice].cuit,cuit);
        }
    }
    return retorno;
}
static int cli_buscarIndiceVacio(Cliente* pBuffer,int limite,int*indice){
    int i;
    int retorno=-1;
    if(pBuffer!=NULL && limite>0 && indice!=NULL){
        for(i=0;i<limite;i++){
            if(pBuffer[i].isEmpty==1){
                *indice=i;
                retorno=0;
                break;
            }
        }
    }
    return retorno;
}
int cli_obtenerID(){
    static int ID=0;
    return ID++;
}
int cli_modificarbyId(Cliente* pBuffer,int limite,int id){
    int i;
    char auxNombre [50];
    char auxApellido[50];
    char auxCuit[50];
    int retorno=-1;
    if(pBuffer!=NULL&&limite>0){
        for (i=0;i<limite;i++){
            if(pBuffer[i].idCliente==id&& pBuffer[i].isEmpty==0){
                if(!utn_getLetras(auxNombre,50,3,"\nIngrese el nombre: ","\nError..El nombre debe contener solo letras")&&
                    !utn_getLetras(auxApellido,50,3,"\nIngrese el apellido: ","\nError..El apellido debe contener solo letras")&&
                    !utn_getCuit(auxCuit,50,3,"\nIngrese el cuit: ","\nError...Ingrese el cuit debe ingresarse solo con numero Cant 11")){
                        strcpy(pBuffer[i].apellido,auxApellido);
                        strcpy(pBuffer[i].nombre,auxNombre);
                        strcpy(pBuffer[i].cuit,auxCuit);
                        printf("Modificacion satisfactoria ");
                        getchar();
                        retorno=0;
                }
            }
        }
    }
    return retorno;
}
int cli_eliminarbyId(Cliente* pBuffer,int limite,int idCliente, int idClientePublicacion){
    int i;
    int retorno=-1;
    if(pBuffer!=NULL && limite>0){
        for(i=0;i<limite;i++){
            if(pBuffer[i].isEmpty==0 && pBuffer[i].idCliente==idCliente && idClientePublicacion){
                pBuffer[i].isEmpty=1;
                retorno=0;
                break;
            }
        }
    }
    return retorno;
}
int cli_existeId(Cliente* pBuffer,int limite,int id){
    int i;
    int retorno=-1;
    if(pBuffer!=NULL && limite>0){
        for(i=0;i<limite;i++){
            if(pBuffer[i].idCliente==id && !pBuffer[i].isEmpty){
                retorno=0;
                break;
            }
        }
    }
    return retorno;
}
int cli_impById(Cliente* pBuffer,int limite,int id){
    int i;
    int retorno=-1;
    if(pBuffer!=NULL && limite>0){
        for(i=0;i<limite;i++){
            if(pBuffer[i].idCliente==id){
                printf("\nId: %d",pBuffer[i].idCliente);
                printf("\t Nombre: %s",pBuffer[i].nombre);
                printf("\t Apellido: %s",pBuffer[i].apellido);
                printf("\t Cuit: %s",pBuffer[i].cuit);
                getchar();
                retorno=0;
                break;
            }
        }
    }
    return retorno;
}
int cli_cantidadClientes(Cliente* pBuffer,int limite){
    int i;
    int cantidad=0;
    if(pBuffer!=NULL && limite>0){
        for(i=0;i<limite;i++){
            if(!pBuffer[i].isEmpty){
            cantidad++;
            }
        }
    }
    return cantidad;
}

int cli_listar (Cliente* pBuffer,int limite, int id){
    int i;
    int retorno=-1;
    if(pBuffer!=NULL&&limite>0){
        for(i=0;i<limite;i++){
            if(pBuffer[i].isEmpty==0 && pBuffer[i].idCliente==id){
                retorno=0;
                printf("Nombre: %s",pBuffer[i].nombre);
                printf("\nApellido: %s",pBuffer[i].apellido);
                printf("\nCuit: %s",pBuffer[i].cuit);
                printf("\nID: %d",pBuffer[i].idCliente);
            }
        }
    }
    return retorno;
}

int cli_pruebaImpresion(Cliente* pBuffer, int limite)
{
		int i;
		int retorno=-1;
	    if(pBuffer!=NULL && limite>0){
	        for(i=0;i<limite;i++){
	            if(pBuffer!= NULL && !pBuffer[i].isEmpty){

	            	printf("\n\n Nombre des cliente es: %s", pBuffer[i].nombre);
	           		printf("\n Apellido del cliente es: %s",pBuffer[i].apellido);
					printf("\n El cuit del cliente es: %s",pBuffer[i].cuit);
					printf("\n ID del cliente es: %d",pBuffer[i].idCliente);
					printf("\n isEmpty %d\n",pBuffer[i].isEmpty);
	            	retorno=0;

	            }
	        }
	    }
	    return retorno;

}
