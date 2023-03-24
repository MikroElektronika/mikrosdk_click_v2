\mainpage Main Page

---
# Ambient 10 click

> Ambient 10 Click is a compact add-on board used to sense the amount of the present ambient light. This board features the APDS-9006-020, analog-output ambient light photosensor from Broadcom Limited.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ambient-10-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : ADC type


# Software Support

We provide a library for the Ambient10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Ambient10 Click driver.

#### Standard key functions :

- `ambient10_cfg_setup` Config Object Initialization function.
```c
void ambient10_cfg_setup ( ambient10_cfg_t *cfg );
```

- `ambient10_init` Initialization function.
```c
err_t ambient10_init ( ambient10_t *ctx, ambient10_cfg_t *cfg );
```

#### Example key functions :

- `ambient10_set_vref` This function sets the voltage reference for Ambient 10 click driver.
```c
err_t ambient10_set_vref ( ambient10_t *ctx, float vref );
```

- `ambient10_read_adc_voltage` This function reads raw 12-bit ADC data and converts it to voltage by using I2C serial interface.
```c
err_t ambient10_read_adc_voltage ( ambient10_t *ctx, float *voltage );
```

- `ambient10_voltage_to_lux` This function calculates illuminance (lux) based on the voltage input.
```c
uint16_t ambient10_voltage_to_lux ( ambient10_t *ctx, float voltage );
```

## Example Description

> This example demonstrates the use of Ambient 10 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and sets the voltage reference.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    ambient10_cfg_t ambient10_cfg;  /**< Click config object. */

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
    Delay_ms( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    ambient10_cfg_setup( &ambient10_cfg );
    AMBIENT10_MAP_MIKROBUS( ambient10_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == ambient10_init( &ambient10, &ambient10_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    ambient10_set_vref( &ambient10, AMBIENT10_VREF_3V3 );
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
    
    if ( AMBIENT10_OK == ambient10_read_an_pin_voltage ( &ambient10, &voltage ) )
    {
        log_printf( &logger, " Illuminance : %u Lux\r\n\n", ambient10_voltage_to_lux( &ambient10, voltage ) );
    }
    
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
