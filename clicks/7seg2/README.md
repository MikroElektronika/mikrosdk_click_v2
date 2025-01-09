
---
# 7-SEG 2 Click

> [7-SEG 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6005) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6005&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Sep 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> The example demonstrates the use of the 7-SEG 2 Click board by displaying a counter number [0.00-9.99] which is incremented by 0.01 at a desired rate.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.7SEG2

### Example Key Functions

- `c7seg2_cfg_setup` Config Object Initialization function.
```c
void c7seg2_cfg_setup ( c7seg2_cfg_t *cfg );
```

- `c7seg2_init` Initialization function.
```c
err_t c7seg2_init ( c7seg2_t *ctx, c7seg2_cfg_t *cfg );
```

- `c7seg2_default_cfg` Click Default Configuration function.
```c
err_t c7seg2_default_cfg ( c7seg2_t *ctx );
```

- `c7seg2_set_segments_current` This function is used to set the current value of the segment's leds.
```c
err_t c7seg2_set_segments_current ( c7seg2_t *ctx, float current_val );
```

- `c7seg2_write_segment` This function is used to write a number [0..9] to a selected segment [0..2] with or w/o a decimal pointer.
```c
err_t c7seg2_write_segment ( c7seg2_t *ctx, uint8_t segment, uint8_t number, uint8_t dpt );
```

- `c7seg2_write_number` This function is used to write a number [0..999] to a selected segment [0..2] with or w/o a decimal pointer.
```c
err_t c7seg2_write_number ( c7seg2_t *ctx, uint16_t number, uint8_t dpt );
```

### Application Init

> Initializes the driver and performs default configuration, sets the device in output enabled mode and checks communication by reading device ID.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c7seg2_cfg_t c7seg2_pnp_cfg;  /**< Click config object. */

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
    c7seg2_cfg_setup( &c7seg2_pnp_cfg );
    C7SEG2_MAP_MIKROBUS( c7seg2_pnp_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c7seg2_init( &c7seg2, &c7seg2_pnp_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint8_t device_id = 0;
    c7seg2_read_reg( &c7seg2, C7SEG2_REG_DEVICE_ID, &device_id );
    if ( C7SEG2_DEVICE_ID != device_id )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    if ( C7SEG2_ERROR == c7seg2_default_cfg ( &c7seg2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Writes a counter number [0.00-9.99] to the display as frequently as possible. The displayed counter value is incremented by 0.01 at a rate defined with the C7SEG2_NUM_COUNTER_RATE macro.

```c
void application_task ( void )
{
    static uint16_t counter = 0;
    static uint16_t time = 0;
    
    c7seg2_write_number( &c7seg2, counter, C7SEG2_DP_AT_SEGMENT_2 );
    
    if ( ++time >= C7SEG2_NUM_COUNTER_RATE ) 
    {
        if ( ++counter > C7SEG2_MAX_NUMBER )
        {
            counter = 0;
        }
        time = 0;
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
