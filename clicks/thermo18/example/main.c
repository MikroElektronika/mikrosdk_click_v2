/*!
 * @file main.c
 * @brief Thermo18 Click example
 *
 * # Description
 * The example application showcases ability of device
 * to read temperature and detect and assert interrupt
 * on undertemperature or overtemperature thresholds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of communication modules and interrupt pin.
 * Reads device ID to check comunication. Then resets device,
 * and sets undertemperature and overtemperature thresholds
 * on 24 and 30 degrees Celsius. In the end enables OneShot
 * temperature conversion.
 *
 * ## Application Task
 * Checks status to see if the temperature conversion is finished.
 * When it's finished reads and logs calculated temperature data.
 * Then checks if status is asserted for threshold detection, and
 * logs if detected. In the end re-enables OneShot conversion.
 *
 * @author Luka FIlipovic
 *
 */

#include "board.h"
#include "log.h"
#include "thermo18.h"

static thermo18_t thermo18;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo18_cfg_t thermo18_cfg;  /**< Click config object. */

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
    thermo18_cfg_setup( &thermo18_cfg );
    THERMO18_MAP_MIKROBUS( thermo18_cfg, MIKROBUS_1 );
    err_t init_flag = thermo18_init( &thermo18, &thermo18_cfg );
    if ( I2C_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    uint8_t temp_data = 0;
    thermo18_generic_read( &thermo18, THERMO18_REG_DEVICE_ID, &temp_data );
    log_printf( &logger, " > ID: 0x%.2X\r\n", ( uint16_t )temp_data );

    if ( THERMO18_DEVICE_ID != temp_data )
    {
        log_error( &logger, " Device ID. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    if ( thermo18_default_cfg ( &thermo18 ) )
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    Delay_ms( 2000 );
    //One shot reading
    thermo18_generic_write( &thermo18, THERMO18_REG_CTRL, THERMO18_CONTROL_ONESHOT_ENABLED );

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t status;
    thermo18_generic_read( &thermo18, THERMO18_REG_STATUS, &status );
    //Check if data is ready
    if ( THERMO18_STATUS_DATA_READY == ( status & THERMO18_STATUS_DATA_BUSY ) )
    {
        //Temperature reading
        float temp = 0.0;
        thermo18_read_temperature( &thermo18, &temp );
        log_printf( &logger, " > Temperature[degC]: %.2f\r\n", temp );
        //Check threshold
        if ( 0 != status )
        {
            if ( THERMO18_STATUS_OVERTEMPERATURE == status )
            {
                log_info( &logger, " Overtemperature Threshold detected." );
            }
            else if ( THERMO18_STATUS_UNDERTEMPERATURE == status )
            {
                log_info( &logger, " Undertemperature Threshold detected." );
            }
        }
        //Re-Enable One shot reading
        thermo18_generic_write( &thermo18, THERMO18_REG_CTRL, THERMO18_CONTROL_ONESHOT_ENABLED );
    }

    Delay_ms( 300 );
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
