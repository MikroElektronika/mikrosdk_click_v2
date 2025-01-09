
---
# Color 14 Click

> [Color 14 Click](https://www.mikroe.com/?pid_product=MIKROE-4793) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4793&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This application showcases ability of Click board to read RGB and IR data
from device. Also it can be configured to read proximity data and
ALS data in lux units.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Color14

### Example Key Functions

- `color14_cfg_setup` Config Object Initialization function.
```c
void color14_cfg_setup ( color14_cfg_t *cfg );
```

- `color14_init` Initialization function.
```c
err_t color14_init ( color14_t *ctx, color14_cfg_t *cfg );
```

- `color14_get_rgb_ir` Read color data from device.
```c
err_t color14_get_rgb_ir ( color14_t *ctx, color14_color_t *color_data );
```

- `color14_get_als` Read lux data from device.
```c
err_t color14_get_als ( color14_t *ctx, float *als_data );
```

- `color14_get_proximity` Read proximity data from device.
```c
err_t color14_get_proximity ( color14_t *ctx, uint16_t *ps_data );
```

### Application Init

> ## Application Init
Initialization of host communication modules (UART, I2C) and additonal pin.
Read and check device ID, selects example and configures device for it.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color14_cfg_t color14_cfg;  /**< Click config object. */

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
    color14_cfg_setup( &color14_cfg );
    COLOR14_MAP_MIKROBUS( color14_cfg, MIKROBUS_1 );
    err_t init_flag = color14_init( &color14, &color14_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    uint8_t temp_data = 0;
    init_flag = color14_generic_read( &color14, COLOR14_REG_PART_ID, &temp_data, 1 );
    log_printf( &logger, " > ID: 0x%.2X\r\n", ( uint16_t )temp_data );
    
    if ( ( COLOR14_OK != init_flag ) && ( COLOR14_ID != temp_data ) )
    {
        log_error( &logger, " ID" );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    //Select example
    example_type = COLOR14_EXAMPLE_RGB;
    color14_generic_write( &color14, COLOR14_REG_MAIN_CTRL, &example_type, 1 );
    
    if ( COLOR14_EXAMPLE_PS_LS == example_type )
    {
        //Configure proximity data to 11 bit
        color14_generic_read( &color14, COLOR14_REG_PS_MEASRATE, &temp_data, 1 );
        temp_data |= 0x18;
        color14_generic_write( &color14, COLOR14_REG_PS_MEASRATE, &temp_data, 1 );
    }
    
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Depending of selected example in task proximity and als data will be read from
device, or it will show ADC value for red, green, blue and ir data from device.

```c
void application_task ( void ) 
{
    switch ( example_type )
    {
        case COLOR14_EXAMPLE_PS_LS:
        {
            color14_proximity_als_example( );
            break;
        }
        case COLOR14_EXAMPLE_RGB:
        {
            color14_rgb_example( );
            break;
        }
        default:
        {
            log_error( &logger, " Select example!" );
            break;
        }
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
