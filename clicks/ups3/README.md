
---
# UPS 3 Click

> [UPS 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4479) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4479&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application demonstrates the use of UPS 3 Click board. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ups3

### Example Key Functions

- `ups3_cfg_setup` Config Object Initialization function.
```c
void ups3_cfg_setup ( ups3_cfg_t *cfg );
```

- `ups3_init` Initialization function.
```c
err_t ups3_init ( ups3_t *ctx, ups3_cfg_t *cfg );
```

- `ups3_default_cfg` Click Default Configuration function.
```c
void ups3_default_cfg ( ups3_t *ctx );
```

- `ups3_set_enable` UPS 3 enable device function.
```c
err_t ups3_set_enable ( ups3_t *ctx, uint8_t enable );ON>
```

- `ups3_get_error` UPS 3 get error function.
```c
uint8_t ups3_get_error ( ups3_t *ctx );
```

- `ups3_get_chrg` UPS 3 get charge/backup mode function.
```c
uint8_t ups3_get_chrg ( ups3_t *ctx );
```

### Application Init

> Initialization driver enable's - GPIO, also write log.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;    /**< Logger config object. */
    ups3_cfg_t ups3_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    ups3_cfg_setup( &ups3_cfg );
    UPS3_MAP_MIKROBUS( ups3_cfg, MIKROBUS_1 );
    if ( ups3_init( &ups3, &ups3_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    ups3_default_cfg ( &ups3 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> With this example we show the operation of UPS 3 Clicks.
> This example shows an autonomously transition from charge to backup mode.
> Results are being sent to the Usart Terminal where you can track their changes. 

```c
void application_task ( void ) 
{      
    if ( ups3_get_error( &ups3 ) == UPS3_GET_ERROR_CMPIN_OK ) {
        if ( ups3_get_cap_ok( &ups3 ) != cok_status ) {
            new_status = UPS3_STATUS_NEW; 
            cok_status = ups3_get_cap_ok( &ups3 );
        } else {
            new_status = UPS3_STATUS_OLD;    
        }
    
        if ( new_status == UPS3_STATUS_NEW ) {
            ups3_hw_reset( &ups3 );
            new_status = UPS3_STATUS_OLD;
        }
        
        if ( ( ups3_get_chrg( &ups3 ) == UPS3_GET_CHRG_BACKUP_MODE ) && 
             ( ups3_get_cap_ok( &ups3 ) == UPS3_GET_CAP_OK_FBV_LOW ) ) {
            log_printf( &logger, "      Backup Mode ON      \r\n" );
        }
        
        if ( ups3_get_cap_ok( &ups3 ) == UPS3_GET_CAP_OK_FBV_HIGH ) {
            log_printf( &logger, "       Vcap charged       \r\n" );
        }
    } else {
        log_printf( &logger, "      Backup Mode OFF     \r\n" );
        log_printf( &logger, " Turn ON the Power Supply \r\n" );
            
        while ( ups3_get_error( &ups3 ) == UPS3_GET_ERROR_CMPIN_EMPTY ) {
            Delay_ms ( 100 );   
        }
            
        ups3_hw_reset( &ups3 );
        Delay_ms ( 100 );
    }
    
    log_printf( &logger, "--------------------------\r\n" );
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
