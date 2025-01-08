
---
# Accel 14 Click

> [Accel 14 Click](https://www.mikroe.com/?pid_product=MIKROE-4185) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4185&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This application measures accelermeter data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel14

### Example Key Functions

- `accel14_cfg_setup` Config Object Initialization function. 
```c
void accel14_cfg_setup ( accel14_cfg_t *cfg );
``` 
 
- `accel14_init` Initialization function. 
```c
err_t accel14_init ( accel14_t *ctx, accel14_cfg_t *cfg );
```

- `accel14_default_cfg` Click Default Configuration function. 
```c
void accel14_default_cfg ( accel14_t *ctx );
```

- `accel14_check_accel_data_ready` Check accel data ready function. 
```c
uint8_t accel14_check_accel_data_ready ( accel14_t *ctx );
```
 
- `accel14_get_temperature` Get temperature function. 
```c
float accel14_get_temperature ( accel14_t *ctx );
```

- `accel14_read_accel` Read Accel data function. 
```c
void accel14_read_accel( accel14_t *ctx, accel14_accel_fs_xl_t *accel_fs );
```

### Application Init

> SPI, check device ID, sets default configuration, also write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    accel14_cfg_t cfg;

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

    accel14_cfg_setup( &cfg );
    ACCEL14_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel14_init( &accel14, &cfg );

    Delay_ms ( 100 );
    
    log_printf( &logger, "   Driver init done   \r\n" );
    log_printf( &logger, "--------------------- \r\n" );
    log_printf( &logger, " Communication check  \r\n" );
    
    if ( accel14_check_communication( &accel14 ) == ACCEL14_CHECK_ID_SUCCESS )
    {
        log_printf( &logger, "       SUCCESS        \r\n" );
        log_printf( &logger, "--------------------- \r\n" );
    }
    else
    {
        log_printf( &logger, "        ERROR         \r\n" );
        log_printf( &logger, "   Reset the device   \r\n" );
        log_printf( &logger, "--------------------- \r\n" );
        for ( ; ; );
    }
    
    log_printf( &logger, " Set default config.  \r\n" );
    log_printf( &logger, "--------------------- \r\n" );
    accel14_default_cfg( &accel14 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "  Acceleration data:  \r\n" );
    log_printf( &logger, "--------------------- \r\n" );
}
```

### Application Task

> This is an example which demonstrates the use of Accel 14 Click board.
> Measured and display Acceleration data for X-axis, Y-axis and Z-axis.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB uart changes for every 1 sec.

```c
void application_task ( void )
{
    data_ready_flag = accel14_check_accel_data_ready( &accel14 );
    Delay_ms ( 10 );
    
    if ( data_ready_flag == ACCEL14_NEW_DATA_AVAILABLE )
    {
        accel14_get_data ( &accel14, &accel_data );

        log_printf( &logger, "  Accel X : %d \r\n", accel_data.x );
        log_printf( &logger, "  Accel Y : %d \r\n", accel_data.y );
        log_printf( &logger, "  Accel Z : %d \r\n", accel_data.z );
        log_printf( &logger, "--------------------- \r\n" );
        Delay_ms ( 1000 );
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
