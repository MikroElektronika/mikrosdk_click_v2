
---
# Flash 8 Click

> [Flash 8 Click](https://www.mikroe.com/?pid_product=MIKROE-5293) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5293&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : May 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains API for Flash 8 Click driver.
> The library using SPI serial interface.
> The library also includes a function for write and read memory
> as well as write protection control functions.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash8

### Example Key Functions

- `flash8_cfg_setup` Config Object Initialization function.
```c
void flash8_cfg_setup ( flash8_cfg_t *cfg );
```

- `flash8_init` Initialization function.
```c
err_t flash8_init ( flash8_t *ctx, flash8_cfg_t *cfg );
```

- `flash8_default_cfg` Click Default Configuration function.
```c
void flash8_default_cfg ( flash8_t *ctx );
```

- `flash8_write_memory` Flash 8 write memory function.
```c
err_t flash8_write_memory ( flash8_t *ctx, uint32_t row_address, uint16_t column_address, uint8_t *data_in, uint16_t len, uint8_t *feature_status_out );
```

- `flash8_read_memory` Flash 8 read memory function.
```c
err_t flash8_read_memory ( flash8_t *ctx, uint32_t row_address, uint16_t column_address, uint8_t *data_out, uint16_t len, uint8_t *feature_status_out );
```

- `flash8_read_id` Flash 8 read ID function.
```c
err_t flash8_read_id ( flash8_t *ctx, uint8_t *manufacture_id, uint8_t *device_id, uint8_t *organization_id );
```

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization and default setting, 
> involves disabling write protection and hold, 
> the app writes demo_data string ( mikroE ) starting 
> from the selected row_address of the 123 ( 0x0000007B ) 
> and column_address of the 456 ( 0x01C8 ).

```c
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
```

### Application Task

> This is an example that shows the use of a Flash 8 Click board&trade;.
> The app reads a data string, which we have previously written to memory, 
> starting from the selected row_address of the 123 ( 0x0000007B ) 
> and column_address of the 456 ( 0x01C8 ).
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{   
    flash8_read_memory( &flash8, 123, 456, &rx_data[ 0 ], 9, &feature_status_out );
    log_printf( &logger, "    Read data : %s", rx_data );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
