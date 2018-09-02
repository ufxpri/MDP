#include <io.h>
#include <delay.h>
#include <stdio.h>
#include <alcd.h>

#define BUF_SIZE 16
#define QUEUE_SIZE 32

void tx_trans(int, char);

volatile unsigned char sbuf[BUF_SIZE];

char data0, data1;

interrupt [USART0_RXC] void usart0_rx_isr(void){
    //char data0;
    //char status, data;
    //status = UCSR0A;
    data0 = UDR0;  
    tx_trans(1,data0);    
    //lcd_putchar(data0);
    //qput0(UDR0); 
}

interrupt [USART1_RXC] void usart1_rx_isr(void){
    //char status, data;
    //status = UCSR01A;  
    //char data1;
    //status = UCSR1A;
    data1 = UDR1;   
    tx_trans(0,data1);    
    lcd_putchar(data1);
    //qput0(UDR1);
}

void tx_trans(int tx_port, char data){
    switch(tx_port)
    {
        case 0:
            //while(!(UCSR1A & 0x80));
            while(!(UCSR0A & 0x20));
            UDR0 = data;
            break;
        case 1:
            //while(!(UCSR0A & 0x80));
            while(!(UCSR1A & 0x20));
            UDR1 = data;
            break;
        default:
            break;
    }
}

void tx_str_trans(int tx_port, unsigned char *tx_str){
    int i = 0;
    while(*(tx_str+i) != '\0')
    {
        tx_trans(tx_port,*(tx_str+i));
        i++;
    }
}

void init(){
    UCSR0A=(0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (0<<U2X0) | (0<<MPCM0);
    UCSR0B=(1<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
    UCSR0C=(0<<UMSEL0) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);
    UBRR0H=0x00;
    UBRR0L=0x67;         
              
    UCSR1A=(0<<RXC1) | (0<<TXC1) | (0<<UDRE1) | (0<<FE1) | (0<<DOR1) | (0<<UPE1) | (0<<U2X1) | (0<<MPCM1);
    UCSR1B=(1<<RXCIE1) | (0<<TXCIE1) | (0<<UDRIE1) | (1<<RXEN1) | (1<<TXEN1) | (0<<UCSZ12) | (0<<RXB81) | (0<<TXB81);
    UCSR1C=(0<<UMSEL1) | (0<<UPM11) | (0<<UPM10) | (0<<USBS1) | (1<<UCSZ11) | (1<<UCSZ10) | (0<<UCPOL1);
    UBRR1H=0x00;
    UBRR1L=0x67;  
    
    lcd_init(16);  
    #asm("sei")
}

void main(){
    init();    
    
    lcd_init(16);
    lcd_clear();
    
    while(1)
    {  
    }
}