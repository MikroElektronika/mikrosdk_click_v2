\mainpage Main Page

---
# Diff Press 2 Click

> Diff Press 2 Click is a compact add-on board that contains Sensirion’s differential pressure sensor. This board features the SDP31-500PA, a small differential pressure sensor designed for high-volume applications. The SDP31-500PA comes with a configurable host interface that supports I2C serial communication and measures pressure in a range from -500Pa up to +500Pa with an accuracy of 3%. It comes as calibrated and temperature compensated with high reliability/long-term stability, has the best signal-to-noise ratio. It operates in a temperature range of -40°C to 85°C, ensuring stable operation under extreme conditions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/diffpress2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/diff-press-2-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Sep 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the DiffPress2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DiffPress2 Click driver.

#### Standard key functions :

- `diffpress2_cfg_setup` Config Object Initialization function.
```c
void diffpress2_cfg_setup ( diffpress2_cfg_t *cfg );
```

- `diffpress2_init` Initialization function.
```c
err_t diffpress2_init ( diffpress2_t *ctx, diffpress2_cfg_t *cfg );
```

- `diffpress2_default_cfg` Click Default Configuration function.
```c
err_t diffpress2_default_cfg ( diffpress2_t *ctx );
```

#### Example key functions :

- `diffpress2_get_id` Reads device ID's
```c
err_t diffpress2_get_id ( diffpress2_t *ctx );
```

- `diffpress2_reset` Reset device
```c
err_t diffpress2_reset ( diffpress2_t *ctx );
```

- `diffpress2_trigger_measurement` Pressure and temperature reading
```c
err_t diffpress2_trigger_measurement ( diffpress2_t *ctx, uint16_t trigger_type, 
                                       float *diff_press, float *temperature );
```

## Example Description

> This example application showcases ability for device
to read and calculate mass flow or diff press pressure
in Pascals and temperature in degrees Celsius.

**The demo application is composed of two sections :**

### Application Init

> Initialization of module communication(I2C, UART) and 
additional interrupt pin. Resets device and reads
serial and product ID's and logs them.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    diffpress2_cfg_t diffpress2_cfg;  /**< Click config object. */

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
    diffpress2_cfg_setup( &diffpress2_cfg );
    DIFFPRESS2_MAP_MIKROBUS( diffpress2_cfg, MIKROBUS_1 );
    err_t init_flag = diffpress2_init( &diffpress2, &diffpress2_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    if ( diffpress2_default_cfg ( &diffpress2 ) ) 
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf( &logger, " > Product ID: 0x%.8LX\r\n", diffpress2.product_id );
    log_printf( &logger, " > Serial ID: 0x%.8LX%.8LX\r\n", 
                diffpress2.serial_id[ 0 ], diffpress2.serial_id[ 1 ] );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Read and calculate differential in Pascal and temperature 
in degrees Celsius every 300ms.

```c

void application_task ( void )
{
    float pressure;
    float temperature;

    if ( diffpress2_trigger_measurement( &diffpress2, DIFFPRESS2_CMD_TRIGGER_MEAS_DIFF_PRESS, 
                                         &pressure, &temperature ) )
    {
        log_error( &logger, " Read data." );
    }
    else
    {
        log_printf( &logger, " > Pressure[Pa]: %.2f\r\n", pressure );
        log_printf( &logger, " > Temperature[degC]: %.2f\r\n", temperature );
        log_printf( &logger, "*************************************\r\n" );
    }

    Delay_ms ( 300 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DiffPress2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
