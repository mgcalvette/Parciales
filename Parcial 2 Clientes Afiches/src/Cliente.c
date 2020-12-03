#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cliente.h"

static int isValidString(char* string);
static int isValidInt(char* string);
static int isValidCuit(char* string);

Cliente* cliente_new()
{
	return (Cliente*)malloc(sizeof(Cliente));
}

Cliente* cliente_newWithParameters(int id, char* name, char* lastName, char* cuit)
{
	Cliente* this = cliente_new();
	if(this!=NULL)
	{
		if( !cliente_setId(this, id) && !cliente_setName(this, name) && !cliente_setLastName(this, lastName) && !cliente_setCuit(this, cuit) )
		{
			return this;
		}
		else
		{
			cliente_delete(this);
		}
	}
	return NULL;
}

Cliente* cliente_newWithParametersTxt(char* id, char* name, char* lastName, char* cuit)
{
	Cliente* this = cliente_new();
	if(this!=NULL)
	{
		if( !cliente_setIdTxt(this, id) && !cliente_setName(this, name) && !cliente_setLastName(this, lastName) && !cliente_setCuit(this, cuit))
		{
			return this;
		}
		else
		{
			cliente_delete(this);
		}
	}
	return NULL;
}

void cliente_delete(Cliente* this)
{
	free(this);
}

int cliente_getId(void* this, int* pResult)
{
	int retornar=-1;
	Cliente* bufferClient;
	if(this!=NULL)
	{
		bufferClient = (Cliente*) this;
		*pResult = bufferClient->id;
		retornar=0;
	}
	return retornar;
}

int cliente_getName(Cliente* this, char* pResult)
{
	int retornar=-1;
	if(this!=NULL)
	{
		retornar=0;
		strncpy(pResult, this->name, NAME_SIZE);
	}
	return retornar;
}

int cliente_getLastName(Cliente* this, char* pResult)
{
	int retornar=-1;
	if(this!=NULL)
	{
		retornar=0;
		strncpy(pResult, this->lastName, NAME_SIZE);
	}
	return retornar;
}

int cliente_getCuit(Cliente* this, char* pResult)
{
	int retornar=-1;
	if(this!=NULL)
	{
		retornar=0;
		strncpy(pResult, this->cuit, CUIT_SIZE);
	}
	return retornar;
}

int cliente_setId(Cliente* this, int id)
{
	int retorno=-1;
	if(this!=NULL && id>-1)
	{
		this->id = id;
		retorno=0;
	}
	return retorno;
}

int cliente_setIdTxt(Cliente* this, char* id)
{
	int retorno=-1;
	if(this!=NULL && isValidInt(id)==1)
	{
		this->id = atoi(id);
		retorno=0;
	}
	return retorno;
}

int cliente_setName(Cliente* this, char* name)
{
	int retorno=-1;
	if(this!=NULL && isValidString(name)==1)
	{
		strncpy(this->name, name, NAME_SIZE);
		retorno=0;
	}
	return retorno;
}

int cliente_setLastName(Cliente* this, char* lastName)
{
	int retorno=-1;
	if(this!=NULL && isValidString(lastName)==1)
	{
		strncpy(this->lastName, lastName, NAME_SIZE);
		retorno=0;
	}
	return retorno;
}

int cliente_setCuit(Cliente* this, char* cuit)
{
	int retorno=-1;
	if(this!=NULL && isValidCuit(cuit)==1)
	{
		strncpy(this->cuit, cuit, CUIT_SIZE);
		retorno=0;
	}
	return retorno;
}

static int isValidString(char* string)
{
	int retorno=1;
	if(string!=NULL && strlen(string)>0)
	{
		for(int i=0;i<strlen(string);i++)
		{
			if((string[i]<'a' || string[i]>'z') && (string[i]<'A' || string[i]>'Z') && string[i]!=32 && string[i]!='-')
			{
				retorno=0;
				break;
			}
		}
	}
	return retorno;
}

static int isValidInt(char* string)
{
	int retorno = 1;
	int i = 0;

	if(string!=NULL && strlen(string)>0)
	{
		if(string[0]=='-')
		{
			i=1;
		}
		for(;i<strlen(string);i++)
		{
			if(string[i]>'9' || string[i]<'0')
			{
				retorno=0;
				break;
			}
		}
	}
	return retorno;
}

static int isValidCuit(char* string)
{
	int retorno;
	int dashCounter=0;
	if(string != NULL && strlen(string) > 0 && string[2] == '-' && string[11] == '-' && string[12] != '\0')
	{
		retorno = 1;
		for(int i = 0;string[i] != '\0'; i++)
		{
			if(string[i] == '-')
			{
				dashCounter++;
			}
			if(dashCounter>2 || ((string[i] < '0' || string[i] > '9') && string[i] != '-'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

int cliente_print(void* this)
{
	int retornar=-1;
	Cliente* bufferClient;
	int bufferId;
	char bufferName[NAME_SIZE];
	char bufferLastName[NAME_SIZE];
	char bufferCuit[CUIT_SIZE];
	if(this!=NULL)
	{
		retornar=0;
		bufferClient = (Cliente*) this;
		if( !cliente_getId(bufferClient, &bufferId) && !cliente_getName(bufferClient, bufferName) &&
			!cliente_getLastName(bufferClient, bufferLastName) && !cliente_getCuit(bufferClient, bufferCuit))
		{
			printf("\nID: %d - Nombre: %s - Apellido: %s - Cuit: %s", bufferId, bufferName, bufferLastName, bufferCuit);
		}
	}
	return retornar;
}
