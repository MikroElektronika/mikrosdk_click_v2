/*!
 * \file 
 * \brief Adapter Click example
 * 
 * # Description
 * Adapter click is a breakout board which simplifies connection of add-on boards. 
 * There are two ways of establishing connection: using male or female IDC10 connectors. 
 * Male header must be soldered on the top side of Adapter Click to connect the add-on board 
 * directly or via flat cable. Female header can be soldered either on the top, or the bottom 
 * side, depending on which one is more convenient in given circumstances.  
 * There are two jumpers for SPI/I2C selection and one for selection of power supply range.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C or SPI driver and makes an initial log.
 * 
 * ## Application Task  
 * This is an example that shows the use of the Adapter click board (SPI mode -  set as default). 
 * In I2C mode we are reading internal temperature from another device (THERMO 5 click board).
 * In SPI mode example we are writing "mikroElektronika" to SRAM click board, 
 * and then reading from the same memory location.
 * 
 * ## Additional Functions
 *   - float thermo5_read_inter_temp ( adapter_t *ctx ) - 
 *     @description Function reads measurements made by internal diode.
 *   - void sram_write_byte ( adapter_t *ctx, uint32_t reg_address, uint8_t write_data ) - 
 *     @description Function writes the 8-bit data to the target 24-bit register address of 23LC1024 chip.
 *   - uint8_t sram_read_byte ( adapter_t *ctx, uint32_t reg_address ) -
 *     @description Function reads the 8-bit data to the target 24-bit register address of 23LC1024 chip.
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "adapter.h"

#define THERMO5_INTER_DIO_DATA_HI_BYTE          0x00
#define THERMO5_INTER_DIO_DATA_LO_BYTE          0x29

#define SRAM_24BIT_DATA                         0x00FFFFFF
#define SRAM_CMD_WRITE                          0x02
#define SRAM_CMD_READ                           0x03

// ------------------------------------------------------------------ VARIABLES

static adapter_t adapter;
static log_t logger;

char send_buffer[ 17 ] = { 'm', 'i', 'k', 'r', 'o', 'E', 'l', 'e', 'k', 't', 'r', 'o', 'n', 'i', 'k', 'a', ' ' };
char mem_data[ 17 ];
uint8_t n_cnt;

// ------------------------------------------------------ ADDITIONAL FUNCTIONS

float thermo5_read_inter_temp ( adapter_t *ctx )
{
    uint16_t inter_temp;
    uint8_t high_byte;
    uint8_t low_byte;
    float output;
    output = 0.0;
    
    adapter_generic_read ( ctx, THERMO5_INTER_DIO_DATA_HI_BYTE, &high_byte, 1 );
    adapter_generic_read ( ctx, THERMO5_INTER_DIO_DATA_LO_BYTE, &low_byte, 1 );

    inter_temp = high_byte;
    inter_temp <<= 8;
    inter_temp |= low_byte;
    inter_temp >>= 5;
    output = ( float )inter_temp;
    output *= 0.125;

    return output;
}

void sram_write_byte ( adapter_t *ctx, uint32_t reg_address, uint8_t write_data )
{
    uint8_t tx_buf[ 4 ];
    uint8_t rx_buf;
    
    reg_address &= SRAM_24BIT_DATA;
    
    tx_buf[ 0 ]  = ( uint8_t ) ( reg_address >> 16 );
    tx_buf[ 1 ]  = ( uint8_t ) ( reg_address >> 8 );
    tx_buf[ 2 ]  = ( uint8_t )   reg_address;
    tx_buf[ 3 ]  = write_data;
    
    adapter_generic_write( ctx, SRAM_CMD_WRITE, tx_buf, 4 );
}

uint8_t sram_read_byte ( adapter_t *ctx, uint32_t reg_address )
{
    uint8_t tx_buf[ 5 ];
    uint8_t rx_buf[ 5 ];
    uint8_t read_data;
    
    reg_address &= SRAM_24BIT_DATA;

    tx_buf[ 0 ] = SRAM_CMD_READ;
    tx_buf[ 1 ] = ( uint8_t ) ( reg_address >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( reg_address >> 8 );
    tx_buf[ 3 ] = ( uint8_t )   reg_address;
    
    adapter_generic_transfer( ctx, tx_buf, 4, rx_buf, 1 );
    
    read_data = rx_buf[ 0 ];

    return read_data;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    adapter_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adapter_cfg_setup( &cfg );
    ADAPTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adapter_init( &adapter, &cfg );
}

void application_task ( void )
{
    float temp_value;

    if ( adapter.master_sel == ADAPTER_MASTER_SPI )
    {
        log_printf( &logger, " Writing text :\r\n" );
   
        for ( n_cnt = 0; n_cnt < 16; n_cnt++ )
        {
            sram_write_byte( &adapter, n_cnt, send_buffer[ n_cnt ] );
            Delay_ms ( 100 );
            log_printf( &logger, "%c", send_buffer[ n_cnt ] );
        }
    
    
        log_printf( &logger, "\r\n" );
        log_printf( &logger, " Read text :\r\n" );
        for ( n_cnt = 0; n_cnt < 16; n_cnt++ )
        {
            mem_data[ n_cnt ] = sram_read_byte( &adapter, n_cnt );
            Delay_ms ( 100 );
            log_printf( &logger, "%c", mem_data[ n_cnt ] );
        }   
        log_printf( &logger, "\r\n" );
        log_printf( &logger, "--------------------------\r\n" );
    
        Delay_ms ( 1000 );
    }
    else if ( adapter.master_sel == ADAPTER_MASTER_I2C )
    {
        temp_value = thermo5_read_inter_temp( &adapter );

        log_printf( &logger, " Thermo 5 internal temperature :  %.2f\r\n", temp_value );
        log_printf( &logger, "--------------------------\r\n" );
    
        Delay_ms( 2000 );
    }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
