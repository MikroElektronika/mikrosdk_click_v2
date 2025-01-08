
---
# Opto Encoder 5 Click

> [Opto Encoder 5 Click](https://www.mikroe.com/?pid_product=MIKROE-6056) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6056&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the Opto Encoder 5 Click board by detecting eclipse states.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.OptoEncoder5

### Example Key Functions

- `optoencoder5_cfg_setup` Config Object Initialization function.
```c
void optoencoder5_cfg_setup ( optoencoder5_cfg_t *cfg );
```

- `optoencoder5_init` Initialization function.
```c
err_t optoencoder5_init ( optoencoder5_t *ctx, optoencoder5_cfg_t *cfg );
```

- `optoencoder5_enable` This function enables the slotted optical switch of Opto Encoder 5 Click board.
```c
void optoencoder5_enable ( optoencoder5_t *ctx );
```

- `optoencoder5_disable` This function disables the slotted optical switch of Opto Encoder 5 Click board.
```c
void optoencoder5_disable ( optoencoder5_t *ctx );
```

- `optoencoder5_get_out_state` This function detecting slotted optical switch states of Opto Encoder 5 Click board.
```c
uint8_t optoencoder5_get_out_state ( optoencoder5_t *ctx );
```

### Application Init

> Initialization of GPIO module, log UART and enables the slotted optical switch.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                      /**< Logger config object. */
    optoencoder5_cfg_t optoencoder5_cfg;    /**< Click config object. */

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
    optoencoder5_cfg_setup( &optoencoder5_cfg );
    OPTOENCODER5_MAP_MIKROBUS( optoencoder5_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == optoencoder5_init( &optoencoder5, &optoencoder5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    optoencoder5_enable( &optoencoder5 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> When the beam from the slotted optical switch is broken by placing an object in
  the gap ( like a piece of paper ), the counter is incremented by one 
  when the sensor is triggered.

```c
void application_task ( void ) 
{
    out_state = optoencoder5_get_out_state( &optoencoder5 );
    if ( cmp_state != out_state )
    {
        if ( OPTOENCODER5_OUT_STATE_SWITCH_CLOSED == out_state )
        {
            log_printf( &logger, " Counter: %u \r\n", cnt );
            cnt++;
        }
        cmp_state = out_state;
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
