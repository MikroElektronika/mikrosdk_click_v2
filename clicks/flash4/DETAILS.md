
---
# Flash 4 click

Flash 4 click is a perfect solution for the mass storage option in various embedded applications. With fast performance being one of its key features, Flash 4 click can also be used for the code shadowing, execute-in-place (XIP), and data storage.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/flash4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/flash-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Flash4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Flash4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void flash4_cfg_setup ( flash4_cfg_t *cfg ); 
 
- Initialization function.
> FLASH4_RETVAL flash4_init ( flash4_t *ctx, flash4_cfg_t *cfg );

- Generic transfer function.
> void flash4_generic_transfer ( flash4_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );


#### Example key functions :

- Function for read Manufacturer ID.
> void flash4_read_manufacturer_id ( flash4_t *ctx, uint8_t *device_id );
 
- Write command function.
> void flash4_write_command ( flash4_t *ctx, uint8_t cmd );

- Read Flash with 4 byte address function.
> void flash4_read_flash_4 ( flash4_t *ctx, uint8_t *out_data, uint32_t addr, uint8_t n_data );

## Examples Description

> This example demonstrates the use of Flash 4 Click board. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and enables the click board, then checks the communication by reading the device and manufacturer IDs.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    flash4_cfg_t cfg;

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

    flash4_cfg_setup( &cfg );
    FLASH4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flash4_init( &flash4, &cfg );
    
    flash4_reset( &flash4 );
    
    Delay_ms ( 1000 );
    
    flash4_read_manufacturer_id( &flash4, device_id );
    
    if ( device_id[ 0 ] != FLASH4_MANUFACTURER_ID || device_id[ 1 ] != FLASH4_DEVICE_ID )
    {
        log_error( &logger, "WRONG ID READ" );
        log_printf( &logger, "Please restart your system.\r\n" );
        for( ; ; );
    }
    Delay_ms ( 1000 );
}
  
```

### Application Task

> Erases sector memory starting from 0x00001234 address, then writes a desired message
> to the same address. After that, verifies if the message is written correctly by reading 
> it back and displaying it to the USB UART every 5 seconds.

```c

void application_task ( void )
{
    char read_buffer[ 10 ] = { 0 };

    flash4_write_command( &flash4, FLASH4_CMD_WRITE_ENABLE_WREN );
    log_printf( &logger, "--- Erase chip --START-- \r\n" );
    flash4_sector_erase_4( &flash4,  0x00001234 );
    while ( flash4_check_wip( &flash4 ) );
    log_printf( &logger, "--- Erase chip --DONE-- \r\n" );
    
    flash4_write_command( &flash4, FLASH4_CMD_WRITE_ENABLE_WREN );
    flash4_page_program_4( &flash4, DEMO_MESSAGE, 0x00001234, strlen( DEMO_MESSAGE ) );
    while ( flash4_check_wip( &flash4 ) );
    Delay_100ms( );
    
    flash4_read_flash_4( &flash4, read_buffer, 0x00001234, strlen( DEMO_MESSAGE ) );
    while ( flash4_check_wip( &flash4 ) );
    
    log_printf( &logger, "--- Read buffer : %s\r\n", read_buffer );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Flash4

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
