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

#if (defined __unix_ || defined __linux__)
/* cabeceras predeterminados. */
#include <stdio.h>
#include <stdlib.h>

/* cabeceras linux. */
#include "lnxutils.h"
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <limits.h>
#include <math.h>

int gotoxy(int x, int y) {
    printf("%c[%d;%df", 0x1B, y, x);
    return (1);
}

int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

char getch() {
    char c;
    system("stty raw");
    c = getchar();
    system("stty sane");
    return (c);
}

void clrscr() {
    system("clear");
    return;
}

char waitForAnyKey(void) {
    int pressed;

    while (!kbhit());

    pressed = getch();
    return ((char) pressed);
}
void Sleep(int tm) {
    usleep(1000 * tm);
}
void console_cursor(int _visible) {
    printf("%s", (_visible) 
                ? "\033[?25h" 
                : "\033[?25l");
}
char *gets(char *__restrict __s) {
    char *_value = malloc(sizeof(char));
    fgets(_value, INT_MAX, stdin);    
    *__s = *_value;
    return _value;
}
#endif
