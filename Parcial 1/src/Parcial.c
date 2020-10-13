/*
 ============================================================================
 Name        : Parcial.c
 Author      : gula
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utn.h"
#include "clientes.h"
#include "publicacion.h"

#define CANTIDADCLIENTES 5
#define CANTIDADPUBLICACIONES 5

int menu(int*opcion);
int main()
{
	setbuf(stdout, NULL);
    Cliente clientes[CANTIDADCLIENTES];
    Publicacion publicaciones [CANTIDADPUBLICACIONES];
    int opcion;
    int auxid;
    int auxidPubli;
    char auxNombre [50];
    char auxApellido[50];
    char auxTextoAviso[64];
    int auxNumeroRubro;
    char auxCuit[50];
    int confirmar;
    int i;

    cli_inicializarArray(clientes,CANTIDADCLIENTES);
    publi_inicializarArray(publicaciones,CANTIDADPUBLICACIONES);
/*

    cli_alta(clientes,cli_obtenerID(),CANTIDADCLIENTES,"perez","pedro","152461535");
    cli_alta(clientes,cli_obtenerID(),CANTIDADCLIENTES,"mafia","lucia","22250452");
 */
    cli_alta(clientes,cli_obtenerID(),CANTIDADCLIENTES,"ramiro","azafran","002678226");
    cli_alta(clientes,cli_obtenerID(),CANTIDADCLIENTES,"perro","coriandro","12859218921");
    cli_alta(clientes,cli_obtenerID(),CANTIDADCLIENTES,"rica","cebolla","3421292");
    do{
        menu(&opcion);
        switch (opcion){
            case 1:
                if(!utn_getLetras(auxNombre,50,3,"\nIngrese el nombre: ",
                		"\nError..El nombre debe contener solo letras")&&
                    !utn_getLetras(auxApellido,50,3,"\nIngrese el apellido: ",
                    		"\nError..El apellido debe contener solo letras")&&
                    !utn_getCuit(auxCuit,50,3,"Ingrese el cuit: ",
                    		"Error...Ingrese el cuit debe ingresarse solo con numero Cant 11")){
                        auxid=cli_obtenerID();
                        cli_alta(clientes,auxid,CANTIDADCLIENTES,auxApellido,auxNombre,auxCuit);
                        printf("Alta satisfactoria Nº de Id: %d",auxid);
                        cli_pruebaImpresion(clientes,CANTIDADCLIENTES);
						getchar();

                    }
                break;
            case 2:
                if(!utn_getEntero(&auxid,3,"\nIngrese el id: ","\nError! Ingrese un id valido ",-1,999)&&
                    !cli_existeId(clientes,CANTIDADCLIENTES,auxid))
                {
                    cli_modificarbyId(clientes,CANTIDADCLIENTES,auxid);
                }else{
                        printf("\nEl id no existe..Vuelva A Intentarlo");
                        getchar();
                    }
                break;
            case 3:
                if(!utn_getEntero(&auxid,3,"\nIngrese el id: ","\nError! Ingrese un id valido ",-1,999)&&
                    !cli_existeId(clientes,CANTIDADCLIENTES,auxid)&&
                    !utn_getEntero(&confirmar,3,"\nEsta seguro q desea eliminar? 0-si 1-no ",
                    		"Error! Elija una opcion valida",0,1)&&
                    !confirmar){
                	cli_listar(clientes,CANTIDADCLIENTES,auxid);
                    cli_eliminarbyId(clientes,CANTIDADCLIENTES,auxid);
                }else{
                        printf("\nEl id no existe..Vuelva A Intentarlo");
                        getchar();
                    }

                break;
            case 4:
                if(!utn_getEntero(&auxid,3,"\nIngrese el id del cliente: ","\nError...Ingrese un id valido ",-1,999)&&
                    !cli_existeId(clientes,CANTIDADCLIENTES,auxid)&&
                    !utn_getEntero(&auxNumeroRubro,3,"\nIngrese el numero de rubro 1:arte 2:promocion :",
                    		"\nError ingrese un numero valido",0,2)&&
                    !utn_getLetrasYNumeros(auxTextoAviso,64,"\nIngrese el texto del aviso :"))
                    {
                	publi_alta(publicaciones,auxid,CANTIDADPUBLICACIONES,auxTextoAviso,auxNumeroRubro);
                	publi_PruebaImpresion(publicaciones,CANTIDADPUBLICACIONES);
                    }else{
                        printf("\nERROR! Vuelva a intentarlo");
                    }
                break;
            case 5:
            	if(!utn_getEntero(&auxid,3,"\nIngrese el id la publicacion a modificar: ",
            			"\nError...Ingrese un id valido ",-1,999)&& !publi_existeId(publicaciones,CANTIDADPUBLICACIONES,auxid))
            	{
            		publi_ImprimiByIdCliente(publicaciones,CANTIDADPUBLICACIONES,clientes,CANTIDADCLIENTES,auxid,&i);
            	}

                break;
            case 6:

                break;
            case 7:

                break;
            case 8:
            	break;
        }
    }while(opcion!=9);

    return EXIT_SUCCESS;
}
int menu(int*opcion){
    printf("\n1-ALTAS\n2-MODIFICAR\n3-BAJA\n4-PUBLICAR AVISO\n5-PAUSAR AVISO\n6-REANUDAR VEAVISONTA\n7-IMPRIMIR CLIENTES\n8-INFORMAR\n9-SALIR");
    utn_getEntero(opcion,3,"\nIngrese una opcion: ","\nError...ingrese una opcion valida...",1,8);
    return 0;

}



