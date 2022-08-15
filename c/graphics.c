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

/* inico if */
#if (defined _WIN32 || defined _WIN64)
/* caneceras windows. */
#include <windows.h>
#include <conio.h>

/* inclumos windows-utils*/
#include "../win/winutils.h"
#elif (defined __unix_ || defined __linux__)
/* cabeceras linux. */
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

/* incluimos linux-utils. */
#include "../unix/lnxutils.h"
#endif /* fin if */

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
void GL_fill_rect(Vector2 size, Vector2 pos) {
    int w = 0, h = 0;
    for (; h < size.y; h++) {
        for (w = 0; w <= size.x; w++) {
            gotoxy(pos.x + w, pos.y + h);
            printf("%c", ' ');
        }
    }
}
void GL_line(Vector2 start, Vector2 end, LineMesh tp) {
    int x0 = start.x, x1 = end.x,
        y0 = start.y, y1 = end.y;
    if (tp == Vert) {
        for (; y0 < y1; y0++) {
            gotoxy(x0, y0);
            printf(" ");
        }
    } else if (tp == Horz) {
        for (;x0 < x1; x0++) {
            gotoxy(x0, y0);
            printf(" ");
        }
    }
}
int GL_max(int a, int b) {
    return (a >= b) ? a : b;
}
int GL_min(int a, int b) {
    return (a <= b) ? a : b;
}
void GL_color(char *_color) {
    printf(_color);
}

void GL_button(Vector2 pos, Vector2 size, char *_value) {
    GL_fill_rect(size, pos); 
    if (_value != NULL) {
        int x = pos.x,
            y = pos.y;
        
        int w = size.x,
            h = size.y;
        
        gotoxy(x + 2, y + (h / 2));
        printf("%s", _value);
    }
}
