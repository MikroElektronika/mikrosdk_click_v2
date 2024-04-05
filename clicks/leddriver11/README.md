\mainpage Main Page

---
# LED Driver 11 click

LED Driver 11 Click is a compact add-on board that simplifies the control of multiple LEDs. This board features the WLMDU9456001JT (172946001), a fully integrated constant current LED driver with the buck switching regulator and inductor in a single package from Würth Elektronik.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/led-driver-11-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the LEDDriver11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LEDDriver11 Click driver.

#### Standard key functions :

- `leddriver11_cfg_setup` Config Object Initialization function.
```c
void leddriver11_cfg_setup ( leddriver11_cfg_t *cfg );
```

- `leddriver11_init` Initialization function.
```c
err_t leddriver11_init ( leddriver11_t *ctx, leddriver11_cfg_t *cfg );
```

- `leddriver11_default_cfg` Click Default Configuration function.
```c
err_t leddriver11_default_cfg ( leddriver11_t *ctx );
```

#### Example key functions :

- `leddriver11_pwm_start` This function starts the PWM moudle output.
```c
err_t leddriver11_pwm_start ( leddriver11_t *ctx );
```

- `leddriver11_set_current` This function sets the LEDs current via a 12-bit DAC module.
```c
err_t leddriver11_set_current ( leddriver11_t *ctx, uint16_t curr );
```

- `leddriver11_set_duty_cycle` This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
```c
err_t leddriver11_set_duty_cycle ( leddriver11_t *ctx, float duty_cycle );
```

## Example Description

> This example demonstrates the use of LED Driver 11 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and executes the click default configuration which starts the PWM module and sets the LEDs current to minimum.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    leddriver11_cfg_t leddriver11_cfg;  /**< Click config object. */

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
    leddriver11_cfg_setup( &leddriver11_cfg );
    LEDDRIVER11_MAP_MIKROBUS( leddriver11_cfg, MIKROBUS_1 );
    err_t init_flag = leddriver11_init( &leddriver11, &leddriver11_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    leddriver11_default_cfg ( &leddriver11 );
    log_printf( &logger, " Dimming the LEDs light...\r\n" );
}

```

### Application Task

> Controls the LEDs brightness by changing the PWM duty cycle. The PWM duty cycle percentage will be logged on the USB UART.

```c

void application_task ( void )
{
    static int16_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    leddriver11_set_duty_cycle ( &leddriver11, duty );
    log_printf( &logger, "> Duty: %u%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );
    
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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDDriver11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
