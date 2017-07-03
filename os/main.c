#include <openautos.h>

const uint8_t TASKS_TOTAL = 7;

const TaskType task_rx = 1;
TASK(task_rx);
const TaskType task_farol = 2;
TASK(task_farol);
const TaskType task_seta = 3;
TASK(task_seta);
const TaskType task_volante = 4;
TASK(task_volante);
const TaskType task_velocidade = 5;
TASK(task_velocidade);
const TaskType task_sentido = 6;
TASK(task_sentido);
const TaskType task_init = 7;
TASK(task_init);

const ResourceType res_a = 1;

#define _XTAL_FREQ 64000000

void TASK_FUNC_IDLE() {
	while( TRUE ) {
#ifdef _XTAL_FREQ
		__delay_us(10);
#endif
		Schedule();
	}
}

void InitializeTasks() {
	InitializeTaskData( g_idle, TASK_ID_IDLE, 0, READY, TASK_FUNC_IDLE );
	InitializeTaskData( &g_tasks[0], task_rx, 3, SUSPENDED, TASK_FUNC_task_rx );
	InitializeTaskData( &g_tasks[1], task_farol, 2, SUSPENDED, TASK_FUNC_task_farol );
	InitializeTaskData( &g_tasks[2], task_seta, 2, SUSPENDED, TASK_FUNC_task_seta );
	InitializeTaskData( &g_tasks[3], task_volante, 2, SUSPENDED, TASK_FUNC_task_volante );
	InitializeTaskData( &g_tasks[4], task_velocidade, 2, SUSPENDED, TASK_FUNC_task_velocidade );
	InitializeTaskData( &g_tasks[5], task_sentido, 2, SUSPENDED, TASK_FUNC_task_sentido );
	InitializeTaskData( &g_tasks[6], task_init, 254, READY, TASK_FUNC_task_init );
	GroupTasksSamePriority();
}

ResourceDataType g_res[1];
void InititializeResources() {
	AddResourceDataToResources( &g_res[0], res_a, 255 );
}

asm("GLOBAL _TASK_FUNC_IDLE, _TASK_FUNC_task_rx, _TASK_FUNC_task_farol, _TASK_FUNC_task_seta, _TASK_FUNC_task_volante, _TASK_FUNC_task_velocidade, _TASK_FUNC_task_sentido, _TASK_FUNC_task_init" );
#include <stdint.h>
#include <xc.h>

typedef void (*callback_isr_t)(void);

///////////////////////////////////////////////////////////////////////////////
/// USART
///////////////////////////////////////////////////////////////////////////////
// TODO talvez trocar os buffers internos por ponteiros para buffers externos.
#define TX_BUFFER_MAX_SIZE 11
#define RX_BUFFER_MAX_SIZE 11

typedef enum {
    USART_SYNC_MODE_ASYNCHRONOUS = LOW,
    USART_SYNC_MODE_SYNCHRONOUS  = HIGH
} usart_sync_mode_t;

typedef enum {
    USART_9BIT_MODE_NOT_IMPLEMENTED = LOW
} usart_9bit_mode_t;

// Definição dos Baud Rates mais usados.
const uint32_t USART_BAUD_RATE_300    =    300ul;
const uint32_t USART_BAUD_RATE_484    =    484ul;
const uint32_t USART_BAUD_RATE_1200   =   1200ul;
const uint32_t USART_BAUD_RATE_2400   =   2400ul;
const uint32_t USART_BAUD_RATE_9600   =   9600ul;
const uint32_t USART_BAUD_RATE_10417  =  10417ul;
const uint32_t USART_BAUD_RATE_19200  =  19200ul;
const uint32_t USART_BAUD_RATE_57600  =  57600ul;
const uint32_t USART_BAUD_RATE_115200 = 115200ul;

/**
 * Inicia a comunicação por EUSART.
 * 
 * @param usart_sync_mode Modo de sincronização desejado. Por hora, só tem Assincrono.
 * @param baud_rate Velocidade da transferencia. Existem constantes definidas com os valores mais comuns.
 * @todo Implementar modo sincrono!
 */
void usart_initialize( usart_sync_mode_t usart_sync_mode, uint32_t baud_rate );

/**
 * Transmite uma mensagem, utilizando interrupções.
 * @param message String que será enviada.
 * @param usart_callback_transmit_done Função que será chamada após o ultimo byte ser transmitido.
 */
void usart_transmite_interrupt_write_message( char * message, callback_isr_t usart_callback_transmit_done );
/**
 * @remark Não precisa chamar esta função. Ela é chamada automaticamente pela função tratadora de interrupções.
 * Função que trata a interrupção de envio de mensagem.
 * @todo Transformar em uma macro depois.
 */
void usart_transmite_interrupt_isr();

void usart_transmite_lock_write_byte( uint8_t data );

/**
 * Transmite uma string (mas trava a tarefa).
 * @param message String que será transmitida.
 */
void usart_transmite_lock_write_message( char * message );

/**
 * Recebe um byte (mas trava a tarefa).
 * @return O valor recebido do RX.
 */
uint8_t usart_receive_lock_read_byte();

/**
 * Recebe uma string inteira (mas trava a tarefa). A string deve terminar em '\r'.
 * @param buffer O buffer onde a mensagem será salva.
 * @param size O tamanho do buffer.
 * @return A quantidade de caracteres recebida.
 */
uint8_t usart_receive_lock_read_message( char * buffer, uint8_t size );

/**
 * Recebe uma string inteira, utilizando interrupções. A string deve terminar em '\r'.
 * @param usart_callback_receive_done função que será chamada quando a mensagem for totalmente recebida.
 */
void usart_receive_interrupt_read_message( callback_isr_t usart_callback_receive_done );

/**
 * Recebe um unico byte, utilizando interrupções.
 * @param usart_callback_receive_done função que será chamada quando o byte for recebido.
 */
void usart_receive_interrupt_read_byte( callback_isr_t usart_callback_receive_done );

/**
 * @remark Não precisa chamar esta função. Ela é chamada automaticamente pela função tratadora de interrupções.
 * Função que trata a interrupção de recepção de mensagem.
 * @todo Transformar em uma macro depois.
 */
void usart_receive_interrupt_isr();

/**
 * Recupera o ponteiro para a mensagem recebida ao final da interrupção.
 */
char* usart_receive_interrupt_get_message();

/**Recupera o caracter lido da interrupção*/
char usart_receive_interrupt_get_byte();

#include "string.h"

/**Buffer para envio de mensagens*/
char _tx_buffer[TX_BUFFER_MAX_SIZE];
/**Iterador do buffer de envio*/
char* _tx_buffer_iterator = NULL;
/**Função disparda quando a mensagem for totalmente enviada no modo por interrupção*/
callback_isr_t _tx_isr_done_callback = NULL;

/**Buffer para recebimento de mensagens*/
char _rx_buffer[RX_BUFFER_MAX_SIZE];
/**Iterador do buffer de recebimento*/
char* _rx_buffer_iterator = NULL;
/**Tamanho da mensagem recebida pelo buffer*/
uint8_t _rx_buffer_message_size;
/**Função disparda quando uma mensagem for totalmente recebida (terminada em 'r')*/
callback_isr_t _rx_isr_done_callback = NULL;
/**Define se o modo do rx por interrupção será por string ou caracter*/
const uint8_t _RX_ISR_MODE_STRING = 0;
const uint8_t _RX_ISR_MODE_CHAR = 1;
uint8_t _rx_isr_mode = 0;

void usart_initialize( usart_sync_mode_t usart_sync_mode, uint32_t baud_rate ) {
    // Ativa o envio (Transmit Enable)
    TXSTA1bits.TXEN = HIGH;
    // Setting the SPEN bit of the RCSTA register enables the EUSART and automatically configures the TX/CK I/O pin as an output.
    RCSTA1bits.SPEN = HIGH;
    // Synchronization Mode
    TXSTA1bits.SYNC = usart_sync_mode;
            
    // Ativa a recepção (Receive Enable)
    RCSTA1bits.CREN = HIGH;
    // Segundo o manual, o pino de entrada deve ser setado manualmente.
    TRISCbits.TRISC6 = OUTPUT; // TX
    TRISCbits.TRISC7 = INPUT;  // RX
    
    // TODO: Implementar o protocolo pra 9 bits, se necessário.
    TXSTA1bits.TX9 = USART_9BIT_MODE_NOT_IMPLEMENTED;
    RCSTA1bits.RX9 = USART_9BIT_MODE_NOT_IMPLEMENTED;            
        
    // -------------------------------------------------------------------------
    // The default state of this bit is ?0? which selects high true transmit 
    // idle and data bits. Setting the SCKP bit to ?1? will invert the transmit
    // data resulting in low true idle and data bits.
    // -------------------------------------------------------------------------
    // Basicamente, se tiver em modo Assincrono:
    //   SCKP(LOW)  => Faz transmissao com sinal 1
    //   SCKP(HIGH) => Faz transmissao com sinal 0 (invertido)
    if( usart_sync_mode == USART_SYNC_MODE_ASYNCHRONOUS ) {
        BAUDCON1bits.SCKP = LOW;
    }
  
    SPBRG1 = 64000000ul / ( 9600ul * 64ul ) - 1ul;
//    // Faz o calculo do Baud Rate!
//    // Primeiro, determina a frequencia
//    uint32_t fosc = 64000000;    
//    // Fatores que decidem a formula para calculo do Baud Rate
//    uint8_t baud_switch = SYNC << 2 | BRG16 << 1 | BRGH << 0;
//    // Calibra o valor de SPBRG (X na formula do Baud Rate, pág. 348) para o Baud Rate desejado.
//    switch( baud_switch ) {
//        case 0b000: SPBRG1 = ( fosc / ( 64ul * baud_rate ) ) - 1ul; break;
//        case 0b001:
//        case 0b010: SPBRG = ( fosc / ( 16ul * baud_rate ) ) - 1ul; break;
//        default: // Para as demais combinações, a formula é:
//            SPBRG = ( fosc / ( 4ul * baud_rate ) ) - 1ul; break;
//    }
}

/**
 * @remark Função privada (Não acessivel de fora - não é pra cagar nela).
 * 
 * Função que copia a mensagem para um buffer interno E cria um iterador (ponteiro) para percorre ela.
 */
void usart_transmite_set_message( char * message ) {
    // Copia a mensagem para o buffer, para que ela fique disponivel durante todo o processo.
    strcpy( _tx_buffer, message );
    // Inicia o iterador que ira enviar caracter por caracter para o inicio da mensagem.
    _tx_buffer_iterator = _tx_buffer;
}

void usart_transmite_interrupt_write_message( char * message, callback_isr_t usart_callback_transmit_done ) {
    // Copia a mensagem e prepara o iterador
    usart_transmite_set_message(message);
    // seta a função que será chamada no final da transmissão
    _tx_isr_done_callback = usart_callback_transmit_done;
    // Ativa as interrupções de periféricos externos.
    INTCONbits.PEIE = HIGH;
    // Ativa o uso de interrupções para transmissão
    // É para disparar uma interrupção imediatamente.
    PIE1bits.TXIE = HIGH;    
}

void usart_transmite_interrupt_isr() {
    // Envia o proximo caracter, se ele existir.
    if( *_tx_buffer_iterator ) {        
        TXREG = *_tx_buffer_iterator;        
        _tx_buffer_iterator++;
    // Do contrário, encerra o envio e dispara o callback.
    } else {
        // Se o canal de envio ainda não havia sido encerrado E existe uma função de callback...
        if( PIE1bits.TXIE && _tx_isr_done_callback ) {
            // Faz a chamada da função
            _tx_isr_done_callback();
        }
        // Desativa interrupções para transmissão
        PIE1bits.TXIE = LOW;
    }
}

/**
 * @remark Função privada (Não acessivel de fora - não é pra cagar nela).
 *
 * Transmite um byte (mas trava a tarefa).
 *  
 * @param data Byte que será transmitido.
 */
void usart_transmite_lock_write_byte( uint8_t data ) {        
    // <TXIF (Interrupt Flag Bit for Transmiting) é controlado por hardware>
    // Aguarda a a transmissão anterior encerrar ...
    while( !PIR1bits.TXIF ) {
        NOP();
    }
    // ... para então escrever o byte.
	TXREG1 = data;
}

void usart_transmite_lock_write_message( char * message ) {
    // Habilita o canal de transmissao e prepara o iterador.
    usart_transmite_set_message( message );
    // Enquanto tiver mensagem para escrever...
    while( *_tx_buffer_iterator ) {
        // Escreve um byte ...
        usart_transmite_lock_write_byte( *_tx_buffer_iterator );
        // ...  e avança um byte por vez
        _tx_buffer_iterator++;
    }
    // Finalmente, desabilita o canal de transmissao
    PIE1bits.TXIE = LOW;
}

uint8_t usart_receive_lock_read_byte() {
 	/*// Verifica se ocorreu algum erro (Frame/Overflow)
    if( RCSTAbits.FERR || RCSTAbits.OERR ) {
        //TODO fazer um tratamento de erro
		// Reinicia o receiver, para poder resetar as flags de erro.
        RCSTAbits.CREN = LOW;
		RCSTAbits.CREN = HIGH;        
	}*/
    
    // <RCIF (Interrupt Flag bit for Receiving) é controlador por hardware>
    // Aguarda a flag ir para high (indicando que recebeu 8+ bytes) ...
    while( !PIR1bits.RCIF ) {
        NOP();
    }
    // ... para então fazer a leitura do byte
    return RCREG1;
}

uint8_t usart_receive_lock_read_message( char * buffer, uint8_t size ) {
    // Cursor que irá navegar o buffer
    char* cursor = buffer;
    // Conta a quantidade de caratereres recebida pela mensagem
    uint8_t i;
    // Itera pelo buffer, salvando nele os bytes recebidos
    for( i = 0; i < size; i++ ) {
        // Recebe uma letra do RX
        uint8_t letter = usart_receive_lock_read_byte();
        // Verifica se é final do buffer. Estamos usando o carriage return, mas ideal era ver pelo caracter NULO mesmo...
        if( letter == '\r' ) {
            // Arrumamos a string para final NULO antes de retornar.
            *cursor = '\0';
            break;
        // Se não for a letra de termino de string
        } else {
            // salva a letra no buffer e posiciona o cursor na proxima posição.
            *cursor = letter;
            cursor++;
        }
    }
    // Retorna a quantidade de caracters lido (incluindo o nulo)
    return i;
}

void _usart_receive_interrupt_read_message( callback_isr_t usart_callback_receive_done ) {
    // Inicia as variaveis de interrupção para RX.
    _rx_buffer_iterator = _rx_buffer;
    _rx_buffer_message_size = 0;
    _rx_isr_done_callback = usart_callback_receive_done;
    // Ativa as interrupções de periféricos externos.
    INTCONbits.PEIE = HIGH;
    // Ativa o uso de interrupções para transmissão
    // É para disparar uma interrupção imediatamente.
    PIE1bits.RCIE = HIGH;
}

void usart_receive_interrupt_read_message( callback_isr_t usart_callback_receive_done ) {
    _rx_isr_mode = _RX_ISR_MODE_STRING;
    _usart_receive_interrupt_read_message( usart_callback_receive_done );
}

void usart_receive_interrupt_read_byte( callback_isr_t usart_callback_receive_done ) {
    _rx_isr_mode = _RX_ISR_MODE_CHAR;
    _usart_receive_interrupt_read_message( usart_callback_receive_done );
}

void usart_receive_interrupt_isr() {
    // Recebeu um byte inteiro, e agora armazena ele no buffer.
    *_rx_buffer_iterator = RCREG1;    
    // Aumenta o tamanho recebido no buffer.
    _rx_buffer_message_size++;
    
    if( _rx_isr_mode == _RX_ISR_MODE_STRING ) {
        if( *_rx_buffer_iterator == '\r' ) {
            *_rx_buffer_iterator = '\0';
            // Se o canal de recepção ainda não havia sido encerrado E existe uma função de callback...
            if( PIE1bits.RCIE && _rx_isr_done_callback ) {
                // Faz a chamada da função
                _rx_isr_done_callback();
            }
            // Desativa interrupções para recepção
            PIE1bits.RCIE = LOW;
        } else if( _rx_buffer_message_size == (RX_BUFFER_MAX_SIZE-1) ) {
            //TODO deu merda. Veio mais caracteres do que o buffer comportava.
            PIE1bits.RCIE = LOW;
        } else {
            // Move o cursor para a proxima posição
            _rx_buffer_iterator++;
        }
    } else {
        // Faz a chamada da função
        _rx_isr_done_callback();
    }
}

char* usart_receive_interrupt_get_message() {
    return _rx_buffer;
}

char usart_receive_interrupt_get_byte() {
    return (*_rx_buffer);
}

//////////////////////////////////////////////////////////////////////////USART

///////////////////////////////////////////////////////////////////////////////
/// TIMER1
///////////////////////////////////////////////////////////////////////////////
/**
 * Reseta o timer1 para a quantidade de atrasos especificada e liga-o.
 * @param a_delay Quantidade de ciclos de atraso.
 */
void timer1_reset( uint16_t a_delay );

/**
 * Inicializa o timer1, mas não o liga.
 * @param timer1_callback Função que será chamada a cada estouro de timer.
 */
void timer1_initialize( callback_isr_t timer1_callback );

/**
 * Rotina invocada quando ocorre uma interrupção.
 */
void timer1_isr();

void timer1_reset( uint16_t a_delay ) {
    // Prepara a quantidade de ciclos para atrasar
    uint16_t l_timer = 65535u - a_delay;
    // Seta no timer a quantidade de ciclos de atraso
    TMR1H = l_timer >> 8;
    TMR1L = l_timer;
    // Ativa o timer1 para iniciar a contagem
    T1CONbits.TMR1ON = 1;
}

static callback_isr_t _timer1_callback;
asm("GLOBAL __timer1_callback");
void timer1_initialize( callback_isr_t timer1_callback ) {
    T1CONbits.TMR1CS = 0b00;  // Timer1 Clock Source = FOSC/4
    T1CONbits.T1CKPS = 0b11;  // Timer1 Input Clock Prescale = 1:8
    T1CONbits.SOSCEN = 0b0;   // SOSC Oscillator Enable = Disabled
    T1CONbits.nT1SYNC = 0b00; // Timer1 External Clock Input Synchronization = This bit is ignored. Timer1 uses the internal clock when TMR1CS<1:0> = 0x.
    T1CONbits.RD16 = 0b1;     // 16-Bit Read/Write Mode Enable = Enables register read/write of Timer1 in one 16-bit operation
    
    T1GCONbits.TMR1GE = 0b0;  // Timer1 Gate Enable = Timer1 counts regardless of Timer1 gate function
    
    timer1_reset( 0xFFFF );   // Resets the timer
    _timer1_callback = timer1_callback;
    
    PIR1bits.TMR1IF = 0;      // Timer1 Interrupt Flag = Off
    PIE1bits.TMR1IE = 1;      // Timer1 Interrupt Enable = True
    
    INTCONbits.PEIE = TRUE;
    
    T1CONbits.TMR1ON = 0;     // Timer1 On = Start Disabled
}

void timer1_isr() {
    T1CONbits.TMR1ON = 0;
    if( _timer1_callback != NULL ) {
        _timer1_callback();
    }
    // Clear Timer1 Interruption Flag
    PIR1bits.TMR1IF = 0;
}

/////////////////////////////////////////////////////////////////////////TIMER1

///////////////////////////////////////////////////////////////////////////////
/// TIMER3
///////////////////////////////////////////////////////////////////////////////
void timer3_reset( uint16_t a_delay ) {
    // Prepara a quantidade de ciclos para atrasar
    uint16_t l_timer = 65535u - a_delay;
    // Seta no timer a quantidade de ciclos de atraso
    WRITETIMER3( l_timer );
    // Ativa o timer3 para iniciar a contagem
    T3CONbits.TMR3ON = 1;
}

static callback_isr_t _timer3_callback;
asm("GLOBAL __timer3_callback");
void timer3_initialize( callback_isr_t timer3_callback ) {
    T3CONbits.TMR3CS = 0b00;  // Timer3 Clock Source = FOSC/4
    T3CONbits.T3CKPS = 0b11;  // Timer3 Input Clock Prescale = 1:8
    T3CONbits.SOSCEN = 0b0;   // SOSC Oscillator Enable = Disabled
    T3CONbits.nT3SYNC = 0b00; // Timer3 External Clock Input Synchronization = This bit is ignored. Timer3 uses the internal clock when TMR3CS<1:0> = 0x.
    T3CONbits.RD16 = 0b1;     // 16-Bit Read/Write Mode Enable = Enables register read/write of Timer3 in one 16-bit operation
    
    T3GCONbits.TMR3GE = 0b0;  // Timer3 Gate Enable = Timer3 counts regardless of Timer3 gate function
    
    timer3_reset( 0xFFFF );   // Resets the timer
    _timer3_callback = timer3_callback;
    
    PIR2bits.TMR3IF = 0;      // Timer3 Interrupt Flag = Off
    PIE2bits.TMR3IE = 1;      // Timer3 Interrupt Enable = True
    
    INTCONbits.PEIE = 1;
    
    T3CONbits.TMR3ON = 0;     // Timer3 On = Start Disabled
}

void timer3_isr() {
    T3CONbits.TMR3ON = 0;
    if( _timer3_callback != NULL ) {
        _timer3_callback();
    }
    // Clear Timer3 Interruption Flag
    PIR2bits.TMR3IF = 0;
}
/////////////////////////////////////////////////////////////////////////TIMER1

///////////////////////////////////////////////////////////////////////////////
/// PWM
///////////////////////////////////////////////////////////////////////////////
void pwm0_initialize() {
    PR2 = 64000000ul / ( 64000ul * 4ul * 1ul ) - 1; // 249 >> 1111 1001
    T2CONbits.T2CKPS = 0b00;
    T2CONbits.TMR2ON = 1;
}

void pwm5_initialize() {
    pwm0_initialize();
    TRISBbits.TRISB5 = 0;
    // CCPx Module Mode Select bits
    CCP5CONbits.CCP5M = 0b1100; // PWM mode
    //-- CCPTMRS: CCP TIMER SELECT REGISTER --//
    // CCP5 Timer Selection bit
    CCPTMRSbits.C5TSEL = 0b0; // CCP5 is based off of TMR1/TMR2
}

void pwm5_set_duty( uint16_t a_duty ) {
    CCPR5Lbits.CCPR5L = ((a_duty >> 2 ) & 0xFF);
    CCP5CONbits.DC5B = (a_duty & 0b11);
}

void pwm2_initialize() {
    pwm0_initialize();
    TRISCbits.TRISC2 = 0;
    // CCPx Module Mode Select bits
    CCP2CONbits.CCP2M = 0b1100; // PWM mode
    //-- CCPTMRS: CCP TIMER SELECT REGISTER --//
    // CCP2 Timer Selection bit
    CCPTMRSbits.C2TSEL = 0b0; // CCP2 is based off of TMR1/TMR2
}

void pwm2_set_duty( uint16_t a_duty ) {
    CCPR2Lbits.CCPR2L = ((a_duty >> 2 ) & 0xFF);
    CCP2CONbits.DC2B = (a_duty & 0b11);
}
////////////////////////////////////////////////////////////////////////////PWM

///////////////////////////////////////////////////////////////////////////////
/// RELAMPAGO MARQUINHOS
///////////////////////////////////////////////////////////////////////////////
typedef struct relampago_s {
	uint8_t comando;
	uint8_t freio_re;
	uint8_t volante_cmd;
    uint16_t volante;
    uint8_t velocidade_cmd;
    uint16_t velocidade;
} relampago_t;

typedef relampago_t* relampago_ptr_t;

void rm_init( relampago_ptr_t a_rc );

/**
 * Retorna um valor para o servomotor que controla o marquinhos
 * @param a_rc Ponteiro para o marquinhos
 * @return Valor entre 1 e 2 ms
 */
void rm_set_servo_volante( relampago_ptr_t a_rc );
/**
 * Retorna um valor para o tempo de alta do pwm do motor do marquinhos
 * @param a_rc Ponteiro para o marquinhos
 * @return Valor entre 50 e 0
 */
void rm_set_pwm_velocidade( relampago_ptr_t a_rc );

#define LPE (0b00000001)
#define LPD (0b00000010)
#define LFP (0b00000100)
#define LFM (0b00001000)
#define LFR (0b00010000)

static const uint8_t _CMD_VOLANTE[] = { 'B','L','R','G','I','H','J','S','F' };
static const uint8_t _CMD_VELOCIDADE[] = { '0', '1','2','3','4','5','6','7','8','9','q' };

void rm_init( relampago_ptr_t a_rc ) {
    a_rc->comando = 0;
    a_rc->freio_re = 0;
    a_rc->volante_cmd = 'B';
    rm_set_servo_volante( a_rc ); // a_rc->volante = 3000 + VOLANTE_OFFSET;
	a_rc->velocidade_cmd = '0';
    rm_set_pwm_velocidade( a_rc ); // a_rc->velocidade = 0;
}

#define VOLANTE_OFFSET 0
void rm_set_servo_volante( relampago_ptr_t a_marquinhos ) {    
    switch( a_marquinhos->volante_cmd ) {
        case 'G': a_marquinhos->volante = 3666 + VOLANTE_OFFSET; break; // Left Forward >> Esquerda 100% >> 1.0ms
        case 'L': a_marquinhos->volante = 3444 + VOLANTE_OFFSET; break; // Left         >> Esquerda  66%
        case 'H': a_marquinhos->volante = 3222 + VOLANTE_OFFSET; break; // Left Back    >> Esquerda  33%
        case 'B': a_marquinhos->volante = 3000 + VOLANTE_OFFSET; break; // Back         >> Neutro     0% >> 1.5ms
        case 'J': a_marquinhos->volante = 2778 + VOLANTE_OFFSET; break; // Right        >> Direita   33%
        case 'R': a_marquinhos->volante = 2556 + VOLANTE_OFFSET; break; // Right        >> Direita   66%
        case 'I': a_marquinhos->volante = 2334 + VOLANTE_OFFSET; break; // Right        >> Direita  100% >> 2.0ms
        default : a_marquinhos->volante = 3000 + VOLANTE_OFFSET;
    }
    
}

void rm_set_pwm_velocidade( relampago_ptr_t a_marquinhos ) {    
    switch( a_marquinhos->velocidade_cmd ) {
        case 'q': a_marquinhos->velocidade = 250 << 2; break; // Throttle 100% (Full Throttle :D)
        case '9': a_marquinhos->velocidade = 225 << 2; break; // Throttle  90%
        case '8': a_marquinhos->velocidade = 200 << 2; break; // Throttle  80%
        case '7': a_marquinhos->velocidade = 175 << 2; break; // Throttle  70%
        case '6': a_marquinhos->velocidade = 150 << 2; break; // Throttle  60%
        case '5': a_marquinhos->velocidade = 125 << 2; break; // Throttle  50%
        case '4': a_marquinhos->velocidade = 100 << 2; break; // Throttle  40%
        case '3': a_marquinhos->velocidade =  75 << 2; break; // Throttle  30%
        case '2': a_marquinhos->velocidade =  50 << 2; break; // Throttle  20%
        case '1': a_marquinhos->velocidade =  25 << 2; break; // Throttle  10%
        case '0': a_marquinhos->velocidade =   0 << 2; break; // Throttle   0%
		default: a_marquinhos->velocidade = 0;
    }    
}
///////////////////////////////////////////////////////////RELAMPAGO MARQUINHOS

// #define _XTAL_FREQ 64000000

#define EVENT_RX			(0b00000001)
#define EVENT_VOLANTE		(0b00000001)
#define EVENT_VELOCIDADE	(0b00000001)
#define EVENT_PE_ON			(0b00001000)
#define EVENT_PE_OFF		(0b00000100)
#define EVENT_PD_ON			(0b00000010)
#define EVENT_PD_OFF		(0b00000001)
#define EVENT_FAR_MILHA_ON	(0b00001000)
#define EVENT_FAR_MILHA_OFF	(0b00000100)
#define EVENT_FAR_ON		(0b00000010)
#define EVENT_FAR_OFF		(0b00000001)
#define EVENT_MOV_F			(0b00000010)
#define EVENT_MOV_R			(0b00000001)

relampago_t marquinhos;

void isr_extra() {
	// USART RX
    if( PIE1bits.RCIE == HIGH && PIR1bits.RCIF == HIGH ) {
        usart_receive_interrupt_isr();
    }
    // TIMER1
    if( PIE1bits.TMR1IE && PIR1bits.TMR1IF ) {
        timer1_isr();
    }
    // TIMER3
    if( PIE2bits.TMR3IE && PIR2bits.TMR3IF ) {
        timer3_isr();
    }
}

void isr_rx_callback() {
	marquinhos.comando = usart_receive_interrupt_get_byte();	
	SetEvent( task_rx, EVENT_RX );
}

#define VOLANTE_SERVO LATBbits.LB4
#define VOLANTE_LAZY_CYCLE 40000ul

uint16_t _volante_duty_cycle = 0ul;
uint16_t _volante_lazy_cycle = VOLANTE_LAZY_CYCLE;
uint8_t _volante_duty = 1;
void isr_timer1_callback() {
    // Duty
    if( _volante_duty ) {
        timer1_reset( _volante_duty_cycle );
        VOLANTE_SERVO = HIGH;
    // Full
    } else {
        timer1_reset( _volante_lazy_cycle );
        VOLANTE_SERVO = LOW;
    }
    _volante_duty = !_volante_duty;
}

#define MODO_PISCA_ESQ (0b00000010)
#define MODO_PISCA_DIR (0b00000001)
#define MODO_PISCA_ALL (0b00000011)

#define LED_FREIO		LATBbits.LATB1
#define LED_PISCA_ESQ	LATBbits.LATB7
#define LED_PISCA_DIR	LATBbits.LATB6
#define LED_FAROL		LATBbits.LATB3
#define LED_FAROL_MILHA	LATBbits.LATB2

#define LED_FREIO_READ			PORTBbits.RB1
#define LED_PISCA_ESQ_READ		PORTBbits.RB7
#define LED_PISCA_DIR_READ		PORTBbits.RB6
#define LED_FAROL_READ			PORTBbits.RB3
#define LED_FAROL_MILHA_READ 	PORTBbits.RB2

static uint8_t _timer3_counter = 0;
static uint8_t _timer3_pisca_modo = 0;
void isr_timer3_callback() {
    _timer3_counter++;
    if( _timer3_counter >= 20 ) {
        LATBbits.LATB2 = !PORTBbits.RB2;
        _timer3_counter = 0;

        if( _timer3_pisca_modo == MODO_PISCA_ESQ ) {
        	LED_PISCA_ESQ = !LED_PISCA_ESQ_READ;
        } else
        if( _timer3_pisca_modo == MODO_PISCA_DIR ) {
        	LED_PISCA_DIR = !LED_PISCA_DIR_READ;
        } else
        if( _timer3_pisca_modo == MODO_PISCA_ALL ) {        	
        	LED_PISCA_DIR = !LED_PISCA_ESQ_READ;
        	LED_PISCA_ESQ = !LED_PISCA_ESQ_READ;
        } else {
        }
    }
    timer3_reset( 50000ul );
}

void setup_portas() {
    // Saidas
    TRISB = 0b00000000;
    TRISCbits.TRISC2 = OUTPUT;        
        
    TRISAbits.TRISA0 = INPUT;
    TRISAbits.TRISA1 = INPUT;    
    TRISAbits.TRISA2 = INPUT;
    
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
}

TASK( task_init ) {
	_isr_extra = isr_extra;
    
    setup_portas();
    
    usart_initialize( USART_SYNC_MODE_ASYNCHRONOUS, USART_BAUD_RATE_9600 );
    usart_receive_interrupt_read_byte( isr_rx_callback );
    // 40000 ciclos = 20 ms
    timer1_initialize( isr_timer1_callback );
    timer1_reset( 0xFFFF );

    timer3_initialize( isr_timer3_callback );
    timer3_reset( 50000ul );       
    _timer3_counter = 0;
    
    pwm5_initialize(); // Velocidade -> Frente
    pwm5_set_duty(0);    
    pwm2_initialize(); // Velocidade -> Re    
    pwm2_set_duty(0);

    rm_init( &marquinhos );

    _volante_duty_cycle = marquinhos.volante;
	_volante_lazy_cycle = VOLANTE_LAZY_CYCLE - marquinhos.volante;

	ActivateTask( task_rx );
	ActivateTask( task_farol );
	ActivateTask( task_seta );
	ActivateTask( task_volante );
	ActivateTask( task_velocidade );
	ActivateTask( task_sentido );

	TerminateTask();
}

TASK( task_rx ) {
	while( TRUE ) {
		WaitEvent( EVENT_RX );
		ClearEvent( EVENT_RX );

		// Discarte de comandos
	    if( marquinhos.comando == 'S' || 
	    	marquinhos.comando == 'F' || 
	    	marquinhos.comando == 'D' ) { 
	    	continue; 
		}
	    
	    // Comandos do Volante
	    for( uint8_t i = 0; i < sizeof(_CMD_VOLANTE); i++ ) {
	        if( marquinhos.comando == _CMD_VOLANTE[i] ) {
	        	marquinhos.volante_cmd = marquinhos.comando;
	        	SetEvent( task_volante, EVENT_VOLANTE );
	            continue;
	        }
	    }

	    // Comandos de Velocidade
	    for( uint8_t i = 0; i < sizeof(_CMD_VELOCIDADE); i++ ) {
	        if( marquinhos.comando == _CMD_VELOCIDADE[i] ) {
	        	marquinhos.velocidade_cmd = marquinhos.comando;
	            SetEvent( task_velocidade, EVENT_VELOCIDADE );
	            continue;
	        }
	    }

		// LEDs
		if( marquinhos.comando == 'W' ) { SetEvent( task_seta   , EVENT_PE_ON   ); } else
		if( marquinhos.comando == 'w' ) { SetEvent( task_seta   , EVENT_PE_OFF  ); } else
	    if( marquinhos.comando == 'U' ) { SetEvent( task_seta   , EVENT_PD_ON   ); } else
	    if( marquinhos.comando == 'u' ) { SetEvent( task_seta   , EVENT_PD_OFF  ); } else
	    if( marquinhos.comando == 'V' ) { SetEvent( task_farol  , EVENT_FAR_ON  ); } else
	    if( marquinhos.comando == 'v' ) { SetEvent( task_farol  , EVENT_FAR_OFF ); } else
	    if( marquinhos.comando == 'X' ) { SetEvent( task_sentido, EVENT_MOV_R   ); } else
	    if( marquinhos.comando == 'x' ) { SetEvent( task_sentido, EVENT_MOV_F   ); }
	}
}

TASK( task_farol ) {
	while( TRUE ) {
		WaitEvent( EVENT_FAR_MILHA_ON | EVENT_FAR_MILHA_OFF | EVENT_FAR_ON | EVENT_FAR_OFF );
		EventMaskType l_event;
		GetEvent( task_farol, &l_event );
		if( l_event & EVENT_FAR_MILHA_ON ) {
			ClearEvent( EVENT_FAR_MILHA_ON );
			LED_FAROL_MILHA = TRUE;
		} else
		if( l_event & EVENT_FAR_MILHA_OFF ) {
			ClearEvent( EVENT_FAR_MILHA_OFF );
			LED_FAROL_MILHA = FALSE;
		} else
		if( l_event & EVENT_FAR_ON ) {
			ClearEvent( EVENT_FAR_ON );
			LED_FAROL = TRUE;
		} else
		if( l_event & EVENT_FAR_OFF ) {
			ClearEvent( EVENT_FAR_OFF );
			LED_FAROL = FALSE;
		}
	}
}

TASK( task_seta ) {
	while( TRUE ) {
		WaitEvent( EVENT_PE_ON | EVENT_PE_OFF | EVENT_PD_ON | EVENT_PD_OFF );
		EventMaskType l_event;
		GetEvent( task_seta, &l_event );
		if( l_event & EVENT_PE_ON ) {
			ClearEvent( EVENT_PE_ON );
			LED_PISCA_ESQ = TRUE;
			_timer3_pisca_modo |= MODO_PISCA_ESQ;
		} else
		if( l_event & EVENT_PE_OFF ) {
			ClearEvent( EVENT_PE_OFF );
			LED_PISCA_ESQ = FALSE;
			_timer3_pisca_modo &= ~MODO_PISCA_ESQ;
		} else
		if( l_event & EVENT_PD_ON ) {
			ClearEvent( EVENT_PD_ON );
			LED_PISCA_DIR = TRUE;
			_timer3_pisca_modo |= MODO_PISCA_DIR;
		} else
		if( l_event & EVENT_PD_OFF ) {
			ClearEvent( EVENT_PD_OFF );
			LED_PISCA_DIR = FALSE;
			_timer3_pisca_modo &= ~MODO_PISCA_DIR;
		}
	}
}

TASK( task_volante ) {
	while( TRUE ) {
		WaitEvent( EVENT_VOLANTE );
		ClearEvent( EVENT_VOLANTE );
		rm_set_servo_volante( &marquinhos );
		_volante_duty_cycle = marquinhos.volante;
    	_volante_lazy_cycle = VOLANTE_LAZY_CYCLE - _volante_duty_cycle;   
	}
}

TASK( task_velocidade ) {
	while( TRUE ) {
		WaitEvent( EVENT_VELOCIDADE );
		ClearEvent( EVENT_VELOCIDADE );
		rm_set_pwm_velocidade( &marquinhos );
		pwm5_set_duty( marquinhos.freio_re ? 0 : marquinhos.velocidade ); // Frente
		pwm2_set_duty( marquinhos.freio_re ? marquinhos.velocidade : 0 ); // Ré
	}
}

TASK( task_sentido ) {
	while( TRUE ) {
		WaitEvent( EVENT_MOV_F | EVENT_MOV_R );
		EventMaskType l_event;
		GetEvent( task_sentido, &l_event );
		// Frente
		if( l_event & EVENT_MOV_F ) {
			ClearEvent( EVENT_MOV_F );
			marquinhos.freio_re = FALSE;	
		} else
		// Re
		if( l_event & EVENT_MOV_R ) {
			ClearEvent( EVENT_MOV_R );
			marquinhos.freio_re = TRUE;
		}
		LED_FREIO = marquinhos.freio_re;
		pwm5_set_duty( marquinhos.freio_re ? 0 : marquinhos.velocidade ); // Frente
		pwm2_set_duty( marquinhos.freio_re ? marquinhos.velocidade : 0 ); // Ré
	}
}
void main(void) {
	InitializeTasks();
	InititializeResources();

	StartOS( 0 );

	while( 1 ) { NOP(); }

	return;
}
