
---
# Compass 6 Click

> [Compass 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4796) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4796&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example is a showcase the ability of the device
to read 3 axis data of magnetic raw value when data is ready.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Compass6

### Example Key Functions

- `compass6_cfg_setup` Config Object Initialization function.
```c
void compass6_cfg_setup ( compass6_cfg_t *cfg );
```

- `compass6_init` Initialization function.
```c
err_t compass6_init ( compass6_t *ctx, compass6_cfg_t *cfg );
```

- `compass6_default_cfg` Click Default Configuration function.
```c
err_t compass6_default_cfg ( compass6_t *ctx );
```

- `compass6_get_axes_data` Magnetic axes data reading.
```c
err_t compass6_get_axes_data ( compass6_t *ctx, compass6_axes_t *axes_data );
```

- `compass6_data_ready` Get data ready pin state.
```c
uint8_t compass6_data_ready ( compass6_t *ctx );
```

- `compass6_generic_read` Reading function.
```c
err_t compass6_generic_read ( compass6_t *ctx, uint8_t reg, uint8_t *rx_data );
```

### Application Init

> Initialization of communication modules (I2C, UART) and data 
ready pin as input. Then reads identification data and checks 
if some of them have wrong value, and configures device for reading.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    compass6_cfg_t compass6_cfg;  /**< Click config object. */

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
    compass6_cfg_setup( &compass6_cfg );
    COMPASS6_MAP_MIKROBUS( compass6_cfg, MIKROBUS_1 );
    err_t init_flag = compass6_init( &compass6, &compass6_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    uint8_t temp_data = 0;
    compass6_generic_read( &compass6, COMPASS6_REG_WHO_I_AM, &temp_data );
    log_printf( &logger, " > Who am I: 0x%.2X\r\n", ( uint16_t )temp_data );
    if ( COMPASS6_WHO_AM_I != temp_data )
    {
        log_error( &logger, " Who am I. " );
    }
    
    compass6_generic_read( &compass6, COMPASS6_REG_INFO_VERSION, &temp_data );
    log_printf( &logger, " > Version: 0x%.2X\r\n", ( uint16_t )temp_data );
    if ( COMPASS6_VERSION != temp_data )
    {
        log_error( &logger, " Version. " );
    }
    
    compass6_generic_read( &compass6, COMPASS6_REG_INFO_ALPS, &temp_data );
    log_printf( &logger, " > ALPS: 0x%.2X\r\n", ( uint16_t )temp_data );
    if ( COMPASS6_ALPS != temp_data )
    {
        log_error( &logger, " ALPS. " );
    }

    compass6_default_cfg ( &compass6 );
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Application Task

> Checks Data ready pin and if asserted high it will read data of all
3 axes(x, y, z) and log data to Terminal.

```c
void application_task ( void ) 
{
    if ( compass6_data_ready( &compass6 ) )
    {      
        compass6_axes_t axes_data;
        compass6_get_axes_data( &compass6, &axes_data );
        log_printf( &logger, " > X: %d\r\n", axes_data.x );
        log_printf( &logger, " > Y: %d\r\n", axes_data.y );
        log_printf( &logger, " > Z: %d\r\n", axes_data.z );
        log_printf( &logger, "*********************\r\n" );
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
