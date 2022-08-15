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

#if (defined _WIN32 || defined _WIN64)
/* cabeceras predeterminados. */
#include <stdio.h>
#include <stdlib.h>

/* cabeceras windows. */
#include <windows.h>
#include <conio.h>
#include "winutils.h"

int gotoxy(int x, int y) {
    COORD coord;
    HANDLE h_stdout;
    coord.X = x;
    coord.Y = y;
    if ((h_stdout = GetStdHandle(STD_OUTPUT_HANDLE)) 
            == INVALID_HANDLE_VALUE)
        return 0;
    if (SetConsoleCursorPosition(h_stdout, coord) == 0)
        return 0;
    return 1;
}

void clrscr() {
    system("cls");
}

char waitForAnyKey(void) {
    int pressed;

    while (!kbhit());

    pressed = getch();
    return ((char) pressed);
}
void console_cursor(int _visible) {
    static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(handle, &cci);
    cci.bVisible = _visible; // show/hide cursor
    SetConsoleCursorInfo(handle, &cci);
}
#endif

