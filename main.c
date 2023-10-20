#include <stdio.h>
#include "bst.h"

int main () {
	Tree t = createTree();
	link x;
	RNinsert(t,100);
	RNinsert(t,110);
	RNinsert(t,120);
	RNinsert(t,130);
	RNinsert(t,140);
	imprime(t, "RubraNegra");
	printf("-------------------------------------\n");
	x = search(t, 130);
	x = search(t, 150);
	x = search(t, 100);
	return 0;
}
