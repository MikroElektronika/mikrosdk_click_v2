/*!
 * \file 
 * \brief Mp3 Click example
 * 
 * # Description
 * This app demonstrates the use of MP3 click for playing .mp3 file from SD.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init, MP3 init and reset procedure. 
 * Standard configuration chip and set volume on the left and right channel.
 * Then initializes SD card and searching for songs on the SD card.
 * 
 * ## Application Task  
 * Play audio, every 100 ms.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mp3.h"

// ------------------------------------------------------------------ VARIABLES

static mp3_t mp3;
static log_t logger;
static const buff_size = 512;

// ------------------------------------------------------------------ ADDITIONAL FUNCTIONS

void mp3_set_volume ( mp3_t *ctx, uint8_t vol_left, uint8_t vol_right )
{
    uint16_t volume;
    volume = ( vol_left << 8 ) + vol_right;
    mp3_cmd_write( ctx, MP3_VOL_ADDR, volume );    
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mp3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mp3_cfg_setup( &cfg );
    MP3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mp3_init( &mp3, &cfg );

    mp3_reset( &mp3 );

    mp3_cmd_write( &mp3, MP3_MODE_ADDR, 0x0800 );
    mp3_cmd_write( &mp3, MP3_BASS_ADDR, 0x7A00 );
    mp3_cmd_write( &mp3, MP3_CLOCKF_ADDR, 0x2000 );

    mp3_set_volume( &mp3, 0x2F, 0x2F );

    log_printf( &logger, "App init done\r\n" );
}

void application_task ( void )
{   
    uint32_t file_size = 32778;
    uint8_t cnt;
    uint8_t file_pos = 0;
    uint8_t *ptr;

    log_printf( &logger, "--Play audio\r\n" );

    while( file_size > buff_size )
    {
        for (cnt = 0; cnt < buff_size / 32 ; cnt++)
        {
            ptr = &MP3_LAKI[0] + ( cnt * 32 );
            while( mp3_data_write_32( &mp3, ptr ) );
            file_pos += 32;
        }
        file_size -= buff_size;
    }

    for( cnt = 0; cnt < file_size; cnt++ )
    {
        
        while( mp3_data_write( &mp3, MP3_LAKI[ file_pos ] ) );
        file_pos++;
    }
    log_printf( &logger, "--Finish\r\n" );
    Delay_ms( 100 );

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
