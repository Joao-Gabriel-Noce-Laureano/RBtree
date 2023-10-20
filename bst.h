#ifndef BST_H
#define BST_H

#define RED 1
#define BLACK 0

typedef struct node * link;
struct node {
  link l;
  link r;
  link pai;
  int item;
  int N;      // quantidade de nos na subarvore
  int id;     // id da nó
  int altura; //altura da sub�rvore **********
  int cor; //cor do n� 
};

typedef struct tree {
  link head; // raiz
  link z;    // n� externo
} * Tree;

Tree createTree();


link rotR (Tree t, link h);

link rotL (Tree t, link h);

link search (Tree h, int query);

link insert (Tree h, int item);

void imprimeEmOrdem (Tree t, link h);
void imprimePosOrdem (Tree t, link h);
void imprimePreOrdem (Tree t, link h, int k);

link RNinsert (Tree t, int item); 

link avo(link n);
link tio(Tree t,link n);

void insCasos(Tree t, link h);


void imprime(Tree a, char *s);
 
#endif 


