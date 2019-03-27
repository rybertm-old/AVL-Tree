#include "bst.h"

#include <iostream>

int main()
{
	BST<int> bst;
	bst.insere(1);
	bst.insere(4);
	bst.insere(7);
	bst.insere(-5);
	std::cout << "\nArvore" << std::endl;
	bst.preOrder();
	bst.deleta(7);
	std::cout << "\nArvore" << std::endl;
	bst.preOrder();
	std::cout << "\n\nPressione Qualquer tecla para continuar: ";
	std::cin.get();
}