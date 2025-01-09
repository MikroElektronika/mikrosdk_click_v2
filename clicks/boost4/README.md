
---
# Boost 4 Click

> [Boost 4 Click](https://www.mikroe.com/?pid_product=MIKROE-2757) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2757&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jovan Stajkovic
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Boost 4 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Boost4

### Example Key Functions

- `boost4_cfg_setup` Config Object Initialization function. 
```c
void boost4_cfg_setup ( boost4_cfg_t *cfg );
``` 
 
- `boost4_init` Initialization function. 
```c
err_t boost4_init ( boost4_t *ctx, boost4_cfg_t *cfg );
```

- `boost4_generic_transfer` Generic SPI transfer, for sending and receiving packages. 
```c
void boost4_generic_transfer ( boost4_t *ctx, spi_master_transfer_data_t *block );
```
 
- `boost4_set_out_voltage` Function set output voltage by write 12-bit data to the register on the TPS61230A High Efficiency Step-Up Converter of Boost 4 Click. 
```c
void boost4_set_out_voltage ( boost4_t *ctx, uint16_t value );
```

- `boost4_enable` Function is used to enabled or disabled the device. 
```c
void boost4_enable ( boost4_t *ctx, uint8_t state );
```

### Application Init

> Initializes the driver and logger, and enables the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    boost4_cfg_t cfg;

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

    boost4_cfg_setup( &cfg );
    BOOST4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boost4_init( &boost4, &cfg );
    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, "        Boost 4 Click        \r\n" );
    log_printf( &logger, "-----------------------------\r\n" );
    boost4_enable( &boost4, BOOST4_ENABLE );
    Delay_ms ( 1000 );
}
```

### Application Task

> Set the desired output voltage by cycling through a couple of predefined voltage values.
> All data are being logged on USB UART every 3 seconds.

```c
void application_task ( void )
{
    log_printf( &logger, " Set the max Vout \r\n" );
    boost4_set_out_voltage( &boost4, BOOST4_VOUT_MAX );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "-----------------------------\r\n" );

    log_printf( &logger, " Set Vout to 5V\r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_5 );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-----------------------------\r\n" );

    log_printf( &logger, " Set Vout to 4.5V\r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_4_5 );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "-----------------------------\r\n" );
    
    log_printf( &logger, " Set Vout to 4V\r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_4 );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "-----------------------------\r\n" );
    
    log_printf( &logger, " Set Vout to 3.5V\r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_3_5 );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "-----------------------------\r\n" );
    
    log_printf( &logger, " Set Vout to 3V\r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_3 );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "-----------------------------\r\n" );
    
    log_printf( &logger, " Set Vout to 2.5V\r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_2_5 );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "-----------------------------\r\n" );
    
    log_printf( &logger, " Set the min Vout \r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_MIN );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "-----------------------------\r\n" );
}
```

### Note

> Vout cannot be set to voltage below Vin. So in order to get all values at Vout exactly 
> as it is set in this example, please provide 2.5V to Vin. 

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
