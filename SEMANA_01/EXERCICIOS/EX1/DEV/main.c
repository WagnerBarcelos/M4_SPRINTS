#define DIREITA 0
#define ESQUERDA 1
#define FRENTE 2
#define TRAS 3

#include <stdio.h>
#include <string.h>

int converteSensor(float medida, float min, float max);
int leituraSensor();
int armazenaVetor(int *vetor, int tamanhoVetor, int posicao, int medida);
int direcaoMenorCaminho(int *vetor, int *var);
int leComando();



int main (){
    int i = 0;
    int max = 64;
    int vetor[max]; // capacidade de ate 16 conjuntos de leituras 

    do{
        int direcao = -1;
        int distancia;
        char string_direcao[25];

        // cada conjunto de leituras recebe 4 leituras e preenche o vetor
        for(int j = 0; j < 4; j++){
            int medida = leituraSensor();
            i = armazenaVetor(vetor, max, i, medida);
        }
        
        // ((i-1)/4) * 4 --> caso nao seja o primeiro conjunto de leituras ((i-1)/4 == 0), retorna a exata posicao da primeira leitura do conjunto atual
        direcao = direcaoMenorCaminho(vetor + ((i-1)/4) * 4, &distancia);
        
        if(direcao == DIREITA){
            strcpy(string_direcao, "DIREITA");
        }
        if(direcao == ESQUERDA){
            strcpy(string_direcao, "ESQUERDA");
        }
        if(direcao == FRENTE){
            strcpy(string_direcao, "FRENTE");
        }
        if(direcao == TRAS){
            strcpy(string_direcao, "TRAS");
        }
        
        printf("\nDirecao: %s\nDistancia: %d\n", string_direcao, distancia);
    }
    while(leComando());
}

/*
1. Implemente a função 'converteSensor' que receberá 3 argumentos: uma medida, um valor mínimo e um valor máximo. A função retornará o valor percentual da medida (0 a 100) em função do intervalo entre os valores mínimo e máximo.
*/
int converteSensor(float medida, float min, float max){
    // funcao para normalizar medidas entre 0 e 1
    float temp = (medida - min) / (max - min);

    // retorna a medida entre 0 e 100
    // converte explicitamente de float para int
    return (int)(temp * 100);
}

/*
2. Implemente a função 'leituraSensor' que não receberá argumentos. Esta função tem por objetivo simular a leitura de sensores (neste caso, sensores de distância). A função solicita e retorna um valor inteiro, entre o intervalo de mínimo e máximo (ver item 1), digitado pelo usuário (via teclado).
*/
int leituraSensor(){
    float medida, min, max;

    printf("Digite os valores (medida | min | max): ");
    scanf("%f%f%f", &medida, &min, &max);
    
    return converteSensor(medida, min, max);
}

/*
3. Implemente a função 'armazenaVetor' que receberá 4 argumentos: o ponteiro do vetor que receberá a medida, o tamanho do vetor, a posição atual para armazenamento e a medida para ser armazenada no vetor. A função deve armazenar a medida no vetor, segundo posição indicada (posição atual) e retornar a próxima posição para armazenamento futuro.
*/
int armazenaVetor(int *vetor, int tamanhoVetor, int posicao, int medida){
    if(posicao >= tamanhoVetor){
        printf("ERRO: Nao ha espaco disponivel no vetor!\n");
        return -1;
    }

    vetor[posicao] = medida;
    return posicao + 1;

}

/*
4. Implemente a função 'direcaoMenorCaminho' que receberá 2 argumentos: (1) o ponteiro para um vetor e (2) o ponteiro para uma variável. Esta função deve avaliar 4 valores do vetor, a partir do ponteiro (1) recebido. Os 4 valores representam as distâncias nos sentidos: Direta, Esquerda, Frente e Trás (esses valores foram inseridos com a função 'leituraSensor', convertidos com a função 'converteSensor' e armazenados no vetor com a função 'armazenaVetor'). Esta função retorna o sentido de maior distância, e com base no ponteiro (2) para a variável, nela armazena o valor da maior distância.
*/
int direcaoMenorCaminho(int *vetor, int *var){
    int direita, esquerda, frente, tras;
    direita = vetor[DIREITA];
    esquerda = vetor[ESQUERDA];
    frente = vetor[FRENTE];
    tras = vetor[TRAS];

    int maiorDistancia = -1;
    int direcao = -1;

    // compara todos as direcoes procurando a maior
    if(direita > maiorDistancia){
        direcao = DIREITA;
        maiorDistancia = direita;
    }
    if(esquerda > maiorDistancia){
        direcao = ESQUERDA;
        maiorDistancia = esquerda;
    }
    if(frente > maiorDistancia){
        direcao = FRENTE;
        maiorDistancia = frente;
    }
    if(tras > maiorDistancia){
        direcao = TRAS;
        maiorDistancia = tras;
    }

    // acessa o ponteiro e armazena o valor da distancia
    *var = maiorDistancia;
    return direcao;
}

/*
5. Implemente a função 'leComando' que não receberá argumentos. Esta função pergunta ao usuário se ele deseja continuar o mapeamento. A função retorna o inteiro 1 (um) se a resposta for SIM ou 0 (zero) se a resposta for NÃO.
*/
int leComando(){
    // se repete infinitamente até retornar algo
    while(1){
        printf("\nDeseja continuar o mapeamento? ");
        char string[30];
        scanf("%s", string);
        // funcao para comparar a string lida com a string "SIM"
        // strcmp retorna 0 caso as strings sejam iguais
        if(strcmp(string, "SIM") == 0){
            return 1;
            printf("sera");
        }
        // funcao para comparar a string lida com a string "NAO"
        else if(strcmp(string, "NAO") == 0){
            return 0;
        }
        else{
            printf("ERRO: Opcao invalida!\n");
        }
    }
}