
---
# Angle 7 Click

> Angle 7 Click is a compact add-on board that detects the absolute angular position of a permanent magnet. This board features the AS5600, a programmable Hall-based rotary magnetic position sensor with a high-resolution 12-bit analog or PWM output from ams AG.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/angle7_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/angle-7-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : May 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Angle 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Angle 7 Click driver.

#### Standard key functions :

- `angle7_cfg_setup` Config Object Initialization function.
```c
void angle7_cfg_setup ( angle7_cfg_t *cfg );
```

- `angle7_init` Initialization function.
```c
err_t angle7_init ( angle7_t *ctx, angle7_cfg_t *cfg );
```

- `angle7_default_cfg` Click Default Configuration function.
```c
err_t angle7_default_cfg ( angle7_t *ctx );
```

#### Example key functions :

- `angle7_get_status` This function reads the status data.
```c
err_t angle7_get_status ( angle7_t *ctx, uint8_t *status );
```

- `angle7_get_angle` This function reads the calculated angle in degrees.
```c
err_t angle7_get_angle ( angle7_t *ctx, float *angle );
```

- `angle7_get_magnitude` This function reads the magnitude data.
```c
err_t angle7_get_magnitude ( angle7_t *ctx, uint16_t *magnitude );
```

## Example Description

> This example demonstrates the use of Angle 7 Click board by reading and displaying
the magnet's angular position in degrees and analog voltage output as well as
the magnet's status and magnitude.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    angle7_cfg_t angle7_cfg;  /**< Click config object. */

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
    angle7_cfg_setup( &angle7_cfg );
    ANGLE7_MAP_MIKROBUS( angle7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == angle7_init( &angle7, &angle7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ANGLE7_ERROR == angle7_default_cfg ( &angle7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the magnet's angular position in degrees and analog voltage output
as well as the magnet's status and magnitude and displays the results on the USB UART approximately every 100ms.

```c
void application_task ( void )
{
    float voltage, raw_angle, angle;
    uint16_t magnitude;
    uint8_t status;
    if ( ADC_ERROR != angle7_read_an_pin_voltage ( &angle7, &voltage ) ) 
    {
        log_printf( &logger, " AN voltage: %.3f V\r\n", voltage );
    }
    if ( ANGLE7_OK == angle7_get_angle ( &angle7, &angle ) )
    {
        log_printf ( &logger, " Angle: %.2f Degrees\r\n", angle );
    }
    if ( ANGLE7_OK == angle7_get_magnitude ( &angle7, &magnitude ) )
    {
        log_printf ( &logger, " Magnitude: %u\r\n", magnitude );
    }
    if ( ANGLE7_OK == angle7_get_status ( &angle7, &status ) )
    {
        log_printf ( &logger, " Status:" );
        if ( status & ANGLE7_STATUS_MAGNET_DETECTED )
        {
            log_printf ( &logger, " Magnet Detected \r\n Magnet Strength:" );
            if ( status & ANGLE7_STATUS_MAGNET_TOO_STRONG )
            {
                log_printf ( &logger, " Too Strong \r\n\n" );
            }
            else if ( status & ANGLE7_STATUS_MAGNET_TOO_WEAK )
            {
                log_printf ( &logger, " Too Weak \r\n\n" );
            }
            else
            {
                log_printf ( &logger, " Good \r\n\n" );
            }
        }
        else
        {
            log_printf ( &logger, " Magnet Not Detected \r\n\n" );
        }
    }
    Delay_ms ( 100 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
