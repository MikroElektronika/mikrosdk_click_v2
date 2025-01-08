
---
# Pressure Click

> [Pressure Click](https://www.mikroe.com/?pid_product=MIKROE-1422) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1422&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nemanja Medakovic
- **Date**          : Nov 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

>
> This is a example which demonstrates the use of Pressure Click board.
> Measured pressure and temperature data from the LPS331AP sensor on Pressure Click.
>

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure

### Example Key Functions

- `pressure_cfg_setup` Configuration Object Setup function. 
```c
void pressure_cfg_setup ( pressure_cfg_t *cfg );
```

- `pressure_init` Click Initialization function. 
```c
pressure_err_t pressure_init ( pressure_t *ctx, pressure_cfg_t *cfg );
```

- `pressure_default_cfg` Click Default Configuration function. 
```c
void pressure_default_cfg ( pressure_t *ctx );
```

- `pressure_generic_single_write` Generic Single Write function. 
```c
pressure_err_t pressure_generic_single_write ( pressure_t *ctx, uint8_t reg_addr, uint8_t data_in );
```

- `pressure_generic_multiple_read` Generic Multiple Read function. 
```c
pressure_err_t pressure_generic_multiple_read ( pressure_t *ctx, uint8_t reg_addr, uint8_t *data_out, uint8_t n_data );
```

- `pressure_get_pressure` Pressure Get function. 
```c
float pressure_get_pressure ( pressure_t *ctx );
```

### Application Init

>
> Initializes I2C/SPI serial interface and puts a device to the initial state.
> Also initializes UART console module for results logging.
>

```c
void application_init( void )
{
    pressure_cfg_t pressure_cfg;
    log_cfg_t console_cfg;

    //  Click initialization.
    pressure_cfg_setup( &pressure_cfg );
    PRESSURE_MAP_MIKROBUS( pressure_cfg, MIKROBUS_1 );
    pressure_init( &pressure, &pressure_cfg );
    pressure_sw_reset( &pressure );
    pressure_default_cfg( &pressure );

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( console_cfg );
    log_init( &console, &console_cfg );
    log_write( &console, "***  Pressure initialization done  ***",
               LOG_FORMAT_LINE );
    log_write( &console, "**************************************",
               LOG_FORMAT_LINE );
}
```

### Application Task

>
> Reads the pressure and temperature results in standard units when
> measurement was done and sends results to the console (usb uart terminal).
> Repeats operation every 500ms.
>

```c
void application_task( void )
{
    uint8_t status;
    float press;
    float temp;

    status = pressure_get_status( &pressure, PRESSURE_FLAG_MASK_P_DATA_RDY |
                                             PRESSURE_FLAG_MASK_T_DATA_RDY );

    while (!status)
    {
        status = pressure_get_status( &pressure, PRESSURE_FLAG_MASK_P_DATA_RDY |
                                                 PRESSURE_FLAG_MASK_T_DATA_RDY );
    }

    press = pressure_get_pressure( &pressure );
    temp = pressure_get_temperature( &pressure );

    log_printf( &console, "** Pressure is %.2f mbar\r\n", press );
    log_printf( &console, "** Temperature is %.2f ", temp );
    log_write( &console, deg_cels, LOG_FORMAT_LINE );
    log_write( &console, "**************************************",
               LOG_FORMAT_LINE );

    Delay_ms ( 500 );
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
