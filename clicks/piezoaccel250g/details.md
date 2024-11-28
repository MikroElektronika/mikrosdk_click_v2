
---
# Piezo Accel 2 50g Click

> Piezo Accel 2 Click - 50g is a compact add-on board for precise vibration and motion monitoring in condition-based maintenance applications. This board features the 830M1-0050, a triaxial piezoelectric accelerometer from TE Connectivity, capable of detecting motion and acceleration along all three axes (X, Y, Z). The 830M1-0050 offers a ±50g range with a sensitivity of 25mV/g, providing reliable and accurate analog voltage outputs. It integrates a built-in RTD temperature sensor for simultaneous vibration and temperature monitoring, and the onboard MCP3562R 24-bit ADC converts these signals into high-resolution digital data. Communication is made through an SPI interface with additional interrupt and clock functionality for easy integration with a host MCU.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/piezoaccel250g_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/piezo-accel-2-click-50g)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : SPI type


# Software Support

We provide a library for the Piezo Accel 2 50g Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Piezo Accel 2 50g Click driver.

#### Standard key functions :

- `piezoaccel250g_cfg_setup` Config Object Initialization function.
```c
void piezoaccel250g_cfg_setup ( piezoaccel250g_cfg_t *cfg );
```

- `piezoaccel250g_init` Initialization function.
```c
err_t piezoaccel250g_init ( piezoaccel250g_t *ctx, piezoaccel250g_cfg_t *cfg );
```

- `piezoaccel250g_default_cfg` Click Default Configuration function.
```c
err_t piezoaccel250g_default_cfg ( piezoaccel250g_t *ctx );
```

#### Example key functions :

- `piezoaccel250g_read_adc_data` This function reads raw ADC values of X, Y, and Z axis, and the internal temperature sensor measurements.
```c
err_t piezoaccel250g_read_adc_data ( piezoaccel250g_t *ctx, piezoaccel250g_adc_data_t *data_out );
```

- `piezoaccel250g_fast_cmd_write` This function writes the selected fast command by using SPI serial interface.
```c
err_t piezoaccel250g_fast_cmd_write ( piezoaccel250g_t *ctx, uint8_t fast_cmd );
```

- `piezoaccel250g_reg_read_multi` This function reads a desired number of data bytes starting from the selected register by using SPI serial interface.
```c
err_t piezoaccel250g_reg_read_multi ( piezoaccel250g_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );
```

## Example Description

> This example demonstrates the use of Piezo Accel 2 50g Click board by reading and displaying
the ADC values of X, Y, and Z axis, and the internal temperature sensor measurements. 
Those data can be visualized on the SerialPlot application.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration for ADC measurements.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    piezoaccel250g_cfg_t piezoaccel250g_cfg;  /**< Click config object. */

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
    piezoaccel250g_cfg_setup( &piezoaccel250g_cfg );
    PIEZOACCEL250G_MAP_MIKROBUS( piezoaccel250g_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == piezoaccel250g_init( &piezoaccel250g, &piezoaccel250g_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PIEZOACCEL250G_ERROR == piezoaccel250g_default_cfg ( &piezoaccel250g ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the ADC values of X, Y, and Z axis, and the internal temperature sensor measurements
and displays them on the USB UART (SerialPlot) every 5ms approximately.

```c
void application_task ( void )
{
    piezoaccel250g_adc_data_t adc_data;
    if ( PIEZOACCEL250G_OK == piezoaccel250g_read_adc_data ( &piezoaccel250g, &adc_data ) )
    {
        log_printf ( &logger, "%lu;%lu;%lu;%lu;\r\n", adc_data.raw_x, adc_data.raw_y, 
                                                      adc_data.raw_z, adc_data.raw_temp );
    }
}
```

## Note

> We recommend using the SerialPlot tool for data visualization. The temperature measurements
should be visualized independently. The data format for plotter is as follows: X;Y;Z;TEMP;

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.PiezoAccel250g

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
