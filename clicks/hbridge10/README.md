
---
# H-Bridge 10 Click

> [H-Bridge 10 Click](https://www.mikroe.com/?pid_product=MIKROE-5108) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5108&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the H-Bridge 10 Click board by driving the motors connected between OUT1-OUT2 and OUT2-OUT3 in both directions. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge10

### Example Key Functions

- `hbridge10_cfg_setup` Config Object Initialization function.
```c
void hbridge10_cfg_setup ( hbridge10_cfg_t *cfg );
```

- `hbridge10_init` Initialization function.
```c
err_t hbridge10_init ( hbridge10_t *ctx, hbridge10_cfg_t *cfg );
```

- `hbridge10_default_cfg` Click Default Configuration function.
```c
err_t hbridge10_default_cfg ( hbridge10_t *ctx );
```

- `hbridge10_set_output_state` This function sets the output channel state.
```c
err_t hbridge10_set_output_state ( hbridge10_t *ctx, uint8_t channel, uint8_t state );
```

- `hbridge10_get_status` This function reads the status of output register.
```c
err_t hbridge10_get_status ( hbridge10_t *ctx, uint16_t *status );
```

- `hbridge10_get_fault_pin` This function returns the fault (FLT) pin logic state.
```c
uint8_t hbridge10_get_fault_pin ( hbridge10_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge10_cfg_t hbridge10_cfg;  /**< Click config object. */

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
    hbridge10_cfg_setup( &hbridge10_cfg );
    HBRIDGE10_MAP_MIKROBUS( hbridge10_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hbridge10_init( &hbridge10, &hbridge10_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE10_ERROR == hbridge10_default_cfg ( &hbridge10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motors connected between OUT1-OUT2 and OUT2-OUT3 in both directions in the span of 6 seconds, and displays the status messages on the USB UART.

```c
void application_task ( void )
{
    uint16_t status;
    if ( ( HBRIDGE10_OK == hbridge10_set_output_state ( &hbridge10, HBRIDGE10_CHANNEL_OUT1, HBRIDGE10_OUT_HIGH ) ) && 
         ( HBRIDGE10_OK == hbridge10_set_output_state ( &hbridge10, HBRIDGE10_CHANNEL_OUT2, HBRIDGE10_OUT_LOW ) ) && 
         ( HBRIDGE10_OK == hbridge10_set_output_state ( &hbridge10, HBRIDGE10_CHANNEL_OUT3, HBRIDGE10_OUT_HIGH ) ) )
    {
        Delay_ms ( 100 );
        if ( HBRIDGE10_OK == hbridge10_get_status ( &hbridge10, &status ) )
        {
            hbridge10_display_status ( status );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
    }
    if ( ( HBRIDGE10_OK == hbridge10_set_output_state ( &hbridge10, HBRIDGE10_CHANNEL_OUT1, HBRIDGE10_OUT_LOW ) ) && 
         ( HBRIDGE10_OK == hbridge10_set_output_state ( &hbridge10, HBRIDGE10_CHANNEL_OUT2, HBRIDGE10_OUT_HIGH ) ) && 
         ( HBRIDGE10_OK == hbridge10_set_output_state ( &hbridge10, HBRIDGE10_CHANNEL_OUT3, HBRIDGE10_OUT_LOW ) ) )
    {
        Delay_ms ( 100 );
        if ( HBRIDGE10_OK == hbridge10_get_status ( &hbridge10, &status ) )
        {
            hbridge10_display_status ( status );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
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
