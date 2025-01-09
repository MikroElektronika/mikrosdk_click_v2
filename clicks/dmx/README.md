
---
# DMX Click

> [DMX Click](https://www.mikroe.com/?pid_product=MIKROE-4130) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4130&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of the DMX Click board by showcasing the control for a 6-channel DMX RGB LED reflector connected to it.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Dmx

### Example Key Functions

- `dmx_cfg_setup` Config Object Initialization function.
```c
void dmx_cfg_setup ( dmx_cfg_t *cfg ); 
```

- `dmx_init` Initialization function.
```c
err_t dmx_init ( dmx_t *ctx, dmx_cfg_t *cfg );
```

- `dmx_generic_write` Generic write function.
```c
void dmx_generic_write ( dmx_t *ctx, uint8_t *data_buf, uint16_t len );
```

- `dmx_generic_read` Generic read function.
```c
err_t dmx_generic_read ( dmx_t *ctx, uint8_t *data_buf, uint16_t max_len );
```

- `dmx_send_cmd` Send command function.
```c
void dmx_send_cmd ( dmx_t* ctx, uint8_t *cmd );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dmx_cfg_t cfg;

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
    dmx_cfg_setup( &cfg );
    DMX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dmx_init( &dmx, &cfg );

    dmx_set_auto_baud_rate( &dmx, 1 );
    Delay_ms ( 100 );

    dmx_reset( &dmx, DMX_MASTER );
    dmx_run( &dmx, DMX_CONFIG_MODE );
    Delay_ms ( 100 );
    
    dmx_process( );
    dmx_clear_app_buf( );

    // Clear the internal buffers
    dmx_send_cmd( &dmx, DMX_CMD_PURGEBFR );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );

    // Set start address
    dmx_send_cmd( &dmx, DMX_CMD_SADR );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );

    // Set input data buffer length
    dmx_send_cmd( &dmx, DMX_CMD_BLEN );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );

    // Set DMX frame length
    dmx_send_cmd( &dmx, DMX_CMD_FLEN_MASTER );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );

    // Set interrupt pulse duration
    dmx_send_cmd( &dmx, DMX_CMD_ITMR );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );

    // Set a time delay between two frames
    dmx_send_cmd( &dmx, DMX_CMD_FTMR );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );

    // Display configuration
    dmx_send_cmd( &dmx, DMX_CMD_DISPLCFG );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );
    dmx_clear_app_buf( );
    
    dmx_run( &dmx, DMX_RUN_MODE );

    log_info( &logger, " Application Task " );
    Delay_ms ( 500 );
}
```

### Application Task

> Performs the LEDs dimming control on a 6-channel DMX RGB LED reflector.

```c
void application_task ( void )
{
    uint8_t dmx_6_ch_buf[ 6 ] = { 0 };
    int16_t cnt = 0;
    
    dmx_6_ch_buf[ 0 ] = 255; // Dimmer
    dmx_6_ch_buf[ 1 ] = 0;   // Red
    dmx_6_ch_buf[ 2 ] = 0;   // Green
    dmx_6_ch_buf[ 3 ] = 0;   // Blue
    dmx_6_ch_buf[ 4 ] = 0;   // Strobe
    dmx_6_ch_buf[ 5 ] = 0;   // Macro
    
    log_printf( &logger, "\r\nDimming RED LEDs\r\n" );
    for ( cnt = 0; cnt <= 255; cnt++ )
    {
        dmx_6_ch_buf[ 1 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    for ( cnt = 255; cnt >= 0; cnt-- )
    {
        dmx_6_ch_buf[ 1 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    
    log_printf( &logger, "Dimming GREEN LEDs\r\n" );
    for ( cnt = 0; cnt <= 255; cnt++ )
    {
        dmx_6_ch_buf[ 2 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    for ( cnt = 255; cnt >= 0; cnt-- )
    {
        dmx_6_ch_buf[ 2 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    
    log_printf( &logger, "Dimming BLUE LEDs\r\n" );
    for ( cnt = 0; cnt <= 255; cnt++ )
    {
        dmx_6_ch_buf[ 3 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    for ( cnt = 255; cnt >= 0; cnt-- )
    {
        dmx_6_ch_buf[ 3 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    
    dmx_6_ch_buf[ 1 ] = 255;
    dmx_6_ch_buf[ 2 ] = 255;
    dmx_6_ch_buf[ 3 ] = 255;
    log_printf( &logger, "Dimming all LEDs\r\n" );
    for ( cnt = 0; cnt <= 255; cnt++ )
    {
        dmx_6_ch_buf[ 0 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    for ( cnt = 255; cnt >= 0; cnt-- )
    {
        dmx_6_ch_buf[ 0 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
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
