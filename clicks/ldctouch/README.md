
---
# LDC Touch Click

> [LDC Touch Click](https://www.mikroe.com/?pid_product=MIKROE-5204) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5204&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of LDC Touch Click board by configuring
the buttons to trigger on finger press, and reading the buttons state in the loop.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LDCTouch

### Example Key Functions

- `ldctouch_cfg_setup` Config Object Initialization function.
```c
void ldctouch_cfg_setup ( ldctouch_cfg_t *cfg );
```

- `ldctouch_init` Initialization function.
```c
err_t ldctouch_init ( ldctouch_t *ctx, ldctouch_cfg_t *cfg );
```

- `ldctouch_default_cfg` Click Default Configuration function.
```c
err_t ldctouch_default_cfg ( ldctouch_t *ctx );
```

- `ldctouch_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t ldctouch_get_int_pin ( ldctouch_t *ctx );
```

- `ldctouch_get_data` This function reads status, out_state, and all buttons raw data.
```c
err_t ldctouch_get_data ( ldctouch_t *ctx, ldctouch_data_t *button_data );
```

- `ldctouch_set_operation_mode` This function sets the operation mode.
```c
err_t ldctouch_set_operation_mode ( ldctouch_t *ctx, uint8_t mode );
```

### Application Init

> Initializes the driver and configures the buttons to be active on finger press.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ldctouch_cfg_t ldctouch_cfg;  /**< Click config object. */

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
    ldctouch_cfg_setup( &ldctouch_cfg );
    LDCTOUCH_MAP_MIKROBUS( ldctouch_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ldctouch_init( &ldctouch, &ldctouch_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LDCTOUCH_ERROR == ldctouch_default_cfg ( &ldctouch ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the button active event interrupt and then reads and displays the buttons
state and their raw data on the USB UART every 200ms approximately.

```c
void application_task ( void )
{
    static bool button_active = true;
    if ( !ldctouch_get_int_pin ( &ldctouch ) )
    {
        ldctouch_data_t button_data;
        if ( LDCTOUCH_OK == ldctouch_get_data ( &ldctouch, &button_data ) )
        {
            button_active = true;
            log_printf ( &logger, " Active button: -" ); 
            for ( uint8_t cnt = 0; cnt < 4; cnt++ )
            {
                if ( button_data.out_state & ( 1 << cnt ) )
                {
                    log_printf ( &logger, " %u - ", ( uint16_t ) cnt ); 
                }
            }
            log_printf ( &logger, "\r\n Button 0 raw data: %d\r\n", button_data.ch0_raw_button );
            log_printf ( &logger, " Button 1 raw data: %d\r\n", button_data.ch1_raw_button );
            log_printf ( &logger, " Button 2 raw data: %d\r\n", button_data.ch2_raw_button );
            log_printf ( &logger, " Button 3 raw data: %d\r\n\n", button_data.ch3_raw_button );
            Delay_ms ( 200 );
        }
    }
    else
    {
        if ( button_active )
        {
            button_active = false;
            log_printf ( &logger, " Active button: - none -\r\n" ); 
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
