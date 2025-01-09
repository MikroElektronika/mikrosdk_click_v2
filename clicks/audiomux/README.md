
---
# AudioMUX Click

> [AudioMUX Click](https://www.mikroe.com/?pid_product=MIKROE-3344) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3344&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> The following demo shows basic Click functionality:
Initializes AudioMUX device to work with the desired configurations and
shows a message on uart when playing is started. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AudioMUX

### Example Key Functions

- `audiomux_cfg_setup` Config Object Initialization function. 
```c
void audiomux_cfg_setup ( audiomux_cfg_t *cfg );
``` 
 
- `audiomux_init` Initialization function. 
```c
err_t audiomux_init ( audiomux_t *ctx, audiomux_cfg_t *cfg );
```

- `audiomux_default_cfg` Click Default Configuration function. 
```c
void audiomux_default_cfg ( audiomux_t *ctx );
```

- This function performs a input selection and control.
err_t audiomux_select_input ( audiomux_t *ctx, uint8_t input_sel, uint8_t mute_in,
>                                           uint8_t mic_gain, uint8_t mic_state );
 
- This function performs a left or right volume control.
err_t audiomux_set_volume ( audiomux_t *ctx, uint8_t volume1, uint8_t volume2,
>                                         uint8_t side_sel );

- `audiomux_set_treble_bass` This function performs a control of the treble and bass for EQ section. 
```c
err_t audiomux_set_treble_bass ( audiomux_t *ctx, uint8_t treble, uint8_t bass );
```

### Application Init

> Initializes Click and logger driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    audiomux_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    audiomux_cfg_setup( &cfg );
    AUDIOMUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audiomux_init( &audiomux, &cfg );

    init_check = 0;
    mess_cnt   = 0;

    log_info( &logger, "** AudioMUX initialized **\r\n" );
}
```

### Application Task

> Plays selected channel and shows output on the terminal.

```c
void application_task ( void )
{
    if (init_check == 0)
    {
        audiomux_default_cfg ( &audiomux );
        init_check = 1;

        log_printf( &logger, "Playing from IN1 " );
        Delay_ms ( 1000 );
    }

    if (mess_cnt < 5)
    {
        log_printf( &logger, ". " );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        mess_cnt++;
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
