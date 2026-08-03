/*!
 * @file main.c
 * @brief USB-C Power 3 Click example
 *
 * # Description
 * This example demonstrates the use of the USB-C Power 3 Click board for
 * monitoring USB Type-C connection and power status. The application reads
 * CC and power status registers, detects connection changes, and logs
 * detailed information about VBUS state, connection type, and cable orientation.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and USB-C Power 3 Click driver, and reads device
 * identification information.
 *
 * ## Application Task
 * Continuously monitors CC and power status registers, detects changes,
 * parses connection state, and controls VBUS direction (sink/source) accordingly.
 *
 * @note
 * The application automatically handles USB connection and disconnection events,
 * including VBUS control based on detected role.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "usbcpower3.h"

#ifndef MIKROBUS_POSITION_USBCPOWER3
    #define MIKROBUS_POSITION_USBCPOWER3 MIKROBUS_1
#endif

static usbcpower3_t usbcpower3;
static log_t logger;

/**
 * @brief USBC Power 3 parse power status function.
 * @details This function parses and logs the PTN power status register flags.
 * @param[in] power_status : Power status register value.
 * @return None.
 * @note None.
 */
static void usbcpower3_parse_power_status ( uint8_t power_status );

/**
 * @brief USBC Power 3 parse CC status function.
 * @details This function parses CC status, logs connection state, and controls VBUS direction.
 * @param[in] ctx : Click context object.
 * See #usbcpower3_t object definition for detailed explanation.
 * @param[in] cc_status : CC status register value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The function manages USB connection state and may restart the device on disconnect.
 */
static err_t usbcpower3_parse_cc_status ( usbcpower3_t *ctx, uint8_t cc_status );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcpower3_cfg_t usbcpower3_cfg;  /**< Click config object. */

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
    usbcpower3_cfg_setup( &usbcpower3_cfg );
    USBCPOWER3_MAP_MIKROBUS( usbcpower3_cfg, MIKROBUS_POSITION_USBCPOWER3 );
    if ( USBCPOWER3_OK != usbcpower3_init( &usbcpower3, &usbcpower3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( USBCPOWER3_OK != usbcpower3_ptn_read_info ( &usbcpower3 ) )
    {
        log_error( &logger, " PTN read info." );
        for ( ; ; );
    }
    log_printf( &logger, " --- PTN info ---\r\n" );
    log_printf( &logger, " Vendor ID: 0x%.4X\r\n", usbcpower3.info.vendor_id );
    log_printf( &logger, " Product ID: 0x%.4X\r\n", usbcpower3.info.product_id );
    log_printf( &logger, " Device ID: 0x%.4X\r\n", usbcpower3.info.device_id );
    log_printf( &logger, " USB-C rev: 0x%.4X\r\n", usbcpower3.info.usbtypec_rev );
    log_printf( &logger, " USB-PD rev/ver: 0x%.4X\r\n", usbcpower3.info.usbpd_rev_ver );
    log_printf( &logger, " PD interface rev: 0x%.4X\r\n\n", usbcpower3.info.pd_interface_rev );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    err_t error_flag = USBCPOWER3_OK;
    static uint8_t cc_status_old = 0;
    static uint8_t power_status_old = 0;
    uint8_t cc_status = 0;
    uint8_t power_status = 0;

    // Read CC and power status registers
    error_flag = usbcpower3_ptn_read_reg_byte ( &usbcpower3, USBCPOWER3_PTN_REG_CC_STATUS, &cc_status );
    if ( USBCPOWER3_OK == error_flag )
    {
        error_flag = usbcpower3_ptn_read_reg_byte ( &usbcpower3, USBCPOWER3_PTN_REG_POWER_STATUS, &power_status );
    }
    
    // Check if any of them are updated
    if ( ( USBCPOWER3_OK == error_flag ) && 
         ( ( cc_status_old != cc_status ) || ( power_status_old != power_status ) ) )
    {
        cc_status_old = cc_status;
        power_status_old = power_status;
        log_printf ( &logger, "###############################\r\n" );
        usbcpower3_parse_power_status ( power_status );
        error_flag = usbcpower3_parse_cc_status ( &usbcpower3, cc_status );
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

static void usbcpower3_parse_power_status ( uint8_t power_status )
{
    log_printf ( &logger, " --- Power status ---\r\n" );
    if ( power_status & USBCPOWER3_PTN_POWER_STATUS_DEBUG_CONNECTED )
    {
        log_printf ( &logger, " Debug Accessory connected\r\n" );
    }
    if ( power_status & USBCPOWER3_PTN_POWER_STATUS_TCPC_INIT )
    {
        log_printf ( &logger, " The TCPC is still performing internal initialization\r\n" );
    }
    if ( power_status & USBCPOWER3_PTN_POWER_STATUS_SRC_HIGH_V )
    {
        log_printf ( &logger, " Sourcing High Voltage\r\n" );
    }
    if ( power_status & USBCPOWER3_PTN_POWER_STATUS_SRC_VBUS_EN )
    {
        log_printf ( &logger, " Sourcing VBUS is enabled\r\n" );
    }
    if ( power_status & USBCPOWER3_PTN_POWER_STATUS_VBUS_DET_EN )
    {
        log_printf ( &logger, " VBUS Detection Enabled\r\n" );
    }
    if ( power_status & USBCPOWER3_PTN_POWER_STATUS_VBUS_PRESENT )
    {
        log_printf ( &logger, " VBUS Connected\r\n" );
    }
    if ( power_status & USBCPOWER3_PTN_POWER_STATUS_VCONN_PRESENT )
    {
        log_printf ( &logger, " VCONN present CC1 or CC2\r\n" );
    }
    if ( power_status & USBCPOWER3_PTN_POWER_STATUS_SINKING_VBUS )
    {
        log_printf ( &logger, " TCPC is sinking VBUS to the system load\r\n" );
    }
    log_printf ( &logger, "\r\n" );
    Delay_ms ( 1 );
}

static err_t usbcpower3_parse_cc_status ( usbcpower3_t *ctx, uint8_t cc_status )
{
    err_t error_flag = USBCPOWER3_OK;
    static uint8_t usb_connected = 0;
    log_printf ( &logger, " --- CC status ---\r\n" );
    if ( usb_connected )
    {
        // USB was connected in previous state
        if ( ( USBCPOWER3_PTN_CC_STATUS_CC2_OPEN == ( cc_status & USBCPOWER3_PTN_CC_STATUS_CC2_MASK ) ) && 
             ( USBCPOWER3_PTN_CC_STATUS_CC1_OPEN == ( cc_status & USBCPOWER3_PTN_CC_STATUS_CC1_MASK ) ) )
        {
            // CC2 and CC1 open means USB is disconnected
            log_printf ( &logger, " USB Disconnected\r\n" );
            if ( 1 == usb_connected )
            {
                // Disable sink VBUS and reset receive buffer
                error_flag = usbcpower3_ptn_write_reg_byte ( ctx, USBCPOWER3_PTN_REG_COMMAND, 
                                                             USBCPOWER3_PTN_COMMAND_DIS_SINK_VBUS );
                if ( USBCPOWER3_OK == error_flag )
                {
                    error_flag = usbcpower3_ptn_write_reg_byte ( ctx, USBCPOWER3_PTN_REG_COMMAND, 
                                                                 USBCPOWER3_PTN_COMMAND_RESET_RECEIVE_BUFFER );
                }
            }
            else if ( 2 == usb_connected )
            {
                // Disable source VBUS and reset transmit buffer
                error_flag = usbcpower3_ptn_write_reg_byte ( ctx, USBCPOWER3_PTN_REG_COMMAND, 
                                                            USBCPOWER3_PTN_COMMAND_DIS_SRC_VBUS );
                if ( USBCPOWER3_OK == error_flag )
                {
                    error_flag = usbcpower3_ptn_write_reg_byte ( ctx, USBCPOWER3_PTN_REG_COMMAND, 
                                                                 USBCPOWER3_PTN_COMMAND_RESET_TRANSMIT_BUFFER );
                }
            }

            if ( USBCPOWER3_OK == error_flag )
            {
                // Set look for connection mode and clear usb_connected state
                error_flag = usbcpower3_ptn_write_reg_byte ( ctx, USBCPOWER3_PTN_REG_COMMAND, 
                                                             USBCPOWER3_PTN_COMMAND_LOOK_4_CONNECTION );
                usb_connected = 0;
            }
        }
        else if ( USBCPOWER3_PTN_CC_STATUS_CONNECT_RESULT_SINK == 
                  ( cc_status & USBCPOWER3_PTN_CC_STATUS_CONNECT_RESULT_MASK ) )
        {
            // Parsing USB sink state
            if ( USBCPOWER3_PTN_CC_STATUS_CC2_OPEN != 
                 ( cc_status & USBCPOWER3_PTN_CC_STATUS_CC2_MASK ) )
            {
                if ( USBCPOWER3_PTN_CC_STATUS_CC2_SINK_DEFAULT == 
                     ( cc_status & USBCPOWER3_PTN_CC_STATUS_CC2_MASK ) )
                {
                    log_printf ( &logger, " Sink default (reversed orientation)\r\n" );
                }
                else if ( USBCPOWER3_PTN_CC_STATUS_CC2_SINK_POWER_1_5 == 
                          ( cc_status & USBCPOWER3_PTN_CC_STATUS_CC2_MASK ) )
                {
                    log_printf ( &logger, " Sink 1.5A (reversed orientation)\r\n" );
                }
                else if ( USBCPOWER3_PTN_CC_STATUS_CC2_SINK_POWER_3_0 == 
                          ( cc_status & USBCPOWER3_PTN_CC_STATUS_CC2_MASK ) )
                {
                    log_printf ( &logger, " Sink 3.0A (reversed orientation)\r\n" );
                }
            }
            else if ( USBCPOWER3_PTN_CC_STATUS_CC1_OPEN != 
                      ( cc_status & USBCPOWER3_PTN_CC_STATUS_CC1_MASK ) )
            {
                if ( USBCPOWER3_PTN_CC_STATUS_CC1_SINK_DEFAULT == 
                     ( cc_status & USBCPOWER3_PTN_CC_STATUS_CC1_MASK ) )
                {
                    log_printf ( &logger, " Sink default (normal orientation)\r\n" );
                }
                else if ( USBCPOWER3_PTN_CC_STATUS_CC1_SINK_POWER_1_5 == 
                          ( cc_status & USBCPOWER3_PTN_CC_STATUS_CC1_MASK ) )
                {
                    log_printf ( &logger, " Sink 1.5A (normal orientation)\r\n" );
                }
                else if ( USBCPOWER3_PTN_CC_STATUS_CC1_SINK_POWER_3_0 == 
                          ( cc_status & USBCPOWER3_PTN_CC_STATUS_CC1_MASK ) )
                {
                    log_printf ( &logger, " Sink 3.0A (normal orientation)\r\n" );
                }
            }
        }
        else
        {
            // Parsing USB source state
            if ( USBCPOWER3_PTN_CC_STATUS_CC2_OPEN != 
                 ( cc_status & USBCPOWER3_PTN_CC_STATUS_CC2_MASK ) )
            {
                if ( USBCPOWER3_PTN_CC_STATUS_CC2_SRC_RA == 
                     ( cc_status & USBCPOWER3_PTN_CC_STATUS_CC2_MASK ) )
                {
                    log_printf ( &logger, " Source Ra (reversed orientation)\r\n" );
                }
                else if ( USBCPOWER3_PTN_CC_STATUS_CC2_SRC_RD == 
                          ( cc_status & USBCPOWER3_PTN_CC_STATUS_CC2_MASK ) )
                {
                    log_printf ( &logger, " Source Rd (reversed orientation)\r\n" );
                }
            }
            else if ( USBCPOWER3_PTN_CC_STATUS_CC1_OPEN != 
                      ( cc_status & USBCPOWER3_PTN_CC_STATUS_CC1_MASK ) )
            {
                if ( USBCPOWER3_PTN_CC_STATUS_CC1_SRC_RA == 
                     ( cc_status & USBCPOWER3_PTN_CC_STATUS_CC1_MASK ) )
                {
                    log_printf ( &logger, " Source Ra (normal orientation)\r\n" );
                }
                else if ( USBCPOWER3_PTN_CC_STATUS_CC1_SRC_RD == 
                          ( cc_status & USBCPOWER3_PTN_CC_STATUS_CC1_MASK ) )
                {
                    log_printf ( &logger, " Source Rd (normal orientation)\r\n" );
                }
            }
        }
    }
    else if ( cc_status & USBCPOWER3_PTN_CC_STATUS_LOOKING_4_CONNECTION )
    {
        // USB is not connected, waiting for connection
        log_printf ( &logger, " Looking for USB connection\r\n" );
    }
    else
    {
        // USB connected, checking direction to enable sinking or sourcing on VBUS
        if ( USBCPOWER3_PTN_CC_STATUS_CONNECT_RESULT_SINK == 
             ( cc_status & USBCPOWER3_PTN_CC_STATUS_CONNECT_RESULT_MASK ) )
        {
            log_printf ( &logger, " USB Source Connected -> enabling VBUS Sink\r\n" );
            error_flag = usbcpower3_ptn_write_reg_byte ( ctx, USBCPOWER3_PTN_REG_POWER_CONTROL, 
                                                         USBCPOWER3_PTN_POWER_CONTROL_VBUS_V_MON_DIS );
            if ( USBCPOWER3_OK == error_flag )
            {
                error_flag = usbcpower3_ptn_write_reg_byte ( ctx, USBCPOWER3_PTN_REG_COMMAND, 
                                                             USBCPOWER3_PTN_COMMAND_EN_SINK_VBUS );
            }
            usb_connected = 1;
        }
        else
        {
            log_printf ( &logger, " USB Sink Connected -> enabling VBUS Source\r\n" );
            error_flag = usbcpower3_ptn_write_reg_byte ( ctx, USBCPOWER3_PTN_REG_POWER_CONTROL, 
                                                         USBCPOWER3_PTN_POWER_CONTROL_VBUS_V_MON_DIS | 
                                                         USBCPOWER3_PTN_POWER_CONTROL_DIS_V_ALARM_DIS );
            if ( USBCPOWER3_OK == error_flag )
            {
                error_flag = usbcpower3_ptn_write_reg_byte ( ctx, USBCPOWER3_PTN_REG_COMMAND, 
                                                             USBCPOWER3_PTN_COMMAND_SRC_VBUS_DEF_V );
            }
            usb_connected = 2;
        }
    }
    log_printf ( &logger, "\r\n" );
    Delay_ms ( 1 );

    return error_flag;
}

// ------------------------------------------------------------------------ END
