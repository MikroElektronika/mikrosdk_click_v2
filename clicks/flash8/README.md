\mainpage Main Page

---
# Flash 8 click

> Flash 8 Click is a compact add-on board representing a highly reliable memory solution. This board features the GD5F2GQ5UEYIGR, a 2Gb high-density non-volatile memory storage solution for embedded systems from GigaDevice Semiconductor. It is based on an industry-standard NAND Flash memory core, representing an attractive alternative to SPI-NOR and standard parallel NAND Flash with advanced features. The GD5F2GQ5UEYIGR also has advanced security features (8K-Byte OTP region), software/hardware write protection, can withstand many write cycles (minimum 100k), and has a data retention period greater than ten years.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/flash8_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/flash-8-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : May 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Flash8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Flash8 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This library contains API for Flash 8 Click driver.
> The library using SPI serial interface.
> The library also includes a function for write and read memory
> as well as write protection control functions.

**The demo application is composed of two sections :**

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
    Delay_ms( 100 );
    
    flash8_read_id( &flash8, &manufacture_id, &device_id, &organization_id );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "  Manufacture ID  : 0x%.2X\r\n", ( uint16_t) manufacture_id );
    log_printf( &logger, "  Device ID       : 0x%.2X\r\n", ( uint16_t) device_id );
    log_printf( &logger, "  Organization ID : 0x%.2X\r\n", ( uint16_t) organization_id );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 100 );   
      
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
    Delay_ms( 1000 );
    
    feature_data.brwd   = FLASH8_SET_BRWD_ENABLE;
    feature_data.bl     = FLASH8_SET_BL_ALL_UNLOCKED;
    feature_data.idr_e  = FLASH8_SET_IDR_E_NORMAL_OPERATION;
    feature_data.ecc_e  = FLASH8_SET_ECC_E_INTERNAL_ECC_ENABLE;
    feature_data.prt_e  = FLASH8_SET_PRT_E_NORMAL_OPERATION;
    feature_data.hse    = FLASH8_SET_HSE_HIGH_SPEED_MODE_ENABLE;
    feature_data.hold_d = FLASH8_SET_HOLD_D_HOLD_IS_ENABLED;
    feature_data.wel    = FLASH8_SET_WEL_WRITE_ENABLE;
    flash8_set_config_feature( &flash8, feature_data );
    Delay_ms( 100 );
    
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
    Delay_ms( 1000 );
    
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
    Delay_ms( 1000 );
    
    log_printf( &logger, "    Check data ready...\r\n" );  
    while ( FLASH8_GET_OIP_READY_STATE != feature_status_out ) 
    {
        flash8_get_feature( &flash8, FLASH8_FEATURE_C0, &feature_status_out );
        log_printf( &logger, "\tBusy state.\r\n" );  
        Delay_ms( 100 );    
    }
    
    if ( FLASH8_GET_OIP_READY_STATE == feature_status_out ) 
    {
        log_printf( &logger, "\tReady state.\r\n" );    
    }
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 100 );
}

```

### Application Task

> This is an example that shows the use of a Flash 8 Click board™.
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
    Delay_ms( 2000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash8

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
