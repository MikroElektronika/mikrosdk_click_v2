\mainpage Main Page

---
# Thermo 23 click

> Thermo 23 Click is a compact add-on board that provides an accurate temperature measurement. This board features the TMP144, a high-precision digital temperature sensor from Texas Instruments. The temperature sensor in the TMP144 is the chip itself, that houses temperature sensor circuitry, 12-bit analog-to-digital converter (ADC), a control logic, and a serial interface block in one package. Characterized by its high accuracy (up to ±0.5°C typical) and high resolution of 0.0625°C, this temperature sensor provides temperature data to the host controller with a configurable UART interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo23_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermo-23-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : UART type


# Software Support

We provide a library for the Thermo 23 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Thermo 23 Click driver.

#### Standard key functions :

- `thermo23_cfg_setup` Config Object Initialization function.
```c
void thermo23_cfg_setup ( thermo23_cfg_t *cfg );
```

- `thermo23_init` Initialization function.
```c
err_t thermo23_init ( thermo23_t *ctx, thermo23_cfg_t *cfg );
```

- `thermo23_default_cfg` Click Default Configuration function.
```c
err_t thermo23_default_cfg ( thermo23_t *ctx );
```

#### Example key functions :

- `thermo23_set_config` This function sets the configuration register.
```c
err_t thermo23_set_config ( thermo23_t *ctx, uint16_t config );
```

- `thermo23_read_temperature` This function reads the temperature value in Celsius.
```c
err_t thermo23_read_temperature ( thermo23_t *ctx, float *temperature );
```

- `thermo23_read_command` This function reads data from the selected command by using UART serial interface.
```c
err_t thermo23_read_command ( thermo23_t *ctx, uint8_t cmd, uint16_t *data_out );
```

## Example Description

> This example demonstrates the use of Thermo 23 click board by reading and displaying the temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger, and performs the click default configuration which enables continuous conversion and sets the conversion rate to 1 Hz.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo23_cfg_t thermo23_cfg;  /**< Click config object. */

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
    thermo23_cfg_setup( &thermo23_cfg );
    THERMO23_MAP_MIKROBUS( thermo23_cfg, MIKROBUS_1 );
    if ( UART_ERROR == thermo23_init( &thermo23, &thermo23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO23_ERROR == thermo23_default_cfg ( &thermo23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the temperature measurement in Celsius and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float temperature;
    if ( THERMO23_OK == thermo23_read_temperature ( &thermo23, &temperature ) ) 
    {
        log_printf( &logger, " Temperature : %.2f C\r\n\n", temperature );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo23

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
