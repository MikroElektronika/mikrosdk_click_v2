
---
# Ambient 14 Click

> Ambient 14 Click is a compact add-on board for ambient light and proximity detection applications. This board features the TMD2755, an advanced sensor from ams OSRAM, which combines ambient light sensing (ALS) and proximity detection in a single, compact module. The TMD2755 features an integrated infrared VCSEL and driver and a proximity engine that includes offset adjustment and ambient light subtraction for enhanced accuracy. It provides 16-bit data output for ALS and proximity detection, allowing precise control of backlight brightness in devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient14_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ambient-14-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Ambient 14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Ambient 14 Click driver.

#### Standard key functions :

- `ambient14_cfg_setup` Config Object Initialization function.
```c
void ambient14_cfg_setup ( ambient14_cfg_t *cfg );
```

- `ambient14_init` Initialization function.
```c
err_t ambient14_init ( ambient14_t *ctx, ambient14_cfg_t *cfg );
```

- `ambient14_default_cfg` Click Default Configuration function.
```c
err_t ambient14_default_cfg ( ambient14_t *ctx );
```

#### Example key functions :

- `ambient14_read_proximity` This function reads the raw proximity data. The higher the value, the closer the detected object is.
```c
err_t ambient14_read_proximity ( ambient14_t *ctx, uint16_t *prox_data );
```

- `ambient14_read_als_ir` This function reads the raw ALS and IR data.
```c
err_t ambient14_read_als_ir ( ambient14_t *ctx, uint16_t *als_data, uint16_t *ir_data );
```

- `ambient14_get_illuminance` This function calculates the illuminance level (Lux) from ALS data counts input.
```c
err_t ambient14_get_illuminance ( ambient14_t *ctx, uint16_t als_data, float *illuminance );
```

## Example Description

> This example demonstrates the use of Ambient 14 Click board by measuring the illuminance level (Lux) and the proximity data on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient14_cfg_t ambient14_cfg;  /**< Click config object. */

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
    ambient14_cfg_setup( &ambient14_cfg );
    AMBIENT14_MAP_MIKROBUS( ambient14_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient14_init( &ambient14, &ambient14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT14_ERROR == ambient14_default_cfg ( &ambient14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the proximity, ALS, and IR raw data counts when data is ready.
Calculates the illuminance level in Lux from ALS data counts and displays the results on the USB UART approximately every 500ms.

```c
void application_task ( void )
{
    uint16_t proximity = 0;
    uint16_t als_data = 0;
    uint16_t ir_data = 0;
    float illuminance = 0;
    
    // Enable and wait for proximity interrupt
    ambient14_write_reg ( &ambient14, AMBIENT14_REG_INTENAB, AMBIENT14_INTENAB_PIEN );
    while ( ambient14_get_int_pin ( &ambient14 ) );

    // Read proximity data and clear interrupts
    if ( AMBIENT14_OK == ambient14_read_proximity ( &ambient14, &proximity ) )
    {
        log_printf ( &logger, " Proximity: %u\r\n", proximity );
    }
    ambient14_clear_interrupts ( &ambient14 );

    // Enable and wait for ALS interrupt
    ambient14_write_reg ( &ambient14, AMBIENT14_REG_INTENAB, AMBIENT14_INTENAB_AIEN );
    while ( ambient14_get_int_pin ( &ambient14 ) );

    // Read ALS and IR data counts, calculates illuminance level, and clear interrupts
    if ( AMBIENT14_OK == ambient14_read_als_ir ( &ambient14, &als_data, &ir_data ) )
    {
        log_printf ( &logger, " ALS: %u\r\n", als_data );
        log_printf ( &logger, " IR: %u\r\n", ir_data );
        if ( AMBIENT14_OK == ambient14_get_illuminance ( &ambient14, als_data, &illuminance ) )
        {
            log_printf ( &logger, " Illuminance: %.1f Lux\r\n\n", illuminance );
        }
    }
    ambient14_clear_interrupts ( &ambient14 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
