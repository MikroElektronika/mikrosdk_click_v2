
---
# Ambient 15 click

> Ambient 15 Click is a compact add-on board used to measure the amount of the present ambient light. This board features the TSL2584TSV, a very-high sensitivity light-to-digital converter with an I2C interface that transforms light intensity into a digital output signal from AMS-AG. The TSL2584TSV’s near-photopic response produces a highly accurate lux measurement up to 33klx even when mounted behind dark glass. Filtering out unwanted IR light enables the sensor to measure the ambient light more accurately, thus producing a near-photopic response.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient15_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ambient-15-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Ambient15 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Ambient15 Click driver.

#### Standard key functions :

- `ambient15_cfg_setup` Config Object Initialization function.
```c
void ambient15_cfg_setup ( ambient15_cfg_t *cfg );
```

- `ambient15_init` Initialization function.
```c
err_t ambient15_init ( ambient15_t *ctx, ambient15_cfg_t *cfg );
```

- `ambient15_default_cfg` Click Default Configuration function.
```c
err_t ambient15_default_cfg ( ambient15_t *ctx );
```

#### Example key functions :

- `ambient15_set_atime` This function sets the timing register for the selected integration time.
```c
err_t ambient15_set_atime ( ambient15_t *ctx, float atime_ms );
```

- `ambient15_set_gain` This function sets the gain level.
```c
err_t ambient15_set_gain ( ambient15_t *ctx, uint8_t gain );
```

- `ambient15_measure_light_level` This function reads the raw ADC data from two channels and then measures the light level in lux based on those readings.
```c
err_t ambient15_measure_light_level ( ambient15_t *ctx, uint16_t *lux );
```

## Example Description

> This example demonstrates the use of Ambient 15 click board by measuring the ambient light level in Lux.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient15_cfg_t ambient15_cfg;  /**< Click config object. */

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
    ambient15_cfg_setup( &ambient15_cfg );
    AMBIENT15_MAP_MIKROBUS( ambient15_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient15_init( &ambient15, &ambient15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT15_ERROR == ambient15_default_cfg ( &ambient15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the data ready interrupt, then reads the ambient light level in Lux
and displays the results on the USB UART. By default, the data ready interrupt triggers
upon every ADC cycle which will be performed every 200ms.

```c

void application_task ( void )
{
    if ( !ambient15_get_int_pin ( &ambient15 ) )
    {
        uint16_t lux;
        if ( AMBIENT15_OK == ambient15_measure_light_level ( &ambient15, &lux ) )
        {
            log_printf ( &logger, " Ambient light level [Lux]: %u\r\n\n", lux );
        }
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient15

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
