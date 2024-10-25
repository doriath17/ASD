#include <stdlib.h>
#include <limits.h>
#include <iso646.h>
#include "bst.h"
#include "util.h"


/**
 * Idea
 * The main idea of this algorithm is to pass each call information 
 * abount the min or max value a node could have. So min and max 
 * essentially represents the range a node's vale can be in.
 *      - When descending left it is important to keep info about the 
 *        max to set an upperbound. This is because node on the left 
 *        should be <= than the actual node's value.
 *      - When descending right it is important to keep info about the 
 *        max and the min: node's value must be smaller than the the last max
 *        (and the last max is set on the last right descend) but can be greater 
 *        than the actual node's value.
 * Every call actually controls that the total order proprerty is respected.
 * 
 * Time complexity:     Θ(n)
 * Space complexity:    Θ(1) 
 * 
 * Note:
 *      - the root will never cause violation.
 *      - an empty tree is always a BST by definition.
 *      - using t->key-1 or t->key+1 assure the unicity of the values.
 *        To allow different node to have the same value just use t->key.
 */
static int checkBST_impl(struct binary_tree *t, int min, int max){
    if (t != NULL){
        if (min <= t->key && max >= t->key){                // if the node is valid
            int sx = checkBST_impl(t->sx, min, t->key-1);   // assure its childs are valid
            int dx = checkBST_impl(t->dx, t->key+1, max);
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
int checkBST(struct binary_tree *t){
    return checkBST_impl(t, INT_MIN, INT_MAX);
}


/**
 * Idea
 * In a BST:
 *      - min is in the right-most node of the t->sx
 *      - max is in the left-most node of t->dx
 * This is because of the total order proprerty. So for ex.for the min: 
 *  - from the root continuing descending left.
 * 
 * Time complexity:     Θ(h) where h is the tree's height.
 * Space complexity:    Θ(1)
 * 
 * Note:
 *  - the search of min and max is a specialization of find / search.
 */
struct binary_tree *minBST(struct binary_tree *t){
    if (t!=NULL){
        if (t->sx != NULL){
            return minBST(t->sx);
        }
        else {
            return t;
        }
    }
    else {
        return t;
    }
}


struct binary_tree *maxBST(struct binary_tree *t){
    if (t!=NULL){
        if (t->dx != NULL){
            return maxBST(t->dx);
        }
        else {
            return t;
        }
    }
    else {
        return t;
    }
}


/**
 * Idea: 
 * La ricerca di un valore k in un ABR è molto simile alla ricerca binaria: 
 *  - se il valore del nodo corrente è minore di k      => cerca nel sottoalbero destro
 *  - se il valore del nodo corrente è maggiore di k    => cerca nel sottoalbero sinistro
 * Questo algoritmo percorre un solo percorso dell'albero (per questo avrà complessità 
 * lineare sull'altezza dell'ABR). 
 * 
 * Time complexity:     Θ(h) dove h è l'altezza dell'ABR.
 *  - Nota: a differenza degli array, questa ricerca non è logaritmica come la ricerca binaria
 *          perché l'altezza dell'ABR non è vicolata ad essere logaritmica su n.
 *          -> caso peggiore sarà lineare su n: Θ(n)
 *          -> in generale puoi dire: O(n) e Ω(log(n))
 *  
 * Space complexity:    Θ(1) tail recursive.
 * 
 * Note:
 *  - Puoi eseguire questo tipo di ricerca solo se esiste un ordinamento totale.
 */
struct binary_tree *searchBST_recursive(struct binary_tree *bst, int k){
    if (bst not_eq NULL){
        if (bst->key < k){          // cerca a destra
            return searchBST_recursive(bst->dx, k);
        } else if (bst->key > k){   // cerca a sinistra 
            return searchBST_recursive(bst->sx, k);
        } else {                    // ha trovato k
            return bst;
        }
    }
    return bst;
}

struct binary_tree *searchBST_iter(struct binary_tree *bst, int k){
    while (bst not_eq NULL){
        if (bst->key < k){
            bst = bst->dx;
        } else if (bst->key > k) {
            bst = bst->sx;
        } else {
            return bst;
        }
    }
    return bst;
}

struct binary_tree *searchBST(struct binary_tree *bst, int k){
    return searchBST_recursive(bst, k);
}


/**
 * Idea
 * dato un valore k di cui cercare il successore in t hai 3 casi possibili:
 *  - k è presente nell'albero + esiste il sottoalbero destro
 *    cerca il minimo nel sottoalbero destro.
 *  - k è presente nell'albero + NON esiste il sottoalbero destro
 *    il successore sta lungo il percorso di ricerca di k e in particolare è
 *    l'ultimo nodo da cui sono sceso a sinistra (che rappresenterebbe il 
 *    minimo valore nell'albero che è maggiore di k).
 *  - k non è presente in t
 *    anche se k non c'è il percorso esiste e posso considerare come nel 
 *    caso precedente l'ultimo nodo da cui sono sceso a sinistra.
 * 
 * Time complexity:      Θ(h) dove h è la lunghezza del percorso di ricerca.
 * Space complexity:     Θ(h) questa implementazione non è tail recursive
 *                       Θ(1) se reso tail recursive o fatto iterativo.
 * 
 * Nota:
 *  - succ = t verrà eseguita solo una volta quando una chiamata padre scende
 *    a sinistra e il figlio ritorna NULL, indicando dunque che k non è presente
 *    e che il padre (o l'ultima chiamata che era scesa a sx) saranno il nodo
 *    con il successore.
 */
struct binary_tree *successorBST(struct binary_tree *t, int k){
    struct binary_tree *succ = NULL;
    if (t != NULL){
        if (t->key == k) {
            if (t->dx != NULL){
                succ = minBST(t->dx);
            }
        } else if (t->key < k){
            succ = successorBST(t->dx, k);
        } else {
            succ = successorBST(t->sx, k);
            if (succ == NULL){
                succ = t;
            }
        }
    }
    return succ;
}


/**
 * Idea
 * dato un valore k di cui cercare il predecessore in t hai 3 casi possibili:
 *  - k è presente nell'albero + esiste il sottoalbero sinistro
 *    cerca il massimo del sottoalbero sinistro.
 *  - k è presente nell'albero + NON esiste il sottoalbero sinistro
 *    il successore sta lungo il percorso di ricerca di k e in particolare è
 *    l'ultimo nodo da cui sono sceso a destra (che rappresenterebbe il 
 *    massimo valore nell'albero che è minore di k).
 *  - k non è presente in t
 *    anche se k non c'è il percorso esiste e posso considerare come nel 
 *    caso precedente l'ultimo nodo da cui sono sceso a destra.
 * 
 * Time complexity:      Θ(h) dove h è la lunghezza del percorso di ricerca.
 * Space complexity:     Θ(h) questa implementazione non è tail recursive
 *                       Θ(1) se reso tail recursive o fatto iterativo.
 * 
 * Nota:
 *  - succ = t verrà eseguita solo una volta quando una chiamata padre scende
 *    a sinistra e il figlio ritorna NULL, indicando dunque che k non è presente
 *    e che il padre (o l'ultima chiamata che era scesa a sx) saranno il nodo
 *    con il successore.
 */
struct binary_tree *predecessorBST(struct binary_tree *t, int k){
    struct binary_tree *succ = NULL;
    if (t != NULL){
        if (t->key == k) {
            if (t->sx != NULL){     // k presente e sx esiste
                succ = maxBST(t->sx);
            }
        } else if (t->key > k){     // k sta a sinistra di t->key 
            succ = predecessorBST(t->sx, k);
        } else {                    // k sta a destra di t->key
            succ = predecessorBST(t->dx, k);
            if (succ == NULL){
                succ = t;
            }
        }
    }
    return succ;
}

/**
 * Idea: 
 * L'idea base è quella di inserire un nodo al posto di un albero vuoto / nodo NIL.
 * Dunque se il nodo viene inserito, esso è inserito come foglia. 
 * Ovviamente, per rispettare l'ordine totale, devi ricercare la posizione corretta in 
 * cui poter inserire il nodo: dunque l'inserimento si basa su una ricerca nell'albero 
 * del valore k da inserire (puoi infatti notare la stessa struttura dell'algo. di ricerca).
 *  - se k è presente nell'albero: non inserisci / non modifichi l'albero volendo mantenere
 *    l'unicità dei valori chiave.
 *  - se invece k non sarà presente la ricerca ti porterà a NULL, cioè ad una foglia che avrà 
 *    come figli due alberi vuoti in cui poter inserire il nuovo nodo contenente k.
 * 
 * CON: negli ABR ogni inserimento può far aumentare l'altezza e potenzialmente distruggere 
 * l'efficienza poiché l'albero assume una struttura / forma più sbilanciata. 
 * 
 * Time complexity:     Θ(h) dove h è l'altezza dell'ABR. 
 * Space complexity:    Θ(h) (non è tail recursive).
 * 
 * Nota:
 *  - questo algo. può essere visto come un inserimento in coda ad una lista: il percorso
 *    è una lista.
 */
struct binary_tree *insertBST(struct binary_tree *t, int k){
    if (t not_eq NULL){
        if (t->key == k){
            return t;
        }
        else if (t->key < k) {
            t->dx = insertBST(t->dx, k);
            return t;
        }
        else {
            t->sx = insertBST(t->sx, k);
            return t;
        }
    }
    else {
        return create_node(k);
    }
}