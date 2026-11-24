#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct Codificado{
    float *valor_inicial;
    uint16_t valor_codificado;
    int binario[16];
};

struct Decodificado{
    float *valor_final;
    uint16_t *valor_codificado;
    int *binario[16];

};

struct Codificado encoder(float *valor){
    if(*valor>1 || *valor<0.6){
        printf("Valor não condizente");
        struct Codificado erro;
        erro.valor_codificado = 0x00;
        erro.valor_inicial = (float*)5;
        return erro;
    }
    else{
        float valor_max = 1;
        float valor_min = 0.6;
        int jump_num = (1 << 16) - 1; 
        float diff = (valor_max-valor_min);
        float res = diff/jump_num;
        struct Codificado resultado;
        resultado.valor_inicial = valor;
        resultado.valor_codificado =(uint16_t)roundf((*valor - valor_min)/res);
        printf("certo\n");
        for(int i=0;i<16;i++){
            resultado.binario[i] = (resultado.valor_codificado >> (15 - i)) & 1;
            printf("%u \n",resultado.binario[i]);
        }
        return resultado;
    }
}

int main(void){
    float valor_teste = 0.988;
    encoder(&valor_teste);

}