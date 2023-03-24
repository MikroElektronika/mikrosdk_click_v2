
---
# PWR Meter 3 click

> PWR Meter 3 Click is a compact add-on board that measures voltage and current through the connected load. This board features the ACS37800, an I2C-configurable power monitoring solution from Allegro MicroSystems, which simplifies the addition of power monitoring to many AC/DC powered systems. The ACS37800’s Hall-effect-based current sensing technology achieves reinforced isolation ratings (4800 VRMS) alongside a reliable ±90A bidirectional current sensing. It also has two LED indicators for the realization of visual detection of some anomalies in operation, such as under/overvoltage and fast overcurrent fault detection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pwrmeter3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pwr-meter-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the PWR Meter 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for PWR Meter 3 Click driver.

#### Standard key functions :

- `pwrmeter3_cfg_setup` Config Object Initialization function.
```c
void pwrmeter3_cfg_setup ( pwrmeter3_cfg_t *cfg );
```

- `pwrmeter3_init` Initialization function.
```c
err_t pwrmeter3_init ( pwrmeter3_t *ctx, pwrmeter3_cfg_t *cfg );
```

- `pwrmeter3_default_cfg` Click Default Configuration function.
```c
err_t pwrmeter3_default_cfg ( pwrmeter3_t *ctx );
```

#### Example key functions :

- `pwrmeter3_get_dio0_pin` This function returns the DIO0 pin logic state.
```c
uint8_t pwrmeter3_get_dio0_pin ( pwrmeter3_t *ctx );
```

- `pwrmeter3_get_dio1_pin` This function returns the DIO1 pin logic state.
```c
uint8_t pwrmeter3_get_dio1_pin ( pwrmeter3_t *ctx );
```

- `pwrmeter3_read_average_rms` This function reads the voltage and current RMS measurements averaged from a specified number of samples.
```c
err_t pwrmeter3_read_average_rms ( pwrmeter3_t *ctx, float *v_rms, float *i_rms, uint16_t num_avg );
```

## Example Description

> This example demonstrates the use of PWR Meter 3 click board by reading and displaying the voltage, current, and power RMS measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which sets the DC measurement
and VRMS thresholds to about 28V for overvoltage and about 9.3V for undervoltage flag.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pwrmeter3_cfg_t pwrmeter3_cfg;  /**< Click config object. */

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
    pwrmeter3_cfg_setup( &pwrmeter3_cfg );
    PWRMETER3_MAP_MIKROBUS( pwrmeter3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pwrmeter3_init( &pwrmeter3, &pwrmeter3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PWRMETER3_ERROR == pwrmeter3_default_cfg ( &pwrmeter3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the voltage and current RMS values averaged from 500 samples, then calculates the power from it
and displays the results on the USB UART. Also if an UV or OV flag is detected it will be logged accordingly.

```c
void application_task ( void )
{
    float v_rms, i_rms;
    if ( PWRMETER3_OK == pwrmeter3_read_average_rms ( &pwrmeter3, &v_rms, &i_rms, PWRMETER3_DEF_AVG_SAMPLES ) )
    {
        if ( !pwrmeter3_get_dio0_pin ( &pwrmeter3 ) )
        {
            log_printf ( &logger, " Over-voltage detected!\r\n" );
        }
        if ( !pwrmeter3_get_dio1_pin ( &pwrmeter3 ) )
        {
            log_printf ( &logger, " Under-voltage detected!\r\n" );
        }
        log_printf ( &logger, " Voltage: %.2f V\r\n", v_rms );
        log_printf ( &logger, " Current: %.2f A\r\n", i_rms );
        log_printf ( &logger, " Power: %.2f W\r\n\n", i_rms * v_rms );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.PWRMeter3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
