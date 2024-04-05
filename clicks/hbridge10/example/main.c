/*!
 * @file main.c
 * @brief HBridge10 Click example
 *
 * # Description
 * This example demonstrates the use of the H-Bridge 10 click board by
 * driving the motors connected between OUT1-OUT2 and OUT2-OUT3 in both directions. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Drives the motors connected between OUT1-OUT2 and OUT2-OUT3 in both directions
 * in the span of 6 seconds, and displays the status messages on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hbridge10.h"

static hbridge10_t hbridge10;
static log_t logger;

/**
 * @brief H-Bridge 10 display status function.
 * @details This function parses the status from output register and displays it on the USB UART.
 * @param[in] status : 16-bit status value.
 * @return None.
 * @note None.
 */
void hbridge10_display_status ( uint16_t status );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge10_cfg_t hbridge10_cfg;  /**< Click config object. */

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
    hbridge10_cfg_setup( &hbridge10_cfg );
    HBRIDGE10_MAP_MIKROBUS( hbridge10_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hbridge10_init( &hbridge10, &hbridge10_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE10_ERROR == hbridge10_default_cfg ( &hbridge10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint16_t status;
    if ( ( HBRIDGE10_OK == hbridge10_set_output_state ( &hbridge10, HBRIDGE10_CHANNEL_OUT1, HBRIDGE10_OUT_HIGH ) ) && 
         ( HBRIDGE10_OK == hbridge10_set_output_state ( &hbridge10, HBRIDGE10_CHANNEL_OUT2, HBRIDGE10_OUT_LOW ) ) && 
         ( HBRIDGE10_OK == hbridge10_set_output_state ( &hbridge10, HBRIDGE10_CHANNEL_OUT3, HBRIDGE10_OUT_HIGH ) ) )
    {
        Delay_ms ( 100 );
        if ( HBRIDGE10_OK == hbridge10_get_status ( &hbridge10, &status ) )
        {
            hbridge10_display_status ( status );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
    }
    if ( ( HBRIDGE10_OK == hbridge10_set_output_state ( &hbridge10, HBRIDGE10_CHANNEL_OUT1, HBRIDGE10_OUT_LOW ) ) && 
         ( HBRIDGE10_OK == hbridge10_set_output_state ( &hbridge10, HBRIDGE10_CHANNEL_OUT2, HBRIDGE10_OUT_HIGH ) ) && 
         ( HBRIDGE10_OK == hbridge10_set_output_state ( &hbridge10, HBRIDGE10_CHANNEL_OUT3, HBRIDGE10_OUT_LOW ) ) )
    {
        Delay_ms ( 100 );
        if ( HBRIDGE10_OK == hbridge10_get_status ( &hbridge10, &status ) )
        {
            hbridge10_display_status ( status );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
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

void hbridge10_display_status ( uint16_t status )
{
    if ( HBRIDGE10_OUT_OVER_TEMP_SD == status )
    {
        log_printf ( &logger, " Over temperature shutdown! \r\n" );
        return;
    }
    if ( status & HBRIDGE10_OUT_OVER_TEMP_WARNING )
    {
        log_printf ( &logger, " Over temperature pre-warning! \r\n" );
    }
    log_printf ( &logger, " OUT1 : " );
    if ( status & HBRIDGE10_OUT_STATUS_LS1_ON )
    {
        log_printf ( &logger, "LOW \r\n" );
    }
    else if ( status & HBRIDGE10_OUT_STATUS_HS1_ON )
    {
        log_printf ( &logger, "HIGH \r\n" );
    }
    else
    {
        log_printf ( &logger, "OFF \r\n" );
    }
    log_printf ( &logger, " OUT2 : " );
    if ( status & HBRIDGE10_OUT_STATUS_LS2_ON )
    {
        log_printf ( &logger, "LOW \r\n" );
    }
    else if ( status & HBRIDGE10_OUT_STATUS_HS2_ON )
    {
        log_printf ( &logger, "HIGH \r\n" );
    }
    else
    {
        log_printf ( &logger, "OFF \r\n" );
    }
    log_printf ( &logger, " OUT3 : " );
    if ( status & HBRIDGE10_OUT_STATUS_LS3_ON )
    {
        log_printf ( &logger, "LOW \r\n" );
    }
    else if ( status & HBRIDGE10_OUT_STATUS_HS3_ON )
    {
        log_printf ( &logger, "HIGH \r\n" );
    }
    else
    {
        log_printf ( &logger, "OFF \r\n" );
    }
    if ( status & HBRIDGE10_OUT_SHORT_CIRCUIT_DETECTED )
    {
        log_printf ( &logger, " Short circuit detected! \r\n" );
    }
    log_printf ( &logger, " Power : " );
    if ( HBRIDGE10_OUT_NORMAL_OPERATION != ( status & HBRIDGE10_OUT_NORMAL_OPERATION ) )
    {
        log_printf ( &logger, "Standby \r\n" );
    }
    else if ( status & HBRIDGE10_OUT_VS_UNDER_VOLTAGE )
    {
        log_printf ( &logger, "Under-voltage at VS detected \r\n" );
    }
    else
    {
        log_printf ( &logger, "Normal operation \r\n" );
    }
    log_printf ( &logger, "\r\n" );
}

// ------------------------------------------------------------------------ END
