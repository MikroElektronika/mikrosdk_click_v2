\mainpage Main Page

---
# H-Bridge 8 click

H-Bridge 8 Click is a compact add-on board that contains H-bridge current regulator. This board features the MP6519, a monolithic, step-down, current-source driver for applications that require accurate and fast current-response control from Monolithic Power Systems (MPS). It achieves excellent load and line regulation over a wide input supply range up to 28V. The four integrated MOSFET H-bridge control provide a fast dynamic load response and an ultra-high efficiency solution. Complete protection features include load open, load-short protection, over-current protection (OCP), over-temperature protection (OTP), and input over-voltage protection (OVP).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hbridge8_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/h-bridge-8-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2021.
- **Type**          : PWM type


# Software Support

We provide a library for the HBridge8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for HBridge8 Click driver.

#### Standard key functions :

- `hbridge8_cfg_setup` Config Object Initialization function.
```c
void hbridge8_cfg_setup ( hbridge8_cfg_t *cfg );
```

- `hbridge8_init` Initialization function.
```c
err_t hbridge8_init ( hbridge8_t *ctx, hbridge8_cfg_t *cfg );
```

- `hbridge8_default_cfg` Click Default Configuration function.
```c
void hbridge8_default_cfg ( hbridge8_t *ctx );
```

#### Example key functions :

- `hbridge8_set_mode` H-Bridge 8 set operating mode function.
```c
err_t hbridge8_set_mode ( hbridge8_t *ctx, uint8_t mode );
```

- `hbridge8_enable` H-Bridge 8 set IC enable function.
```c
err_t hbridge8_enable ( hbridge8_t *ctx );
```

- `hbridge8_set_duty_cycle` H-Bridge 8 sets PWM duty cycle.
```c
err_t hbridge8_set_duty_cycle ( hbridge8_t *ctx, float duty_cycle );
```

## Example Description

> This library contains an API for the H-Bridge 8 Click driver.
> This demo application shows the use of a H-Bridge 8 Click board™.

**The demo application is composed of two sections :**

### Application Init

> Initialization of PWM module and log UART.
> After driver initialization, the app set duty cycle, start PWM and
> set motor drive the forward.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    hbridge8_cfg_t hbridge8_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.

    hbridge8_cfg_setup( &hbridge8_cfg );
    HBRIDGE8_MAP_MIKROBUS( hbridge8_cfg, MIKROBUS_1 );
    err_t init_flag  = hbridge8_init( &hbridge8, &hbridge8_cfg );
    if ( PWM_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    hbridge8_default_cfg ( &hbridge8 );
    Delay_ms ( 100 );
   
    hbridge8_set_mode( &hbridge8, HBRIDGE8_MODE_FORWARD );
    log_printf( &logger, "\r\n>>> Forward\r\n\r\n" );
    hbridge8_set_duty_cycle ( &hbridge8, 0.1 );
    hbridge8_pwm_start( &hbridge8 );
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that shows the use of an H-Bridge 8 Click board™.
> In this example, the app drives the motor forward/reverse and switched the PWM signal back and forth 
> from 3% duty cycle to 8% duty cycle every 3000 milliseconds and back.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) 
{
    static int8_t duty_cnt = 3;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 100.0;
    
    hbridge8_set_duty_cycle ( &hbridge8, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt ) );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    if ( 8 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 3 == duty_cnt ) 
    {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge8

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
