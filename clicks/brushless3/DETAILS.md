
---
# Brushless 3 Click

Brushless 3 Click carries the DRV10983, a three-phase sensorless motor driver with integrated power MOSFETs. When an external power supply is applied, you can drive a brushless DC motor through the PWM pin, AN pin or I2C interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/brushless-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Brushless3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Brushless3 Click driver.

#### Standard key functions :

- `brushless3_cfg_setup` Config Object Initialization function.
```c
void brushless3_cfg_setup ( brushless3_cfg_t *cfg );
```

- `brushless3_init` Initialization function.
```c
err_t brushless3_init ( brushless3_t *ctx, brushless3_cfg_t *cfg );
```

- `brushless3_default_cfg` Click Default Configuration function.
```c
err_t brushless3_default_cfg ( brushless3_t *ctx );
```

#### Example key functions :

- `brushless3_set_speed` Set speed function
```c
err_t brushless3_set_speed ( brushless3_t *ctx, uint16_t motor_speed_hz );
```

- `brushless3_get_speed` Get speed function
```c
err_t brushless3_get_speed ( brushless3_t *ctx, float *speed );
```

- `brushless3_forward_direction` Set the direction of rotation in the forward direction function
```c
void brushless3_forward_direction ( brushless3_t *ctx );
```

## Examples Description

> This Click has three-phase sensorless motor driver and with an external power supply it drives a brushless DC motor. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - I2C, set default parameter value.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless3_cfg_t cfg;

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
    brushless3_cfg_setup( &cfg );
    BRUSHLESS3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless3_init( &brushless3, &cfg );
    
    if ( BRUSHLESS3_ERROR == brushless3_default_cfg ( &brushless3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
}
  
```

### Application Task

> This is an example which demonstrates the use of Brushless 3 Click board.
> Read and display float motor frequency value from the DRV10983 sensorless 
> BLDC motor driver on Brushless 3 Click board. Results are being sent to 
> the Usart Terminal where you can track their changes. 

```c

void application_task ( void )
{
    log_printf( &logger, "    acceleration      \r\n" );
    
    for ( speed = 100; speed <= BRUSHLESS3_MAX_SPEED; speed += 20 )
    {
        brushless3_set_speed( &brushless3, speed );
        brushless3_get_speed( &brushless3, &velocity );
        log_printf( &logger, " Motor frequency: %.2f Hz\r\n", velocity );
        Delay_ms ( 100 );
    }

    log_printf( &logger,  "\r\n ---------------------- \r\n" ); 
    log_printf( &logger, "    slowing down     \r\n" );
    
    for ( speed = BRUSHLESS3_MAX_SPEED; speed >= 50; speed -= 20 )
    {
        brushless3_set_speed( &brushless3, speed );
        brushless3_get_speed( &brushless3, &velocity );
        log_printf( &logger, " Motor frequency: %.2f Hz\r\n", velocity );
        Delay_ms ( 100 );
    }
    
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 1000 );
}  

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless3

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
