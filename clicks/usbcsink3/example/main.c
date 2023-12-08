/*!
 * @file main.c
 * @brief USB-C Sink 3 Click example
 *
 * # Description
 * This example demonstrates the use of USB-C Sink 3 Click board™ 
 * by setting DC power requests and control for Type-C connector-equipped devices (TCD).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI, I2C and ADC modules and log UART.
 * After driver initialization the app set default settings:
 * Voltage Selection: 5 [V] and Power: 15.0 [W].
 *
 * ## Application Task
 * In this example, the app configures Power Data Objects (PDO) 
 * highest priority profile and requests power from a standard USB PD source adapter.
 * It interprets power input requirements (voltage/current and maximum power) from the TCD.
 * The example uses two configurations: 
 *  - Voltage 5 [V] and Power 15.0 [W]
 *  - Voltage 9 [V] and Power 18.0 [W]
 * Results are being sent to the Usart Terminal where you can track their changes.
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
#include "usbcsink3.h"

static usbcsink3_t usbcsink3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcsink3_cfg_t usbcsink3_cfg;  /**< Click config object. */

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
    usbcsink3_cfg_setup( &usbcsink3_cfg );
    USBCSINK3_MAP_MIKROBUS( usbcsink3_cfg, MIKROBUS_1 );
    err_t init_flag = usbcsink3_init( &usbcsink3, &usbcsink3_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    
    if ( USBCSINK3_ERROR == usbcsink3_default_cfg ( &usbcsink3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ------------------------\r\n" );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    static float voltage = 0.0;
    if ( ( USBCSINK3_OK == usbcsink3_set_voltage( &usbcsink3, USBCSINK3_VTG_SEL_5V ) ) &&
         ( USBCSINK3_OK == usbcsink3_set_power( &usbcsink3, USBCSINK3_PWR_SEL_15W ) ) )
    {
        log_printf( &logger, " Output:\r\nVoltage: 5.0 [V]\r\nPower: 15.0 [W]\r\n" );
        log_printf( &logger, " - - - - - -  - - - - - -\r\n" );
        Delay_ms( 1000 );
        usbcsink3_get_vbus ( &usbcsink3, &voltage );
        log_printf( &logger, " VBUS : %.1f [V]\r\n", voltage );
        log_printf( &logger, " ------------------------\r\n" );
        Delay_ms( 5000 );
    }
    
    if ( ( USBCSINK3_OK == usbcsink3_set_voltage( &usbcsink3, USBCSINK3_VTG_SEL_9V ) ) &&
         ( USBCSINK3_OK == usbcsink3_set_power( &usbcsink3, USBCSINK3_PWR_SEL_18W ) ) )
    {
        log_printf( &logger, " Output:\r\nVoltage: 9.0 [V]\r\nPower: 18.0 [W]\r\n" );
        log_printf( &logger, " - - - - - -  - - - - - -\r\n" );
        Delay_ms( 1000 );
        usbcsink3_get_vbus ( &usbcsink3, &voltage );
        log_printf( &logger, " VBUS : %.1f [V]\r\n", voltage );
        log_printf( &logger, " ------------------------\r\n" );
        Delay_ms( 5000 );
    }
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
