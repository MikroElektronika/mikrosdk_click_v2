\mainpage Main Page

---
# Thermo 19 Click

> Thermo 19 Click is a compact add-on board that provides an accurate temperature measurement. This board features the MAX31825, a temperature sensor that provides 8-bit to 12-bit Celsius temperature measurements with better than ±1.75°C from -45°C to +145°C from Analog Devices. It has a unique 64-bit serial code stored in an on-chip ROM, an alarm output for detection of temperature faults, temperature resolution selection from 8 to 12 bits, and it allows temperature conversion to 10-bit digital word in a period of 80ms (max).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo19_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/thermo-19-click)

---


#### Click library

- **Author**        : Nikola Citakovic
- **Date**          : Feb 2022.
- **Type**          : PWM type


# Software Support

We provide a library for the Thermo 19 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Thermo 19 Click driver.

#### Standard key functions :

- `thermo19_cfg_setup` Config Object Initialization function.
```c
void thermo19_cfg_setup ( thermo19_cfg_t *cfg );
```

- `thermo19_init` Initialization function.
```c
err_t thermo19_init ( thermo19_t *ctx, thermo19_cfg_t *cfg );
```

- `thermo19_default_cfg` Click Default Configuration function.
```c
err_t thermo19_default_cfg ( thermo19_t *ctx );
```

#### Example key functions :

- `thermo19_write_scratchpad` This function writes the temperature thresholds and configuration byte to the scratchpad.
```c
err_t thermo19_write_scratchpad ( thermo19_t *ctx, uint16_t temp_high, uint16_t temp_low, uint8_t config );
```

- `thermo19_read_scratchpad` This function reads the scratchpad bytes.
```c
err_t thermo19_read_scratchpad ( thermo19_t *ctx, uint8_t *scratchpad );
```

- `thermo19_read_temperature` This function reads the temperature value in Celsius.
```c
err_t thermo19_read_temperature ( thermo19_t *ctx, float *temperature );
```

## Example Description

> This example demonstrates the use of Thermo 19 Click board by reading and displaying the temperature in Celsius.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo19_cfg_t thermo19_cfg;  /**< Click config object. */

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
    thermo19_cfg_setup( &thermo19_cfg );
    THERMO19_MAP_MIKROBUS( thermo19_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == thermo19_init( &thermo19, &thermo19_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO19_ERROR == thermo19_default_cfg ( &thermo19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays the temperature measured by the Click board on the USB UART
approximately every 400ms as this matches the required conversion time for 12-bit temperature resolution.

```c
void application_task ( void )
{
    float temperature;
    if ( THERMO19_OK == thermo19_read_temperature ( &thermo19, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo19

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
