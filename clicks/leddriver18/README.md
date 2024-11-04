\mainpage Main Page

---
# LED Driver 18 Click

> LED Driver 18 Click is a compact add-on board that simplifies the control of multiple LEDs. This board features the TLC5947, a 24-channel LED driver from Texas Instruments. Each channel is individually adjustable with 4096 pulse-width modulated (PWM) steps and has a programmable current value of all channels with a maximum of 30mA of LED current per channel.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver18_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/led-driver-18-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the LED Driver 18 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LED Driver 18 Click driver.

#### Standard key functions :

- `leddriver18_cfg_setup` Config Object Initialization function.
```c
void leddriver18_cfg_setup ( leddriver18_cfg_t *cfg );
```

- `leddriver18_init` Initialization function.
```c
err_t leddriver18_init ( leddriver18_t *ctx, leddriver18_cfg_t *cfg );
```

- `leddriver18_default_cfg` Click Default Configuration function.
```c
err_t leddriver18_default_cfg ( leddriver18_t *ctx );
```

#### Example key functions :

- `leddriver18_set_output_pwm` LED Driver 18 set output channel PWM value function.
```c
err_t leddriver18_set_output_pwm ( uint8_t out_num, float pwm_val );
```

- `leddriver18_write_config` LED Driver 18 write config function.
```c
void leddriver18_write_config ( leddriver18_t *ctx );
```

- `leddriver18_set_cc_output` LED Driver 18 set constant current output function.
```c
err_t leddriver18_set_cc_output ( leddriver18_t *ctx, uint8_t current_limit );
```

## Example Description

> This library contains API for LED Driver 18 Click driver. 
The library initializes and defines the I2C bus drivers to 
write and read data for setting constant current output, 
as well as the default configuration for a PWM output value 
of the OUT pins.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs default configuration and sets 
the device in output enabled mode.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver18_cfg_t leddriver18_cfg;  /**< Click config object. */

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
    leddriver18_cfg_setup( &leddriver18_cfg );
    LEDDRIVER18_MAP_MIKROBUS( leddriver18_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == leddriver18_init( &leddriver18, &leddriver18_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER18_ERROR == leddriver18_default_cfg ( &leddriver18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example demonstrates the use of the LED Driver 18 Click board by 
changing PWM values for all output from a minimum value to 
maximum value and back to minimum controlling the brightness of the 
LEDs in the process.

```c
void application_task ( void ) 
{
    float pwm_val;

    for ( int8_t  n_cnt = 0; n_cnt <= 100; n_cnt += 10 )
    {
        for ( uint8_t out_cnt = 0; out_cnt < LEDDRIVER18_MAX_OUTPUT_NUM; out_cnt++ )
        {
            leddriver18_set_output_pwm( out_cnt, n_cnt );
        }
        pwm_val = leddriver18_get_output_pwm( 0 );
        log_printf( &logger, " PWM value: %.2f \r\n", pwm_val );
        leddriver18_write_config( &leddriver18 );
        Delay_ms ( 200 );
    }
    for ( int8_t  n_cnt = 100; n_cnt >= 10; n_cnt -= 10 )
    {
        for ( uint8_t out_cnt = 0; out_cnt < LEDDRIVER18_MAX_OUTPUT_NUM; out_cnt++ )
        {
            leddriver18_set_output_pwm( out_cnt, n_cnt );
        }
        pwm_val = leddriver18_get_output_pwm( 0 );
        log_printf( &logger, " PWM value: %.2f \r\n", pwm_val );
        leddriver18_write_config( &leddriver18 );
        Delay_ms ( 200 );
    }
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDDriver18

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
