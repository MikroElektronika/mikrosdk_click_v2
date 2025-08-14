
---
# Charger 29 Click

> [Charger 29 Click](https://www.mikroe.com/?pid_product=MIKROE-6652) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6652&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Charger 29 Click board.
The application initializes the device and periodically checks the charging status.
The status is displayed over the UART terminal and reflects whether the battery is 
charging in constant current (CC) mode, constant voltage (CV) mode, fully charged,
or not charging.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger29

### Example Key Functions

- `charger29_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void charger29_cfg_setup ( charger29_cfg_t *cfg );
```

- `charger29_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t charger29_init ( charger29_t *ctx, charger29_cfg_t *cfg );
```

- `charger29_default_cfg` This function executes a default configuration of Charger 29 Click board.
```c
err_t charger29_default_cfg ( charger29_t *ctx );
```

- `charger29_enable_charging` This function enables charging by clearing the charging disable bit.
```c
err_t charger29_enable_charging ( charger29_t *ctx );
```

- `charger29_set_charging_current` This function sets the charging current based on the specified value in milliamps.
```c
err_t charger29_set_charging_current ( charger29_t *ctx, uint16_t ichg );
```

- `charger29_read_status` This function reads the status and flag registers of the Charger 29 Click board.
```c
err_t charger29_read_status ( charger29_t *ctx, charger29_status_t *status );
```

### Application Init

> Initializes the logger and the Charger 29 Click driver and applies default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger29_cfg_t charger29_cfg;  /**< Click config object. */

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
    charger29_cfg_setup( &charger29_cfg );
    CHARGER29_MAP_MIKROBUS( charger29_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == charger29_init( &charger29, &charger29_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CHARGER29_ERROR == charger29_default_cfg ( &charger29 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically reads and logs the charging status once per second.

```c
void application_task ( void )
{
    static uint8_t chg_stat = 255;
    charger29_status_t status;
    if ( CHARGER29_OK == charger29_read_status ( &charger29, &status ) )
    {
        if ( chg_stat != ( status.stat0 & CHARGER29_STAT0_CHG_STAT_MASK ) )
        {
            chg_stat = ( status.stat0 & CHARGER29_STAT0_CHG_STAT_MASK );
            switch ( chg_stat )
            {
                case CHARGER29_STAT0_CHG_STAT_NOT_CHARGING:
                {
                    log_printf ( &logger, " Not Charging while charging is enabled\r\n\n" );
                    break;
                }
                case CHARGER29_STAT0_CHG_STAT_CC_CHARGING:
                {
                    log_printf ( &logger, " Constant Current Charging\r\n\n" );
                    break;
                }
                case CHARGER29_STAT0_CHG_STAT_CV_CHARGING:
                {
                    log_printf ( &logger, " Constant Voltage Charging\r\n\n" );
                    break;
                }
                case CHARGER29_STAT0_CHG_STAT_CHARGE_DONE:
                {
                    log_printf ( &logger, " Charge Done or charging is disabled\r\n\n" );
                    break;
                }
                default:
                {
                    log_printf ( &logger, " Unknown Charging Status\r\n\n" );
                    break;
                }
            }
        }
    }
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
