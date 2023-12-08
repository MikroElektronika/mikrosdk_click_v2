/*!
 * \file 
 * \brief Mp3 Click example
 * 
 * # Description
 * This app demonstrates the use of MP3 click by playing the specified sound
 * from the mp3_resources.h file.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and performs the default click configuration.
 * 
 * ## Application Task  
 * Playing the specified sound form the mp3_resources.h file.
 * 
 * \author MikroE Team
 *
 */

#include "board.h"
#include "log.h"
#include "mp3.h"
#include "mp3_resources.h"

static mp3_t mp3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    mp3_cfg_t cfg;

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
    mp3_cfg_setup( &cfg );
    MP3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mp3_init( &mp3, &cfg );

    mp3_reset( &mp3 );

    mp3_cmd_write( &mp3, MP3_MODE_ADDR, 0x0800 );
    mp3_cmd_write( &mp3, MP3_BASS_ADDR, 0x7A00 );
    mp3_cmd_write( &mp3, MP3_CLOCKF_ADDR, 0x2000 );

    // MP3 set volume, maximum volume is 0x00 and total silence is 0xFE.
    mp3_set_volume( &mp3, 0x2F, 0x2F );
    Delay_ms ( 1000 );

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{   
    uint32_t file_size = sizeof ( gandalf_sax_mp3_compressed );
    uint32_t file_pos = 0;
    uint8_t data_buf[ 32 ] = { 0 };

    log_printf( &logger, " Playing audio..." );
    for ( file_pos = 0; ( file_pos + 32 ) <= file_size; file_pos += 32 )
    {
        memcpy ( data_buf, &gandalf_sax_mp3_compressed[ file_pos ], 32 );
        while ( MP3_OK != mp3_data_write_32( &mp3, data_buf ) );
    }

    for ( ; file_pos < file_size; file_pos++ )
    {
        while ( MP3_OK != mp3_data_write( &mp3, gandalf_sax_mp3_compressed[ file_pos ] ) );
    }
    log_printf( &logger, "Done\r\n\n" );
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
