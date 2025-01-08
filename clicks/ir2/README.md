
---
# IR 2 Click

> [IR 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5088) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5088&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : PWM type

# Software Support

## Example Description

> This example demonstrates the use of an IR 2 Click board by showing
the communication between the two Click boards configured as a receiver and transmitter using the NEC protocol.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IR2

### Example Key Functions

- `ir2_cfg_setup` Config Object Initialization function.
```c
void ir2_cfg_setup ( ir2_cfg_t *cfg );
```

- `ir2_init` Initialization function.
```c
err_t ir2_init ( ir2_t *ctx, ir2_cfg_t *cfg );
```

- `ir2_get_out_pin` This function returns the OUT pin logic state.
```c
uint8_t ir2_get_out_pin ( ir2_t *ctx );
```

- `ir2_nec_send_data` This function sends an address and data bytes using NEC protocol.
```c
void ir2_nec_send_data ( ir2_t *ctx, uint8_t address, uint8_t data_in );
```

- `ir2_nec_read_data` This function reads an address and data bytes by using NEC protocol.
```c
err_t ir2_nec_read_data ( ir2_t *ctx, uint8_t *address, uint8_t *data_out );
```

### Application Init

> Initializes the driver and logger and displays the selected application mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ir2_cfg_t ir2_cfg;  /**< Click config object. */

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
    ir2_cfg_setup( &ir2_cfg );
    IR2_MAP_MIKROBUS( ir2_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == ir2_init( &ir2, &ir2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
#ifdef IR2_TRANSMITTER_MODE
    log_printf( &logger, "-  Transmitter mode   - \r\n" );
#else
    log_printf( &logger, "-    Receiver mode    - \r\n" );
#endif
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Depending on the selected mode, it sends a desired message using NEC protocol or
reads all the received data and displays them on the USB UART.

```c
void application_task ( void )
{
#ifdef IR2_TRANSMITTER_MODE
    log_printf( &logger, " Sending message." );
    
    for ( uint8_t cnt = 0; cnt < sizeof ( IR2_DATA ); cnt++ )
    {
        ir2_nec_send_data ( &ir2, IR2_ADDRESS, IR2_DATA[ cnt ] );
        log_printf( &logger, "." );
    }
    
    log_printf( &logger, "\r\n Message has been sent! \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    Delay_ms ( 500 );
#else
    uint8_t address;
    uint8_t rx_data;
    
    if ( IR2_OK == ir2_nec_read_data ( &ir2, &address, &rx_data ) )
    {
        log_printf( &logger, "Address: 0x%.2X, Data: %c\r\n", ( uint16_t ) address, rx_data );
    }
#endif
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
