/*!
 * @file main.c
 * @brief UltraLowPress Click example
 *
 * # Description
 * This application reads the serial number of the sensor. If there were 
 * no errors it continues reading temperature and pressure data from the sensor.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes host communication(UART and I2C). Reads devices serial number and logs it.
 *
 * ## Application Task
 * Checks if data is available. When it's available it reads the temperature 
 * and pressure data from the sensor and logs it.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ultralowpress.h"

static ultralowpress_t ultralowpress;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ultralowpress_cfg_t ultralowpress_cfg;  /**< Click config object. */

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
    ultralowpress_cfg_setup( &ultralowpress_cfg );
    ULTRALOWPRESS_MAP_MIKROBUS( ultralowpress_cfg, MIKROBUS_1 );
    err_t init_flag = ultralowpress_init( &ultralowpress, &ultralowpress_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    //Serial number of sensor read
    uint16_t temp_read = 0;
    uint32_t serial_read = 0;
    init_flag = ultralowpress_generic_read( &ultralowpress, ULTRALOWPRESS_REG_SERIAL_NUM_H, &temp_read );
    serial_read = temp_read;
    serial_read <<= 16;
    init_flag |= ultralowpress_generic_read( &ultralowpress, ULTRALOWPRESS_REG_SERIAL_NUM_L, &temp_read );
    serial_read |= temp_read;
    
    if ( init_flag < 0 )
    {
        log_error( &logger, " Read" );
        for ( ; ; );
    }
    else
    {
        log_printf( &logger, " > Serial number: 0x%.8LX\r\n", serial_read );
    }
    
    Delay_ms( 1000 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( ultralowpress_ready_to_read( &ultralowpress ) )
    {
        ultralowpress_clear_status( &ultralowpress );
        float temp = ultralowpress_get_temp( &ultralowpress );
        float press = ultralowpress_get_press( &ultralowpress );
        log_printf( &logger, " > Temperature[ C ]: %.2f\r\n > Pressure[ Pa ]: %.2f\r\n", temp, press );
    }
    Delay_ms( 100 );
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
