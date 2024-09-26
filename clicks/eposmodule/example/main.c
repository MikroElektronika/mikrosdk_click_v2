/*!
 * @file main.c
 * @brief EPOS Module Click example
 *
 * # Description
 * This example demonstrates the use of EPOS Module click board by showing
 * the communication between the two click boards connected to PBX system.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, and displays the selected application mode.
 *
 * ## Application Task
 * Dialing application mode:
 * - Resets the device settings and dials the selected number. If a call is answered
 * it starts sending desired messages every couple of seconds with constantly checking
 * if a call is still in progress or it's terminated from the other side.
 * Answering application mode:
 * - Resets the device settings and waits for an incoming call indication, answers the call,
 * and waits for a desired number of messages. The call is terminated after all messages
 * are received successfully.
 *
 * @note
 * We have used a Yeastar S20 VoIP PBX system for the test, where the click boards are
 * connected to ports 1 and 2 configured as FXS extension with numbers 1000 and 1001 (dialer).
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "eposmodule.h"

// Demo aplication selection macros
#define APP_DIALING                 0
#define APP_ANSWERING               1
#define DEMO_APP                    APP_DIALING

// Dialing application settings - a dial number and text to send (must end with CRLF - \r\n)
#define DIAL_NUMBER                 "1000"
#define TEXT_TO_SEND                "MIKROE - EPOS Module click\r\n"

// Answering application settings - a number of successfully received messages before call termination
#define NUM_MESSAGES                5u

static eposmodule_t eposmodule;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eposmodule_cfg_t eposmodule_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    eposmodule_cfg_setup( &eposmodule_cfg );
    EPOSMODULE_MAP_MIKROBUS( eposmodule_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == eposmodule_init( &eposmodule, &eposmodule_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

#if ( DEMO_APP == APP_DIALING )
    log_printf( &logger, " Application Mode: Dialing\r\n" );
#elif ( DEMO_APP == APP_ANSWERING )
    log_printf( &logger, " Application Mode: Answering\r\n" );
#else
    #error "Selected application mode is not supported!"
#endif
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t state = EPOSMODULE_STATE_IDLE;
    uint32_t time_cnt = 0;
    uint8_t msg_cnt = 0;

    eposmodule_handshake_init ( &eposmodule );

#if ( DEMO_APP == APP_DIALING )
    log_printf( &logger, "\r\n Hook OFF\r\n" );
    eposmodule_hook_off ( &eposmodule );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Dial: %s\r\n", ( char * ) DIAL_NUMBER );
    eposmodule_dial ( &eposmodule, DIAL_NUMBER );
    eposmodule.rx_mode &= EPOSMODULE_RX_LEVEL_MASK; // No change in rx level setting
    eposmodule.rx_mode |= ( EPOSMODULE_RX_MODE_DTMF_TONES | EPOSMODULE_RX_TONE_DETECT_CALL_PROG );
    eposmodule_set_receive_mode ( &eposmodule, eposmodule.rx_mode );
    for ( ; ; )
    {
        Delay_ms ( 1 );
        if ( !eposmodule_get_irq_pin ( &eposmodule ) )
        {
            time_cnt = 0;
            state = EPOSMODULE_STATE_IRQ_SET;
        }
        if ( ( EPOSMODULE_STATE_IRQ_SET == state ) && !eposmodule_call_progress ( &eposmodule ) )
        {
            if ( time_cnt < EPOSMODULE_TIMING_BUSY )
            {
                log_printf( &logger, " Busy\r\n" );
                break;
            }
            else if ( time_cnt < EPOSMODULE_TIMING_DISCONNECTED )
            {
                log_printf( &logger, " Disconnected\r\n" );
                break;
            }
            else if ( time_cnt < EPOSMODULE_TIMING_RINGING )
            {
                log_printf( &logger, " Ringing\r\n" );
                state = EPOSMODULE_STATE_RINGING;
            }
        }
        if ( ( EPOSMODULE_STATE_RINGING == state ) && ( time_cnt > EPOSMODULE_TIMING_CALL_PROGRESS ) )
        {
            log_printf( &logger, " Call in progress\r\n" );
            state = EPOSMODULE_STATE_CALL_IN_PROGRESS;
            time_cnt = 0;
        }
        if ( ( EPOSMODULE_STATE_CALL_IN_PROGRESS == state ) && !( time_cnt % EPOSMODULE_TIMING_SEND_MESSAGE ) )
        {
            log_printf( &logger, " Send message %u\r\n", ( uint16_t ) msg_cnt++ );
            eposmodule_send_message ( &eposmodule, TEXT_TO_SEND, strlen ( TEXT_TO_SEND ) );
        }
        if ( time_cnt++ > EPOSMODULE_TIMEOUT_CALL_PROGRESS )
        {
            log_printf( &logger, " Timeout\r\n" );
            break;
        }
    }
    log_printf( &logger, " Hook ON\r\n" );
    eposmodule_hook_on ( &eposmodule );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#elif ( DEMO_APP == APP_ANSWERING )
    uint8_t rx_data = 0;
    uint8_t msg_end_buff[ 2 ] = { 0 };

    log_printf( &logger, "\r\n Waiting for a call...\r\n" );

    while ( !eposmodule_ring_detect ( &eposmodule ) );

    Delay_ms ( 1000 );
    log_printf( &logger, " Hook OFF\r\n" );
    eposmodule_hook_off ( &eposmodule );
    Delay_ms ( 1000 );
    log_printf( &logger, " Waiting for %u messages...\r\n", ( uint16_t ) NUM_MESSAGES );
    eposmodule.rx_mode &= EPOSMODULE_RX_LEVEL_MASK; // No change in rx level setting
    eposmodule.rx_mode |= ( EPOSMODULE_RX_MODE_V23_FSK_1200 | EPOSMODULE_RX_DATA_FORMAT_SS_NO_OVS | 
                            EPOSMODULE_RX_DATA_PARITY_8_NO_PAR );
    eposmodule_set_receive_mode ( &eposmodule, eposmodule.rx_mode );

    for ( ; ; )
    {
        Delay_ms ( 1 );
        if ( !eposmodule_get_irq_pin ( &eposmodule ) )
        {
            if ( EPOSMODULE_STATE_IDLE != state )
            {
                log_printf( &logger, "\r\n Disconnected\r\n" );
                break;
            }
            log_printf( &logger, " Message %u: ", ( uint16_t ) msg_cnt );
            state = EPOSMODULE_STATE_IRQ_SET;
            time_cnt = 0;
        }
        if ( ( EPOSMODULE_STATE_IRQ_SET == state ) && !( time_cnt % EPOSMODULE_TIMING_RX_READY ) )
        {
            if ( eposmodule_unscram_1s_det ( &eposmodule ) && eposmodule_rx_ready ( &eposmodule ) )
            {
                eposmodule_receive_data ( &eposmodule, &rx_data );
                if ( ( ( ' ' <= rx_data ) && ( '~' >= rx_data ) ) || 
                     ( '\r' == rx_data ) || ( '\n' == rx_data ) )
                {
                    log_printf( &logger, "%c", ( char ) rx_data );
                }
                if ( '\r' == rx_data )
                {
                    msg_end_buff[ 0 ] = rx_data;
                }
                else if ( '\n' == rx_data )
                {
                    msg_end_buff[ 1 ] = rx_data;
                }
                else
                {
                    msg_end_buff[ 0 ] = 0;
                    msg_end_buff[ 1 ] = 0;
                }
            }
            if ( ( '\r' == msg_end_buff[ 0 ] ) && ( '\n' == msg_end_buff[ 1 ] ) )
            {
                msg_end_buff[ 0 ] = 0;
                msg_end_buff[ 1 ] = 0;
                state = EPOSMODULE_STATE_IDLE;
                if ( NUM_MESSAGES == ++msg_cnt )
                {
                    Delay_ms ( 100 );
                    log_printf( &logger, " Terminate call\r\n" );
                    Delay_ms ( 100 );
                    break;
                }
            }
        }
        if ( time_cnt++ > EPOSMODULE_TIMING_WAIT_FOR_MESSAGE )
        {
            log_printf( &logger, "\r\n Timeout\r\n" );
            break;
        }
    }
    log_printf( &logger, " Hook ON\r\n" );
    eposmodule_hook_on ( &eposmodule );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
