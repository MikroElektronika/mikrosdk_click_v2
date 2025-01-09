
---
# Thermo 17 Click

> [Thermo 17 Click](https://www.mikroe.com/?pid_product=MIKROE-3994) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3994&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo-app shows local and remote temperature measurement procedure using Thermo 17 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo17

### Example Key Functions

- `thermo17_cfg_setup` Config Object Initialization function. 
```c
void thermo17_cfg_setup ( thermo17_cfg_t *cfg );
``` 
 
- `thermo17_init` Initialization function. 
```c
err_t thermo17_init ( thermo17_t *ctx, thermo17_cfg_t *cfg );
```

- `thermo17_generic_read` This function reads data from the desired register. 
```c
uint8_t thermo17_generic_read ( thermo17_t *ctx,  uint8_t reg_adr );
```

- `thermo17_generic_write` This function writes data to the desired register. 
```c
void thermo17_generic_write ( thermo17_t *ctx, uint8_t reg_adr, uint8_t write_data );
```
 
- `thermo17_read_temp` This function reads data from the local or remote registers. 
```c
float thermo17_read_temp ( thermo17_t *ctx, uint8_t temp_macro );
```

### Application Init

> Initialization of the device and checks ID.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo17_cfg_t cfg;
    uint8_t id_data;

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
    log_info( &logger, " Application Init " );

    //  Click initialization.

    thermo17_cfg_setup( &cfg );
    THERMO17_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo17_init( &thermo17, &cfg );

    id_data = thermo17_generic_read( &thermo17 ,THERMO17_REG_R_ID );
    
    if ( id_data == THERMO17_DEV_ID )
    {
        log_info( &logger, " - Correct device ID" );
    }
    else
    {
        log_info( &logger, " - Device ID ERROR" );
        for ( ; ; );
    }

    log_info( &logger, " Starting measurement " );
}
```

### Application Task

> Appliction measures temp value every 1000ms and logs it.

```c
void application_task ( void )
{
    float read_data;

    read_data = thermo17_read_temp( &thermo17 ,THERMO17_TEMPERATURE_LOCAL );
    log_printf( &logger, " - LOCAL: : %.2f C\r\n", read_data );

    Delay_ms ( 100 );

    read_data = thermo17_read_temp( &thermo17 ,THERMO17_TEMPERATURE_REMOTE );
    log_printf( &logger, " - REMOTE: : %.2f C\r\n", read_data );
    
    Delay_ms ( 100 );
    log_printf( &logger, " ******************** \r\n" );
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
