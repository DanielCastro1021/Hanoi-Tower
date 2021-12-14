/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Pedro
 *
 * Created on 6 de Janeiro de 2018, 10:34
 */

//@file
/* 
 * File:   main.c
 * Author: estgf
 *
 * Created on 15 de Novembro de 2017, 9:23
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 8
#define SIZEPLAYERS 50

/*
 * 
 */
typedef struct {
    char name[30];
    int moves;
    float tempo;
} PLAYER;

typedef struct {
    int origem;
    int destino;
} Mudar;

typedef struct {
    int discos[MAX];
} Torres;

typedef struct {
    Torres torre[3];
    int tam_max_discos;
} Hanoi;


Hanoi h;
Mudar m;

/*Esta funçãp confirma se o jogo termina ou continua. 
 * @param i variavel de incrementação.
 * @param c1 variavel de incrmentação.
 * @param c2 variavel de incrmentação.
 * @param n_discos variavel de decrementação. 
 * @return 1 caso o jogo termine.
 * @return 0 caso o jogo continue.  
 */
int fim_jogo() {

    int i, c1 = 0, c2 = 0, n_discos = h.tam_max_discos;

    for (i = 0; i < h.tam_max_discos; i++) {
        if (h.torre[1].discos[i] == n_discos && n_discos > 0)c1++;
        if (h.torre[2].discos[i] == n_discos && n_discos > 0)c2++;
        n_discos--;

    }

    if (c1 == h.tam_max_discos || c2 == h.tam_max_discos) {
        return 1;
    } else
        return 0;
}

/*Esta função troca os valores entre  dois vetores de acordo com os argumentos que recebe. 
 * @param i variável de incrementação. 
 * @param n guarda o valor do disco retirado.
 * @param k guarda o valor da posição do disco retirado.
 * @param origem e o primeiro argumento recebido pela funcao,torre onde será retirado o disco.
 * @param destino e o segundo argumento recebido pela funcao, torre onde será colocado o disco.
 * @return
 */
int mover_torres(int origem, int destino) {
    int i, n, k;

    for (i = h.tam_max_discos - 1; i >= 0; i--) {


        if (h.torre[origem].discos[i] != 0) {
            n = h.torre[origem].discos[i]; //guardar valor para mover para outra torre
            h.torre[origem].discos[i] = 0; //subtituir o valor retirado por 0
            k = i; //guardar posicao caso o movimento seja impossivel
            i = 0; // terminar o ciclo 
        } else
            n = 0;
    }

    for (i = 0; i < h.tam_max_discos; i++) {
        if (n > h.torre[destino].discos[i] && h.torre[destino].discos[i] != 0) {
            printf("Movimento impossivel");
            h.torre[origem].discos[k] = n; //repor calor retirado por e um movimento impossivel

            return 0;

        } else

            if (h.torre[destino].discos[i] == 0) {
            h.torre[destino].discos[i] = n; // colocar valor retirado no local destino
            i = h.tam_max_discos; //terminar ciclo;

            return 1;
        }

    }

}

/* Esta funçao atribui valores a struct Mudar m de acordo com os @param local e @param destino.
 * @param local corresponde à torre que retira o disco.
 * @param destino corresponde à torre que coloca o disco retirado.
 * @return  
 */
void player_mover() {

    char local, destino;

    printf("\nDe:");
    scanf("%s", &local);


    printf("Para:");
    scanf("%s", &destino);


    if (local == 'A' && destino == 'B' || local == 'A' && destino == 'b' || local == 'a' && destino == 'B' || local == 'a' && destino == 'b') {
        m.origem = 0;
        m.destino = 1;
    } else
        if (local == 'A' && destino == 'C' || local == 'A' && destino == 'c' || local == 'a' && destino == 'C' || local == 'a' && destino == 'c') {
        m.origem = 0;
        m.destino = 2;
    } else
        if (local == 'B' && destino == 'A' || local == 'B' && destino == 'a' || local == 'b' && destino == 'A' || local == 'b' && destino == 'a') {
        m.origem = 1;
        m.destino = 0;
    } else
        if (local == 'B' && destino == 'C' || local == 'B' && destino == 'c' || local == 'b' && destino == 'C' || local == 'b' && destino == 'c') {
        m.origem = 1;
        m.destino = 2;
    } else
        if (local == 'C' && destino == 'A' || local == 'C' && destino == 'a' || local == 'c' && destino == 'A' || local == 'c' && destino == 'a') {
        m.origem = 2;
        m.destino = 0;
    } else
        if (local == 'C' && destino == 'B' || local == 'C' && destino == 'b' || local == 'c' && destino == 'B' || local == 'c' && destino == 'b') {
        m.origem = 2;
        m.destino = 1;
    } else {
        m.origem = -1;
        m.destino = -1;
    }


}

/*Esta função serve para imprimir mesa do jogo.
 * @param torre é o número correspondente à torre que deve ser imprimida.
 * @param i variável de incrementação.
 * @return
 */
void desenhar_mesa(int torre) {
    int i;

    for (i = 0; i < 17; i++) {
        printf("=");
    }
    printf("\n");
    for (i = 0; i < 8; i++) {
        printf(" ");
    }
    if (torre == 0)printf("A");
    else
        if (torre == 1)printf("B");
    else
        if (torre == 2)printf("C");

    for (i = 0; i < 8; i++) {
        printf(" ");
    }
    printf("\n");
}

/*Esta função serve para imprimir os discos do jogo.
 * @param i variavel de incrementação.
 * @return
 */
void desenhar_disco(int disco, int torre) {
    int i;

    if (disco == 0) {

        for (i = 0; i < MAX; i++) {
            printf(" ");
        }

        printf("|");

        for (i = 0; i < MAX; i++) {
            printf(" ");
        }
    } else {

        for (i = 0; i < MAX - disco; i++) {
            printf(" ");
        }

        for (i = 0; i < 1 + 2 * disco; i++) {
            printf("%d", disco);
        }

        for (i = 0; i < MAX - disco; i++) {
            printf(" ");
        }

    }

}

/*Esta função principal de desenho do jogo hanoi,que recorre as funções desenhar_disco e desenhar_mesa.
 * @param h.tam_max_discos corresponde ao nº de discos.
 * @param i variável de incrementação que permite percorrer as torres A,B,C.
 * @param j variável de incrementação que permite percorrer os discos que pertencem as torres; 
 * @return 
 */
void desenhar_jogo() {

    printf("\n");

    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = h.tam_max_discos - 1; j >= 0; j--) {

            desenhar_disco(h.torre[i].discos[j], i);
            printf("\n");
        }

        desenhar_mesa(i);
        printf("\n\n\n");

    }
}

/* Esta função serve para preencher os vetores dos registos com o nº de discos que o utilizador
 * escolheu de forma a inicializar o jogo.
 * @param n_discos é o primeiro argumento da função.
 * @param h.tam_max_discos e o argumento para guardar nos registos o argumento n_discos.
 * @param h.torre[0].discos[i] e o argumento que corresponde ao vetor da torre A.
 * @param h.torre[1].discos[i] e o argumento que corresponde ao vetor da torre B.
 * @param h.torre[2].discos[i] e o argumento que corresponde ao vetor da torre C.
 * @param i e o argumento de incrementação utilizado para percorrer os vetores.
 * @return
 */
void iniciar_jogo(int n_discos) {
    int i;
    h.tam_max_discos = n_discos;

    for (i = 0; i < h.tam_max_discos; i++) {
        h.torre[0].discos[i] = n_discos;
        h.torre[1].discos[i] = 0;
        h.torre[2].discos[i] = 0;
        n_discos--;
    }


}

/*Esta função é responsável por imprimir as soluções de acordo com o nº de discos.
 * @param n é o número de discos. 
 * @param beg é a torre inicial com todos os discos ordenados pelo diâmetro.
 * @param aux é a torre auxiliar, ou seja não irá ter todos discos.
 * @param end  é a torre final onde todos os discos da torre inicial iram estar e ordenados pelo diâmetro.
 * @return
 */
void soluc_jogo(int n, char beg, char aux, char end) {


    if (n == 1) {
        printf("%c --> %c\n", beg, end);
    } else {
        soluc_jogo(n - 1, beg, end, aux);
        soluc_jogo(1, beg, aux, end);
        soluc_jogo(n - 1, aux, beg, end);
    }

}

/*Esta funcao abre o ficheiro file.txt e imprime o seu conteudo.
 * @param p apontador para a estrutura PLAYER.
 * @param c é variável char que permite contar as linhas.
 * @param n_discos é o número de discos colocados nas torres.
 * @param i variável de incrementação, para percorrer os jogadores.
 * @param lines é o número de linhas que o ficheiro tem.
 * @return -1 caso exista erro ao abrir o ficheiro.
 * @return 0 caso o ficheiro abra com sucesso.
 */
int ver_recordes(PLAYER *p){
    char c;
    int n_discos, i, lines = 0;

    do {
        printf("\nNº de discos(MIN:3 MÁX:8):");
        scanf("%d", &n_discos);
    } while (n_discos < 3 || n_discos > 8);

    FILE *fp;

    if (n_discos == 3) {
        fp = fopen("file_n3.txt", "r");

    } else
        if (n_discos == 4) {
        fp = fopen("file_n4.txt", "r");
    } else
        if (n_discos == 5) {
        fp = fopen("file_n5.txt", "r");
    } else
        if (n_discos == 6) {
        fp = fopen("file_n6.txt", "r");
    } else
        if (n_discos == 7) {
        fp = fopen("file_n7.txt", "r");
    } else
        if (n_discos == 8) {
        fp = fopen("file_n8.txt", "r");
    }

    if (fp == NULL) {
        perror("Erro a abrir o ficheiro");
        return -1;
    }else{


    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            lines++;
        }
    }

    rewind(fp);

    if (lines == 0)printf("\nNão existem jogadores nos recordes.");
    else {
       
        for (i = 0; i < lines; i++) {
            fscanf(fp, " %30[^\t]", p[i].name);
            fscanf(fp, "%d[^\t]", &p[i].moves);
            fscanf(fp, "%f[^\n]", &p[i].tempo);
        }


        for (i = 0; i < lines; i++) {
            printf("\n==================================");
            printf("\nPLAYER %d", i + 1);
            printf("\nNome:%s", p[i].name);
            printf("\nMovimetos:%d", p[i].moves);
            printf("\nTempo:%.2fs", p[i].tempo);
            printf("\n==================================");
        }

        fclose(fp);

    }
    return 0;
    } 
}

/*Esta funcao guarda a estrutura PLAYER no ficheiro de acordo com o valor do @param n_discos.
 * @param p apontador para a estrutura PLAYER.
 * @param contador é o número de jogadores presentes nos recordes.
 * @param n_discos é o número de discos que permite guardar no ficheiro correcto.
 * @param name é o nome do utilizador a ser guardado no ficheiro respetivo.
 * @return 
 */
void guardar_recordes(PLAYER *p, int contador, int n_discos) {
    char name[30];
    FILE *fp;


    if (n_discos == 3) {
        fp = fopen("file_n3.txt", "a");
    } else
        if (n_discos == 4) {
        fp = fopen("file_n4.txt", "a");
    } else
        if (n_discos == 5) {
        fp = fopen("file_n5.txt", "a");
    } else
        if (n_discos == 6) {
        fp = fopen("file_n6.txt", "a");
    } else
        if (n_discos == 7) {
        fp = fopen("file_n7.txt", "a");
    } else
        if (n_discos == 8) {
        fp = fopen("file_n8.txt", "a");
    }

    printf("\nTempo:%.2f s.\n", p[contador].tempo);
    printf("\nPontuação(nº de movimentos):%d", p[contador].moves);

    printf("\nNome:");
    scanf(" %[^\n]s", p[contador].name);

    fprintf(fp, " %s", p[contador].name);
    fprintf(fp, "\t %d", p[contador].moves);
    fprintf(fp, " \t %.2f \n", p[contador].tempo);

    fclose(fp);

    return;
}

/* A função a abaixo permite imprimir as regras do jogo hanoi ao jogador.
 */
void regras() {
    printf("\n\nRegras:\n");
    printf("1. Deslocar um disco de cada vez, o qual deverá ser o do topo de uma das três torres.\n");
    printf("2. Cada disco nunca poderá ser colocado sobre outro de diâmetro mais pequeno.\n\n");

}

/*Esta função executa o jogo hanoi.
 * @param p apontador para a estrutura PLAYER.
 * @param contador é o número de jogadores presentes nos recordes.
 * @param start guarda o tempo em que jogo começou.
 * @param end guarda o tempo em que jogo terminou.
 * @param tempo é os segundos de jogo.
 *  @param n_discos é o número de discos colocados nas torres.
 * @param n é a variavel de verificação se o jogo acaba ou não.
 * @param moves é a variavel de incrementação correspondente ao nº de movimentos executados pelo utilizador.
 * @return
 */

void jogo_hanoi(PLAYER *p, int contador, int n_discos) {
    int n, t;
    time_t start, end;

    iniciar_jogo(n_discos);

    start = time(0);

    do {
        desenhar_jogo();
        do {
            player_mover();
        } while (m.origem == -1 && m.destino == -1);

        if (mover_torres(m.origem, m.destino) == 1) {
            if (fim_jogo() == 1) {
                n = 1;
                p[contador].moves++;
                desenhar_jogo();
                printf("\nFim jogo.Parabéns!!!");
            } else {
                n = 0;
                p[contador].moves++;
            }
        }
    } while (n == 0);

    end = time(0);

    p[contador].tempo = end - start;

}

/*Esta função é um menu que permite acessar varias funcinalidades,o jogo,os recordes e as soluções de jogo.
 * @param *Ap_PLAYER aponta para a struct PLAYER.
 * @param contador é o número de jogadores presentes nos recordes.
 * @param opcao corresponde a opcao escolhida pelo jogador no menu de jogo.
 * @param n_discos é o número de discos colocados nas torres.
 * @return 0
 */
int main() {
    int opcao, n_discos, contador = 0;

    PLAYER *Ap_PLAYER;

    Ap_PLAYER = (PLAYER*) malloc(SIZEPLAYERS * sizeof (PLAYER));

    do {
        do {
            printf("==================================\n");
            printf("Menu:\n");
            printf("1.Jogar.\n");
            printf("2.Recordes.\n");
            printf("3.Soluções de jogo.\n");
            printf("0.Sair\n");
            printf("==================================");
            printf("\nOpção:");
            scanf("%d", &opcao);
            printf("==================================");

        } while (opcao > 3 || opcao < 0);


        switch (opcao) {
            case 1:

                regras();

                do {

                    printf("Nº de discos(MIN:3 MÁX:8):");
                    scanf("%d", &n_discos);

                } while (n_discos > 8 || n_discos < 3);

                jogo_hanoi(Ap_PLAYER, contador, n_discos);

                guardar_recordes(Ap_PLAYER, contador, n_discos);

                contador++;

                break;

            case 2:

                ver_recordes(Ap_PLAYER);

                break;

            case 3:

                do {
                    printf("Nº de discos(MIN:3 MÁX:8):");
                    scanf("%d", &n_discos);
                } while (n_discos > 8 || n_discos < 3);

                
                printf("\nSoluções:\n\n");
                soluc_jogo(n_discos, 'A', 'B', 'C');

                break;
        }

        printf("\n\n");
   
    } while (opcao != 0);

    printf("EXIT SUCCESSFUL.");

    return 0;
}

