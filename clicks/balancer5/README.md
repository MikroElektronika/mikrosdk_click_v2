
---
# Balancer 5 Click

> [Balancer 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3853) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3853&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo performs neccessary initializations, reads ADC values from Click registers and logs it.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Balancer5

### Example Key Functions

- `balancer5_cfg_setup` Config Object Initialization function. 
```c
void balancer5_cfg_setup ( balancer5_cfg_t *cfg );
``` 
 
- `balancer5_init` Initialization function. 
```c
err_t balancer5_init ( balancer5_t *ctx, balancer5_cfg_t *cfg );
```

- `balancer5_default_cfg` Click Default Configuration function. 
```c
void balancer5_default_cfg ( balancer5_t *ctx );
```

- `balancer5_charge` This function sets charging status. 
```c
void balancer5_charge ( balancer5_t *ctx, uint8_t state );
```

### Application Init

> Initializes Click and Driver, Checks Device ID, starts charging, reads charge status registers and configures ADC.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    balancer5_cfg_t cfg;

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

    balancer5_cfg_setup( &cfg );
    BALANCER5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    balancer5_init( &balancer5, &cfg );

    //  Device ID sanity check

    temp_data = balancer5_check_id( &balancer5 );

    if ( temp_data == BALANCER5_ERROR_ID )
    {
        log_info( &logger, "ID ERROR!!!" );
        for ( ; ; );
    }
    
    log_info( &logger, "***** ID OK *****" );

    //  Switch charger on

    balancer5_charge( &balancer5, BALANCER5_CHARGE_ON );

    //  Send configuration info to logger

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_CHARGER_STATUS_1 );
    charger_status_1_handler( temp_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_CHARGER_STATUS_2 );
    charger_status_2_handler( temp_data );

    //  Set default configuration

    balancer5_default_cfg ( &balancer5 );
   
}
```

### Application Task

> Reads ADC values from registers and logs it.

```c
void application_task ( void )
{
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_IBUS_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_IBUS_ADC0 );
    temp_uint_data |= temp_data;
    log_printf( &logger, "- IBUS: %umA\r\n", temp_uint_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_ICHG_ADC1 ); 
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_ICHG_ADC0 );
    temp_uint_data |= temp_data;
    log_printf( &logger, "- ICHG: %umA\r\n", temp_uint_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VBAT_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VBAT_ADC0 );
    temp_uint_data |= temp_data;
    log_printf( &logger, "- VBAT: %umV\r\n", temp_uint_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VBUS_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VBUS_ADC0 );
    temp_uint_data |= temp_data;
    log_printf( &logger, "- VBUS: %umV\r\n", temp_uint_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VCELLTOP_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VCELLTOP_ADC0 );
    temp_uint_data |= temp_data;
    log_printf( &logger, "- VCELLTOP: %umV\r\n", temp_uint_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VCELLBOT_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_VCELLBOT_ADC0 );
    temp_uint_data |= temp_data;
    log_printf( &logger, "- VCELLBOT: %umV\r\n", temp_uint_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_TS_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_TS_ADC0 );
    temp_uint_data |= temp_data;
    temp_float_data = temp_uint_data;
    temp_float_data *= 0.098;
    log_printf( &logger, "- TS: %.2f%%\r\n", temp_float_data );

    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_TDIE_ADC1 );
    temp_uint_data = temp_data;
    temp_uint_data <<= 8;
    temp_data = balancer5_read_data( &balancer5, BALANCER5_REG_TDIE_ADC0 );
    temp_uint_data |= temp_data;
    temp_float_data = temp_uint_data;
    temp_float_data *= 0.5;
    log_printf( &logger, "- TDIE: %.2f%s\r\n", temp_float_data, log_degree );
    
    log_printf( &logger, "____________________\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

Additional functions charger_status_1_handler() and charger_status_2_handler() 
are used to log charger status 1 and 2. 

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
