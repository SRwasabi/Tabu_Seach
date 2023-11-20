#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#define MAX_ITERACOES 20

/*
TODO LIST

PERMUTAR A LISTA DE ITENS DE MANEIRAS DIFERENTES
BANIR MOVIMENTOS
JULGAR A LISTA PELO solucao.area_ocupada.

*/

//escopo de funcoes
int valor_item(int item);
void tabu_search(int[], int[]);
enum Erro solucao_valida(int[]);
int area_total(int);
int valor_total_sacola(int []);
int valor_item(int);
bool posiciona_sacola(int, int [30][30]);
void tamanho_item(int, int *, int *);
int area_ocupada(int [30][30]);
void log();


//global variaveis
FILE *logfile;
int itens[8] = {4,1,4,5,4,4,5,4}, sacola[30][30];
enum Erro{
    PRECO,
    TAMANHO,
    COUBE
};
struct Solucao{
    enum Erro erro;
    uint16_t area_total;
    uint16_t area_ocupada;
    int16_t preco;
}solucao;



//funcoes
int main(){
    logfile = fopen("logfile.txt","w+");
    srand(time(NULL)); 
    int melhor_solucao[8], i;
    memset(melhor_solucao,0,sizeof(melhor_solucao));
    // for (i = 0; i < 8; i++)
    // {
    //     itens[i] = (rand()%8)+1;
    // }
    tabu_search(itens, melhor_solucao);
    log();
    fclose(logfile);
    return 0;
}

void tabu_search(int itens[], int melhor_solucao[]){
    int lista_tabu[10],vetor;
    solucao.erro = solucao_valida(itens);

}

enum Erro solucao_valida(int itens[]){
    int i, j, tamanhos[8][2];
    memset(sacola,0,30*30*sizeof(int));
    memset(&solucao,0,sizeof(struct Solucao));
    

    solucao.preco = valor_total_sacola(itens);
    //se extrapolar 100 real retorna o erro de preco
    if(solucao.preco > 100) return PRECO;



    //soma a area total de todos os itens
    for(i=0;i<8;i++){
        solucao.area_total += area_total(itens[i]);
    } 
    //se for maior que 900 entao nem cabe na sacola e retorna o erro tamanho
    if(solucao.area_total>900) return TAMANHO;



    for (i = 0; i < 8; i++){
        if(!posiciona_sacola(itens[i], sacola))
            solucao.preco -= valor_item(itens[i]); //Remove o item da sacola
    }


    //me diz a area que foi ocupada pelos itens na sacola pela ordenação atual
    solucao.area_ocupada = area_ocupada(sacola);

    return COUBE;
}

//retorna a area somada de todos os itens independente da organização, calculo somente para verificar se a soma de todos os itens ultrpassa o tamanhho da sacola
int area_total(int item){
    int tam_x, tam_y;
    tamanho_item(item, &tam_x, &tam_y);
    return (tam_x*tam_y);
}

int valor_total_sacola(int itens[]){
    int i, total = 0;
    for(i = 0; i < 8; i++){
        total += valor_item(itens[i]);
    }
    return total;
}

int valor_item(int item){
    switch(item)
    {
    case 1:
        return 3;
    case 2:
        return 5;
    case 3:
        return 6;
    case 4:
        return 8;
    case 5:
        return 10;
    case 6:
        return 12;
    case 7:
        return 20;
    case 8:
        return 30;
    }
}

bool posiciona_sacola(int item, int sacola[30][30]){
    int i, x, y, j;
    bool cabe;
    for (j = 0; j < 30; j++){        
        for (i = 0; i < 30; i++){
            cabe = 1;
            if(sacola[i][j] == 0){
                int tam_x, tam_y;
                tamanho_item(item, &tam_x, &tam_y);
                if(i + tam_y > 30){
                    j++;
                    break;
                }
                if((i + tam_y > 30) && (j + tam_x > 30)) return ; //O item nao cabe na mochila

                //Verifica se e possivel guardar o item sem sobrepor outros itens guardados
                for(y = 0; y < tam_y; y++){
                    for(x = 0; x < tam_x; x++){
                        if(sacola[y+i][x+j] != 0){//A area esta ocupada!
                            cabe = 0;
                        }
                    }
                }
                if(cabe){
                    for(y = 0; y < tam_y; y++)
                        {
                            for(x = 0; x < tam_x; x++)
                            {
                                sacola[y+i][x+j] = item;
                            }
                        }
                }else break;
                return cabe;
            }
        }
    }
    //Sacola esta cheia!
    return cabe;
    }

void tamanho_item(int item, int * tam_x, int * tam_y){
    switch(item)
    {
    case 1:
        *tam_x = 15;
        *tam_y = 15;
        return;
    case 2:
        *tam_x = 10;
        *tam_y = 10;
        return;
    case 3:
        *tam_x = 7;
        *tam_y = 4;
        return;
    case 4:
        *tam_x = 7;
        *tam_y = 2;
        return;
    case 5:
        *tam_x = 6;
        *tam_y = 4;
        return;
    case 6:
        *tam_x = 5;
        *tam_y = 5;
        return;
    case 7:
        *tam_x = 3;
        *tam_y = 3;
        return;
    case 8:
        *tam_x = 1;
        *tam_y = 1;
        return;
    }
}

int area_ocupada(int sacola[30][30]){
    int i, j, x=0, y=0;
    for(i=0;i<30;i++) for(j=0;j<30;j++){
        if(sacola[i][j]!=0){
            x = (x<i+1) ? i+1: x;
            y = (y<j+1) ? j+1: y;
        }
    }
    return (x*y);
}

//funcao para escrever tudo em um arquivo de log
void log(){
    int i, j;
    fprintf(logfile,"itens: ");
    for (i = 0; i < 8; i++){
        fprintf(logfile,"%d ", itens[i]);
    }
    fprintf(logfile,"\nValor TOTAL = %i\n",solucao.preco);
    fprintf(logfile,"Area total: %i\n\n",solucao.area_total);
    for(i = 0; i < 30; i++){
        for(j = 0; j < 30; j++){
            fprintf(logfile,"%d ", sacola[i][j]);
        }
        fprintf(logfile,"\n");
    }
    switch (solucao.erro){
        case 0:
            fprintf(logfile,"\nO preço ultrapassou o limite de 100");
            break;
        case 1:
            fprintf(logfile,"\nO tamanho de todos os itens ultrapassa o tamanho da sacola");
            break;
        case 2:
            fprintf(logfile,"\nTudo certo!");
            break;
    }
    fprintf(logfile,"\nArea ocupada: %i\n",solucao.area_ocupada);
    fprintf(logfile,"Valor FINAL = %i\n",solucao.preco);

}