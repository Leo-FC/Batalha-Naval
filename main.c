// Alunos: Leonardo Ferreira da Cunha e Lucas de Jesus Santos Moura

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 10
#define MAPA_JOGADOR1 "jogador1.txt"
#define MAPA_JOGADOR2 "jogador2.txt"
#define mar '.'

void mostrar_tabuleiro(int T, char map_j1[T][T]);

void mostrar_tentativas(int T, char map_j2[T][T]);

int verificar_sobreposicoes(int navio5[5][2], int navio4[4][2], int navio3_1[3][2], int navio3_2[3][2], int navio2[2][2]);

int human_X_human();

int humano_x_maquina();

int mostrar_menu();

int main() {
    int jogo;

    do{
        jogo = mostrar_menu();

        if(jogo == 1) {
            printf("Escolhido: Humano x Humano\n");
            human_X_human();
        } else if(jogo == 2) {
            printf("Escolhido: Humano x Maquina\n");
            humano_x_maquina();
        } else {
            printf("Jogo finalizado\n");
            return 0;
        }
    }while(jogo != 3);

    return 0;
}

int mostrar_menu() {
    int escolha = 0;

    do{
        printf("\n    __|__ |___| |\\");
        printf("\n    |o__| |___| | \\");
        printf("\n    |___| |___| |o \\");
        printf("\n   _|___| |___| |__o\\");
        printf("\n  /...\\_____|___|____\\_/");
        printf("\n  \\   o * o * * o o  /");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\n[1] - Humano x Humano\n");
        printf("\n[2] - Humano x Maquina\n");
        printf("\n[3] - Sair do jogo\n");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        if(escolha == -1) {
            printf(">Digite uma opcao valida\n");
        }

        scanf("%d", &escolha);
        fflush(stdin);

        switch(escolha) {
            case 1:
                system("cls");
                return 1;
                break;

            case 2:
                system("cls");
                return 2;
                break;

            case 3:
                system("cls");
                return 3;
                break;

            default:
                escolha = -1;
                system("cls");
        }
    }while(escolha != 1 || escolha != 2 || escolha != 3);
}

int human_X_human() {
    char mapa_j1[TAM][TAM];
    char mapa_j2[TAM][TAM];
    char tentativa_j1[TAM][TAM];
    char tentativa_j2[TAM][TAM];
    int i, j, erro, pontuacaoj1, pontuacaoj2;

    erro = 0;
    pontuacaoj1 = 0;
    pontuacaoj2 = 0;

    while(erro == 0) {
        //DEFININDO OS MAPAS
        for(i=0; i< TAM; i++){
            for(j=0; j < TAM; j++){
                mapa_j1[i][j] = mar;
                mapa_j2[i][j] = mar;
                tentativa_j1[i][j] = mar;
                tentativa_j2[i][j] = mar;
            }
        }

        //CONFIGURANDO O JOGADOR 1
        FILE *jogador1;
        jogador1 = fopen(MAPA_JOGADOR1, "r");
        /*
            EXEMPLO
            NAV[PRIMEIRA/SEGUNDA/N CELULA][0=LINHA 1=COLUNA]
        */
        // PREENCHENDO AS POSICOES DOS NAVIOS / LINHA E COLUNA
        // NAVIO DE 5 CELULAS
        int j1_nav5[5][2];
        for(i=0; i < 5; i++) {
            fscanf(jogador1, "%d %d",&j1_nav5[i][0], &j1_nav5[i][1]);
        }

        // NAVIO DE 4 CELULAS
        int j1_nav4[4][2];
        for(i=0; i < 4; i++) {
            fscanf(jogador1, "%d %d", &j1_nav4[i][0], &j1_nav4[i][1]);
        }

        // NAVIO DE 3 CELULAS 1
        int j1_nav3_um[3][2];
        for(i=0; i < 3; i++) {
            fscanf(jogador1, "%d %d", &j1_nav3_um[i][0], &j1_nav3_um[i][1]);
        }

        // NAVIO DE 3 CELULAS 2
        int j1_nav3_dois[3][2];
        for(i=0; i < 3; i++) {
            fscanf(jogador1, "%d %d", &j1_nav3_dois[i][0], &j1_nav3_dois[i][1]);
        }

        // NAVIO DE 2 CELULAS
        int j1_nav2[2][2];
        for(i=0; i < 2; i++) {
            fscanf(jogador1, "%d %d", &j1_nav2[i][0], &j1_nav2[i][1]);
        }

        fclose(jogador1);

        erro = verificar_sobreposicoes(j1_nav5,j1_nav4,j1_nav3_um,j1_nav3_dois,j1_nav2);

        if(erro == 1) {
            printf("\nErro: Ha uma sobreposicao nos navios\nVerifique o arquivo de texto e reposicione os navios\n");
            printf("\nSobreposicao nos navios do JOGADOR 01\n");
            break;
        }
        // PREENCHENDO AS CELULAS DO NAVIO DE 5
        for (i=0; i < 5; i ++) {
            mapa_j1[j1_nav5[i][0]][j1_nav5[i][1]] = 'A';
        }

        // PREENCHENDO AS CELULAS DO NAVIO DE 4
        for (i=0; i < 4; i ++) {
            mapa_j1[j1_nav4[i][0]][j1_nav4[i][1]] = 'B';
        }

        // PREENCHENDO AS CELULAS DOS DOIS NAVIOS DE 3
        for (i=0; i < 3; i ++) {
            mapa_j1[j1_nav3_um[i][0]][j1_nav3_um[i][1]] = 'C';
            mapa_j1[j1_nav3_dois[i][0]][j1_nav3_dois[i][1]] = 'D';
        }

        // PREENCHENDO AS CELULAS DO NAVIO DE 2
        for (i=0; i < 2; i++) {
          mapa_j1[j1_nav2[i][0]][j1_nav2[i][1]] = 'E';
        }

    /////////////////////////////////////////////////////////////////////

        //CONFIGURANDO O JOGADOR 2
        FILE *jogador2;
        jogador2 = fopen(MAPA_JOGADOR2, "r");
        /*
            EXEMPLO
            NAV[PRIMEIRA/SEGUNDA/N CELULA][0=LINHA 1=COLUNA]
        */
        // NAVIO DE 5 CELULAS
        int j2_nav5[5][2];
            for(i=0; i < 5; i++) {
            fscanf(jogador2, "%d %d",&j2_nav5[i][0], &j2_nav5[i][1]);
        }

        // NAVIO DE 4 CELULAS
        int j2_nav4[4][2];
        for(i=0; i < 4; i++) {
            fscanf(jogador2, "%d %d",&j2_nav4[i][0], &j2_nav4[i][1]);
        }

        // NAVIO DE 3 CELULAS 1
        int j2_nav3_um[3][2];
        for(i=0; i < 3; i++) {
            fscanf(jogador2, "%d %d",&j2_nav3_um[i][0], &j2_nav3_um[i][1]);
        }

        // NAVIO DE 3 CELULAS 2
        int j2_nav3_dois[3][2];
        for(i=0; i < 3; i++) {
            fscanf(jogador2, "%d %d",&j2_nav3_dois[i][0], &j2_nav3_dois[i][1]);
        }

        // NAVIO DE 2 CELULAS
        int j2_nav2[2][2];
        for(i=0; i < 2; i++) {
            fscanf(jogador2, "%d %d",&j2_nav2[i][0], &j2_nav2[i][1]);
        }

        fclose(jogador2);

        erro = verificar_sobreposicoes(j2_nav5, j2_nav4, j2_nav3_um, j2_nav3_dois, j2_nav2);

        if(erro == 1) {
            printf("\nErro: Ha uma sobreposicao nos navios\nVerifique o arquivo de texto e reposicione os navios\n");
            printf("\nSobreposicao nos navios do JOGADOR 02\n");
            break;
        }

        // PREENCHENDO AS CELULAS DO NAVIO DE 5
        for (i=0; i < 5; i ++) {
            mapa_j2[j2_nav5[i][0]][j2_nav5[i][1]] = 'A';
        }

        // PREENCHENDO AS CELULAS DO NAVIO DE 4
        for (i=0; i < 4; i ++) {
            mapa_j2[j2_nav4[i][0]][j2_nav4[i][1]] = 'B';
        }

        // PREENCHENDO AS CELULAS DOS DOIS NAVIOS DE 3
        for (i=0; i < 3; i ++) {
            mapa_j2[j2_nav3_um[i][0]][j2_nav3_um[i][1]] = 'C';
            mapa_j2[j2_nav3_dois[i][0]][j2_nav3_dois[i][1]] = 'D';
        }

        // PREENCHENDO AS CELULAS DO NAVIO DE 2
        for (i=0; i < 2; i++) {
          mapa_j2[j2_nav2[i][0]][j2_nav2[i][1]] = 'E';
        }


    /////////////////////////////////////////////////////////////////////

        // HORA DOS JOGADORES ATACAREM
        int linha_atq, coluna_atq, fim;

        fim = 0;

        while(fim == 0){
            //JOGADOR 1 ATACANDO
            do{
                if(fim == 1) {
                    break;
                }

                printf("TENTATIVAS DO JOGADOR 01\n");
                mostrar_tentativas(TAM, tentativa_j1);
                printf("\nQUEM ESTA ATACANDO: Jogador 01\n");

                do {
                    printf("\nDigite a LINHA do seu ataque: ");
                    scanf("%d", &linha_atq);

                    if(linha_atq < 0 || linha_atq > 9) {
                        printf("\nPosicao invalida\nDigite numeros no intervalo de 0 a 9\n");
                    }
                }while(linha_atq < 0 || linha_atq > 9);

                do {
                    printf("\nDigite a COLUNA do seu ataque: ");
                    scanf("%d", &coluna_atq);

                    if(coluna_atq < 0 || coluna_atq > 9) {
                        printf("\nPosicao invalida\nDigite numeros no intervalo de 0 a 9\n");
                    }
                }while(coluna_atq < 0 || coluna_atq > 9);

                if (mapa_j2[linha_atq][coluna_atq] == 'X' || tentativa_j1[linha_atq][coluna_atq] == 'T') {
                    system("cls");
                    printf("\nEsse alvo ja foi selecionado, tente novamente JOGADOR 01\n");
                    continue;
                }

                if (mapa_j2[linha_atq][coluna_atq] == mar) {
                    system("cls");
                    tentativa_j1[linha_atq][coluna_atq] = 'T';
                    printf("\nERROU! Agora quem ira jogar sera o JOGADOR 02\n");
                    break;
                } else {
                    system("cls");
                    printf("\nVOCE ACERTOU O ALVO! JOGADOR 01, CONTINUE A JOGAR \n");
                    mapa_j2[linha_atq][coluna_atq] = 'X';
                    tentativa_j1[linha_atq][coluna_atq] = 'X';
                    pontuacaoj1 ++;

                    if (pontuacaoj1 == 17) {
                        fim = 1;
                    }
                }
            }while (tentativa_j1[linha_atq][coluna_atq] != mar);

            // JOGADOR 2 ATACANDO
            do{
                if(fim == 1) {
                    break;
                }

                printf("TENTATIVAS DO JOGADOR 02\n");
                mostrar_tentativas(TAM, tentativa_j2);
                printf("\nQUEM ESTA ATACANDO: Jogador 02\n");

                do {
                    printf("\nDigite a LINHA do seu ataque: ");
                    scanf("%d", &linha_atq);

                    if(linha_atq < 0 || linha_atq > 9) {
                        printf("\nPosicao invalida\nDigite numeros no intervalo de 0 a 9\n");
                    }
                }while(linha_atq < 0 || linha_atq > 9);

                do {
                    printf("\nDigite a COLUNA do seu ataque: ");
                    scanf("%d", &coluna_atq);

                    if(coluna_atq < 0 || coluna_atq > 9) {
                        printf("\nPosicao invalida\nDigite numeros no intervalo de 0 a 9\n");
                    }
                }while(coluna_atq < 0 || coluna_atq > 9);

                if (mapa_j1[linha_atq][coluna_atq] == 'X' || tentativa_j2[linha_atq][coluna_atq] == 'T') {
                    system("cls");
                    printf("\nEsse alvo ja foi selecionado, tente novamente JOGADOR 02\n");
                    continue;
                }

                if (mapa_j1[linha_atq][coluna_atq] == mar) {
                    system("cls");
                    printf("\nERROU! Agora quem ira jogar sera o JOGADOR 01\n");
                    tentativa_j2[linha_atq][coluna_atq] = 'T';

                    break;
                } else {
                    system("cls");
                    printf("\nVOCE ACERTOU O ALVO! JOGADOR 02, CONTINUE A JOGAR \n");
                    mapa_j1[linha_atq][coluna_atq] = 'X';
                    tentativa_j2[linha_atq][coluna_atq] = 'X';
                    pontuacaoj2 ++;

                    if (pontuacaoj2 == 17) {
                        fim = 1;
                    }
                }
            }while (tentativa_j2[linha_atq][coluna_atq] != mar);

        }

        printf("MAPA DO JOGADOR 01\n");
        mostrar_tabuleiro(TAM, mapa_j1);

        printf("MAPA DO JOGADOR 02\n");
        mostrar_tabuleiro(TAM, mapa_j2);

        if(pontuacaoj1 > pontuacaoj2) {
            printf("Fim de Jogo!\nJogador 1 venceu!");
        } else {
            printf("Fim de Jogo!\nJogador 2 venceu!");
        }

        printf("\nPontuacao do JOGADOR 01: %d\n", pontuacaoj1);
        printf("\nPontuacao do JOGADOR 02: %d\n", pontuacaoj2);

        system("pause");

        system("cls");

        break;
    }

    return 0;
}

int humano_x_maquina(){
    char mapa_j1[TAM][TAM];
    char tentativa_j1[TAM][TAM];
    char tentativa_maquina[TAM][TAM];
    int i, j, erro, pontuacaoj1, pontuacao_maquina;

    erro = 0;
    pontuacaoj1 = 0;
    pontuacao_maquina = 0;
    while(erro == 0) {
        //DEFININDO OS MAPAS
        for(i=0; i< TAM; i++){
            for(j=0; j < TAM; j++){
                mapa_j1[i][j] = mar;
                tentativa_j1[i][j] = mar;
                tentativa_maquina[i][j] = mar;
            }
        }

        //CONFIGURANDO O HUMANO
        FILE *jogador1;
        jogador1 = fopen(MAPA_JOGADOR1, "r");
        /*
            EXEMPLO
            NAV[PRIMEIRA/SEGUNDA/N CELULA][0=LINHA 1=COLUNA]
        */
        // PREENCHENDO AS POSICOES DOS NAVIOS / LINHA E COLUNA
        // NAVIO DE 5 CELULAS
        int j1_nav5[5][2];
        for(i=0; i < 5; i++) {
            fscanf(jogador1, "%d %d",&j1_nav5[i][0], &j1_nav5[i][1]);
        }

        // NAVIO DE 4 CELULAS
        int j1_nav4[4][2];
        for(i=0; i < 4; i++) {
            fscanf(jogador1, "%d %d", &j1_nav4[i][0], &j1_nav4[i][1]);
        }

        // NAVIO DE 3 CELULAS 1
        int j1_nav3_um[3][2];
        for(i=0; i < 3; i++) {
            fscanf(jogador1, "%d %d", &j1_nav3_um[i][0], &j1_nav3_um[i][1]);
        }

        // NAVIO DE 3 CELULAS 2
        int j1_nav3_dois[3][2];
        for(i=0; i < 3; i++) {
            fscanf(jogador1, "%d %d", &j1_nav3_dois[i][0], &j1_nav3_dois[i][1]);
        }

        // NAVIO DE 2 CELULAS
        int j1_nav2[2][2];
        for(i=0; i < 2; i++) {
            fscanf(jogador1, "%d %d", &j1_nav2[i][0], &j1_nav2[i][1]);
        }

        fclose(jogador1);

        erro = verificar_sobreposicoes(j1_nav5,j1_nav4,j1_nav3_um,j1_nav3_dois,j1_nav2);

        if(erro == 1) {
            printf("\nErro: Ha uma sobreposicao nos navios\nVerifique o arquivo de texto e reposicione os navios\n");
            printf("\nSobreposicao nos navios do JOGADOR 01\n");
            break;
        }
        // PREENCHENDO AS CELULAS DO NAVIO DE 5
        for (i=0; i < 5; i ++) {
            mapa_j1[j1_nav5[i][0]][j1_nav5[i][1]] = 'A';
        }

        // PREENCHENDO AS CELULAS DO NAVIO DE 4
        for (i=0; i < 4; i ++) {
            mapa_j1[j1_nav4[i][0]][j1_nav4[i][1]] = 'B';
        }

        // PREENCHENDO AS CELULAS DOS DOIS NAVIOS DE 3
        for (i=0; i < 3; i ++) {
            mapa_j1[j1_nav3_um[i][0]][j1_nav3_um[i][1]] = 'C';
            mapa_j1[j1_nav3_dois[i][0]][j1_nav3_dois[i][1]] = 'D';
        }

        // PREENCHENDO AS CELULAS DO NAVIO DE 2
        for (i=0; i < 2; i++) {
          mapa_j1[j1_nav2[i][0]][j1_nav2[i][1]] = 'E';
        }

        int i, j, l, c, problema, direcao, linha, coluna;
        int m_nav5[5][2];
        int m_nav4[4][2];
        int m_nav3_1[3][2];
        int m_nav3_2[3][2];
        int m_nav2[2][2];
        char mapa_maquina[TAM][TAM];

        srand(time(NULL));

        // NAVIO DE 5 CELULAS DA MAQUINA
        do{
            for(i=0; i < TAM; i++){
                for(j=0; j < TAM; j++){
                    mapa_maquina[i][j] = mar;
                }
            }

            problema = 0;

            // Gerando aleatoriamente a primeira linha do Navio de 5 da maquina.
            m_nav5[0][0] = rand() % 10;


            // Gerando aleatoriamente a primeira coluna do Navio de 5 da maquina.
            m_nav5[0][1] = rand() % 10;

            // Gerando aleatoriamente a direcao do Navio.
            direcao = rand() % 4;


            linha = m_nav5[0][0];
            coluna = m_nav5[0][1];


            // Se a direcao for o numero 0, o navio ira para a esquerda partindo da linha e coluna inicial..
            if(direcao == 0){

                // Definindo as posicoes de linha e coluna dentro da matriz do Navio
                for(i=1; i < 5; i++){
                    m_nav5[i][0] = linha;
                    m_nav5[i][1] = coluna - i;
                }

                // Caso o Navio se movimente para fora do tabuleiro, o laço é encerrado,as posicoes iniciais
                // do navio sera gerada novamente e a variavel PROBLEMA recebera o numero 1, indicando que
                // houve um erro durante o posicionamento do navio

                // (O Navio sai do tabuleiro quando a linha ou a coluna é igual ou maior que 10, ou menor que 0.)
                for(i=0; i < 5; i++){
                    if(m_nav5[i][1] < 0){
                        problema = 1;
                        break;
                    }
                }

                // Caso nao haja nenhum problema no bloco de codigo acima, a matriz mapa da maquina recebera as posicoes
                // da matriz do navio de 5 e sera marcada com um K, que representa o Navio de 5.
                if (problema == 0){
                    mapa_maquina[linha][coluna] = 'K';

                    for(i=1; i < 5; i++){
                        mapa_maquina[m_nav5[i][0]][m_nav5[i][1]] = 'K';
                    }

                }
            }

            // Se a direcao for o numero 1, o navio ira para cima partindo da linha e coluna inicial..
            if(direcao == 1){


                for(i = 1; i < 5; i++){
                    m_nav5[i][0] = linha - i;
                    m_nav5[i][1] = coluna;
                }

                for(i=0; i < 5; i++){
                    if(m_nav5[i][0] < 0){
                        problema = 1;
                    }
                }

                if (problema == 0){
                    mapa_maquina[linha][coluna] = 'K';

                    for(i=1; i < 5; i++){
                        mapa_maquina[m_nav5[i][0]][m_nav5[i][1]] = 'K';
                    }
                }
            }
            // Se a direcao for o numero 2, o navio ira para direita partindo da linha e coluna inicial.
            if(direcao == 2){

                for (i = 1; i < 5; i++){
                    m_nav5[i][0] = linha;
                    m_nav5[i][1] = coluna + i;
                }

                for(i=0; i < 5; i++){
                    if(m_nav5[i][1] > 9){
                        problema = 1;
                        break;
                    }
                }

                if (problema == 0){
                    mapa_maquina[linha][coluna] = 'K';
                    for(i=1; i<5; i++){
                        mapa_maquina[m_nav5[i][0]][m_nav5[i][1]] = 'K';
                    }
                }
            }

            // Se a direcao for o numero 3, o navio ira para baixo partindo da linha e coluna inicial.
            if(direcao == 3){

                for(i = 1; i < 5; i++){
                    m_nav5[i][0] = linha + i;
                    m_nav5[i][1] = coluna;
                }
                for(i=0; i < 5; i++){
                    if(m_nav5[i][0] > 9){
                        problema = 1;
                        break;

                    }
                }
                if (problema == 0){
                    mapa_maquina[linha][coluna] = 'K';
                    for(i=1; i<5; i++){
                        mapa_maquina[m_nav5[i][0]][m_nav5[i][1]] = 'K';
                    }
                }
            }


        }while(problema != 0);


        // NAVIO DE 4 CELULAS DA MAQUINA
        do{
            problema = 0;
            // O Bloco abaixo só tera algum tipo de impacto relevante no código caso haja algum problema na primeira
            // iteração, será responsavel por apagar os 'Z'.
            for(i=0; i < TAM; i++){
                for(j=0; j < TAM; j++){
                    if(mapa_maquina[i][j] == 'Z'){
                        mapa_maquina[i][j] = mar;
                    }
                }
            }

            //linha inicial
            m_nav4[0][0] = rand() % 10;


            //coluna inicial
            m_nav4[0][1] = rand() % 10;


            direcao = rand() % 4;


            linha = m_nav4[0][0];
            coluna = m_nav4[0][1];


            if(direcao == 0){

                for(i=1; i < 4; i++){
                    m_nav4[i][0] = linha;
                    m_nav4[i][1] = coluna - i;
                }

                for(i=0; i < 4; i++){
                    if(m_nav4[i][1] < 0){
                        problema = 1;
                        break;
                    }
                }

                if (problema == 0){
                    mapa_maquina[linha][coluna] = 'Z';

                    for(i=1; i < 4; i++){
                        mapa_maquina[m_nav4[i][0]][m_nav4[i][1]] = 'Z';
                    }

                }
            }

            if(direcao == 1){

                for(i = 1; i < 4; i++){
                    m_nav4[i][0] = linha - i;
                    m_nav4[i][1] = coluna;
                }

                for(i=0; i < 4; i++){
                    if(m_nav4[i][0] < 0){
                        problema = 1;
                    }
                }

                if (problema == 0){
                    mapa_maquina[linha][coluna] = 'Z';

                    for(i=1; i < 4; i++){
                        mapa_maquina[m_nav4[i][0]][m_nav4[i][1]] = 'Z';
                    }
                }
            }

            if(direcao == 2){

                for (i = 1; i < 4; i++){
                    m_nav4[i][0] = linha;
                    m_nav4[i][1] = coluna + i;
                }

                for(i=0; i < 4; i++){
                    if(m_nav4[i][1] > 9){
                        problema = 1;
                        break;
                    }
                }

                if (problema == 0){
                    mapa_maquina[linha][coluna] = 'Z';
                    for(i=1; i<4; i++){
                        mapa_maquina[m_nav4[i][0]][m_nav4[i][1]] = 'Z';
                    }
                }
            }

            if(direcao == 3){

                for(i = 1; i < 4; i++){
                    m_nav4[i][0] = linha + i;
                    m_nav4[i][1] = coluna;
                }
                for(i=0; i < 4; i++){
                    if(m_nav4[i][0] > 9){
                        problema = 1;
                        break;

                    }
                }
                if (problema == 0){
                    mapa_maquina[linha][coluna] = 'Z';
                    for(i=1; i<4; i++){
                        mapa_maquina[m_nav4[i][0]][m_nav4[i][1]] = 'Z';
                    }
                }
            }

            // Verificando se ha algum tipo de sobreposicao entre o navio de 4 celulas definido agora
            // E o navio de 5 celulas definido anteriormente, caso haja alguma sobreposicao, o navio
            // de 4 celulas será apagado e gerado novamente até que nao haja qualquer tipo de sobreposicao com o N5
            for (i=0 ; i < 5; i++)
                {
                    for (j=0 ; j < 4; j++)
                    {
                        //Verificando se as linhas de n5 sao iguais a de n4 e se as colunas de n5 sao iguais a de n4
                        //Caso forem iguais, houve sobreposicao, logo a variavel problema sera ativada
                        if(m_nav5[i][0] == m_nav4[j][0] && m_nav5[i][1] == m_nav4[j][1]){

                            // Como houve sobreposicao, a letra 'Z' ( Que representa o N4 ) Ficou por cima do
                            // 'K' definido anteriormente, o que está sendo feito abaixo é devolver o 'K'
                            // A sua posicao original

                            l = m_nav5[i][0];
                            c = m_nav5[i][1];
                            mapa_maquina[l][c] = 'K';

                            problema = 1;
                            break;
                        }
                    }
                }



        }while(problema != 0);

        // NAVIO 1 DE 3 CELULAS DA MAQUINA
        do{

            problema = 0;

            for(i=0; i < TAM; i++){
                for(j=0; j < TAM; j++){
                    if(mapa_maquina[i][j] == 'P'){
                        mapa_maquina[i][j] = mar;
                    }
                }
            }

            //linha inicial
            m_nav3_1[0][0] = rand() % 10;


            //coluna inicial
            m_nav3_1[0][1] = rand() % 10;


            direcao = rand() % 4;


            linha = m_nav3_1[0][0];
            coluna = m_nav3_1[0][1];


            if(direcao == 0){

                for(i=1; i < 3; i++){
                    m_nav3_1[i][0] = linha;
                    m_nav3_1[i][1] = coluna - i;
                }

                for(i=0; i < 3; i++){
                    if(m_nav3_1[i][1] < 0){
                        problema = 1;
                        break;
                    }
                }

                if (problema == 0){
                    mapa_maquina[linha][coluna] = 'P';

                    for(i=1; i < 3; i++){
                        mapa_maquina[m_nav3_1[i][0]][m_nav3_1[i][1]] = 'P';
                    }

                }
                }

                if(direcao == 1){

                    for(i = 1; i < 3; i++){
                        m_nav3_1[i][0] = linha - i;
                        m_nav3_1[i][1] = coluna;
                    }

                    for(i=0; i < 3; i++){
                        if(m_nav3_1[i][0] < 0){
                            problema = 1;
                        }
                    }

                    if (problema == 0){
                        mapa_maquina[linha][coluna] = 'P';

                        for(i=1; i < 3; i++){
                            mapa_maquina[m_nav3_1[i][0]][m_nav3_1[i][1]] = 'P';
                        }
                    }
                }

                if(direcao == 2){

                    for (i = 1; i < 3; i++){
                        m_nav3_1[i][0] = linha;
                        m_nav3_1[i][1] = coluna + i;
                    }

                    for(i=0; i < 3; i++){
                        if(m_nav3_1[i][1] > 9){
                            problema = 1;
                            break;
                        }
                    }

                    if (problema == 0){
                        mapa_maquina[linha][coluna] = 'P';
                        for(i=1; i<3; i++){
                            mapa_maquina[m_nav3_1[i][0]][m_nav3_1[i][1]] = 'P';
                        }
                    }
                }

                if(direcao == 3){

                    for(i = 1; i < 3; i++){
                        m_nav3_1[i][0] = linha + i;
                        m_nav3_1[i][1] = coluna;
                    }
                    for(i=0; i < 3; i++){
                        if(m_nav3_1[i][0] > 9){
                            problema = 1;
                            break;

                        }
                    }
                    if (problema == 0){
                        mapa_maquina[linha][coluna] = 'P';
                        for(i=1; i<3; i++){
                            mapa_maquina[m_nav3_1[i][0]][m_nav3_1[i][1]] = 'P';
                        }
                    }
                }

                for (i=0 ; i < 5; i++)
                    {
                        for (j=0 ; j < 3; j++)
                        {
                            // VERIFICANDO SE HA CONFLITO COM O N4
                            if(m_nav5[i][0] == m_nav3_1[j][0] && m_nav5[i][1] == m_nav3_1[j][1]){

                                l = m_nav5[i][0];
                                c = m_nav5[i][1];
                                mapa_maquina[l][c] = 'K';

                                problema = 1;
                                break;
                            }
                        }
                    }

                for (i=0 ; i < 4; i++)
                    {
                        for (j=0 ; j < 3; j++)
                        {
                            // VERIFICANDO SE HA CONFLITO COM O N4
                            if(m_nav4[i][0] == m_nav3_1[j][0] && m_nav4[i][1] == m_nav3_1[j][1]){

                                l = m_nav4[i][0];
                                c = m_nav4[i][1];
                                mapa_maquina[l][c] = 'Z';

                                problema = 1;
                                break;
                            }
                        }
                    }

            }while(problema != 0);

        // NAVIO 2 DE 3 CELULAS DA MAQUINA
        do{
            problema = 0;

            for(i=0; i < TAM; i++){
                for(j=0; j < TAM; j++){
                    if(mapa_maquina[i][j] == 'Q'){
                        mapa_maquina[i][j] = mar;
                    }
                }
            }

                //linha inicial
            m_nav3_2[0][0] = rand() % 10;


                //coluna inicial
            m_nav3_2[0][1] = rand() % 10;


            direcao = rand() % 4;


            linha = m_nav3_2[0][0];
            coluna = m_nav3_2[0][1];


            if(direcao == 0){

                for(i=1; i < 3; i++){
                    m_nav3_2[i][0] = linha;
                    m_nav3_2[i][1] = coluna - i;
                }

                for(i=0; i < 3; i++){
                    if(m_nav3_2[i][1] < 0){
                        problema = 1;
                        break;
                    }
                }

                if (problema == 0){
                    mapa_maquina[linha][coluna] = 'Q';

                    for(i=1; i < 3; i++){
                        mapa_maquina[m_nav3_2[i][0]][m_nav3_2[i][1]] = 'Q';
                    }

                }
                }

                if(direcao == 1){

                    for(i = 1; i < 3; i++){
                        m_nav3_2[i][0] = linha - i;
                        m_nav3_2[i][1] = coluna;
                    }

                    for(i=0; i < 3; i++){
                        if(m_nav3_2[i][0] < 0){
                            problema = 1;
                        }
                    }

                    if (problema == 0){
                        mapa_maquina[linha][coluna] = 'Q';

                        for(i=1; i < 3; i++){
                            mapa_maquina[m_nav3_2[i][0]][m_nav3_2[i][1]] = 'Q';
                        }
                    }
                }

                if(direcao == 2){

                    for (i = 1; i < 3; i++){
                        m_nav3_2[i][0] = linha;
                        m_nav3_2[i][1] = coluna + i;
                    }

                    for(i=0; i < 3; i++){
                        if(m_nav3_2[i][1] > 9){
                            problema = 1;
                            break;
                        }
                    }

                    if (problema == 0){
                        mapa_maquina[linha][coluna] = 'Q';
                        for(i=1; i<3; i++){
                            mapa_maquina[m_nav3_2[i][0]][m_nav3_2[i][1]] = 'Q';
                        }
                    }
                }

                if(direcao == 3){

                    for(i = 1; i < 3; i++){
                        m_nav3_2[i][0] = linha + i;
                        m_nav3_2[i][1] = coluna;
                    }
                    for(i=0; i < 3; i++){
                        if(m_nav3_2[i][0] > 9){
                            problema = 1;
                            break;

                        }
                    }
                    if (problema == 0){
                        mapa_maquina[linha][coluna] = 'Q';
                        for(i=1; i<3; i++){
                            mapa_maquina[m_nav3_2[i][0]][m_nav3_2[i][1]] = 'Q';
                        }
                    }
                }

                for (i=0 ; i < 5; i++)
                    {
                        for (j=0 ; j < 3; j++)
                        {
                            if(m_nav5[i][0] == m_nav3_2[j][0] && m_nav5[i][1] == m_nav3_2[j][1]){

                                l = m_nav5[i][0];
                                c = m_nav5[i][1];
                                mapa_maquina[l][c] = 'K';

                                problema = 1;
                                break;
                            }
                        }
                    }

                for (i=0 ; i < 4; i++)
                    {
                        for (j=0 ; j < 3; j++)
                        {

                            if(m_nav4[i][0] == m_nav3_2[j][0] && m_nav4[i][1] == m_nav3_2[j][1]){

                                l = m_nav4[i][0];
                                c = m_nav4[i][1];
                                mapa_maquina[l][c] = 'Z';

                                problema = 1;
                                break;
                            }
                        }
                    }

                for (i=0 ; i < 3; i++)
                    {
                        for (j=0 ; j < 3; j++)
                        {

                            if(m_nav3_1[i][0] == m_nav3_2[j][0] && m_nav3_1[i][1] == m_nav3_2[j][1]){

                                l = m_nav3_1[i][0];
                                c = m_nav3_1[i][1];
                                mapa_maquina[l][c] = 'P';

                                problema = 1;
                                break;
                            }
                        }
                    }

            }while(problema != 0);

        // NAVIO DE 2 CELULAS DA MAQUINA
        do{
            problema = 0;

            for(i=0; i < TAM; i++){
                for(j=0; j < TAM; j++){
                    if(mapa_maquina[i][j] == 'V'){
                        mapa_maquina[i][j] = mar;
                    }
                }
            }

                //linha inicial
            m_nav2[0][0] = rand() % 10;


                //coluna inicial
            m_nav2[0][1] = rand() % 10;


            direcao = rand() % 4;


            linha = m_nav2[0][0];
            coluna = m_nav2[0][1];


            if(direcao == 0){

                for(i=1; i < 2; i++){
                    m_nav2[i][0] = linha;
                    m_nav2[i][1] = coluna - i;
                }

                for(i=0; i < 2; i++){
                    if(m_nav2[i][1] < 0){
                        problema = 1;
                        break;
                    }
                }

                if (problema == 0){
                    mapa_maquina[linha][coluna] = 'V';

                    for(i=1; i < 2; i++){
                        mapa_maquina[m_nav2[i][0]][m_nav2[i][1]] = 'V';
                    }

                }
                }

                if(direcao == 1){

                    for(i = 1; i < 2; i++){
                        m_nav2[i][0] = linha - i;
                        m_nav2[i][1] = coluna;
                    }

                    for(i=0; i < 2; i++){
                        if(m_nav2[i][0] < 0){
                            problema = 1;
                        }
                    }

                    if (problema == 0){
                        mapa_maquina[linha][coluna] = 'V';

                        for(i=1; i < 2; i++){
                            mapa_maquina[m_nav2[i][0]][m_nav2[i][1]] = 'V';
                        }
                    }
                }

                if(direcao == 2){

                    for (i = 1; i < 2; i++){
                        m_nav2[i][0] = linha;
                        m_nav2[i][1] = coluna + i;
                    }

                    for(i=0; i < 2; i++){
                        if(m_nav2[i][1] > 9){
                            problema = 1;
                            break;
                        }
                    }

                    if (problema == 0){
                        mapa_maquina[linha][coluna] = 'V';
                        for(i=1; i<2; i++){
                            mapa_maquina[m_nav2[i][0]][m_nav2[i][1]] = 'V';
                        }
                    }
                }

                if(direcao == 3){

                    for(i = 1; i < 2; i++){
                        m_nav2[i][0] = linha + i;
                        m_nav2[i][1] = coluna;
                    }
                    for(i=0; i < 2; i++){
                        if(m_nav2[i][0] > 9){
                            problema = 1;
                            break;

                        }
                    }
                    if (problema == 0){
                        mapa_maquina[linha][coluna] = 'V';
                        for(i=1; i<2; i++){
                            mapa_maquina[m_nav2[i][0]][m_nav2[i][1]] = 'V';
                        }
                    }
                }

                for (i=0 ; i < 5; i++)
                    {
                        for (j=0 ; j < 2; j++)
                        {
                            if(m_nav5[i][0] == m_nav2[j][0] && m_nav5[i][1] == m_nav2[j][1]){

                                l = m_nav5[i][0];
                                c = m_nav5[i][1];
                                mapa_maquina[l][c] = 'K';
                                problema = 1;
                                break;
                            }
                        }
                    }

                for (i=0 ; i < 4; i++)
                    {
                        for (j=0 ; j < 2; j++)
                        {

                            if(m_nav4[i][0] == m_nav2[j][0] && m_nav4[i][1] == m_nav2[j][1]){

                                l = m_nav4[i][0];
                                c = m_nav4[i][1];
                                mapa_maquina[l][c] = 'Z';
                                problema = 1;
                                break;
                            }
                        }
                    }

                for (i=0 ; i < 3; i++)
                    {
                        for (j=0 ; j < 2; j++)
                        {

                            if(m_nav3_1[i][0] == m_nav2[j][0] && m_nav3_1[i][1] == m_nav2[j][1]){

                                l = m_nav3_1[i][0];
                                c = m_nav3_1[i][1];
                                mapa_maquina[l][c] = 'P';
                                problema = 1;
                                break;
                            }
                        }
                    }

                for(i=0; i < 3; i++)
                    {
                        for(j=0 ; j < 2; j++)
                        {
                            if(m_nav3_2[i][0] == m_nav2[j][0] && m_nav3_2[i][1] == m_nav2[j][1]){

                                l = m_nav3_2[i][0];
                                c = m_nav3_2[i][1];

                                mapa_maquina[l][c] = 'Q';

                                problema = 1;
                                break;
                            }
                        }
                    }

            }while(problema != 0);

    // PARTIDA IRA COMECAR
    int linha_atq, coluna_atq, fim;

        fim = 0;

        while(fim == 0){
            //JOGADOR 1 ATACANDO
            do{
                if(fim == 1)
                {
                    break;
                }
                mostrar_tentativas(TAM, tentativa_j1);
                printf("\nQUEM ESTA ATACANDO: Jogador 01\n");

                do {
                    printf("\nDigite a LINHA do seu ataque: ");
                    scanf("%d", &linha_atq);

                    if(linha_atq < 0 || linha_atq > 9) {
                        printf("\nPosicao invalida\nDigite numeros no intervalo de 0 a 9\n");
                    }
                }while(linha_atq < 0 || linha_atq > 9);

                do {
                    printf("\nDigite a COLUNA do seu ataque: ");
                    scanf("%d", &coluna_atq);

                    if(coluna_atq < 0 || coluna_atq > 9) {
                        printf("\nPosicao invalida\nDigite numeros no intervalo de 0 a 9\n");
                    }
                }while(coluna_atq < 0 || coluna_atq > 9);

                if (mapa_maquina[linha_atq][coluna_atq] == 'X' || tentativa_j1[linha_atq][coluna_atq] == 'T')
                {
                    system("cls");
                    printf("\nEsse alvo ja foi selecionado, tente novamente JOGADOR 01\n");
                    continue;
                }

                if (mapa_maquina[linha_atq][coluna_atq] == mar)
                {
                    system("cls");
                    tentativa_j1[linha_atq][coluna_atq] = 'T';
                    printf("\nERROU! Agora quem ira jogar sera a MAQUINA\n");
                    break;
                }else
                {
                    system("cls");
                    printf("\nVOCE ACERTOU O ALVO! JOGADOR 01, CONTINUE A JOGAR \n");
                    mapa_maquina[linha_atq][coluna_atq] = 'X';
                    tentativa_j1[linha_atq][coluna_atq] = 'X';
                    pontuacaoj1 ++;
                    if (pontuacaoj1 == 17)
                    {
                        fim = 1;
                    }
                }
            }while (tentativa_j1[linha_atq][coluna_atq] != mar);

            // MAQUINA ATACANDO

            do{
                if(fim == 1)
                {
                    break;
                }

                linha_atq = rand() % 10;
                coluna_atq = rand() % 10;

                if (mapa_j1[linha_atq][coluna_atq] == 'X' || tentativa_maquina[linha_atq][coluna_atq] == 'T')
                {
                    continue;
                }

                if (mapa_j1[linha_atq][coluna_atq] == mar)
                {
                    tentativa_maquina[linha_atq][coluna_atq] = 'T';
                    mostrar_tabuleiro(TAM, tentativa_maquina);

                    printf("\nEsse foi o movimento da maquina! Como a maquina errou, agora e sua vez.\n\n\n");
                    system("pause");

                    break;
                }else
                {
                    mapa_j1[linha_atq][coluna_atq] = 'X';
                    tentativa_maquina[linha_atq][coluna_atq] = 'X';

                    pontuacao_maquina ++;
                    mostrar_tabuleiro(TAM, tentativa_maquina);
                    printf("\nEsse foi o movimento da maquina! Como a maquina acertou, ela ira jogar novamente.\n\n");
                    system("pause");

                    if (pontuacao_maquina == 17)
                    {
                        fim = 1;
                    }
                }


            }while (tentativa_maquina[linha_atq][coluna_atq] != mar);

    }

        printf("MAPA DO JOGADOR 01\n");
        mostrar_tabuleiro(TAM, mapa_j1);

        printf("MAPA DA MAQUINA\n");
        mostrar_tabuleiro(TAM, mapa_maquina);

        if(pontuacaoj1 > pontuacao_maquina)
        {
            printf("Fim de Jogo!\nJogador 1 venceu!\n");
        }
        else
        {
            printf("Fim de Jogo!\nMaquina venceu!\n");
        }

        printf("Pontuacao do JOGADOR 01: %d\n", pontuacaoj1);
        printf("Pontuacao da MAQUINA: %d\n", pontuacao_maquina);

        system("pause");

        system("cls");

        break;
    }

    return 0;
}

void mostrar_tabuleiro(int T, char map_j1[T][T]) {
    int i, j;
    printf("\n   0  1  2  3  4  5  6  7  8  9\n");
    for(i=0; i < T; i++){
        printf("%d ",i);
        for(j=0; j < T; j++){
            printf(" %c ", map_j1[i][j]);
        }
        printf("\n");
    }
}

void mostrar_tentativas(int T, char map_j1[T][T]) {
    int i, j;
    printf("\n   0  1  2  3  4  5  6  7  8  9\n");
    for(i=0; i < T; i++){
        printf("%d ",i);
        for(j=0; j < T; j++){
            printf(" %c ", map_j1[i][j]);
        }
        printf("\n");
    }
    printf("\nT: Tentativas\nX: Acertos\n");
}

int verificar_sobreposicoes(int navio5[5][2], int navio4[4][2], int navio3_1[3][2], int navio3_2[3][2], int navio2[2][2]) {
    int i, j;

    for (i=0 ; i < 5; i++) {
        for (j=0 ; j < 4; j++) {

            // VERIFICANDO SE HA CONFLITO COM O N4
            if(navio5[i][0] == navio4[j][0] && navio5[i][1] == navio4[j][1]) {
                printf("Ha uma sobreposicao entre o Navio de 5 Celulas e o de 4 Celulas\n");
                return 1;
            }


            if(j <= 2) {
                if(navio5[i][0] == navio3_1[j][0] && navio5[i][1] == navio3_1[j][1]) {
                    printf("Ha uma sobreposicao entre o Navio de 5 Celulas e o primeiro de 3 Celulas\n");
                    return 1;
                }
            }

            // VERIFICANDO SE HA CONFLITO COM O N3 UM E DOIS
            if(navio5[i][0] == navio3_2[j][0] && navio5[i][1] == navio3_2[j][1]) {
                printf("Ha uma sobreposicao entre o Navio de 5 Celulas e o segundo de 3 Celulas\n");
                return 1;
            }

            // VERIFICANDO SE HA CONFLITO COM O N2
            if(j <= 1) {
                if(navio5[i][0] == navio2[j][0] && navio5[i][1] == navio2[j][1]){
                    printf("Ha uma sobreposicao entre o Navio de 5 Celulas e o de 2 Celulas\n");
                    return 1;
                }
            }
        }
    }

        // VERIFICANDO SE HÁ SOBREPOSICOES NO N4
    for (i=0 ; i < 4; i++) {
        for (j=0 ; j < 3; j++) {

            if(j <= 2) {
                // VERIFICANDO SE HA CONFLITO COM O N3 UM E DOIS
                if(navio4[i][0] == navio3_1[j][0] && navio4[i][1] == navio3_1[j][1]) {
                    printf("Ha uma sobreposicao entre o Navio de 4 Celulas e o primeiro de 3 Celulas\n");
                    return 1;
                }

                if(navio4[i][0] == navio3_2[j][0] && navio4[i][1] == navio3_2[j][1]) {
                    printf("Ha uma sobreposicao entre o Navio de 4 Celulas e o segundo de 3 Celulas\n");
                    return 1;
                }
            }

            // VERIFICANDO SE HA CONFLITO COM O N2
            if(j <= 1) {
                if(navio4[i][0] == navio2[j][0] && navio4[i][1] == navio2[j][1]) {
                    printf("Ha uma sobreposicao entre o Navio de 4 Celulas e o de 2 Celulas\n");
                    return 1;
                }
            }
        }
    }

    // VERIFICANDO SE HÁ SOBREPOSICOES NO N3
    for (i=0 ; i < 3; i++) {
        for (j=0 ; j < 2; j++) {
            // VERIFICANDO SE HA CONFLITO COM O N2
            if(navio3_1[i][0] == navio2[j][0] && navio3_1[i][1] == navio2[j][1]) {
                printf("Ha uma sobreposicao entre o primeiro navio de 3 Celulas e o de 2 Celulas\n");
                return 1;
            }

            if(navio3_2[i][0] == navio2[j][0] && navio3_2[i][1] == navio2[j][1]) {
                printf("Ha uma sobreposicao entre o segundo navio de 3 Celulas e o de 2 Celulas\n");
                return 1;
            }
        }
    }

}
