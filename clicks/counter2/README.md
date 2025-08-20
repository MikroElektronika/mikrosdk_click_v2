
---
# Counter 2 Click

> [Counter 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6603) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6603&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Counter 2 Click board. The application reads the current
pulse count from the board and handles rollover events using the loop counter mechanism. It logs
the total number of detected pulses, including those beyond the register's capacity.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Counter2

### Example Key Functions

- `counter2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void counter2_cfg_setup ( counter2_cfg_t *cfg );
```

- `counter2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t counter2_init ( counter2_t *ctx, counter2_cfg_t *cfg );
```

- `counter2_reset_counter` This function performs a hardware counter reset by toggling the RST pin and synchronizing with the LOOP pin.
```c
void counter2_reset_counter ( counter2_t *ctx );
```

- `counter2_get_counter` This function reads the current 24-bit counter value via I2C.
```c
err_t counter2_get_counter ( counter2_t *ctx, uint32_t *counter );
```

- `counter2_check_loop` This function checks if the LOOP pin state has changed since the last call.
```c
uint8_t counter2_check_loop ( counter2_t *ctx );
```

### Application Init

> Initializes the logger and the Click board driver and resets the internal pulse counter.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    counter2_cfg_t counter2_cfg;  /**< Click config object. */

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
    counter2_cfg_setup( &counter2_cfg );
    COUNTER2_MAP_MIKROBUS( counter2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == counter2_init( &counter2, &counter2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    counter2_reset_counter ( &counter2 );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically reads the counter value and checks for rollover (loop) events. Logs the total pulse count every second.

```c
void application_task ( void )
{
    static uint8_t loop_cnt = 0;
    uint32_t counter = 0;
    if ( COUNTER2_OK == counter2_get_counter ( &counter2, &counter ) )
    {
        loop_cnt += counter2_check_loop ( &counter2 );
        log_printf ( &logger, " Counter: %lu\r\n\n", 
                     ( uint32_t ) loop_cnt * COUNTER2_LOOP_THRESHOLD + counter );
        Delay_ms ( 1000 );
    }
}
```

### Note

> Ensure that the input signal to the counting channel is within electrical and timing specifications to avoid missed or incorrect counts.

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
