/*!
 * @file main.c
 * @brief USB-C Sink 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of the USB-C Sink 2 Click board™ 
 * by setting DC power requests and control for Type-C connector-equipped devices (TCD).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C and ADC modules and log UART.
 * After driver initialization the app set default settings.
 *
 * ## Application Task
 * In this example, the app configures Power Data Objects (PDO) 
 * highest priority profile and requests power from a standard USB PD source adapter.
 * After connecting the PD source and USB-C Sink 2 Click with the Type-C cable,
 * the app gets the total number of valid PDO's 
 * and switches all PDO configurations every 10 seconds.
 * When the PD source accepts the request, the app displays information about 
 * VOUT Voltage [mV] and Current [mA] and the temperature [degree Celsius] of the USB-C connector.
 *
 * @note
 * FAULT LED flickering notified of the system status:
 *  - Charging: Breathing light (2 sec dimming), 1 cycle is 4 sec.
 *  - Fully charged: Continuously lit Charging current < 500mA.
 *  - Mismatch: 1s flicker Voltage or power mismatch. Non-PD power source, 1 cycle is 2sec.
 *  - Fault: 300ms flicker OVP, 1 cycle is 600ms.
 * 
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "usbcsink2.h"

static usbcsink2_t usbcsink2;   /**< USB-C Sink 2 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcsink2_cfg_t usbcsink2_cfg;  /**< Click config object. */

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
    usbcsink2_cfg_setup( &usbcsink2_cfg );
    USBCSINK2_MAP_MIKROBUS( usbcsink2_cfg, MIKROBUS_1 );
    err_t init_flag = usbcsink2_init( &usbcsink2, &usbcsink2_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( USBCSINK2_ERROR == usbcsink2_default_cfg ( &usbcsink2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    static float voltage_mv = 0, current_ma = 0;
    static uint8_t temperature = 0;
    for ( uint8_t pdo_num = 0; pdo_num < usbcsink2.number_of_valid_pdo; pdo_num++ )
    {
        usbcsink2.pdo_data[ pdo_num * 4 + 3 ] = ( pdo_num + 1 ) << 4;
        if ( USBCSINK2_OK == usbcsink2_write_rdo( &usbcsink2, &usbcsink2.pdo_data[ pdo_num * 4 ] ) )
        {
            log_printf( &logger, " --- PDO[ %d ] ---\r\n", ( uint16_t ) pdo_num );
        }
        
        if ( USBCSINK2_OK == usbcsink2_wait_rdo_req_success( &usbcsink2 ) )
        {
            if ( USBCSINK2_OK == usbcsink2_get_pdo_voltage( &usbcsink2, &voltage_mv ) )
            {
                log_printf( &logger, " Voltage : %.2f mV\r\n", voltage_mv );
            }
            
            if ( USBCSINK2_OK == usbcsink2_get_pdo_current( &usbcsink2, &current_ma ) )
            {
                log_printf( &logger, " Current : %.2f mA\r\n", current_ma );
            }
            
            if ( USBCSINK2_OK == usbcsink2_get_temperature( &usbcsink2, &temperature ) )
            {
                log_printf( &logger, " Temperature : %d C\r\n", ( uint16_t ) temperature );
            }
            log_printf( &logger, "---------------------------\r\n" );
            // 10 seconds delay
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
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
