
---
# OPTO Click

> [OPTO Click](https://www.mikroe.com/?pid_product=MIKROE-1196) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1196&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example checks the state of selected inputs and prints it.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.OPTO

### Example Key Functions

- `opto_cfg_setup` Config Object Initialization function. 
```c
void opto_cfg_setup ( opto_cfg_t *cfg );
``` 
 
- `opto_init` Initialization function. 
```c
err_t opto_init ( opto_t *ctx, opto_cfg_t *cfg );
```

- `opto_default_cfg` Click Default Configuration function. 
```c
void opto_default_cfg ( opto_t *ctx );
```

- `opto_check_out1` Function checks the state of OUT1 pin. 
```c
uint8_t opto_check_out1 ( opto_t *ctx );
```
 
- `opto_check_out2` Function checks the state of OUT2 pin. 
```c
uint8_t opto_check_out2 ( opto_t *ctx );
```

- `opto_check_out3` Function checks the state of OUT3 pin. 
```c
uint8_t opto_check_out3 ( opto_t *ctx );
```

- `opto_check_out4` Function checks the state of OUT4 pin. 
```c
uint8_t opto_check_out4 ( opto_t *ctx );
```

### Application Init

> Initialization driver enables GPIO and also starts write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    opto_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    opto_cfg_setup( &cfg );
    OPTO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    opto_init( &opto, &cfg );
    opto_set_logger(1,1,1,1);
}
```

### Application Task

> This example demonstrates the use of OPTO Click board by performing
> the check procedure for selected outputs and displays the results on USART terminal.

```c
void application_task ( void )
{
    tmp = 1;

    for( cnt = 0; cnt < 4; cnt++ )
    {
        switch ( sel_output & tmp )
        {
            case 0x01 :
            {
                check_output = opto_check_out1( &opto );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT1 is low\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT1 is high\r\n" );
                }
            break;
            }
            case 0x02 :
            {
                check_output = opto_check_out2( &opto );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT2 is low\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT2 is high\r\n" );
                }
            break;
            }
            case 0x04 :
            {
                check_output = opto_check_out3( &opto );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT3 is low\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT3 is high\r\n" );
                }
            break;
            }
            case 0x08 :
            {
                check_output = opto_check_out4( &opto );

                if ( check_output == 0 )
                {
                    log_printf( &logger, "OUT4 is low\r\n" );
                }
                else
                {
                    log_printf( &logger, "OUT4 is high\r\n" );
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
