
---
# Pressure 27 Click

> [Pressure 27 Click](https://www.mikroe.com/?pid_product=MIKROE-6956) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6956&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Mar 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the Pressure 27 Click board for
measuring pressure. The application reads sensor
values via the SPI interface and displays the measured results on
the serial terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure27

### Example Key Functions

- `pressure27_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void pressure27_cfg_setup ( pressure27_cfg_t *cfg );
```

- `pressure27_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t pressure27_init ( pressure27_t *ctx, pressure27_cfg_t *cfg );
```

- `pressure27_hw_reset` This function performs a hardware reset of the sensor by driving the RES pin low for 1 ms, then high again.
```c
void pressure27_hw_reset ( pressure27_t *ctx );
```

- `pressure27_get_eoc` This function reads the current logic level of the EOC pin.
```c
uint8_t pressure27_get_eoc ( pressure27_t *ctx );
```

- `pressure27_get_pressure` This function performs a pressure measurement, reads the 24-bit result, and converts raw counts to pressure in kPa.
```c
err_t pressure27_get_pressure ( pressure27_t *ctx, float *pressure );
```

### Application Init

> Initializes the logger and the Pressure 27 Click driver. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure27_cfg_t pressure27_cfg;  /**< Click config object. */

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
    pressure27_cfg_setup( &pressure27_cfg );
    PRESSURE27_MAP_MIKROBUS( pressure27_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == pressure27_init( &pressure27, &pressure27_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically reads pressure values from the sensor and
logs the results to the serial terminal.

```c
void application_task ( void )
{
    float pressure = 0.0f;

    if ( PRESSURE27_OK == pressure27_get_pressure( &pressure27, &pressure ) )
    {
        log_printf( &logger, " Pressure: %.2f kPa\r\n\n", pressure );
    }
    else
    {
        log_error( &logger, " Pressure read failed.\r\n" );
    }

    Delay_ms( 1000 );
}
```

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
