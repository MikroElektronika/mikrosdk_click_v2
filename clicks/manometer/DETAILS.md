
# Manometer Click

Manometer Click carries a piezoresistive silicon pressure sensor,the HSCMAND060PA3A3 from Honeywell, an industry-leading module with an extremely high accuracy of ±0.25%FSS BFSL.>

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/manometer_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/manometer-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Manometer Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Manometer Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void manometer_cfg_setup ( manometer_cfg_t *cfg ); 
 
- Initialization function.
> MANOMETER_RETVAL manometer_init ( manometer_t *ctx, manometer_cfg_t *cfg );

#### Example key functions :

- Generic write function.
> void manometer_generic_write ( manometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
 
- Generic read function.
> void manometer_generic_read ( manometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

- Function read 16-bit data and convert to pressure in mbar.
> float manometer_get_pressure ( manometer_t *ctx );

## Examples Description
 
> This application carries a piezoresistive silicon pressure       sensor. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - I2C and start write log to      Usart Terminal. 

```c

void application_init ( void )
{
 log_cfg_t log_cfg;
    manometer_cfg_t cfg;

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

    manometer_cfg_setup( &cfg );
    MANOMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    manometer_init( &manometer, &cfg );
}
  
```

### Application Task

> This is a example which demonstrates the use of Manometer Click board.

```c

void application_task ( void )
{
 float read_data;

    read_data = manometer_get_pressure( &manometer );
    Delay_10ms( );

    log_printf( &logger, " Pressure: %d mbar\r\n", read_data );

    read_data = manometer_get_temperature( &manometer );
    Delay_10ms( );

    log_printf( &logger, " Temperature:  %d C\r\n", read_data );
    log_printf( &logger, "--------------------------\r\n" );

    Delay_1sec( );
    Delay_1sec( );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Manometer

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
