/*!
 * \file 
 * \brief rfid Click example
 * 
 * # Description
 * This example configures RFID click and reads tag ID
 *
 * The demo application is composed of 3 sections :
 * 
 * ## Additional function
 * Calibrates RFID and checks calibration output.
 * 
 * ## Application Init 
 * Initializes driver and wake-up module and what's importatns, selects
 * tag reading protocol.
 * 
 * ## Application Task  
 * Reads tag id in read buffer.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rfid.h"

// ------------------------------------------------------------------ VARIABLES

static rfid_t rfid;
static log_t logger;

static uint8_t r_buf[ RFID_MAX_DATA_LEN ] = { 0 };
static uint8_t w_buf[ RFID_MAX_DATA_LEN ] = { 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTION

uint8_t rfid_calibration( void )
{
    uint8_t check = 0;
    
    uint8_t calibration[ 14 ] = { 0x03 , 0xA1 , 0x00 , 0xF8 , 0x01 , 0x18 , 0x00 , 0x20 , 0x60 , 0x60 , 0x00 , 0x00 , 0x3F , 0x00 };
    check = rfid_write( &rfid , RFID_IDLE , 0x0E , calibration );
    check = rfid_poll( &rfid );
    rfid_read( &rfid , r_buf , 0xFF );
    if(!check)
        return 0;
    memset( r_buf , 0 , RFID_MAX_DATA_LEN );
    
    calibration[11] = 0xFC;
    check = rfid_write( &rfid , RFID_IDLE , 0x0E , calibration );
    check = rfid_poll( &rfid );
    rfid_read( &rfid , r_buf , 0xFF );
    if(!check)
        return 0;
    memset( r_buf , 0 , RFID_MAX_DATA_LEN );
    
    calibration[11] = 0x7C;
    check = rfid_write( &rfid , RFID_IDLE , 0x0E , calibration );
    check = rfid_poll( &rfid );
    rfid_read( &rfid , r_buf , 0xFF );
    if(!check)
        return 0;
    memset( r_buf , 0 , RFID_MAX_DATA_LEN );
    
    calibration[11] = 0x3C;
    check = rfid_write( &rfid , RFID_IDLE , 0x0E , calibration );
    check = rfid_poll( &rfid );
    rfid_read( &rfid , r_buf , 0xFF );
    if(!check)
        return 0;
    memset( r_buf , 0 , RFID_MAX_DATA_LEN );
    
    calibration[11] = 0x5C;
    check = rfid_write( &rfid , RFID_IDLE , 0x0E , calibration );
    check = rfid_poll( &rfid );
    rfid_read( &rfid , r_buf , 0xFF );
    if(!check)
        return 0;
    memset( r_buf , 0 , RFID_MAX_DATA_LEN );
    
    calibration[11] = 0x6C;
    check = rfid_write( &rfid , RFID_IDLE , 0x0E , calibration );
    check = rfid_poll( &rfid );
    rfid_read( &rfid , r_buf , 0xFF );
    if(!check)
        return 0;
    memset( r_buf , 0 , RFID_MAX_DATA_LEN );
    
    calibration[11] = 0x74;
    check = rfid_write( &rfid , RFID_IDLE , 0x0E , calibration );
    check = rfid_poll( &rfid );
    rfid_read( &rfid , r_buf , 0xFF );
    if(!check)
        return 0;
    memset( r_buf , 0 , RFID_MAX_DATA_LEN );
    
    calibration[11] = 0x70;
    check = rfid_write( &rfid , RFID_IDLE , 0x0E , calibration );
    check = rfid_poll( &rfid );
    rfid_read( &rfid , r_buf , 0xFF );
    if(!check)
        return 0;
    memset( r_buf , 0 , RFID_MAX_DATA_LEN );
    
    return 1;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rfid_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rfid_cfg_setup( &cfg );
    RFID_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rfid_init( &rfid, &cfg );
    
    // Click configuration and protocol select 
    
    rfid_com_select( &rfid , RFID_SPI );
    rfid_read_idn( &rfid , r_buf );
    rfid_calibration( );
    rfid_index_mod( &rfid , r_buf  );
    rfid_auto_det( &rfid , r_buf  );
    rfid_protocol_select( &rfid , r_buf , RFID_ISO_14443A );
}

void application_task ( void )
{
    rfid_read_nfc_tag( &rfid , r_buf );
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
