
---
# Cap Wheel 2 Click

> [Cap Wheel 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3677) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3677&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example sets basic device configuration; Contains function for waiting RDY(INT) pin, function for getting RDY(INT) pin state, function for I2C read and write with waiting for RDY(INT) pin and without waiting for RDY(INT) pin.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CapWheel2

### Example Key Functions

- `capwheel2_cfg_setup` Config Object Initialization function. 
```c
void capwheel2_cfg_setup ( capwheel2_cfg_t *cfg );
``` 
 
- `capwheel2_init` Initialization function. 
```c
err_t capwheel2_init ( capwheel2_t *ctx, capwheel2_cfg_t *cfg );
```

- `capwheel2_default_cfg` Click Default Configuration function. 
```c
void capwheel2_default_cfg ( capwheel2_t *ctx );
```

- `capwheel2_int_get` This function gets state of INT pin. 
```c
uint8_t capwheel2_int_get ( capwheel2_t *ctx );
```
 
- `capwheel2_wait_for_rdy` This function waits for RDY pin to transition from HIGH to LOW state. 
```c
uint8_t capwheel2_wait_for_rdy ( capwheel2_t *ctx );
```

### Application Init

> Initializes CAP Wheel 2 device

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    capwheel2_cfg_t cfg;

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

    capwheel2_cfg_setup( &cfg );
    CAPWHEEL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capwheel2_init( &capwheel2, &cfg );
}
```

### Application Task

> Executes one of three 'capwheel2_get_xxx_task( )' functions.

```c
void application_task ( void )
{
    capwheel2_get_channels_task( );
}
```

### Note

<pre> 
Additional Functions :

- capwheel2_error( ) - Logs error message and blocks code execution in endless while loop
- capwheel2_get_channels_task( ) - Logs active channels in touch and halt bytes ( channels: CH0 - proximity channel, CH1, CH2, CH3 )
- capwheel2_get_gesture_task( ) - Logs active gestures ( gestures: tap, touch, proximity )
- capwheel2_get_channel_counts_task( ) - Logs channel count values for each channel
- capwheel2_get_channels_touch( ) - Logs touch byte active channels ( exectuted by 'capwheel2_get_channels_task( )' function )
- capwheel2_get_channels_halt( ) - Logs halt byte active channels ( exectuted by 'capwheel2_get_channels_task( )' function )

</pre> 

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
