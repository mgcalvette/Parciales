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
                printf("\nId: %d",pBufferCli[i].idCliente);
                printf("\tNombre: %s",pBufferCli[i].nombre);
                printf("\tApellido: %s",pBufferCli[i].apellido);
                printf("\tCuit: %s",pBufferCli[i].cuit);
                contadorAvisosActivos=publi_contadorActivas(pBufferPubli,CANTIDADPUBLICACIONES,pBufferCli[i].idCliente);
                printf("\t Avisos activos: %d",contadorAvisosActivos);
                retorno=0;
            }
        }
    }
    return retorno;
}



int inf_clienteMasventas(Publicacion* pBufferPubli,int limitePubli,Cliente* pBufferCli,int limiteCli){
    int i;
    int auxMayorId;
    int auxMaxVentas;
    int flag=0;
    if(pBufferCli!=NULL && limiteCli>0 && pBufferPubli!=NULL && limitePubli>0){
        for(i=0;i<limiteCli;i++){
            if (!pBufferCli[i].isEmpty){
                if(!flag || auxMaxVentas<publi_contadorActivas(pBufferPubli,CANTIDADPUBLICACIONES,pBufferCli[i].idCliente)){
                    flag=1;
                    auxMaxVentas=publi_contadorActivas(pBufferPubli,CANTIDADPUBLICACIONES,pBufferCli[i].idCliente);
                    auxMayorId=pBufferCli[i].idCliente;
                }

            }
        }
        if(!auxMaxVentas){
            printf("\nNo posee ventas");
        }else{
            printf("\nNumero mayor de ventas: %d",auxMaxVentas);
            cli_impById(pBufferCli,limiteCli,auxMayorId);
        }
    }
    return 0;
}

int inf_clienteMasAvisosPausados(Publicacion* pBufferPubli,int limitePubli,Cliente* pBufferCli,int limiteCli){
    int i;
    int auxMayorId;
    int auxMaxPausadas;
    int flag=0;
    if(pBufferCli!=NULL && limiteCli>0 && pBufferPubli!=NULL && limitePubli>0){
        for(i=0;i<limiteCli;i++){
            if (!pBufferCli[i].isEmpty){
                if(!flag || auxMaxPausadas<publi_contadorPausadas(pBufferPubli,CANTIDADPUBLICACIONES,pBufferCli[i].idCliente)){
                    flag=1;
                    auxMaxPausadas=publi_contadorPausadas(pBufferPubli,CANTIDADPUBLICACIONES,pBufferCli[i].idCliente);
                    auxMayorId=pBufferCli[i].idCliente;
                }

            }
        }
        if(!auxMaxPausadas){
            printf("\nNo posee publicaciones en Pausa");
        }else{
            printf("\nNumero mayor de publicaciones pausadas: %d",auxMaxPausadas);
            cli_impById(pBufferCli,limiteCli,auxMayorId);
        }
    }
    return 0;
}
int inf_rubroMasAvisos(Publicacion* pBufferPubli,int limitePubli,Cliente* pBufferCli,int limiteCli){
    int i;
    int auxMasAvisos;
    int flag=0;
    if(pBufferCli!=NULL && limiteCli>0 && pBufferPubli!=NULL && limitePubli>0){
        for(i=0;i<limiteCli;i++){
            if (!pBufferCli[i].isEmpty){
                if(!flag || auxMasAvisos<publi_cantPublicacionesByRubro(pBufferPubli,CANTIDADPUBLICACIONES,pBufferPubli[i].numeroRubro)){
                    flag=1;
                    auxMasAvisos=publi_contadorPausadas(pBufferPubli,CANTIDADPUBLICACIONES,pBufferCli[i].idCliente);
                }

            }
        }
        if(!auxMasAvisos){
            printf("\nNo posee publicaciones en este rubro");
        }else{
            printf("\nNumero mayor de publicaciones pausadas: %d",auxMasAvisos);
        	 }
    }
    return 0;
}
