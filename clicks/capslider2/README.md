
---
# CAP Slider 2 Click

> [CAP Slider 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3204) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3204&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application could be used for controlling various devices.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CapSlider2

### Example Key Functions

- `capslider2_cfg_setup` Config Object Initialization function. 
```c
void capslider2_cfg_setup ( capslider2_cfg_t *cfg );
``` 
 
- `capslider2_init` Initialization function. 
```c
err_t capslider2_init ( capslider2_t *ctx, capslider2_cfg_t *cfg );
```

- `capsldr2_write_reg` Generic Write function. 
```c
uint8_t capsldr2_write_reg( capslider2_t *ctx, uint8_t register_address, uint8_t *data_in, uint8_t n_bytes );
```
 
- `capsldr2_read_reg` Generic Read function. 
```c
uint8_t capsldr2_read_reg( capslider2_t *ctx, uint8_t register_address, uint8_t *data_out, uint8_t n_bytes );
```

- `capsldr2_check_data_ready` Data Ready Check function. 
```c
uint8_t capsldr2_check_data_ready( capslider2_t *ctx );
```

### Application Init

> Initializes I2C interface, performs the device reset and configurations
> and sets the desired threshold value which determines sensor sensitivity.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    capslider2_cfg_t cfg;

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

    capslider2_cfg_setup( &cfg );
    CAPSLIDER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capslider2_init( &capslider2, &cfg );

    Delay_ms ( 500 );

    cnt = 0;
    wheel_avrg1 = 0;
    wheel_avrg2 = 0;
    
    capsldr2_reset( &capslider2 );
    Delay_ms ( 500 );
    
    capsldr2_enable_chann( &capslider2, CAPSLDR2_CH0_PROX_EN | CAPSLDR2_CH1_EN | CAPSLDR2_CH2_EN | CAPSLDR2_CH3_EN | CAPSLDR2_CH4_EN | CAPSLDR2_CH5_EN | CAPSLDR2_CH6_EN | CAPSLDR2_CH7_EN | CAPSLDR2_CH8_EN | CAPSLDR2_CH9_EN );
    capsldr2_config( &capslider2 );
    capsldr2_set_threshold( &capslider2, 0x04 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "CAP Slider 2 is initialized\r\n" );

}
```

### Application Task

> Checks for data ready and then read capacitance from all channels.
> There are two sliders on the clik board (X and Y).
> X slider selects which LEDs are being activated, 
> while Y slider increases/decreases the LEDs intensity.

```c
void application_task ( void )
{
    uint16_t data_wheel1;
    uint16_t data_wheel2;
    uint8_t ready_check;

    ready_check = capsldr2_check_data_ready( &capslider2 );
    
    if (ready_check == CAPSLDR2_DATA_READY)
    {
        capsldr2_get_data( &capslider2, &data_wheel1, &data_wheel2 );
        
        wheel_avrg1 += data_wheel1;
        wheel_avrg2 += data_wheel2;
        cnt++;
    }
    
    if (cnt == 1)
    {
        if ((wheel_avrg2 / cnt) > 1800)
        {
            horizontal_check(  );
            capsldr2_set_output( &capslider2, out_val, out_mode );
        }
        else if (((wheel_avrg2 / cnt) < 1650) && ((wheel_avrg2 / cnt) > 1000))
        {
            vertical_check(  );
            capsldr2_set_output( &capslider2, out_val, out_mode );
        }
        
        wheel_avrg1 = 0;
        wheel_avrg2 = 0;
        cnt = 0;
    }
}
```

### Note

> In some cases, the user will need to wait several seconds after the Click initialization for the sensor to be stabilized.

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
