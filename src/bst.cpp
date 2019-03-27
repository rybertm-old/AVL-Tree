#include "bst.h"

#include <iostream>

template class BST<int>;
template class BST<float>;
template class BST<double>;
template class BST<char>;

template <typename T>
BST<T>::BST()
{
	m_raiz = nullptr;
}

template<typename T>
BST<T>::~BST()
{
	esvazia();
}

/* --------------------Insercao e Remocao-------------------------------------*/

template<typename T>
void BST<T>::insere(T dado)
{
	m_raiz = insereNoh(m_raiz, dado);
}

template<typename T>
void BST<T>::deleta(T dado)
{
	m_raiz = deletaNoh(m_raiz, dado);
}

template<typename T>
void BST<T>::esvazia()
{
	while (m_raiz != nullptr)
	{
		m_raiz = esvaziaNoh(m_raiz, m_raiz->m_dado);
	}
}

template<typename T>
auto BST<T>::insereNoh(arv *raiz, T dado)
{
	if (raiz == nullptr)
		return criaNoh(dado);

	if (dado < raiz->m_dado)
		raiz->esq = insereNoh(raiz->esq, dado);
	else if (dado > raiz->m_dado)
		raiz->dir = insereNoh(raiz->dir, dado);
	else
		return raiz;

	//Pega o fator de balanceamento
	int balance = FatorBalanceamento(raiz);
	int balanceFilho;

	//Verifica em qual lado foi inserido o noh e calcula o FatorBalanceamento do filho do noh desbalanceado
	if (dado > raiz->m_dado)
		balanceFilho = FatorBalanceamento(raiz->dir);
	else if (dado < raiz->m_dado)
		balanceFilho = FatorBalanceamento(raiz->esq);

	//Nao modifica se estiver balanceada
	return balanceia(raiz, balance, balanceFilho);
}

template<typename T>
auto BST<T>::criaNoh(T dado)
{
	arv *noh = new arv;

	noh->m_dado = dado;
	noh->esq = nullptr;
	noh->dir = nullptr;

	return noh;
}

template<typename T>
auto BST<T>::deletaNoh(arv *raiz, T dado)
{
	if (raiz == nullptr)
		return raiz;

	//Recursa ate achar o noh com o dado

	if (dado < raiz->m_dado)
		raiz->esq = deletaNoh(raiz->esq, dado);

	else if (dado > raiz->m_dado)
		raiz->dir = deletaNoh(raiz->dir, dado);

	else
	{
		//Caso o noh tenha apenas um subnoh ou nenhum subnoh

		if (raiz->esq == nullptr)
		{
			arv *temp = raiz->dir;
			delete raiz;
			return temp;
		}
		else if (raiz->dir == nullptr)
		{
			arv *temp = raiz->esq;
			delete raiz;
			return temp;
		}

		//Caso o noh tenha dois subnohs pega-se o noh maior da esquerda do noh atual, copia-se o conteudo para o noh atual
		// e exclui-se o maior noh a esquerda
		arv *temp = maiorNohEsq(raiz->esq);

		raiz->m_dado = temp->m_dado;

		raiz->esq = deletaNoh(raiz->esq, temp->m_dado);
	}

	//Pega o fator de balanceamento
	int balance = FatorBalanceamento(raiz);

	//Noh filho sera o noh com maior altura
	arv *maisAlto = nohMaiorAltura(raiz);
	int balanceFilho = FatorBalanceamento(maisAlto);

	return balanceia(raiz, balance, balanceFilho);
}

template<typename T>
auto BST<T>::esvaziaNoh(arv * raiz, T dado)
{
	if (raiz == nullptr)
		return raiz;

	//Recursa ate achar o noh com o dado

	if (dado < raiz->m_dado)
		raiz->esq = esvaziaNoh(raiz->esq, dado);

	else if (dado > raiz->m_dado)
		raiz->dir = esvaziaNoh(raiz->dir, dado);

	else
	{
		//Caso o noh tenha apenas um subnoh ou nenhum subnoh

		if (raiz->esq == nullptr)
		{
			arv *temp = raiz->dir;
			delete raiz;
			return temp;
		}
		else if (raiz->dir == nullptr)
		{
			arv *temp = raiz->esq;
			delete raiz;
			return temp;
		}

		//Caso o noh tenha dois subnohs pega-se o noh maior da esquerda do noh atual, copia-se o conteudo para o noh atual
		// e exclui-se o maior noh a esquerda
		arv *temp = maiorNohEsq(raiz->esq);

		raiz->m_dado = temp->m_dado;

		raiz->esq = esvaziaNoh(raiz->esq, temp->m_dado);
	}

	return raiz;
}

/* ------------------------Impressao-------------------------------------*/

template<typename T>
void BST<T>::imprimeOrdem()
{
	if (m_raiz != nullptr)
		order(m_raiz);
	else
		std::cout << "\nArvore vazia" << std::endl;
}

template<typename T>
void BST<T>::preOrder()
{
	PreOrder(m_raiz);
}

template<typename T>
void BST<T>::order(arv *raiz)
{
	if (raiz != nullptr)
	{
		order(raiz->esq);
		std::cout << raiz->m_dado << " ";
		order(raiz->dir);
	}
}

template<typename T>
void BST<T>::PreOrder(arv *raiz)
{
	if (raiz != nullptr)
	{
		std::cout << raiz->m_dado << " ";
		PreOrder(raiz->esq);
		PreOrder(raiz->dir);
	}
}

/* ------------------------Auxiliares-------------------------------------*/

template<typename T>
auto BST<T>::balanceia(arv * raiz, int & balance, int & balanceFilho)
{
	//Caso 1

	if (balance > 1 && balanceFilho == 1)
		return rodaD(raiz);

	if (balance < -1 && balanceFilho == -1)
		return rodaE(raiz);

	//Caso 2

	if (balance > 1 && balanceFilho == -1)
	{
		raiz->esq = rodaE(raiz->esq);
		return rodaD(raiz);
	}

	if (balance < -1 && balanceFilho == 1)
	{
		raiz->dir = rodaD(raiz->dir);
		return rodaE(raiz);
	}

	else
		return raiz;
}

template<typename T>
int BST<T>::FatorBalanceamento(arv *noh)
{
	if (noh == nullptr)
		return 0;
	else
		return altura(noh->esq) - altura(noh->dir);
}

template<typename T>
int BST<T>::altura(arv *noh)
{
	if (noh == nullptr)
		return 0;
	else
	{
		int hEsq = altura(noh->esq);
		int hDir = altura(noh->dir);
		if (hEsq < hDir)
			return hDir + 1;
		else
			return hEsq + 1;
	}
}

template<typename T>
auto BST<T>::nohMaiorAltura(arv *noh)
{
	int altEsq = altura(noh->esq);
	int altDir = altura(noh->dir);
	return (altEsq > altDir) ? noh->esq : noh->dir;
}

template<typename T>
auto BST<T>::maiorNohEsq(arv *nohEsq)
{
	arv *atual = nohEsq;

	while (atual->dir != nullptr)
		atual = atual->dir;

	return atual;
}

template<typename T>
auto BST<T>::rodaE(arv *noh)
{
	arv *p = noh->dir;
	arv *temp = p->esq;

	//Rotaciona
	p->esq = noh;
	noh->dir = temp;

	//Retorna nova raiz
	return p;
}

template<typename T>
auto BST<T>::rodaD(arv *noh)
{
	arv *p = noh->esq;
	arv *temp = p->dir;

	//Rotaciona
	p->dir = noh;
	noh->esq = temp;

	//Retorna nova raiz
	return p;
}