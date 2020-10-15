/*
 * informes.c
 *
 *  Created on: 13 oct. 2020
 *      Author: Gula
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utn.h"
#include "clientes.h"
#include "publicacion.h"
#define CANTIDADPUBLICACIONES 5

int inf_impClientesYAvisos(Cliente*pBufferCli,int limiteCli,Publicacion* pBufferPubli,int limitePubli){
    int retorno=-1;
    int i;
    int contadorAvisosActivos;
    if(pBufferCli!=NULL && limiteCli>0 && pBufferPubli!=NULL && pBufferPubli>0){
        for(i=0;i<limiteCli;i++){
            if(!pBufferCli[i].isEmpty){
                printf("\nId: %d\n",pBufferCli[i].idCliente);
                printf("Nombre: %s\n",pBufferCli[i].nombre);
                printf("Apellido: %s\n",pBufferCli[i].apellido);
                printf("Cuit: %s\n",pBufferCli[i].cuit);
                contadorAvisosActivos=publi_contadorActivas(pBufferPubli,CANTIDADPUBLICACIONES,pBufferCli[i].idCliente);
                printf("Avisos activos: %d\n",contadorAvisosActivos);
                retorno=0;
            }
        }
    }
    return retorno;
}



int inf_clienteMasAvisos(Publicacion* pBufferPubli,int limitePubli,Cliente* pBufferCli,int limiteCli){
    int i;
    int auxId;
    int contadorAvisos;
    if(pBufferCli!=NULL && limiteCli>0 && pBufferPubli!=NULL && limitePubli>0){
        for(i=0;i<limiteCli;i++){
            if (!pBufferCli[i].isEmpty){
                if(contadorAvisos<publi_contadorActivas(pBufferPubli,CANTIDADPUBLICACIONES,pBufferCli[i].idCliente)){
                    contadorAvisos=publi_contadorActivas(pBufferPubli,CANTIDADPUBLICACIONES,pBufferCli[i].idCliente);
                    auxId=pBufferCli[i].idCliente;
                }

            }
        }
        if(!contadorAvisos){
            printf("\nNo posee avisos");
        }else{
            printf("\nNumero mayor de avisos: %d",contadorAvisos);
            cli_impById(pBufferCli,limiteCli,auxId);
        }
    }
    return 0;
}

int inf_clienteMasAvisosPausados(Publicacion* pBufferPubli,int limitePubli,Cliente* pBufferCli,int limiteCli){
    int i;
    int auxId;
    int contadorAvisos;
    if(pBufferCli!=NULL && limiteCli>0 && pBufferPubli!=NULL && limitePubli>0){
        for(i=0;i<limiteCli;i++){
            if (!pBufferCli[i].isEmpty){
                if(contadorAvisos<publi_contadorPausadas(pBufferPubli,CANTIDADPUBLICACIONES,pBufferCli[i].idCliente)){
                	contadorAvisos=publi_contadorPausadas(pBufferPubli,CANTIDADPUBLICACIONES,pBufferCli[i].idCliente);
                    auxId=pBufferCli[i].idCliente;
                }

            }
        }
        if(!contadorAvisos){
            printf("\nNo posee publicaciones en Pausa");
        }else{
            printf("\nNumero mayor de publicaciones pausadas: %d",contadorAvisos);
            cli_impById(pBufferCli,limiteCli,auxId);
        }
    }
    return 0;
}
int inf_rubroMasAvisos(Publicacion* pBufferPubli,int limitePubli,Cliente* pBufferCli,int limiteCli){
    int i;
    int auxRubro1;
    int auxRubro2;
    if(pBufferCli!=NULL && limiteCli>0 && pBufferPubli!=NULL && limitePubli>0){
        for(i=0;i<limitePubli;i++)
        {
            if (!pBufferPubli[i].isEmpty && pBufferPubli[i].numeroRubro==1)
            {
            			auxRubro1++;
            }
            if (!pBufferPubli[i].isEmpty && pBufferPubli[i].numeroRubro==2)
            {
            			auxRubro2++;
            }

        }
    }
    if (auxRubro1>auxRubro2){
            	printf("El rubro con mas publicaciones es Arte");
            }
    if (auxRubro1<auxRubro2){
            	printf("El rubro con mas publicaciones es Publicidad");
            }

    return 0;
}
