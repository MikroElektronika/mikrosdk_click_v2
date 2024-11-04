\mainpage Main Page

---
# Charger Click

> Charger Click is a compact add-on board providing a standalone battery charger and monitor. This board features Microchip's MCP73831, a miniature single-cell, fully integrated Li-Ion, Li-Polymer charge management controller. The charge voltage of the MCP73831 is set to 4.20V, and a charge current to 250mA with an external resistor. In addition, this Click board™ features the DS2438, a smart battery monitor that monitors the total amount of current going into and out of the battery.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/charger_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/charger-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2024.
- **Type**          : One Wire type


# Software Support

We provide a library for the Charger Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Charger Click driver.

#### Standard key functions :

- `charger_cfg_setup` Config Object Initialization function.
```c
void charger_cfg_setup ( charger_cfg_t *cfg );
```

- `charger_init` Initialization function.
```c
err_t charger_init ( charger_t *ctx, charger_cfg_t *cfg );
```

- `charger_default_cfg` Click Default Configuration function.
```c
err_t charger_default_cfg ( charger_t *ctx );
```

#### Example key functions :

- `charger_read_temperature` This function reads the chip internal temperature measurement in degrees Celsius.
```c
err_t charger_read_temperature ( charger_t *ctx, float *temperature );
```

- `charger_read_batt_vdd` This function reads the battery input voltage.
```c
err_t charger_read_batt_vdd ( charger_t *ctx, float *voltage );
```

- `charger_read_current` This function reads the battery charging current.
```c
err_t charger_read_current ( charger_t *ctx, float *current );
```

## Example Description

> This example demonstrates the use of Charger Click board by monitoring the battery charging status.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the Click default configuration, calibrates the zero current charging offset, and resets the elapsed time counter.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger_cfg_t charger_cfg;  /**< Click config object. */

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
    charger_cfg_setup( &charger_cfg );
    CHARGER_MAP_MIKROBUS( charger_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == charger_init( &charger, &charger_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CHARGER_ERROR == charger_default_cfg ( &charger ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf( &logger, "\r\n Zero current calibration process\r\n" );
    log_printf( &logger, " Keep the battery disconnected in the next 5 seconds\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( CHARGER_ERROR == charger_calibrate_current ( &charger ) )
    {
        log_error( &logger, " Calibration." );
        for ( ; ; );
    }
    log_printf( &logger, " Calibration done!\r\n\n" );

    if ( CHARGER_OK == charger_write_elapsed_time ( &charger, 0 ) )
    {
        log_printf( &logger, " Elapsed time reset done!\r\n\n" );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the chip internal temperature, battery and system VDD, battery charging
current, and the elapsed time counter, approximately once per second. All data
are displayed on the USB UART where you can track their changes.

```c
void application_task ( void )
{
    float temperature = 0;
    float batt_vdd = 0;
    float system_vdd = 0;
    float current = 0;
    uint32_t elapsed_time = 0;
    if ( CHARGER_OK == charger_read_temperature ( &charger, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f degC\r\n", temperature );
    }
    if ( CHARGER_OK == charger_read_batt_vdd ( &charger, &batt_vdd ) )
    {
        log_printf( &logger, " Battery VDD: %.3f V\r\n", batt_vdd );
    }
    if ( CHARGER_OK == charger_read_system_vdd ( &charger, &system_vdd ) )
    {
        log_printf( &logger, " System VDD: %.3f V\r\n", system_vdd );
    }
    if ( CHARGER_OK == charger_read_current ( &charger, &current ) )
    {
        log_printf( &logger, " Charging current: %.3f A\r\n", current );
    }
    if ( CHARGER_OK == charger_read_elapsed_time ( &charger, &elapsed_time ) )
    {
        log_printf( &logger, " Elapsed time: %lu s\r\n\n", elapsed_time );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
