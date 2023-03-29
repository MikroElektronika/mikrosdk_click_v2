\mainpage Main Page

---
# BATT-MON 2 click

> BATT-MON 2 Click is a compact add-on board representing a battery monitoring solution. 
> This board features the MAX17262, an ultra-low power I2C-configurable fuel-gauge IC which implements the ModelGauge™ m5 algorithm from Analog Devices. 
> The MAX17262 monitors a single-cell battery pack (best performance for batteries with 100mAhr to 6Ahr capacity), 
> providing precision measurements of current, voltage, and temperature, and supporting internal current sensing for up to 3.1A pulse current. 
> The battery pack's temperature is measured using an internal temperature sensor or external thermistor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/battmon2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/batt-mon-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the BATT-MON 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for BATT-MON 2 Click driver.

#### Standard key functions :

- `battmon2_cfg_setup` Config Object Initialization function.
```c
void battmon2_cfg_setup ( battmon2_cfg_t *cfg );
```

- `battmon2_init` Initialization function.
```c
err_t battmon2_init ( battmon2_t *ctx, battmon2_cfg_t *cfg );
```

#### Example key functions :

- `battmon2_get_battery_voltage` This function reads the battery voltage in mV.
```c
err_t battmon2_get_battery_voltage ( battmon2_t *ctx, float *voltage );
```

- `battmon2_get_battery_current` This function reads the battery current in mA.
```c
err_t battmon2_get_battery_current ( battmon2_t *ctx, float *current );
```

- `battmon2_get_battery_percentage` This function reads the battery remaining SOC percentage.
```c
err_t battmon2_get_battery_percentage ( battmon2_t *ctx, float *percentage );
```

## Example Description

> This example demonstrates the use of BATT-MON 2 click board by monitoring
the measurements of battery voltage, current, capacity, percentage, time-to-empty or time-to-full,
as well as the chip internal temperature.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and checks the communication by reading and verifying the device ID.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    battmon2_cfg_t battmon2_cfg;  /**< Click config object. */

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
    battmon2_cfg_setup( &battmon2_cfg );
    BATTMON2_MAP_MIKROBUS( battmon2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == battmon2_init( &battmon2, &battmon2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BATTMON2_ERROR == battmon2_check_communication ( &battmon2 ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays on the USB UART the measurements of battery voltage, current, capacity, percentage, 
time-to-empty or time-to-full, as well as the chip internal temperature approximately once per second.

```c
void application_task ( void )
{
    float voltage, capacity, percentage, current, die_temp;
    if ( BATTMON2_OK == battmon2_get_battery_voltage ( &battmon2, &voltage ) )
    {
        log_printf ( &logger, " Voltage: %.1f mV \r\n", voltage );
    }
    if ( BATTMON2_OK == battmon2_get_battery_current ( &battmon2, &current ) )
    {
        log_printf ( &logger, " Current: %.1f mA \r\n", current );
    }
    if ( BATTMON2_OK == battmon2_get_battery_capacity ( &battmon2, &capacity ) )
    {
        log_printf ( &logger, " Capacity: %.1f mAh \r\n", capacity );
    }
    if ( BATTMON2_OK == battmon2_get_battery_percentage ( &battmon2, &percentage ) )
    {
        log_printf ( &logger, " Percentage: %.1f %% \r\n", percentage );
    }
    if ( current > 0 )
    {
        uint32_t time_to_full;
        if ( BATTMON2_OK == battmon2_get_battery_ttf ( &battmon2, &time_to_full ) )
        {
            log_printf ( &logger, " Time to full: %uh %umin %usec \r\n", ( uint16_t ) ( time_to_full / 3600 ), 
                                                                         ( uint16_t ) ( time_to_full % 3600 ) / 60,
                                                                         ( uint16_t ) ( time_to_full % 60 ) );
        }
    }
    else if ( current < 0 )
    {
        uint32_t time_to_empty;
        if ( BATTMON2_OK == battmon2_get_battery_tte ( &battmon2, &time_to_empty ) )
        {
            log_printf ( &logger, " Time to empty: %uh %umin %usec \r\n", ( uint16_t ) ( time_to_empty / 3600 ), 
                                                                          ( uint16_t ) ( time_to_empty % 3600 ) / 60,
                                                                          ( uint16_t ) ( time_to_empty % 60 ) );
        }
    }
    if ( BATTMON2_OK == battmon2_get_die_temperature ( &battmon2, &die_temp ) )
    {
        log_printf ( &logger, " Internal temperature: %.2f C \r\n\n", die_temp );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BATTMON2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
