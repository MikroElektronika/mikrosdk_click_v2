
---
# TMR mix-sens Click

> [TMR mix-sens Click](https://www.mikroe.com/?pid_product=MIKROE-4106) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4106&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : ADC type

# Software Support

## Example Description

> The TMR mix-sens Click has three types of magnetic field sensors: Two digital and one analog sensor. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Tmrmixsens

### Example Key Functions

- `tmrmixsens_cfg_setup` Config Object Initialization function. 
```c
void tmrmixsens_cfg_setup ( tmrmixsens_cfg_t *cfg );
``` 
 
- `tmrmixsens_init` Initialization function. 
```c
err_t tmrmixsens_init ( tmrmixsens_t *ctx, tmrmixsens_cfg_t *cfg );
```

- `tmrmixsens_generic_read` Generic read function. 
```c
tmrmixsens_data_t tmrmixsens_generic_read ( tmrmixsens_t *ctx );
```
 
- `tmrmixsens_get_omnipolar` Get state of the omnipolar ( OMN ) pin function. 
```c
uint8_t tmrmixsens_get_omnipolar ( tmrmixsens_t *ctx );
```

- `tmrmixsens_get_bipolar` Get state of the bipolar ( BI ) pin function. 
```c
uint8_t tmrmixsens_get_bipolar ( tmrmixsens_t *ctx );
```

### Application Init

> Initializes the driver and logger and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    tmrmixsens_cfg_t cfg;

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

    tmrmixsens_cfg_setup( &cfg );
    TMRMIXSENS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tmrmixsens_init( &tmrmixsens, &cfg );
}
```

### Application Task

> Displays the ADC value of linear output and the states of bipolar and omnipolar indicators on the USB UART each second.

```c
void application_task ( void )
{
    tmrmixsens_data_t tmp;
    
    tmp = tmrmixsens_generic_read ( &tmrmixsens );
    log_printf( &logger, " ADC value of linear output : %d \r\n", tmp );

    log_printf( &logger, " Bipolar response: " );
    if ( tmrmixsens_get_bipolar( &tmrmixsens ) == TMRMIXSENS_NORTH_POLE )
    {
        log_printf( &logger, " North pole is detected!\r\n" );
    }
    else if( tmrmixsens_get_bipolar( &tmrmixsens ) == TMRMIXSENS_SOUTH_POLE )
    {
        log_printf( &logger, " South pole is detected!\r\n" );
    }
    
    if ( tmrmixsens_get_omnipolar ( &tmrmixsens ) == 0 )
    {
        log_printf( &logger, " Omnipolar response: Either South or North pole is detected!\r\n" );
    }
    
    log_printf( &logger, "--------------------------------------\r\n" );
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
