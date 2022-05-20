/*!
 * @file main.c
 * @brief SolidSwitch3 Click example
 *
 * # Description
 * This example demonstrates the use of SolidSwitch 3 click board by controlling
 * the output state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Enables all outputs one by one in the span of 8 seconds, and after that disables 
 * all outputs for 3 seconds. Accordingly, the outputs status will be displayed on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "solidswitch3.h"

static solidswitch3_t solidswitch3;
static log_t logger;

/**
 * @brief SolidSwitch 3 display all enabled channels function.
 * @details This function displays all enabled channels on USB UART.
 * @param[out] ctx : Click context object.
 * See #solidswitch3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void solidswitch3_display_enabled_channels ( solidswitch3_t *ctx );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch3_cfg_t solidswitch3_cfg;  /**< Click config object. */

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
    solidswitch3_cfg_setup( &solidswitch3_cfg );
    SOLIDSWITCH3_MAP_MIKROBUS( solidswitch3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == solidswitch3_init( &solidswitch3, &solidswitch3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    SET_SPI_DATA_SAMPLE_EDGE;
    
    if ( SOLIDSWITCH3_ERROR == solidswitch3_default_cfg ( &solidswitch3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    for ( uint16_t cnt = SOLIDSWITCH3_CH_OUT1; cnt <= SOLIDSWITCH3_CH_OUT8; cnt <<= 1 )
    {
        if ( SOLIDSWITCH3_OK == solidswitch3_enable_output ( &solidswitch3, cnt ) )
        {
            solidswitch3_display_enabled_channels( &solidswitch3 );
            Delay_ms ( 1000 );
        }
    }
    
    if ( SOLIDSWITCH3_OK == solidswitch3_disable_output ( &solidswitch3, SOLIDSWITCH3_ALL_CHANNELS ) )
    {
        solidswitch3_display_enabled_channels( &solidswitch3 );
        Delay_ms ( 3000 );
    }
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

static void solidswitch3_display_enabled_channels ( solidswitch3_t *ctx )
{
    uint16_t output_state = ctx->output_state;
    uint8_t enabled_flag = 0;
    
    log_printf( &logger, " Outputs enabled: " );
    for ( uint8_t cnt = 1; cnt <= 16; cnt++ )
    {
        if ( SOLIDSWITCH3_OUT_ENABLE == ( output_state & SOLIDSWITCH3_OUT_BITS_MASK ) )
        {
            if ( enabled_flag == 1 )
            {
                log_printf( &logger, ", %u", ( uint16_t ) cnt );
            }
            else
            {
                log_printf( &logger, " %u", ( uint16_t ) cnt );
            }
            enabled_flag = 1;
        }
        output_state >>= 2;
    }
    
    if ( enabled_flag == 0 )
    {
        log_printf( &logger, " none" );
    }
    log_printf( &logger, "\r\n-----------------------\r\n" );
}

// ------------------------------------------------------------------------ END
