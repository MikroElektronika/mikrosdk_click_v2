
---
# LED driver 6 click

LED driver 6 Click is a high brightness LED or LED strip driver, designed to be used in tunable Smart Connected Lighting (SCL) applications. It is based on the AL1781, a single-channel PWM dimmable linear LED driver.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/led-driver-6-click)

---


#### Click library 

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type


# Software Support

We provide a library for the Leddriver6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Leddriver6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void leddriver6_cfg_setup ( leddriver6_cfg_t *cfg ); 
 
- Initialization function.
> LEDDRIVER6_RETVAL leddriver6_init ( leddriver6_t *ctx, leddriver6_cfg_t *cfg );


#### Example key functions :

- Generic sets PWM duty cycle.
> void leddriver6_set_duty_cycle ( leddriver6_t *ctx, pwm_data_t duty_cycle );
 
- Stop PWM module.
> void leddriver6_pwm_stop ( leddriver6_t *ctx );

- Start PWM module.
> void leddriver6_pwm_start ( leddriver6_t *ctx );

## Examples Description
 
> This application designed to be used in tunable Smart Connected Lighting applications. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init and pwm init for LED. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;

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
    log_info( &logger, "---- Application Init... ----" );

    leddriver6_cfg_t leddriver6_cfg;

    //  Click initialization.

    leddriver6_cfg_setup( &leddriver6_cfg );
    LEDDRIVER6_MAP_MIKROBUS( leddriver6_cfg, MIKROBUS_1 );

    if ( leddriver6_init( &leddriver6, &leddriver6_cfg ) == LEDDRIVER6_INIT_ERROR )
    {
        log_info( &logger, "---- Application Init Error. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- Application Init Done. ----" );
    
    leddriver6_set_duty_cycle ( &leddriver6, 0.0 );
    if ( leddriver6_pwm_start( &leddriver6 ) == LEDDRIVER6_INIT_ERROR )
    {
        log_info( &logger, "---- PWM can't be started. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- PWM is started. ----" );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms( 500 );
}
  
```

### Application Task

>  This is an example that demonstrates the use of the LED Driver 6 Click board.
>  This example shows the automatic control LED light intensity,
>  the first intensity of light is rising and then the intensity of light is falling.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    leddriver6_set_duty_cycle ( &leddriver6, duty );
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
- Click.Leddriver6

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
