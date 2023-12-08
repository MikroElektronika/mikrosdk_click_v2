/*!
 * @file main.c
 * @brief USB-C Power Click example
 *
 * # Description
 * This example demonstrates the use of the USB-C Power Click board™
 * by configuring the PD controller to attempt to become a Power Source.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C module, log UART, and additional pins.
 * After the driver init, the app executes a default configuration,
 * depending on PD Device Mode, the app performs the patch bundle update tasks
 * for loading a patch bundle in burst mode to the PD controller.
 *
 * ## Application Task
 * The application display status information about 
 * the PD controller data role and power of the connection.
 * Results are being sent to the UART Terminal, where you can track their changes.
 * 
 * ## Additional Function
 * - static void usbcpower_display_status ( void )
 * - static void usbcpower_display_pwr_status ( void )
 *
 * @note
 * For the advanced configuration, use the TPS25750 Application Customization Tool:
 * https://dev.ti.com/gallery/search/TPS25750_Application_Customization_Tool
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "usbcpower.h"

static usbcpower_t usbcpower;
static log_t logger;
static uint32_t response;
static usbcpower_status_t status;
static usbcpower_pwr_status_t pwr_status;

/**
 * @brief USB-C Power display status function.
 * @details This function display status information.
 * @return Nothing.
 * @note None.
 */
static void usbcpower_display_status ( void );

/**
 * @brief USB-C Power display PWR status function.
 * @details This function display power of the connection status information.
 * @return Nothing.
 * @note None.
 */
static void usbcpower_display_pwr_status ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcpower_cfg_t usbcpower_cfg;  /**< Click config object. */

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
    usbcpower_cfg_setup( &usbcpower_cfg );
    USBCPOWER_MAP_MIKROBUS( usbcpower_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == usbcpower_init( &usbcpower, &usbcpower_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( USBCPOWER_ERROR == usbcpower_default_cfg ( &usbcpower ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    usbcpower_set_patch_mode( &usbcpower, &response );
    if ( USBCPOWER_RSP_OK != response )
    {
        log_error( &logger, " Go to Patch Mode." );
        for ( ; ; );
    }
    
    uint8_t device_mode[ 6 ] = { 0 };
    usbcpower_get_device_mode( &usbcpower, &device_mode );
    log_printf( &logger, " PD Device Mode: %s\r\n", &device_mode[ 1 ] );
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    if ( USBCPOWER_OK == usbcpower_get_status( &usbcpower, &status ) )
    {
        if ( USBCPOWER_OK == usbcpower_get_pwr_status( &usbcpower, &pwr_status ) )
        {
            usbcpower_display_status( );
            log_printf( &logger, "- - - - - - - - - - - - - - -\r\n" );
            usbcpower_display_pwr_status( );
            log_printf( &logger, "-----------------------------\r\n" );
        }
    }
    Delay_ms( 3000 );
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

static void usbcpower_display_status ( void )
{
    if ( status.plug_present )
    {
        log_printf( &logger, " A plug is connected.\r\n" );
    }
    else
    {
        log_printf( &logger, " No plug is connected\r\n" );
    }
    
    if ( USBCPOWER_STATUS_NO_CONNECTION == status.conn_state )
    {
        log_printf( &logger, " No connection.\r\n" );
    }
    else if ( USBCPOWER_STATUS_PORT_DISABLED == status.conn_state )
    {
        log_printf( &logger, " Port is disabled.\r\n" );
    }
    else if ( USBCPOWER_STATUS_AUDIO_CONNECTION == status.conn_state )
    {
        log_printf( &logger, " Audio connection (Ra/Ra).\r\n" );
    }
    else if ( USBCPOWER_STATUS_DEBUG_CONNECTION == status.conn_state )
    {
        log_printf( &logger, " Debug connection (Rd/Rd).\r\n" );
    }
    else if ( USBCPOWER_STATUS_NO_CONNECTION_Ra == status.conn_state )
    {
        log_printf( &logger, " No connection, Ra detected (Ra but no Rd).\r\n" );
    }
    else if ( USBCPOWER_STATUS_RESERVED == status.conn_state )
    {
        log_printf( &logger, " Reserved (may be used for Rp/Rp Debug connection).\r\n" );
    }
    else if ( USBCPOWER_STATUS_CONNECT_NO_Ra == status.conn_state )
    {
        log_printf( &logger, " Connection present, no Ra detected.\r\n" );
    }
    else
    {
        log_printf( &logger, " Connection present, Ra detected.\r\n" );
    }
    
    if ( status.plug_orientation )
    {
        log_printf( &logger, " Upside-down orientation.\r\n" );
    }
    else
    {
        log_printf( &logger, " Upside-up orientation.\r\n" );
    }
    
    if ( status.port_role )
    {
        log_printf( &logger, " PD Controller is Source.\r\n" );
    }
    else
    {
        log_printf( &logger, " PD Controller is in the Sink role.\r\n" );
    }
}

static void usbcpower_display_pwr_status ( void )
{
    if ( pwr_status.pwr_conn )
    {
        log_printf( &logger, " Connection present.\r\n" );
    }
    else
    {
        log_printf( &logger, " No connection.\r\n" );
    }
    
    if ( USBCPOWER_PWR_STATUS_USB == pwr_status.type_c_current )
    {
        log_printf( &logger, " USB Default Current.\r\n" );
    }
    else if ( USBCPOWER_PWR_STATUS_TYPE_C_1_5A  == pwr_status.type_c_current )
    {
        log_printf( &logger, " Type-C Current: 1.5 A\r\n" );
    }
    else if ( USBCPOWER_PWR_STATUS_TYPE_C_3_0A  == pwr_status.type_c_current )
    {
        log_printf( &logger, " Type-C Current: 3.0 A\r\n" );
    }
    else
    {
        log_printf( &logger, "Explicit PD contract sets current.\r\n" );
    }
    
    if ( USBCPOWER_PWR_STATUS_CHG_ADV_DISABLE == pwr_status.charger_advertise )
    {
        log_printf( &logger, " Charger advertise disabled or not run.\r\n" );
    }
    else if ( USBCPOWER_PWR_STATUS_CHG_ADV_PROCESS == pwr_status.charger_advertise )
    {
        log_printf( &logger, " Charger advertisement in process.\r\n" );
    }
    else if ( USBCPOWER_PWR_STATUS_CHG_ADV_COMPLETE == pwr_status.charger_advertise )
    {
        log_printf( &logger, "Charger advertisement complete.\r\n" );
    }
    else
    {
        log_printf( &logger, "Reserved.\r\n" );
    }
}

// ------------------------------------------------------------------------ END
