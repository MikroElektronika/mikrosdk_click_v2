
---
# Accel 18 Click

> [Accel 18 Click](https://www.mikroe.com/?pid_product=MIKROE-4826) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4826&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example application showcases ability of the device
to read axes values on detected interrupt.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel18

### Example Key Functions

- `accel18_cfg_setup` Config Object Initialization function.
```c
void accel18_cfg_setup ( accel18_cfg_t *cfg );
```

- `accel18_init` Initialization function.
```c
err_t accel18_init ( accel18_t *ctx, accel18_cfg_t *cfg );
```

- `accel18_default_cfg` Click Default Configuration function.
```c
err_t accel18_default_cfg ( accel18_t *ctx );
```

- `accel18_read_axes` Accel data reading.
```c
err_t accel18_read_axes ( accel18_t *ctx, accel18_axes_t *axes_data );
```

- `accel18_set_range` Set range configuration.
```c
err_t accel18_set_range ( accel18_t *ctx, uint8_t range_macro );
```

- `accel18_get_interrupt_1` Get interrupt 1 pin state.
```c
uint8_t accel18_get_interrupt_1 ( accel18_t *ctx );
```

### Application Init

> Initialization of comunication modules(SPI/I2C, UART) and additional
two interrupt pins. Then configures device and sets 8g range and 10 Hz
data rate, with interrupt enabled.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel18_cfg_t accel18_cfg;  /**< Click config object. */

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
    accel18_cfg_setup( &accel18_cfg );
    ACCEL18_MAP_MIKROBUS( accel18_cfg, MIKROBUS_1 );
    err_t init_flag  = accel18_init( &accel18, &accel18_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    if ( accel18_default_cfg ( &accel18 ) )
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Whenever interrupt is detected checks interrupt status for data ready,
and then reads x, y, and z axes, calculates value and logs result.

```c
void application_task ( void )
{
    accel18_axes_t axes_data;
    if ( !accel18_get_interrupt_1( &accel18 ) )
    {
        // Check interrupts
        uint8_t interrupt_state = 0;
        accel18_byte_read( &accel18, ACCEL18_REG_INTERRUPT_STATUS, &interrupt_state );
        if ( interrupt_state & ACCEL18_INT_ACQ_EN )
        {
            // Axis read
            accel18_read_axes( &accel18, &axes_data );
            log_printf( &logger, " > X[g]: %.2f\r\n", axes_data.x );
            log_printf( &logger, " > Y[g]: %.2f\r\n", axes_data.y );
            log_printf( &logger, " > Z[g]: %.2f\r\n", axes_data.z );
            log_printf( &logger, "**************************\r\n" );
        }
        // Clear interrupts
        if ( interrupt_state )
        {
            accel18_byte_write( &accel18, ACCEL18_REG_INTERRUPT_STATUS, ~interrupt_state );
        }
    }
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
