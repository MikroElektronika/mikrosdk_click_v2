

---
# Clock Gen 2 Click

Clock Gen 2 Click is an accurate square wave generator that can generate a clock signal in the range from 260kHz to 66.6MHz. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/clockgen2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/clock-gen-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the ClockGen2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https:///shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https:///shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ClockGen2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void clockgen2_cfg_setup ( clockgen2_cfg_t *cfg ); 
 
- Initialization function.
> CLOCKGEN2_RETVAL clockgen2_init ( clockgen2_t *ctx, clockgen2_cfg_t *cfg );

- Click Default Configuration function.
> void clockgen2_default_cfg ( clockgen2_t *ctx );


#### Example key functions :

- Function for enabling/disabling of the clock output.
> void clockgen2_output_enable ( clockgen2_t *ctx, uint8_t state );
 
- Function used for enabling/disabling auto settings preservation.
> void clockgen2_auto_setting_preserve ( clockgen2_t *ctx, uint8_t state );

- Function for setting the main clock prescaler.
> void clockgen2_set_prescaler ( clockgen2_t *ctx, uint8_t val );

## Examples Description

> This application enables generation of square waved clock signal in range from 260 kHz to 66,6 MHz

**The demo application is composed of two sections :**

### Application Init 

> Driver initialization.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    clockgen2_cfg_t cfg;

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

    clockgen2_cfg_setup( &cfg );
    CLOCKGEN2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    clockgen2_init( &clockgen2, &cfg );

    Delay_ms ( 100 );
}
  
```

### Application Task

> Changes the prescaler and enables/disables the clock output.

```c

void application_task ( void )
{
    //  Task implementation.

    char i;
     
     for ( i = 5; i< 8; i++ )
     {
       clockgen2_set_prescaler( &clockgen2, i );
       clockgen2_output_enable( &clockgen2, 1 );
       Delay_ms ( 1000 );
       Delay_ms ( 1000 );

       clockgen2_output_enable( &clockgen2, 0 );
       Delay_ms ( 1000 );
       Delay_ms ( 1000 );
     }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ClockGen2

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https:///shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https:///shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https:///shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https:///shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
