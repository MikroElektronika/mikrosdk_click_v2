/*!
 * @file main.c
 * @brief Smart Buck 4 Click example
 *
 * # Description
 * This example demonstrates the use of the Smart Buck 4 Click board.
 * This driver provides functions for device configurations 
 * and for the setting of the output voltage.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After initializing the driver, the default configuration is executed 
 * and the outputs are turned off.
 *
 * ## Application Task
 * Changes the output voltage every 5 seconds, starting from 0.6 V to 3.3V/3.7V  
 * depending on the input voltage.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "smartbuck4.h"

static smartbuck4_t smartbuck4;
static log_t logger;

#define SMARTBUCK4_MIN_VOLTAGE      600
#define SMARTBUCK4_STEP             25

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartbuck4_cfg_t smartbuck4_cfg;  /**< Click config object. */

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
    smartbuck4_cfg_setup( &smartbuck4_cfg );
    SMARTBUCK4_MAP_MIKROBUS( smartbuck4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == smartbuck4_init( &smartbuck4, &smartbuck4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTBUCK4_ERROR == smartbuck4_default_cfg ( &smartbuck4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( uint8_t n_cnt = SMARTBUCK4_REGULATOR_B_600_MV; 
          n_cnt <= SMARTBUCK4_REGULATOR_B_3700_MV; 
          n_cnt += SMARTBUCK4_REGULATOR_B_700_MV )
    {
        err_t error_flag = smartbuck4_send_command( &smartbuck4, SMARTBUCK4_REG_R600B_PROGRAM | 
                                                                 SMARTBUCK4_REG_R400B_PROGRAM | 
                                                                 SMARTBUCK4_REG_LDO_MODE, 
                                                                 SMARTBUCK4_ENABLE_REGULATOR | n_cnt );
        if ( SMARTBUCK4_OK == error_flag )
        {
            log_printf( &logger, " Set output to %d mV. \r\n", 
                        ( SMARTBUCK4_MIN_VOLTAGE + n_cnt * SMARTBUCK4_STEP ) );
        }
        else
        {
            log_error( &logger, " Transmission error occurred." );
            smartbuck4_disable_regulators( &smartbuck4 );
            for ( ; ; );
        }
        Delay_ms( 5000 );
    }
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
