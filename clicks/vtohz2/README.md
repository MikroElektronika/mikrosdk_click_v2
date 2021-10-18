\mainpage Main Page
 
---
# V to Hz 2 click

V to Hz 2 click is a device that converts an analog voltage input signal into a pulse wave signal of a certain frequency.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/vtohz2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/v-to-hz-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the VToHz2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for VToHz2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void vtohz2_cfg_setup ( vtohz2_cfg_t *cfg ); 
 
- Initialization function.
> VTOHZ2_RETVAL vtohz2_init ( vtohz2_t *ctx, vtohz2_cfg_t *cfg );


#### Example key functions :

- Function gets the out frequency on mikrobus INT pin.
> uint8_t vtohz2_get_freq_out ( vtohz2_t *ctx );
 
- Function performs enabling and disabling of the device.
> void vtohz2_enable ( vtohz2_t *ctx, uint8_t state );

- This function starts PWM module.
> void vtohz2_pwm_start ( vtohz2_t *ctx );

## Examples Description

> This appliaction enables usage of a converter for analog voltage input signal into 
> a pulse wave signal of a certain frequency.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and enables the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    vtohz2_cfg_t cfg;

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

    vtohz2_cfg_setup( &cfg );
    VTOHZ2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vtohz2_init( &vtohz2, &cfg );

    vtohz2_enable( &vtohz2, VTOHZ2_ENABLE );
    vtohz2_pwm_start( &vtohz2 );
}

  
```

### Application Task

> Sets the output frequency by incrementing the pwm duty cycle from 0 to 100% in an infinite loop.
> Results are being sent to USB UART terminal.

```c

void application_task ( void )
{
    for ( duty_cycle = 0; duty_cycle <= 1.0; duty_cycle += 0.01 )
    {
        vtohz2_set_duty_cycle ( &vtohz2, duty_cycle );
        log_printf( &logger," PWM Duty: %.2f%%\r\n", duty_cycle * 100 );
        Delay_ms( 100 );
    }
    log_printf( &logger, "------------------------------\r\n" );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.VToHz2

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
