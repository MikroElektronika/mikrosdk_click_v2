\mainpage Main Page

---
# DAC 13 click

> DAC 13 Click is a compact add-on board providing a highly accurate digital-to-analog conversion. This board features the AD3541R, a low drift, single channel, 16-bit accuracy, voltage output digital-to-analog converter (DAC) from Analog Devices. The AD3542R operates with a fixed 2.5V reference, communicates with the host MCU through the SPI interface, and can be configurable in multiple voltage span ranges. Also, it provides the possibility to select the power supply of the internal trans-impedance amplifier as well as its gain, which scales the output voltage.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dac13_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dac-13-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the DAC 13 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DAC 13 Click driver.

#### Standard key functions :

- `dac13_cfg_setup` Config Object Initialization function.
```c
void dac13_cfg_setup ( dac13_cfg_t *cfg );
```

- `dac13_init` Initialization function.
```c
err_t dac13_init ( dac13_t *ctx, dac13_cfg_t *cfg );
```

- `dac13_default_cfg` Click Default Configuration function.
```c
err_t dac13_default_cfg ( dac13_t *ctx );
```

#### Example key functions :

- `dac13_set_output_range` This function sets the output voltage range and as well as the @b ctx->v_zero_scale and @b ctx->v_full_scale variables for the selected range.
```c
err_t dac13_set_output_range ( dac13_t *ctx, uint8_t out_range );
```

- `dac13_set_dac_value` This function sets the raw DAC value.
```c
err_t dac13_set_dac_value ( dac13_t *ctx, uint16_t dac_value );
```

- `dac13_set_output_voltage` This function sets the DAC output voltage.
```c
err_t dac13_set_output_voltage ( dac13_t *ctx, float voltage );
```

## Example Description

> This example demonstrates the use of DAC 13 click board by changing the outputs voltage level every 2 seconds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac13_cfg_t dac13_cfg;  /**< Click config object. */

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
    dac13_cfg_setup( &dac13_cfg );
    DAC13_MAP_MIKROBUS( dac13_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == dac13_init( &dac13, &dac13_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC13_ERROR == dac13_default_cfg ( &dac13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the output voltage every 2 seconds and logs the voltage value on the USB UART.
It will go through the entire voltage range taking into account the number of steps which is defined below.

```c
void application_task ( void )
{
    float step = ( dac13.v_full_scale - dac13.v_zero_scale ) / ( NUMBER_OF_STEPS - 1 );
    float out_voltage = dac13.v_zero_scale;
    for ( uint8_t cnt = 0; cnt < NUMBER_OF_STEPS; cnt++ )
    {
        if ( DAC13_OK == dac13_set_output_voltage ( &dac13, out_voltage ) )
        {
            log_printf ( &logger, " Output voltage : %.2f V\r\n\n", out_voltage );
            out_voltage += step;
            Delay_ms ( 2000 );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC13

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
