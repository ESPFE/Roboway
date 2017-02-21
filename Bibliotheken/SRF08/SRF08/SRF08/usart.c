#include "usart.h"


void setUsartBaudRate( uint32_t usartBaudRate )
{
    // liegt Baudrate noch im Toleranzbereich?? ( +/- 5% )
    if( USART_BAUD_CALC( usartBaudRate ) > 30 )
    {
        UBRR0H = (uint8_t)HIGH_BYTE( USART_BAUD_CALC( usartBaudRate ) );
        UBRR0L = (uint8_t)LOW_BYTE( USART_BAUD_CALC( usartBaudRate ) );
        UCSR0A = 0x00;
    }
    // Ansonsten Doppelte Baudrate verwenden
    else
    {
        UBRR0H = (uint8_t)HIGH_BYTE( USART_DOUBLE_BAUD_CALC( usartBaudRate ) );
        UBRR0L = (uint8_t)LOW_BYTE( USART_DOUBLE_BAUD_CALC( usartBaudRate ) );
        UCSR0A = ( 1 << U2X0 );
    }
}


// USART0 initialisieren
void setupUsart0( uint32_t usartBaudRate )
{
    // BaudRate einstellen
    setUsartBaudRate( usartBaudRate );
    // RX, TX und Interrupts einschalten
    UCSR0B = ( 1 << RXEN0 ) | ( 1 << TXEN0 ) | ( 1 << RXCIE0 );
    // 8n1 -> 1 Startbit , 8 Datenbits , 1 Stopbit
    UCSR0C = ( 1 << UCSZ00 ) | ( 1 << UCSZ01 );
}


// SENDEN an USART0
void usart0Transmit( uint8_t data )
{
    // warten, bis senderegister frei
    while( !( UCSR0A & ( 1 << UDRE0 ) ) );
    // und ab dafür
    UDR0 = data;
}


void usart0PrintStr( char str[] )
{
    while( *str != '\0' )
    {
        usart0Transmit( (uint8_t)(*str) );
        ++str;
    }
}
