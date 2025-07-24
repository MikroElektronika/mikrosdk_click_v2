/*!
 * @file main.c
 * @brief Solenoid Driver Click example
 *
 * # Description
 * This example demonstrates the use of the Solenoid Driver Click board by 
 * enabling output channels one by one in a round-robin fashion and parsing 
 * the diagnostic status after each update. The diagnosis includes 
 * undervoltage detection, output fault status, and operation mode.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the Click board driver, and applies the default configuration.
 *
 * ## Application Task
 * Sequentially enables each output channel with a 1-second delay, 
 * checks the diagnostic register, logs operation status, and clears the latch register.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "solenoiddriver.h"

static solenoiddriver_t solenoiddriver;
static log_t logger;

/**
 * @brief Solenoid Driver parse diagnosis function.
 * @details This function parses the content of the diagnosis register and logs status 
 * messages based on the diagnosis flags from the Solenoid Driver Click board.
 * @param[in] ctx : Click context object.
 * See #solenoiddriver_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void solenoiddriver_parse_diag ( solenoiddriver_t *ctx );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solenoiddriver_cfg_t solenoiddriver_cfg;  /**< Click config object. */

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
    solenoiddriver_cfg_setup( &solenoiddriver_cfg );
    SOLENOIDDRIVER_MAP_MIKROBUS( solenoiddriver_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == solenoiddriver_init( &solenoiddriver, &solenoiddriver_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SOLENOIDDRIVER_ERROR == solenoiddriver_default_cfg ( &solenoiddriver ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint8_t out_en = SOLENOIDDRIVER_OUT_CTRL_EN0;
    if ( SOLENOIDDRIVER_OK == solenoiddriver_set_output ( &solenoiddriver, out_en ) )
    {
        solenoiddriver_parse_diag ( &solenoiddriver );
        log_printf ( &logger, " OUT0: %u\r\n", ( uint16_t ) 
                    ( SOLENOIDDRIVER_OUT_CTRL_EN0 == ( out_en & SOLENOIDDRIVER_OUT_CTRL_EN0 ) ) );
        log_printf ( &logger, " OUT1: %u\r\n", ( uint16_t ) 
                    ( SOLENOIDDRIVER_OUT_CTRL_EN1 == ( out_en & SOLENOIDDRIVER_OUT_CTRL_EN1 ) ) );
        log_printf ( &logger, " OUT2: %u\r\n", ( uint16_t ) 
                    ( SOLENOIDDRIVER_OUT_CTRL_EN2 == ( out_en & SOLENOIDDRIVER_OUT_CTRL_EN2 ) ) );
        log_printf ( &logger, " OUT3: %u\r\n\n", ( uint16_t ) 
                    ( SOLENOIDDRIVER_OUT_CTRL_EN3 == ( out_en & SOLENOIDDRIVER_OUT_CTRL_EN3 ) ) );
        out_en <<= 1;
        if ( out_en > SOLENOIDDRIVER_OUT_CTRL_EN3 )
        {
            out_en = SOLENOIDDRIVER_OUT_CTRL_EN0;
        }
        solenoiddriver_clear_latch ( &solenoiddriver );
    }
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

static void solenoiddriver_parse_diag ( solenoiddriver_t *ctx )
{
    if ( ctx->diagnosis & SOLENOIDDRIVER_DIAG_UVRVM )
    {
        log_printf ( &logger, " VM Undervoltage condition since last Standard Diagnosis readout\r\n" );
    }
    switch ( ctx->diagnosis & SOLENOIDDRIVER_DIAG_MODE_MASK )
    {
        case SOLENOIDDRIVER_DIAG_MODE_LIMP_HOME:
        {
            log_printf ( &logger, " Operation mode: Limp Home\r\n" );
            break;
        }
        case SOLENOIDDRIVER_DIAG_MODE_ACTIVE:
        {
            log_printf ( &logger, " Operation mode: Active\r\n" );
            break;
        }
        case SOLENOIDDRIVER_DIAG_MODE_IDLE:
        {
            log_printf ( &logger, " Operation mode: Idle\r\n" );
            break;
        }
        default:
        {
            log_printf ( &logger, " Operation mode: Reserved\r\n" );
            break;
        }
    }
    if ( ctx->diagnosis & SOLENOIDDRIVER_DIAG_TER )
    {
        log_printf ( &logger, " Previous transmission failed or first frame after reset\r\n" );
    }
    if ( ctx->diagnosis & SOLENOIDDRIVER_DIAG_OLOFF )
    {
        log_printf ( &logger, " At least one channel in OFF state (with IOLx bit set to 1b)\r\n" );
    }
    if ( ctx->diagnosis & SOLENOIDDRIVER_DIAG_ERR_OUT3 )
    {
        log_printf ( &logger, " Over temperature or overload detected on OUT3\r\n" );
    }
    if ( ctx->diagnosis & SOLENOIDDRIVER_DIAG_ERR_OUT2 )
    {
        log_printf ( &logger, " Over temperature or overload detected on OUT2\r\n" );
    }
    if ( ctx->diagnosis & SOLENOIDDRIVER_DIAG_ERR_OUT1 )
    {
        log_printf ( &logger, " Over temperature or overload detected on OUT1\r\n" );
    }
    if ( ctx->diagnosis & SOLENOIDDRIVER_DIAG_ERR_OUT0 )
    {
        log_printf ( &logger, " Over temperature or overload detected on OUT0\r\n" );
    }
}

// ------------------------------------------------------------------------ END
