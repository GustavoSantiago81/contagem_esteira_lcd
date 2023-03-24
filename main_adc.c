#define _XTAL_FREQ 4000000	// define frequ�ncia do cristal
#include <stdio.h>        //biblioteca padr�o do C para fun��es de entradas/sa�das
#include <xc.h>           //biblioteca com as defini��es do microcontrolador
#include "config_bits.h"  //arquivo de configura��es de bits do microcontrolador
#include "lcd.h"         //arquivo com as defini��es do display LCD
#include "adc.h"

char linha1[16]; //Linha 1 do Display m�ximo 16 caracteres
char linha2[16];

void main (void)
{
    TRISD = 0x00;   //Configura o port D como sa�da
    TRISE = 0X00;
    Lcd_Init(); //Chama a fun��o para inicializar os par�metros do lcd
    ADC_Init(); // Inicializa ADC
    
    //Declara��o de Vari�veis
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
        
        //Apresenta��o do valor da convers�o AD
        sprintf(linha2,"%d%d%d%d",ValorInt[3],ValorInt[2],ValorInt[1],ValorInt[0]);    
        Lcd_Set_Cursor(2,1);  // Posiciona na linha 1
        Lcd_Write_String(linha2);
    }
}
