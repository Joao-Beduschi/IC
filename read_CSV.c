#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CSV
{
    char (*colloum)[50];
    float (**valor);

};


struct CSV CSVReader(char filename[50]){
    char buffer[1000];
    struct CSV *teste = malloc(sizeof(struct CSV));
    FILE *csv_File = fopen(filename,"r");
    if(csv_File == NULL){
        printf("erro");
        exit(-1);
    }
    fgets(buffer,sizeof(buffer),csv_File);
    char *nomes = strtok(buffer,",");
    int i = 0;
    int colunas = 2;
    teste->colloum = malloc(colunas*(sizeof(*teste->colloum)));
    teste->valor = malloc(sizeof(teste->valor));
    if (teste->colloum == NULL) {
        free(teste);
        return *teste;
    }
    while(nomes != NULL){
        if(i>colunas){
           colunas++;
           teste->colloum = realloc(teste->colloum,sizeof(teste->colloum)*colunas);
        }
        strcpy(teste->colloum[i],nomes);
        printf("%s\n", teste->colloum[i]);
        nomes = strtok(NULL,",");
        i++;
    }
    teste->valor = malloc(colunas*sizeof(float*));
    char *valores = fgets(buffer,sizeof(buffer),csv_File);
    int linhas = 0;
    for(int f=0; f<colunas;f++){
        teste->valor[f] = malloc(sizeof(float));
        if(f ==0){
            teste->valor[f][linhas] = atof(strtok(valores,","));
        }
        else{
            teste->valor[f][linhas] = atof(strtok(NULL,","));
        }
    }
    linhas++;
    while(fgets(buffer, sizeof(buffer), csv_File) != NULL){
        for(int f=0; f<colunas;f++){
            teste->valor[f] = realloc(teste->valor[f],sizeof(float)*(linhas+1));
            if(f ==0){
                teste->valor[f][linhas] = atof(strtok(buffer,","));
            }
            else{
                teste->valor[f][linhas] = atof(strtok(NULL,","));
            }          
        }
        linhas++;
    }
    fclose(csv_File);
    return *teste;
}

int main(void) {
    char filename[50] = "dados_teste_100x2.csv";
    struct CSV resultado = CSVReader(filename);
    printf("%f\n", resultado.valor[1][10]);

    // Liberação da memória alocada dentro de CSVReader
    for (int f = 0; f < 2; f++) {
        free(resultado.valor[f]);
    }
    free(resultado.valor);
    free(resultado.colloum);

    return 0;
}