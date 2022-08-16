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
 * File:   utils.h
 * 
 * Author: wil
 * Author: Javier
 */

#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif
/* librerias. */
#include <time.h>
#include "graphics.h"
    
/*un sonido 'beep'.*/
#define beeb (printf("\7"))

/* dimension del campo/consola*/
#define src_width  80
#define src_height 25

/*
 * macros encargado de cembrar la semilla y generara 
 * un numero aleatrorio entre 0 - num.
 */
#define randomize (srand(time(NULL)))
#define random(min, max) ((min) + rand() / (RAND_MAX / ((max) - (min) + 1) + 1))
    
/* los posibles valores que puede tener un
 punto en el juego. */
#define IA_Def -1
#define IA_Uno  1
#define IA_Zero 0
    
/* turnos de los jugadores. */
#define GM_Null  -1
#define GM_IA     1
#define GM_Player 0
    
/* utilidades. */
typedef enum enum_bool {
    False = 0, True = 1
} Boolean;

/* estructura encargado de los puntos
 en el juego de totito. */
typedef struct stc_point {
    int x,   /* posicion en x. */ 
        y;   /* posicion en y. */
    int val; /* valor del punto. */
} Point;

/* estructura fecha. */
typedef struct stc_cal {
    int hours,      /* hora     */
        minutes,    /* minutos  */
        seconds,    /* segundos */
        day,        /* dias     */
        month,      /* mes      */
        year;       /* año      */
} Calendar;

/* sinonimos-utilidades. */
typedef int Integer;
typedef float Float;

/* funciones-utilidades*/
Calendar newCalendar();

/* IA mini-max */
Boolean IA_tablero_completo(int rows, int cols, Point m[rows][cols]);
Boolean IA_fin_partida     (int rows, int cols, Point m[rows][cols]);

Integer IA_ganar_partida(int rows, int cols, Point m[rows][cols]);
Boolean IA_check_partida(int rows, int cols, Point m[rows][cols], Integer _t);
Integer IA_min(int rows, int cols, Point m[rows][cols]);
Integer IA_max(int rows, int cols, Point m[rows][cols]);

Vector2 IA_mini_max(int rows, int cols, Point m[rows][cols]);
#ifdef __cplusplus
}
#endif

#endif /* UTILS_H */

