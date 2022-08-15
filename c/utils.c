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

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include "utils.h"

Calendar newCalendar() {
    Calendar c;
    
    // variables para almacenar los componentes de fecha y hora
    //int hours, minutes, seconds, day, month, year;
 
    // `time_t` es un tipo de tiempo aritmético
    time_t now;
 
    // Obtener la hora actual
    // `time()` devuelve la hora actual del sistema como un valor `time_t`
    time(&now);
 
    // Convertir al formato de hora local e imprimir a stdout
    printf("Today is %s", ctime(&now));
 
    // localtime convierte un valor de `time_t` a la hora del calendario y
    // devuelve un puntero a una estructura `tm` con sus miembros
    // rellenado con los valores correspondientes
    struct tm *local = localtime(&now);
 
    c.hours = local->tm_hour;         // obtener horas desde la medianoche (0-23)
    c.minutes = local->tm_min;        // obtener minutos pasados después de la hora (0-59)
    c.seconds = local->tm_sec;        // obtener segundos pasados después de un minuto (0-59)
 
    c.day = local->tm_mday;            // obtener el día del mes (1 a 31)
    c.month = local->tm_mon + 1;      // obtener el mes del año (0 a 11)
    c.year = local->tm_year + 1900;   // obtener el año desde 1900
 
    // imprime la hora local
    //if (c.hours < 12) {    // antes del mediodia
    //    printf("Time is %02d:%02d:%02d am\n", c.hours, c.minutes, c.seconds);
    //}
    //else {    // Después de mediodía
    //    printf("Time is %02d:%02d:%02d pm\n", c.hours - 12, c.minutes, c.seconds);
    //}
    //
    // imprime la fecha actual
    //printf("Date is: %02d/%02d/%d\n", c.day, c.month, c.year);
    return c;
}
Boolean IA_tablero_completo(int rows, int cols, Point m[rows][cols]) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (m[r][c].val == IA_Def) {
                return False;
            }
        }
    }
    return True;
}
Boolean IA_fin_partida(int rows, int cols, Point m[rows][cols]) {
    return IA_tablero_completo(rows, cols, m) 
            || (IA_ganar_partida(rows, cols, m) != IA_Def);
}
Integer IA_ganar_partida(int rows, int cols, Point m[rows][cols]) {
/*
    if (m[0][0].val != IA_Def
            && m[0][0].val == m[1][1].val 
            && m[0][0].val == m[2][2].val) {
        return m[0][0].val;
    }
    if (m[0][2].val != IA_Def
            && m[0][2].val == m[1][1].val 
            && m[0][2].val == m[2][0].val) {
        return m[0][2].val;
    }
    for (int f = 0; f <rows; f++) {
        if (m[f][0].val != IA_Def 
                && m[f][0].val == m[f][1].val 
                && m[f][0].val == m[f][2].val) {
            return m[f][0].val;
        }
    }
    for (int c = 0; c < cols; c++) {
        if (m[0][c].val != IA_Def 
                && m[0][c].val == m[1][c].val
                && m[0][c].val == m[2][c].val) {
            return m[0][c].val;
        }
    }
*/
    return IA_Def;
}
Integer IA_min(int rows, int cols, Point m[rows][cols]) {
    if (IA_fin_partida(rows, cols, m)) {
        if (IA_ganar_partida(rows, cols, m) != IA_Def) {
            return 1;
        } else {
            return 0;
        }
    }
    int v = INT_MAX;
    int aux;
    for (int n = 0; n < rows; n++) {
        for (int j = 0; j < cols; j++) {
            if (m[n][j].val == IA_Def) {
                m[n][j].val = IA_Zero;
                aux = IA_max(rows, cols, m);
                
                if (aux < v) {
                    v = aux;
                }
                m[n][j].val = IA_Def;
            }
        }
    }
    return v;
}
Integer IA_max(int rows, int cols, Point m[rows][cols]) {
    if (IA_fin_partida(rows, cols, m)) {
        if (IA_ganar_partida(rows, cols, m) != IA_Def) {
            return -1;
        } else {
            return 0;
        }
    }
    int v = INT_MIN;
    int aux;
    for (int n = 0; n < rows; n++) {
        for (int j = 0; j < cols; j++) {
            if (m[n][j].val == IA_Def) {
                m[n][j].val = IA_Uno;
                aux = IA_min(rows, cols, m);
                
                if (aux > v) {
                    v = aux;
                }
                m[n][j].val = IA_Def;
            }
        }
    }
    return v;
}
Vector2 IA_mini_max(int rows, int cols, Point m[rows][cols]) {
    if (!IA_fin_partida(rows, cols, m)) {
        int f = 0, c = 0;
        int v = INT_MIN;
        int aux;
        
        for (int n = 0; n < rows; n++) {
            for (int j = 0; j < cols; j++) {
                if (m[n][j].val == IA_Def) {
                    m[n][j].val = IA_Uno;
                    aux = IA_min(rows, cols, m);
                    
                    if (aux > v) {
                        v = aux;
                        f = n;
                        c = j;
                    }
                    m[n][j].val = IA_Def;
                }
            }
        }
        return new_vector2(f, c);
    }
    return new_vector2(-1, -1);
}
