
---
# Opto Encoder 4 Click

> [Opto Encoder 4 Click](https://www.mikroe.com/?pid_product=MIKROE-5979) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5979&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Opto Encoder 4 Click board by processing
the encoder output pin state and incrementing the step counter on falling edge.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.OptoEncoder4

### Example Key Functions

- `optoencoder4_cfg_setup` Config Object Initialization function.
```c
void optoencoder4_cfg_setup ( optoencoder4_cfg_t *cfg );
```

- `optoencoder4_init` Initialization function.
```c
err_t optoencoder4_init ( optoencoder4_t *ctx, optoencoder4_cfg_t *cfg );
```

- `optoencoder4_get_out_pin` This function returns the output pin logic state.
```c
uint8_t optoencoder4_get_out_pin ( optoencoder4_t *ctx );
```

- `optoencoder4_get_our_pin` This function returns the output pin reversed logic state.
```c
uint8_t optoencoder4_get_our_pin ( optoencoder4_t *ctx );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    optoencoder4_cfg_t optoencoder4_cfg;  /**< Click config object. */

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
    optoencoder4_cfg_setup( &optoencoder4_cfg );
    OPTOENCODER4_MAP_MIKROBUS( optoencoder4_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == optoencoder4_init( &optoencoder4, &optoencoder4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Increments the step counter on falling edge of the encoder output pin state and displays it on the USB UART.

```c
void application_task ( void )
{
    static uint32_t step_cnt = 0;

    log_printf( &logger, " Step counter : %lu\r\n", step_cnt );
    
    // Increment counter on falling edge of output pin
    while ( !optoencoder4_get_out_pin ( &optoencoder4 ) );
    while ( optoencoder4_get_out_pin ( &optoencoder4 ) );

    step_cnt++;
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
