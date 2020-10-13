/*
 * publicacion.h
 *
 *  Created on: 9 oct. 2020
 *      Author: Gula
 */

#ifndef PUBLICACION_H_
#define PUBLICACION_H_
#include "clientes.h"


typedef struct{
    int id;
    int idCliente;
    int numeroRubro;
    char nombreArchivo[64];
    int estadoPublicacion;
    int isEmpty;
}Publicacion;

int publi_alta(Publicacion* pBuffer,int idCliente,int limite,char* nombreArchivo, int numeroRubro);
int publi_obtenerID();
int publi_inicializarArray(Publicacion* pBuffer,int limite);
/*Probandola*/
int publi_ImprimiByIdCliente(Publicacion* pBufferPubli,int limitePubli,Cliente* pBufferCli,int limiteCli,int id,int* indice);
int publi_existeId(Publicacion* pBuffer,int limite,int id);

int publi_PruebaImpresion(Publicacion* pBuffer, int limite);

#endif /* PUBLICACION_H_ */
