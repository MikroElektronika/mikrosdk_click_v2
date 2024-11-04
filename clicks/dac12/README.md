\mainpage Main Page

---
# DAC 12 Click

> DAC 12 Click is a compact add-on board that contains a highly accurate digital-to-analog converter. This board features the DAC60508, a general-purpose octal 12-bit analog voltage-output DAC from Texas Instruments. It includes a 2.5V, 5ppm/°C internal reference, eliminating the need for an external precision reference in most applications, and supports the SPI serial interface, which operates at clock rates up to 40MHz. A user interface-selectable gain configuration provides full-scale output voltages of 1.25V, 2.5V, or 5 V. This Click board™ represents an excellent choice for digital gain and offset adjustment applications, programmable voltage, and current sources, programmable reference, and many more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dac12_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dac-12-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the DAC 12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DAC 12 Click driver.

#### Standard key functions :

- `dac12_cfg_setup` Config Object Initialization function.
```c
void dac12_cfg_setup ( dac12_cfg_t *cfg );
```

- `dac12_init` Initialization function.
```c
err_t dac12_init ( dac12_t *ctx, dac12_cfg_t *cfg );
```

- `dac12_default_cfg` Click Default Configuration function.
```c
err_t dac12_default_cfg ( dac12_t *ctx );
```

#### Example key functions :

- `dac12_soft_reset` This function executes the software reset command.
```c
err_t dac12_soft_reset ( dac12_t *ctx );
```

- `dac12_set_channel_value` This function sets the raw DAC value to the specific channels output.
```c
err_t dac12_set_channel_value ( dac12_t *ctx, uint8_t channel, uint16_t dac_value );
```

- `dac12_set_channel_voltage` This function sets the output voltage of the specific channels.
```c
err_t dac12_set_channel_voltage ( dac12_t *ctx, uint8_t channel, float voltage );
```

## Example Description

> This example demonstrates the use of DAC 12 Click board by changing the outputs voltage level every 2 seconds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac12_cfg_t dac12_cfg;  /**< Click config object. */

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
    dac12_cfg_setup( &dac12_cfg );
    DAC12_MAP_MIKROBUS( dac12_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == dac12_init( &dac12, &dac12_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    DAC12_SET_DATA_SAMPLE_EDGE;
    
    if ( DAC12_ERROR == dac12_default_cfg ( &dac12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the output voltage of all channels every 2 seconds and logs the voltage value on the USB UART.
It will go through the entire voltage range taking into account the number of steps which is defined below.

```c
void application_task ( void )
{
    float step = DAC12_INTERNAL_VREF / NUMBER_OF_STEPS;
    float output_voltage = step;
    for ( uint8_t cnt = 0; cnt < NUMBER_OF_STEPS; cnt++ )
    {
        if ( DAC12_OK == dac12_set_channel_voltage ( &dac12, DAC12_SELECT_CHANNEL_ALL, output_voltage ) )
        {
            log_printf( &logger, " All channels output voltage set to %.3f V\r\n", output_voltage );
            output_voltage += step;
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
