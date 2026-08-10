/*!
 * @file main.c
 * @brief USB-C Sink 5 Click example
 *
 * # Description
 * This example demonstrates the use of the USB-C Sink 5 Click board for
 * monitoring USB Type-C sink operation. The application reads VBUS and CC
 * status registers, detects connection changes, and logs information about
 * power availability, current capability, cable orientation, and device attachment.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and USB-C Sink 5 Click driver, and reads device
 * identification information.
 *
 * ## Application Task
 * Continuously monitors VBUS and CC status registers, detects changes,
 * and logs sink state, current level (default, 1.5A, 3.0A), cable orientation,
 * and attachment status.
 *
 * @note
 * If there is no communication, check the USB source connection.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "usbcsink5.h"

#ifndef MIKROBUS_POSITION_USBCSINK5
    #define MIKROBUS_POSITION_USBCSINK5 MIKROBUS_1
#endif

static usbcsink5_t usbcsink5;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcsink5_cfg_t usbcsink5_cfg;  /**< Click config object. */

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
    usbcsink5_cfg_setup( &usbcsink5_cfg );
    USBCSINK5_MAP_MIKROBUS( usbcsink5_cfg, MIKROBUS_POSITION_USBCSINK5 );
    if ( I2C_MASTER_ERROR == usbcsink5_init( &usbcsink5, &usbcsink5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( USBCSINK5_ERROR == usbcsink5_read_info ( &usbcsink5 ) )
    {
        log_error( &logger, " Read info." );
        for ( ; ; );
    }
    log_printf( &logger, " --- Device info ---\r\n" );
    log_printf( &logger, " Vendor ID: 0x%.4X\r\n", usbcsink5.info.vendor_id );
    log_printf( &logger, " Product ID: 0x%.4X\r\n", usbcsink5.info.product_id );
    log_printf( &logger, " USB XID: 0x%.8LX\r\n", usbcsink5.info.usb_xid );
    log_printf( &logger, " FW version: 0x%.2X\r\n", ( uint16_t ) usbcsink5.info.fw_ver );
    log_printf( &logger, " HW version: 0x%.2X\r\n", ( uint16_t ) usbcsink5.info.hw_ver );
    log_printf( &logger, " PD revision: 0x%.2X\r\n", ( uint16_t ) usbcsink5.info.pd_rev );
    log_printf( &logger, " PD version: 0x%.2X\r\n\n", ( uint16_t ) usbcsink5.info.pd_ver );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    err_t error_flag = USBCSINK5_OK;
    static uint8_t vbus_status_old = 0;
    static uint8_t cc_status_old = 0;
    uint8_t vbus_status = 0;
    uint8_t cc_status = 0;

    // Read VBUS and CC status registers
    error_flag = usbcsink5_read_reg_byte ( &usbcsink5, USBCSINK5_REG_VBUS_STATUS, &vbus_status );
    if ( USBCSINK5_OK == error_flag )
    {
        error_flag = usbcsink5_read_reg_byte ( &usbcsink5, USBCSINK5_REG_CC_STATUS, &cc_status );
    }
    else
    {
        log_printf ( &logger, "###############################\r\n" );
        log_printf ( &logger, " No communication, check USB source connection.\r\n" );
        log_printf ( &logger, "*******************************\r\n\n" );
    }

    // Check if any of them are updated
    if ( ( USBCSINK5_OK == error_flag ) && 
         ( ( vbus_status_old != vbus_status ) || ( cc_status_old != cc_status ) ) )
    {
        vbus_status_old = vbus_status;
        cc_status_old = cc_status;
        log_printf ( &logger, "###############################\r\n" );
        if ( USBCSINK5_VBUS_STATUS_SWITCH_CLOSED & vbus_status )
        {
            log_printf ( &logger, " Sinking VBUS to VSNK is enabled\r\n" );
        }
        else
        {
            log_printf ( &logger, " Sinking VBUS to VSNK is disabled\r\n" );
        }
        
        if ( ( USBCSINK5_CC_STATUS_CC2_SINK_DEFAULT == ( cc_status & USBCSINK5_CC_STATUS_CC2_MASK ) ) || 
             ( USBCSINK5_CC_STATUS_CC1_SINK_DEFAULT == ( cc_status & USBCSINK5_CC_STATUS_CC1_MASK ) ) )
        {
            log_printf ( &logger, " Sink default\r\n" );
        }
        else if ( ( USBCSINK5_CC_STATUS_CC2_SINK_POWER_1_5 == ( cc_status & USBCSINK5_CC_STATUS_CC2_MASK ) ) || 
                  ( USBCSINK5_CC_STATUS_CC1_SINK_POWER_1_5 == ( cc_status & USBCSINK5_CC_STATUS_CC1_MASK ) ) )
        {
            log_printf ( &logger, " Sink 1.5A\r\n" );
        }
        else if ( ( USBCSINK5_CC_STATUS_CC2_SINK_POWER_3_0 == ( cc_status & USBCSINK5_CC_STATUS_CC2_MASK ) ) || 
                  ( USBCSINK5_CC_STATUS_CC1_SINK_POWER_3_0 == ( cc_status & USBCSINK5_CC_STATUS_CC1_MASK ) ) )
        {
            log_printf ( &logger, " Sink 3.0A\r\n" );
        }
        else
        {
            log_printf ( &logger, " Both CC1 and CC2 are open\r\n" );
        }
        
        if ( cc_status & USBCSINK5_CC_STATUS_PLUG_ORIENTATION_REVERSED )
        {
            log_printf ( &logger, " Orientation reversed\r\n" );
        }
        else
        {
            log_printf ( &logger, " Orientation normal\r\n" );
        }

        if ( cc_status & USBCSINK5_CC_STATUS_DEVICE_ATTACHED )
        {
            log_printf ( &logger, " Device attached\r\n" );
        }
        else
        {
            log_printf ( &logger, " Device not attached\r\n" );
        }
        log_printf ( &logger, "*******************************\r\n\n" );
    }
    else
    {
        // No updates in status registers, check again in 100ms
        Delay_ms ( 100 );
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
