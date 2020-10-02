/*!
 * \file 
 * \brief Fingerprint2 Click example
 * 
 * # Description
 * This example reads and processes data from Fingerprint 2 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization of UART module and additional pins, 
 * UART interrupt initialization and soft restart device.
 * 
 * ## Application Task  
 * Waits for command to execute code. 
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - fingerprint2_process ( ) - The general process of collecting presponce that sends a module.
 *
 * - fp_reg_one ( uint8_t fngr_number ) - Function for registering fingerprint on specific index.
 * - fp_clr_one ( uint8_t fngr_number ) - Function for deleteing fingerprint on specific index
 * - fp_reg_ring ( ) - Function for registering fingerprint circular..
 * - fp_clr_all ( ) - Function for deleteing all fingerprints.
 * - fp_curr_state (  ) - Function for getting number of memorized fingerprints.
 *
 * 
 * *note:* 
 * In the registration state each fingerprint needs to be enrolled 3 times.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "fingerprint2.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES

static fingerprint2_t fingerprint2;
static log_t logger;

uint8_t flag;
uint8_t fngr_cnt;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void fp_print ( char *buffer )
{
    uint8_t curr_pos;
    uint8_t length = strlen( buffer );

    for ( curr_pos = 0; curr_pos < length; curr_pos++ )
    {
        if ( buffer[ curr_pos ] == '\n' )
        {
            log_printf( &logger, "\r%c", buffer[ curr_pos ] );
        }
        else if ( buffer[ curr_pos ] == '.' )
        {
            log_printf( &logger, "%c ", buffer[ curr_pos ] );
        }
        else
        {
            log_printf( &logger, "%c", buffer[ curr_pos ] );
        }
    }
}

static void fingerprint2_process ( void )
{
    uint16_t rsp_size;
    uint16_t rsp_cnt = 0;

    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    flag = 0;
    
    while( process_cnt != 0 )
    {
        rsp_size = fingerprint2_generic_read( &fingerprint2, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != 0 )
        {  
            fp_print( uart_rx_buffer );

            // Validation of the received data
            if ( strcmp( uart_rx_buffer, "</R>" )  )
            {
                flag = 1;
                //log_printf( &logger, "\r\n" );
            }
            if ( strcmp( uart_rx_buffer, "put fingerprint" ) )
            {
                Delay_ms( 2000 );
            }
            if ( strcmp( uart_rx_buffer, "Move finger away from sensor" ) )
            {
                Delay_ms( 2000 );
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

//Write index number of fingeprint to be store: from 0 to 23
void fp_reg_one ( uint8_t fngr_number )
{
    log_printf( &logger, "Registration process\r\n" );
    Delay_ms( 500 );
   
    fingerprint2_reg_one_fp( &fingerprint2, fngr_number );
    do
    {
        fingerprint2_process(  );
    } 
    while ( flag == 0 );
}

// Write index number of fingeprint to be deleted: from 0 to 23
void fp_clr_one ( uint8_t fngr_number )
{
    log_printf( &logger, "Deleting process\r\n" );
    Delay_ms( 500 );
    
    fingerprint2_delete_one_fp( &fingerprint2, fngr_number );
    do
    {
        fingerprint2_process(  );
    } 
    while ( flag == 0 );
}

//Write fingeprint circular ( starting at 0 - up to 23 )
void fp_reg_ring ( )
{
    log_printf( &logger, "Circular fingeprints registration process\r\n" );
    Delay_ms( 500 );
    if( fngr_cnt > 23 )
    {
        fngr_cnt = 0;
    }
    else
    {
        fingerprint2_reg_one_fp( &fingerprint2, fngr_cnt );
        fngr_cnt++;
        do
        {
            fingerprint2_process(  );
        } 
        while ( flag == 0 );
    }
}

// Delete all fingeprints: from 0 to 23
void fp_clr_all ( )
{
    uint8_t cnt = 0;
    log_printf( &logger, "Process of deleting all fingeprints\r\n" );
    Delay_ms( 500 );
    
    while ( cnt < 23 )
    {
        fingerprint2_delete_one_fp( &fingerprint2, cnt );
        cnt++;
        do
        {
            fingerprint2_process(  );
        } 
        while ( flag == 0 );
    }
}

// Current state ( number of memorized fingerprints )
void fp_curr_state ( )
{
    fingerprint2_generic_write( &fingerprint2, FINGERPRINT2_CMD_FP_REG_NO, strlen( FINGERPRINT2_CMD_FP_REG_NO ) );
    do
    {
        fingerprint2_process(  );
    } 
    while ( flag == 0 );
}

// Compare fingerprint on input with all other fingerprints that are memorized.
void fp_compare ( )
{
    fingerprint2_generic_write( &fingerprint2, FINGERPRINT2_CMD_FP_CMP, strlen( FINGERPRINT2_CMD_FP_CMP ) );
    do
    {
        fingerprint2_process(  );
    }
    while ( flag == 0 );
}


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    fingerprint2_cfg_t cfg;

    fngr_cnt = 0;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    fingerprint2_cfg_setup( &cfg );
    FINGERPRINT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fingerprint2_init( &fingerprint2, &cfg );
    
    Delay_ms( 1000 );
}

void application_task ( void )
{    
    fp_reg_ring( );
    Delay_ms( 200 );

    fp_curr_state( );
    Delay_ms( 200 );
    
    fp_compare( );
    Delay_ms( 200 );
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
