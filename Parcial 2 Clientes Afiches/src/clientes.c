#include "utn.h"
#include "clientes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int isValidNombre(char* nombre);
static int isValidApellido(char* apellido);

Cliente* clientes_new()
{
    Cliente* this;
    this=malloc(sizeof(Cliente));
    return this;
}

void clientes_delete(Cliente* this)
{
    free(this);
}

Cliente* clientes_newConParametros(int idCliente, char *nombre, char *apellido, char *cuit) {
	Cliente* this;
	this=clientes_new();

	if (this != NULL) {

		if (clientes_setIdCliente(this, idCliente) != -1
			&& clientes_setNombre(this, nombre) != -1
			&& clientes_setApellido(this, apellido) != -1
			&& clientes_setCuit(this, cuit) != -1)
			{
				return this;
			}
	}
	clientes_delete(this);
	return NULL;
}


int clientes_setNombre(Cliente* this,char* nombre)
{
    int retorno=-1;
    if(this!=NULL && !isValidNombre(nombre))
    {
        strcpy(this->nombre,nombre);
        retorno=0;
    }
    return retorno;
}

int clientes_getNombre(Cliente* this,char* nombre)
{
    int retorno=-1;
    if(this!=NULL && nombre!=NULL)
    {
        strcpy(nombre,this->nombre);
        retorno=0;
    }
    return retorno;
}

int clientes_setApellido(Cliente* this,char* apellido)
{
    int retorno=-1;
    if(this!=NULL && !isValidApellido(apellido))
    {
        strcpy(this->apellido,apellido);
        retorno=0;
    }
    return retorno;
}

int clientes_getApellido(Cliente* this,char* apellido)
{
    int retorno=-1;
    if(this!=NULL && apellido!=NULL)
    {
        strcpy(apellido,this->apellido);
        retorno=0;
    }
    return retorno;
}

int clientes_setIdCliente(Cliente* this,char* idCliente)
{
    int retorno=-1;
    if(this!=NULL && idCliente!=NULL && !isInt(idCliente))
    {

        this->idCliente=atoi(idCliente);
        retorno=0;
    }
    return retorno;
}

int clientes_getIdCliente(Cliente* this,int* idCliente)
{
    int retorno=-1;
    if(this!=NULL)
    {
        *idCliente=this->idCliente;
        retorno=0;
    }
    return retorno;
}

int clientes_setIsEmpty(Cliente* this,char* isEmpty)
{
    int retorno=-1;
    if(this!=NULL && isEmpty!= NULL && !isInt(isEmpty) )
    {
        this->isEmpty=atoi(isEmpty);
        retorno=0;
    }
    return retorno;
}

int clientes_getIsEmpty(Cliente* this,int* isEmpty)
{
    int retorno=-1;
    if(this!=NULL)
    {
        *isEmpty=this->isEmpty;
        retorno=0;
    }
    return retorno;
}

int clientes_setCuit(Cliente *this, char* cuit) {
	int result = -1;
	if (this != NULL) {
		strncpy(this -> cuit, cuit, (int) sizeof(this -> cuit));
		result = 0;
	}
	return result;
}


int clientes_getCuit(Cliente *this, char *cuit) {
	int result = -1;
	if (this != NULL) {
		strcpy(cuit, this -> cuit);
		result = 0;
	}
	return result;
}

void clientes_mostrar(void* pCliente){
    int bufferId;
    char bufferNombre[50];
    char bufferApellido[50];
    char bufferCuit[50];
    if(pCliente!=NULL){
    	clientes_getIdCliente(pCliente,&bufferId);
    	clientes_getNombre(pCliente,&bufferNombre);
    	clientes_getApellido(pCliente,&bufferApellido);
    	clientes_getCuit(pCliente,&bufferCuit);
        printf("%d -%s - %s -%s\n",bufferId,bufferNombre,bufferApellido,bufferCuit);
    }
}

static int isValidNombre(char* nombre){
    return isLetras(nombre);
}
static int isValidApellido(char* apellido){
    return isLetras(apellido);
}


