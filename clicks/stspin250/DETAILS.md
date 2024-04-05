
---
# STSPIN250 click

STSPIN250 click is a brushed DC motor driver with the current limiting and current sensing. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stspin250_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/stspin250-click)

---


#### Click library 

- **Author**        : Nikola Peric
- **Date**          : Feb 2022.
- **Type**          : PWM type


# Software Support

We provide a library for the Stspin250 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Stspin250 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void stspin250_cfg_setup ( stspin250_cfg_t *cfg ); 
 
- Initialization function.
> STSPIN250_RETVAL stspin250_init ( stspin250_t *ctx, stspin250_cfg_t *cfg );

- Click Default Configuration function.
> void stspin250_default_cfg ( stspin250_t *ctx );


#### Example key functions :

- This function regulates Direction control pin state. It controls direction
- of the current.
> void stspin250_set_ph ( stspin250_t *ctx, uint8_t state );
 
- This function regulates enable pin state.
> void stspin250_enable ( stspin250_t *ctx, uint8_t state);

- This function regulates reset pin state.
> void stspin250_reset ( stspin250_t *ctx );

## Examples Description

> This application enables usage of brushed DC motor driver with the current limiting and current sensing.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init, PWM init and enable device


```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    stspin250_cfg_t cfg;

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

    stspin250_cfg_setup( &cfg );
    STSPIN250_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stspin250_init( &stspin250, &cfg );

    stspin250_enable( &stspin250, STSPIN250_DEVICE_ENABLE );
    stspin250_set_duty_cycle ( &stspin250, 0.0 );

    stspin250_pwm_start( &stspin250 );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms ( 500 );
}
  
```

### Application Task

>  This is a example which demonstrates the use of Stspin250 Click board.
>  Stspin250 Click communicates with register via PWM interface.
>  It shows moving in the left direction from slow to fast speed
>  and from fast to slow speed.
>  Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    if ( motor_direction == 1 )
    {
        stspin250_set_ph( &stspin250, 1 );
        log_printf( &logger, "> CLOCKWISE <\r\n" );
    }
    else
    {
        stspin250_set_ph( &stspin250, 0 );
        log_printf( &logger, "> COUNTER CLOCKWISE <\r\n" );
    }

    stspin250_set_duty_cycle ( &stspin250, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
        if ( motor_direction == 1 )
        {
            motor_direction = 0;
        }
        else if ( motor_direction == 0 )
        {
            motor_direction = 1;
        }
    }
    duty_cnt += duty_inc;
}


```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Stspin250

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
