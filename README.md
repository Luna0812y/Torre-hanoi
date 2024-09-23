# Jogo da Torre de Hanói

Este é um jogo simples desenvolvido com a linguagem C e suas bibliotecas, projetado para explorar pilhas estáticas como estrutura de dados. O objetivo principal é mover os discos para as torres correspondentes, permitindo ao usuário desenvolver habilidades de resolução de problemas por meio de soluções estratégicas.

## Estrutura do Projeto

- **main.c**
  - **`main.c`**: Inicialização e controle do jogo.

- **torre.c**
  - **`torre.c`**: Funções usadas no jogo.

- **torre.h**
  - **`torre.h`**: Declaração da estrutura da torre e das funções.
 
## Executar o jogo

#### 1. **Compile o projeto com um compilador C**

    ```bash
    gcc -o .\minha_torre.exe .\torre.c .\main.c 
    ```
#### 2. **Executa o programa**

    ```bash
    .\minha_torre.exe
    ```

### 2. Estrutura da Explicação do Código

#### 1. **Introdução**

Visão geral de como funciona o jogo.

O jogo permite ao jogador mover discos entre três torres: R (vermelho), G (verde) e B (azul). O objetivo é organizar os discos em uma torre específica, seguindo estas regras:
- Apenas um disco pode ser movido por vez.
- A torre não pode ultrapassar a capacidade de 7 discos.

#### 2. **Importações e Configurações Iniciais**

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
```

- `stdio.h`: Biblioteca usada para entrada e saída de dados, permitindo funções como `printf` e `scanf`
- `stdlib.h`: Biblioteca usada para alocação de memória, conversões e geração de números aleatórios, como a função `rand` 
- `time.h`: Biblioteca usada para manipulação de tempo e data, especialmente útil para inicializar a semente do gerador de números aleatórios com `srand(time(NULL))`

#### 3. **Configuração de Variáveis**

```c
capacidade_torre = 7;
total_disco = 12;
```

- Define a capacidade da torre e o total de discos que a função `distribuir_itens_aleatorios()` vai `empilhar()` aleatoriamente os discos na torre.

#### 4. **Criação das torres**

`torre.h`
```c
typedef struct {
    char *ponto;
    int topo;
    int capacidade;
} Torres;
```

- Cria uma estrutura para armazenar as torres e seus `*ponto` discos, com uma `capacidade` estática para cada uma das torres indicando a sua posição `topo`.

`main.c`
```c
int capacidade_torre = 7;
int total_disco = 12;

Torres *torre_R = criar_torre(capacidade_torre);
Torres *torre_G = criar_torre(capacidade_torre);
Torres *torre_B = criar_torre(capacidade_torre);
```

- Cria três torres, definindo sua capacidade e o total disco que o jogador vai reposionar ao longo do jogo.

#### 5. **Distribuição do discos**
`torre.c`
```c
    void distribuir_itens_aleatorios(Torres *torreR, Torres *torreG, Torres *torreB, int total) {
    srand(time(NULL));

    char itens[] = {'R', 'G', 'B'}; 
    int num_itens = sizeof(itens) / sizeof(itens[0]); 

    for (int i = 0; i < total; i++) {
        if (torre_cheia(torreR) && torre_cheia(torreG) && torre_cheia(torreB)) {
            printf("Todas as torres estão cheias!\n");
            break;
        }

        int tipo = rand() % num_itens; 
        char item = itens[tipo];
        
        Torres *torreAleatoria = NULL;
        int torreEscolhida = rand() % 3; 

        if(torreEscolhida = 0){
            torreAleatoria = torreR;
        }else if(torreEscolhida = 1){
            torreAleatoria = torreG;
        }else if(torreEscolhida = 2){
            torreAleatoria = torreB;
        }

        if (!torre_cheia(torreAleatoria)) {
            empilhar(torreAleatoria, item);
        } else {
            i--;
        }
    }
}
```
- `srand(time(NULL));`: Inicializa o gerador de números aleatórios usando a hora atual para garantir que a sequência sempre seja aleatória.

- `int tipo = rand() % num_itens`: Gera um índice aleatório para escolher o tipo da torre.

- `int torreEscolhida = rand() % 3`: Gera um índice aleatório para escolher uma das três torres.

Funções auxiliares:
`torre.c`
- `torre_cheia()`: Verifica se a torre atingiu a capacidade máxima.
- `empilhar()`: Aloca os discos nas torres correspondentes,  passando: 
    -  A torre `torreAleatoria` --> `*torreR`, `*torreG` ou `*torreB`
    - Tipo do disco `item` --> `char itens[] = {'R', 'G', 'B'}`

`main.c`
```c
distribuir_itens_aleatorios(torre_R, torre_G, torre_B, total_disco);
```
- As torres criandas são passadas na função.

#### 6. **Inicialização do jogo**
`main.c`
- Imprime o estado inicial de distribuição das torres
`imprimir_estado(Torres *torreR, Torres *torreG, Torres *torreB)`

- Inicializa o loop principal, que termina assim que a vitória for alcançada
```c
while (1) {
    if (verificar_vitoria(torre_R, torre_G, torre_B)) {
        printf("Parabéns, você ganhou em %d jogadas.\n", jogadas);
        return 0;
    }
}
```

### 2. Detalhes adicionais

#### 1. **Cores do Disco**
`torre.c`
```c
void imprimir_torres(Torres *torre1, char cor1, Torres *torre2, char cor2, Torres *torre3, char cor3){
    const char *corR = "\033[31m"; // Vermelho para 'R'
    const char *corG = "\033[32m"; // Verde para 'G'
    const char *corB = "\033[34m"; // Azul para 'B'
    const char *reset = "\033[0m"; // Reseta a cor

    printf("\n");
    for (int i = max_linhas - 1; i >= 0; i--) {
        // Torre 1
        if (i <= torre1->topo) {
            printf("  %s%c%s       ", torre1->ponto[i] == 'R' ? corR : (torre1->ponto[i] == 'G' ? corG : corB), torre1->ponto[i], reset);
        } else {
            printf("          ");  
        }
    }
}
```
- Claro! Vamos detalhar a seção sobre as cores dos discos e a função `imprimir_torres`.

### 2. Detalhe Adicional

#### 1. **Cores do Disco**

A função `imprimir_torres` exibe o estado das torres e utiliza cores diferentes para representar os discos. Aqui está a implementação da função:

```c
void imprimir_torres(Torres *torre1, char cor1, Torres *torre2, char cor2, Torres *torre3, char cor3) {
    int max_linhas = (torre1->topo + 1 > torre2->topo + 1) ? torre1->topo + 1 : torre2->topo + 1;
    max_linhas = (max_linhas > torre3->topo + 1) ? max_linhas : torre3->topo + 1;

    const char *corR = "\033[31m"; // Vermelho para 'R'
    const char *corG = "\033[32m"; // Verde para 'G'
    const char *corB = "\033[34m"; // Azul para 'B'
    const char *reset = "\033[0m"; // Reseta a cor

    printf("\n");
    for (int i = max_linhas - 1; i >= 0; i--) {
        // Torre 1
        if (i <= torre1->topo) {
            printf("  %s%c%s       ", torre1->ponto[i] == 'R' ? corR : (torre1->ponto[i] == 'G' ? corG : corB), torre1->ponto[i], reset);
        } else {
            printf("          ");  
        }

        // Torre 2
        if (i <= torre2->topo) {
            printf("  %s%c%s       ", torre2->ponto[i] == 'R' ? corR : (torre2->ponto[i] == 'G' ? corG : corB), torre2->ponto[i], reset);
        } else {
            printf("          ");
        }

        // Torre 3
        if (i <= torre3->topo) {
            printf("  %s%c%s   ", torre3->ponto[i] == 'R' ? corR : (torre3->ponto[i] == 'G' ? corG : corB), torre3->ponto[i], reset);
        } else {
            printf("          ");
        }

        printf("\n");
    }

    printf(" T%c        T%c        T%c\n", cor1, cor2, cor3);
}
```

- **Cores**: 
    - `corR`, `corG`, `corB`: Definem as cores para os discos vermelho, verde e azul, respectivamente, usando códigos ANSI.
    - `reset`: Usado para restaurar a cor padrão do terminal após imprimir um disco.

- **Impressão das Torres**: Um loop percorre as linhas de cima para baixo. Para cada torre, se houver um disco naquela posição `topo`, ele imprime o disco na cor correspondente. Se não houver disco, imprime espaços em branco.

- **Vizualização**: A função gera uma visualização clara do estado atual das torres e dos discos, permitindo que o jogador acompanhe o progresso do jogo.

## Contato

Para qualquer dúvida ou sugestão, entre em contato pelo e-mail: [layspessoal338@gmail.com].


