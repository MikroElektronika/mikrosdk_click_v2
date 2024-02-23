/*!
 * @file main.c
 * @brief UT-S 7-SEG B 2 Click example
 *
 * # Description
 * This example demonstrates the use of the UT-S 7-SEG B 2 Click board
 * by writing and displaying the desired numbers on the screen.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 * After driver initialization, the app executes a default configuration.
 *
 * ## Application Task
 * The demo application draws numbers, in hexadecimal format, 
 * from 0h to FFFh on the top segment group and from FFFh to 0h on the bottom segment group.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Mikroe Team
 *
 */

#include "board.h"
#include "log.h"
#include "uts7segb2.h"

static uts7segb2_t uts7segb2;
static log_t logger;
static uts7segb2_number_cfg_t number;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uts7segb2_cfg_t uts7segb2_cfg;  /**< Click config object. */

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
    uts7segb2_cfg_setup( &uts7segb2_cfg );
    UTS7SEGB2_MAP_MIKROBUS( uts7segb2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == uts7segb2_init( &uts7segb2, &uts7segb2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( UTS7SEGB2_ERROR == uts7segb2_default_cfg ( &uts7segb2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    number.brightness_top = UTS7SEGB2_BRIGHTNESS_DEFAULT;
    number.brightness_bottom = UTS7SEGB2_BRIGHTNESS_DEFAULT;
    number.base = UTS7SEGB2_BASE_NUM_SYS_HEXADECIMAL;
    number.dot_bit_mask = UTS7SEGB2_TOP_SEG_NO_DOT | UTS7SEGB2_BOTTOM_SEG_NO_DOT;
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void )
{
    for ( uint16_t num_cnt = 0; num_cnt <= UTS7SEGB2_HEXADECIMAL_NUM_MAX; num_cnt++ )
    {
        number.num_top = num_cnt;
        number.num_bottom = UTS7SEGB2_HEXADECIMAL_NUM_MAX - num_cnt;
        if ( UTS7SEGB2_OK == uts7segb2_display_number( &uts7segb2, number ) )
        {
            log_printf( &logger, " %.3X\r\n", number.num_top );
            log_printf( &logger, " %.3X\r\n\n", number.num_bottom );
            Delay_ms( 100 );
        }
    }
    log_printf( &logger, " --------------\r\n\n" );
    Delay_ms( 1000 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
