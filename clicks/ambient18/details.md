
---
# Ambient 18 Click

> Ambient 18 Click is a compact add-on board used to sense the amount of the present ambient light. This board features the BH1680FVC, an analog current-output ambient light sensor from Rohm Semiconductor. The BH1680FVC can detect a wide range of illuminance up to 10klx and provides excellent responsivity close to the human eyes' response. Besides, it is also characterized by low sensitivity variation across various light sources, a built-in shutdown function, and the ability to process the output signal in analog or digital form. This Click board™ is the most suitable for obtaining ambient light data for adjusting brightness in applications that require power saving and better visibility.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient18_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ambient-18-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the Ambient 18 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Ambient 18 Click driver.

#### Standard key functions :

- `ambient18_cfg_setup` Config Object Initialization function.
```c
void ambient18_cfg_setup ( ambient18_cfg_t *cfg );
```

- `ambient18_init` Initialization function.
```c
err_t ambient18_init ( ambient18_t *ctx, ambient18_cfg_t *cfg );
```

#### Example key functions :

- `ambient18_set_gain_mode` This function sets the gain mode.
```c
void ambient18_set_gain_mode ( ambient18_t *ctx, uint8_t mode );
```

- `ambient18_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t ambient18_read_voltage ( ambient18_t *ctx, float *voltage );
```

- `ambient18_voltage_to_lux` This function calculates illuminance (lux) based on the voltage input.
```c
int32_t ambient18_voltage_to_lux ( ambient18_t *ctx, float voltage );
```

## Example Description

> This example demonstrates the use of Ambient 18 Click board by measuring and displaying the illuminance value in Lux.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and sets the gain mode to M-Gain which can detect the illuminance of up to 1000 lux.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient18_cfg_t ambient18_cfg;  /**< Click config object. */

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
    ambient18_cfg_setup( &ambient18_cfg );
    AMBIENT18_MAP_MIKROBUS( ambient18_cfg, MIKROBUS_1 );
    err_t init_flag = ambient18_init( &ambient18, &ambient18_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    ambient18_set_gain_mode ( &ambient18, AMBIENT18_MODE_M_GAIN );
    log_printf( &logger, " M-Gain mode selected.\r\n Up to 1000 lux can be measured.\r\n" );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the ADC voltage and then calculates the illuminance from it.
The calculated value of illuminance in lux is being displayed on the USB UART 
approximately once per second.

```c

void application_task ( void )
{
    float voltage = 0;
    if ( AMBIENT18_OK == ambient18_read_voltage ( &ambient18, &voltage ) ) 
    {
        log_printf( &logger, " Illuminance : %ld Lux\r\n\n", ambient18_voltage_to_lux( &ambient18, voltage ) );
        Delay_ms ( 1000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient18

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
