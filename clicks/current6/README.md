\mainpage Main Page

---
# Current 6 click

> Current 6 Click is a compact add-on board providing a precise and accurate current sensing solution. This board features the MAX40080, a fast-response bi-directional current-sense amplifier from Analog Devices. The device features ultra-low 5uV input offset voltage, very-low 0.2% gain error, and includes an analog-to-digital converter with programmable sample rate and 12-bit resolution featuring I2C compatible interface. It also features a wake-up current-threshold and auto-shutdown mode when the I2C is inactive, both designed to minimize power consumption. The current-shunt monitor can measure voltage signals on common-mode voltages ranging from -0.1V (ground sensing) to 36V, independent of the supply voltage. This Click board™ delivers higher performance to industrial control and automation applications, load and power supplies monitoring, telecom equipment, and many more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/current6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/current-6-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Current 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Current 6 Click driver.

#### Standard key functions :

- `current6_cfg_setup` Config Object Initialization function.
```c
void current6_cfg_setup ( current6_cfg_t *cfg );
```

- `current6_init` Initialization function.
```c
err_t current6_init ( current6_t *ctx, current6_cfg_t *cfg );
```

- `current6_default_cfg` Click Default Configuration function.
```c
err_t current6_default_cfg ( current6_t *ctx );
```

#### Example key functions :

- `current6_get_alert_pin` This function returns the alert pin logic state.
```c
uint8_t current6_get_alert_pin ( current6_t *ctx );
```

- `current6_read_data` This function reads the input voltage and current measurement values.
```c
err_t current6_read_data ( current6_t *ctx, float *voltage, float *current );
```

- `current6_get_status` This function reads and clears the status register.
```c
err_t current6_get_status ( current6_t *ctx, uint16_t *status );
```

## Example Description

> This example demonstrates the use of Current 6 click board by reading the input voltage and current measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current6_cfg_t current6_cfg;  /**< Click config object. */

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
    current6_cfg_setup( &current6_cfg );
    CURRENT6_MAP_MIKROBUS( current6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == current6_init( &current6, &current6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENT6_ERROR == current6_default_cfg ( &current6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the FIFO data interrupt and then reads the measurements of the input voltage and current and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    if ( current6_get_alert_pin ( &current6 ) )
    {
        uint16_t status;
        if ( CURRENT6_OK == current6_get_status ( &current6, &status ) )
        {
            if ( status & CURRENT6_FIFO_CFG_DATA_OVERFLOW_MASK )
            {
                float voltage, current;
                if ( CURRENT6_OK == current6_read_data ( &current6, &voltage, &current ) )
                {
                    log_printf( &logger, " Voltage: %.3f V\r\n Current: %.3f A\r\n\n", voltage, current );
                }
            }
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Current6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
