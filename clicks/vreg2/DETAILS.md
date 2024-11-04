 
---
# VREG 2 Click

> VREG 2 Click is a voltage regulator Click, with outstanding performances.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/vreg2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/vreg-2-click)

---


#### Click library 

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2023.
- **Type**          : PWM type


# Software Support

We provide a library for the Vreg2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Vreg2 Click driver.

#### Standard key functions :

- `vreg2_cfg_setup` Config Object Initialization function.
```c
void vreg2_cfg_setup ( vreg2_cfg_t *cfg ); 
```

- `vreg2_init` Initialization function.
```c
err_t vreg2_init ( vreg2_t *ctx, vreg2_cfg_t *cfg );
```

- `vreg2_default_cfg` Click Default Configuration function.
```c
err_t vreg2_default_cfg ( vreg2_t *ctx );
```

#### Example key functions :

- `vreg2_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t vreg2_set_duty_cycle ( vreg2_t *ctx, float duty_cycle );
```

- `vreg2_pwm_start` This function starts the PWM module output.
```c
err_t vreg2_pwm_start ( vreg2_t *ctx );
```

- `vreg2_pwm_stop` This function stops the PWM module output.
```c
err_t vreg2_pwm_stop ( vreg2_t *ctx );
```

## Examples Description

> This example demonstrates the use of the VREG 2 Click board by changing the voltage output every 5 seconds.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vreg2_cfg_t vreg2_cfg;  /**< Click config object. */

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
    vreg2_cfg_setup( &vreg2_cfg );
    VREG2_MAP_MIKROBUS( vreg2_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == vreg2_init( &vreg2, &vreg2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( VREG2_ERROR == vreg2_default_cfg ( &vreg2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Controls the voltage output by changing the PWM duty cycle every 5 seconds.
The duty cycle ranges from 10% to 50%. Each step will be logged on the USB UART where you can track the program flow.

```c

void application_task ( void )
{
    static int8_t duty_pct = 10;
    static int8_t duty_step = 10;
    if ( VREG2_OK == vreg2_set_duty_cycle ( &vreg2, ( float ) duty_pct / 100 ) )
    {
        log_printf( &logger, "\r\n Duty: %u%%\r\n", ( uint16_t ) duty_pct );
    }
    duty_pct += duty_step;
    if ( ( duty_pct > 50 ) || ( duty_pct < 10 ) ) 
    {
        duty_step = -duty_step;
        duty_pct += ( duty_step * 2 );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Vreg2

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
