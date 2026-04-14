
---
# WRLS 2.4GHz Click

> [WRLS 2.4GHz Click](https://www.mikroe.com/?pid_product=MIKROE-6915) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6915&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2026.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of WRLS 2.4GHz Click board by processing data from a connected BLE device.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.WRLS24GHz

### Example Key Functions

- `wrls24ghz_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void wrls24ghz_cfg_setup ( wrls24ghz_cfg_t *cfg );
```

- `wrls24ghz_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t wrls24ghz_init ( wrls24ghz_t *ctx, wrls24ghz_cfg_t *cfg );
```

- `wrls24ghz_reset_device` This function resets the device by toggling the RST pin state.
```c
void wrls24ghz_reset_device ( wrls24ghz_t *ctx );
```

- `wrls24ghz_get_status_pin` This function returns the connection active status (STATUS) pin logic state.
```c
uint8_t wrls24ghz_get_status_pin ( wrls24ghz_t *ctx );
```

- `wrls24ghz_send_cmd` This function sends a specified command to the Click module.
```c
void wrls24ghz_send_cmd ( wrls24ghz_t *ctx, uint8_t *cmd );
```

- `wrls24ghz_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t wrls24ghz_generic_read ( wrls24ghz_t *ctx, uint8_t *data_out, uint16_t len );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    wrls24ghz_cfg_t wrls24ghz_cfg;  /**< Click config object. */

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
    wrls24ghz_cfg_setup( &wrls24ghz_cfg );
    WRLS24GHZ_MAP_MIKROBUS( wrls24ghz_cfg, MIKROBUS_1 );
    if ( UART_ERROR == wrls24ghz_init( &wrls24ghz, &wrls24ghz_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = WRLS24GHZ_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - WRLS24GHZ_POWER_UP:
   > Powers up the device, reads software version, and restores factory settings.
 - WRLS24GHZ_CONFIG_EXAMPLE:
   > Sets sleep timeout and BT device name, and reads the BT address.
 - WRLS24GHZ_EXAMPLE:
   > Performs a BT terminal example by processing all data from a connected BLE device and sending back an adequate response messages.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case WRLS24GHZ_POWER_UP:
        {
            if ( WRLS24GHZ_OK == wrls24ghz_power_up( &wrls24ghz ) )
            {
                app_state = WRLS24GHZ_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case WRLS24GHZ_CONFIG_EXAMPLE:
        {
            if ( WRLS24GHZ_OK == wrls24ghz_config_example( &wrls24ghz ) )
            {
                app_state = WRLS24GHZ_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case WRLS24GHZ_EXAMPLE:
        {
            wrls24ghz_example( &wrls24ghz );
            break;
        }
        default:
        {
            log_error( &logger, " APP STATE." );
            break;
        }
    }
}
```

### Note

> We have used the Serial Bluetooth Terminal smartphone application for the test.

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
