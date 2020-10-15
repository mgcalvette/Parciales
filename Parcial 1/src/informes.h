/*
 * informes.h
 *
 *  Created on: 13 oct. 2020
 *      Author: Gula
 */

#ifndef INFORMES_H_
#define INFORMES_H_
/** \brief  Imprime clientes y avisos
 *\param Cliente puntero al array clientes
 *\param int limite del array
 *\param int limite del array
 * \return int Return devuelve en 0 si esta todo bien y -1 si algun parametro es incorrecto
 */
int inf_impClientesYAvisos(Cliente*pBufferCli,int limiteCli,Publicacion* pBufferPubli,int limitePubli);
/** \brief  Imprime cliente con mas avisos
  *\param Publicacion puntero al array publicaciones
 *\param int limite del array
 *\param Cliente puntero al array clientes
 *\param int limite del array
 * \return int Return devuelve en 0 si esta todo bien y -1 si algun parametro es incorrecto
 */
int inf_clienteMasAvisos(Publicacion* pBufferPubli,int limitePubli,Cliente* pBufferCli,int limiteCli);
/** \brief  Imprime cliente con mas avisos pausados
  *\param Publicacion puntero al array publicaciones
 *\param int limite del array
 *\param Cliente puntero al array clientes
 *\param int limite del array
 * \return int Return devuelve en 0 si esta todo bien y -1 si algun parametro es incorrecto
 */
int inf_clienteMasAvisosPausados(Publicacion* pBufferPubli,int limitePubli,Cliente* pBufferCli,int limiteCli);
/** \brief  Imprime cliente con mas avisos
  *\param Publicacion puntero al array publicaciones
 *\param int limite del array
 *\param Cliente puntero al array clientes
 *\param int limite del array
 * \return int Return devuelve en 0 si esta todo bien
 */
int inf_rubroMasAvisos(Publicacion* pBufferPubli,int limitePubli, Cliente* pBufferCli, int limiteCli);

#endif /* INFORMES_H_ */
