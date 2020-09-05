#include <stdio.h>
#include <stdlib.h>

// Estrutura
struct noArvore {
    int valor;
    struct noArvore *esq;
    struct noArvore *dir;
    //struct noArvore *pai; nao sei se vai usar
};
typedef struct noArvore tipoArv;

tipoArv *inicializaArvore(tipoArv *no) {
    no = NULL;
    return no;
}

tipoArv *inserirNo(tipoArv *no, int valor) {
    if(no == NULL) { // se a arvore estiver vazia, entao insere como no raiz
        no = (tipoArv *) malloc(sizeof(tipoArv));
        no->valor = valor;
        no->esq = NULL;
        no->dir = NULL;
    }
    
    else if(valor < no->valor) { // se o nó a ser inserido for menor ou igual ao nó atual// se o no a ser inserido for menor ou igual ao nó atual
        no->esq = inserirNo(no->esq, valor); // entao caminha para a esquerda
    }
    
    else if(valor > no->valor){ // se o nó a ser inserido for maior que o nó atual
        no->dir = inserirNo(no->dir, valor); // entao caminha para a direita
    }
    return no;
}

tipoArv *valorMinimo(tipoArv *no) {
    while(no->esq != NULL) {
        no = no->esq;
    }
    return no;
}

// faz a remocao de um no da arvore, com base no valor
tipoArv *removerNo(tipoArv *no, int valor) {

    if(no == NULL) {
        return NULL;
    }
    if(valor < no->valor) { // se o nó a ser inserido for menor ou igual ao nó atual// se o no a ser inserido for menor ou igual ao nó atual
        no->esq = removerNo(no->esq, valor); // entao caminha para a esquerda
    }
    else if(valor > no->valor){ // se o nó a ser inserido for maior que o nó atual
        no->dir = removerNo(no->dir, valor); // entao caminha para a direita
    }
    else {
        if((no->esq == NULL) && (no->dir == NULL)) { // se for no folha, apenas remove
            free(no);
            no = NULL;
        }
        else if(no->esq == NULL) { // se tem filhos somente a direta
            tipoArv *aux = no;
            no = no->dir; // troca pelo seu primeiro no a direita
            free(aux);
        }
        else if(no->dir == NULL) { // se tem filhos somente a esquerda
            tipoArv *aux = no;
            no = no->esq;
            free(aux);
        }
        else { // se tem filhos a esquerda E a direita
            tipoArv *min = valorMinimo(no->dir); // obtem a menor chave da subarvore da direita
            no->valor = min->valor;
            no->dir = removerNo(no->dir, min->valor);
        }
    }

    return no;
}

// realiza a impressao da arvore Em ordem
void imprimirArvore(tipoArv *no) {

    if(no != NULL) {
        imprimirArvore(no->esq);
        printf("%i ", no->valor);
        imprimirArvore(no->dir);
    }
}

// realiza a busca na arvore pelo seu valor
tipoArv *pesquisa(tipoArv *no, int valor) {
    
    tipoArv *achou;
    
    if(no == NULL) {
        return NULL;
    }
    else if(no->valor == valor) {
        return no;
    }

    if(no->valor > valor) {
        achou = pesquisa(no->esq, valor);
    }

    else {
        achou = pesquisa(no->dir, valor);
    }
}
// controla se o programa deve inserir ou remover um elemento
tipoArv *controlador(tipoArv *no, int valor) {

    tipoArv *temp = pesquisa(no, valor);
    
    if(temp == NULL) {
        no = inserirNo(no, valor);
    } else {
        no = removerNo(no, valor);
    }
    return no;
}

// obtem o tamanho da arvore
int tamanhoDicionario(tipoArv *no) { 

    if (no == NULL)
        return 0;
    else {          
        int contEsq = tamanhoDicionario(no->esq);         
        int contDir = tamanhoDicionario(no->dir); 
        return contEsq + contDir + 1;   
    }
}

// obtem a altura da arvore
int alturaArv(tipoArv *no) {

    if (no == NULL) 
        return 0; // altura da árvore vazia
    else {
        int hEsq = alturaArv(no->esq);
        int hDir = alturaArv(no->dir);
        if (hEsq < hDir)
            return hDir + 1;
        else
            return hEsq + 1;
   }
}

int main() {
    
    tipoArv *arvore;
    arvore = inicializaArvore(arvore);
    
    // leitura dos inteiros a serem inseridos na arvore  
    int op, num;
    while(1) {
        scanf(" %d", &op);
        if(op < 0) break;
        arvore = inserirNo(arvore, op);
    }
    
    // leitura do numero a ser removido/inserido
    scanf("%d", &num);
    
    // impressao do tamanho e altura da arvore antes
    printf("%d %d\n",
        tamanhoDicionario(arvore),
        alturaArv(arvore)
    );

    // controla se o numero deve ser inserido ou removido da arvore
    arvore = controlador(arvore, num);
    
    // impressao do tamanho e altura da arvore depois
    printf("%d %d",
        tamanhoDicionario(arvore),
        alturaArv(arvore)
    );
    
}

