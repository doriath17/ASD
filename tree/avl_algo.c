#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "avl.h"

int get_h_avl(struct avl_tree *avl){
    if (avl == NULL){
        return -1;
    } else {
        return avl->h;
    }
}

void update_h_avl(struct avl_tree *avl){
    int hsx = get_h_avl(avl->sx);
    int hdx = get_h_avl(avl->dx);
    int hmax = hsx >= hdx ? hsx : hdx;
    avl->h = 1 + hmax;
}

/**
 * Idea
 * Se la differenza tra le altezze dei sottoalberi è uguale a 2 allora 
 * c'è violazione della proprietà degli avl.
 * Nota che bisgona usare get_h_avl per valutare l'altezza di un NULL come -1.
 * 
 * return 
 *  - 1 se violazione
 *  - 0 altrimenti
 */
int is_violation_avl(struct avl_tree *avl){
    if (get_h_avl(avl) <= 2){
        return 0;
    } else if (get_h_avl(avl->sx) - get_h_avl(avl->dx) == 2){
        return 1;
    } else {
        return 0;
    }
}

static int checkBST_avl_impl(struct avl_tree *t, int min, int max){
    if (t != NULL){
        if (min <= t->key && max >= t->key){                // if the node is valid
            int sx = checkBST_avl_impl(t->sx, min, t->key-1);   // assure its childs are valid
            int dx = checkBST_avl_impl(t->dx, t->key+1, max);
            return sx && dx;
        }
        else {      
            return 0;                                       // the node is invalid
        }
    }
    else {                                                  // an empty tree is a BST
        return 1;
    }
}

// interface
int checkBST_avl(struct avl_tree *t){
    return checkBST_avl_impl(t, INT_MIN, INT_MAX);
}

int checkAVL(struct avl_tree *avl){
    if (avl != NULL){
        if (is_violation_avl(avl)){
            return 0;
        } else {
            int sx = checkAVL(avl->sx);
            int dx = checkAVL(avl->dx);
            return sx && dx; 
        }
    } 
    return 1;
}

/**
 * Idea
 * Dato un albero T.
 * A seguito di un inserimento nel figlio sinistro del figlio sinistro di T cioè in T->sx->sx 
 * si ha che T->sx->sx ha un peso maggiore (altezza maggiore) rispetto a T->sx->dx
 * Per risolvere questa violazione allora si vuole eliminare questo peso da T->sx->sx ruotando T con 
 * il suo figlio sinistro T->sx. In pratica si ha che T->sx sale e infatti diventa la nuova radice, prendendo il 
 * posto di T : in questo modo il peso eliminato dato che l'altezza e diminuita. 
 * D'altra parte T (a assieme T->dx) scendono e dunque aumentano il peso di 1 (altezza aumenta di 1). 
 * Cosi facendo si sono bilanciati i due sottoalberi.
 * 
 * time complexity:     O(1)
 * space complexity:    O(1)
 * 
 */
struct avl_tree *rotation_sx_avl(struct avl_tree *avl){
    struct avl_tree *new_root = avl->sx;
    avl->sx = new_root->sx;
    new_root->sx = avl;
    update_h_avl(avl);
    return new_root;
}

/**
 * Idea
 * Dato un albero T.
 * A seguito di un inserimento su T->dx->dx il peso di questo sottoalbero aumenta. Dunque si vuole eliminare 
 * questo peso tramite una rotazione di T con T->dx. Cosi T e T->sx scendono a sinistra (aumentando il loro peso di 1).
 * Invece T->dx prende il posto di T in radice salendo di un livello: l'altezza diminuisci e il peso si bilancia.
 * 
 * 
 * time complexity:     O(1)
 * space complexity:    O(1)
 * 
 */
struct avl_tree *rotation_dx_avl(struct avl_tree *avl){
    struct avl_tree *new_root = avl->dx;
    avl->dx = new_root->sx;
    new_root->sx = avl;
    update_h_avl(avl);
    return new_root;
}

/**
 * Idea
 * Dato un albero T.
 * A seguito di un inserimento su T->sx->dx il peso di questo sottoalbero aumenta. Dunque si vuole eliminare 
 * questo peso tramite due rotazioni: 
 *  - Si sposta il peso da T->sx->dx su T->sx->sx tramite una rotazione destra.
 *  - Si elimina il peso tramite una rotazione sx 
 * Simmetrico per rotazione doppia dx.
 * 
 * time complexity:     O(1)
 * space complexity:    O(1)
 * 
 */
struct avl_tree *double_rotation_sx_avl(struct avl_tree *avl){
    avl->sx = rotation_dx_avl(avl->sx); // sposta il peso da avl->sx->dx su avl->sx->sx
    return rotation_sx_avl(avl);        // elimina il peso da avl->sx->sx
}

struct avl_tree *double_rotation_dx_avl(struct avl_tree *avl){
    avl->dx = rotation_sx_avl(avl->dx); // sposta il peso da avl->dx->sx su avl->dx->dx
    return rotation_dx_avl(avl);        // elimina il peso da avl->dx->dx
}

struct avl_tree *balance_sx_avl(struct avl_tree *avl){
    if (is_violation_avl(avl)){
        /* inserimento su T->sx->sx => il peso sta su T->sx->sx*/
        if (get_h_avl(avl->sx->sx) > get_h_avl(avl->sx->dx)){ 
            avl = rotation_sx_avl(avl);
        } else {
            avl = double_rotation_sx_avl(avl);
        }
    } else {
        update_h_avl(avl);
    }
    return avl;
}

struct avl_tree *balance_dx_avl(struct avl_tree *avl){
    if (is_violation_avl(avl)){
        if (get_h_avl(avl->dx->dx) > get_h_avl(avl->dx->sx)){
            avl = rotation_dx_avl(avl);
        } else {
            avl = double_rotation_dx_avl(avl);
        }
    } else {
        update_h_avl(avl);
    }
    return avl;
}

/**
 * Idea
 * Dato in input un albero T e un valore chiave k. 
 * Per eseguire un inserimento si segue lo stesso ragionamento di una ricerca:
 * si segue il percorso lungo il quale si trova o si dovrebbe trovare k e si distinguono 
 * i seguenti casi
 *  - caso base: T è NULL (albero vuoto) => in questo caso si crea un nodo.
 * se T non è NULL
 *  - caso base: si trova k: l'albero non viene modificato, si ritorna direttamente T così com'è.
 *  - se key > k => k sta a sx => inserisci a sinistra. Bilancia se necessario.
 *  - se key < k => k sta a dx => inserisci a destra. Bilancia se necessario.
 * 
 * Time complexity:     Θ(h)
 *  - Insert segue il percorso di ricerca di k. L'albero di ricorsione sarà lineare sulla 
 *    lunghezza del percorso e quindi sull'altezza dell'albero nel caso peggiore.
 *    Considera che il bilanciamento viene eseguito solo una volta nel caso di un inserimento, 
 *    dunque il suo contributo sarà costante. Allora è la ricerca che ha un impatto asintotico rispetto
 *    alla dimensione dell'input.
 *  
 * Space complexity:    Θ(h) è ricorsivo in coda.
 * 
 */
struct avl_tree *insertAVL(struct avl_tree *avl, int k){
    if (avl != NULL){
        if (avl->key == k){
            return avl;
        } else if (avl->key > k){
            avl->sx = insertAVL(avl->sx, k);
            avl = balance_dx_avl(avl);
        } else {
            avl->dx = insertAVL(avl->dx, k);
            avl = balance_sx_avl(avl); 
        }
        return avl;
    } else {
        return create_avl_node(k);
    }
}





