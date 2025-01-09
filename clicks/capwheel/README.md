
---
# Cap Wheel Click

> [CAP WHEEL Click](https://www.mikroe.com/?pid_product=MIKROE-3203) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3203&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application is use for controling various devices.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CapWheel

### Example Key Functions

- `capwheel_cfg_setup` Config Object Initialization function. 
```c
void capwheel_cfg_setup ( capwheel_cfg_t *cfg );
``` 
 
- `capwheel_init` Initialization function. 
```c
err_t capwheel_init ( capwheel_t *ctx, capwheel_cfg_t *cfg );
```

- `capwheel_write_reg` Generic Write function. 
```c
uint8_t capwheel_write_reg ( capwheel_t *ctx, uint8_t register_address, uint8_t *data_in, uint8_t n_bytes );
```
 
- `capwheel_read_reg` Generic Read function. 
```c
uint8_t capwheel_read_reg ( capwheel_t *ctx, uint8_t register_address, uint8_t *data_out, uint8_t n_bytes );
```

- `capwheel_check_data_ready` Data Ready Check function. 
```c
uint8_t capwheel_check_data_ready ( capwheel_t *ctx );
```

### Application Init

> Initializes I2C interface, performs the device reset and activates the desired channels (from CH0 to CH9), in this example all channels are activated.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    capwheel_cfg_t cfg;

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

    capwheel_cfg_setup( &cfg );
    CAPWHEEL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capwheel_init( &capwheel, &cfg );

    capwheel_reset ( &capwheel );
    capwheel_enable_chann( &capwheel, CAPWHEEL_CH0_PROX_EN | CAPWHEEL_CH1_EN | CAPWHEEL_CH2_EN | CAPWHEEL_CH3_EN | CAPWHEEL_CH4_EN | CAPWHEEL_CH5_EN | CAPWHEEL_CH6_EN | CAPWHEEL_CH7_EN | CAPWHEEL_CH8_EN | CAPWHEEL_CH9_EN );
    capwheel_set_threshold( &capwheel, 0x03 );
    Delay_ms ( 500 );
    
    log_printf( &logger, "CAP Wheel is initialized and ready\r\n" );
}
```

### Application Task

> Checks is sense data ready for reading and if was ready, then reads wheel coordinates and sends these results to the LEDs.

```c
void application_task ( void )
{
    uint16_t sense_data;
    uint8_t ready_check;

    ready_check = capwheel_check_data_ready( &capwheel );

    if (ready_check == CAPWHEEL_DATA_READY)
    {
        capwheel_get_data( &capwheel, &sense_data );
        
        capwheel_set_output( &capwheel, sense_data, CAPWHEEL_LED_BRIGHTNESS_NUMBER );
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
