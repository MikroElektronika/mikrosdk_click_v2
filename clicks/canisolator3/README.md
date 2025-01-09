
---
# CAN Isolator 3 Click

> [CAN Isolator 3 Click](https://www.mikroe.com/?pid_product=MIKROE-5785) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5785&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example writes and reads and processes data from CAN Isolator 3 Click.
  The library also includes a function for selection of the output polarity.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CANIsolator3

### Example Key Functions

- `canisolator3_cfg_setup` Config Object Initialization function.
```c
void canisolator3_cfg_setup ( canisolator3_cfg_t *cfg );
```

- `canisolator3_init` Initialization function.
```c
err_t canisolator3_init ( canisolator3_t *ctx, canisolator3_cfg_t *cfg );
```

- `canisolator3_default_cfg` Click Default Configuration function.
```c
err_t canisolator3_default_cfg ( canisolator3_t *ctx );
```

- `canisolator3_generic_write` CAN Isolator 3 data writing function.
```c
err_t canisolator3_generic_write ( canisolator3_t *ctx, uint8_t *data_in, uint16_t len );
```

- `canisolator3_generic_read` CAN Isolator 3 data reading function.
```c
err_t canisolator3_generic_read ( canisolator3_t *ctx, uint8_t *data_out, uint16_t len );
```

- `canisolator3_set_pol_pin` CAN Isolator 3 set polarity function.
```c
void canisolator3_set_pol_pin ( canisolator3_t *ctx, uint8_t pin_state );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    canisolator3_cfg_t canisolator3_cfg;  /**< Click config object. */

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
    canisolator3_cfg_setup( &canisolator3_cfg );
    CANISOLATOR3_MAP_MIKROBUS( canisolator3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == canisolator3_init( &canisolator3, &canisolator3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    canisolator3_default_cfg ( &canisolator3 );
    
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
    canisolator3_generic_write( &canisolator3, TX_MESSAGE, strlen( TX_MESSAGE ) );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    canisolator3_process( &canisolator3 );
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
