\mainpage Main Page

---
# Ambient 21 Click

> Ambient 21 Click is a compact add-on board used to measure the amount of the present ambient light. This board features ams AG's TSL2591, a very-high sensitivity light-to-digital converter that transforms light intensity to a digital signal output capable of the direct I2C interface. It combines one broadband photodiode (visible plus infrared) and one infrared-responding photodiode on a single CMOS integrated circuit, providing a flexible and wide operating range of up to 88klx with an excellent responsivity close to the human eyes' response. The TSL2591 also has a programmable interrupt function and an integrated filter to reduce unwanted IR signals from the environment, improving lux accuracy across various light sources.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient21_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ambient-21-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Ambient 21 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Ambient 21 Click driver.

#### Standard key functions :

- `ambient21_cfg_setup` Config Object Initialization function.
```c
void ambient21_cfg_setup ( ambient21_cfg_t *cfg );
```

- `ambient21_init` Initialization function.
```c
err_t ambient21_init ( ambient21_t *ctx, ambient21_cfg_t *cfg );
```

- `ambient21_default_cfg` Click Default Configuration function.
```c
err_t ambient21_default_cfg ( ambient21_t *ctx );
```

#### Example key functions :

- `ambient21_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t ambient21_get_int_pin ( ambient21_t *ctx );
```

- `ambient21_read_raw_data` This function checks if the data is ready and then reads the raw ADC data from two channels.
```c
err_t ambient21_read_raw_data ( ambient21_t *ctx, uint16_t *ch_0, uint16_t *ch_1 );
```

- `ambient21_measure_light_level` This function reads the raw ADC data from two channels and then measures the light level in lux based on those readings.
```c
err_t ambient21_measure_light_level ( ambient21_t *ctx, uint16_t *lux );
```

## Example Description

> This example demonstrates the use of Ambient 21 Click board by measuring the ambient light level in Lux.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient21_cfg_t ambient21_cfg;  /**< Click config object. */

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
    ambient21_cfg_setup( &ambient21_cfg );
    AMBIENT21_MAP_MIKROBUS( ambient21_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient21_init( &ambient21, &ambient21_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT21_ERROR == ambient21_default_cfg ( &ambient21 ) )
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
upon every ADC cycle which occurs every 200ms.

```c
void application_task ( void )
{
    uint16_t lux;
    if ( !ambient21_get_int_pin ( &ambient21 ) )
    {
        if ( AMBIENT21_OK == ambient21_measure_light_level ( &ambient21, &lux ) )
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
- Click.Ambient21

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
