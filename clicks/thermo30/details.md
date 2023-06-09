
---
# Thermo 30 click

> Thermo 30 Click is a compact add-on board that accurately measures temperature. This board features the STS32-DIS-10KS, a third-generation, high-reliability, certified digital temperature sensor from Sensirion. It is a digitally calibrated and ISO17025-certified temperature sensor with an operating temperature range of -40 to 125°C. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo30_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermo-30-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Thermo 30 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Thermo 30 Click driver.

#### Standard key functions :

- `thermo30_cfg_setup` Config Object Initialization function.
```c
void thermo30_cfg_setup ( thermo30_cfg_t *cfg );
```

- `thermo30_init` Initialization function.
```c
err_t thermo30_init ( thermo30_t *ctx, thermo30_cfg_t *cfg );
```

- `thermo30_default_cfg` Click Default Configuration function.
```c
err_t thermo30_default_cfg ( thermo30_t *ctx );
```

#### Example key functions :

- `thermo30_hw_reset` Thermo 30 hw reset device function.
```c
void thermo30_hw_reset ( thermo30_t *ctx );
```

- `thermo30_start_measurement` Thermo 30 start measurement function.
```c
err_t thermo30_start_measurement ( thermo30_t *ctx, uint16_t cmd );
```

- `thermo30_read_temperature` Thermo 30 read temperature function.
```c
err_t thermo30_read_temperature ( thermo30_t *ctx, float *temperature );
```

## Example Description

> This example demonstrates the use of Thermo 30 click board by reading and displaying
  the temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and resets the device, and
  starts the periodic measurements at 1 mps with high repeatability.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo30_cfg_t thermo30_cfg;  /**< Click config object. */

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
    thermo30_cfg_setup( &thermo30_cfg );
    THERMO30_MAP_MIKROBUS( thermo30_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thermo30_init( &thermo30, &thermo30_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
   
    if ( THERMO30_ERROR == thermo30_default_cfg( &thermo30 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the temperature measurement in degrees Celsius and displays the results on the USB UART
  approximately once per second.

```c
void application_task ( void ) 
{
    float temperature;
    
    if ( THERMO30_OK == thermo30_read_temperature( &thermo30, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f deg C\r\n\n", temperature );
    }
    
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo30

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
