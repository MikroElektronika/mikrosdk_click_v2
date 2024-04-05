/*!
 * @file main.c
 * @brief TDC 2 Click example
 *
 * # Description
 * This library contains API for TDC 2 Click driver. 
 * The library initializes and defines the SPI bus drivers to 
 * write and read data from registers, as well as the default 
 * configuration for a reading time between two STOP signals.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver after that resets the device and 
 * performs default configuration and sets the device in read mode.

 *
 * ## Application Task
 * This example demonstrates the use of the TDC 2 Click board by 
 * measuring the time between two STOP signals. This example is set up to
 * generate stop signals until FIFO fil's up which is indicated by interrupt pin going to low state.
 * After that FIFO buffer is completely emptied by reading, and that data is used to calculate 
 * the time between STOP signals.
 *
 * @note
 * In order to test this example, you will need to connect STOP1 with the DIS pin. Disable pin is 
 * disabled by software and it isn't going to affect the working state of the TDC 2 Click Bord.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "tdc2.h"

static tdc2_t tdc2;
static log_t logger;

/**
 * @brief Dev generate stop signal function.
 * @details This function generates the stop signal by toggling DIS pin.
 * @param[out] cfg : Click configuration structure.
 * See #tdc2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note DIS pin ( Disable STOP channels) is disabled by software and isn't affecting the example.
 */
void dev_generate_stop( tdc2_t *ctx );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tdc2_cfg_t tdc2_cfg;  /**< Click config object. */

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
    tdc2_cfg_setup( &tdc2_cfg );
    TDC2_MAP_MIKROBUS( tdc2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == tdc2_init( &tdc2, &tdc2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TDC2_ERROR == tdc2_default_cfg ( &tdc2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    tdc2_start_measuring ( &tdc2 );
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint32_t reference_index [ 18 ] = { 0 };
    uint32_t stop_result [ 18 ] = { 0 };
    uint8_t cnt = 0;
    
    tdc2_reset_index( &tdc2 );
    Delay_ms ( 10 );
    
    while ( tdc2_get_int_state( &tdc2 ) == 1 )
    {
        dev_generate_stop( &tdc2 );
        Delay_ms ( 100 );
    }
    
    while ( tdc2_get_int_state( &tdc2 ) == 0 )
    {
        tdc2_read_results( &tdc2, TDC2_REG_INDEX_CH1_BYTE3, &reference_index[ cnt ], &stop_result[ cnt ] );
        
        log_printf( &logger, "CH1: Reference Index[%d]: %lu, Stop Result[%d]: %lu \r\n", ( uint16_t ) cnt, 
                    reference_index[ cnt ], ( uint16_t ) cnt, stop_result[ cnt ] ); 
        Delay_ms ( 10 ); 
        
        if ( cnt )
        {
            uint32_t time = 0;
            tdc2_get_time_between_stops ( &tdc2, stop_result[ cnt - 1 ], reference_index[ cnt - 1 ],
                                          stop_result[ cnt ], reference_index[ cnt ], &time );
            log_printf( &logger, "Time between STOP %d and STOP %d is %lu ms \r\n", 
                        ( uint16_t ) ( cnt - 1 ), ( uint16_t ) cnt, time / TDC2_uS_TO_mS ); 
            Delay_ms ( 10 );
        }
        cnt++;
    }
    log_printf( &logger, "---------------------------------------------- \r\n" ); 
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

void dev_generate_stop( tdc2_t *ctx )
{
    digital_out_high( &ctx->dis );
    Delay_ms ( 1 );
    digital_out_low( &ctx->dis );
}

// ------------------------------------------------------------------------ END
