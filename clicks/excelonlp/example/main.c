/*!
 * \file 
 * \brief ExcelonLP Click example
 * 
 * # Description
 * This application writes in RAM memory and read from RAM memory.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Device init
 * 
 * ## Application Task  
 * Reads device ID, writes 6-bytes (MikroE) to memory and reads 6-bytes from memory
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "excelonlp.h"

// ------------------------------------------------------------------ VARIABLES

static excelonlp_t excelonlp;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    uint8_t out_buf[ 20 ] = { 0 };
    uint8_t cnt;
    
    log_cfg_t log_cfg;
    excelonlp_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    excelonlp_cfg_setup( &cfg );
    EXCELONLP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    excelonlp_init( &excelonlp, &cfg );
    
    log_printf( &logger, "Read Device ID: " );
    excelonlp_send_command( &excelonlp, EXCELONLP_OPCODE_SET_WRITE_ENABLE_LATCH );
    excelonlp_read_data( &excelonlp, EXCELONLP_OPCODE_READ_DEVICE_ID, out_buf, 9 );

    for ( cnt = 0; cnt < 9; cnt++ )
    {
        log_printf( &logger, " 0x%x - ", out_buf[ cnt ] );
        Delay_100ms();
    }
    log_printf( &logger, "\r\n" );
}

void application_task ( )
{
    uint8_t cnt;
    char memory_data[ 3 ];
    uint8_t send_buffer[ 7 ] = { 'M',  'i', 'k',  'r',  'o',  'E',  0 };
    uint32_t memory_address = 0x00000055;

   log_printf( &logger, "Write MikroE data.\r\n" );
   excelonlp_send_command( &excelonlp, EXCELONLP_OPCODE_SET_WRITE_ENABLE_LATCH );
   for ( cnt = 0; cnt < 6; cnt++ )
   {
        excelonlp_send_command( &excelonlp, EXCELONLP_OPCODE_SET_WRITE_ENABLE_LATCH );
        excelonlp_write_memory_data( &excelonlp, EXCELONLP_OPCODE_WRITE_MEMORY_DATA, memory_address++, send_buffer[ cnt ] );
        Delay_100ms();
   }
   memory_address = 0x00000055;
   log_printf( &logger, "Read memory data: " );
   for ( cnt = 0; cnt < 6; cnt++ )
   {
       memory_data[ cnt ] = excelonlp_read_memory_data( &excelonlp, EXCELONLP_OPCODE_READ_MEMORY_DATA, memory_address++ );
       log_printf( &logger, " %c", memory_data[ cnt ]  );
       Delay_100ms();
   }
   log_printf( &logger, "\r\n \r\n" );
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
