
---
# 3D Hall Click

> [3D Hall Click](https://www.mikroe.com/?pid_product=MIKROE-1987) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1987&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This application use to determine angle position.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.3DHall

### Example Key Functions

- `c3dhall_cfg_setup` Config Object Initialization function. 
```c
void c3dhall_cfg_setup ( c3dhall_cfg_t *cfg );
``` 
 
- `c3dhall_init` Initialization function. 
```c
err_t c3dhall_init ( c3dhall_t *ctx, c3dhall_cfg_t *cfg );
```

- `c3dhall_read_all_data` Read 8 bytes data from sensor function. 
```c
void c3dhall_read_all_data ( c3dhall_t *ctx, c3dhall_all_data_t *all_data );
```
 
- `c3dhall_calculate_angle` Calculate angle function. 
```c
uint8_t c3dhall_calculate_angle ( c3dhall_t *ctx, uint16_t data_angle );
```

### Application Init

> Initialization driver enable's - SPI and start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c3dhall_cfg_t cfg;
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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c3dhall_cfg_setup( &cfg );
    C3DHALL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall_init( &c3dhall, &cfg );
    Delay_100ms( );
}
```

### Application Task

> This is a example which demonstrates the use of 3D Hall Click board. 
> 3D Hall Click communicates with register via SPI by read data from register and calculate Alpha and Beta angle position. 
> Results are being sent to the Usart Terminal where you can track their changes. All data logs on usb uart.

```c
void application_task ( void )
{
    c3dhall_all_data_t all_data;

    uint8_t angle_alpha;
    uint8_t angle_beta;

    c3dhall_read_all_data( &c3dhall, &all_data );
    Delay_100ms( );

    if ( ( all_data.data_error ) == C3DHALL_NO_ERRORS )
    {
        angle_alpha = c3dhall_calculate_angle( &c3dhall, all_data.data_angle_a );
        angle_beta = c3dhall_calculate_angle( &c3dhall, all_data.data_angle_b );
        
        log_printf( &logger, "     Alpha : %u\r\n", ( uint16_t ) angle_alpha );

        log_printf( &logger, "     Beta  : %u\r\n", ( uint16_t ) angle_beta );

        log_printf( &logger, "-------------------------\r\n", angle_beta );
    }
    else
    {
        if ( all_data.data_error == C3DHALL_F_ADCMONITOR )
            log_printf( &logger, "       ADC Failure       \r\n" );
        else if ( all_data.data_error == C3DHALL_F_ADCSATURA )
            log_printf( &logger, "    Electrical failure   \r\n"  );
        else if ( all_data.data_error == C3DHALL_F_GAINTOOLOW )
            log_printf( &logger, "    Gain code is less    \r\n" );
        else if ( all_data.data_error == C3DHALL_F_GAINTOOHIGH )
            log_printf( &logger, "   Gain code is greater  \r\n" );
        else if ( all_data.data_error == C3DHALL_F_NORMTOOLOW )
            log_printf( &logger, "   Fast norm below 30   \r\n" );
        else if ( all_data.data_error == C3DHALL_F_FIELDTOOLOW )
            log_printf( &logger, "     The norm is less    \r\n" );
        else if ( all_data.data_error == C3DHALL_F_FIELDTOOHIGH )
            log_printf( &logger, "   The norm is greater   \r\n" );
        else if ( all_data.data_error == C3DHALL_F_ROCLAMP )
            log_printf( &logger, "  Analog Chain Rough off \r\n" );
        else if ( all_data.data_error == C3DHALL_F_DEADZONEALPHA )
            log_printf( &logger, " Angle ALPHA in deadzone \r\n" );
        else if ( all_data.data_error == C3DHALL_F_DEADZONEBETA )
            log_printf( &logger, "  Angle BETA in deadzone \r\n" );
        else if ( all_data.data_error == C3DHALL_MULTIPLE_ERRORS )
            log_printf( &logger, "   More than one error   \r\n" );
        else
            log_printf( &logger, "      Unknown error      \r\n" );

        log_printf( &logger, "-------------------------\r\n" );
        Delay_1sec( );
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
