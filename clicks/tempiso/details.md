
---
# Temp ISO Click

> Temp ISO Click is a compact add-on board for accurate and isolated temperature measurements in high-voltage environments. This board features the ISOTMP35-Q1, an automotive-grade isolated temperature sensor with analog output from Texas Instruments. This sensor integrates a robust isolation barrier with a withstand voltage of up to 3000VRMS, a linear analog output with a 10mV/°C slope, and a wide temperature range of –40°C to 150°C. It delivers high accuracy of ±2.0°C, fast thermal response, and is AEC-Q100 qualified, ensuring long-term reliability in demanding conditions. The board also features Click Snap, enabling flexible sensor placement by detaching the PCB for standalone operation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/tempiso_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/temp-iso-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2024.
- **Type**          : ADC type


# Software Support

We provide a library for the Temp ISO Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Temp ISO Click driver.

#### Standard key functions :

- `tempiso_cfg_setup` Config Object Initialization function.
```c
void tempiso_cfg_setup ( tempiso_cfg_t *cfg );
```

- `tempiso_init` Initialization function.
```c
err_t tempiso_init ( tempiso_t *ctx, tempiso_cfg_t *cfg );
```

#### Example key functions :

- `tempiso_read_temperature` This function reads the voltage level from AN pin and converts it to temperature in degrees Celsius.
```c
err_t tempiso_read_temperature ( tempiso_t *ctx, float *data_out );
```

- `tempiso_read_voltage_avg` This function reads a desired number of ADC samples and calculates the average voltage level.
```c
err_t tempiso_read_voltage_avg ( tempiso_t *ctx, uint16_t num_conv, float *voltage_avg );
```

- `tempiso_set_vref` This function sets the voltage reference for Temp ISO Click driver.
```c
err_t tempiso_set_vref ( tempiso_t *ctx, float vref );
```

## Example Description

> This example demonstrates the use of Temp ISO Click board by reading and displaying the temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tempiso_cfg_t tempiso_cfg;  /**< Click config object. */

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
    tempiso_cfg_setup( &tempiso_cfg );
    TEMPISO_MAP_MIKROBUS( tempiso_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == tempiso_init( &tempiso, &tempiso_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the temperature measurement in degrees Celsius and displays the results on the USB UART approximately once per second.

```c

void application_task ( void )
{
    float temperature = 0;
    if ( TEMPISO_OK == tempiso_read_temperature ( &tempiso, &temperature ) ) 
    {
        log_printf( &logger, " Temperature: %.1f degC\r\n\n", temperature );
        Delay_ms ( 1000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.TempISO

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
