
---
# Opto 3 Click

> [Opto 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3319) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3319&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> Opto 3 Click to be used in applications that require reinforced galvanic 
> isolation for both their input and output stages.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Opto3

### Example Key Functions

- `opto3_cfg_setup` Config Object Initialization function.
```c
void opto3_cfg_setup ( opto3_cfg_t *cfg ); 
```

- `opto3_init` Initialization function.
```c
err_t opto3_init ( opto3_t *ctx, opto3_cfg_t *cfg );
```

- `opto3_get_in1` This function gets input 1 pin state.
```c
uint8_t opto3_get_in1 ( opto3_t *ctx );
```

- `opto3_get_in2` This function gets input 2 pin state.
```c
uint8_t opto3_get_in2 ( opto3_t *ctx );
```

- `opto3_set_out1` This function sets output 1 pin state.
```c
void opto3_set_out1 ( opto3_t *ctx, uint8_t state );
```

### Application Init

> Initializes GPIO interface.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    opto3_cfg_t cfg;

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
    opto3_cfg_setup( &cfg );
    OPTO3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    opto3_init( &opto3, &cfg );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the input pins state and sets their respective output pins to the same logic state.
> The output pins state will be displayed on the USB UART where you can track their changes.

```c
void application_task ( void )
{
    static uint8_t out1_state = 0;
    static uint8_t out2_state = 0;
    uint8_t in1_state = 0;
    uint8_t in2_state = 0;

    in1_state = opto3_get_in1( &opto3 );
    in2_state = opto3_get_in2( &opto3 );
    
    if ( in1_state != out1_state )
    {
        out1_state = in1_state;
        opto3_set_out1( &opto3, out1_state );
        log_printf( &logger, " OUT1 state: %u\r\n", ( uint16_t ) out1_state );
    }
    
    if ( in2_state != out2_state )
    {
        out2_state = in2_state;
        opto3_set_out2( &opto3, out2_state );
        log_printf( &logger, " OUT2 state: %u\r\n", ( uint16_t ) out2_state );
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
