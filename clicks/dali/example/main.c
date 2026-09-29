/*!
 * @file main.c
 * @brief DALI Click Example.
 *
 * # Description
 * This example demonstrates the use of DALI Click for controlling the light level
 * of DALI control gear and reading its status when an individual short address is selected.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and driver, checks that the receive input is idle, and displays the selected addressing mode.
 *
 * ## Application Task
 * Cycles arc power levels from 0 to 254 in steps of five, with a 250 ms pause after each level.
 * Displays changes in the PHY SEL pushbutton state.
 * In short-address mode, queries and displays the actual level and control-gear status after each interval.
 *
 * @note
 * Connect a dedicated, current-limited DALI bus power supply and separately powered DALI control gear.
 * Set the INT/ICP jumper to match APP_RX_SELECTION and select the MCU logic voltage with the VCC SEL jumper.
 * Broadcast mode controls all connected gear without commissioning. Short addresses and group membership
 * must be configured beforehand using a DALI commissioning tool; this example does not assign addresses.
 * Arc power levels are not percentages. Successful transmission does not acknowledge receipt by the control gear.
 * The blocking GPIO driver is intended for a single master and requires accurate MCU clock/delay settings.
 * Long interrupt handlers can disturb the Manchester timing. Check the signal timing on the target hardware.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dali.h"

#ifndef MIKROBUS_POSITION_DALI
    #define MIKROBUS_POSITION_DALI MIKROBUS_1
#endif

/** Select broadcast, group, or short-address control. Readback is enabled only for a short address. */
#define APP_ADDRESS_TYPE        DALI_ADDRESS_BROADCAST
#define APP_ADDRESS             0
#define APP_LEVEL_STEP          5
#define APP_STEP_INTERVAL_MS    250

/** Match the INT/ICP jumper: INT uses mikroBUS INT, and ICP uses mikroBUS PWM. */
#define APP_RX_SELECTION        DALI_RX_INT

#if ( APP_ADDRESS_TYPE != DALI_ADDRESS_SHORT ) && \
    ( APP_ADDRESS_TYPE != DALI_ADDRESS_GROUP ) && ( APP_ADDRESS_TYPE != DALI_ADDRESS_BROADCAST )
    #error "Select a supported DALI address type."
#elif ( APP_ADDRESS_TYPE == DALI_ADDRESS_SHORT ) && ( ( APP_ADDRESS < 0 ) || ( APP_ADDRESS > 63 ) )
    #error "DALI short address must be between 0 and 63."
#elif ( APP_ADDRESS_TYPE == DALI_ADDRESS_GROUP ) && ( ( APP_ADDRESS < 0 ) || ( APP_ADDRESS > 15 ) )
    #error "DALI group address must be between 0 and 15."
#endif

#if ( APP_RX_SELECTION != DALI_RX_INT ) && ( APP_RX_SELECTION != DALI_RX_ICP )
    #error "Select DALI_RX_INT or DALI_RX_ICP to match the receive jumper."
#endif

static dali_t dali;   /**< DALI Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dali_cfg_t dali_cfg;  /**< Click config object. */

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
    dali_cfg_setup( &dali_cfg );
    DALI_MAP_MIKROBUS( dali_cfg, MIKROBUS_POSITION_DALI );
    dali_cfg.rx_sel = APP_RX_SELECTION;
    if ( DALI_OK != dali_init( &dali, &dali_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DALI_OK != dali_default_cfg( &dali ) )
    {
        log_error( &logger, " RX is not idle. Check the INT/ICP jumper and DALI bus wiring." );
        for ( ; ; );
    }

#if ( APP_ADDRESS_TYPE == DALI_ADDRESS_SHORT )
    log_printf( &logger, " Short address: %u | Status readback enabled\r\n", ( uint16_t ) APP_ADDRESS );
#elif ( APP_ADDRESS_TYPE == DALI_ADDRESS_GROUP )
    log_printf( &logger, " Group address: %u | No status readback\r\n", ( uint16_t ) APP_ADDRESS );
#else
    log_printf( &logger, " Broadcast control | No status readback\r\n" );
#endif
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t level = DALI_LEVEL_OFF;
    static uint8_t last_phy_state = DALI_PHY_RELEASED;
    uint8_t phy_state;
    err_t error_flag;
#if ( APP_ADDRESS_TYPE == DALI_ADDRESS_SHORT )
    uint8_t actual_level;
    uint8_t status;
#endif

    // Sample the local button between frames so logging cannot disturb Manchester timing.
    phy_state = dali_get_phy_state( &dali );
    if ( phy_state != last_phy_state )
    {
        log_printf( &logger, " PHY SEL button: %s\r\n", ( DALI_PHY_PRESSED == phy_state ) ? "Pressed" : "Released" );
        last_phy_state = phy_state;
    }

    // DALI control gear applies its own fade time and configured minimum/maximum levels.
    error_flag = dali_set_level( &dali, APP_ADDRESS, APP_ADDRESS_TYPE, level );
    if ( DALI_OK == error_flag )
    {
        log_printf( &logger, " Arc power level sent: %u\r\n", ( uint16_t ) level );
        if ( level == DALI_LEVEL_MAX )
        {
            level = DALI_LEVEL_OFF;
        }
        else if ( level > ( DALI_LEVEL_MAX - APP_LEVEL_STEP ) )
        {
            level = DALI_LEVEL_MAX;
        }
        else
        {
            level += APP_LEVEL_STEP;
        }
    }
    else
    {
        log_error( &logger, " Set arc power level: %d", ( int16_t ) error_flag );
    }
    Delay_ms( APP_STEP_INTERVAL_MS );

#if ( APP_ADDRESS_TYPE == DALI_ADDRESS_SHORT )
    // Query only one commissioned device so multiple backward frames cannot collide.
    if ( DALI_OK == error_flag )
    {
        error_flag = dali_query( &dali, APP_ADDRESS, DALI_CMD_QUERY_ACTUAL_LEVEL, &actual_level );
        if ( DALI_OK == error_flag )
        {
            log_printf( &logger, " Actual arc power level: %u\r\n", ( uint16_t ) actual_level );
            error_flag = dali_query( &dali, APP_ADDRESS, DALI_CMD_QUERY_STATUS, &status );
            if ( DALI_OK == error_flag )
            {
                log_printf( &logger, " Status: 0x%.2X | Lamp: %s | Fade: %s\r\n", ( uint16_t ) status,
                            ( status & DALI_STATUS_LAMP_ON ) ? "ON" : "OFF",
                            ( status & DALI_STATUS_FADE_RUNNING ) ? "Running" : "Idle" );
            }
        }

        if ( DALI_ERROR_TIMEOUT == error_flag )
        {
            log_error( &logger, " No response. Check the commissioned short address and control-gear power." );
        }
        else if ( DALI_OK != error_flag )
        {
            log_error( &logger, " Query response: %d", ( int16_t ) error_flag );
        }
    }
#endif
    log_printf( &logger, "\r\n" );
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
