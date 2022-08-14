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

/* librerias estandar .*/
#include <stdio.h>
#include <stdlib.h>

/* librerias con los prototipos. */
#include "graphics.h"

/* funciones especiales. */
Vector2 new_vector2(int x, int y) {
    Vector2 nv;
    nv.x = x;
    nv.y = y;
    return nv;
}

/*
 * implementacion de las funciones 'GL'.
 */
void GL_string(char *_value, Vector2 pos) {
    gotoxy(pos.x, pos.y);
    printf("%s", _value);
}
void GL_rect(Vector2 size, Vector2 pos) {
    int w = 0, h = 0;
    for (; h < size.y; h++) {
        gotoxy(pos.x, pos.y + h);
        printf("%c", '|');
        
        gotoxy(pos.x + size.x, pos.y + h);
        printf("%c", '|');
    }
    for (; w <= size.x; w++) {
        gotoxy(pos.x + w, pos.y);
        printf("%c", '-');
        
        gotoxy(pos.x + w, pos.y + size.y);
        printf("%c", '-');
    }
}
void GL_line(Vector2 start, Vector2 end) {
    int sx = GL_min(start.x, end.x),
        nx = GL_max(start.x, end.y);
    
    int sy = GL_min(start.x, end.x),
        ny = GL_max(start.x, end.y);
    int w = sx - nx, h = sy - ny;
    
}
int GL_max(int a, int b) {
    return (a >= b) ? a : b;
}
int GL_min(int a, int b) {
    return (a <= b) ? a : b;
}