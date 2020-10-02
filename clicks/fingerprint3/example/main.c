/*!
 * \file 
 * \brief Fingerprint3 Click example
 * 
 * # Description
 * This example reads and processes data from Fingerprint 3 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - fingerprint3_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "fingerprint3.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

static char data_buf[ 20 ] = "12.2";
static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0; 

static uint8_t check_sensor[ 12 ] =
{ 0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x36, 0x00, 0x3A };

static uint8_t read_sys_para[ 12 ] =
{ 0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x0F, 0x00, 0x13 };

static uint8_t vfy_pwd[ 16 ] =
{ 0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x07, 0x13, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x1B };

static uint8_t aura_led_config_red[ 16 ] =
{ 0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x07, 0x35, 0x01, 0x80,
  0x01, 0x01, 0x00, 0xC0 };

static uint8_t aura_led_config_blue[ 16 ] =
{ 0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x07, 0x35, 0x01, 0x80,
  0x02, 0x01, 0x00, 0xC1 };

static uint8_t aura_led_config_purple[ 16 ] =
{ 0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x07, 0x35, 0x01, 0x80,
  0x03, 0x01, 0x00, 0xC2 };

static uint8_t gen_img[ 12 ] =
{ 0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x01, 0x00, 0x05 };

static uint8_t img_2_tz_1[ 13 ] =
{ 0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x04, 0x02, 0x01, 0x00, 0x08 };

static uint8_t img_2_tz_2[ 13 ] =
{ 0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x04, 0x02, 0x02, 0x00, 0x09 };

static uint8_t reg_model[ 12 ] =
{ 0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x05, 0x00, 0x09 };

static uint8_t fingerprint_match[ 12 ] =
{ 0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x03, 0x03, 0x00, 0x07 };

// ------------------------------------------------------------------ VARIABLES

static fingerprint3_t fingerprint3;
static log_t logger;
fingerprint3_rsp_t rsp;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void fingerprint3_process ( void )
{
    uint16_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = fingerprint3_generic_read( &fingerprint3, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size > 0 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                if ( uart_rx_buffer[ check_buf_cnt ] == 0 ) 
                {
                    uart_rx_buffer[ check_buf_cnt ] = 13;
                }
            }
            log_printf( &logger, "%s", uart_rx_buffer );

            // Storages data in parser buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_PARSER_BUFFER_SIZE )
            {
                strncat( current_parser_buf, uart_rx_buffer, rsp_size );
            }
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_100ms( );
        }
    }
}

void fingerprint3_display_rsp ( )
{
    uint16_t n_cnt;

    log_printf( &logger, "* Header            : 0x%x \r\n", rsp.header );
    log_printf( &logger, "* Address           : 0x%x \r\n", rsp.addr );
    log_printf( &logger, "* Package identifier: 0x%x \r\n", rsp.pkg_ident );
    log_printf( &logger, "* Package length    : 0x%x \r\n", rsp.pkg_len );

    log_printf( &logger, "* Confirmation code : " );

    if ( rsp.confirm_code == FINGERPRINT3_OK )
    {
        log_printf( &logger, "OK \r\n" );
    }
    else
    {
        log_printf( &logger, "0x%x", rsp.confirm_code );

    }

    if ( rsp.pkg_len > 3 )
    {
        log_printf( &logger, " \r\n" );
    }

    for ( n_cnt = 0; n_cnt < rsp.pkg_len - 3; n_cnt++ )
    {
        log_printf( &logger, "* Message Content[" );

        if ( n_cnt < 10 )
        {
            log_printf( &logger, "0" );
        }

        log_printf( &logger, "%d ", n_cnt );
        log_printf( &logger, "]: 0x%x \r\n", rsp.pkg_contents[ n_cnt ] );
    }

    log_printf( &logger, " \r\n" );
    log_printf( &logger, "* Checksum           : 0x%x \r\n", rsp.checksum );
}

void fingerprint3_display_match_score ( )
{
    uint16_t match_score;

    log_printf( &logger, "--------------------------------- \r\n" );
    log_printf( &logger, "    Fingerprint match details     \r\n" );
    log_printf( &logger, " \r\n" );

    match_score = rsp.pkg_contents[ 1 ];
    match_score <<= 8;
    match_score |= rsp.pkg_contents[ 2 ];

    if ( rsp.confirm_code == FINGERPRINT3_OK )
    {
        log_printf( &logger, "  >>>>> FINGERPRINT MATCH <<<<<<  \r\n" );
        log_printf( &logger, " \r\n" );
        log_printf( &logger, "  Match score       : %d \r\n", match_score );
        log_printf( &logger, "--------------------------------- \r\n" );
        fingerprint3_generic_write( &fingerprint3, &aura_led_config_blue[ 0 ], 16 );
    }

    if ( rsp.confirm_code == FINGERPRINT3_PACKET_RECIEVE_ERR )
    {
        log_printf( &logger, "  Error When Receiving Package!   \r\n" );
        log_printf( &logger, " \r\n" );
        log_printf( &logger, "--------------------------------- \r\n" );
        fingerprint3_generic_write( &fingerprint3, &aura_led_config_red[ 0 ], 16 );
    }

    if ( rsp.confirm_code == FINGERPRINT3_NO_MATCH )
    {
        log_printf( &logger, "      >>>>> NO MATCH <<<<<<       \r\n" );
        log_printf( &logger, " \r\n" );
        log_printf( &logger, "--------------------------------- \r\n" );
        fingerprint3_generic_write( &fingerprint3, &aura_led_config_red[ 0 ], 16 );
    }
}

void log_write ( uint8_t *str_buf, uint8_t str_type )
{
    char *temp_buf = str_buf;
    log_printf( &logger, temp_buf, str_type );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    fingerprint3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    fingerprint3_cfg_setup( &cfg );
    FINGERPRINT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fingerprint3_init( &fingerprint3, &cfg );

    log_printf( &logger, "--------------------------------- \r\n" );
    log_printf( &logger, "       Fingerprint 3 click        \r\n" );
    log_printf( &logger, "--------------------------------- \r\n" );
    Delay_ms( 500 );

    fingerprint3_generic_write( &fingerprint3, &check_sensor[ 0 ], 12 );
    log_printf( &logger, "        Check the sensor          \r\n" );
    fingerprint3_parser_rsp( &rsp );
    fingerprint3_display_rsp( );
    log_printf( &logger, "--------------------------------- \r\n" );
    Delay_ms( 3000 );

    fingerprint3_generic_write( &fingerprint3, &vfy_pwd[ 0 ], 16 );
    log_printf( &logger, "     Verify Module Password       \r\n" );
    fingerprint3_parser_rsp( &rsp );
    fingerprint3_display_rsp( );
    log_printf( &logger, "--------------------------------- \r\n" );
    Delay_ms( 3000 );

    log_printf( &logger, " >>>  Register fingerprint  <<<   \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - - - - \r\n" );
    log_printf( &logger, " Place your finger on the sensor  \r\n" );


    while ( fingerprint3_finger_indicator( &fingerprint3 ) == FINGERPRINT3_DETECT_NO_FINGER )
    {
        fingerprint3_generic_write( &fingerprint3, &aura_led_config_purple[ 0 ], 16 );
        Delay_ms( 2000 );
    }

    log_printf( &logger, "--------------------------------- \r\n" );
    log_printf( &logger, "    Add fingerprint process...    \r\n" );
    fingerprint3_buf_clear( );
    fingerprint3_generic_write( &fingerprint3, &gen_img[ 0 ], 12 );
    Delay_ms( 500 );
    fingerprint3_parser_rsp( &rsp );

    if ( rsp.confirm_code == FINGERPRINT3_OK )
    {
        fingerprint3_generic_write( &fingerprint3, &img_2_tz_1[ 0 ], 13 );
        Delay_ms( 2000 );
        
        log_printf( &logger, "- - - - - - - - - - - - - - - - - \r\n" );
        log_printf( &logger, "      Scanning is complete        \r\n" );
        log_printf( &logger, "--------------------------------- \r\n" );
        Delay_ms( 1000 );
    }

    fingerprint3_buf_clear( );
    log_printf( &logger, "  >>> Comparing Fingerprints <<<  \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - - - - \r\n" );
    log_printf( &logger, " Place your finger on the sensor  \r\n" );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    if ( fingerprint3_finger_indicator( &fingerprint3 ) == FINGERPRINT3_DETECT_FINGER )
    {
        fingerprint3_buf_clear( );
        log_printf( &logger, "--------------------------------- \r\n" );
        log_printf( &logger, " >>> Verification in progress...  \r\n" );
        Delay_ms( 2000 );

        fingerprint3_generic_write( &fingerprint3, &gen_img[ 0 ], 12 );
        Delay_ms( 500 );
        fingerprint3_parser_rsp( &rsp );
        Delay_ms( 100 );

        if ( rsp.confirm_code == FINGERPRINT3_OK )
        {
            fingerprint3_generic_write( &fingerprint3, &img_2_tz_2[ 0 ], 13 );
            Delay_ms( 500 );
            fingerprint3_buf_clear( );
        }

        fingerprint3_generic_write( &fingerprint3, &reg_model[ 0 ], 12 );
        Delay_ms( 100 );
        fingerprint3_buf_clear( );

        fingerprint3_generic_write( &fingerprint3, &fingerprint_match[ 0 ], 12 );
        Delay_ms( 500 );
        fingerprint3_parser_rsp( &rsp );
        fingerprint3_display_match_score( );
        Delay_ms( 3000 );

        log_printf( &logger, "  >>> Comparing Fingerprints <<<  \r\n" );
        log_printf( &logger, "- - - - - - - - - - - - - - - - - \r\n" );
        log_printf( &logger, " Place your finger on the sensor  \r\n" );
    }
    else
    {
        fingerprint3_generic_write( &fingerprint3, &aura_led_config_purple[ 0 ], 16 );
        Delay_ms( 2000 );
        fingerprint3_buf_clear( );
    }
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
