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
#endif /* fin if */

/* librerias estandar .*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* librerias propias. */
#include "c/arraylist.h"
#include "c/graphics.h"
#include "c/utils.h"

/* definiciones de macros. */
#define STRING_LEN 20

/* numeros de teclas. */
#define ky_up    65 /* ACII - Fecha arriba. */
#define ky_down  66 /* ACII - Fecha abajo. */
#define ky_left  68 /* ACII - Fecha izquierda. */
#define ky_right 67 /* ACII - Fecha derecha. */
#define ky_enter 10 /* ACII - Tecla entrar. */
#define ky_esc   27 /* ACII - Tecla escape. */

/* enumerados */
typedef enum enum_nivel {
    Facil, Medio, Dificil
} Nivel;

/* estrcturas. */
typedef struct stc_partida {
    Nivel tp_nivel;
    Boolean activo;
    int p_ganada,
        p_empate,
        p_perdida;
} Partida;
typedef struct stc_datos {
    int partidas,
        puntage;
    Calendar f_registro;
    Partida p_facil, 
            p_normal,
            p_dificil;
} Datos;
typedef struct stc_jugador {
    int id;
    char name[STRING_LEN];
    Datos d_jugador;
} Jugador;

/* prototipos. */
void loader_screen(void);
void pre_screen(void);
void menu_screen(void);
void menu_estadistica(void);
void owner_details(void);
void GL_clear(void);

void limpiar_fichas(void);
void input_game(void);
void hud_game(void);

void move_boot_facil(void);
void move_boot_normal(void);
void poner_ficha_boot(void);

Nivel menu_modo(void);
Jugador *menu_play(Nivel _n);
Partida newPartida(Nivel _n);
Nivel getNivelJugador(Jugador *_j);

/* constantes. */
const int n_rows = 3;
const int n_cols = 3;

/* variables */
Jugador *player = NULL;
ArrayList *list = NULL;
Point tablero[3][3];

Boolean run     = False;
Integer turno   = GM_IA;
Integer ganador = GM_IA;

/*
 * funcion principal encargado de gestionar las ebtradas
 * y salidas de la aplicacion.
 */
int main(int argc, char** argv) {
    GL_clear();
    console_cursor(False);
    loader_screen();
    return (EXIT_SUCCESS);
}

void move_boot_facil(void) {
    ArrayList *list_pint = newArrayList(sizeof(Point));
    
    for (int f = 0; f < n_rows; f++) {
        for (int c = 0; c < n_cols; c++) {
            if (tablero[f][c].val != IA_Def)
                continue;
            
            Point *n_point = malloc(sizeof(Point));
            n_point->val = tablero[f][c].val;
            n_point->x   = f;
            n_point->y   = c;
            
            list_pint->add(list_pint, n_point);
        }
    }
    
    randomize;
    int rn = random(0 , list_pint->length - 1);   
    
    Point *pn   = list_pint->get(list_pint, rn);
    Point punto = tablero[pn->x][pn->y];
    
    tablero[pn->x][pn->y].val = IA_Uno;
    
    GL_color(FG_BLANCO);
    GL_color(BG_VERDE);
    
    gotoxy(punto.x, punto.y);
    printf("%c", 'x');
}

void move_boot_normal(void) {
    randomize;
    if (random(0, 10) % 2 == 0) {
        move_boot_facil();
    } else {
        poner_ficha_boot();
    }
}

void poner_ficha_boot(void) {
    Vector2 v2 = IA_mini_max(n_rows, n_cols, tablero);
    if (v2.x != -1 && v2.y != -1) {
        tablero[v2.x][v2.y].val = IA_Uno;
        
        GL_color(FG_BLANCO);
        GL_color(BG_VERDE);

        gotoxy(tablero[v2.x][v2.y].x,
               tablero[v2.x][v2.y].y);
        printf("%c", 'x');
    }
}

void GL_clear(void) {
    clrscr();
    GL_color(BG_BLANCO);
    GL_fill_rect(new_vector2(src_width, src_height), VECTOR2_ZERO);
}

void loader_screen(void) {
    gotoxy((src_width / 2) - 12, src_height / 2 - 3);
    printf(FG_NEGRO "J U E G O   T O T I T O");
    
    gotoxy((src_width / 2) - 20, src_height / 2 - 1);
    printf(FG_NEGRO "Cargando...");

    int x = (src_width / 2) - 20, y = (src_height / 2) + 1;
    int w = 60,
        h = 3;

    GL_color(BG_VERDE);
    GL_fill_rect(new_vector2(w - x, h), new_vector2(x, y));

    int _f = x + 1;
    while (_f < (w - 1)) {
        Sleep(100);

        gotoxy(_f, y + 1);
        
        GL_color(BG_NEGRO);
        printf(" \n");
        GL_color(BG_NULL);

        _f++;
    }
    menu_screen();
}
void menu_screen(void) {
    GL_clear();

    int x = (src_width / 2) - 15, y = (src_height / 2) + 2;

    GL_color(BG_VERDE);
    /*GL_color(FG_NEGRO)*/;

    GL_fill_rect(new_vector2(40, 20), new_vector2(x - 5, y - 12));
    /*GL_rect(new_vector2(40, 20), new_vector2(x - 5, y - 12));*/

    /*GL_color(G2D_NULL);*/
    /*GL_color(FG_NEGRO);*/
    /*GL_rect(new_vector2(36, 4), new_vector2(x - 3, y - 11));*/


    gotoxy(x + 8, y - 9);
    printf(FG_NEGRO "Menu Principal." G2D_NULL);

    GL_color(BG_NEGRO);
    GL_color(FG_BLANCO);

    GL_button(new_vector2(x, y - 4), new_vector2(30, 3), "Nueva Partida");
    GL_button(new_vector2(x, y), new_vector2(30, 3), "Estadisticas");
    GL_button(new_vector2(x, y + 4), new_vector2(30, 3), "Salir");

    int cx = x - 3,
        cy = y - 3;

    gotoxy(cx, cy);

    GL_color(BG_ROJO);
    printf("*" G2D_NULL);

    Boolean _b = True;
    int _op = 0;
    while (_b) {
        if (kbhit()) {
            int _pressed = getch();
            switch (_pressed) {
                case ky_down:
                    GL_color(BG_VERDE);
                    gotoxy(cx, cy);
                    printf(" ");
                    GL_color(BG_NULL);

                    cy += 4;
                    _op++;
                    if (cy > (y + 5)) {
                        cy = y + 5;
                    }
                    if (_op > 2) {
                        _op = 2;
                    }

                    gotoxy(cx, cy);
                    GL_color(BG_ROJO);
                    printf(FG_BLANCO "*" G2D_NULL);
                    break;
                case ky_up:
                    GL_color(BG_VERDE);
                    gotoxy(cx, cy);
                    printf(" ");
                    GL_color(BG_NULL);

                    cy -= 4;
                    _op--;
                    if (cy < (y - 3)) {
                        cy = y - 3;
                    }
                    if (_op < 0) {
                        _op = 0;
                    }

                    gotoxy(cx, cy);
                    GL_color(BG_ROJO);
                    printf(FG_BLANCO "*" G2D_NULL);
                    break;
                case ky_enter:
                    beeb;
                    switch (_op) {
                        case 0:
                            _b = False;
                            GL_clear();
                            pre_screen();
                            break;
                        case 1:
                            _b = False;
                            GL_clear();
                            menu_estadistica();
                            break;
                        case 2:
                            _b = False;
                            GL_clear();
                            owner_details();
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
void menu_estadistica(void) {
    int x = src_width / 2, y = src_height - 2;

    GL_color(BG_VERDE);
    GL_color(FG_BLANCO);
    GL_fill_rect(new_vector2(40, 20), new_vector2(x - 20, y - 20));

    /*GL_color(G2D_NULL);*/
    GL_color(FG_AZUL);

    gotoxy(x - 19, y - 18);
    printf(FG_BLANCO " Elelige un modo: ");
    gotoxy(x - 19, y - 17);
    printf(FG_NEGRO " - Principiante");
    gotoxy(x - 19, y - 16);
    printf(" - Medio");
    gotoxy(x - 19, y - 15);
    printf(" - Experto");

    gotoxy(x - 19, y - 13);
    printf(FG_BLANCO " Moviminetos: ");
    gotoxy(x - 19, y - 12);
    printf(FG_NEGRO " - Subir     >> Flecha arriba  [ ^ ]");
    gotoxy(x - 19, y - 11);
    printf(" - Abajor    >> Flecha abajo   [ v ]");
    gotoxy(x - 19, y - 10);
    printf(" - Derecha   >> Flecha derecha [ < ]");
    gotoxy(x - 19, y - 9);
    printf(" - Izquierda >> Flecha derecha [ > ]");

    gotoxy(x - 19, y - 7);
    printf(FG_BLANCO " Retorno: ");
    gotoxy(x - 19, y - 6);
    printf(FG_NEGRO " - ESC" G2D_NULL);

    Boolean _b = True;
    while (_b) {
        if (kbhit()) {
            int c = getch();
            if (c == ky_esc) {
                _b = False;
                beeb;
                menu_screen();
            }
        }
    }
}
void owner_details(void) {
    GL_color(FG_NEGRO);
    gotoxy(30, 4);printf("CREADORES\n");
    Sleep(500);
    
    gotoxy(20, 5);printf("Programacion II");
    gotoxy(38, 5);printf("Seccion E\n");
    Sleep(500);
    
    gotoxy(18, 7);printf("Wilson Martin");
    gotoxy(38, 7);printf("Cabrera Juarez\n");
    Sleep(500);
    
    gotoxy(31, 8);printf("202208003\n");
    Sleep(500);
    
    gotoxy(18, 10);printf("Javier Alejandro");
    gotoxy(38, 10);printf("Garcia Aguilon\n");
    Sleep(500);
    
    gotoxy(31, 11);printf("202208004\n");
    Sleep(500);
    
    gotoxy(20, 13);printf("Ingenieria en Sistemas");
    
    puts("");
    puts("");
    puts("");
    waitForAnyKey();
}

void pre_screen(void) {
    if (list == NULL) {
        list = newArrayList(sizeof(Jugador));
    }
    
    Nivel n = menu_modo();
    
    GL_clear();
    player = menu_play(n);
    
    ganador = GM_Null;
    run     = True;
    
    randomize;
    int ra = random(0, 10);    
    turno  = /*ra % 2 == 0 ? GM_IA :*/ GM_Player;
    
    GL_clear();
    limpiar_fichas();    
    hud_game();
}

void limpiar_fichas(void) {
    int xPos = 21, yPos = 6;
    for (int fil = 0; fil < n_rows; fil++) {
        for (int col = 0; col < n_cols; col++) {
            tablero[fil][col].val = IA_Def;
            tablero[fil][col].x = xPos;
            tablero[fil][col].y = yPos;
            xPos += 4;
        }
        xPos = 21;
        yPos += 4;
    }
}
void hud_game(void) {
    GL_color(BG_VERDE);
    GL_fill_rect(new_vector2(30, src_height - 7), new_vector2(10, 2));
    
    GL_color(BG_AMARILLO);
    GL_fill_rect(new_vector2(30, src_height - 7), new_vector2(42, 2));
    
    GL_color(FG_BLANCO);
    GL_string("Tic-Tac Toe", new_vector2(52, 4));
    
    /*GL_color(BG_AZUL);*/
    GL_string("-- -- -- --", new_vector2(52, 5));
    
    GL_color(BG_NEGRO);
    GL_fill_rect(new_vector2(26, 6), new_vector2(44, 8));
    GL_fill_rect(new_vector2(26, 3), new_vector2(44, 16));
    
    GL_color(FG_BLANCO);
    GL_string("1ro. Turno:   ", new_vector2(45, 9));
    GL_string("2do. Turno:   ", new_vector2(45, 12));
    
    GL_color(BG_NEGRO);    
    if (turno == GM_IA) {
        GL_color(FG_ROJO);
        GL_string("Maquina", new_vector2(56, 17));
    } else {
        GL_color(FG_VERDE);
        GL_string("Jugador", new_vector2(56, 17));
    }
        
    int x = 20, y = 8;
    GL_color(BG_NEGRO);
    GL_color(FG_BLANCO);
    
    GL_line(new_vector2(x, y),     new_vector2(x + 11, y), Horz);
    GL_line(new_vector2(x, y + 4), new_vector2(x + 11, y), Horz);
    
    GL_line(new_vector2(x + 3, y - 3), new_vector2(x , y +8), Vert);
    GL_line(new_vector2(x + 7, y - 3), new_vector2(x , y +8), Vert);
        
    input_game();
}

void input_game(void) {
    int xdef = 21, ydef = 6;
    int xpos = xdef, ypos = ydef;
    
    int f = 0, c = 0;
    
    console_cursor(True);
    gotoxy(xpos, ypos);
    
    Nivel estado = getNivelJugador(player);
    while (run) {
            if (turno == GM_IA) {            
            switch (estado) {                
                case Medio:
                    move_boot_normal(); break;
                case Dificil:
                    poner_ficha_boot(); break;
                case Facil:
                default:
                    move_boot_facil(); break;
            }
            
            printf("\n");
            Sleep(10);
            
            gotoxy(xpos, ypos);
            turno = GM_Player;
            
            if (IA_fin_partida(n_rows, n_cols, tablero)) {
                ganador = IA_ganar_partida(n_rows, n_cols, tablero) == IA_Uno ? GM_IA : GM_Player;
                run     = False;
            }
        } else {
            if (kbhit()) {
                int key = getch();
                switch (key) {
                    case ky_up:
                        ypos -= 4;
                        f--;
                        if (ypos < ydef) {
                            ypos = ydef;
                            f    = 0;
                        }
                        break;
                    case ky_down:
                        ypos += 4;
                        f++;
                        if (ypos > (ydef + 8)) {
                            ypos = (ydef + 8);
                            f    = n_rows -1;
                        }
                        break;
                    case ky_left:
                        xpos -= 4;
                        c--;
                        if (xpos < xdef) {
                            xpos = xdef;
                            c    = 0;
                        }
                        break;
                    case ky_right:
                        xpos += 4;
                        c++;
                        if (xpos > (xdef + 8)) {
                            xpos = (xdef + 8);
                            c    = n_cols -1;
                        }
                        break;
                    case ky_enter:
                        if (!IA_tablero_completo(n_rows, n_cols, tablero) && turno == GM_Player) {
                            GL_color(FG_BLANCO);
                            GL_color(BG_VERDE);
                            gotoxy(xpos, ypos);
                            printf("o");
                            
                            tablero[f][c].val = IA_Zero;
                            turno             = GM_IA;
                            
                            if (IA_fin_partida(n_rows, n_cols, tablero)) {
                                ganador = IA_ganar_partida(n_rows, n_cols, tablero) == IA_Uno ? GM_IA : GM_Player;
                                run     = False;
                            }                     
                        }
                        break;
                    default:
                        break;
                }                
                gotoxy(xpos, ypos);
            }
        }
    }
    
/*
    if (win != JNull) {
        if (win == boot) {
            color(BG_AMARILLO);
            color(FG_BLANCO);
            
            gotoxy(src_width / 2, src_height - 2);
            printf("Perdidste ;D...");
        } else {
            color(BG_VERDE);
            color(FG_BLANCO);
            
            gotoxy(src_width / 2, src_height - 2);
            printf("Has Ganado ;D...");
        }
    }
    
    color(RESET_COLOR);
*/
    waitForAnyKey();    
    menu_screen();
}

Partida newPartida(Nivel _n) {
    Partida p;
    p.activo = False;
    p.p_empate = 0;
    p.p_ganada = 0;
    p.p_perdida = 0;
    p.tp_nivel = _n;
    return p;
}

Jugador *menu_play(Nivel _n) {
    Jugador *j = malloc(sizeof(Jugador));
    
    int x = src_width / 2, 
        y = src_height / 2;
    
    char str1[] = "Binevenido al juego ToTiTo";
    GL_color(FG_NEGRO);
    gotoxy(x - (strlen(str1) / 2), y - 10);
    printf("%s", str1);
    
    char str2[] = "nickname: ";
    gotoxy(x - (strlen(str1)), y - 5);
    printf("%s", str2);
    
    /*GL_color(BG_AZUL);*/
    GL_rect(new_vector2(35, 2), new_vector2(x - strlen(str1) + strlen(str2), y - 6));
    
    gotoxy(x - strlen(str1) + strlen(str2) + 1, y - 5);
    console_cursor(True);
        
    char *j_name = malloc(sizeof(char));
    fflush(stdin);
    gets(j_name);
    fflush(stdin);
    
    console_cursor(False);
    
    Boolean ya_regis = False;
    for (int i = 0; i < list->length; i++) {
        Jugador *item = list->get(list, i);
        if (item == NULL)
            continue;
        
        if (strcmp(item->name, j_name) == 0) {
            ya_regis = True;
            j = item;
            break;
        }
    }
    
    if (!ya_regis) {
        Datos d;
        d.partidas   = 0;
        d.f_registro = newCalendar();
        d.p_dificil  = newPartida(Dificil);
        d.p_facil    = newPartida(Facil);
        d.p_normal   = newPartida(Medio);
        
        j->d_jugador = d;
        j->id = list->length + 1;
        j->d_jugador.puntage = 0;
        strcpy(j->name, j_name);
    }
    switch (_n) {
        case Facil:
            j->d_jugador.p_facil.activo   = True;
            j->d_jugador.p_normal.activo  = False;
            j->d_jugador.p_dificil.activo = False;
            break;
        case Medio:
            j->d_jugador.p_facil.activo   = False;
            j->d_jugador.p_normal.activo  = True;
            j->d_jugador.p_dificil.activo = False;
            break;
        case Dificil:
            j->d_jugador.p_facil.activo   = False;
            j->d_jugador.p_normal.activo  = False;
            j->d_jugador.p_dificil.activo = True;
        default:
            break;
    }
    int n_p = j->d_jugador.partidas;
    j->d_jugador.partidas = n_p + 1;
    
    list->add(list, j);
    return j;
}

Nivel getNivelJugador(Jugador *_j) {
    Datos d = _j->d_jugador;
    if (d.p_dificil.activo) {
        /* modi dificil. */
        return d.p_dificil.tp_nivel;
    } else if (d.p_facil.activo) {
        /* modo facil. */
        return d.p_facil.tp_nivel;
    }
    /* modo normal. */
    return d.p_normal.tp_nivel;
}
Nivel menu_modo(void) {
    int x = (src_width / 2) - 15, 
        y = (src_height / 2) + 2;
    
    GL_color(BG_VERDE);
    /*GL_color(FG_BLANCO);*/
    GL_fill_rect(new_vector2(40, 22), new_vector2(x - 5, y - 12));
    
    /*GL_color(G2D_NULL);*/
    /*GL_color(FG_AZUL); */
    /*GL_fill_rect(new_vector2(36, 4), new_vector2(x - 3, y - 11));*/
    
    gotoxy(src_width / 2 - 9, y - 10);
    printf(FG_NEGRO "Modo de la partida." G2D_NULL);
    
    GL_color(BG_NEGRO);
    GL_color(FG_BLANCO);
    
    GL_button(new_vector2(x, y - 7), new_vector2(30, 3), "- Principiante");
    GL_button(new_vector2(x, y - 3), new_vector2(30, 3), "- Intermedio");
    GL_button(new_vector2(x, y + 1), new_vector2(30, 3), "- Experto");
    GL_button(new_vector2(x, y + 5), new_vector2(30, 3), "- Atras");
    
    int cx = x - 2,
        cy = y - 6;//3
    
    gotoxy(cx, cy);
    GL_color(BG_ROJO);
    printf(FG_BLANCO "*" G2D_NULL);
    
    Boolean _b = True;
    Nivel _m;
    _m = Facil;    
    int _op = 0;
    while (_b) {
        if (kbhit()) {
            int _pressed = getch();            
            switch (_pressed) {
                case ky_down:
                    GL_color(BG_VERDE);
                    gotoxy(cx, cy);printf(" ");
                    
                    
                    cy += 4;
                    _op++;
                    if (cy > (y + 6)) { cy  =  y + 6; }
                    if (_op > 3)      { _op = 3;     }
                    
                    gotoxy(cx, cy);
                    GL_color(BG_ROJO);
                    printf(FG_BLANCO "*" G2D_NULL);
                    break;
                case ky_up:
                    GL_color(BG_VERDE);
                    gotoxy(cx, cy);printf(" ");
                    
                    cy -= 4;
                    _op--;
                    if (cy < (y - 6)) { cy =  y - 6; }
                    if (_op < 0)      { _op = 0;     }
                    
                    gotoxy(cx, cy);
                    GL_color(BG_ROJO);
                    printf(FG_BLANCO "*" G2D_NULL);
                    break;
                case ky_enter:
                    beeb;
                    switch (_op) {
                        case 0: // modo principiante.
                            _b = False;
                            _m = Facil;
                            break;
                        case 1: // modo intermedio
                            _b = False;
                            _m = Medio;
                            break;
                        case 2: // modo experto
                            _b = False;
                            _m = Dificil;
                            break;
                        case 3:
                            _b = False;                            
                            GL_clear();
                            menu_screen();                             
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
    }    
    return _m;
}

