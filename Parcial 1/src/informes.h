/*
 * informes.h
 *
 *  Created on: 13 oct. 2020
 *      Author: Gula
 */

#ifndef INFORMES_H_
#define INFORMES_H_

int inf_impClientesYAvisos(Cliente*pBufferCli,int limiteCli,Publicacion* pBufferPubli,int limitePubli);
int inf_clienteMasAvisos(Publicacion* pBufferPubli,int limitePubli,Cliente* pBufferCli,int limiteCli);
int inf_clienteMasAvisosPausados(Publicacion* pBufferPubli,int limitePubli,Cliente* pBufferCli,int limiteCli);

int inf_rubroMasAvisos(Publicacion* pBufferPubli,int limitePubli, Cliente* pBufferCli, int limiteCli);

#endif /* INFORMES_H_ */
