#include <iostream>
using namespace std;

class No {
public:
    int dado;
    No* proximo;
    // Construtor para inicializar os membros
    No(int dado, No* p = nullptr) {
        this->dado = dado;
        this->proximo = p;
    }
};

class ListaEncadeada {
public:
    No *head;
    ListaEncadeada(){
        this -> head = new No(0);
    }
    void add(int info) {
        No *novo = new No(info);
        No *p = head;
        while (p->proximo != nullptr) p = p->proximo;
        p->proximo = novo;
    }

    void remover(int info) {
        if (head->proximo == nullptr) {
            return;
        } else {
            No *p = head;
            while (p->proximo != nullptr) {
                if (p->proximo->dado != info) p = p -> proximo;
                else {
                    p->proximo = p->proximo->proximo;
                    break;
                }
            }
        }
    }
    
    
    int contar() {
        No* p = head->proximo;
        int contador = 0;
        while (p != nullptr) {
            contador++;
            p = p->proximo;
        }
        return contador;
    }
    
    bool buscar(int dado) {
        No* p = head->proximo;
        while (p != nullptr) {
            if (dado == p->dado) return true;
            p = p->proximo;
        }
        return false;
    }
    
    void inverter() {
        No* p = head->proximo;
        No* anterior = head->proximo;
        if (p == nullptr) return;
        if (p->proximo == nullptr) return;
        if (p == anterior) p = p->proximo;
        anterior->proximo = nullptr;
        while (p->proximo != nullptr) {
            No* proximo = p->proximo;
            p->proximo = anterior;
            anterior = p;
            p = proximo;
        }
        p->proximo = anterior;
        head->proximo = p;
    }
    
    int nfinal(int n) {
        if (head->proximo == nullptr) {
            return -1;
        }
        No* p = head->proximo;
        int tamanho_total = contar();
        int contagem = 0;
        while (p != nullptr) {
            if (tamanho_total - contagem == n) return p->dado;
            contagem++;
            p = p->proximo;
        }
        return -1;
    }
    
    void removern(int n) {
        No *p = head;
        int contador = 0;
        while (p->proximo != nullptr) {
            contador++;
            if (contador != n) p = p -> proximo;
            else {
                p->proximo = p->proximo->proximo;
                break;
            }
        }
    }
    
    void duplicar() {
        No* p = head->proximo;
        while (p != nullptr) {
            No* novo = new No(p->dado, p->proximo);
            p->proximo = novo;
            p = novo->proximo;
        }
    }
    
    void inverter_recursivo() {
        
    }
    
    void print() {
        No* p = head->proximo;
        while (p != nullptr) {
            cout << p->dado << " ";
            p = p->proximo;
        }
        cout << endl;
    }
};

int main() {
    ListaEncadeada lista;
    
    lista.add(10);
    lista.add(20);
    lista.add(30);
    cout << "Lista inicial: ";
    lista.print();

    lista.remover(20);
    cout << "Após remover 20: ";
    lista.print();

    lista.add(40);
    cout << "Após adicionar 40: ";
    lista.print();
    
    cout << "Duplicando lista: ";
    lista.duplicar();
    lista.print();
    
    cout << "Num de elementos na lista: " << lista.contar() << endl;
    cout << "20 está na lista: " << lista.buscar(20) << endl;
    cout << "30 está na lista: " << lista.buscar(30) << endl;
    
    cout << "Lista atual: ";
    lista.print();
    lista.inverter();
    cout << "Lista depois de inverter: ";
    lista.print();
    
    cout << "Valor no índice 2 (de trás pra frente): ";
    int valor = lista.nfinal(2);
    cout << valor << endl;
    
    cout << "Valor no índice 1 (de trás pra frente): ";
    int valor2 = lista.nfinal(1);
    cout << valor2 << endl;
    
    cout << "Removendo elemento 2 da lista: ";
    lista.removern(2);
    lista.print();
    
    
    
    return 0;
}
