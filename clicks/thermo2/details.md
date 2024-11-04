
---
# Thermo 2 Click

> THERMO 2 Click carries DS1825, a programmable resolution digital thermometer IC with a unique 64-bit address. The Click is designed to run on a 3.3V power supply. The board communicates with the target microcontroller through a 1-wire interface. Using the onboard jumper you can select between two outputs: GP1 (default mikroBUS™ AN pin), and GPO (default PWM pin).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/thermo-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2022.
- **Type**          : PWM type


# Software Support

We provide a library for the Thermo 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Thermo 2 Click driver.

#### Standard key functions :

- `thermo2_cfg_setup` Config Object Initialization function.
```c
void thermo2_cfg_setup ( thermo2_cfg_t *cfg );
```

- `thermo2_init` Initialization function.
```c
err_t thermo2_init ( thermo2_t *ctx, thermo2_cfg_t *cfg );
```

- `thermo2_default_cfg` Click Default Configuration function.
```c
err_t thermo2_default_cfg ( thermo2_t *ctx );
```

#### Example key functions :

- `thermo2_write_scratchpad` This function writes the temperature thresholds and configuration byte to the scratchpad.
```c
err_t thermo2_write_scratchpad ( thermo2_t *ctx, uint8_t temp_high, uint8_t temp_low, uint8_t config );
```

- `thermo2_read_scratchpad` This function reads the scratchpad bytes.
```c
err_t thermo2_read_scratchpad ( thermo2_t *ctx, uint8_t *scratchpad );
```

- `thermo2_read_temperature` This function reads the temperature value in Celsius.
```c
err_t thermo2_read_temperature ( thermo2_t *ctx, float *temperature );
```

## Example Description

> This example demonstrates the use of Thermo 2 Click board by reading and displaying the temperature in Celsius.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo2_cfg_t thermo2_cfg;  /**< Click config object. */

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
    thermo2_cfg_setup( &thermo2_cfg );
    THERMO2_MAP_MIKROBUS( thermo2_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == thermo2_init( &thermo2, &thermo2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO2_ERROR == thermo2_default_cfg ( &thermo2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays the temperature measured by the Click board on the USB UART
approximately every 800ms as this matches the required conversion time for 12-bit temperature resolution.

```c
void application_task ( void )
{
    float temperature;
    if ( THERMO2_OK == thermo2_read_temperature ( &thermo2, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
