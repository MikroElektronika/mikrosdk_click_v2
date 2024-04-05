/*!
 * @file main.c
 * @brief BucknBoost Click example
 *
 * # Description
 * This application demonstrates the use of Buck n Boost click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and sets the click default configuration.
 * The default config enables the click board and limits the current of all outputs to 1100mA.
 * It also sets the default voltages of all channels which are the following:
 * OUT1 - 1.8V, OUT2 - 1.1V, OUT3 - 1.8V, OUT4 - 1.05V, OUT5 - 1.25V, OUT6 - 12V 
 *
 * ## Application Task
 * Iterates through the entire range of Buck voltages for Buck 1 output starting from the maximal output.
 * It also checks the Power Good and Overcurrent status.
 * All data is being displayed on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "bucknboost.h"

static bucknboost_t bucknboost;
static log_t logger;


void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bucknboost_cfg_t bucknboost_cfg;  /**< Click config object. */

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

    bucknboost_cfg_setup( &bucknboost_cfg );
    BUCKNBOOST_MAP_MIKROBUS( bucknboost_cfg, MIKROBUS_1 );
    
    err_t init_flag = bucknboost_init( &bucknboost, &bucknboost_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    init_flag = bucknboost_default_cfg ( &bucknboost );
    if ( init_flag == BUCKNBOOST_ERROR ) 
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    bucknboost_status_t status_data;
    
    for ( uint8_t cnt = BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_3300mV; 
          cnt <= BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_800mV; cnt++ )
    {
        err_t error_check = bucknboost_set_buck_out_voltage( &bucknboost, 
                                                             BUCKNBOOST_OUTPUT_CH_1, 
                                                             cnt );
        if ( error_check == BUCKNBOOST_ERROR )
        {
            log_error( &logger, " Setting Buck 1 Output Voltage." );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
        else
        {
            log_printf( &logger, " Buck 1 Output Voltage set to %u mV.\r\n", 3300 - cnt * 50 );
            
            bucknboost_get_status( &bucknboost, &status_data );
            log_printf( &logger, " Power Good status -" );
            if ( status_data.power_good == BUCKNBOOST_PGOOD_ALL_MASK )
            {
                log_printf( &logger, " Valid!\r\n" );
            }
            else
            {
                log_printf( &logger, " Not Valid! - Mask: 0x%.2X\r\n", ( uint16_t ) status_data.power_good );
            }
            
            log_printf( &logger, " Overcurrent status -" );
            if ( status_data.power_good == BUCKNBOOST_PGOOD_ALL_MASK )
            {
                log_printf( &logger, " No Fault!\r\n" );
            }
            else
            {
                log_printf( &logger, " Fault! - Mask: 0x%.2X\r\n", ( uint16_t ) status_data.overcurrent_fault );
            }
            log_printf( &logger, "-----------------------------------\r\n" );
        }
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
