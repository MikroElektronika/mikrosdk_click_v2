/*!
 * \file 
 * \brief OPTO Click example
 * 
 * # Description
 * This application checks the state of selected inputs and prints it.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables GPIO and also starts write log.
 * 
 * ## Application Task  
 * This example demonstrates the use of OPTO Click board by performing
 * the check procedure for selected outputs and displays the results on USART terminal.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "opto.h"

// ------------------------------------------------------------------ VARIABLES

static opto_t opto;
static log_t logger;
uint8_t sel_output;
uint8_t check_output;
uint8_t cnt;
uint8_t tmp;
// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void opto_set_logger( uint8_t sel_out1, uint8_t sel_out2, uint8_t sel_out3, uint8_t sel_out4 )
{
    if ( sel_out1 > 1 )
    {
        sel_out1 = 1;
    }
    if ( sel_out2 > 1 )
    {
        sel_out2 = 1;
    }
    if ( sel_out3 > 1 )
    {
        sel_out3 = 1;
    }
    if ( sel_out4 > 1 )
    {
        sel_out4 = 1;
    }

    sel_output = 0;
    sel_output |= sel_out1;
    sel_output |= sel_out2 << 1;
    sel_output |= sel_out3 << 2;
    sel_output |= sel_out4 << 3;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    opto_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    opto_cfg_setup( &cfg );
    OPTO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    opto_init( &opto, &cfg );
    opto_set_logger(1,1,1,1);
}

void application_task ( void )
{
    tmp = 1;

    for( cnt = 0; cnt < 4; cnt++ )
    {
        switch( sel_output & tmp )
        {
            case 0x01 :
            {
                check_output = opto_check_out1( &opto );

                if( check_output == 0 )
                {
                    log_printf( &logger, "OUT1 is low\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT1 is high\r\n" );
                }
            break;
            }
            case 0x02 :
            {
                check_output = opto_check_out2( &opto );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT2 is low\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT2 is high\r\n" );
                }
            break;
            }
            case 0x04 :
            {
                check_output = opto_check_out3( &opto );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT3 is low\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT3 is high\r\n" );
                }
            break;
            }
            case 0x08 :
            {
                check_output = opto_check_out4( &opto );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT4 is low\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT4 is high\r\n" );
                }
            break;
            }
            default :
            {
            break;
            }
        }

        tmp <<= 1;
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
