/*!
 * @file main.c
 * @brief Flash8 Click example
 *
 * # Description
 * This library contains API for Flash 8 Click driver.
 * The library using SPI serial interface.
 * The library also includes a function for write and read memory
 * as well as write protection control functions.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 * After driver initialization and default setting, 
 * involves disabling write protection and hold, 
 * the app writes demo_data string ( mikroE ) starting 
 * from the selected row_address of the 123 ( 0x0000007B ) 
 * and column_address of the 456 ( 0x01C8 ).
 *
 * ## Application Task
 * This is an example that shows the use of a Flash 8 Click board™.
 * The app reads a data string, which we have previously written to memory, 
 * starting from the selected row_address of the 123 ( 0x0000007B ) 
 * and column_address of the 456 ( 0x01C8 ).
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "flash8.h"

static flash8_t flash8;
static log_t logger;

static uint8_t manufacture_id;
static uint8_t device_id;
static uint8_t organization_id;
static uint8_t feature_status_out;
static uint8_t demo_data[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13 ,10 , 0 };
static uint8_t rx_data[ 9 ] = { 0 };
static feature_cfg_t feature_data;

void application_init ( void ) 
{
    log_cfg_t log_cfg;        /**< Logger config object. */
    flash8_cfg_t flash8_cfg;  /**< Click config object. */

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
    flash8_cfg_setup( &flash8_cfg );
    FLASH8_MAP_MIKROBUS( flash8_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == flash8_init( &flash8, &flash8_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    flash8_default_cfg ( &flash8 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
    
    flash8_read_id( &flash8, &manufacture_id, &device_id, &organization_id );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "  Manufacture ID  : 0x%.2X\r\n", ( uint16_t) manufacture_id );
    log_printf( &logger, "  Device ID       : 0x%.2X\r\n", ( uint16_t) device_id );
    log_printf( &logger, "  Organization ID : 0x%.2X\r\n", ( uint16_t) organization_id );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 100 );   
      
    flash8_sw_reset( &flash8, &feature_status_out );
    if ( feature_status_out & FLASH8_GET_PRG_F_PROGRAM_FAIL ) 
    {
        log_printf( &logger, "\tProgram Fail \r\n" );    
    } 
    else 
    {
        log_printf( &logger, "\tProgram Pass \r\n" );    
    }
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    feature_data.brwd   = FLASH8_SET_BRWD_ENABLE;
    feature_data.bl     = FLASH8_SET_BL_ALL_UNLOCKED;
    feature_data.idr_e  = FLASH8_SET_IDR_E_NORMAL_OPERATION;
    feature_data.ecc_e  = FLASH8_SET_ECC_E_INTERNAL_ECC_ENABLE;
    feature_data.prt_e  = FLASH8_SET_PRT_E_NORMAL_OPERATION;
    feature_data.hse    = FLASH8_SET_HSE_HIGH_SPEED_MODE_ENABLE;
    feature_data.hold_d = FLASH8_SET_HOLD_D_HOLD_IS_ENABLED;
    feature_data.wel    = FLASH8_SET_WEL_WRITE_ENABLE;
    flash8_set_config_feature( &flash8, feature_data );
    Delay_ms ( 100 );
    
    flash8_block_erase( &flash8, 123, &feature_status_out );
    if ( feature_status_out & FLASH8_GET_ERS_F_ERASE_FAIL ) 
    {
        log_printf( &logger, "\tErase Fail \r\n" );    
    } 
    else 
    {
        log_printf( &logger, "\tErase Pass \r\n" );    
    }
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "   Write data : %s", demo_data );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "        Write status:\r\n"  );
    flash8_write_memory( &flash8, 123, 456, &demo_data[ 0 ], 9, &feature_status_out );
    if ( feature_status_out & FLASH8_GET_OIP_BUSY_STATE ) 
    {
        log_printf( &logger, " Operation is in progress.\r\n" );    
    } 
    else 
    {
        log_printf( &logger, " Operation is not in progress.\r\n" );    
    }
    log_printf( &logger, "- - - - - - - - - - -  - -\r\n" );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "    Check data ready...\r\n" );  
    while ( FLASH8_GET_OIP_READY_STATE != feature_status_out ) 
    {
        flash8_get_feature( &flash8, FLASH8_FEATURE_C0, &feature_status_out );
        log_printf( &logger, "\tBusy state.\r\n" );  
        Delay_ms ( 100 );    
    }
    
    if ( FLASH8_GET_OIP_READY_STATE == feature_status_out ) 
    {
        log_printf( &logger, "\tReady state.\r\n" );    
    }
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{   
    flash8_read_memory( &flash8, 123, 456, &rx_data[ 0 ], 9, &feature_status_out );
    log_printf( &logger, "    Read data : %s", rx_data );
    log_printf( &logger, "--------------------------\r\n" );
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
