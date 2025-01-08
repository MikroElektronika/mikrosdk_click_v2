
---
# CO2 Click

> [CO2 Click](https://www.mikroe.com/?pid_product=MIKROE-4725) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4725&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases ability of Click board. It reads ID's 
configures device for operation work and reads CO2 gas 
concentration in air and temperature of IC every second.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CO2

### Example Key Functions

- `co2_cfg_setup` Config Object Initialization function.
```c
void co2_cfg_setup ( co2_cfg_t *cfg );
```

- `co2_init` Initialization function.
```c
err_t co2_init ( co2_t *ctx, co2_cfg_t *cfg );
```

- `co2_default_cfg` Click Default Configuration function.
```c
err_t co2_default_cfg ( co2_t *ctx );
```

- `co2_get_id` Read device and serial ID's.
```c
err_t co2_get_id ( co2_t *ctx );
```

- `co2_set_reference` Set device refrence values for gas calculation.
```c
err_t co2_set_reference ( co2_t *ctx, uint16_t humidity, uint16_t pressure );
```

- `co2_read_gas` Read CO2 concentration and temperature value.
```c
err_t co2_read_gas ( co2_t *ctx, float *gas_concentration, float *temperature );
```

### Application Init

> Initialization of host communication modules (UART, I2C). 
Checks device and serial ID's from device. Then calls default 
configuration function that resets device, self tests it selft 
and configures for measuring CO2 concentration from air.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */

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

    // Click initialization.
    co2_cfg_setup( &co2_cfg );
    CO2_MAP_MIKROBUS( co2_cfg, MIKROBUS_1 );
    err_t init_flag = co2_init( &co2, &co2_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    init_flag = co2_get_id( &co2 );
    
    if ( ( init_flag < 0 ) && ( co2.device_id != CO2_DEVICE_ID ) )
    {
        log_error( &logger, "ID" );
    }
    else
    {
        log_printf( &logger, " > Device ID: 0x%.8lX\r\n", co2.device_id );
        log_printf( &logger, " > Serial ID: 0x%.8lX%.8lX\r\n", co2.serial_id[ 0 ], co2.serial_id[ 1 ] );
    }
    
    init_flag = co2_default_cfg ( &co2 );
    
    if ( init_flag < 0 )
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    //Set reference values for device to calculate gas concentartion.
    if ( CO2_OK != co2_set_reference( &co2, CO2_AIR_HUMIDITY, CO2_AIR_PRESSURE ) )
    {
        log_error( &logger, " Reference values." );
    }
    
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads air CO2 gas concentration in precentage and IC's 
temperature in deg Celzius in span of 1 second and logs 
data to UART Terminal.

```c
void application_task ( void )
{
    float gas_data = 0;
    float temp_data = 0;
    
    if ( CO2_OK == co2_read_gas( &co2, &gas_data, &temp_data ) )
    {
        log_printf( &logger, " > CO2[%%]: %.2f\r\n", gas_data );
        log_printf( &logger, " > Temperature[degC]: %.2f\r\n", temp_data );
        Delay_ms ( 1000 );
    }
    
    Delay_ms ( 1 );
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
