
---
# UV 4 Click

> [UV 4 Click](https://www.mikroe.com/?pid_product=MIKROE-2989) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2989&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> Reads all configured measurements from selected channels and logs results every 500ms.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UV4

### Example Key Functions

- `uv4_cfg_setup` Config Object Initialization function. 
```c
void uv4_cfg_setup ( uv4_cfg_t *cfg );
``` 
 
- `uv4_init` Initialization function. 
```c
err_t uv4_init ( uv4_t *ctx, uv4_cfg_t *cfg );
```

- `uv4_default_cfg` Click Default Configuration function. 
```c
void uv4_default_cfg ( uv4_t *ctx );
```

- `uv4_write_reg` This function write one byte of data to given address. 
```c
err_t uv4_write_reg ( uv4_t* ctx, const uint8_t reg_address, const uint8_t transfer_data );
```
 
- `uv4_read_reg` This function reads determined number of bytes from given address. 
```c
err_t uv4_read_reg ( uv4_t* ctx, uint8_t reg_address, uint8_t* data_out, uint8_t inc_en, uint8_t n_bytes );
```

- `uv4_write_param_data` This function writes one byte of data in parameter table. 
```c
err_t uv4_write_param_data ( uv4_t* ctx, uint8_t param_address, uint8_t transfer_data );
```

### Application Init

> Initializes driver, performs reset command and enables selected channels.
 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    uv4_cfg_t cfg;

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

    uv4_cfg_setup( &cfg );
    UV4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uv4_init( &uv4, &cfg );
    uv4_default_cfg( &uv4 );
}
```

### Application Task

> Reads all configured measurements from selected channels and logs results every 500ms.

```c
void application_task ( void )
{
    uint8_t cnt;
    uint8_t pom = 1;
    uint32_t data_r[ 6 ];
    
    uv4_read_measurements( &uv4, &data_r[ 0 ] );
    
    for ( cnt = 0; cnt < 6; cnt++ )
    {
        if ( uv4.config_byte & pom )
        {
            switch ( uv4.optical_data[ cnt ] )
            {
                case UV4_OPT_FUNC_SMALL_IR:
                {
                    log_printf( &logger, "Small IR: " );
                    break;
                }
                case UV4_OPT_FUNC_MEDIUM_IR:
                {
                    log_printf( &logger, "Medium IR: " );
                    break;
                }
                case UV4_OPT_FUNC_LARGE_IR:
                {
                    log_printf( &logger, "Large IR: " );
                    break;
                }
                case UV4_OPT_FUNC_WHITE:
                {
                    log_printf( &logger, "White : " );
                    break;
                }
                case UV4_OPT_FUNC_LARGE_WHITE:
                {
                    log_printf( &logger, "Large White: " );
                    break;
                }
                case UV4_OPT_FUNC_UV:
                {
                    log_printf( &logger, "UV: " );
                    break;
                }
                case UV4_OPT_FUNC_UV_DEEP:
                {
                    log_printf( &logger, "UV-Deep: " );
                    break;
                }
                default:
                {
                    break;
                }
            }
            log_printf( &logger, "%d\r\n", data_r[ cnt ] );
        }
        pom <<= 1;
    }
    Delay_ms ( 500 );
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
