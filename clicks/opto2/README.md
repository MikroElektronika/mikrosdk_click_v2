
---
# Opto 2 Click

> [Opto 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3015) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3015&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application used to provide an optical isolation of sensitive microcontroller. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Opto2

### Example Key Functions

- `opto2_cfg_setup` Config Object Initialization function. 
```c
void opto2_cfg_setup ( opto2_cfg_t *cfg );
``` 
 
- `opto2_init` Initialization function. 
```c
err_t opto2_init ( opto2_t *ctx, opto2_cfg_t *cfg );
```

- `opto2_check_out1` OUT1 Check function. 
```c
uint8_t opto2_check_out1 ( opto2_t *ctx );
```
 
- `opto2_check_out2` OUT2 Check function. 
```c
uint8_t opto2_check_out2 ( opto2_t *ctx );
```

- `opto2_check_out3` OUT3 Check function. 
```c
uint8_t opto2_check_out3 ( opto2_t *ctx );
```

### Application Init

> Initializes device selects the outputs (OUT1 - OUT4) which state be checked. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    opto2_cfg_t cfg;

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

    opto2_cfg_setup( &cfg );
    OPTO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    opto2_init( &opto2, &cfg );

    log_info( &logger, "---- Application Init ----" );

    opto2_set_logger( 1, 1, 0, 0 );
    log_printf( &logger, "OPTO 2 is initialized \r\n" );
    log_printf( &logger, "" );
    Delay_ms ( 200 );
}
```

### Application Task

> Performs the check procedure for selected outputs and logs the states from that
  outputs on USB UART. Repeat the check procedure every 2 seconds.

```c
void application_task ( void )
{
    tmp = 1;

    for ( cnt = 0; cnt < 4; cnt++ )
    {
        switch ( sel_output & tmp )
        {
            case 0x01 :
            {
                check_output = opto2_check_out1( &opto2 );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT1 is low %d\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT1 is high %d\r\n" );
                }
                break;
            }
            case 0x02 :
            {
                check_output = opto2_check_out2( &opto2 );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT2 is low %d\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT2 is high %d\r\n" );
                }
                break;
            }
            case 0x04 :
            {
                check_output = opto2_check_out3( &opto2 );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT3 is low %d\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT3 is high %d\r\n" );
                }
                break;
            }
            case 0x08 :
            {
                check_output = opto2_check_out4( &opto2 );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT4 is low %d\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT4 is high %d\r\n" );
                }
                break;
            }
            default :
            {
                break;
            }
        }

    tmp <<= 1;
    }

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
