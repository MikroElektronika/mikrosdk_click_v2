
---
# DIGI Isolator 2 Click

> [DIGI Isolator 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5981) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5981&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of DIGI Isolator 2 Click board by reading and displaying the state of 8 digital input channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIIsolator2

### Example Key Functions

- `digiisolator2_cfg_setup` Config Object Initialization function.
```c
void digiisolator2_cfg_setup ( digiisolator2_cfg_t *cfg );
```

- `digiisolator2_init` Initialization function.
```c
err_t digiisolator2_init ( digiisolator2_t *ctx, digiisolator2_cfg_t *cfg );
```

- `digiisolator2_default_cfg` Click Default Configuration function.
```c
err_t digiisolator2_default_cfg ( digiisolator2_t *ctx );
```

- `digiisolator2_enable_output` This function enables output by setting the EN pin to high state.
```c
void digiisolator2_enable_output ( digiisolator2_t *ctx );
```

- `digiisolator2_disable_output` This function disables output by setting the EN pin to low state.
```c
void digiisolator2_disable_output ( digiisolator2_t *ctx );
```

- `digiisolator2_read_inputs` This function reads all inputs state via the selected driver interface.
```c
err_t digiisolator2_read_inputs ( digiisolator2_t *ctx, uint8_t *data_out );
```

### Application Init

> Initializes the driver and enables isolator outputs.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digiisolator2_cfg_t digiisolator2_cfg;  /**< Click config object. */

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
    digiisolator2_cfg_setup( &digiisolator2_cfg );
    DIGIISOLATOR2_MAP_MIKROBUS( digiisolator2_cfg, MIKROBUS_1 );
    if ( DIGIISOLATOR2_OK != digiisolator2_init( &digiisolator2, &digiisolator2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    digiisolator2_enable_output( &digiisolator2 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the state of 8 digital input channels in hex format where MSB represents IN8 and LSB the channel IN1. The results are displayed on the USB UART every 500ms.

```c
void application_task ( void )
{
    uint8_t input_data = 0;
    if ( DIGIISOLATOR2_OK == digiisolator2_read_inputs ( &digiisolator2, &input_data ) )
    {
        log_printf( &logger, " INPUT: 0x%.2X\r\n\n", ( uint16_t ) input_data );
        Delay_ms ( 500 );
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
