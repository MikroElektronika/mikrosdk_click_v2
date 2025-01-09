
---
# GNSS MAX Click

> [GNSS MAX Click](https://www.mikroe.com/?pid_product=MIKROE-4643) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4643&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This example showcases device abillity to read data outputed 
from device and show it's coordinates and altitude when connected.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GNSSMAX

### Example Key Functions

- `gnssmax_cfg_setup` Config Object Initialization function.
```c
void gnssmax_cfg_setup ( gnssmax_cfg_t *cfg );
```

- `gnssmax_init` Initialization function.
```c
err_t gnssmax_init ( gnssmax_t *ctx, gnssmax_cfg_t *cfg );
```

- `gnssmax_default_cfg` Click Default Configuration function.
```c
err_t gnssmax_default_cfg ( gnssmax_t *ctx );
```

- `gnssmax_generic_read` GNSS MAX data reading function.
```c
err_t gnssmax_generic_read ( gnssmax_t *ctx, char *data_buf, uint16_t max_len );
```

- `gnssmax_reset` GNSS MAX reset function.
```c
void gnssmax_reset ( gnssmax_t *ctx );
```

- `gnssmax_get_pps` GNSS MAX reads timestamp pin state.
```c
uint8_t gnssmax_get_pps ( gnssmax_t *ctx );
```

### Application Init

> Initializes host communication modules, additioaln GPIO's used 
for control of device and resets device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnssmax_cfg_t gnssmax_cfg;  /**< Click config object. */

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
    Delay_ms ( 500 );

    // Click initialization.
    gnssmax_cfg_setup( &gnssmax_cfg );
    GNSSMAX_MAP_MIKROBUS( gnssmax_cfg, MIKROBUS_1 );
    err_t init_flag  = gnssmax_init( &gnssmax, &gnssmax_cfg );
    if ( init_flag == UART_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    gnssmax_default_cfg( &gnssmax );
    
    last_error_flag = GNSSMAX_OK;
    log_info( &logger, " Application Task " );
    Delay_ms ( 500 );
}
```

### Application Task

> Reads data from device and wait's untill device is connected. 
While not connected it will log '.'. When conneceted and received 
data for latitude, longitude, and altitude it will log that data 
parsed from "GNGGA" command.

```c
void application_task ( void ) 
{
    gnssmax_process();
    
    err_t error_flag = gnssmax_element_parser( RSP_GNGGA, RSP_GNGGA_LATITUDE_ELEMENT, 
                                             latitude_data );
    
    error_flag |= gnssmax_element_parser(  RSP_GNGGA, RSP_GNGGA_LONGITUDE_ELEMENT, 
                                         longitude_data );
    
    error_flag |= gnssmax_element_parser(  RSP_GNGGA, RSP_GNGGA_ALTITUDE_ELEMENT, 
                                         altitude_data );
    
    
    if ( error_flag == GNSSMAX_OK )
    {
        if ( last_error_flag != GNSSMAX_OK )
        {
            log_printf( &logger, "\r\n" );
        }
        log_printf( &logger, ">Latitude:\r\n - deg: %.2s \r\n - min: %s\r\n", 
                    latitude_data, &latitude_data[ 2 ] );
        
        log_printf( &logger, ">Longitude:\r\n - deg: %.3s \r\n - min: %s\r\n", 
                    longitude_data, &longitude_data[ 3 ] );
        
        log_printf( &logger, ">Altitude:\r\n - %sm\r\n", 
                    altitude_data );
        
        log_printf( &logger, "----------------------------------------\r\n" );
    }
    else if ( error_flag < GNSSMAX_ERROR )
    {
        if ( last_error_flag == GNSSMAX_OK )
        {
            log_printf( &logger, "Waiting for data " );
        }
        log_printf( &logger, "." );
    }
    
    if ( error_flag != GNSSMAX_ERROR )
    {
        last_error_flag = error_flag;
        gnssmax_clear_app_buf(  );
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
