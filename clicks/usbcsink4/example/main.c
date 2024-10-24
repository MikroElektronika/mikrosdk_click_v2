/*!
 * @file main.c
 * @brief USB-C Sink 4 Click example
 *
 * # Description
 * This example demonstrates the use of a USB-C Sink 4 Click board 
 * by setting DC power requests and control for Type-C connector-equipped devices (TCD).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of the I2C module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * The demo app displays the reports of the Type-C port, active legacy charging mode status, 
 * and live voltage measurements on the VBUS supply for the specified port.
 *
 * ## Additional Function
 * - static void usbcsink4_display_type_c_status ( void )
 * - static void usbcsink4_display_chrg_mode ( void )
 * - static void usbcsink4_display_bus_voltage ( void )
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "usbcsink4.h"

static usbcsink4_t usbcsink4;
static log_t logger;

/**
 * @brief USB-C Sink 4 display Type-C status.
 * @details This function displays the reports of the status of the Type-C port.
 * @return Nothing.
 */
static void usbcsink4_display_type_c_status ( void );

/**
 * @brief USB-C Sink 4 display charging mode status.
 * @details This function displays the reports of the status 
 * of the active legacy charging mode.
 * @return Nothing.
 */
static void usbcsink4_display_chrg_mode ( void );

/**
 * @brief USB-C Sink 4 display VBUS voltage.
 * @details This function displays the live voltage 
 * on the VBUS supply for the specified port.
 * @return Nothing.
 */
static void usbcsink4_display_bus_voltage ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcsink4_cfg_t usbcsink4_cfg;  /**< Click config object. */

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
    usbcsink4_cfg_setup( &usbcsink4_cfg );
    USBCSINK4_MAP_MIKROBUS( usbcsink4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == usbcsink4_init( &usbcsink4, &usbcsink4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( USBCSINK4_ERROR == usbcsink4_default_cfg ( &usbcsink4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ------------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    usbcsink4_display_type_c_status( );
    Delay_ms ( 100 );

    usbcsink4_display_chrg_mode( );
    Delay_ms ( 100 );

    usbcsink4_display_bus_voltage( );
    Delay_ms ( 1000 );
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

static void usbcsink4_display_type_c_status ( void ) 
{
    usbcsink4_type_c_status_t type_c_status;
    if ( USBCSINK4_OK == usbcsink4_get_type_c_status( &usbcsink4, &type_c_status ) )
    {
        log_printf( &logger, "  >> Port Partner Connection Status:" );
        if ( USBCSINK4_TYPE_C_ST_PORT_DISCONN == type_c_status.port_par_cxn )
        {
            log_printf( &logger, " Port is not connected to partner.\r\n" );
        }
        else
        {
            log_printf( &logger, " Port is connected to partner.\r\n" );
        }
        log_printf( &logger, " >> CC Polarity:" );
        if ( USBCSINK4_TYPE_C_ST_CC_1 == type_c_status.cc_pol )
        {
            log_printf( &logger, " CC1\r\n" );
        }
        else
        {
            log_printf( &logger, " CC2\r\n" );
        }
        log_printf( &logger, " >> Attached device type:" );
        if ( USBCSINK4_TYPE_C_ST_ATT_NTH == type_c_status.att_dev_type )
        {
            log_printf( &logger, " Nothing attached\r\n" );
        }
        else if ( USBCSINK4_TYPE_C_ST_ATT_SRC == type_c_status.att_dev_type )
        {
            log_printf( &logger, " Source attached\r\n" );
        }
        else if ( USBCSINK4_TYPE_C_ST_ATT_DEBUG == type_c_status.att_dev_type )
        {
            log_printf( &logger, " Debug Accessory attached\r\n" );
        }
        else
        {
            log_printf( &logger, " Unknown\r\n" );
        }
        log_printf( &logger, " >> Type-C Current Level:" );
        if ( USBCSINK4_TYPE_C_ST_CURR_0_9A == type_c_status.curr_lvl )
        {
            log_printf( &logger, " 900mA\r\n" );
        }
        else if ( USBCSINK4_TYPE_C_ST_CURR_1A == type_c_status.curr_lvl )
        {
            log_printf( &logger, " 1.5A\r\n" );
        }
        else if ( USBCSINK4_TYPE_C_ST_CURR_3A == type_c_status.curr_lvl )
        {
            log_printf( &logger, " 3A\r\n" );
        }
        else
        {
            log_printf( &logger, " Unknown\r\n" );
        }
    }
}

static void usbcsink4_display_chrg_mode ( void ) 
{
    uint8_t chrg_mode = 0;
    if ( USBCSINK4_OK == usbcsink4_get_chrg_mode( &usbcsink4, &chrg_mode ) )
    {
        log_printf( &logger, " >> Charging Mode Status:" );
        if ( USBCSINK4_CHG_MODE_STATUS_NO_LGC == chrg_mode )
        {
            log_printf( &logger, " No legacy charging mode\r\n" );
        }
        if ( USBCSINK4_CHG_MODE_STATUS_BC1_2DCP_CDC == chrg_mode )
        {
            log_printf( &logger, " BC 1.2 DCP/CDP charging\r\n" );
        }
        if ( USBCSINK4_CHG_MODE_STATUS_QC2_1 == chrg_mode )
        {
            log_printf( &logger, " QC2.0 charging\r\n" );
        }
        if ( USBCSINK4_CHG_MODE_STATUS_AFC == chrg_mode )
        {
            log_printf( &logger, " AFC charging\r\n" );
        }
        if ( USBCSINK4_CHG_MODE_STATUS_APPLE == chrg_mode )
        {
            log_printf( &logger, " Apple charging\r\n" );
        }
    }
}

static void usbcsink4_display_bus_voltage ( void ) 
{
    float vtg = 0;
    if ( USBCSINK4_OK == usbcsink4_get_bus_voltage( &usbcsink4, &vtg ) )
    {
        log_printf( &logger, " >> VBUS Voltage: %.1f V \r\n", vtg );
    }
    log_printf( &logger, " ------------------------\r\n" );
}

// ------------------------------------------------------------------------ END
