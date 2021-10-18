\mainpage Main Page
 
 

---
# UV click

Design devices that warn you of excesive ultraviolet radiation levels with UV click. This click boards carries the ML8511 IC that is sensitive to UV-A (365-315 nm) and UV-B (315-280 nm) rays.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uv_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/uv-click)

---


#### Click library 

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Uv Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Uv Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void uv_cfg_setup ( uv_cfg_t *cfg ); 
 
- Initialization function.
> UV_RETVAL uv_init ( uv_t *ctx, uv_cfg_t *cfg );

- Click Default Configuration function.
> void uv_default_cfg ( uv_t *ctx );


#### Example key functions :

- Read 12-bit UV data function.
> uint16_t uv_read_data ( uv_t *ctx );
 
- Set power mode function.
> void uv_set_poewr_mode ( uv_t *ctx, uint8_t pwr_en );

## Examples Description

> 
> This is a example which demonstrates the use of UV Click board.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Configuring clicks and log objects.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    uv_cfg_t cfg;

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
    log_printf( &logger, "- Application Init -\r\n" );

    //  Click initialization.

    uv_cfg_setup( &cfg );
    UV_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uv_init( &uv, &cfg );
    
    uv_default_cfg ( &uv );
    Delay_ms( 100 );
    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "      UV Click\r\n" );
    log_printf( &logger, "--------------------\r\n" );
}
  
```

### Application Task

>
> This is a example which demonstrates the use of UV Click board.
> Reads 12-bit UV data.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart is changed for every 5 sec.
> 

```c

void application_task ( void )
{
    uint16_t uv_data;
    
    uv_data = uv_read_data ( &uv );
    
    log_printf( &logger, "     UV : %4d\r\n", uv_data );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms( 5000 );
}  

```

## Note

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Uv

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
