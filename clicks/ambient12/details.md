
---
# Ambient 12 Click

> Ambient 12 Click is a compact add-on board used to sense the amount of the present ambient light. This board features the BH1620FVC, an analog current-output type ambient light sensor from Rohm Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient12_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ambient-12-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : ADC type


# Software Support

We provide a library for the Ambient12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Ambient12 Click driver.

#### Standard key functions :

- `ambient12_cfg_setup` Config Object Initialization function.
```c
void ambient12_cfg_setup ( ambient12_cfg_t *cfg );
```

- `ambient12_init` Initialization function.
```c
err_t ambient12_init ( ambient12_t *ctx, ambient12_cfg_t *cfg );
```

#### Example key functions :

- `ambient12_read_adc_voltage` This function reads raw 12-bit ADC data and converts it to voltage by using I2C serial interface.
```c
err_t ambient12_read_adc_voltage ( ambient12_t *ctx, float *voltage );
```

- `ambient12_voltage_to_lux` This function calculates illuminance (lux) based on the voltage input.
```c
int32_t ambient12_voltage_to_lux ( ambient12_t *ctx, float voltage );
```

- `ambient12_set_gain_mode` This function sets the gain mode.
```c
void ambient12_set_gain_mode ( ambient12_t *ctx, uint8_t mode );
```

## Example Description

> This example demonstrates the use of Ambient 12 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and sets the gain mode to M-Gain which can detect the illuminance of up to 10000 lux.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    ambient12_cfg_t ambient12_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    ambient12_cfg_setup( &ambient12_cfg );
    AMBIENT12_MAP_MIKROBUS( ambient12_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == ambient12_init( &ambient12, &ambient12_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    ambient12_set_gain_mode ( &ambient12, AMBIENT12_MODE_M_GAIN );
    log_printf( &logger, " M-Gain mode selected.\r\n Up to 10000 lux can be measured.\r\n" );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the ADC voltage and then calculates the illuminance from it.
> The calculated value of illuminance in lux is being displayed on the USB UART approximately once per second. 

```c

void application_task ( void )
{
    float voltage = 0;
    
    if ( AMBIENT12_OK == ambient12_read_adc_voltage ( &ambient12, &voltage ) )
    {
        log_printf( &logger, " Illuminance : %ld Lux\r\n\n", ambient12_voltage_to_lux( &ambient12, voltage ) );
    }
    
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
