
---
# Accel 25 click

> Accel 25 Click is a compact add-on board that contains an acceleration sensor. This board features the MXC4005XC, a 12-bit three-axis thermal accelerometer from MEMSIC. It allows selectable full-scale acceleration measurements of ±2g, ±4g, or ±8g in three axes with a compatible I2C serial interface with 400KHz fast mode operation. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel25_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/accel-25-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Accel 25 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Accel 25 Click driver.

#### Standard key functions :

- `accel25_cfg_setup` Config Object Initialization function.
```c
void accel25_cfg_setup ( accel25_cfg_t *cfg );
```

- `accel25_init` Initialization function.
```c
err_t accel25_init ( accel25_t *ctx, accel25_cfg_t *cfg );
```

- `accel25_default_cfg` Click Default Configuration function.
```c
err_t accel25_default_cfg ( accel25_t *ctx );
```

#### Example key functions :

- `accel25_soft_reset` Accel 25 soft reset function.
```c
err_t accel25_soft_reset ( accel25_t *ctx );
```

- `accel25_set_full_scale_range` Accel 25 set full scale range function.
```c
err_t accel25_set_full_scale_range ( accel25_t *ctx, uint8_t fsr );
```

- `accel25_read_data` Accel 25 read data function.
```c
err_t accel25_read_data ( accel25_t *ctx, accel25_data_t *data_out );
```

## Example Description

> This example demonstrates the use of Accel 25 click board by reading and displaying 
 accel data (X, Y, and Z axis) as well as temperature measurements on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel25_cfg_t accel25_cfg;  /**< Click config object. */

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
    accel25_cfg_setup( &accel25_cfg );
    ACCEL25_MAP_MIKROBUS( accel25_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == accel25_init( &accel25, &accel25_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL25_ERROR == accel25_default_cfg ( &accel25 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays the accel data (X, Y, and Z axis) as well as temperature measurements
 on the USB UART every 100ms approximately.

```c
void application_task ( void ) 
{
    accel25_data_t meas_data;
    // Wait for data ready indication
    if ( ACCEL25_PIN_STATE_LOW == accel25_get_int_pin ( &accel25 ) );
    {
        if ( ACCEL25_OK == accel25_read_data ( &accel25, &meas_data ) )
        {
            log_printf( &logger, " X: %.3f g\r\n", meas_data.x );
            log_printf( &logger, " Y: %.3f g\r\n", meas_data.y );
            log_printf( &logger, " Z: %.3f g\r\n", meas_data.z );
            log_printf( &logger, " Temperature: %.2f degC\r\n", meas_data.temperature );
        }
    Delay_ms ( 100 );
    }
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel25

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
