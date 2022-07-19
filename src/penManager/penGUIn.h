/*-----------------------------------------------------------
Name:       penGUIn.h

Author:     Keefer Gregoire

Description: penGUIn is a user interface library
-----------------------------------------------------------*/

#include <stdlib.h>

//  Doubly Linked List used for managing state
typedef struct dll_node_t{
    void *val;
    dll_node_t *prev;
    dll_node_t *next;
} DLL_NODE;


void penGUIn_start(void);
void PenGUIn_restart(void);
void PenGUIn_stop(void);
void penGUIN_update(const Mip_t * const elem);
