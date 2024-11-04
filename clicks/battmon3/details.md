
---
# BATT-MON 3 Click

> BATT-MON 3 Click is a compact add-on board representing an advanced battery monitoring solution. This board features the BQ35100, battery fuel gauge, and end-of-service monitor from Texas Instruments. The BQ35100 provides highly configurable fuel gauging for non-rechargeable (primary) lithium batteries without requiring a forced battery discharge. It uses patented TI gauging algorithms to support the option to replace an old battery with a new one seamlessly. It provides accurate results with ultra-low average power consumption, alongside an I2C interface through which the host can read the gathered data.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/battmon3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/batt-mon-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the BATT-MON 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for BATT-MON 3 Click driver.

#### Standard key functions :

- `battmon3_cfg_setup` Config Object Initialization function.
```c
void battmon3_cfg_setup ( battmon3_cfg_t *cfg );
```

- `battmon3_init` Initialization function.
```c
err_t battmon3_init ( battmon3_t *ctx, battmon3_cfg_t *cfg );
```

- `battmon3_default_cfg` Click Default Configuration function.
```c
err_t battmon3_default_cfg ( battmon3_t *ctx );
```

#### Example key functions :

- `battmon3_read_voltage` This function reads the battery voltage in millivolts.
```c
err_t battmon3_read_voltage ( battmon3_t *ctx, uint16_t *voltage );
```

- `battmon3_read_current` This function reads the battery current load from BATT+ to GND in milliampers.
```c
err_t battmon3_read_current ( battmon3_t *ctx, int16_t *current );
```

- `battmon3_read_used_capacity` This function reads the used battery capacity in mAh.
```c
err_t battmon3_read_used_capacity ( battmon3_t *ctx, float *used_capacity );
```

## Example Description

> This example demonstrates the use of BATT-MON 3 Click by measuring the battery
voltage, current and used capacity, as well as the chip internal temperature.

**The demo application is composed of two sections :**

### Application Init

> Initialized the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    battmon3_cfg_t battmon3_cfg;  /**< Click config object. */

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
    battmon3_cfg_setup( &battmon3_cfg );
    BATTMON3_MAP_MIKROBUS( battmon3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == battmon3_init( &battmon3, &battmon3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BATTMON3_ERROR == battmon3_default_cfg ( &battmon3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the battery voltage (mV), current (mA), used capacity (mAh) and the chip internal 
temperature (Celsius) and displays the results on the USB UART approximately once per second. 

```c
void application_task ( void )
{
    uint16_t voltage;
    int16_t current;
    float temperature, used_capacity;
    if ( BATTMON3_OK == battmon3_read_voltage ( &battmon3, &voltage ) )
    {
        log_printf ( &logger, " Voltage: %u mV\r\n", voltage );
    }
    
    if ( BATTMON3_OK == battmon3_read_current ( &battmon3, &current ) )
    {
        log_printf ( &logger, " Current: %d mA\r\n", current );
    }
    
    if ( BATTMON3_OK == battmon3_read_temperature ( &battmon3, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.3f C\r\n", temperature );
    }
    
    if ( BATTMON3_OK == battmon3_read_used_capacity ( &battmon3, &used_capacity ) )
    {
        log_printf ( &logger, " Used Capacity: %.3f mAh\r\n\n", used_capacity );
    }
    
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BATTMON3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
