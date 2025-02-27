
---
# Opto Encoder 6 Click

> [Opto Encoder 6 Click](https://www.mikroe.com/?pid_product=MIKROE-6569) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6569&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2025.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Opto Encoder 6 Click board by processing
the encoder output pin state and incrementing the step counter on falling edge.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.OptoEncoder6

### Example Key Functions

- `optoencoder6_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void optoencoder6_cfg_setup ( optoencoder6_cfg_t *cfg );
```

- `optoencoder6_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t optoencoder6_init ( optoencoder6_t *ctx, optoencoder6_cfg_t *cfg );
```

- `optoencoder6_enable_output` This function enables output by setting the EN pin to high logic state.
```c
void optoencoder6_enable_output ( optoencoder6_t *ctx );
```

- `optoencoder6_disable_output` This function disables output by setting the EN pin to low logic state.
```c
void optoencoder6_disable_output ( optoencoder6_t *ctx );
```

- `optoencoder6_get_out_pin` This function returns the OUT pin logic state.
```c
uint8_t optoencoder6_get_out_pin ( optoencoder6_t *ctx );
```

### Application Init

> Initializes the driver and logger, and enables the encoder output.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    optoencoder6_cfg_t optoencoder6_cfg;  /**< Click config object. */

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
    optoencoder6_cfg_setup( &optoencoder6_cfg );
    OPTOENCODER6_MAP_MIKROBUS( optoencoder6_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == optoencoder6_init( &optoencoder6, &optoencoder6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    optoencoder6_enable_output ( &optoencoder6 );
    
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
    while ( !optoencoder6_get_out_pin ( &optoencoder6 ) );
    while ( optoencoder6_get_out_pin ( &optoencoder6 ) );

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
