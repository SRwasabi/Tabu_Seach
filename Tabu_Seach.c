#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int valor_item(int item);
void tabu_search(int[], int[]);
int solucao_valida(int[]);
int valor_total_sacola(int []);
int valor_item(int);
bool posiciona_sacola(int, bool [30][30]);
void tamanho_item(int, int *, int *);

int main(){
    srand(time(NULL));
    int itens[8], melhor_solucao[8], i;
    memset(melhor_solucao,0,sizeof(melhor_solucao));
    for (i = 0; i < 8; i++)
    {
        itens[i] = 4;//(rand()%8)+1;
    }
    tabu_search(itens, melhor_solucao);
    for (i = 0; i < 8; i++)
    {
        printf("%d ", melhor_solucao[i]);
    }
    return 0;
}

#define MAX_ITERACOES 20
void tabu_search(int itens[], int melhor_solucao[]){
    int lista_tabu[10];
    int Vtotal = solucao_valida(itens);

}

int solucao_valida(int itens[]){
    int valor = valor_total_sacola(itens);
    int i, j;
    if(valor > 1000) return 999;
    bool sacola[30][30];
    memset(sacola,0,30*30*sizeof(bool));
    //memset(sacola,0,sizeof(sacola));

    for (i = 0; i < 8; i++)
    {
        if(!posiciona_sacola(itens[i], sacola))
            valor -= valor_item(itens[i]); //Remove o item da sacola
        }

        for(i = 0; i < 30; i++){
            for(j = 0; j < 30; j++){
                printf("%d ", sacola[i][j]);
            }
            printf("\n");
        }

    return valor;
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
    case 0:
        return 0;
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

bool posiciona_sacola(int item, bool sacola[30][30]){
    int i;
    int j;
    bool veri = 1;
  do{                                   //sacola = calloc(30*30, sizeof(bool *));
    for (i = 0; i < 30; i++){
                                         //sizeof(sacola)/sizeof(*sacola)
        for (j = 0; j < 30; j++){
                                        //sizeof(sacola)/sizeof(*(sacola[i]))
//Procura um espaco vazio
            if(sacola[i][j] == 0){
                int tam_x, tam_y;

//Posiciona o item no espaco
///erro aqui

                tamanho_item(item, &tam_x, &tam_y);
                if((i + tam_y > 30) && (j + tam_x > 30))
//O item não cabe na mochila
                return false;
//Verifica se é possível guardar o item sem sobrepor outros itens guardados
                int x,y;
                for(y = 0; y < tam_y; y++){
                    for(x = 0; x < tam_x; x++){
                        if(sacola[y+i][x+j] != 0){
//A área já está ocupada!
                            //return false;
                            veri == 0;
                        }
                    }
                }
//Posiciona o item nos espacos ‘0’
                if(veri == 1){
                    for(y = 0; y < tam_y; y++)
                    {
                        for(x = 0; x < tam_x; x++)
                        {
                            sacola[y+i][x+j] = item;
                        }
                    }
                }
//Posicionou o item na sacola
                return true;
            }
        }
    }
    }while(veri == true);
//Sacola esta’ cheia!
    return false;
    }


void tamanho_item(int item, int * tam_x, int * tam_y){
    switch(item)
    {
    case 0:
        *tam_x = 0;
        * tam_y = 0;
        return;
    case 1:
        *tam_x = 15;
        * tam_y = 15;
        return;
    case 2:
        *tam_x = 10;
        * tam_y = 10;
        return;
    case 3:
        *tam_x = 7;
        * tam_y = 4;
        return;
    case 4:
        *tam_x = 7;
        * tam_y = 2;
        return;
    case 5:
        *tam_x = 6;
        * tam_y = 4;
        return;
    case 6:
        *tam_x = 5;
        * tam_y = 5;
        return;
    case 7:
        *tam_x = 3;
        * tam_y = 3;
        return;
    case 8:
        *tam_x = 1;
        * tam_y = 1;
        return;
    }
}



