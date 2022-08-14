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
 * File:   lnxutils.h
 * 
 * Author: wil
 * Author: Javier
 */

#ifndef LNXUTILS_H
#define LNXUTILS_H

#ifdef __cplusplus
extern "C" {
#endif
    /* posiciona el cursor. */
    void gotoxy(int x, int y);

    /* limpia la pantalla. */
    void clrscr();
    
    /* pone en pausa hasta que se precione
     una tecla por parte del usuario. */
    char waitForAnyKey(void);
    
    /* funciones propios para linux. */
    int kbhit(void);    /* detecta si se presiona una tecla o no. */
    char getch();       /* espera hasta que se preciones una tecla. */
#ifdef __cplusplus
}
#endif

#endif /* LNXUTILS_H */

