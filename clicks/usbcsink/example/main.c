/*!
 * @file main.c
 * @brief USBCSink Click example
 *
 * # Description
 * This is an example which demonstrates the use of USB-C Sink Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - I2C,
 * set hw reset, set PDO2 profile and current value for PDO2 1.5A,
 * upload new data and reset device to write NVM settings to the STUSB450,
 * also write log.
 *
 * ## Application Task
 * USB-C Sink Click board can be used to read the Power Data Objects (PDO) 
 * highest priority profile:
 * PDO1 :  5V,
 * PDO2 : 12V,
 * PDO3 : 20V.
 * All data logs write on USB uart changes for every 5 sec.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "usbcsink.h"

static usbcsink_t usbcsink;
static log_t logger;

uint8_t sel_profile;
float demo_data;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcsink_cfg_t usbcsink_cfg;  /**< Click config object. */

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
    usbcsink_cfg_setup( &usbcsink_cfg );
    USBCSINK_MAP_MIKROBUS( usbcsink_cfg, MIKROBUS_1 );
    err_t init_flag = usbcsink_init( &usbcsink, &usbcsink_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    usbcsink_hw_reset( &usbcsink );
    Delay_ms( 1000 );
    
    usbcsink_set_pdo_num( USBCSINK_SET_PDO_2 );
    usbcsink_set_current( USBCSINK_SET_PDO_2, 1.5 );
    
    sel_profile = usbcsink_get_pdo_num( );
    log_printf( &logger , "- - - - - - - - - - - - \r\n" );
    log_printf( &logger , "   Setting PDO ~ PDO%d \r\n", ( uint16_t ) sel_profile );
    log_printf( &logger , "- - - - - - - - - - - - \r\n" );
    
    usbcsink_upload_new_data( &usbcsink, USBCSINK_UPLOAD_NEW_DATA_VAL );
    Delay_ms( 1000 );
    
    usbcsink_hw_reset( &usbcsink );
    Delay_ms( 1000 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    usbcsink_load_data( &usbcsink );

    log_printf( &logger , "     New Parameters     \r\n" );
    log_printf( &logger , "------------------------\r\n" );
    
    sel_profile = usbcsink_get_pdo_num( );
    
    log_printf( &logger , "    PDO Number ~ PDO%d\r\n", ( uint16_t ) sel_profile );
    log_printf( &logger , "- - - - - - - - - - - - \r\n" );

    demo_data = usbcsink_get_voltage( sel_profile );
    log_printf( &logger , " Voltage : %.2f V\r\n", demo_data );

    demo_data = usbcsink_get_current( sel_profile );
    log_printf( &logger , " Current :  %.2f A\r\n", demo_data );

    log_printf( &logger , "------------------------\r\n" );
    Delay_ms( 5000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
