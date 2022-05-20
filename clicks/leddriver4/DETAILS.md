
---
# LED Driver 4 click

LED Driver 4 click is a form of a high-efficiency boost converter that is ideally suited for driving an array of white LEDs. The driver has the ability to dim the connected LED array, without producing any noise on the output. The Click board is capable of driving a LED array with up to 26V, providing a constant current to the LED segments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/led-driver-4-click)

---


#### Click library 

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type


# Software Support

We provide a library for the LedDriver4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LedDriver4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void leddriver4_cfg_setup ( leddriver4_cfg_t *cfg ); 
 
- Initialization function.
> LEDDRIVER4_RETVAL leddriver4_init ( leddriver4_t *ctx, leddriver4_cfg_t *cfg );

#### Example key functions :

- Generic sets PWM duty cycle.
> void leddriver4_set_duty_cycle ( leddriver4_t *ctx, float duty_cycle );
 
- Stop PWM module.
> void leddriver4_pwm_stop ( leddriver4_t *ctx );

- Start PWM module.
> leddriver4_pwm_start ( leddriver4_t *ctx );

## Examples Description

> This click has the ability to dim the connected LED array, without producing any noise on the output.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the GPIO driver and configures the PWM peripheral for controlling the LED array intensity.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver4_cfg_t cfg;

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

    leddriver4_cfg_setup( &cfg );
    LEDDRIVER4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver4_init( &leddriver4, &cfg );
    
    leddriver4_set_duty_cycle ( &leddriver4, 0.0 );
    leddriver4_pwm_start( &leddriver4 );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms( 500 );
}
  
```

### Application Task

>  Increases and decreases LED array intensity
>  ( first increases light intensity to the maximum and then decreases to the minimum ).
>  Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    leddriver4_set_duty_cycle ( &leddriver4, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms( 500 );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
}
 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LedDriver4

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
