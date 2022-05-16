\mainpage Main Page

---
# Ambient 17 click

> Ambient 17 Click is a compact add-on board used to measure the amount of the present ambient light. This board features the TSL2572, a digital-output ambient light sensor with an I2C interface from ams AG. The TSL2572 can detect a wide range of illuminance up to 60klx and provides excellent responsivity close to the human eyes' response. It is designed to control the brightness in various applications based on ambient light availability, brightness for optimum visibility, and energy efficiency. Operation in a temperature range of -30°C to 70°C ensures stable operation under extreme conditions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient17_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ambient-17-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Ambient 17 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Ambient 17 Click driver.

#### Standard key functions :

- `ambient17_cfg_setup` Config Object Initialization function.
```c
void ambient17_cfg_setup ( ambient17_cfg_t *cfg );
```

- `ambient17_init` Initialization function.
```c
err_t ambient17_init ( ambient17_t *ctx, ambient17_cfg_t *cfg );
```

- `ambient17_default_cfg` Click Default Configuration function.
```c
err_t ambient17_default_cfg ( ambient17_t *ctx );
```

#### Example key functions :

- `ambient17_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t ambient17_get_int_pin ( ambient17_t *ctx );
```

- `ambient17_set_atime` This function sets the ATIME register for the selected ALS integration time.
```c
err_t ambient17_set_atime ( ambient17_t *ctx, float atime_ms );
```

- `ambient17_measure_light_level` This function reads the raw ADC data from two channels and then measures the light level in lux based on those readings.
```c
err_t ambient17_measure_light_level ( ambient17_t *ctx, uint16_t *lux );
```

## Example Description

> This example demonstrates the use of Ambient 17 click board by measuring the ambient light level in Lux.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient17_cfg_t ambient17_cfg;  /**< Click config object. */

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
    ambient17_cfg_setup( &ambient17_cfg );
    AMBIENT17_MAP_MIKROBUS( ambient17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient17_init( &ambient17, &ambient17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT17_ERROR == ambient17_default_cfg ( &ambient17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the data ready interrupt, then reads the ambient light level in Lux and displays the results on the USB UART. By default, the data ready interrupt triggers 
upon every ADC cycle which will be performed every 200ms.

```c
void application_task ( void )
{
    if ( !ambient17_get_int_pin ( &ambient17 ) )
    {
        uint16_t lux;
        if ( AMBIENT17_OK == ambient17_measure_light_level ( &ambient17, &lux ) )
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
- Click.Ambient17

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
