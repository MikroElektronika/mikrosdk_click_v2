
---
# DIGI Isolator 4 Click

> [DIGI Isolator 4 Click](https://www.mikroe.com/?pid_product=MIKROE-7029) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7029&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Jun 2026.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the DIGI Isolator 4 Click board by
reading and displaying the state of two isolated digital input channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIIsolator4

### Example Key Functions

- `digiisolator4_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void digiisolator4_cfg_setup ( digiisolator4_cfg_t *cfg );
```

- `digiisolator4_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t digiisolator4_init ( digiisolator4_t *ctx, digiisolator4_cfg_t *cfg );
```

- `digiisolator4_enable_output` This function enables isolator outputs by setting the EN pin to high logic state.
```c
void digiisolator4_enable_output ( digiisolator4_t *ctx );
```

- `digiisolator4_disable_output` This function disables isolator outputs by setting the EN pin to low logic state.
```c
void digiisolator4_disable_output ( digiisolator4_t *ctx );
```

- `digiisolator4_get_in1_pin` This function returns the IN1 pin logic state.
```c
uint8_t digiisolator4_get_in1_pin ( digiisolator4_t *ctx );
```

- `digiisolator4_read_inputs` This function reads the state of both input channels and stores the result.
```c
err_t digiisolator4_read_inputs ( digiisolator4_t *ctx, digiisolator4_inputs_t *data_out );
```

### Application Init

> Initializes the driver and enables outputs.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digiisolator4_cfg_t digiisolator4_cfg;  /**< Click config object. */

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
    digiisolator4_cfg_setup( &digiisolator4_cfg );
    DIGIISOLATOR4_MAP_MIKROBUS( digiisolator4_cfg, MIKROBUS_POSITION_DIGIISOLATOR4 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == digiisolator4_init( &digiisolator4, &digiisolator4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    digiisolator4_enable_output( &digiisolator4 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the state of both isolated digital input channels and displays
the results on the USB UART every 500ms.

```c
void application_task ( void ) 
{
    digiisolator4_inputs_t input_data;

    if ( DIGIISOLATOR4_OK == digiisolator4_read_inputs( &digiisolator4, &input_data ) )
    {
        log_printf( &logger, " IN1: %u\r\n", ( uint16_t ) input_data.in1_state );
        log_printf( &logger, " IN2: %u\r\n\n", ( uint16_t ) input_data.in2_state );
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
