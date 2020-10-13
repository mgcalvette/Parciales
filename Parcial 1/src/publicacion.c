/*
 * publicacion.c
 *
 *  Created on: 9 oct. 2020
 *      Author: Gula
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "publicacion.h"
#include "clientes.h"

static int publi_buscarIndiceVacio(Publicacion* pBuffer,int limite,int*indice);
int i;

int publi_inicializarArray(Publicacion* pBuffer,int limite){
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

int publi_alta(Publicacion* pBuffer,int idCliente,int limite,char* nombreArchivo, int numeroRubro){
    int indice;
    int retorno=-1;
    if(pBuffer!=NULL && limite>0 &&nombreArchivo!= NULL){
        retorno=0;
        if(publi_buscarIndiceVacio(pBuffer,limite,&indice)==0){
            pBuffer[indice].id=publi_obtenerID();
            pBuffer[indice].idCliente=idCliente;
            pBuffer[indice].isEmpty=0;
            pBuffer[indice].numeroRubro=numeroRubro;
            strcpy(pBuffer[indice].nombreArchivo,nombreArchivo);
            pBuffer[indice].estadoPublicacion=1;
            printf("El ID de su publicacion es %d",pBuffer[indice].id);
        }
    }
    return retorno;
}





int publi_ImprimiByIdCliente(Publicacion* pBufferPubli,int limitePubli,Cliente* pBufferCli,int limiteCli,int id,int* indice){
    int i,j;
    int retorno=-1;
    if(pBufferPubli!=NULL&&limitePubli>0&& pBufferCli!= NULL && limiteCli>0){
        for(i=0;i<limitePubli;i++){
            if(pBufferPubli[i].idCliente==id){
                for(j=0;j<limiteCli;j++){
                    if(pBufferPubli[i].idCliente==pBufferCli[i].idCliente && !pBufferPubli[i].isEmpty){
                    	 printf("\nId: %d",pBufferCli[i].idCliente);
                    	 printf("\tNombre: %s",pBufferCli[i].nombre);
                    	 printf("\tApellido: %s",pBufferCli[i].apellido);
                    	 printf("\tCuit: %s",pBufferCli[i].cuit);
                        retorno=0;
                        *indice=i;
                        break;
                    }
                }
            }
        }
    }
    return retorno;
}



int publi_existeId(Publicacion* pBuffer,int limite,int id){
    int i;
    int retorno=-1;
    if(pBuffer!=NULL && limite>0){
        for(i=0;i<limite;i++){
            if(pBuffer[i].id==id && !pBuffer[i].isEmpty){
                retorno=0;
                break;
            }
        }
    }
    return retorno;
}












static int publi_buscarIndiceVacio(Publicacion* pBuffer,int limite,int*indice){
    int i;
    int retorno=-1;
    if(pBuffer!=NULL && limite>0){
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

/** \brief  devuelve un numero de Id que no se repite.
 * \return int Return comienza en 0 y se incrementa en 1
 */
 int publi_obtenerID(){
    static int ID=0;
    return ID++;
}

int publi_PruebaImpresion(Publicacion* pBuffer, int limite)
{
	    int retorno=-1;
	    int i;
	    if(pBuffer!=NULL && limite>0){
	        for(i=0;i<limite;i++){
	            if(pBuffer!= NULL && !pBuffer[i].isEmpty){

	            	printf("\n el nombre es %s", pBuffer[i].nombreArchivo);
	           		printf("\n estado %d",pBuffer[i].estadoPublicacion);
					printf("\n id %d",pBuffer[i].id);
					printf("\n idCliente %d",pBuffer[i].idCliente);
					printf("\n numeroRubro %d",pBuffer[i].numeroRubro);
					printf("\n isEmpty %d",pBuffer[i].isEmpty);
	            	retorno=0;

	            }
	        }
	    }
	    return retorno;

}

int publi_contadorActivas(Publicacion* pBuffer,int limite,int idCliente){
    int i;
    int retorno=0;
    for(i=0;i<limite;i++){
        if(pBuffer[i].idCliente==idCliente&& pBuffer[i].estadoPublicacion== 1 && !pBuffer[i].isEmpty){
            retorno++;
        }
    }
    return retorno;
}

int publi_contadorPausadas(Publicacion* pBuffer,int limite,int idCliente){
    int i;
    int retorno=0;
    for(i=0;i<limite;i++){
        if(pBuffer[i].idCliente==idCliente&& pBuffer[i].estadoPublicacion== 0 && !pBuffer[i].isEmpty){
            retorno++;
        }
    }
    return retorno;
}




int publi_cantidadDeAfichesByIdCliente(Publicacion* pBuffer,int limite,int idCliente){
    int i;
    int cantidad=0;
    if(pBuffer!=NULL&& limite >0){
        for(i=0;i<limite;i++){
            if(!pBuffer[i].isEmpty && pBuffer[i].idCliente==idCliente && pBuffer[i].estadoPublicacion==1){
                cantidad++;
            }
        }
    }
    return cantidad;
}
int publi_cantPublicacionesByRubro(Publicacion *pBuffer,int limite,int numeroRubro){
    int i;
    int cantidad=0;
    if(pBuffer!=NULL&& limite >0){
        for(i=0;i<limite;i++){
            if(!pBuffer[i].isEmpty && pBuffer[i].numeroRubro== numeroRubro){
                cantidad++;
            }
        }
    }
    return cantidad;
}
