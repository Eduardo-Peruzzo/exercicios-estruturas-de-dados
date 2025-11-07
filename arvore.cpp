#include <iostream>
using namespace std;

class No {
public:
    int dado;
    No* esquerda;
    No* direita;
    int altura;
    
    No(int dado, No* e = nullptr, No* d = nullptr, int altura = 1) {
        this->dado = dado;
        this->esquerda = e;
        this->direita = d;
        this->altura = altura;
    }
};

class Tree {
public:
    No* raiz = nullptr;
    
    No* rotacaoDireita(No* p) {
        No* x = p->esquerda;
        No* sub_arvore = x->direita;
        
        x->direita = p;
        p->esquerda = sub_arvore;
        
        p->altura = 1 + max(altura(p->esquerda), altura(p->direita));
        x->altura = 1 + max(altura(x->esquerda), altura(x->direita));
    
        return x; // nova raiz
    }
    
    No* rotacaoEsquerda(No* p) {
        No* x = p->direita;
        No* sub_arvore = x->esquerda;

        x->esquerda = p;
        p->direita = sub_arvore;

        p->altura = 1 + max(altura(p->esquerda), altura(p->direita));
        x->altura = 1 + max(altura(x->esquerda), altura(x->direita));
    
        return x; // nova raiz
    }
    
    int altura(No* p) {
        if (p != nullptr) return p->altura;
        else return 0;
    }
    
    No* addRe(int info, No* r) {
        if (r == nullptr) return new No(info);
        else {
            if (info > r->dado) r->direita = addRe(info, r->direita);
            else r->esquerda = addRe(info, r->esquerda);
        }
        
        r->altura = 1 + max(altura(r->esquerda), altura(r->direita));
        
        int fator = altura(r->esquerda) - altura(r->direita);
        
        cout << "Nó atual: " << r->dado << endl;
        printTree(raiz);
        cout << "Altura nó atual: " << r->altura << endl;
        cout << "Fator: " << fator << endl;
        
        if (fator < -1) {
            if (info < r->direita->dado) {
                r->direita = rotacaoDireita(r->direita);
            }
            return rotacaoEsquerda(r);
        }
        if (fator > 1) {
            if (info > r->esquerda->dado) {
                r->esquerda = rotacaoEsquerda(r->esquerda);
            }
            return rotacaoDireita(r);
        }
        
        return r;
    }
    
    void addR(int info) {
        cout << "ADICIONANDO: " << info << endl;
        raiz = addRe(info, raiz);
    }
    
    void add(int info) {
        No* novo = new No(info);
        if (raiz == nullptr) raiz = novo;
        else {
            No* p = raiz;
            while (p != nullptr) {
                if (novo->dado > p->dado) {
                    if (p->direita == nullptr) {
                        p->direita = novo;
                        break;
                    }
                    else p = p->direita;
                }
                else {
                    if (p->esquerda == nullptr) {
                        p->esquerda = novo;
                        break;
                    }
                    else p = p->esquerda;
                }
            }
        }
    }
    
    void emOrdem(No* p) {
        if (p != nullptr) {
            emOrdem(p->esquerda);
            cout << p->dado << " ";
            emOrdem(p->direita);
        }
    }

    void print() {
        emOrdem(raiz);
        cout << endl;
    }
    
    void printTree(No* p, int nivel = 0) {
        if (p == nullptr) return;

        // Primeiro imprime o lado direito
        printTree(p->direita, nivel + 1);

        // Imprime o nó atual com indentação proporcional ao nível
        for (int i = 0; i < nivel; i++) cout << "    ";
        cout << p->dado << endl;

        // Depois imprime o lado esquerdo
        printTree(p->esquerda, nivel + 1);
    }
    
    void preOrdem(No* raiz) {
        if (raiz != nullptr) {
            cout << raiz->dado << " ";
            preOrdem(raiz->esquerda);
            preOrdem(raiz->direita);
        }
    }
    
    void printarPreOrdem() {
        preOrdem(raiz);
        cout << endl;
    }
    
    void posOrdem(No* raiz) {
        if (raiz != nullptr) {
            posOrdem(raiz->esquerda);
            posOrdem(raiz->direita);
            cout << raiz->dado << " ";
        }
    }
    
    void printarPosOrdem() {
        posOrdem(raiz);
        cout << endl;
    }
};

int main() {
    Tree arvore;
    arvore.add(10);
    arvore.add(5);
    arvore.add(3);
    arvore.add(20);
    arvore.add(15);
    arvore.add(7);
    arvore.add(25);

    cout << "Elementos em pré ordem: ";
    arvore.printarPreOrdem();
    
    cout << "Elementos em ordem: ";
    arvore.print();
    cout << "Elementos em pós ordem: ";
    arvore.printarPosOrdem();
    arvore.printTree(arvore.raiz);
    
    Tree arvore2;
    arvore2.addR(8);
    arvore2.addR(10);
    arvore2.addR(12);
    arvore2.addR(15);
    arvore2.addR(17);
    arvore2.addR(20);
    arvore2.addR(30);
    arvore2.addR(70);
    arvore2.addR(50);
    arvore2.addR(80);
    arvore2.addR(65);
    arvore2.addR(35);
    arvore2.addR(19);
    arvore2.addR(25);
    arvore2.addR(2);
    arvore2.addR(1);
    arvore2.addR(7);
    arvore2.addR(14);
    arvore2.addR(12);
    arvore2.addR(13);
    arvore2.addR(18);
    arvore2.addR(22);
    
    cout << "Elementos em pré ordem: ";
    arvore2.printarPreOrdem();
    
    cout << "Elementos em ordem: ";
    arvore2.print();
    cout << "Elementos em pós ordem: ";
    arvore2.printarPosOrdem();
    arvore2.printTree(arvore2.raiz);
    
    return 0;
}
