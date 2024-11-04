
---
# VCP Monitor 3 Click

> VCP Monitor 3 Click is a high precision Voltage, Current and Power measurement Click board™ with an input capable of taking up to 15V. It features the LTC2947, from Analog Devices, a high precision power and energy monitor with an internal sense resistor supporting up to ±30A.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/vcpmonitor3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/vcp-monitor-3-click)

---


#### Click library

- **Author**        : Mikroe Team
- **Date**          : Oct 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the VCPMonitor3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for VCPMonitor3 Click driver.

#### Standard key functions :

- `vcpmonitor3_cfg_setup` Config Object Initialization function.
```c
void vcpmonitor3_cfg_setup ( vcpmonitor3_cfg_t *cfg );
```

- `vcpmonitor3_init` Initialization function.
```c
err_t vcpmonitor3_init ( vcpmonitor3_t *ctx, vcpmonitor3_cfg_t *cfg );
```

- `vcpmonitor3_default_cfg` Click Default Configuration function.
```c
err_t vcpmonitor3_default_cfg ( vcpmonitor3_t *ctx );
```

#### Example key functions :

- `vcpmonitor3_rd_page_0` Read Data From Page 0 function.
```c
void vcpmonitor3_rd_page_0 ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *rd_data, uint8_t n_bytes );
```

- `vcpmonitor3_set_op_mode` Set Operation Mode function.
```c
void vcpmonitor3_set_op_mode ( vcpmonitor3_t *ctx, uint8_t op_mode );
```

- `vcpmonitor3_read_p` Read Power in Watts function.
```c
float vcpmonitor3_read_p ( vcpmonitor3_t *ctx );
```

## Example Description

> VCP Monitor 3 Click show it's full usage by reading current, voltage, power, die temperature and voltage at DVCC using SPI or I2C communication protocol.

**The demo application is composed of two sections :**

### Application Init

> Initalizes SPI or I2C driver and sets up the device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vcpmonitor3_cfg_t vcpmonitor3_cfg;  /**< Click config object. */

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
    vcpmonitor3_cfg_setup( &vcpmonitor3_cfg );
    VCPMONITOR3_MAP_MIKROBUS( vcpmonitor3_cfg, MIKROBUS_1 );
    err_t init_flag  = vcpmonitor3_init( &vcpmonitor3, &vcpmonitor3_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( VCPMONITOR3_ERROR == vcpmonitor3_default_cfg ( &vcpmonitor3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example shows capabilities of VCP Monitor 3 Click board by reading current, voltage, power, die temperature and 
> voltage at DVCC and displaying the results via USART terminal.

```c

void application_task ( void )
{
    volt_data = vcpmonitor3_read_v( &vcpmonitor3 );
    log_printf( &logger, " Voltage :         %.2f V \r\n", volt_data );
    
    cur_data = vcpmonitor3_read_i( &vcpmonitor3 );
    log_printf( &logger, " Current :         %.2f A \r\n", cur_data );
    
    pow_data = vcpmonitor3_read_p( &vcpmonitor3 );
    log_printf( &logger, " Power :           %.2f W \r\n", pow_data );
   
    die_temp = vcpmonitor3_read_temp( &vcpmonitor3 );
    log_printf( &logger, " Die Temperature : %.2f C \r\n", die_temp );

    volt_vcc = vcpmonitor3_read_vcc( &vcpmonitor3 );
    log_printf( &logger, " Voltage at DVCC : %.2f V \r\n", volt_vcc );

    log_printf( &logger, " ------------------------------- \r\n" );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.VCPMonitor3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
