
---
# Brushless 14 click

> Brushless 14 Click is a compact add-on board suitable for controlling BLDC motors with any MCU. This board features the TB67B001FTG, a three-phase, brushless, Hall sensorless driver IC from Toshiba Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless_14_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/brushless-14-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Brushless14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushless14 Click driver.

#### Standard key functions :

- `brushless14_cfg_setup` Config Object Initialization function.
```c
void brushless14_cfg_setup ( brushless14_cfg_t *cfg );
```

- `brushless14_init` Initialization function.
```c
err_t brushless14_init ( brushless14_t *ctx, brushless14_cfg_t *cfg );
```

- `brushless14_default_cfg` Click Default Configuration function.
```c
err_t brushless14_default_cfg ( brushless14_t *ctx );
```

#### Example key functions :

- `brushless14_set_duty_cycle` Sets PWM duty cycle.
```c
err_t brushless14_set_duty_cycle ( brushless14_t *ctx, float duty_cycle );
```

- `brushless14_set_la` Set lead angle setting input.
```c
err_t brushless14_set_la ( brushless14_t *ctx, uint16_t m_voltage );
```

- `brushless14_set_dir` Set dirrection pin state.
```c
void brushless14_set_dir ( brushless14_t *ctx, uint8_t state );
```

## Example Description

> This application example showcases ability of the device to control motor,
It's speed and rotation direction. Also it gives user ability to change other
configuration parameters.

**The demo application is composed of two sections :**

### Application Init

> Initialization of communication modules (I2C, PWM, UART) and additional 
pins (INT, DIR). It reads ID from DAC ic to confirm communcation. Then
configures device for control.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless14_cfg_t brushless14_cfg;  /**< Click config object. */

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
    brushless14_cfg_setup( &brushless14_cfg );
    BRUSHLESS14_MAP_MIKROBUS( brushless14_cfg, MIKROBUS_1 );
    err_t init_flag = brushless14_init( &brushless14, &brushless14_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    uint16_t data_read = 0;
    brushless14_dac_read( &brushless14, 0x02, &data_read);
    if ( BRUSHLESS14_DAC_ID != data_read )
    {
        log_error( &logger, " Communication. " );
    }
    
    brushless14_default_cfg ( &brushless14 );
    
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives motor using PWM from 10% duty cycle to 100% and back to 0%. 
Increment is done by 10% in span of 2 seconds. Whenever application gets
to 0% duty cycle it chages direction of rotation.

```c

void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    static uint8_t direction = 0;
    float duty = duty_cnt / 10.0;
    
    brushless14_set_duty_cycle ( &brushless14, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
        direction = !direction;
        brushless14_set_dir( &brushless14, direction );
    }
    duty_cnt += duty_inc;
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
