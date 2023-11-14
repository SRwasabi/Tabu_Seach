#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int valor_item(int item);
void tabu_search(int[], int[]);
int solucao_valida(int[]);
int valor_total_sacola(int []);
int valor_item(int);
bool posiciona_sacola(int, int [30][30]);
void tamanho_item(int, int *, int *);

int main(){
    srand(time(NULL));
    int itens[8] = {4,1,4,5,4,4,5,4}, melhor_solucao[8], i;
    memset(melhor_solucao,0,sizeof(melhor_solucao));
    // for (i = 0; i < 8; i++)
    // {
    //     itens[i] = (rand()%8)+1;
    // }
    tabu_search(itens, melhor_solucao);
    for (i = 0; i < 8; i++)
    {
        printf("%d ", itens[i]);
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
    printf("Valor TOTAL = %i\n",valor);
    int i, j;
    if(valor > 1000) return 999;
    int sacola[30][30];
    memset(sacola,0,30*30*sizeof(int));

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
    printf("Valor FINAL = %i\n",valor);
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

bool posiciona_sacola(int item, int sacola[30][30]){
    int i, x, y, j;
    bool cabe;
    for (i = 0; i < 30; i++){
        for (j = 0; j < 30; j++){        
            cabe = 1;
            if(sacola[i][j] == 0){
                int tam_x, tam_y;
                tamanho_item(item, &tam_x, &tam_y);
                if(j + tam_x > 30){
                    i++;
                    break;
                }
                if((i + tam_y > 30) && (j + tam_x > 30)) return false; //O item nao cabe na mochila

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
//Sacola esta� cheia!
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



