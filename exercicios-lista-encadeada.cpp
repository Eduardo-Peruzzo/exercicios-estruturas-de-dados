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
                    No* temp = p->proximo;
                    p->proximo = p->proximo->proximo;
                    delete temp;
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
                No* temp = p->proximo;
                p->proximo = p->proximo->proximo;
                delete temp;
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
    
    void remover_duplicatas() {
        No* p = head->proximo;
        while (p != nullptr) {
            No* t = p;
            while (t->proximo != nullptr) {
                if (p->dado == t->proximo->dado) {
                    No* temp = t->proximo;
                    t->proximo = t->proximo->proximo;
                    delete temp;
                } else t = t->proximo;
            }
            p = p->proximo;
        }
    }
    
    void sort() {
        No* p = head->proximo;
        
        while (p != nullptr) {
            No* t = p;
            No* menor = t;
            while (t != nullptr) {
                if (t->dado < menor->dado) {
                    menor = t;
                }
                t = t->proximo;
            }
            int temp = menor->dado;
            menor->dado = p->dado;
            p->dado = temp;
            p = p->proximo;
        }
    }
    
    No* aux_inverter_recursivo(No *no) {
        if (no == nullptr || no->proximo == nullptr) {
            head->proximo = no;
            return no;
        }
        No* ultimo = aux_inverter_recursivo(no->proximo);
        ultimo->proximo = no;
        no->proximo = nullptr;
        return no;
    }
    
    void inverter_recursivo() {
        aux_inverter_recursivo(head->proximo);
    }
    
    bool palindromo() {
        ListaEncadeada lista_invertida;

        No* p = head->proximo;
        while (p != nullptr) {
            lista_invertida.add(p->dado);
            p = p->proximo;
        }
    
        lista_invertida.inverter();
        
        p = head->proximo;
        No* t = lista_invertida.head->proximo;
        
        while(p != nullptr) {
            if (p->dado != t->dado) return false;
            p = p->proximo;
            t = t->proximo;
        }
        return true;
    }
    
    // usei um negócio chamado "algoritmo de Floyd"
    bool detectar_ciclos() {
        No* lento = head;
        No* rapido = head;
    
        while (rapido != nullptr && rapido->proximo != nullptr) {
            lento = lento->proximo;
            rapido = rapido->proximo->proximo;
    
            if (lento == rapido) return true;
        }
        return false;
    }
    
    pair<ListaEncadeada, ListaEncadeada> dividir() {
        ListaEncadeada primeira;
        ListaEncadeada segunda;
    
        if (head->proximo == nullptr) {
            return {primeira, segunda};
        }
        
        int tamanho = contar();
        int contador = 0;
        No* p = head->proximo;
        while (p != nullptr) {
            contador++;
            if (contador <= tamanho/2) primeira.add(p->dado);
            else segunda.add(p->dado);
            p = p->proximo;
        }
        return {primeira, segunda};
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

ListaEncadeada mesclar(ListaEncadeada lista1, ListaEncadeada lista2) {
    No* p = lista2.head->proximo;
    while (p != nullptr) {
        lista1.add(p->dado);
        p = p->proximo;
    }
    ListaEncadeada mesclada = lista1;
    return mesclada;
}

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
    
    cout << "Removendo duplicatas: ";
    lista.remover_duplicatas();
    lista.print();
    
    ListaEncadeada lista2;
    lista2.add(35);
    lista2.add(15);
    lista2.add(25);
    cout << "Lista 2: ";
    lista2.print();
    
    cout << "Mescla das duas: ";
    ListaEncadeada mesclada = mesclar(lista, lista2);
    mesclada.print();
    
    mesclada.sort();
    cout << "Mesclada sorted: ";
    mesclada.print();
    
    mesclada.inverter_recursivo();
    cout << "Mesclada invertida de forma recursiva: ";
    mesclada.print();
    
    ListaEncadeada palindromo;
    palindromo.add(10);
    palindromo.add(20);
    palindromo.add(10);
    cout << "Lista palindromo: ";
    palindromo.print();
    cout << "É palíndromo: " << palindromo.palindromo() << endl;
    
    cout << "Lista atual: ";
    lista.print();
    auto [l1, l2] = lista.dividir();

    cout << "Primeira metade: ";
    l1.print();
    cout << "Segunda metade: ";
    l2.print();
    
    return 0;
}
