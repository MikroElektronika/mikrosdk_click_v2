/*!
 * @file main.c
 * @brief DALI 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of DALI 2 Click for controlling the light level
 * of DALI control gear and reading its status when an individual short address is selected.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and driver, checks that the DALI bus is idle, and displays the selected addressing mode.
 *
 * ## Application Task
 * Cycles through all arc power levels from 0 to 254, increasing by five levels every 250 ms.
 * In short-address mode, queries and displays the actual level and control-gear status after each interval.
 *
 * @note
 * Connect a dedicated, current-limited DALI bus power supply and separately powered DALI control gear.
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
#include "dali2.h"

#ifndef MIKROBUS_POSITION_DALI2
    #define MIKROBUS_POSITION_DALI2 MIKROBUS_1
#endif

/** Select broadcast, group, or short-address control. Readback is enabled only for a short address. */
#define APP_ADDRESS_TYPE        DALI2_ADDRESS_BROADCAST
#define APP_ADDRESS             0
#define APP_LEVEL_STEP          5
#define APP_STEP_INTERVAL_MS    250

#if ( APP_ADDRESS_TYPE != DALI2_ADDRESS_SHORT ) && \
    ( APP_ADDRESS_TYPE != DALI2_ADDRESS_GROUP ) && ( APP_ADDRESS_TYPE != DALI2_ADDRESS_BROADCAST )
    #error "Select a supported DALI address type."
#elif ( APP_ADDRESS_TYPE == DALI2_ADDRESS_SHORT ) && ( ( APP_ADDRESS < 0 ) || ( APP_ADDRESS > 63 ) )
    #error "DALI short address must be between 0 and 63."
#elif ( APP_ADDRESS_TYPE == DALI2_ADDRESS_GROUP ) && ( ( APP_ADDRESS < 0 ) || ( APP_ADDRESS > 15 ) )
    #error "DALI group address must be between 0 and 15."
#endif

static dali2_t dali2;   /**< DALI 2 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dali2_cfg_t dali2_cfg;  /**< Click config object. */

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
    dali2_cfg_setup( &dali2_cfg );
    DALI2_MAP_MIKROBUS( dali2_cfg, MIKROBUS_POSITION_DALI2 );
    if ( DALI2_OK != dali2_init( &dali2, &dali2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DALI2_OK != dali2_default_cfg( &dali2 ) )
    {
        log_error( &logger, " Bus is not idle. Check the DALI bus power supply and wiring." );
        for ( ; ; );
    }

#if ( APP_ADDRESS_TYPE == DALI2_ADDRESS_SHORT )
    log_printf( &logger, " Short address: %u | Status readback enabled\r\n", ( uint16_t ) APP_ADDRESS );
#elif ( APP_ADDRESS_TYPE == DALI2_ADDRESS_GROUP )
    log_printf( &logger, " Group address: %u | No status readback\r\n", ( uint16_t ) APP_ADDRESS );
#else
    log_printf( &logger, " Broadcast control | No status readback\r\n" );
#endif
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t level = DALI2_LEVEL_OFF;
    err_t error_flag;
#if ( APP_ADDRESS_TYPE == DALI2_ADDRESS_SHORT )
    uint8_t actual_level;
    uint8_t status;
#endif

    // DALI control gear applies its own fade time and configured minimum/maximum levels.
    error_flag = dali2_set_level( &dali2, APP_ADDRESS, APP_ADDRESS_TYPE, level );
    if ( DALI2_OK == error_flag )
    {
        log_printf( &logger, " Arc power level sent: %u\r\n", ( uint16_t ) level );
        if ( level == DALI2_LEVEL_MAX )
        {
            level = DALI2_LEVEL_OFF;
        }
        else if ( level > ( DALI2_LEVEL_MAX - APP_LEVEL_STEP ) )
        {
            level = DALI2_LEVEL_MAX;
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

#if ( APP_ADDRESS_TYPE == DALI2_ADDRESS_SHORT )
    // Query only one commissioned device so multiple backward frames cannot collide.
    if ( DALI2_OK == error_flag )
    {
        error_flag = dali2_query( &dali2, APP_ADDRESS, DALI2_CMD_QUERY_ACTUAL_LEVEL, &actual_level );
        if ( DALI2_OK == error_flag )
        {
            log_printf( &logger, " Actual arc power level: %u\r\n", ( uint16_t ) actual_level );
            error_flag = dali2_query( &dali2, APP_ADDRESS, DALI2_CMD_QUERY_STATUS, &status );
            if ( DALI2_OK == error_flag )
            {
                log_printf( &logger, " Status: 0x%.2X | Lamp: %s | Fade: %s\r\n", ( uint16_t ) status,
                            ( status & DALI2_STATUS_LAMP_ON ) ? "ON" : "OFF",
                            ( status & DALI2_STATUS_FADE_RUNNING ) ? "Running" : "Idle" );
            }
        }

        if ( DALI2_ERROR_TIMEOUT == error_flag )
        {
            log_error( &logger, " No response. Check the commissioned short address and control-gear power." );
        }
        else if ( DALI2_OK != error_flag )
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
