
---
# CAN FD 7 Click

> [CAN FD 7 Click](https://www.mikroe.com/?pid_product=MIKROE-5888) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5888&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example writes and reads and processes data from CAN FD 7 Click.
  The library also includes a function for selection of the output polarity.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CANFD7

### Example Key Functions

- `canfd7_cfg_setup` Config Object Initialization function.
```c
void canfd7_cfg_setup ( canfd7_cfg_t *cfg );
```

- `canfd7_init` Initialization function.
```c
err_t canfd7_init ( canfd7_t *ctx, canfd7_cfg_t *cfg );
```

- `canfd7_default_cfg` Click Default Configuration function.
```c
void canfd7_default_cfg ( canfd7_t *ctx );
```

- `canfd7_generic_write` CAN FD 7 data writing function.
```c
err_t canfd7_generic_write ( canfd7_t *ctx, uint8_t *data_in, uint16_t len ) 
```

- `canfd7_generic_read` CAN FD 7 data reading function.
```c
err_t canfd7_generic_read ( canfd7_t *ctx, uint8_t *data_out, uint16_t len );
```

- `canfd7_set_stb_pin` CAN FD 7 set STB pin function.
```c
void canfd7_set_stb_pin ( canfd7_t *ctx, uint8_t pin_state );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    canfd7_cfg_t canfd7_cfg;  /**< Click config object. */

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
    canfd7_cfg_setup( &canfd7_cfg );
    CANFD7_MAP_MIKROBUS( canfd7_cfg, MIKROBUS_1 );
    if ( UART_ERROR == canfd7_init( &canfd7, &canfd7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    canfd7_default_cfg ( &canfd7 );
    
#ifdef DEMO_APP_TRANSMITTER
    log_info( &logger, "---- Transmitter mode ----" );
#else
    log_info( &logger, "---- Receiver mode ----" );
#endif 
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example contains Transmitter/Receiver task depending on uncommented code.
  Receiver logs each received byte to the UART for data logging,
  while the transmitter sends messages every 2 seconds.

```c
void application_task ( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    canfd7_generic_write( &canfd7, TX_MESSAGE, strlen( TX_MESSAGE ) );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    canfd7_process( &canfd7 );
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
