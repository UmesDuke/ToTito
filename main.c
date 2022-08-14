/*
 * Copyright 2022 wil.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * File:   main.c
 * 
 * Author: wil
 * Author: javier
 * 
 * Application: Totito
 */
#if (defined _WIN32 || defined _WIN64)
/* caneceras windows. */
#include <windows.h>
#include <conio.h>

/* inclumos windows-utils*/
#include "win/winutils.h"
#elif (defined __unix_ || defined __linux__)
/* cabeceras linux. */
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

/* incluimos linux-utils. */
#include "unix/lnxutils.h"
#endif

/* librerias estandar .*/
#include <stdio.h>
#include <stdlib.h>

/* librerias propias. */
#include "c/graphics.h"

/* definiciones de macros. */
#define STRING_LEN 20

/* estrcturas. */
typedef struct {
    
} Datos;
typedef struct  {
    char nikname[STRING_LEN];
    Datos d_jugador;
} Jugador;

/* prototipos. */

/*
 * funcion principal encargado de gestionar las ebtradas
 * y salidas de la aplicacion.
 */
int main(int argc, char** argv) {
    
    return (EXIT_SUCCESS);
}


