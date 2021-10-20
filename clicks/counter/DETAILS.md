

---
# Counter click

Counter click carries an LS7366R 32-bit quadrature counter. The top of the board has a pinout for interfacing with incremental encoders. The interface has ENCA and ENCB pins, along with ENCI, which is a programmable index.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/counter_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/counter-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Counter Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Counter Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void counter_cfg_setup ( counter_cfg_t *cfg ); 
 
- Initialization function.
> COUNTER_RETVAL counter_init ( counter_t *ctx, counter_cfg_t *cfg );

- Click Default Configuration function.
> void counter_default_cfg ( counter_t *ctx );


#### Example key functions :

- This function reads CNTR, using click object.
> int32_t counter_read_cntr ( counter_t *ctx );
 
- This function reads STR, using click object.
> uint8_t counter_read_str ( counter_t *ctx );

- This function reads OTR, using click object.
> int32_t counter_read_otr ( counter_t *ctx );

## Examples Description

> This application measures the speed and the position of the DC motor shafts.


**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init and chip init


```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    counter_cfg_t cfg;

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

    counter_cfg_setup( &cfg );
    COUNTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    counter_init( &counter, &cfg );

    counter_default_cfg( &counter );
    Delay_ms( 300 );
}
  
```

### Application Task

> Reads data from the CNTR register and calculates the speed of the motor in Rad/s.
> All data is being displayed on the USB UART terminal where you can track their changes.
> The CNTR is a software configurable 8, 16, 24 or 32-bit up/down counter which
> counts the up/down pulses resulting from the quadrature clocks applied at the
> A and B inputs, or alternatively, in non-quadrature mode, pulses applied at the A input.


```c

void application_task ( void )
{
    count = counter_read_cntr( &counter );
    log_printf( &logger, "Counter: %ld\r\n",  count );
    speed = ( float ) ( count - count_old ) / 3600.0;
    speed *= 6.283185;
    log_printf( &logger, "Speed: %.4f Rad/s\r\n",  speed );
    count_old = count;
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 1000 );
}  

```

## NOTE

> An appropriate motor with optical encoder needs to be connected to the click board.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Counter

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
