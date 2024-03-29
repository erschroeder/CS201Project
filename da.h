/*
 * da.h
 * dynamic array header file
 *
 *  Created on: Aug 28, 2018
 *      Author: Emily Schroeder
 */
#ifndef __DA_INCLUDED__
    #define __DA_INCLUDED__

	#include <stdio.h>

    typedef struct da DA;

    extern DA   *newDA(void);
    extern void  setDAdisplay(DA *,void (*)(void *,FILE *));
    extern void  setDAfree(DA *,void (*)(void *));
    extern void  insertDA(DA *items,int index,void *value);
    extern void *removeDA(DA *items,int index);
    extern void  unionDA(DA *recipient,DA *donor);
    extern void *getDA(DA *items,int index);
    extern void *setDA(DA *items,int index,void *value);
    extern int   sizeDA(DA *items);
    extern void  displayDA(DA *items,FILE *fp);
    extern int   debugDA(DA *items,int level);
    extern void  freeDA(DA *items);
#endif
