#ifndef ASD_AVL_H
#define ASD_AVL_H

/**
 * Un albero AVL è:
 *  - un albero binario di ricerca su cui vale la proprietà di AVL
 *    per ogni nodo dell'albero vale che la differenza tra le altezze 
 *    dei sottoalberi sx e dx sia <= 1.
 * Si può dimostrare che questa proprietà rende un AVL un albero bilanciato.
 * 
 * Implementazione.
 * Per tenere traccia delle altezze si possono seguire due strade:
 *  - dato il nodo da cui si vuole calcolare l'altezza si segue il 
 *    percorso più lungo. In questo modo si paga in termini di tempo 
 *    di esecuzione la gestione delle altezze: 
 *    - per ogni nodo il costo è lineare sull'altezza.
 *  - si può invece utilizzare un campo altezza in ogni nodo. In questo 
 *    modo l'altezza si ricava a tempo costante ma si utilizza uno spazio
 *    lineare sulla dimensione dell'albero.
 * Volendo ridurre il tempo di esecuzione si sceglie la seconda opzione.
 * Si osserva che aggiornare l'altezza di un nodo x equivale a:
 *  ->  h(x) = 1 + max(h(x->sx), h(x->dx))
 */
struct avl_tree {
    int key;
    int h;
    struct avl_tree *sx;
    struct avl_tree *dx;
};

struct avl_tree * create_avl_node(int key);
void free_avl_tree(struct avl_tree *avl);

int checkAVL(struct avl_tree *avl);
int checkBST_avl(struct avl_tree *t);

void inorder_avl(struct avl_tree *avl);
void breadth_lvs_avl(struct avl_tree *avl);

struct avl_tree *insertAVL(struct avl_tree *avl, int k);

#endif // ASD_AVL_H