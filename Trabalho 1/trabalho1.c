/*Trabalho 1 de Organização e Arquitetura de Computadores
UnB - CIC (2021)
Aluno: João Pedro Rebeschini*/

#include <stdio.h>
#include <stdint.h>

#define MEM_SIZE 4096
int32_t mem[MEM_SIZE];

int32_t lw(uint32_t address, int32_t kte)
{
    int32_t index = address + kte;
    if (index % 4 != 0)
    {
        printf("Nao multiplo de 4\n");
        return 0;
    }
    else
    {
        index = index / 4;
        return mem[index];
    };
};

int32_t lbu(uint32_t address, int32_t kte)
{
    if (kte < 0 || kte > 3)
    {
        printf("Byte invalido!\n");
        return 0;
    };
    if (address % 4 != 0)
    {
        printf("Nao divisivel por quatro!\n");
        return 0;
    };
    int32_t index = address / 4;
    if (index > 4096 || index < 0)
    {
        printf("Fora dos limites da memoria!\n");
        return 0;
    };
    int32_t data = mem[index];
    uint32_t output;
    uint32_t mask = 0x000000FF;
    output = (mask << (kte * 8)) & data;
    output = output >> (kte * 8);
    return output;
}

int32_t lb(uint32_t address, int32_t kte)
{
    if (kte < 0 || kte > 3)
    {
        printf("Byte invalido!\n");
        return 0;
    };
    if (address % 4 != 0)
    {
        printf("Nao divisivel por quatro!\n");
    };
    int32_t index = address / 4;
    int32_t data = mem[index];
    int32_t output;
    uint32_t mask = 0x000000FF;
    uint32_t mask2 = 0xFFFFFF00;
    output = (mask << (kte * 8)) & data;
    output = output >> (kte * 8);
    if (data < 0)
    {
        output = mask2 | output;
    }
    return output;

}

void sw(uint32_t address, int32_t kte, int32_t dado)
{
    int32_t index = address + kte;
    if (index % 4 != 0)
    {
        printf("Endereco nao divisivel por 4!\n");
    }
    else
    {
        index = index / 4;
        mem[index] = dado;
    };
    return;
}

void sb(uint32_t address, int32_t kte, int8_t dado)
{
    int32_t index = address + kte;
    if (address % 4 != 0)
    {
        printf("Nao divisivel por 4!\n");
        return;
    }
    int8_t *b_ptr = (int8_t *)mem;
    b_ptr[index] = dado;
}

int main()
{
    /*1. Iniciar a memória: executar a seguinte sequência de operações de escrita.*/
    printf("1.  Iniciar a memoria\n");
    sb(0, 0, 0x04);
    sb(0, 1, 0x03);
    sb(0, 2, 0x02);
    sb(0, 3, 0x01);
    sb(4, 0, 0xFF);
    sb(4, 1, 0xFE);
    sb(4, 2, 0xFD);
    sb(4, 3, 0xFC);
    sw(12, 0, 0xFF);
    sw(16, 0, 0xFFFF);
    sw(20, 0, 0xFFFFFFFF);
    sw(24, 0, 0x80000000);
    printf("Memoria inicializada!\n\n");
    /*2. Imprimir o conteúdo da memória em formato hexa. O resultado deve ser:*/
    printf("2. Imprimir o conteudo da memoria em formato hexa.\n");
    printf("  ----------\n");
    printf("a:|%08x|\n", mem[0]);
    printf("b:|%08x|\n", mem[1]);
    printf("c:|%08x|\n", mem[2]);
    printf("d:|%08x|\n", mem[3]);
    printf("e:|%08x|\n", mem[4]);
    printf("f:|%08x|\n", mem[5]);
    printf("g:|%08x|\n", mem[6]);
     printf("  ----------\n\n\n");
    /*3. Ler os dados e imprimir em hexadecimal:*/
    printf("3.Ler os dados e imprimir em hexadecimal:\n");
    printf("lb(4, 0):%08x\n", lb(4, 0));
    printf("lb(4, 1):%08x\n", lb(4, 1));
    printf("lb(4, 2):%08x\n", lb(4, 2));
    printf("lb(4, 3):%08x\n", lb(4, 3));
    printf("--------------\n");
    printf("lbu(4, 0):%08x\n", lbu(4, 0));
    printf("lbu(4, 1):%08x\n", lbu(4, 1));
    printf("lbu(4, 2):%08x\n", lbu(4, 2));
    printf("lbu(4, 3):%08x\n", lbu(4, 3));
    printf("--------------\n");
    printf("lw(12, 0):%08x\n", lw(12, 0));
    printf("lw(16, 0):%08x\n", lw(16, 0));
    printf("lw(20, 0):%08x\n\n", lw(20, 0));

    /*4. Testes extras */
    printf("Testes:");
    int32_t data1, data2, data3;
    lw(5, 0);
    lbu(4, 4);
    lb(5, 1);
    sw(5, 1, 0xFFFFFFFF);
    sb(3, 0, 0xFF);
    sw(40, 0, 0xFF1234AB);
    sb(44, 2, lw(40, 0));
    printf("Byte de busca: ab\n");
    printf("Byte manipulado: %02x", lb(44, 2));

    return 0;
}
