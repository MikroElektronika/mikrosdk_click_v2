
---
# Opto 8 Click

> [Opto 8 Click](https://www.mikroe.com/?pid_product=MIKROE-6928) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6928&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2026.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the Opto 8 Click board by monitoring
the state of opto-isolated inputs and controlling the corresponding outputs.
When an input state changes, the application updates the related output and
logs the new state to the serial terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Opto8

### Example Key Functions

- `opto8_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void opto8_cfg_setup ( opto8_cfg_t *cfg );
```

- `opto8_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t opto8_init ( opto8_t *ctx, opto8_cfg_t *cfg );
```

- `opto8_default_cfg` This function executes a default configuration of Opto 8 Click board.
```c
err_t opto8_default_cfg ( opto8_t *ctx );
```

- `opto8_set_out1` This function sets the output 1 control pin to high logic state.
```c
void opto8_set_out1 ( opto8_t *ctx );
```

- `opto8_clear_out1` This function clears the output 1 control pin to low logic state.
```c
void opto8_clear_out1 ( opto8_t *ctx );
```

- `opto8_get_in1` This function reads the input 1 status pin logic state.
```c
uint8_t opto8_get_in1 ( opto8_t *ctx );
```

### Application Init

> Initializes the logger and Opto 8 Click driver and configures the digital input and output pins through the mikroBUS socket.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    opto8_cfg_t opto8_cfg;  /**< Click config object. */

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
    opto8_cfg_setup( &opto8_cfg );
    OPTO8_MAP_MIKROBUS( opto8_cfg, MIKROBUS_POSITION_OPTO8 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == opto8_init( &opto8, &opto8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads the states of the opto-isolated inputs and updates the
corresponding outputs when a change is detected, logging the output state
to the serial terminal.

```c
void application_task ( void )
{
    static uint8_t out1_state = 255;
    static uint8_t out2_state = 255;
    uint8_t in1_state = 0;
    uint8_t in2_state = 0;

    in1_state = opto8_get_in1( &opto8 );
    in2_state = opto8_get_in2( &opto8 );
    
    if ( ( in1_state != out1_state ) || ( in2_state != out2_state ) )
    {
        out1_state = in1_state;
        if ( out1_state )
        {
            opto8_clear_out1( &opto8 );
            log_printf( &logger, " OUT1 state: Disabled\r\n" );
        }
        else
        {
            opto8_set_out1( &opto8 );
            log_printf( &logger, " OUT1 state: Enabled\r\n" );
        }

        out2_state = in2_state;
        if ( out2_state )
        {
            opto8_clear_out2( &opto8 );
            log_printf( &logger, " OUT2 state: Disabled\r\n\n" );
        }
        else
        {
            opto8_set_out2( &opto8 );
            log_printf( &logger, " OUT2 state: Enabled\r\n\n" );
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
