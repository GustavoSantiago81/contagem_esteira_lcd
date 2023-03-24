// =============================================== //
// BIBLIOTECA PARA USO DE ADC NO PIC 18F4550       //
// =============================================== //

// -----------------------------------------------------
// Rotina de inicializa��o do m�dulo ADC
// -----------------------------------------------------
void ADC_Init(void)
{
 TRISAbits.TRISA2 = 1; // Configura RA0 (AN0) como entrada
 ADCON0 = 0x08;        // Configura refer�ncia de tens�o (Vdd e Vss) e habilita AN2 (entrada do ADC)
 ADCON1 = 0x0C;        // Configura o pino como entrada anal�gica (apenas o pino AN2)
 ADCON2 = 0xD9;        // Configura o tempo de aquisi��o (vide datasheet)
 ADCON0bits.ADON = 1;  // Liga m�dulo ADC
}
// -----------------------------------------------------

// -----------------------------------------------------
// Rotina de leitura do ADC
// -----------------------------------------------------
unsigned int ADC_Read(void)
{
    unsigned int temp;

    ADCON0bits.GO = 1;               // Inicia aquisi��o
    while(ADCON0bits.DONE);         // Aguarda o fim da aquisi��o (quando bit DONE = 0)
    temp = ADRESH;                  // Parte alta do valor lido
    temp = ((temp << 8)| ADRESL );  // Junta parte alta com parte baixa em um valor de 16 bits

return temp;
}
// -----------------------------------------------------