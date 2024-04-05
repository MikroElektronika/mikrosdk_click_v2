\mainpage Main Page
 
 

---
# Flash 3 click

Flash 3 Click is a mikroBUS add-on board for adding more Flash Memory to your target board microcontroller. It carries an ISSI IS25LP128 IC with 128 Mbit capacity.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/flash3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/flash-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Flash3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Flash3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void flash3_cfg_setup ( flash3_cfg_t *cfg ); 
 
- Initialization function.
> FLASH3_RETVAL flash3_init ( flash3_t *ctx, flash3_cfg_t *cfg );

- Generic transfer function.
> void flash3_generic_transfer ( flash3_t *ctx, spi_master_transfer_data_t *block );


#### Example key functions :

- Pause function.
> void flash3_pause ( flash3_t *ctx );
 
- Unpause function.
> void flash3_unpause ( flash3_t *ctx );

- Unpause function.
> void flash3_unpause ( flash3_t *ctx );

## Examples Description
 
> This applicaion adding more flash memory. 

**The demo application is composed of two sections :**

### Application Init 

> Initalizes device, Flash 3 click board and makes an initial log. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    flash3_cfg_t cfg;

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

    flash3_cfg_setup( &cfg );
    FLASH3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flash3_init( &flash3, &cfg );

    Delay_ms ( 100 );
    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "  Flash  3  Click  \r\n" );
    log_printf( &logger, "-------------------\r\n" );
    flash3_setting( &flash3 );
    Delay_ms ( 100 );
    log_printf( &logger, "   Initialized     \r\n" );
    log_printf( &logger, "------------------- \r\n" );
}
  
```

### Application Task

> This is an example that shows the capabilities of the Flash 3 click by
  writing into memory array of a Flash 3 click board and reading same data from memory array.

```c

void application_task ( void )
{
    char val_in[ 8 ] = { 0x4D, 0x49, 0x4B, 0x52, 0x4F, 0x45, 0x00 };
    char val_out[ 8 ] = { 0 };

    log_printf( &logger, "\r\n ____________________ \r\n" );
    log_printf( &logger, "Begin demonstration! \r\n\r\n" );
    
    
    log_printf( &logger, "Writing : %s\r\n", val_in );
    flash3_write( &flash3, 0x000000, &val_in[ 0 ], 6 );
    Delay_ms ( 100 );
    log_printf( &logger, "------------------ \r\n" );

    log_printf( &logger, "Reading : %s\r\n", val_in );
    flash3_normal_read( &flash3, 0x000000, &val_in[ 0 ], 6 );
    Delay_ms ( 100 );
    log_printf( &logger, "------------------ \r\n" );

    log_printf( &logger, "Erasing... \r\n" );
    flash3_sector_erase( &flash3, 0x000000 );
    Delay_ms ( 300 );
    log_printf( &logger, "Erased!" );
    Delay_ms ( 100 );
    log_printf( &logger, "------------------ \r\n"  );

    log_printf( &logger, "Reading : %s\r\n", val_out );
    flash3_fast_read( &flash3, 0x000000, &val_out[ 0 ], 6 );
    Delay_ms ( 100 );
    log_printf( &logger, "------------------ \r\n" );

    log_printf( &logger, "Demonstration over!" );
    log_printf( &logger, "\r\n ___________________ \r\n" );
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
- Click.Flash3

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
