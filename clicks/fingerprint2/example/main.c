/*!
 * \file 
 * \brief Fingerprint2 Click example
 * 
 * # Description
 * This example demonstrates the use of Fingerprint 2 click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver, enables the click board, and then executes a command for 
 * registering a fingerprint.
 * 
 * ## Application Task  
 * Compares a fingerprint on input to the registered fingerprint and 
 * displays the results on the USB UART every 5 seconds.
 * 
 * ## Additional Functions
 * - fingerprint2_process ( ) - The general process of collecting data the module sends.
 * - fp_reg_one ( uint8_t fngr_number ) - Registers a fingerprint at a specific index number.
 * - fp_clr_one ( uint8_t fngr_number ) - Deletes a fingerprint from a specific index number.
 * - fp_clr_all ( ) - Clears all fingerprints.
 * - fp_curr_state (  ) - Lists the registration status and returns the number of registered fingerprints.
 * - fp_compare ( ) - Compares a fingerprint on input to all other fingerprints that are memorized.
 * 
 * @note
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

#define PROCESS_COUNTER 100
#define PROCESS_RX_BUFFER_SIZE 800

// ------------------------------------------------------------------ VARIABLES

static fingerprint2_t fingerprint2;
static log_t logger;

uint8_t flag;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void fingerprint2_process ( void )
{
    int32_t rsp_size;

    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    flag = 0;
    
    while( process_cnt != 0 )
    {
        rsp_size = fingerprint2_generic_read( &fingerprint2, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

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
            
            if ( strstr( uart_rx_buffer, "</R>" ) )
            {
                flag = 1;
                process_cnt = 5;
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
    fingerprint2_process(  );
    
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

    fingerprint2_cfg_setup( &cfg );
    FINGERPRINT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fingerprint2_init( &fingerprint2, &cfg );
    
    fingerprint2_reset ( &fingerprint2 );
    Delay_ms( 1000 );
    
    fp_reg_one( 0 );
    Delay_ms( 1000 );
}

void application_task ( void )
{    
    fp_compare( );
    Delay_ms( 5000 );
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
