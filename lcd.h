/*
 * File: lcd.h
 * Descrição: arquivo de definições para display de cristal líquido - LCD    
 */

//***definições de ligação do LCD ao MCU***

 /* 
 * troque essas definições de acordo com
 * as ligações do display em seu hardware
 */
#define RS LATEbits.LATE0
#define EN LATEbits.LATE1
#define D4 LATDbits.LATD4
#define D5 LATDbits.LATD5
#define D6 LATDbits.LATD6
#define D7 LATDbits.LATD7

//***envia valor do PORT ao LCD***
void Lcd_Port(char a){
	if(a & 1)
		D4 = 1;
	else
		D4 = 0;

	if(a & 2)
		D5 = 1;
	else
		D5 = 0;

	if(a & 4)
		D6 = 1;
	else
		D6 = 0;

	if(a & 8)
		D7 = 1;
	else
		D7 = 0;
}
//***instrução de comando***
void Lcd_Cmd(char a){  
    RS = 0;             
    Lcd_Port(a);
    EN  = 1;             
    __delay_ms(4);
    EN  = 0;             
}
//***limpa LCD***
void Lcd_Clear(void){                         
	Lcd_Cmd(0x00);      //4 bits + significativos para comando limpar LCD
	Lcd_Cmd(0x01);      //4 bits - significativos para comando limpar LCD
}
//***posiciona o cursor (a -> linha, b -> posição)***
void Lcd_Set_Cursor(char a, char b){    
	char temp,z,y;
	if(a == 1){
        temp = 0x80 + b - 1;
		z = temp>>4;
		y = temp & 0x0F;
		Lcd_Cmd(z);
		Lcd_Cmd(y);
	}
	else if(a == 2){
        temp = 0xC0 + b - 1;
		z = temp>>4;
		y = temp & 0x0F;
		Lcd_Cmd(z);
		Lcd_Cmd(y);
	}
}
//***inicializa LCD com comunicação a 4 bits***
void Lcd_Init(){   
    Lcd_Cmd(0x00);        //4 bits + significativos para comunicação a 4 bits
    Lcd_Cmd(0x03);        //4 bits - significativos para comunicação a 4 bits 
    __delay_ms(5);        //tempo de estabilização dos sinais (ver datasheet do LCD)

    Lcd_Cmd(0x00);        //4 bits + significativos para comunicação a 4 bits
    Lcd_Cmd(0x03);        //4 bits - significativos para comunicação a 4 bits 
    __delay_ms(11);       //tempo de estabilização dos sinais (ver datasheet do LCD)    


    Lcd_Cmd(0x00);        //4 bits + significativos para comunicação a 4 bits
    Lcd_Cmd(0x03);        //4 bits - significativos para comunicação a 4 bits 
    __delay_ms(11);       //tempo de estabilização dos sinais (ver datasheet do LCD)     

    Lcd_Cmd(0x00);        //4 bits + significativos para CURSOR HOME
    Lcd_Cmd(0x02);        //4 bits - significativos para CURSOR HOME



    Lcd_Cmd(0x02);        //4 bits + significativos para FUNCTION SET - Configura o LCD para 4 bits,
                          //2 linhas, fonte 5X7.
    Lcd_Cmd(0x08);        //4 bits + significativos para FUNCTION SETs


    Lcd_Cmd(0x00);        //4 bits + significativos para DISPLAY CONTROL - Display ligado, sem cursor
    Lcd_Cmd(0x0C);        //4 bits - significativos para DISPLAY CONTROL

    Lcd_Cmd(0x00);        //4 bits + significativos para ENTRY MODE SET - Desloca o cursor para a direita
    Lcd_Cmd(0x06);        //4 bits + significativos para ENTRY MODE SET

    Lcd_Clear();          //limpa LCD
}

//***escreve um caractere no LCD***
void Lcd_Write_Char(char a){        
   char temp,y;
   temp = a&0x0F;
   y = a&0xF0;
   RS = 1;             
   Lcd_Port(y>>4);             
   EN = 1;
   __delay_us(40);
   EN = 0;
   Lcd_Port(temp);
   EN = 1;
   __delay_us(40);
   EN = 0;
}
//***escreve uma string no LCD***
void Lcd_Write_String(char *a){   
	int i;
	for(i=0;a[i]!='\0';i++)
	   Lcd_Write_Char(a[i]);
}
//***desloca mensagem uma posição para direita***
void Lcd_Shift_Right(){          
	Lcd_Cmd(0x01);
	Lcd_Cmd(0x0C);
}
//***desloca mensagem uma posição para a esquerda***
void Lcd_Shift_Left(){               
	Lcd_Cmd(0x01);
	Lcd_Cmd(0x08);
}