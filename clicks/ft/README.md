
---
# FT Click

> [FT Click](https://www.mikroe.com/?pid_product=MIKROE-3929) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3929&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of an FT Click board by showing the communication between the two Click boards.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ft

### Example Key Functions

- `ft_cfg_setup` Config Object Initialization function.
```c
void ft_cfg_setup ( ft_cfg_t *cfg ); 
```

- `ft_init` Initialization function.
```c
err_t ft_init ( ft_t *ctx, ft_cfg_t *cfg );
```

- `ft_get_data_status` Use this function to get current status of data
```c
uint8_t ft_get_data_status ( ft_t *ctx );
```

- `ft_get_data` Use this function to read received data
```c
uint16_t ft_get_data ( ft_t *ctx, uint8_t *data_buf );
```

- `ft_send_package` Use this function to send data to other module
```c
void ft_send_package ( ft_t *ctx, uint8_t *data_buf, uint16_t len, uint8_t queue );
```

### Application Init

> Initalizes device and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ft_cfg_t ft_cfg;

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
    ft_cfg_setup( &ft_cfg );
    FT_MAP_MIKROBUS( ft_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ft_init( &ft, &ft_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Depending on the selected application mode, it reads all the received data or sends the desired text message once per second.

```c
void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    ft_send_package( &ft, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ), 1 );
    log_printf( &logger, " Sent data: %s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms ( 1000 );
#else
    uint8_t rsp_data_buf[ FT_MAX_DATA_BUFFER ] = { 0 };
    uint8_t rx_byte = 0;
    if ( 1 == ft_generic_read( &ft, &rx_byte, 1 ) )
    {
        ft_isr_parser( &ft, rx_byte ); 
        if ( FT_NEW_DATA_AVAILABLE == ft_get_data_status( &ft ) )
        {
            if ( ft_get_data( &ft, rsp_data_buf ) )
            {
                log_printf( &logger, " Received data: %s", rsp_data_buf );
            }
        }
    }
#endif
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
