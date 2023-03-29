
---
# Thermo 29 click

> Thermo 29 Click is a compact add-on board for accurate temperature measurements. This board features the TMP126, a high-accuracy SPI-configurable digital temperature sensor from Texas Instruments. The TMP126 consists of an internal thermal BJT factory-calibrated sensor, 14-bit ADC, and a digital signal processor, offering a high accuracy of ±0.25°C and a temperature resolution of 0.03125°C per LSB. It also has a programmable alarm function that outputs an interrupt signal to the MCU when a specific temperature event occurs.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermo29_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermo-29-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the Thermo 29 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Thermo 29 Click driver.

#### Standard key functions :

- `thermo29_cfg_setup` Config Object Initialization function.
```c
void thermo29_cfg_setup ( thermo29_cfg_t *cfg );
```

- `thermo29_init` Initialization function.
```c
err_t thermo29_init ( thermo29_t *ctx, thermo29_cfg_t *cfg );
```

- `thermo29_default_cfg` Click Default Configuration function.
```c
err_t thermo29_default_cfg ( thermo29_t *ctx );
```

#### Example key functions :

- `thermo29_read_unique_id` This function reads the device unique ID words (6 bytes in total).
```c
err_t thermo29_read_unique_id ( thermo29_t *ctx, uint16_t *unique_id );
```

- `thermo29_get_alert_pin` This function returns the alert pin logic state.
```c
uint8_t thermo29_get_alert_pin ( thermo29_t *ctx );
```

- `thermo29_read_temperature` This function reads the temperature measurement in degrees Celsius.
```c
err_t thermo29_read_temperature ( thermo29_t *ctx, float *temperature );
```

## Example Description

> This example demonstrates the use of Thermo 29 click board by reading and displaying the temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger, and performs the click default configuration which enables
continuous conversion and sets the conversion rate to 1 Hz with a data ready flag enabled on
the alert pin. After that, reads and displays the device 48-bit unique ID.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo29_cfg_t thermo29_cfg;  /**< Click config object. */

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
    thermo29_cfg_setup( &thermo29_cfg );
    THERMO29_MAP_MIKROBUS( thermo29_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == thermo29_init( &thermo29, &thermo29_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMO29_ERROR == thermo29_default_cfg ( &thermo29 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint16_t unique_id[ 3 ];
    if ( THERMO29_OK == thermo29_read_unique_id ( &thermo29, unique_id ) )
    {
        log_printf ( &logger, " Device Unique ID: 0x%.2X%.2X%.2X\r\n", 
                     unique_id[ 0 ], unique_id[ 1 ], unique_id[ 2 ] );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the data ready alert flag, then reads the temperature measurement in Celsius
and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float temperature;
    // Wait for the data ready alert flag
    while ( thermo29_get_alert_pin ( &thermo29 ) );
    
    if ( ( THERMO29_OK == thermo29_clear_alert_status ( &thermo29 ) ) && 
         ( THERMO29_OK == thermo29_read_temperature ( &thermo29, &temperature ) ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n\n", temperature );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo29

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
