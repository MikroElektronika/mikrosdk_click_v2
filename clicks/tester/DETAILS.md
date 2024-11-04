
---
# Tester Click

Tester Click is a Click board™ used as a diagnostic tool on the mikroBUS™ socket.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/tester_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/tester-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : GPIO type

# Software Support

We provide a library for the Tester Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Tester Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void tester_cfg_setup ( tester_cfg_t *cfg ); 
 
- Initialization function.
> TESTER_RETVAL tester_init ( tester_t *ctx, tester_cfg_t *cfg );

- Click Default Configuration function.
> void tester_default_cfg ( tester_t *ctx );


#### Example key functions :

- This function sets the output voltage on the specified pin to high.
> void tester_set_pin_high ( digital_out_t *pin );
 
- This function sets the output voltage on the specified pin to low.
> void tester_set_pin_low ( digital_out_t *pin );

## Examples Description

> This example showcases how to initialize, configure and use the Tester Click. It is a simple
  GPIO Click which is used to test if all the pins on a MikroBUS are working correctly. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the Click and logger modules. 

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    tester_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    tester_cfg_setup( &cfg );
    TESTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tester_init( &tester, &cfg );
}
  
```

### Application Task

> This function sets the output on all the pins (one by one) on the left side to high, going
  from top to bottom and then does the same with the ones on the right side, after which it 
  sets all pins to high and after one second sets them back to low.

```c

void application_task ( )
{
    int i;

    for( i = 0; i < 12; i++ )
    {
        blink( pin_addr[ i ] );
    }

    all_on( );
    Delay_1sec( );
    all_off( );
} 

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Tester

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