
---
# ATA6571 Click

> [ATA6571 Click](https://www.mikroe.com/?pid_product=MIKROE-4381) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4381&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from ATA6571 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ATA6571

### Example Key Functions

- `ata6571_cfg_setup` Config Object Initialization function.
```c
void ata6571_cfg_setup ( ata6571_cfg_t *cfg );
```

- `ata6571_init` Initialization function.
```c
err_t ata6571_init ( ata6571_t *ctx, ata6571_cfg_t *cfg );
```

- `ata6571_set_operating_mode` This function sets the device operating mode by controlling the EN and NSTB pins.
```c
void ata6571_set_operating_mode ( ata6571_t *ctx, uint8_t op_mode );
```

- `ata6571_generic_write` This function writes a desired number of data bytes by using UART serial interface.
```c
err_t ata6571_generic_write ( ata6571_t *ctx, char *data_buf, uint16_t len );
```

- `ata6571_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t ata6571_generic_read ( ata6571_t *ctx, char *data_buf, uint16_t max_len );
```

### Application Init

> Initializes the driver and sets the device operating mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    ata6571_cfg_t ata6571_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    ata6571_cfg_setup( &ata6571_cfg );
    ATA6571_MAP_MIKROBUS( ata6571_cfg, MIKROBUS_1 );
    err_t init_flag = ata6571_init( &ata6571, &ata6571_cfg );
    if ( UART_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 100 );
    
#ifdef DEMO_APP_RECEIVER
    log_printf( &logger, "---- RECEIVER MODE ----\r\n" );
#endif 
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, "---- TRANSMITTER MODE ----\r\n" );
#endif 
    
    ata6571_set_operating_mode ( &ata6571, ATA6571_OPERATING_MODE_NORMAL );
    app_buf_len = 0;
    app_buf_cnt = 0;

    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> Depending on the selected demo application mode, it reads all the received data or sends the desired message every 2 seconds.

```c
void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    ata6571_process();

    if ( app_buf_len > 0 ) 
    {
        Delay_ms ( 100 );
        ata6571_process();
        
        log_printf( &logger, "%s", app_buf );
        log_printf( &logger, "-------------------------------------\r\n" );
        ata6571_clear_app_buf(  );
    }
#endif  

#ifdef DEMO_APP_TRANSMITTER 
    ata6571_generic_write( &ata6571, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_printf( &logger, "---- The message has been sent ----\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
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
