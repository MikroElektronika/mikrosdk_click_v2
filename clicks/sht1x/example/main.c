/*!
 * \file 
 * \brief SHT1x Click example
 * 
 * # Description
 * This click measures temperature and humidity.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables GPIO.
 * 
 * ## Application Task  
 * This example demonstrates the use of SHT1x Click board by measuring 
   temperature and humidity, and displays the results on USART terminal.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "sht1x.h"

// ------------------------------------------------------------------ VARIABLES

static sht1x_t sht1x;
static log_t logger;

static sht1x_cfg_t cfg;

static uint8_t i;
static uint8_t data_val;
static uint8_t err;
static uint8_t msb;
static uint8_t lsb;
static uint8_t checksum;
static uint16_t t;
static uint16_t h;
static float value;
static uint8_t uc_sens_err;
static int16_t int_temp;
static int16_t int_humi;
static float humidity;
static float temperature;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void sht1x_trans_start ( )
{
    sht1x_output_sda ( &sht1x, &cfg );

    sht1x_sda_high( &sht1x );

    sht1x_input_sda ( &sht1x, &cfg );

    sht1x_scl_low( &sht1x );

    Delay_us( 1 );

    sht1x_scl_high( &sht1x );

    Delay_us( 1 );

    sht1x_output_sda ( &sht1x, &cfg );

    sht1x_sda_low( &sht1x );

    Delay_us( 1 );

    sht1x_scl_low( &sht1x );

    Delay_us( 3 );

    sht1x_scl_high( &sht1x );

    Delay_us( 1 );

    sht1x_input_sda ( &sht1x, &cfg );

    Delay_us( 1 );

    sht1x_scl_low( &sht1x );
}

uint8_t sht1x_read_byte( uint8_t ack )
{
    i = 0x80;
    data_val = 0;

    sht1x_output_sda ( &sht1x, &cfg );

    sht1x_sda_high( &sht1x );

    sht1x_input_sda ( &sht1x, &cfg );

    sht1x_scl_low( &sht1x );

    while( i )
    {
        sht1x_scl_high( &sht1x );
        Delay_us( 1 );
        if ( sht1x_get_sda( &sht1x ) == 1 )
        {
            data_val = ( data_val | i );
        }
        sht1x_scl_low( &sht1x );
        Delay_us( 1 );
        i = ( i >> 1 );
    }

    sht1x_output_sda ( &sht1x, &cfg );

    if( ack )
    {
        sht1x_sda_low( &sht1x );
    }
    else
    {
        sht1x_sda_high( &sht1x );
    }

    sht1x_scl_high( &sht1x );
    Delay_us( 3 );
    sht1x_scl_low( &sht1x );
    Delay_us( 1 );

    sht1x_sda_high( &sht1x );

    sht1x_input_sda ( &sht1x, &cfg );

    return data_val;
}

uint8_t sht1x_write_byte( uint8_t value )
{
    i = 0x80;
    err = 0;

    sht1x_output_sda ( &sht1x, &cfg );

    while( i )
    {
        if ( i & value )
        {
            sht1x_sda_high( &sht1x );
        }
        else
        {
            sht1x_sda_low( &sht1x );
        }

        sht1x_scl_high( &sht1x );
        Delay_us( 3 );
        sht1x_scl_low( &sht1x );
        Delay_us( 3 );
        i = ( i >> 1 );
    }

    sht1x_sda_high( &sht1x );
    sht1x_input_sda ( &sht1x, &cfg );

    sht1x_scl_high( &sht1x );
    Delay_us( 3 );
    if ( sht1x_get_sda( &sht1x ) == 1 )
	{
	    err = 1;
	}
    Delay_us( 1 );
    sht1x_scl_low( &sht1x );

    return err;
}

uint8_t sht1x_measure( uint16_t *p_val, uint8_t mode )
{
    i = 0;
    *p_val = 0;
    
    sht1x_trans_start(  );

    if( mode )
    {
        mode = SHT1X_MEAS_HUMI;
    }
    else
    {
        mode = SHT1X_MEAS_TEMP;
    }

    if( sht1x_write_byte( mode ) )
    {
        return( 1 );
    }

    sht1x_input_sda ( &sht1x, &cfg );

    while( i < 240 )
    {
        Delay_ms ( 3 );
        if ( sht1x_get_sda( &sht1x ) == 0 )
        {
            i = 0;
            break;
        }
        i++;
    }

    if( i )
    {
        return( 2 );
    }

    msb = sht1x_read_byte( SHT1X_ACK );
    lsb = sht1x_read_byte( SHT1X_ACK );
    checksum = sht1x_read_byte( SHT1X_NACK );

    *p_val = ( msb << 8 ) | lsb ;

    return( 0 );
}

void sht1x_read_results ( float *f_t, float *f_rh )
{
    uc_sens_err = 0;

    uc_sens_err = sht1x_measure( &t, 0 );
    int_temp = ( int16_t )( sht1x_calc_temp( &sht1x, t ) * 10 );

    uc_sens_err = sht1x_measure(&h, 1);
    int_humi = ( int16_t )( sht1x_calc_humi( &sht1x, h, t ) * 10 );

    value = ( float )int_temp;
    *f_t = value / 10;
    value = ( float )int_humi;
    *f_rh = value / 10;
}

uint8_t sht1x_rd_stat_reg ( uint8_t *p_val )
{
    checksum = 0;

    sht1x_trans_start( );
    if( sht1x_write_byte( SHT1X_STAT_REG_R ) )
    {
        return 1;
    }
    *p_val = sht1x_read_byte( SHT1X_ACK );
    checksum = sht1x_read_byte( SHT1X_NACK );

    return 0;
}

uint8_t sht1x_wr_stat_reg ( uint8_t value )
{
    sht1x_trans_start();
    if( sht1x_write_byte( SHT1X_STAT_REG_W ) )
    {
        return 1;
    }
    if( sht1x_write_byte( value ) )
    {
        return 1;
    }

    return 0;
}

void sht1x_connection_reset ( )
{
    sht1x_output_sda ( &sht1x, &cfg );

    sht1x_sda_high( &sht1x );

    sht1x_input_sda ( &sht1x, &cfg );

    sht1x_scl_low( &sht1x );

    for( i = 0; i < 9; i++ )
    {
        sht1x_scl_high( &sht1x );
        Delay_us( 3 );
        sht1x_scl_low( &sht1x );
        Delay_us( 3 );
    }

    sht1x_trans_start( );
}

uint8_t sht1x_soft_reset ( )
{
    sht1x_connection_reset( );

    return ( sht1x_write_byte( SHT1X_SOFT_RESET ) );
}

void application_init ( void )
{
    log_cfg_t log_cfg;
    
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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    sht1x_cfg_setup( &cfg );
    SHT1X_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    sht1x_init( &sht1x, &cfg );
}

void application_task ( void )
{
    sht1x_read_results( &temperature, &humidity );
    log_printf( &logger, " Temperature: %.2f ", temperature );
    log_printf( &logger, " C \r\n" );
  
    log_printf( &logger, " Humidity: %.2f ", humidity );
    log_printf( &logger, " \r\n" );
    
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

// ------------------------------------------------------------------------ END
