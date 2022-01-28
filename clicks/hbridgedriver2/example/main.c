/*!
 * @file main.c
 * @brief HBridgeDriver2 Click example
 *
 * # Description
 * This library contains API for the H-Bridge Driver 2 Click driver.
 * This demo application shows the use of a H-Bridge Driver 2 Click board™.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI, PWM module and log UART.
 * After driver initialization and default settings,
 * the application displays the device ID data, sets PWM duty cycle to 50% 
 * and start PWM module.
 *
 * ## Application Task
 * This example demonstrates the use of the H-Bridge Driver 2 Click board™.
 * The application turns connected MOSFETs gates high or low in order to drive 
 * the motor forward, backward, stop with brake or stop.
 * Results are being sent to the Usart Terminal, where you can track their changes.
 * 
 * ## Additional Function
 * - static void display_status ( void )
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hbridgedriver2.h"

static hbridgedriver2_t hbridgedriver2;
static log_t logger;
static uint8_t global_fault;
static hbridgedriver2_dev_id_t dev_id;

static void display_status ( void )
{
    uint16_t status;
    
    log_printf( &logger, "- - - - - - - - -  - - - - - - -\r\n" ); 
    log_printf( &logger, " Status :" );
    hbridgedriver2_get_status( &hbridgedriver2, &status );
    
    if ( HBRIDGEDRIVER2_STAT_0_OCHS1 == status )
    {
        log_printf( &logger, " HS1 Over−current detected\r\n" );
    }
    
    if ( HBRIDGEDRIVER2_STAT_0_OCLS1 == status )
    {
        log_printf( &logger, " LS1 Over−current detected\r\n" );
    }
    
    if ( HBRIDGEDRIVER2_STAT_0_OCHS2 == status )
    {
        log_printf( &logger, " HS2 Over−current detected\r\n" );
    }
    
    if ( HBRIDGEDRIVER2_STAT_0_OCLS2 == status )
    {
        log_printf( &logger, " LS2 Over−current detected\r\n" );
    }
    
    if ( HBRIDGEDRIVER2_STAT_0_VSUV == status )
    {
        log_printf( &logger, " Under−voltage detected\r\n" );
    }
    
    if ( HBRIDGEDRIVER2_STAT_0_VSOV == status )
    {
        log_printf( &logger, " Overvoltage detected\r\n" );
    }
    
    if ( HBRIDGEDRIVER2_STAT_0_OK == status )
    {
        log_printf( &logger, " Normal Operation\r\n" );
    }
    
    log_printf( &logger, "--------------------------------\r\n" );    
    Delay_ms( 100 );    
}

void application_init ( void )
{
    log_cfg_t log_cfg;                        /**< Logger config object. */
    hbridgedriver2_cfg_t hbridgedriver2_cfg;  /**< Click config object. */

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
    hbridgedriver2_cfg_setup( &hbridgedriver2_cfg );
    HBRIDGEDRIVER2_MAP_MIKROBUS( hbridgedriver2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hbridgedriver2_init( &hbridgedriver2, &hbridgedriver2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms( 1000 );
    
    hbridgedriver2_enable( &hbridgedriver2 );
    Delay_ms( 100 );
    log_info( &logger, "  Default config " );
    
    if ( HBRIDGEDRIVER2_ERROR == hbridgedriver2_default_cfg ( &hbridgedriver2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms( 1000 );

    log_printf( &logger, "--------------------------------\r\n" );
    Delay_ms( 100 );
    
    hbridgedriver2_get_device_id( &hbridgedriver2, &global_fault, &dev_id );
    Delay_ms( 100 );  
    log_printf( &logger, " ID header      : 0x%.4X \r\n", dev_id.id_header ); 
    log_printf( &logger, " Version        : 0x%.4X \r\n", dev_id.version );
    log_printf( &logger, " Product Code 1 : 0x%.4X \r\n", dev_id.product_code_1 );
    log_printf( &logger, " Product Code 2 : 0x%.4X \r\n", dev_id.product_code_2 );
    log_printf( &logger, " SPI Frame ID   : 0x%.4X \r\n", dev_id.spi_frame_id );
    log_printf( &logger, "--------------------------------\r\n" );
    Delay_ms( 100 );
    
    hbridgedriver2_set_duty_cycle ( &hbridgedriver2, 0.5 );
    hbridgedriver2_pwm_start( &hbridgedriver2 );
    Delay_ms( 100 );
    
    log_printf( &logger, "\t>>> START <<<\r\n" );
    display_status( );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    log_printf( &logger, "\t>>> Run Forward\r\n" );
    hbridgedriver2_run_forward( &hbridgedriver2, &global_fault );
    display_status( );
    Delay_ms( 2000 );
    
    log_printf( &logger, "\t>>> Stop With Brake\r\n" );
    hbridgedriver2_stop_with_brake( &hbridgedriver2, &global_fault );
    display_status( );
    Delay_ms( 2000 );
    
    log_printf( &logger, "\t>>> Run Backward\r\n" );
    hbridgedriver2_run_backward( &hbridgedriver2, &global_fault );
    display_status( );
    Delay_ms( 2000 );
    
    log_printf( &logger, "\t>>> Stop\r\n" );
    hbridgedriver2_stop( &hbridgedriver2, &global_fault );
    display_status( );
    Delay_ms( 2000 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
