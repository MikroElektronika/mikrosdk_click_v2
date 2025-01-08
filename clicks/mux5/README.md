
---
# MUX 5 Click

> [MUX 5 Click](https://www.mikroe.com/?pid_product=MIKROE-5423) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5423&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of MUX 5 Click board by mapping the common connection A and B to different channels every 5 seconds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MUX5

### Example Key Functions

- `mux5_cfg_setup` Config Object Initialization function.
```c
void mux5_cfg_setup ( mux5_cfg_t *cfg );
```

- `mux5_init` Initialization function.
```c
err_t mux5_init ( mux5_t *ctx, mux5_cfg_t *cfg );
```

- `mux5_default_cfg` Click Default Configuration function.
```c
err_t mux5_default_cfg ( mux5_t *ctx );
```

- `mux5_i2c_write_register` This function writes a desired data to the selected register by using I2C serial interface.
```c
err_t mux5_i2c_write_register ( mux5_t *ctx, uint8_t reg, uint8_t data_in );
```

- `mux5_i2c_read_register` This function reads data from the selected register by using I2C serial interface.
```c
err_t mux5_i2c_read_register ( mux5_t *ctx, uint8_t reg, uint8_t *data_out );
```

- `mux5_set_channels_state` This function sets a desired @b ch_state of the channels selected with @b ch_mask.
```c
err_t mux5_set_channels_state ( mux5_t *ctx, uint16_t ch_mask, uint8_t ch_state );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mux5_cfg_t mux5_cfg;  /**< Click config object. */

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
    mux5_cfg_setup( &mux5_cfg );
    MUX5_MAP_MIKROBUS( mux5_cfg, MIKROBUS_1 );
    if ( MUX5_OK != mux5_init( &mux5, &mux5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MUX5_OK != mux5_default_cfg ( &mux5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Maps the common connection A and B to different channels every 5 seconds, and displays the channels state on the USB UART.

```c
void application_task ( void )
{
    static uint8_t ch_num = 0;
    if ( MUX5_OK == mux5_set_channels_state ( &mux5, MUX5_CHANNEL_ALL, MUX5_CHANNEL_STATE_HIGH_Z ) )
    {
        log_printf ( &logger, " All channels disconnected\r\n" );
    }
    Delay_ms ( 1000 );
    if ( MUX5_OK == mux5_set_channels_state ( &mux5, MUX5_CHANNEL_1 << ch_num, MUX5_CHANNEL_STATE_COM_A ) )
    {
        log_printf ( &logger, " Channel %u connected to COM_A\r\n", ( uint16_t ) ( ch_num + 1 ) );
    }
    if ( MUX5_OK == mux5_set_channels_state ( &mux5, MUX5_CHANNEL_16 >> ch_num, MUX5_CHANNEL_STATE_COM_B ) )
    {
        log_printf ( &logger, " Channel %u connected to COM_B\r\n\n", ( uint16_t ) ( 16 - ch_num ) );
    }
    if ( ++ch_num >= 16 )
    {
        ch_num = 0;
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
