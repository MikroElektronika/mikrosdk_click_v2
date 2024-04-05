/*!
 * @file main.c
 * @brief GainAMP3 Click example
 *
 * # Description
 * This example demonstrates the use of GainAMP 3 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which 
 * verifies the communication and sets active the input channel 1.
 *
 * ## Application Task
 * Changes the amplifier gain level every 3 seconds and displays the gain value on the USB UART.
 *
 * @note
 * VDDH should be within the range from +5V to +30V.
 * VSSH should be within the range from -5V to -30V.
 * Input channels should be within the range from GND to VCC selected by the VCC_SEL SMD jumpers.
 * Gain * Input voltage must not exceed VCC voltage.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "gainamp3.h"

static gainamp3_t gainamp3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    gainamp3_cfg_t gainamp3_cfg;  /**< Click config object. */

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

    gainamp3_cfg_setup( &gainamp3_cfg );
    GAINAMP3_MAP_MIKROBUS( gainamp3_cfg, MIKROBUS_1 );
    err_t init_flag = gainamp3_init( &gainamp3, &gainamp3_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    init_flag = gainamp3_default_cfg ( &gainamp3 );
    if ( GAINAMP3_ERROR == init_flag )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    for ( uint8_t cnt = GAINAMP3_GAIN_1_OVER_16; cnt <= GAINAMP3_GAIN_128; cnt++ )
    {
        gainamp3_set_amplifier_gain ( &gainamp3, cnt );
        log_printf( &logger, " Amplifier gain set to " );
        float gain = ( 1 << cnt ) / 16.0;
        
        if ( gain < 1.0 )
        {
            log_printf( &logger, "1/%u\r\n", ( uint16_t ) ( 1.0 / gain ) );
        }
        else
        {
            log_printf( &logger, "%u\r\n", ( uint16_t ) gain );
        }
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
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
