
---
# IR Gesture 2 Click

> [IR Gesture 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5146) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5146&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of IR Gesture 2 Click board by reading and displaying the raw ADC values of entire 60-pixel IR photodiode array.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IRGesture2

### Example Key Functions

- `irgesture2_cfg_setup` Config Object Initialization function.
```c
void irgesture2_cfg_setup ( irgesture2_cfg_t *cfg );
```

- `irgesture2_init` Initialization function.
```c
err_t irgesture2_init ( irgesture2_t *ctx, irgesture2_cfg_t *cfg );
```

- `irgesture2_default_cfg` Click Default Configuration function.
```c
err_t irgesture2_default_cfg ( irgesture2_t *ctx );
```

- `irgesture2_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t irgesture2_get_int_pin ( irgesture2_t *ctx );
```

- `irgesture2_read_pixels` This function reads the raw ADC values of entire 60-pixel IR photodiode array.
```c
err_t irgesture2_read_pixels ( irgesture2_t *ctx, int16_t *pixels, bool flip_pixels );
```

- `irgesture2_write_register` This function writes a data byte to the selected register by using SPI serial interface.
```c
err_t irgesture2_write_register ( irgesture2_t *ctx, uint8_t reg, uint8_t data_in );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irgesture2_cfg_t irgesture2_cfg;  /**< Click config object. */

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
    irgesture2_cfg_setup( &irgesture2_cfg );
    IRGESTURE2_MAP_MIKROBUS( irgesture2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == irgesture2_init( &irgesture2, &irgesture2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IRGESTURE2_ERROR == irgesture2_default_cfg ( &irgesture2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for an end of conversion interrupt and then reads the raw ADC values of entire
60-pixel IR photodiode array and displays the results on the USB UART as a 10x6 matrix every 100ms approximately.

```c
void application_task ( void )
{
    // Wait for an end of conversion interrupt
    while ( irgesture2_get_int_pin ( &irgesture2 ) );
    
    int16_t pixels[ IRGESTURE2_NUM_SENSOR_PIXELS ];
    if ( IRGESTURE2_OK == irgesture2_read_pixels ( &irgesture2, pixels, false ) )
    {
        for ( uint8_t cnt = 0; cnt < IRGESTURE2_NUM_SENSOR_PIXELS; cnt++ )
        {
            if ( 0 == ( cnt % IRGESTURE2_SENSOR_X_SIZE ) )
            {
                log_printf( &logger, "\r\n" );
            }
            log_printf( &logger, "%d\t", pixels[ cnt ] );
        }
        log_printf( &logger, "\r\n" );
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
