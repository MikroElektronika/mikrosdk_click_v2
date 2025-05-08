
---
# AC Current 2 Click

> [AC Current 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6579) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6579&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2025.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates how to use the AC Current 2 Click board for reading
the measurements from the AC Current sensor attached to the Click board input.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ACCurrent2

### Example Key Functions

- `accurrent2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void accurrent2_cfg_setup ( accurrent2_cfg_t *cfg );
```

- `accurrent2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t accurrent2_init ( accurrent2_t *ctx, accurrent2_cfg_t *cfg );
```

- `accurrent2_read_current` This function reads the current measurement from the AC Current sensor (30A/1V).
```c
err_t accurrent2_read_current ( accurrent2_t *ctx, float *current );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accurrent2_cfg_t accurrent2_cfg;  /**< Click config object. */

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
    accurrent2_cfg_setup( &accurrent2_cfg );
    ACCURRENT2_MAP_MIKROBUS( accurrent2_cfg, MIKROBUS_1 );
    err_t init_flag = accurrent2_init( &accurrent2, &accurrent2_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads the AC current value and logs the measured data in amperes (A).

```c
void application_task ( void )
{
    float current = 0;
    if ( ACCURRENT2_OK == accurrent2_read_current ( &accurrent2, &current ) ) 
    {
        log_printf( &logger, " AC Current : %.3f A\r\n\n", current );
        Delay_ms ( 1000 );
    }
}
```

### Note

> The AC Current sensor [MIKROE-2524] required for this Click board should have a specification of 30A/1A.

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
