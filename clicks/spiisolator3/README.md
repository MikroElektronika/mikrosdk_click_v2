
---
# SPI Isolator 3 Click

> [SPI Isolator 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4651) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4651&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains API for the SPI Isolator 3 Click driver.
> This demo application shows an example of an SPI Isolator 3 Click wired 
> to the nvSRAM 4 Click for reading Device ID.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SpiIsolator3

### Example Key Functions

- `spiisolator3_cfg_setup` Config Object Initialization function.
```c
void spiisolator3_cfg_setup ( spiisolator3_cfg_t *cfg );
```

- `spiisolator3_init` Initialization function.
```c
err_t spiisolator3_init ( spiisolator3_t *ctx, spiisolator3_cfg_t *cfg );
```

- `spiisolator3_default_cfg` Click Default Configuration function.
```c
void spiisolator3_default_cfg ( spiisolator3_t *ctx );
```

- `spiisolator3_generic_write` SPI Isolator 3 data writing function.
```c
err_t spiisolator3_generic_write ( spiisolator3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );
```

- `spiisolator3_generic_read` SPI Isolator 3 data reading function.
```c
err_t spiisolator3_generic_read ( spiisolator3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );
```

- `spiisolator3_get_fault` SPI Isolator 3 get fault state function.
```c
uint8_t spiisolator3_get_fault ( spiisolator3_t *ctx );
```

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app sets the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                    /**< Logger config object. */
    spiisolator3_cfg_t spiisolator3_cfg;  /**< Click config object. */

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

    spiisolator3_cfg_setup( &spiisolator3_cfg );
    SPIISOLATOR3_MAP_MIKROBUS( spiisolator3_cfg, MIKROBUS_1 );
    err_t init_flag  = spiisolator3_init( &spiisolator3, &spiisolator3_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    spiisolator3_default_cfg ( &spiisolator3 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that shows the use of an SPI Isolator 3 Click board&trade;.
> Logs Device ID of the nvSRAM 4 Click wired to the SPI Isolator 3 board&trade;.  
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    get_device_id( );
    log_printf( &logger, " Device ID : 0x%.8LX\r\n", device_id ); 
    Delay_ms ( 1000 );
}
```

## Additional Function

- `get_device_id` Get Device ID function.
```c
void get_device_id ( void );
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
