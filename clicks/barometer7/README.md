
---
# Barometer 7 Click

> [Barometer 7 Click](https://www.mikroe.com/?pid_product=MIKROE-4913) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4913&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains API for Barometer 7 Click driver.
> The demo application reads and calculate temperature and pressure data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer7

### Example Key Functions

- `barometer7_cfg_setup` Config Object Initialization function.
```c
void barometer7_cfg_setup ( barometer7_cfg_t *cfg );
```

- `barometer7_init` Initialization function.
```c
err_t barometer7_init ( barometer7_t *ctx, barometer7_cfg_t *cfg );
```

- `barometer7_default_cfg` Click Default Configuration function.
```c
err_t barometer7_default_cfg ( barometer7_t *ctx );
```

- `barometer7_get_pressure` Barometer 7 get pressure function.
```c
err_t barometer7_get_pressure ( barometer7_t *ctx, float *pressure );
```

- `barometer7_get_temperature` Barometer 7 get temperature function.
```c
err_t barometer7_get_temperature ( barometer7_t *ctx, float *temperature );
```

### Application Init

> Initializes SPI driver and log UART.
> After driver initialization the app set default settings 
> and display sensor identifier data.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer7_cfg_t barometer7_cfg;  /**< Click config object. */

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
    barometer7_cfg_setup( &barometer7_cfg );
    BAROMETER7_MAP_MIKROBUS( barometer7_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == barometer7_init( &barometer7, &barometer7_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    BAROMETER7_SET_DATA_SAMPLE_EDGE;
    
    if ( BAROMETER7_ERROR == barometer7_default_cfg ( &barometer7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );;
    
    static barometer7_identifier_t id_data;
    barometer7_get_identifier ( &barometer7, &id_data );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " > Supplier         : %d <\r\n", ( uint16_t ) id_data.supplier );
    log_printf( &logger, " > Silicon Version  : %d <\r\n", ( uint16_t ) id_data.silicon_version );
    log_printf( &logger, " > Metal Version    : %d <\r\n", ( uint16_t ) id_data.metal_version );
    log_printf( &logger, " > ASCI Name        : %c <\r\n", id_data.asic_name );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> This is an example that demonstrates the use of the Barometer 7 Click board&trade;.
> In this example, display the Pressure ( mBar ) and Temperature ( degree Celsius ) data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void )
{
    static float pressure; 
    static float temperature;
    
    barometer7_get_pressure( &barometer7, &pressure );
    if ( BAROMETER7_NO_ERROR != barometer7.diagnosis )
    {
        display_error( );
    }
    log_printf( &logger, " Pressure     : %.0f mbar\r\n", pressure );
    
    barometer7_get_temperature( &barometer7, &temperature );
    if ( BAROMETER7_NO_ERROR != barometer7.diagnosis )
    {
        display_error( );   
    }
    log_printf( &logger, " Temperature  : %.2f C\r\n", temperature );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

## Additional Function

- `display_error` This function displays diagnosis error messages.
```c
static void display_error ( void );
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
