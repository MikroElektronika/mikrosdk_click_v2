\mainpage Main Page

---
# Accel 24 Click

> Accel 24 Click is a compact add-on board that contains an acceleration sensor. This board features the MXC6655XA, a 12-bit three-axis accelerometer from MEMSIC. It allows selectable full-scale acceleration measurements in ranges of ±2g, ±4g, or ±8g in three axes with a compatible I2C serial interface with 400KHz fast mode operation. Alongside low offset and temperature signal with high accuracy, the MXC6655XA also detects six orientation positions, X/Y shake, and shake directions with an appropriate interrupt signal for these states.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel24_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/accel-24-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Accel 24 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Accel 24 Click driver.

#### Standard key functions :

- `accel24_cfg_setup` Config Object Initialization function.
```c
void accel24_cfg_setup ( accel24_cfg_t *cfg );
```

- `accel24_init` Initialization function.
```c
err_t accel24_init ( accel24_t *ctx, accel24_cfg_t *cfg );
```

- `accel24_default_cfg` Click Default Configuration function.
```c
err_t accel24_default_cfg ( accel24_t *ctx );
```

#### Example key functions :

- `accel24_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t accel24_get_int_pin ( accel24_t *ctx );
```

- `accel24_read_data` This function checks the data ready bit, clears it, and then reads the accel (X, Y, Z) and temperature measurements.
```c
err_t accel24_read_data ( accel24_t *ctx, accel24_data_t *data_out );
```

- `accel24_set_full_scale_range` This function sets the full scale range resolution.
```c
err_t accel24_set_full_scale_range ( accel24_t *ctx, uint8_t fsr );
```

## Example Description

> This example demonstrates the use of Accel 24 Click board by reading and displaying accel data (X, Y, and Z axis) as well as temperature measurements on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel24_cfg_t accel24_cfg;  /**< Click config object. */

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
    accel24_cfg_setup( &accel24_cfg );
    ACCEL24_MAP_MIKROBUS( accel24_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == accel24_init( &accel24, &accel24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL24_ERROR == accel24_default_cfg ( &accel24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays the accel data (X, Y, and Z axis) as well as temperature measurements on the USB UART every 100ms approximately.

```c
void application_task ( void )
{
    accel24_data_t meas_data;
    // Wait for data ready indication
    while ( accel24_get_int_pin ( &accel24 ) );
    
    if ( ACCEL24_OK == accel24_read_data ( &accel24, &meas_data ) )
    {
        log_printf( &logger, " X: %.3f g\r\n", meas_data.x );
        log_printf( &logger, " Y: %.3f g\r\n", meas_data.y );
        log_printf( &logger, " Z: %.3f g\r\n", meas_data.z );
        log_printf( &logger, " Temperature: %.2f degC\r\n", meas_data.temperature );
    }
    Delay_ms ( 100 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel24

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
