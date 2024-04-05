
---
# Cap Extend click

Cap Extend click is a mikroBUS add-on board with a SEMTECH SX8633 low power, capacitive button touch controller. It has 12 pins for connecting capacitive inputs (either touch-buttons or proximity sensors).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/capextend_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/cap-extend-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

We provide a library for the CapExtend Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for CapExtend Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void capextend_cfg_setup ( capextend_cfg_t *cfg ); 
 
- Initialization function.
> CAPEXTEND_RETVAL capextend_init ( capextend_t *ctx, capextend_cfg_t *cfg );

- Click Default Configuration function.
> void capextend_default_cfg ( capextend_t *ctx );

#### Example key functions :

- This function does a software reset of the click module.
> void capextend_reset ( capextend_t *ctx );
 
- This function reads the MSB button map data.
> int8_t capextend_read_msb_buttons ( capextend_t *ctx );

- This function reads the LSB button map data.
> int8_t capextend_read_lsb_buttons ( capextend_t *ctx );

## Examples Description

> This example showcases the initialization and configuration of the logger and click modules
  and later on shows how to read and display the 16-bit button map ( LSB + MSB ). 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the click and logger modules. 

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    capextend_cfg_t cfg;

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

    capextend_cfg_setup( &cfg );
    CAPEXTEND_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capextend_init( &capextend, &cfg );
    capextend_reset( &capextend );
}
  
```

### Application Task

> This function collects map data and displays the 16-bit button map, where each bit that has
  the value 1 represents a button that has been pressed. 

```c

void application_task ( )
{
    uint8_t msb;
    uint8_t lsb;

    msb = capextend_read_msb_buttons( &capextend );
    lsb = capextend_read_lsb_buttons( &capextend );

    // LSB

    log_printf( &logger, " * ---------LSB--------- * \r\n" );
    log_printf( &logger, " * | %d", ( lsb & 0x80 ) >> 7 );
    log_printf( &logger, " %d", ( lsb & 0x40 ) >> 6 );
    log_printf( &logger, " %d", ( lsb & 0x20 ) >> 5 );
    log_printf( &logger, " %d |",( lsb & 0x10 ) >> 4 );
    log_printf( &logger, " %d", ( lsb & 0x08 ) >> 3 );
    log_printf( &logger, " %d", ( lsb & 0x04 ) >> 2 );
    log_printf( &logger, " %d", ( lsb & 0x02 ) >> 1 );
    log_printf( &logger, " %d | * \r\n", lsb & 0x01 );

    // MSB

    log_printf( &logger, " * ---------MSB--------- * \r\n" );
    log_printf( &logger, " * | %d", ( msb & 0x80 ) >> 7 );
    log_printf( &logger, " %d", ( msb & 0x40 ) >> 6 );
    log_printf( &logger, " %d", ( msb & 0x20 ) >> 5 );
    log_printf( &logger, " %d |",( msb & 0x10 ) >> 4 );
    log_printf( &logger, " %d", ( msb & 0x08 ) >> 3 );
    log_printf( &logger, " %d", ( msb & 0x04 ) >> 2 );
    log_printf( &logger, " %d", ( msb & 0x02 ) >> 1 );
    log_printf( &logger, " %d | * \r\n", msb & 0x01 );

    log_printf( &logger, " * ----------------------- * \r\n\r\n" );
    Delay_ms ( 500 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.CapExtend

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
