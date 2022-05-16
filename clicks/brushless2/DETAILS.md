
---
# Brushless 2 click

Brushless 2 click carries the DRV10964 BLDC motor controller with an integrated output stage.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/brushless-2-click)

---


#### Click library 

- **Author**        : Nikola peric
- **Date**          : Mar 2022.
- **Type**          : PWM type


# Software Support

We provide a library for the Brushless2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Brushless2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void brushless2_cfg_setup ( brushless2_cfg_t *cfg ); 
 
- Initialization function.
> BRUSHLESS2_RETVAL brushless2_init ( brushless2_t *ctx, brushless2_cfg_t *cfg );

#### Example key functions :

- Set the direction of rotation in the counterclockwise direction function
> void brushless2_counter_clockwise ( brushless2_t *ctx );
 
- Set the direction of rotation in the clockwise direction function
> void brushless2_clockwise ( brushless2_t *ctx );

- Get Interrupt pin state function
> uint8_t brushless2_get_interrupt_status ( brushless2_t *ctx );

## Examples Description

> This application controlled speed motor.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - GPIO, PWM initialization

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless2_cfg_t cfg;

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

    brushless2_cfg_setup( &cfg );
    BRUSHLESS2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless2_init( &brushless2, &cfg );
    
    log_printf( &logger, "---------------------- \r\n" );
    
    brushless2_set_duty_cycle ( &brushless2, 0.0 );
    brushless2_pwm_start ( &brushless2 );
    Delay_ms( 500 );
    log_info( &logger, "---- Application Task ----" );
}
  
```

### Application Task

>  This is a example which demonstrates the use of Brushless 2 Click board.
>  Brushless 2 Click communicates with register via PWM interface.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{    
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    brushless2_set_duty_cycle ( &brushless2, duty );
    brushless2_clockwise ( &brushless2 );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
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
- Click.Brushless2

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
