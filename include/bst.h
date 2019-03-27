#ifndef BST_H
#define BST_H

template <typename T>
class BST
{
private:
	struct arv
	{
		T m_dado;
		arv *esq;
		arv *dir;
	};

	arv *m_raiz;

	// Insercao e remocao
	auto criaNoh(T dado);
	auto insereNoh(arv *raiz, T dado);
	auto deletaNoh(arv *raiz, T dado);
	auto esvaziaNoh(arv *raiz, T dado);

	// Impressao
	void order(arv *raiz);
	void PreOrder(arv *noh);

	// Auxiliares
	auto balanceia(arv *raiz, int &balance, int &balanceFilho);
	int  FatorBalanceamento(arv *noh);
	int  altura(arv* noh);
	auto nohMaiorAltura(arv *noh);
	auto maiorNohEsq(arv *nohEsq);
	auto rodaE(arv *noh);
	auto rodaD(arv *noh);

public:
	BST();
	~BST();

	void insere(T dado);
	void deleta(T dado);
	void esvazia();
	void imprimeOrdem();
	void preOrder();
};

#endif	//BST_H
