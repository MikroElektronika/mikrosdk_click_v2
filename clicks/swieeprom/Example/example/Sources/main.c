/*!
 * @file main.c
 * @brief SWI EEPROM Click Example.
 *
 * # Description
 * This application shows capability of SWI EEPROM Click board. 
 * It checks if device is present, initializes it and show it's
 * functionality to read from memory and write to memory.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of log and communication pin. Checks if device
 * is present and then it's slave address, and checks communication 
 * with checking devices ID.
 *
 * ## Application Task
 * Sends WRITE_DATA_STRING to the device, starting from START_MEMORY_ADDRESS.
 * Then reads that written data and checks if it matches with written data.
 * After that clears that same data and then reads it again to check if data is cleared.
 *
 * *note:*
 * This application is written for Legacy profiles for ARM{STM32F407ZG}, 
 * PIC{PIC18F97J94}, PIC32{PIC32MX975F512L} and specifically for MIKROBUS 1.
 * 
 * @author Luka Filipovic
 *
 */

#include "stdint.h"
#include "log.h"
#include "swieeprom.h"

static swieeprom_t swieeprom;

void application_init ( void )
{
    log_init( );
    log_line( " > Application init <" );
    if ( swieeprom_init( &swieeprom ) )
    {
        log_line( " > ERROR!" );
        for( ; ; );
    }
    else
    {
        log_line( " > Device init done!" );
    }
    
    //read id
    if ( swieeprom_read_id( &swieeprom ) )
    {
        log_line( " > ID ERROR!" );
    }
    else
    {
        log_line( " > ID OK!" );
    }
    
    Delay_ms( 500 );
    log_line( " > Application Task <" );
    log_line( "******************************************" );
}

static void application_task ( void )
{
    #define WRITE_DATA_STRING       "MikroE"
    #define START_MEMORY_ADDRESS    0x10
    
    //write memory
    if ( swieeprom_write_data_to_memory( &swieeprom, START_MEMORY_ADDRESS, WRITE_DATA_STRING, 6 ) )
    {
        log_line( " > Write ERROR!" );
    }
    else
    {
        log_line( " > Write done!" );
    }
    Delay_ms( 1000 );
    
    //read_memory
    uint8_t rx_buf[ 8 ] = { 0 };
    if ( swieeprom_read_data_from_memory( &swieeprom, START_MEMORY_ADDRESS, rx_buf, 6 ) )
    {
        log_line( " > Read ERROR!" );
    }
    else
    {
        log_txt( " > Read data: " );
        log_line( rx_buf );
        if ( 0 != strstr( rx_buf, WRITE_DATA_STRING ) )
        {
            log_line( " > Data Match!" );
        }
        else
        {
            log_line( " > Data Mismatch!" );
        }
    }
    Delay_ms( 1000 );
    
    //clear memory
    if ( swieeprom_clear_data_from_memory( &swieeprom, START_MEMORY_ADDRESS, 6 ) )
    {
        log_line( " > Clear ERROR!" );
    }
    else
    {
        log_line( " > Clear done!" );
    }
    Delay_ms( 1000 );
    
    //read_memory
    uint8_t rec_buf[ 8 ] = { 0 };
    if ( swieeprom_read_data_from_memory( &swieeprom, START_MEMORY_ADDRESS, rec_buf, 6 ) )
    {
        log_line( " > Read ERROR!" );
    }
    else
    {
        log_txt( " > Read data: " );
        log_line( rec_buf );
        
        if ( 0 != strstr( rec_buf, WRITE_DATA_STRING ) )
        {
            log_line( " > Data not cleared!" );
        }
        else
        {
            log_line( " > Data cleared!" );
        }
    }
    
    log_line( "******************************************" );
    Delay_ms( 3000 );
}

void main( void )
{
    application_init(  );
    while ( 1 )
    {
        application_task(  );
    }
}






