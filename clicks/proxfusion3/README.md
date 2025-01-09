
---
# ProxFusion 3 Click

> [ProxFusion 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4469) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4469&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> Display information about the last detected touch.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ProxFusion3

### Example Key Functions

- `proxfusion3_cfg_setup` Config Object Initialization function.
```c
void proxfusion3_cfg_setup ( proxfusion3_cfg_t *cfg );
```

- `proxfusion3_init` Initialization function.
```c
err_t proxfusion3_init ( proxfusion3_t *ctx, proxfusion3_cfg_t *cfg );
```

- `proxfusion3_default_cfg` Click Default Configuration function.
```c
void proxfusion3_default_cfg ( proxfusion3_t *ctx );
```

- `proxfusion3_get_touch` ProxFusion 3 get touch function.
```c
uint8_t proxfusion3_get_touch ( proxfusion3_t *ctx );
```

- `proxfusion3_check_touch_event` ProxFusion 3 check touch event function.
```c
uint8_t proxfusion3_check_touch_event ( proxfusion3_t *ctx );
```

- `proxfusion3_get_version_info` ProxFusion 3 get version info data function.
```c
err_t proxfusion3_get_version_info ( proxfusion3_t *ctx, uint8_t *product_number, uint8_t *software_version );
```

### Application Init

> Initializes I2C driver, read and display version info value
and start to write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    proxfusion3_cfg_t proxfusion3_cfg;  /**< Click config object.  */

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
    log_printf( &logger, "\r\n---------------------------\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    proxfusion3_cfg_setup( &proxfusion3_cfg );
    PROXFUSION3_MAP_MIKROBUS( proxfusion3_cfg, MIKROBUS_1 );
    err_t init_flag = proxfusion3_init( &proxfusion3, &proxfusion3_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    proxfusion3_default_cfg ( &proxfusion3 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 500 );
    
    proxfusion3_get_version_info( &proxfusion3, &product_number, &software_version );
    log_printf( &logger, "  Product Number   : 0x%.2X \r\n", ( uint16_t )product_number );
    log_printf( &logger, "  Software Version : 0x%.2X \r\n", ( uint16_t )software_version );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "      Touch Detection      \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
}
```

### Application Task

> This is an example that demonstrates the use of the ProxFusion 3 Click board.
In this example, we check the touch event and display the last detected touch. 
Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    if ( proxfusion3_check_touch_event( &proxfusion3 ) == PROXFUSION3_EVENT_TOUCH ) {        
        uint8_t touch_data = proxfusion3_get_touch( &proxfusion3 );
        Delay_ms ( 100 );
        
        switch ( touch_data ) {
            case PROXFUSION3_TOUCH_POS_8: {
                log_printf( &logger, "       >>>   8   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_7: {
                log_printf( &logger, "       >>>   7   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_6: {
                log_printf( &logger, "       >>>   6   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_5: {
                log_printf( &logger, "       >>>   5   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_4: {
                log_printf( &logger, "       >>>   4   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_3: {
                log_printf( &logger, "       >>>   3   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_2: {
                log_printf( &logger, "       >>>   2   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_1: {
                log_printf( &logger, "       >>>   1   <<<       \r\n" );
                break;
            }
            default: {
                Delay_ms ( 10 );
                break;
            }
        }
        
        Delay_ms ( 10 );
    } else {
        Delay_ms ( 10 );
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
