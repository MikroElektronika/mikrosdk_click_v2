\mainpage Main Page
 
 

---
# PLL click

PLL click is a frequency multiplier which uses the Phase-Locked Loop (PLL) techniques to provide a high-frequency clock output from a cheap, standard fundamental mode crystal oscillator. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pll_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pll-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Pll Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pll Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pll_cfg_setup ( pll_cfg_t *cfg ); 
 
- Initialization function.
> PLL_RETVAL pll_init ( pll_t *ctx, pll_cfg_t *cfg );

- Click Default Configuration function.
> void pll_default_cfg ( pll_t *ctx );


#### Example key functions :

- This function settings clock output.
> void pll_set_clock_output ( pll_t *ctx, uint8_t mode );
 
- This function settings PLL x4.
> void pll_set_pll_4x ( pll_t *ctx );

- This function settings PLL x6.
> void pll_set_pll_6x ( pll_t *ctx );

## Examples Description

> This app sets PLL signals.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pll_cfg_t cfg;

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

    pll_cfg_setup( &cfg );
    PLL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pll_init( &pll, &cfg );
    pll_set_clock_output( &pll, PLL_CLOCK_ENABLE );
}
  
```

### Application Task

> Every 2 seconds, the PLL increases the input clock in the order of x4, x5, x6 and x8.

```c

void application_task ( void )
{
    pll_set_pll_4x( &pll );
    Delay_ms( 2000 );
    pll_set_pll_5x( &pll );
    Delay_ms( 2000 );
    pll_set_pll_6x( &pll );
    Delay_ms( 2000 );
    pll_set_pll_8x( &pll );
    Delay_ms( 2000 );
} 

```

## Note

> If you use PLL x4, x5, x6 or x8, set S0 (RST pin) and S1 (AN pin) as OUTPUT.
> If you use PLL x3.125 or x6.25, set S1 ( AN pin ) as INPUT and S0( RST pin ) as OUTPUT.
> If you use PLL x3 or x5.3125, set S0 ( RST pin ) as INPUT and S1 ( AN pin ) as OUTPUT.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pll

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
