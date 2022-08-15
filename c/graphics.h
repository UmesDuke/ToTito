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
 * File:   graphics.h
 * 
 * Author: wil
 * Author: Javier
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#ifdef __cplusplus
extern "C" {
#endif
    
/* definimos los diferentes colores que puede
 tomar los textos por consola. */
#define G2D_NULL      "\x1b[0m"
#define FG_NEGRO     "\x1b[30m"
#define FG_ROJO      "\x1b[31m"
#define FG_VERDE     "\x1b[32m"
#define FG_AMARILLO  "\x1b[33m"
#define FG_AZUL      "\x1b[34m"
#define FG_MAGENTA   "\x1b[35m"
#define FG_CYAN      "\x1b[36m"
#define FG_BLANCO    "\x1b[37m"
#define FG_NULL      "\x1b[39m"

/* definios los diferentes colores que puede 
 tomar de fondo cualquie caracter por consola.*/
#define BG_NEGRO     "\x1b[40m"
#define BG_ROJO      "\x1b[41m"
#define BG_VERDE     "\x1b[42m"
#define BG_AMARILLO  "\x1b[43m"
#define BG_AZUL      "\x1b[44m"
#define BG_MAGENTA   "\x1b[45m"
#define BG_CYAN      "\x1b[46m"
#define BG_BLANCO    "\x1b[47m"
#define BG_NULL      "\x1b[49m"
    
/* valores predterminados */
#define VECTOR2_ZERO (new_vector2(0, 0))
    
/* enumerados */
typedef enum enum_ln_tp {
    Vert, Horz
} LineMesh;
    
/* generamos las diferentes estructuras. */    
typedef struct {
    int x, y;
} Vector2;

/* definimos la funciones que se encargaran
 de inicializar las estructuras. */
Vector2 new_vector2(int x, int y);

/* definimos los prototipos para graficar por consola. */

/* dibuja una cadena. */
void GL_string(char *_value, Vector2 pos);

/* dibuja una linea. */
void GL_line(Vector2 start, Vector2 end, LineMesh tp);   

/* dibuna un rectanguloa. */
void GL_rect(Vector2 size, Vector2 pos);
void GL_fill_rect(Vector2 size, Vector2 pos);

/* deermina el maximo. */
int GL_max(int a, int b);

/* deermina el minimo. */
int GL_min(int a, int b);

/* color de la grafica. */
void GL_color(char *_color);

/*--------------------------/
/      DIBUJA: #Button      /
/ -------------------------*/
void GL_button(Vector2 pos, Vector2 size, char *_value);
/* fin prototipos. */    
#ifdef __cplusplus
}
#endif

#endif /* GRAPHICS_H */

