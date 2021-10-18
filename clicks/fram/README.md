\mainpage Main Page
 
 

---
# Fram click

FRAM click is a Click board™ that carries a ferroelectric RAM module. Ferroelectric RAM, also known as FRAM, is a non-volatile memory type, with characteristics comparable to much faster DRAM memory modules.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/fram_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/fram-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Fram Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Fram Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void fram_cfg_setup ( fram_cfg_t *cfg ); 
 
- Initialization function.
> FRAM_RETVAL fram_init ( fram_t *ctx, fram_cfg_t *cfg );

- Click Default Configuration function.
> void fram_default_cfg ( fram_t *ctx );


#### Example key functions :

- This function that sends write enable command to the chip.
> void fram_write_enable ( fram_t *ctx );
 
- This function reads sequential memory locations to buffer.
> void fram_read ( fram_t *ctx, uint16_t address, uint8_t *buffer, uint16_t count );

- This function writes to sequential memory locations from buffer.
> void fram_write ( fram_t *ctx, uint16_t address, uint8_t *buffer, uint16_t count );

## Examples Description

> This app writing data to click memory.

**The demo application is composed of two sections :**

### Application Init 

> Initialization device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    fram_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    fram_cfg_setup( &cfg );
    FRAM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fram_init( &fram, &cfg );
    fram_erase_all( &fram );
}
  
```

### Application Task

> Writing data to click memory and displaying the read data via UART. 

```c

void application_task ( void )
{
    char wr_data[ 10 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };
    char rd_data[ 10 ];

    log_printf( &logger, "Writing MikroE to  Fram memory, from address 0x0150: \r\n" );
    fram_write( &fram, 0x0150, &wr_data[ 0 ], 9 );
    log_printf( &logger, "Reading 9 bytes of Fram memory, from address 0x0150: \r\n" );
    fram_read( &fram, 0x0150, &rd_data[ 0 ], 9 );
    log_printf( &logger, "Data read: %c \r\n", rd_data );
    Delay_ms( 1000 );
}
 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Fram

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
