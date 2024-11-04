
---
# Gyro 8 Click

> Gyro 8 Click is a compact add-on board that contains a high-performance gyroscope. This board features Murata's SCR2100-D08, a high-performance single-axis angular rate sensor (gyroscope). Based on Murata's proven capacitive 3D-MEMS technology, the SCR2100-D08 is characterized by high stability and reliability, providing immensely stable output over a wide range of temperatures, humidity, and vibration. This high-resolution gyroscope supports ±125°/s X-axis angular rate measurement range, extensive self-diagnostic features, an SPI serial interface, and low power consumption.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gyro8_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/gyro-8-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the Gyro 8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Gyro 8 Click driver.

#### Standard key functions :

- `gyro8_cfg_setup` Config Object Initialization function.
```c
void gyro8_cfg_setup ( gyro8_cfg_t *cfg );
```

- `gyro8_init` Initialization function.
```c
err_t gyro8_init ( gyro8_t *ctx, gyro8_cfg_t *cfg );
```

- `gyro8_default_cfg` Click Default Configuration function.
```c
err_t gyro8_default_cfg ( gyro8_t *ctx );
```

#### Example key functions :

- `gyro8_read_serial_id` This function reads the serial ID which is laser marked on the sensor lid.
```c
err_t gyro8_read_serial_id ( gyro8_t *ctx, uint32_t *serial_id );
```

- `gyro8_read_temperature` This function reads the temperature measurement in Celsius.
```c
err_t gyro8_read_temperature ( gyro8_t *ctx, float *temperature );
```

- `gyro8_read_angular_rate` This function reads the angular rate of X-axis in dps.
```c
err_t gyro8_read_angular_rate ( gyro8_t *ctx, float *rate );
```

## Example Description

> This example demonstrates the use of Gyro 8 Click board by reading and displaying the temperature and angular rate measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and the Click board, and reads the serial ID number which is marked on the sensor lid.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gyro8_cfg_t gyro8_cfg;  /**< Click config object. */

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
    gyro8_cfg_setup( &gyro8_cfg );
    GYRO8_MAP_MIKROBUS( gyro8_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == gyro8_init( &gyro8, &gyro8_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( GYRO8_ERROR == gyro8_default_cfg ( &gyro8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint32_t serial_id;
    if ( GYRO8_OK == gyro8_read_serial_id ( &gyro8, &serial_id ) )
    {
        log_printf ( &logger, " Serial ID: %lu\r\n", serial_id );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the temperature and angular rate measurements every 100ms and displays the results on the USB UART.

```c
void application_task ( void )
{
    float temperature, angular_rate;
    if ( GYRO8_OK == gyro8_read_temperature ( &gyro8, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n", temperature );
    }
    if ( GYRO8_OK == gyro8_read_angular_rate ( &gyro8, &angular_rate ) )
    {
        log_printf ( &logger, " Angular rate: %.2f dps\r\n\n", angular_rate );
    }
    Delay_ms ( 100 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Gyro8

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
