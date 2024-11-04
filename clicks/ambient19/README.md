\mainpage Main Page

---
# Ambient 19 Click

> Ambient 19 Click is a compact add-on board used to measure the amount of the present ambient light. This board features the APM-16D24-310-DF8/TR8, a digital output ambient light and proximity sensor with an I2C interface and interrupt from Everlight Electronics. It has a flexible and wide operating range for the ambient light sensor with a maximum resolution of 0.0023Lux/count and full detectable illumination of 57880Lux. The proximity function has an adjustable number of IR pulses from 1 to 256, and a flexible IR LED driving current to meet different application requirements. It is also equipped with an integrated filter to reduce unwanted IR signals and noise from the environment.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient19_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ambient-19-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Ambient 19 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Ambient 19 Click driver.

#### Standard key functions :

- `ambient19_cfg_setup` Config Object Initialization function.
```c
void ambient19_cfg_setup ( ambient19_cfg_t *cfg );
```

- `ambient19_init` Initialization function.
```c
err_t ambient19_init ( ambient19_t *ctx, ambient19_cfg_t *cfg );
```

- `ambient19_default_cfg` Click Default Configuration function.
```c
err_t ambient19_default_cfg ( ambient19_t *ctx );
```

#### Example key functions :

- `ambient19_measure_light_level` This function reads the raw ALS data from two channels and then measures the light level in lux based on those readings.
```c
err_t ambient19_measure_light_level ( ambient19_t *ctx, uint16_t *lux );
```

- `ambient19_read_raw_proximity` This function reads the raw PS and IR data of the proximity sensor.
```c
err_t ambient19_read_raw_proximity ( ambient19_t *ctx, uint16_t *ps_data, uint16_t *ir_data );
```

- `ambient19_clear_interrupts` This function clears all interrupts by clearing the INT_FLAG register.
```c
err_t ambient19_clear_interrupts ( ambient19_t *ctx );
```

## Example Description

> This example demonstrates the use of Ambient 19 Click board by measuring the ambient light level in Lux.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient19_cfg_t ambient19_cfg;  /**< Click config object. */

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
    ambient19_cfg_setup( &ambient19_cfg );
    AMBIENT19_MAP_MIKROBUS( ambient19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient19_init( &ambient19, &ambient19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT19_ERROR == ambient19_default_cfg ( &ambient19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the data ready interrupt, then reads the ambient light level in Lux as well as the raw proximity data of PS and IR leds and displays the results on the USB UART. 
By default, the data ready interrupt triggers upon every ADC cycle which will be performed every 500ms approximately.

```c
void application_task ( void )
{
    if ( !ambient19_get_int_pin ( &ambient19 ) )
    {
        uint16_t lux, ps_data, ir_data;
        if ( AMBIENT19_OK == ambient19_measure_light_level ( &ambient19, &lux ) )
        {
            log_printf ( &logger, "\r\n Ambient light level [Lux]: %u\r\n", lux );
        }
        if ( AMBIENT19_OK == ambient19_read_raw_proximity ( &ambient19, &ps_data, &ir_data ) )
        {
            log_printf ( &logger, " PS data: %u\r\n", ps_data );
            log_printf ( &logger, " IR data: %u\r\n", ir_data );
        }
        ambient19_clear_interrupts ( &ambient19 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient19

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
