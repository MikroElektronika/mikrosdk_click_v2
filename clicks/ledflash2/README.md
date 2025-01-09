
---
# Led Flash 2 Click

> [Led Flash 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2830) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2830&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This app demonstrate flash and torch mode on LED light.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LedFlash2

### Example Key Functions

- `ledflash2_cfg_setup` Config Object Initialization function. 
```c
void ledflash2_cfg_setup ( ledflash2_cfg_t *cfg );
``` 
 
- `ledflash2_init` Initialization function. 
```c
err_t ledflash2_init ( ledflash2_t *ctx, ledflash2_cfg_t *cfg );
```

- `ledflash2_default_cfg` Click Default Configuration function. 
```c
void ledflash2_default_cfg ( ledflash2_t *ctx );
```

- `ledflash2_read_register` This function reads raw data from any register. 
```c
uint8_t ledflash2_read_register ( ledflash2_t *ctx, uint8_t reg_address );
```
 
- `ledflash2_write_register` This function writes data into any register. 
```c
void ledflash2_write_register ( ledflash2_t *ctx, uint8_t reg_address, uint8_t reg_data );
```

- This function will set the flash inhibit pin to either 1 or 0. It should be
- `ledflash2_toggle_flash_inhibit` used when Click is in flash mode, to reduce the flash intensity. 
```c
void ledflash2_toggle_flash_inhibit ( ledflash2_t *ctx, uint8_t pin_state );
```

### Application Init

> Initializes device and sets the Click into "OFF" mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ledflash2_cfg_t cfg;

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

    ledflash2_cfg_setup( &cfg );
    LEDFLASH2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ledflash2_init( &ledflash2, &cfg );

    ledflash2_set_mode( &ledflash2, LEDFLASH2_MODE_OFF, 0, 0 );
    log_printf( &logger, "Initialized...\r\n" );
}
```

### Application Task

> This function will demonstrate how to use the flash mode,
> and the torch mode, with different power settings. 
> It will then turn the Click off.

```c
void application_task ( void )
{
    Delay_ms ( 1000 );
    log_printf( &logger, "Do not look directly into the led lights.\r\n" );
    log_printf( &logger, "Triggering flash in 5...\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "4...\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "3...\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "2...\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "1...\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "Cheese!\r\n" );

    ledflash2_set_mode( &ledflash2, LEDFLASH2_MODE_FLASH, LEDFLASH2_CUR_50, LEDFLASH2_FTMR_312 );
    Delay_ms ( 350 );
    ledflash2_set_mode( &ledflash2, LEDFLASH2_MODE_OFF, 0, 0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "Switching to the torch mode in a moment...\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    ledflash2_set_mode( &ledflash2, LEDFLASH2_MODE_TORCH, LEDFLASH2_CUR_100, 0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "Dimming the torch light...\r\n" );
    
    for ( uint8_t cnt = LEDFLASH2_CUR_100; cnt <= LEDFLASH2_CUR_18; cnt++ )
    {
        ledflash2_set_mode( &ledflash2, LEDFLASH2_MODE_TORCH, cnt, 0 );
        Delay_ms ( 500 );
    }
    Delay_ms ( 1000 );
    log_printf( &logger, "Switching off...\r\n" );
    ledflash2_set_mode( &ledflash2, LEDFLASH2_MODE_OFF, 0, 0 );
    log_printf( &logger, "------------------------------------------------\r\n" );
}
 

```

### Note

> LED lights can be very bright, even on lowest power settings.
> Avoid looking directly into the light when Click is in operation.

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
