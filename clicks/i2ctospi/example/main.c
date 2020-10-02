/*!
 * \file 
 * \brief I2cToSpi Click example
 * 
 * # Description
 * I2C to SPi Click allows serving as an interface between a standard I2C-bus of a microcontroller 
 * and an SPi bus, which allows the microcontroller to communicate directly with SPi devices 
 * through its I2C-bus. By offering an I2C-bus slave-transmitter or slave-receiver and SPI master, 
 * this Click controls all the SPi bus-specific sequences, protocol, and timing. It also has its own 
 * internal oscillator, and it supports the SPi chip select output that may be configured as GPIO when not used.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C,
 * hardware reset, SS0 ( CS ) configured to be used as slave select outputs, set the configuration of SPI:
 * order MSB first, clock Idle low, leading-edge transition, SPI clock rate to 115kHz,
 * set SPI EEPROM write enable SS0, clear  interrupt,
 * clear RT5 register, sets starting time: hours, minutes and seconds ( enable counting ), also write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of RTC 5 click is wired to I2C to SPI click board.
 * I2C to SPI click communicates with register via the I2C interface,
 * serve as an interface between a standard I2C-bus of a microcontroller and an SPI bus.
 * RTC 5 click communicates with register via SPI interface.
 * In this examples, we display RTC time which we received reading from the target register 
 * address of MCP79510 chip on RTC 5 click board via I2C interface of I2C to SPI click board.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on usb uart changes for every 1 sec.
 * 
 * *note:* 
 * <pre>
 * Additional Functions :
 *  - void display_log_uart( uint8_t value ) - Write the value of time or date as a two-digit number.
 *  - void rtc5_clear( i2ctospi_t *ctx, i2ctospi_spi_t *spi ) - Clear RTCC and SRAM memory of RTC 5 click.
 *  - void rtc5_set_time_seconds( i2ctospi_t *ctx, i2ctospi_spi_t *spi, uint8_t seconds ) - Set the seconds and enable counting.
 *  - uint8_t rtc5_get_time_seconds( i2ctospi_t *ctx, i2ctospi_spi_t *spi ) - Get the seconds.
 *  - void rtc5_set_time_minutes( uint8_t minutes ) - Set the minutes.
 *  - uint8_t rtc5_get_time_minutes( i2ctospi_t *ctx, i2ctospi_spi_t *spi ) - Get the minutes.
 *  - void rtc5_set_time_hours( i2ctospi_t *ctx, i2ctospi_spi_t *spi, uint8_t hours ) - Set the hours.
 *  - uint8_t rtc5_get_time_hours( i2ctospi_t *ctx, i2ctospi_spi_t *spi ) - Get the hours.
 * </pre>
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "i2ctospi.h"

// ------------------------------------------------------------------ VARIABLES

static i2ctospi_t i2ctospi;
static i2ctospi_spi_t i2ctospi_spi;
static i2ctospi_gpio_t i2ctospi_gpio;
static log_t logger;

static uint8_t time_hours;
static uint8_t time_minutes;
static uint8_t time_seconds;
static uint8_t time_seconds_new = 0xFF;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void display_log_uart ( uint8_t value )
{
    log_printf( &logger, " %d%d ", value / 10, value % 10 );
}

void rtc5_clear ( i2ctospi_t *ctx, i2ctospi_spi_t *spi )
{
    uint8_t reg_add;
    
    spi->slave_device = I2CTOSPI_SLAVEDEVICE_SS0;
    spi->function_id = I2CTOSPI_RTC5_COMMAND_WRITE;
    spi->reg_addr = reg_add;

    for ( reg_add = 0; reg_add < 0x20; reg_add++ )
    {
        i2ctospi_spi_write_byte( ctx, spi, 0x00 );
        Delay_1us( );
    }

    spi->reg_addr = I2CTOSPI_RTC5_COMMAND_CLEAR;
    i2ctospi_spi_write_byte( ctx, spi, 0x00 );

    i2ctospi_clear_interrupt( ctx );
}

void rtc5_set_time_seconds ( i2ctospi_t *ctx, i2ctospi_spi_t *spi, uint8_t seconds )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;

    ones = 0x00;
    tens = 0x00;

    seconds %= 60;

    ones = seconds % 10;

    tens = ( seconds / 10 ) << 4;

    temp = tens | ones;
    temp |= I2CTOSPI_RTC5_COMMAND_ENABLE_COUNTING;

    spi->slave_device = I2CTOSPI_SLAVEDEVICE_SS0;
    spi->function_id = I2CTOSPI_RTC5_COMMAND_WRITE;
    spi->reg_addr = I2CTOSPI_RTC5_REG_TIME_SEC;

    i2ctospi_spi_write_byte( ctx, spi, temp );
}

uint8_t rtc5_get_time_seconds ( i2ctospi_t *ctx, i2ctospi_spi_t *spi )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result_sec;
    uint8_t temp;

    spi->slave_device = I2CTOSPI_SLAVEDEVICE_SS0;
    spi->function_id = I2CTOSPI_RTC5_COMMAND_READ;
    spi->reg_addr = I2CTOSPI_RTC5_REG_TIME_SEC;

    temp = i2ctospi_spi_read_byte( ctx, spi );

    ones = temp & 0x0F;

    tens = ( temp & 0x70 ) >> 4;

    result_sec = ( 10 * tens ) + ones;

    return result_sec;
}

void rtc5_set_time_minutes ( i2ctospi_t *ctx, i2ctospi_spi_t *spi, uint8_t minutes )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;

    ones = 0x00;
    tens = 0x00;

    minutes %= 60;

    ones = minutes % 10;

    tens = ( minutes / 10 ) << 4;

    temp = tens | ones;

    spi->slave_device = I2CTOSPI_SLAVEDEVICE_SS0;
    spi->function_id = I2CTOSPI_RTC5_COMMAND_WRITE;
    spi->reg_addr = I2CTOSPI_RTC5_REG_TIME_MIN;

    i2ctospi_spi_write_byte( ctx, spi, temp );
}

uint8_t rtc5_get_time_minutes ( i2ctospi_t *ctx, i2ctospi_spi_t *spi )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result_min;
    uint8_t temp;

    spi->slave_device = I2CTOSPI_SLAVEDEVICE_SS0;
    spi->function_id = I2CTOSPI_RTC5_COMMAND_READ;
    spi->reg_addr = I2CTOSPI_RTC5_REG_TIME_MIN;

    temp = i2ctospi_spi_read_byte( ctx, spi );

    ones = temp & 0x0F;

    tens = ( temp & 0x70 ) >> 4;

    result_min = ( 10 * tens ) + ones;

    return result_min;
}

void rtc5_set_time_hours ( i2ctospi_t *ctx, i2ctospi_spi_t *spi, uint8_t hours )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;

    ones = 0x00;
    tens = 0x00;

    hours %= 24;

    ones = hours % 10;

    tens = ( hours / 10 ) << 4;

    temp = tens | ones;

    spi->slave_device = I2CTOSPI_SLAVEDEVICE_SS0;
    spi->function_id = I2CTOSPI_RTC5_COMMAND_WRITE;
    spi->reg_addr = I2CTOSPI_RTC5_REG_TIME_HOUR,

    i2ctospi_spi_write_byte( ctx, spi, temp );
}

uint8_t rtc5_get_time_hours ( i2ctospi_t *ctx, i2ctospi_spi_t *spi )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result_hours;
    uint8_t temp;

    spi->slave_device = I2CTOSPI_SLAVEDEVICE_SS0;
    spi->function_id = I2CTOSPI_RTC5_COMMAND_READ;
    spi->reg_addr = I2CTOSPI_RTC5_REG_TIME_HOUR;

    temp = i2ctospi_spi_read_byte( ctx, spi );

    ones = temp & 0x0F;

    tens = ( temp & 0x30 ) >> 4;

    result_hours = ( 10 * tens ) + ones;

    return result_hours;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    i2ctospi_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    i2ctospi_cfg_setup( &cfg );
    I2CTOSPI_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2ctospi_init( &i2ctospi, &cfg );

    i2ctospi_default_cfg( &i2ctospi );
    
    //Set Time :  23h 59m 48s
    rtc5_clear( &i2ctospi, &i2ctospi_spi );  
    rtc5_set_time_hours( &i2ctospi, &i2ctospi_spi, 23 );
    Delay_1ms( );
    rtc5_set_time_minutes( &i2ctospi, &i2ctospi_spi, 59 );
    Delay_1ms( );
    rtc5_set_time_seconds( &i2ctospi, &i2ctospi_spi, 48 );
    Delay_1ms( );
}

void application_task ( void )
{
    time_seconds = rtc5_get_time_seconds( &i2ctospi, &i2ctospi_spi );
    Delay_1ms( );
    time_minutes = rtc5_get_time_minutes( &i2ctospi, &i2ctospi_spi );
    Delay_1ms( );
    time_hours = rtc5_get_time_hours( &i2ctospi, &i2ctospi_spi );
    Delay_1ms( );

    if ( time_seconds_new != time_seconds )
    {
        log_printf( &logger, " Time :  " );
    
        display_log_uart( time_hours );
        log_printf( &logger, ":" );
    
        display_log_uart( time_minutes );
        log_printf( &logger, ":" );
    
        display_log_uart( time_seconds );
        log_printf( &logger, "\r\n" );
        
        log_printf( &logger, "------------------\r\n" );

        time_seconds_new = time_seconds;
    }

    Delay_1ms( );
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
