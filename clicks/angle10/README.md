\mainpage Main Page

---
# Angle 10 click

> Angle 10 Click is a compact add-on board that detects the absolute angular position of a permanent magnet. 
> This board features the AS5070A, a high-resolution angular position sensor with an analog output for precise absolute angle measurement from ams AG. 
> Based on a Hall sensor technology, the AS5070A measures the orthogonal component of the flux density over a full-turn rotation and compensates 
> for external stray magnetic fields with a robust architecture based on a 14-bit sensor array and analog front-end. 
> Only a simple two-pole magnet rotating over the center of the AS5070A is required to measure the angle, 
> providing an instant indication of the magnet’s angular position.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/angle10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/angle-10-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : ADC type


# Software Support

We provide a library for the Angle 10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Angle 10 Click driver.

#### Standard key functions :

- `angle10_cfg_setup` Config Object Initialization function.
```c
void angle10_cfg_setup ( angle10_cfg_t *cfg );
```

- `angle10_init` Initialization function.
```c
err_t angle10_init ( angle10_t *ctx, angle10_cfg_t *cfg );
```

#### Example key functions :

- `angle10_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t angle10_read_voltage ( angle10_t *ctx, float *voltage );
```

- `angle10_get_angle` This function reads the magnetic angular position in degrees based on @b ANGLE10_NUM_CONVERSIONS of voltage measurements.
```c
err_t angle10_get_angle ( angle10_t *ctx, float *angle );
```

- `angle10_set_vref` This function sets the voltage reference for Angle 10 click driver.
```c
err_t angle10_set_vref ( angle10_t *ctx, float vref );
```

## Example Description

> This example demonstrates the use of Angle 10 click board by reading and displaying the magnet's angular position in degrees and analog voltage output.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    angle10_cfg_t angle10_cfg;  /**< Click config object. */

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
    angle10_cfg_setup( &angle10_cfg );
    ANGLE10_MAP_MIKROBUS( angle10_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == angle10_init( &angle10, &angle10_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the magnet's angular position in degrees and analog voltage output and displays the results on the USB UART approximately every 500ms.

```c

void application_task ( void )
{
    float voltage, angle;
    if ( ANGLE10_OK == angle10_read_voltage ( &angle10, &voltage ) ) 
    {
        log_printf( &logger, " AN Voltage : %.3f V\r\n", voltage );
    }
    if ( ANGLE10_OK == angle10_get_angle ( &angle10, &angle ) )
    {
        log_printf ( &logger, " Angle: %.2f Degrees\r\n\n", angle );
    }
    Delay_ms( 500 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
