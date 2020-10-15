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


/** \brief  devuelve un numero de Id que no se repite.
 * \return int Return comienza en 0 y se incrementa en 1
 */
int publi_obtenerID();
/** \brief  Da de alta un nuevo aviso.
 *\param Publicacion puntero al array publicaciones
 *\param int id del cliente
 *\param int limite del array
 *\param char nombre del archivo a cargar (64 caracteres)
 *\param int numero de rubro a definir
 * \return int Return devuelve en 0 si esta todo bien y -1 si algun parametro es incorrecto
 */
int publi_alta(Publicacion* pBuffer,int idCliente,int limite,char* nombreArchivo, int numeroRubro);

int publi_inicializarArray(Publicacion* pBuffer,int limite);

/*Probandola*/
int publi_ImprimiByIdCliente(Publicacion* pBufferPubli,int limitePubli,Cliente* pBufferCli,int limiteCli,int id,int* indice);

int publi_existeId(Publicacion* pBuffer,int limite,int id);

int publi_contadorActivas(Publicacion* pBuffer,int limite,int idCliente);

int publi_contadorPausadas(Publicacion* pBuffer,int limite,int idCliente);

int publi_pruebaImpresion(Publicacion* pBuffer, int limite);

int publi_cantidadDeAfichesByIdCliente(Publicacion* pBuffer,int limite,int idCliente);

int publi_cantPublicacionesByRubro(Publicacion *pBuffer,int limite,int numeroRubro);

int publi_existeIdCliente(Publicacion* pBuffer,int limite,int idCliente);

#endif /* PUBLICACION_H_ */
