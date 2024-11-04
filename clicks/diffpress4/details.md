
---
# Diff Press 4 Click

> Diff Press 4 Click is a compact add-on board that can measure differential pressure. This board features the SM9336-BCE-S-250-000, a digital pressure and altimeter sensor module from TE Connectivity. The SM9336-BCE-S-250-000 has a configurable host interface that supports I2C serial communication and measures pressure in a wide range with an accuracy of 3%. It comes as calibrated and temperature-compensated with high reliability/long-term stability. It operates in a compensated temperature range of -20°C to 85°C, ensuring stable operation under extreme conditions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/diffpress4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/diff-press-4-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Diff Press 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Diff Press 4 Click driver.

#### Standard key functions :

- `diffpress4_cfg_setup` Config Object Initialization function.
```c
void diffpress4_cfg_setup ( diffpress4_cfg_t *cfg );
```

- `diffpress4_init` Initialization function.
```c
err_t diffpress4_init ( diffpress4_t *ctx, diffpress4_cfg_t *cfg );
```

#### Example key functions :

- `diffpress4_get_measurement_data` Diff Press 4 gets the raw data function.
```c
err_t diffpress4_get_measurement_data ( diffpress4_t *ctx, float *diff_press, float *temperature );
```

- `diffpress4_get_status` Diff Press 4 get status function.
```c
err_t diffpress4_get_status ( diffpress4_t *ctx, diffpress4_status_t *status );
```

- `diffpress4_get_raw_data` Diff Press 4 gets the raw data function.
```c
err_t diffpress4_get_raw_data ( diffpress4_t *ctx, int16_t *temp_data, int16_t *press_data );
```

## Example Description

> This example demonstrates the use of Diff Press 4 Click board™ 
> by reading and displaying the differential pressure and sensor temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    diffpress4_cfg_t diffpress4_cfg;  /**< Click config object. */

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
    diffpress4_cfg_setup( &diffpress4_cfg );
    DIFFPRESS4_MAP_MIKROBUS( diffpress4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == diffpress4_init( &diffpress4, &diffpress4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, " _______________________ \r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application reads and displays the Differential Pressure [Pa] 
> and sensor Temperature [degree Celsius] data measurements.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    static float diff_press = 0, temperature = 0;
    diffpress4_status_t status;
    diffpress4_get_status( &diffpress4, &status );
    if ( ( DIFFPRESS4_OK == diffpress4_get_measurement_data( &diffpress4, &diff_press, &temperature ) ) &&
         ( DIFFPRESS4_STATUS_DSP_S_UPDATED == status.dsp_s_up ) && 
         ( DIFFPRESS4_STATUS_DSP_T_UPDATED == status.dsp_t_up ) )
    {
        log_printf( &logger, " Diff Pressure : %.2f [Pa] \r\n", diff_press );
        log_printf( &logger, " Temperature   : %.2f [degC] \r\n", temperature );
        log_printf( &logger, " _______________________ \r\n" );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DiffPress4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
