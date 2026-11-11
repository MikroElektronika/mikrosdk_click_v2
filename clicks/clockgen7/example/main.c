/*!
 * @file main.c
 * @brief Clock Gen 7 Click example
 *
 * # Description
 * This example demonstrates the use of the Clock Gen 7 Click board by 
 * generating a low-jitter output clock (CLK_OUT) locked to a frequency
 * reference (CLK_IN).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the Click default configuration
 * and sets the CLK_IN reference to 48 kHz.
 *
 * ## Application Task
 * Cycles through several PLL ratios every 3 seconds while keeping CLK_IN fixed,
 * and logs the resulting CLK_OUT frequency.
 *
 * @note
 * The CS2501 SPI control port is write-only, so communication check and lock
 * status read-back are available over the I2C interface only.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "clockgen7.h"

#ifndef MIKROBUS_POSITION_CLOCKGEN7
    #define MIKROBUS_POSITION_CLOCKGEN7 MIKROBUS_1
#endif

// Example selection macros
#define CLOCKGEN7_CLK_IN_FREQ    48000
#define CLOCKGEN7_RATIO_STEP_1   400.0
#define CLOCKGEN7_RATIO_STEP_2   512.0
#define CLOCKGEN7_RATIO_STEP_3   640.0

static clockgen7_t clockgen7;
static log_t logger;

/**
 * @brief Clock Gen 7 apply ratio function.
 * @details This function applies desired ratio and logs CLK_OUT 
 * and PLL status.
 * @param[in] ratio : PLL ratio to be set.
 * @return Nothing.
 * @note None.
 */
static void clockgen7_apply_ratio ( float ratio );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    clockgen7_cfg_t clockgen7_cfg;  /**< Click config object. */

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
    clockgen7_cfg_setup( &clockgen7_cfg );
    CLOCKGEN7_MAP_MIKROBUS( clockgen7_cfg, MIKROBUS_POSITION_CLOCKGEN7 );
    err_t init_flag = clockgen7_init( &clockgen7, &clockgen7_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CLOCKGEN7_ERROR == clockgen7_default_cfg ( &clockgen7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    clockgen7_set_clk_in_freq( &clockgen7, CLOCKGEN7_CLK_IN_FREQ );
    log_printf( &logger, " CLK_IN reference: %lu Hz\r\n", ( uint32_t ) CLOCKGEN7_CLK_IN_FREQ );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    clockgen7_apply_ratio( CLOCKGEN7_RATIO_STEP_1 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    clockgen7_apply_ratio( CLOCKGEN7_RATIO_STEP_2 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    clockgen7_apply_ratio( CLOCKGEN7_RATIO_STEP_3 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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

static void clockgen7_apply_ratio ( float ratio )
{
    uint8_t lock_status = 0;

    log_printf( &logger, "----------------------------\r\n" );

    if ( CLOCKGEN7_OK == clockgen7_set_ratio( &clockgen7, ratio ) )
    {
        log_printf( &logger, " Ratio: %.1f\r\n", ratio );
        log_printf( &logger, " CLK_OUT: %lu Hz\r\n", ( uint32_t ) ( ratio * CLOCKGEN7_CLK_IN_FREQ ) );
    }
    else
    {
        log_printf( &logger, " Failed to set ratio.\r\n" );
        return;
    }

    Delay_10ms( );
    
    if ( CLOCKGEN7_OK == clockgen7_get_lock_status( &clockgen7, &lock_status ) )
    {
        if ( CLOCKGEN7_STATUS_LOCKED == lock_status )
        {
            log_printf( &logger, " PLL status: locked\r\n" );
        }
        else
        {
            log_printf( &logger, " PLL status: unlocked\r\n" );
        }
    }
    else
    {
        log_printf( &logger, " Failed to get status.\r\n" );
    }
}

// ------------------------------------------------------------------------ END
