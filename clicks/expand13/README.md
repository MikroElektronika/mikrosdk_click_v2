
---
# Expand 13 Click

> [Expand 13 Click](https://www.mikroe.com/?pid_product=MIKROE-4887) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4887&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Expand 13 Click board, by writing data to all six ports and then reading back the status of the ports. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand13

### Example Key Functions

- `expand13_cfg_setup` Config Object Initialization function.
```c
void expand13_cfg_setup ( expand13_cfg_t *cfg );
```

- `expand13_init` Initialization function.
```c
err_t expand13_init ( expand13_t *ctx, expand13_cfg_t *cfg );
```

- `expand13_enable_device` This function enables the device by setting the RST pin to high logic state.
```c
void expand13_enable_device ( expand13_t *ctx );
```

- `expand13_write_all_ports` This function writes a desired data to all 6 ports.
```c
err_t expand13_write_all_ports ( expand13_t *ctx, uint8_t *ports );
```

- `expand13_read_all_ports` This function reads the state of all 6 ports.
```c
err_t expand13_read_all_ports ( expand13_t *ctx, uint8_t *ports );
```

### Application Init

> Initializes the driver and enables the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand13_cfg_t expand13_cfg;  /**< Click config object. */

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
    expand13_cfg_setup( &expand13_cfg );
    EXPAND13_MAP_MIKROBUS( expand13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand13_init( &expand13, &expand13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    expand13_enable_device ( &expand13 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Sets the pins of all ports and then reads and displays their status on the USB UART approximately once per second.

```c
void application_task ( void )
{
    uint8_t port_value[ 6 ] = { 0 };
    uint16_t pin_num = 0;
  
    for ( pin_num = EXPAND13_PIN_0_MASK; pin_num <= EXPAND13_PIN_7_MASK; pin_num <<= 1 )
    {
        if ( !expand13_get_int_pin ( &expand13 ) )
        {
            log_printf( &logger, " External input has occurred.\r\n" );
        }
        
        memset ( port_value, pin_num, 6 );
        expand13_write_all_ports( &expand13, port_value );
        
        expand13_read_all_ports( &expand13, port_value );
        for ( uint8_t cnt = EXPAND13_PORT_0; cnt <= EXPAND13_PORT_5; cnt++ )
        {
            log_printf( &logger, " Status port %d : 0x%.2X\r\n", ( uint16_t ) cnt, ( uint16_t ) port_value[ cnt ] );
        }
        log_printf( &logger, "\n" );
        Delay_ms ( 1000 );
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
