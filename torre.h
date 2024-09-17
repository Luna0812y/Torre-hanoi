typedef struct{
    char *ponto;
    int topo;
    int capacidade;
} Torres;

//CRUD Torre
Torres* criar_torre(int capacidade);
int torre_vazia(Torres *torre);
int torre_cheia(Torres *torre);
void empilhar(Torres *torre, char valor);
char desempilhar(Torres *torre);
void encerrar(Torres *torre);

//Jogo Torre
void distribuir_itens_aleatorios(Torres *torreR, Torres *torreG, Torres *torreB, int total);
int mover_item(char origem, char destino, Torres *torreR, Torres *torreG, Torres *torreB);
int verificar_vitoria(Torres *torreR, Torres *torreG, Torres *torreB);
int torre_contem_unico_tipo(Torres *torre, char tipo);
void imprimir_estado(Torres *torreR, Torres *torreG, Torres *torreB);
void imprimir_torres(Torres *torre1, char cor1, Torres *torre2, char cor2, Torres *torre3, char cor3);
void menu_torre();
void sair();