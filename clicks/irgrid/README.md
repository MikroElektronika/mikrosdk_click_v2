
---
# IR Grid Click

> [IR Grid Click](https://www.mikroe.com/?pid_product=MIKROE-2622) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2622&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> IR Grid Click is a thermal imaging sensor. It has an array of 64 very sensitive factory 
> calibrated IR elements (pixels), arranged in 4 rows of 16 pixels, each measuring an 
> object temperature up to 300˚C. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IrGrid

### Example Key Functions

- `irgrid_cfg_setup` Config Object Initialization function. 
```c
void irgrid_cfg_setup ( irgrid_cfg_t *cfg );
``` 
 
- `irgrid_init` Initialization function. 
```c
err_t irgrid_init ( irgrid_t *ctx, irgrid_cfg_t *cfg );
```

- Measures temperature and places it inside internal buffers. This function is 
- `irgrid_measure` needed to be called prior to `irgrid_get_ir_raw` or `irgrid_get_temperature`. 
```c
uint8_t irgrid_measure ( irgrid_t *ctx, irgrid_data_t *data_str );
```
 
- `irgrid_get_temperature` Populates provided buffer with calculated temperatures. Buffer must have at least 64 members. 
```c
void irgrid_get_temperature ( irgrid_data_t *data_str, float *buffer );
```

- `irgrid_read_eeprom` Read function using EEPROM slave adress. 
```c
void irgrid_read_eeprom ( irgrid_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

### Application Init

> Initializes driver init and IR Grid module

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irgrid_cfg_t irgrid_cfg;  /**< Click config object. */

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
    irgrid_cfg_setup( &irgrid_cfg );
    IRGRID_MAP_MIKROBUS( irgrid_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == irgrid_init( &irgrid, &irgrid_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    irgrid_device_init( &irgrid, &irgrid_data, 16 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature of all pixels and creates a pixel temperature matrix that logs 
> on usbuart every half of second

```c
void application_task ( void )
{    
    if ( 1 != irgrid_measure( &irgrid, &irgrid_data ) )
    {
        irgrid_get_temperature( &irgrid_data, &ir_tmp[ 0 ] );
    }

    for ( rc = 0; rc < 4; rc++ )
    {
        for ( cc = 0; cc < 16; cc++ )
        {
            i = ( cc * 4 ) + rc;
            log_printf( &logger, "%.3f    ", ir_tmp[ i ] );
        }
        log_printf( &logger, "\r\n" );
        Delay_ms ( 100 );
    }
    
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "\r\n" );
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
