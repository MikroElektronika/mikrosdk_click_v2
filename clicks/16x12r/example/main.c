/*!
 * @file main.c
 * @brief 16x12 R Click example
 *
 * # Description
 * This example demonstrates the usage of the 16x12 R Click board which features a high-brightness
 * red LED matrix display. It displays characters, rotates them in different orientations,
 * prints a scrolling string, and renders a graphical image (MIKROE logo).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Click board and sets the default configuration.
 *
 * ## Application Task
 * Displays single characters and a string in multiple rotations, followed by
 * drawing and inverting the MIKROE logo image.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c16x12r.h"
#include "c16x12r_resources.h"

static c16x12r_t c16x12r;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c16x12r_cfg_t c16x12r_cfg;  /**< Click config object. */

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
    c16x12r_cfg_setup( &c16x12r_cfg );
    C16X12R_MAP_MIKROBUS( c16x12r_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c16x12r_init( &c16x12r, &c16x12r_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C16X12R_ERROR == c16x12r_default_cfg ( &c16x12r ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " Writing digits\r\n\n" );
    c16x12r.text_rotation = C16X12R_ROTATION_H_0;
    for ( uint8_t digit = '0'; digit <= '9'; digit++ )
    {
        c16x12r_write_char ( &c16x12r, digit );
        Delay_ms ( 500 );
    }

    log_printf( &logger, " Rotating char\r\n\n" );
    c16x12r.text_rotation = C16X12R_ROTATION_H_0;
    c16x12r_write_char ( &c16x12r, 'R' );
    Delay_ms ( 500 );
    c16x12r.text_rotation = C16X12R_ROTATION_H_180;
    c16x12r_write_char ( &c16x12r, 'R' );
    Delay_ms ( 500 );
    c16x12r.text_rotation = C16X12R_ROTATION_V_0;
    c16x12r_write_char ( &c16x12r, 'R' );
    Delay_ms ( 500 );
    c16x12r.text_rotation = C16X12R_ROTATION_V_180;
    c16x12r_write_char ( &c16x12r, 'R' );
    Delay_ms ( 500 );
    c16x12r.text_rotation = C16X12R_ROTATION_H_0;
    c16x12r_write_char ( &c16x12r, 'R' );
    Delay_ms ( 500 );

    log_printf( &logger, " Writing text\r\n\n" );
    c16x12r.text_rotation = C16X12R_ROTATION_H_0;
    c16x12r_write_string ( &c16x12r, "MIKROE - 16x12 R Click", 50 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Writing text\r\n\n" );
    c16x12r.text_rotation = C16X12R_ROTATION_H_180;
    c16x12r_write_string ( &c16x12r, "MIKROE - 16x12 R Click", 50 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Writing text\r\n\n" );
    c16x12r.text_rotation = C16X12R_ROTATION_V_0;
    c16x12r_write_string ( &c16x12r, "MIKROE - 16x12 R Click", 50 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Writing text\r\n\n" );
    c16x12r.text_rotation = C16X12R_ROTATION_V_180;
    c16x12r_write_string ( &c16x12r, "MIKROE - 16x12 R Click", 50 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Drawing MIKROE logo\r\n\n" );
    c16x12r_draw_picture ( &c16x12r, c16x12r_img_mikroe );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Drawing inverted MIKROE logo\r\n\n" );
    c16x12r_draw_picture ( &c16x12r, c16x12r_img_mikroe_inv );
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

// ------------------------------------------------------------------------ END
