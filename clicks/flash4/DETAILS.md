
# Flash 4 click

Flash 4 click is a perfect solution for the mass storage option in various embedded applications. With fast performance being one of its key features, Flash 4 click can also be used for the code shadowing, execute-in-place (XIP), and data storage.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/flash4_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/flash-4-click>)

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
> void flash4_generic_transfer ( flash4_t *ctx, spi_master_transfer_data_t *block );


#### Example key functions :

- Functions for read Manufacturer ID.
> void flash4_read_manufacturer_id ( flash4_t *ctx, uint8_t *device_id );
 
- Functions for Read Identification.
> void flash4_read_identification ( flash4_t *ctx, uint8_t *out_data, uint8_t n_data );

- Functions for Read Electronic Signature.
> uint8_t flash4_read_electronic_id ( flash4_t *ctx );

## Examples Description

 
> This application for the mass storage option in various embedded applications.
 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init and reset device 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    flash4_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    flash4_cfg_setup( &cfg );
    FLASH4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flash4_init( &flash4, &cfg );
}
  
```

### Application Task

> Erases memory at 0x00001234.
   Writes a message (MikroElektronika) to address 0x00001234.
   Then reads the data from the address 0x00001234. 

```c

void application_task ( void )
{
uint8_t data_buffer[ 17 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 'l', 'e', 'k', 't', 'r', 'o', 'n', 'i', 'k', 'a', 0 };
    char read_buffer[ 20 ] = { 0 };

    flash4_write_command( &flash4, FLASH4_CMD_WRITE_ENABLE_WREN );
    log_printf( &logger, "--- Erase chip --START-- \r\n" );
    flash4_4sector_erase( &flash4,  0x00001234 );
    while ( flash4_check_wip ( &flash4 ) );
    log_printf( &logger, "--- Erase chip --DONE-- \r\n" );
    
    flash4_write_command( &flash4, FLASH4_CMD_WRITE_ENABLE_WREN );
    flash4_4_page_program( &flash4, &data_buffer[ 0 ], 0x00001234, 16);
    while ( flash4_check_wip ( &flash4 ) );
    Delay_100ms( );
    
    flash4_4_read_flash( &flash4, &read_buffer[0], 0x00001234, 16);
    while ( flash4_check_wip ( &flash4 ) );
    log_printf( &logger, "--- Read buffer : %s \r\n", read_buffer );
    
    Delay_ms( 7000 );
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
