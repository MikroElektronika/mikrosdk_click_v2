
---
# LED Driver 19 click

> LED Driver 19 Click is a compact add-on board that simplifies the control of multiple LEDs. This board features the LED1202, a 12-channel low quiescent current LED driver from STMicroelectronics. It can output 5V, and each channel can provide up to 20mA with a headroom voltage of typically 350mW.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver19_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/led-driver-19-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Apr 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the LED Driver 19 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LED Driver 19 Click driver.

#### Standard key functions :

- `leddriver19_cfg_setup` Config Object Initialization function.
```c
void leddriver19_cfg_setup ( leddriver19_cfg_t *cfg );
```

- `leddriver19_init` Initialization function.
```c
err_t leddriver19_init ( leddriver19_t *ctx, leddriver19_cfg_t *cfg );
```

- `leddriver19_default_cfg` Click Default Configuration function.
```c
err_t leddriver19_default_cfg ( leddriver19_t *ctx );
```

#### Example key functions :

- `leddriver19_sw_reset` LED Driver 19 software reset function.
```c
err_t leddriver19_sw_reset ( leddriver19_t *ctx );
```

- `leddriver19_enable_channels` LED Driver 19 enables channels function.
```c
err_t leddriver19_enable_channels ( leddriver19_t *ctx, uint16_t channels_en );
```

- `leddriver19_set_pattern_pwm` LED Driver 19 set pattern PWM value function.
```c
err_t leddriver19_set_pattern_pwm ( leddriver19_t *ctx, uint8_t pattern_sel, uint8_t channel_sel, float pwm_value );
```

## Example Description

> This library contains API for LED Driver 19 Click driver. 
  The library initializes and defines the I2C bus drivers to 
  write the default configuration for a PWM output value 
  of the out pins.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs default configuration, sets the device
  in output enabled mode and checks communication by reading device ID.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver19_cfg_t leddriver19_cfg;  /**< Click config object. */

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
    leddriver19_cfg_setup( &leddriver19_cfg );
    LEDDRIVER19_MAP_MIKROBUS( leddriver19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == leddriver19_init( &leddriver19, &leddriver19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint8_t device_id;
    
    leddriver19_read_reg( &leddriver19, LEDDRIVER19_REG_DEVICE_ID, &device_id );
    if ( LEDDRIVER19_DEVICE_ID != device_id )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER19_ERROR == leddriver19_default_cfg ( &leddriver19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example demonstrates the use of the LED Driver 19 Click board by 
  changing PWM values of all channels from maximum to minimum turning 
  LEDs on and off in the process.

```c
void application_task ( void ) 
{
    for ( uint8_t n_cnt = LEDDRIVER19_CH_SEL_0; n_cnt <= LEDDRIVER19_CH_SEL_11; n_cnt++ )
    {
        leddriver19_set_pattern_pwm( &leddriver19, LEDDRIVER19_PATSEL_0, n_cnt, 100  );
        Delay_ms ( 100 );
    }
    Delay_ms ( 1000 );
    
    for ( uint8_t n_cnt = LEDDRIVER19_CH_SEL_0; n_cnt <= LEDDRIVER19_CH_SEL_11; n_cnt++ )
    {
        leddriver19_set_pattern_pwm( &leddriver19, LEDDRIVER19_PATSEL_0, n_cnt, 0  );
        Delay_ms ( 100 );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDDriver19

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
