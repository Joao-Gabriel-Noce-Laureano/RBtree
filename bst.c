#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

#define RED 1
#define BLACK 0

int id = 0;
link novoNo (int item, link l, link r) {
	link t = malloc(sizeof(struct node));
	t->item = item;
	t->pai = NULL;
	t->l = l;
	t->r = r;
	t->N = 1;
	t->cor = RED;
	t->altura = 0; //inicializando altura como 0 *****
	t->id = id++;
	return t;
}
Tree createTree(){
	Tree t = malloc (sizeof (struct tree));
	t->z = malloc (sizeof(struct node));
	t->head = t->z;
	t->z->l = t->z;
	t->z->N = 0;
	t->z->altura = -1; //colocando a altura do nó exterior como -1 para testes em que um dos galhos da árvore está vazio.************
	t->z->cor = BLACK;
	t->z->r = t->z;
	
	return t;
}


link avo(link n)
{
	if ((n != NULL) && (n->pai != NULL))
		return n->pai->pai;
	else
		return NULL;
}

link tio(Tree t, link n)
{
	link g = avo(n);
	if (g == NULL)
		return NULL; // Não tem avô = não tem tio
	if (n->pai == g->l)
		if(g->r == t->z) return NULL;
		else return g->r;
	else
		if(g->l == t->z) return NULL;
		else return g->l;
}



link rotR (Tree t, link h) { //funções de rotação agora atualizam a altura e o número de nós das sub-árvores ***********
	
	link x = h->l;
	if(h == t->head) t->head = x;
	x->pai = h->pai;
	if(h->pai!=NULL)
	{
		if(h->pai->l == h) h->pai->l = x; 
		else h->pai->r = x; 
	}
	h->l = x->r;
	x->r = h;
	h->pai = x;

	x->r->N = x->r->l->N + x->r->r->N + 1;
	x->N = x->l->N + x->r->N + 1;
	return x;
}

link rotL (Tree t, link h) { //funções de rotação agora atualizam a altura e o número de nós das sub-árvores ***********
	link x = h->r; 
	if(h == t->head) t->head = x;
	x->pai = h->pai;
	if(h->pai!=NULL)
	{
		if(h->pai->l == h) h->pai->l = x; 
		else h->pai->r = x; 
	}
	h->r = x->l; 
	x->l = h; 
	h->pai = x;
	

	x->l->N = x->l->l->N + x->l->r->N + 1;
	x->N = x->l->N + x->r->N + 1;
	return x;
}



link searchR(Tree t, link h, int query) {
	if (h == t->z) {
	return NULL;
	}
	if(h->item == query) 
	return h;
	if (h->item >= query) 
	return searchR(t, h->l, query);
	return searchR(t, h->r, query);
} 


link search (Tree t, int query){
	link x = searchR(t, t->head, query);
	if(x == NULL) printf("N%c %d n%co encontrado!\n",162,query,198);
	else printf("N%c %d encontrado!\n",162,query);
	return x;
}

link insertR (Tree t, link h, link n) {
	if (h == t->z) {
	return  n;
	}
	
	if(h->item >= n->item)
	h->l = insertR(t, h->l, n);
	else 
	h->r = insertR(t, h->r, n);
	(h->N)++;
	return h;
}

link insert (Tree t, int item){
	if(t->head == t->z) {
		return (t->head =novoNo(item, t->z, t->z));
	}
	return insertR(t, t->head, novoNo(item, t->z, t->z));
}

void imprimeEmOrdem (Tree t, link h){
	if(h == t->z) return;
	imprimeEmOrdem (t, h->l);
	printf("<chave: %d N: %d>", h->item, h->N); 
	imprimeEmOrdem (t, h->r);
}

void imprimePosOrdem (Tree t, link h){
	if(h == t->z) return;
	imprimePosOrdem (t, h->l);
	imprimePosOrdem (t, h->r);
	printf("<chave: %d N: %d>", h->item, h->N); 
}
void imprimePreOrdem (Tree t, link h, int k) {
	if(h == t->z) return;
	for(int i = 0; i <= k; i++)
		printf (" . ");
	printf("<chave: %d N: %d>\n", h->item, h->N); 
	imprimePreOrdem (t, h->l, k + 1); 
	imprimePreOrdem (t, h->r, k + 1);
}


void printnode (char  *x, int h) {
    int i;
    for(i = 0; i < h; i++)
        printf("\t");
    printf("%s\n", x);
}
int c = 0;
void imprimeR(Tree a, link t){
    char s[255];
    if(t==a->z) { return;}
    imprimeR(a,t->r);
	if(t->cor == BLACK) printf ("%d [ label = \"<f0>| <f1> %d (%d) | <f2>\" ]\n", t->id, t->item, t->N); 
	else printf ("%d [ label = \"<f0>| <f1> %d (%d) | <f2>\", color = red ]\n", t->id, t->item, t->N); 
    if(t->l != a->z){
        printf("%d:f0->%d:f1;\n", t->id, t->l->id);
    } else {
        printf("z%d [ shape=point ];\n", c);
        printf("%d:f0->z%d;\n", t->id, c);
        c++;
    }
    if(t->r != a->z){
        printf("%d:f2->%d:f1;\n", t->id, t->r->id);
    } else {
        printf("z%d [ shape=point ];\n", c);
        printf("%d:f2->z%d;\n", t->id, c );
        c++;
    }
    imprimeR(a,t->l);
}
void imprime(Tree a, char *s) {
    c = 0;
    printf("digraph %s {\n", s);
    printf ("node [shape=record,style=rounded, height=.1]\n");
    imprimeR(a, a->head);
    printf("}\n");
}
void imprimeFromNode(Tree a, link h, char *s) {
	c = 0;
	printf("digraph  {\n" );
	printf ("name [label = \"%s\",shape=plaintext]\n", s);
	printf ("node [shape=record,style=rounded, height=.1]\n");
	imprimeR(a, h);
	printf("}\n");
}

void insCasos(Tree t, link h){
	if (h->pai == NULL)
	{
		h->cor = BLACK;
	} 
	else
	{
		if (h->pai->cor == BLACK) return;
		else
		{
			link u = tio(t,h), g = avo(h);

			if ((u != NULL) && (u->cor == RED)) {
				h->pai->cor = BLACK;
				u->cor = BLACK;
				g->cor = RED;
				insCasos(t,g);
			} 
			else {
				if ((h == h->pai->r) && (h->pai == g->l)) {
					h->pai = rotL(t,h->pai);
					h = h->l;
				} else if ((h == h->pai->l) && (h->pai == g->r)) {
					h->pai = rotR(t,h->pai);
					h = h->r;
				}
				h->pai->cor = BLACK;
				g->cor = RED;
				if ((h == h->pai->l) && (h->pai == g->l)) {	
					g = rotR(t,g);
				} 
				else {
					g = rotL(t,g);
				}
			}
		}
			
	}		
}

link RNinsertR (Tree t, link h, link n){ //Função criada baseada na AVLinsertR
	if (h == t->z) {
	    return  n; 
	}
	
	if(h->item >= n->item){
		h->l = RNinsertR(t, h->l, n);
		h->l->pai = h;
	}
	else {
		h->r = RNinsertR(t, h->r, n);
		h->r->pai = h;
	}

	h->N++;
	
	return h;
}

link RNinsert (Tree t, int item){ //Função criada baseada na AVLinsert
	if(t->head == t->z) {
		t->head =novoNo(item, t->z, t->z);
		t->head->cor = BLACK;
		return t->head;
	}
	link novo = novoNo(item, t->z, t->z);
	t->head = RNinsertR(t, t->head, novo);
	insCasos(t, novo);
	return t->head;
}





