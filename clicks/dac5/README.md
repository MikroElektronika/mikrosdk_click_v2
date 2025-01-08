
---
# DAC 5 Click

> [DAC 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3712) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3712&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Nov 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo example sends digital signal to one of the outputs and converts it to analog

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Dac5

### Example Key Functions

- `dac5_cfg_setup` Config Object Initialization function. 
```c
void dac5_cfg_setup ( dac5_cfg_t *cfg );
``` 
 
- `dac5_init` Initialization function. 
```c
err_t dac5_init ( dac5_t *ctx, dac5_cfg_t *cfg );
```

- `dac5_send_data` Function for sending data to one output. 
```c
uint8_t dac5_send_data( dac5_t *ctx, uint8_t data_reg, uint16_t data_buf );
```
 
- `dac5_config` Function for configurating Click. 
```c
void dac5_config( dac5_t *ctx, uint16_t config_data );
```

- `dac5_get_device_id` Function for reading device id. 
```c
uint16_t dac5_get_device_id( dac5_t *ctx );
```

### Application Init

> Initializes driver init, tests communication and configures device for measuring

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dac5_cfg_t cfg;

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

    dac5_cfg_setup( &cfg );
    DAC5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac5_init( &dac5, &cfg );

    if ( dac5_get_device_id( &dac5 ) != DAC5_DEVICE_ID )
    {
        log_printf( &logger, "ERROR - DEVICE IS NOT READY\r\n" );
        log_printf( &logger, "Please check the onboard jumpers position.\r\n" );
        for ( ; ; );
    }

    dac5_config( &dac5, DAC5_CONFIG_GLOBAL_ENABLED );
    log_printf( &logger, "The Click board is configured.\r\n" );

    Delay_ms ( 100 );
}
```

### Application Task

> Sets the channel H with different values and logs the expected output on USB UART

```c
void application_task ( void )
{
    for ( uint16_t cnt = DAC5_MIN_DATA; cnt < DAC5_MAX_DATA; cnt += 500 )
    {
        if ( dac5_send_data( &dac5, DAC5_REG_DAC_H_DATA, cnt ) == DAC5_ERROR )
        {
            log_printf( &logger, "ERROR SENDING DATA\r\n" );
        }
        else
        {
            log_printf( &logger, "Expected output on channel H:\t %d mV\r\n", ( uint16_t )( ( ( float ) cnt / DAC5_MAX_DATA ) * dac5.vref ) );
        }
        log_printf( &logger,"------------------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}
```

### Note

> In order to improve the accuracy, measure the voltage on the Click board VrefIN SEL jumper and set it as VREF.

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
