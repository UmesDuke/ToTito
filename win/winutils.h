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
 * File:   winutils.h
 * 
 * Author: wil
 * Author: Javier
 */

#ifndef WINUTILS_H
#define WINUTILS_H

#ifdef __cplusplus
extern "C" {
#endif
    /* posiciona el cursor. */
    int gotoxy(int x, int y);

    /* limpia la pantalla. */
    void clrscr();
    
    /* pone en pausa hasta que se precione
     una tecla por parte del usuario. */
    char waitForAnyKey(void);
    
    /* visivilidad del cursor. */
    void console_cursor(int _visible);
#ifdef __cplusplus
}
#endif

#endif /* WINUTILS_H */

