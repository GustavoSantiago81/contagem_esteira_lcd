#define _XTAL_FREQ 4000000	// define frequência do cristal
#include <stdio.h>        //biblioteca padrão do C para funções de entradas/saídas
#include <xc.h>           //biblioteca com as definições do microcontrolador
#include "config_bits.h"  //arquivo de configurações de bits do microcontrolador
#include "lcd.h"         //arquivo com as definições do display LCD
#include "adc.h"

char linha1[16]; //Linha 1 do Display máximo 16 caracteres
char linha2[16];

void main (void)
{
    TRISD = 0x00;   //Configura o port D como saída
    TRISE = 0X00;
    Lcd_Init(); //Chama a função para inicializar os parâmetros do lcd
    ADC_Init(); // Inicializa ADC
    
    //Declaração de Variáveis
    unsigned char i;
    unsigned int ValorADC;
    char ValorInt[4];

    while(1)
    {
        ValorADC = ADC_Read();

        ValorInt[0] = ValorADC%10;          //Equivalente ao valor da unidade
        ValorInt[1] = (ValorADC/10)%10;     //Equivalente ao valor da dezena
        ValorInt[2] = (ValorADC/100)%10;    //Equivalente ao valor da centena
        ValorInt[3] = ValorADC/1000;   //Equivalente ao valor da milhar
        
        //Mensagem a ser escrita na primeira linha
        sprintf(linha1,"Valor Convertido");    
        Lcd_Set_Cursor(1,1);  // Posiciona na linha 1
        Lcd_Write_String(linha1);
        
        //Apresentação do valor da conversão AD
        sprintf(linha2,"%d%d%d%d",ValorInt[3],ValorInt[2],ValorInt[1],ValorInt[0]);    
        Lcd_Set_Cursor(2,1);  // Posiciona na linha 1
        Lcd_Write_String(linha2);
    }
}
