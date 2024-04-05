/*!
 * @file main.c
 * @brief EEPROM8 Click example
 *
 * # Description
 * This example demonstrates the use of EEPROM 8 click board by writing specified data to
 * the memory and reading it back.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and USB UART logging.
 *
 * ## Application Task
 * Task writes a desired number of data bytes to the EEPROM 8 memory 
 * and verifies that it is written correctly by reading from the same memory location and 
 * in case of successful read, displays the memory content on the USB UART. 
 * This is done in two passes.
 *
 * @author Stefan Popovic
 *
 */

#include "board.h"
#include "log.h"
#include "eeprom8.h"

static eeprom8_t eeprom8;
static log_t logger;

// Number of test bytes
#define TEST_NBYTES ( 150 )

// Starting address for example
#define TEST_MEM_LOCATION ( EEPROM8_BLOCK_ADDR_START + 1024ul )

static uint8_t  cnt = 0;
static uint8_t  test_write_buffer[ TEST_NBYTES ]  = { 0 };
static uint8_t  test_read_buffer[ TEST_NBYTES ]   = { 0 };
static uint16_t addr_offset = TEST_MEM_LOCATION;

/**
 * @brief First pass function
 * @details This function writes and reads defined number of bytes
 *  with zero values
 * @param[in] ctx  Click object.
 * @param[in] write_buf  Data to be written.
 * @param[out] read_buf  Data to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t run_first_pass( eeprom8_t* ctx, uint8_t* write_buf, uint8_t* read_buf );

/**
 * @brief Second pass function
 * @details This function writes and reads defined number of bytes
 *  with the values following arithmetical progression
 * @param[in] ctx  Click object.
 * @param[in] write_buf  Data to be written.
 * @param[out] read_buf  Data to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t run_second_pass( eeprom8_t* ctx, uint8_t* write_buf, uint8_t* read_buf );

void application_init ( void ) 
{
    eeprom8_cfg_t eeprom8_cfg;  /**< Click config object. */
    log_cfg_t log_cfg;          /**< Logger config object. */
    
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
    
    //  Click initialization.
    eeprom8_cfg_setup( &eeprom8_cfg );
    EEPROM8_MAP_MIKROBUS( eeprom8_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == eeprom8_init( &eeprom8, &eeprom8_cfg ) )
    {
        log_error( &logger, " Communication Init " );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    // Reset variables
    cnt = 0;
    memset( test_read_buffer, 0, sizeof ( test_read_buffer ) );
    addr_offset = TEST_MEM_LOCATION;
    
    // Initiate first pass 
    //  filling the eeprom addresses with zeros 
    if( EEPROM8_ERROR == run_first_pass( &eeprom8, test_write_buffer, test_read_buffer ) )
    {
        log_error( &logger, " First Pass Failed " );
    }
    
    // Initiate second pass 
    //  filling the eeprom addresses with values following arithmetic sequence with difference of 1 
    if( EEPROM8_ERROR == run_second_pass( &eeprom8, test_write_buffer, test_read_buffer ) )
    {
        log_error( &logger, " Second Pass Failed " );
    }
    
    log_printf( &logger, " \r\nInitiating new iteration\r\n " );
    // 6 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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

// First pass: writing zero values into eeprom memory and reading them back
err_t run_first_pass( eeprom8_t* ctx, uint8_t* write_buf, uint8_t* read_buf )
{
    // Fill write buffer with zeros
    memset( write_buf, 0, TEST_NBYTES );
    
    // Fill whole page with zeros using page write operation
    eeprom8_write_enable( ctx );
    if ( EEPROM8_ERROR == eeprom8_write_page( ctx, addr_offset, write_buf ) )
    {
        log_error( &logger, " Write Page Failed " );
        return EEPROM8_ERROR;
    }
    cnt += EEPROM8_NBYTES_PAGE;
    
    // Fill remaining adresses with zero using byte write operation
    addr_offset += EEPROM8_NBYTES_PAGE;

    while( cnt < TEST_NBYTES )
    {
        if ( EEPROM8_ERROR == eeprom8_write_byte( ctx, addr_offset++, 0 ) )
        {
            log_error( &logger, " Write %d. Byte Failed ", ( uint16_t ) cnt );
            return EEPROM8_ERROR;
        }
        cnt++;
        Delay_10ms( );
    }
    eeprom8_write_protect( ctx );

    Delay_1sec( );
    
    // Read defined number of bytes starting from the test memory location
    addr_offset = TEST_MEM_LOCATION;
    if ( EEPROM8_ERROR == eeprom8_read_sequential( ctx, addr_offset, TEST_NBYTES, read_buf ) )
    {
         log_error( &logger, "Read Sequential Failed" );
         return EEPROM8_ERROR;
    }
  
    // compare written and read buffers and log data in case of a match 
    if ( memcmp( write_buf, read_buf, sizeof( write_buf ) ) == 0 )
    {
        log_printf( &logger, 
                    " \r\nFirst pass: reading %d bytes data starting from eeprom address 0x%x\r\n ", 
                    ( uint16_t ) TEST_NBYTES, 
                    ( uint32_t ) TEST_MEM_LOCATION );
        for ( cnt = 0; cnt < TEST_NBYTES; cnt++ )
        {
            log_printf( &logger, " %d", ( uint16_t ) read_buf[ cnt ] );
            Delay_ms ( 50 );
        }
    
        log_printf( &logger, "\r\n\r\n" );
    }
    else
    {
        return EEPROM8_ERROR;
    }
    return EEPROM8_OK;
}

// Second pass: writing incremental values into eeprom memory and reading them back
err_t run_second_pass( eeprom8_t* ctx, uint8_t* write_buf, uint8_t* read_buf )
{
    for ( cnt = 0; cnt < TEST_NBYTES; cnt++ )
    {
        write_buf[ cnt ] = cnt + 1;
    }
    // Write buffer data using page write operation
    cnt = 0;
    eeprom8_write_enable( ctx );
    if ( EEPROM8_ERROR == eeprom8_write_page( ctx, addr_offset, write_buf ) )
    {
        log_error( &logger, " Write Page Failed ");
        return EEPROM8_ERROR;
    }
    cnt += EEPROM8_NBYTES_PAGE;
    
    // Write remaining buffer data using byte write operation
    addr_offset += EEPROM8_NBYTES_PAGE;

    while ( cnt < TEST_NBYTES )
    {
        if ( EEPROM8_ERROR == eeprom8_write_byte( ctx, addr_offset++, write_buf[ cnt++ ] ) )
        {
            log_error( &logger, " Write %d. Byte Failed ", ( uint16_t ) cnt );
            return EEPROM8_ERROR;
        }
        Delay_10ms( );
    }
    eeprom8_write_protect( ctx );

    Delay_ms ( 1000 );
    
    // Read bytes of the page size starting from the test memory location
    addr_offset = TEST_MEM_LOCATION;
    if ( EEPROM8_ERROR == eeprom8_read_sequential( ctx, addr_offset, EEPROM8_NBYTES_PAGE, read_buf ) )
    {
        log_error( &logger, " Read Sequential Failed " );
        return EEPROM8_ERROR;
    }
    
    // Read two bytes with random byte read operation
    addr_offset += EEPROM8_NBYTES_PAGE;
    cnt = EEPROM8_NBYTES_PAGE;

    if( EEPROM8_ERROR == eeprom8_read_random_byte( ctx, addr_offset, &read_buf[ cnt++ ] ) )
    {
        log_error( &logger, " Read %d. Random Byte Failed ", ( uint16_t ) cnt-1 );
        return EEPROM8_ERROR;
    }
    ++addr_offset;
    if( EEPROM8_ERROR == eeprom8_read_random_byte( ctx, addr_offset, &read_buf[ cnt++ ] ) )
    {
        log_error( &logger, " Read %d. Random Byte Failed ", ( uint16_t ) cnt-1 );
        return EEPROM8_ERROR;
    }
    
    // Read the rest of the bytes with current address read operation
    while ( cnt < TEST_NBYTES )
    {
        if( EEPROM8_ERROR == eeprom8_read_current_byte( ctx, &read_buf[ cnt++ ] ) )
        {
            log_error( &logger, " Read %d. Current Byte Failed ", ( uint16_t ) cnt-1 );
            return EEPROM8_ERROR;
        }
    }
    // compare written and read buffers and log data in case of a match
    if ( memcmp( write_buf, read_buf, TEST_NBYTES ) == 0 )
    {
        log_printf( &logger, 
                    " \r\nSecond pass: reading %d bytes data starting from eeprom address 0x%x\r\n ", 
                    ( uint16_t ) TEST_NBYTES, 
                    ( uint32_t ) TEST_MEM_LOCATION );
        for ( cnt = 0; cnt < TEST_NBYTES; cnt++ )
        {
            log_printf( &logger, " %d", ( uint16_t )read_buf[ cnt ] );
            Delay_ms ( 50 );
        }
    
        log_printf( &logger, "\r\n\r\n" );
    }
    else
    {
        return EEPROM8_ERROR;
    }
    return EEPROM8_OK;
}

// ------------------------------------------------------------------------ END
