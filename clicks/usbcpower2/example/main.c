/*!
 * @file main.c
 * @brief USB-C Power 2 Click example
 *
 * # Description
 * This example demonstrates the use of the USB-C Power 2 Click board for
 * detecting USB cable attachment and monitoring CC (Configuration Channel)
 * status. The application reads interrupt and CC status registers and logs
 * the interpreted results to the serial terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and USB-C Power 2 Click driver, and applies the
 * default device configuration.
 *
 * ## Application Task
 * Waits for an USB detached/attached interrupt event, then reads and displays
 * cable connection status and CC line status information including VBUS detection,
 * Rp value, port attachment state, and cable polarity.
 *
 * @author Stefan Filipovic
 *
 */
#include "board.h"
#include "log.h"
#include "usbcpower2.h"

#ifndef MIKROBUS_POSITION_USBCPOWER2
    #define MIKROBUS_POSITION_USBCPOWER2 MIKROBUS_1
#endif

static usbcpower2_t usbcpower2;
static log_t logger;

/**
 * @brief USB-C Power 2 display CC status function.
 * @details This function parses the CC status register value and displays it on USB UART.
 * @param[in] cc_status : CC status register value.
 * @return None.
 * @note None.
 */
static void usbcpower2_display_cc_status ( uint8_t cc_status );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcpower2_cfg_t usbcpower2_cfg;  /**< Click config object. */

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
    usbcpower2_cfg_setup( &usbcpower2_cfg );
    USBCPOWER2_MAP_MIKROBUS( usbcpower2_cfg, MIKROBUS_POSITION_USBCPOWER2 );
    if ( I2C_MASTER_ERROR == usbcpower2_init( &usbcpower2, &usbcpower2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( USBCPOWER2_ERROR == usbcpower2_default_cfg ( &usbcpower2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t status = 0;
    if ( !usbcpower2_get_int_pin ( &usbcpower2 ) )
    {
        if ( USBCPOWER2_OK == usbcpower2_read_reg ( &usbcpower2, USBCPOWER2_REG_INTERRUPT_STATUS, &status ) )
        {
            log_printf ( &logger, "USB Status: " );
            if ( status & USBCPOWER2_INTERRUPT_STATUS_CABLE_ATTACHED )
            {
                log_printf ( &logger, "Attached\r\n" );
            }
            else if ( status & USBCPOWER2_INTERRUPT_STATUS_CABLE_DETACHED )
            {
                log_printf ( &logger, "Detached\r\n" );
            }
            else
            {
                log_printf ( &logger, "Unknown\r\n" );
            }
        }
        if ( USBCPOWER2_OK == usbcpower2_read_reg ( &usbcpower2, USBCPOWER2_REG_CC_STATUS, &status ) )
        {
            usbcpower2_display_cc_status ( status );
        }
        Delay_ms ( 10 );
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

static void usbcpower2_display_cc_status ( uint8_t cc_status )
{
    log_printf ( &logger, "VBUS Status: " );
    if ( cc_status & USBCPOWER2_CC_STATUS_VBUS_DETECTED )
    {
        log_printf ( &logger, "Detected (UFP mode)\r\n" );
        log_printf ( &logger, "Rp Status: " );
        switch ( cc_status & USBCPOWER2_CC_STATUS_RP_DET_MASK )
        {
            case USBCPOWER2_CC_STATUS_RP_DET_STANDBY:
            {
                log_printf ( &logger, "Standby\r\n" );
                break;
            }
            case USBCPOWER2_CC_STATUS_RP_DET_STD_USB:
            {
                log_printf ( &logger, "Std USB\r\n" );
                break;
            }
            case USBCPOWER2_CC_STATUS_RP_DET_1_5_A:
            {
                log_printf ( &logger, "1.5A\r\n" );
                break;
            }
            case USBCPOWER2_CC_STATUS_RP_DET_3_0_A:
            {
                log_printf ( &logger, "3.0A\r\n" );
                break;
            }
            default:
            {
                log_printf ( &logger, "Unknown\r\n" );
                break;
            }
        }
    }
    else
    {
        log_printf ( &logger, "Not detected (DFP mode)\r\n" );
    }
    
    log_printf ( &logger, "Port Attachment Status: " );
    switch ( cc_status & USBCPOWER2_CC_STATUS_PORT_STATUS_MASK )
    {
        case USBCPOWER2_CC_STATUS_PORT_STATUS_NOT_CONNECTED:
        {
            log_printf ( &logger, "Not connected\r\n" );
            break;
        }
        case USBCPOWER2_CC_STATUS_PORT_STATUS_DFP_ATTACHED:
        {
            log_printf ( &logger, "DFP attached\r\n" );
            break;
        }
        case USBCPOWER2_CC_STATUS_PORT_STATUS_UFP_ATTACHED:
        {
            log_printf ( &logger, "UFP attached\r\n" );
            break;
        }
        case USBCPOWER2_CC_STATUS_PORT_STATUS_ANALOG_AUDIO:
        {
            log_printf ( &logger, "Analog audio accessory attached\r\n" );
            break;
        }
        case USBCPOWER2_CC_STATUS_PORT_STATUS_DEBUG:
        {
            log_printf ( &logger, "Debug accessory attached\r\n" );
            break;
        }
        default:
        {
            log_printf ( &logger, "Unknown\r\n" );
            break;
        }
    }
    
    log_printf ( &logger, "CC Polarity: " );
    switch ( cc_status & USBCPOWER2_CC_STATUS_CC_POLARITY_MASK )
    {
        case USBCPOWER2_CC_STATUS_CC_POLARITY_CABLE_NOT_ATTACHED:
        {
            log_printf ( &logger, "Cable not attached\r\n\n" );
            break;
        }
        case USBCPOWER2_CC_STATUS_CC_POLARITY_CC1_NORMAL:
        {
            log_printf ( &logger, "CC1 is connected (normal orientation)\r\n\n" );
            break;
        }
        case USBCPOWER2_CC_STATUS_CC_POLARITY_CC2_REVERSED:
        {
            log_printf ( &logger, "CC2 is connected (reversed orientation)\r\n\n" );
            break;
        }
        default:
        {
            log_printf ( &logger, "Unknown\r\n\n" );
            break;
        }
    }
}

// ------------------------------------------------------------------------ END
