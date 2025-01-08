
---
# Current 3 Click

> [Current 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4203) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4203&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> Current 3 Click can be used to measure current ranging up to 8000mA, and display temperature, 
> voltage and current data - using I2C comunication.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Current3

### Example Key Functions

- `current3_cfg_setup` Config Object Initialization function.
```c
void current3_cfg_setup ( current3_cfg_t *cfg ); 
```

- `current3_init` Initialization function.
```c
err_t current3_init ( current3_t *ctx, current3_cfg_t *cfg );
```

- `current3_default_cfg` Click Default Configuration function.
```c
void current3_default_cfg ( current3_t *ctx );
```

- `current3_get_temperature` The function get the temperature by read multiple data bytes from a group of contiguous registers
```c
float current3_get_temperature ( current3_t *ctx, uint8_t temp_sel );
```

- `current3_get_source_voltage` The function source voltage registers store the voltage measured at the SENSE+ pin
```c
float current3_get_source_voltage ( current3_t *ctx );
```

- `current3_get_current` The function current measurement measure the direction of current flow ( from SENSE+ to SENSE- or from SENSE- to SENSE+ )
```c
float current3_get_current ( current3_t *ctx );
```

### Application Init

> Initialization driver enables - I2C,
> check communication and set sense sampling configuration, also write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    current3_cfg_t cfg;
    uint8_t read_data;

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

    current3_cfg_setup( &cfg );
    CURRENT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    current3_init( &current3, &cfg );

    Delay_ms ( 100 );
    log_printf( &logger, "     Driver init. done     \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    
    current3_generic_read( &current3, CURRENT3_REG_PRODUCT_ID, &read_data, 1 );
    if (  read_data == CURRENT3_DEV_ID )
    {
        log_printf( &logger, "     Communication OK      \r\n" );
        log_printf( &logger, "---------------------------\r\n" );
    }
    else
    {
        log_printf( &logger, "    Communication ERROR    \r\n" );
        log_printf( &logger, "     Reset the device      \r\n" );
        log_printf( &logger, "---------------------------\r\n" );
        for ( ; ; );
    }
    
    current3_default_cfg( &current3, sense_cfg_data );
}
```

### Application Task

> This is an example which demonstrates the use of Current 3  Click board.
> Current 3 Click board can be used to measure current ranging
> up to 8000mA, and display temperature, voltage and current data.
> All data logs write on USB uart changes for every 2 sec.

```c
void application_task ( void )
{
    temperature = current3_get_temperature( &current3, CURRENT3_TEMP_INTERNAL_DIODE );
    log_printf( &logger, " Temperature = %.2f C\r\n", temperature );

    voltage = current3_get_source_voltage( &current3 );
    log_printf( &logger, " Voltage     = %.2f V\r\n", voltage );

    current = current3_get_current( &current3 );
    log_printf( &logger, " Current     = %.2f mA\r\n", current );
    log_printf( &logger, "---------------------------\r\n" );
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
