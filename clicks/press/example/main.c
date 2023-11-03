/*!
 * @file main.c
 * @brief PRESS Click example
 *
 * # Description
 * This example demonstrates the use of PRESS Click board™ by reading and displaying
 * the pressure, temperature and Qvar measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * The demo application shows the module working depending on the example mode:
 * - EXAMPLE_MODE_PRESS_TEMP: Reads and displays the Pressure [mBar] and Temperature [degree Celsius] data.
 * - EXAMPLE_MODE_SWIPE_SENSING: Detect a touch or a swipe.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * Additional Functions :
 * - void example_pressure_temperature ( void ) - Example pressure and temperature function.
 * - void example_swipe_sensing ( void ) - Example swipe sensing function.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "press.h"

#define EXAMPLE_MODE_PRESS_TEMP        0
#define EXAMPLE_MODE_SWIPE_SENSING     1
#define EXAMPLE_MODE                   EXAMPLE_MODE_PRESS_TEMP

#define PRESS_THOLD_DETECT             10.0
#define PRESS_THOLD_TOUCH              15.0
#define PRESS_THOLD_SWIPE              30.0

static press_t press;
static log_t logger;
static float temperature, pressure, qvar;

/**
 * @brief PRESS example pressure and temperature function.
 * @details This function reads and displays the Pressure [mBar] and Temperature [degree Celsius] data.
 * @return Nothing.
 * @note None.
 */
void example_pressure_temperature ( void );

/**
 * @brief PRESS example swipe sensing function.
 * @details This function is used to detect a touch, a press, or even a swipe.
 * @return Nothing.
 * @note None.
 */
void example_swipe_sensing ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    press_cfg_t press_cfg;  /**< Click config object. */

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
    press_cfg_setup( &press_cfg );
    PRESS_MAP_MIKROBUS( press_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == press_init( &press, &press_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESS_ERROR == press_default_cfg ( &press ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
    
#if ( EXAMPLE_MODE == EXAMPLE_MODE_PRESS_TEMP )
    log_printf( &logger, " Pressure and Temperature\r\n" );
#elif ( EXAMPLE_MODE == EXAMPLE_MODE_SWIPE_SENSING )
    if ( PRESS_OK == press_config_ah_qvar( &press, PRESS_AH_QVAR_ENABLE ) )
    {
        log_printf( &logger, " Swipe sensing\r\n" );
    }
    else
    {
        log_error( &logger, " Qvar configuration.\r\n" );
        for ( ; ; );
    }
#endif
    log_printf( &logger, " ______________________ \r\n" );
    Delay_ms( 1000 );
}

void application_task ( void ) 
{
#if ( EXAMPLE_MODE == EXAMPLE_MODE_PRESS_TEMP )
    example_pressure_temperature( );
#elif ( EXAMPLE_MODE == EXAMPLE_MODE_SWIPE_SENSING )
    example_swipe_sensing( );
#endif
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

void example_pressure_temperature ( void ) 
{
    if ( PRESS_OK == press_get_measurement_data( &press, &pressure, &temperature ) )
    { 
        log_printf( &logger, " Pressure    : %.2f mBar \r\n", pressure );
        log_printf( &logger, " Temperature : %.2f degC \r\n", temperature );
        log_printf( &logger, " ______________________ \r\n" );
        Delay_ms( 1000 );
    }
}

void example_swipe_sensing ( void ) 
{
    if ( PRESS_OK == press_get_ah_qvar_data( &press, &qvar ) )
    {
        if ( PRESS_THOLD_DETECT < qvar )
        {
            if ( PRESS_THOLD_SWIPE < qvar)
            {
            log_printf( &logger, " Swipe \r\n" );
            }
            else if ( PRESS_THOLD_TOUCH < qvar )
            {
            log_printf( &logger, " Touch \r\n" );
            }
        }
    }
}

// ------------------------------------------------------------------------ END
