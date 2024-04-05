/*!
 * @file main.c
 * @brief LDC Click example
 *
 * # Description
 * This example showcases the ability of the device to detect 
 * metal objects. It configures a device for reading data from 
 * channel 0, checks if ID's are OK and reads data when interrupting 
 * is asserted and logs result.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of communication modules (I2C, UART) and 
 * additional pins. Then configures the device for reading data from 
 * channel 0, and checks if device ID's are correctly read, and
 * read the currently set divider.
 *
 * ## Application Task
 * Checks if interrupt pin is asserted, if so reads data from channel 0.
 * Calculates and returns the frequency of the sensor. If the frequency 
 * is greater than 0, then it calculates the inductance of the sensor. 
 * It will log error and error values if it occurred.
 * 
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ldc.h"
#include "math.h"

static ldc_t ldc;
static log_t logger;

uint16_t divider;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ldc_cfg_t ldc_cfg;  /**< Click config object. */

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
    ldc_cfg_setup( &ldc_cfg );
    LDC_MAP_MIKROBUS( ldc_cfg, MIKROBUS_1 );
    err_t init_flag = ldc_init( &ldc, &ldc_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    if ( ldc_default_cfg ( &ldc ) < 0 )
    {
        log_error( &logger, " Default configuration. " );
        for ( ; ; );
    }
    
    uint16_t temp_data = 0;
    ldc_generic_read( &ldc, LDC_REG_MANUFACTURER_ID, &temp_data );
    log_printf( &logger, "> Manufacturer ID: 0x%.4X\r\n", temp_data );
    if ( LDC_MANUFACTURER_ID != temp_data )
    {
        log_error( &logger, " Manufacturer ID. " );
        for ( ; ; );
    }
    
    ldc_generic_read( &ldc, LDC_REG_DEVICE_ID, &temp_data );
    log_printf( &logger, "> Device ID 0x%.4X\r\n", temp_data );
    if ( LDC_DEVICE_ID != temp_data )
    {
        log_error( &logger, " Device ID. " );
        for ( ; ; );
    }
    
    ldc_generic_read( &ldc, LDC_REG_CLOCK_DIVIDERS_CH0, &temp_data );
    divider = temp_data & 0x3FF;
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( !ldc_get_interrupt( &ldc ) )
    {
        float frequency = 0.0;
        float inductance = 0.0;
        uint16_t status = 0;
        ldc_generic_read( &ldc, LDC_REG_STATUS, &status );
        if ( status & LDC_STATUS_DRDY )
        {
            err_t ret_val = ldc_get_frequency( &ldc, LDC_REG_DATA_CH0, divider, &frequency );
            if ( !ret_val )
            {
                log_printf( &logger, "> Freq[MHz]: %.3f\r\n", frequency );
                if ( frequency > 0 )
                {
                    inductance = ldc_calculate_inductance( frequency );
                }
                log_printf( &logger, "> L[uH]: %.3f\r\n", inductance );
                log_printf( &logger, "> ************************\r\n" );
                
                Delay_ms ( 500 );
            }
            else
            {
                log_error( &logger, " Reading data: %ld", ret_val );
            }
        }
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
