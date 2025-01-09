
---
# USB-C Source Click

> [USB-C Source Click](https://www.mikroe.com/?pid_product=MIKROE-4329) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4329&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This is an example that demonstrates the use of the USB-C Source Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.USBCSource

### Example Key Functions

- `usbcsource_cfg_setup` Config Object Initialization function.
```c
void usbcsource_cfg_setup ( usbcsource_cfg_t *cfg );
```

- `usbcsource_init` Initialization function.
```c
err_t usbcsource_init ( usbcsource_t *ctx, usbcsource_cfg_t *cfg );
```

- `usbcsource_hw_reset` HW reset function.
```c
void usbcsource_hw_reset ( usbcsource_t *ctx );
```

- `usbcsource_get_alert_status` Get alert status function.
```c
void usbcsource_get_alert_status ( usbcsource_t *ctx, alert_status_t *alert_status_data );
```

- `usbcsource_set_pdo_config` Set PDO configuration function.
```c
uint8_t usbcsource_set_pdo_config ( usbcsource_t *ctx, pdo_config_t pdo_cfg_data );
```

### Application Init

> Initialization driver enables - I2C, set hardware reset and default configuration and display configuration of the five PDOs, also write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcsource_cfg_t usbcsource_cfg;  /**< Click config object. */

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
    usbcsource_cfg_setup( &usbcsource_cfg );
    USBCSOURCE_MAP_MIKROBUS( usbcsource_cfg, MIKROBUS_1 );
    err_t init_flag = usbcsource_init( &usbcsource, &usbcsource_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    usbcsource_hw_reset( &usbcsource );
    Delay_ms ( 500 );
    usbcsource_default_config( &usbcsource );
    Delay_ms ( 500 );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_pdo_config( &usbcsource, USBCSOURCE_SEL_PDO1, &pdo_data );
    log_printf( &logger, " PDO 1 - Voltage = %.2f V \r\n", pdo_data.vtg_data );
    log_printf( &logger, " PDO 1 - Current = %.2f A \r\n", pdo_data.curr_data );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_pdo_config( &usbcsource, USBCSOURCE_SEL_PDO2, &pdo_data );
    log_printf( &logger, " PDO 2 - Voltage = %.2f V \r\n", pdo_data.vtg_data );
    log_printf( &logger, " PDO 2 - Current = %.2f A \r\n", pdo_data.curr_data );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_pdo_config( &usbcsource, USBCSOURCE_SEL_PDO3, &pdo_data );
    log_printf( &logger, " PDO 3 - Voltage = %.2f V \r\n", pdo_data.vtg_data );
    log_printf( &logger, " PDO 3 - Current = %.2f A \r\n", pdo_data.curr_data );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_pdo_config( &usbcsource, USBCSOURCE_SEL_PDO4, &pdo_data );
    log_printf( &logger, " PDO 4 - Voltage = %.2f V \r\n", pdo_data.vtg_data );
    log_printf( &logger, " PDO 4 - Current = %.2f A \r\n", pdo_data.curr_data );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_pdo_config( &usbcsource, USBCSOURCE_SEL_PDO5, &pdo_data );
    log_printf( &logger, " PDO 5 - Voltage = %.2f V \r\n", pdo_data.vtg_data );
    log_printf( &logger, " PDO 5 - Current = %.2f A \r\n", pdo_data.curr_data );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> In this example, we show port status, monitoring, and connections. All data logs write on USB uart changes every 5 sec.

```c
void application_task ( void ) 
{
    usbcsource_get_port_status( &usbcsource, &port_status );
    display_port_status( );
    Delay_ms ( 100 );
    log_printf( &logger, "- - - - - - - - - - - - - - " );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_monitoring_status( &usbcsource, &monitor_status );
    display_monitoring_status( );
    Delay_ms ( 100 );
    log_printf( &logger, "- - - - - - - - - - - - - - " );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_connection_status( &usbcsource, &conn_status );
    display_connection_status( );
    Delay_ms ( 100 );
    log_printf( &logger, "- - - - - - - - - - - - - - " );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    Delay_ms ( 1000 );
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
