\mainpage Main Page

---
# HW Monitor 3 Click

> HW Monitor 3 Click is a compact add-on board designed for precise voltage monitoring and supervision in critical systems. This board features the TPS389006, a six-channel window voltage supervisor IC from Texas Instruments, offering SIL-3 safety compliance. This board features I2C programmability, ±6mV accuracy, built-in CRC error checking, sequence logging, and an integrated ADC for real-time voltage readouts. It supports fixed window thresholds with fine granularity, undervoltage lockout (UVLO) at 2.48V, and remote sensing to monitor high-current rails accurately.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hwmonitor3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/hw-monitor-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the HW Monitor 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for HW Monitor 3 Click driver.

#### Standard key functions :

- `hwmonitor3_cfg_setup` Config Object Initialization function.
```c
void hwmonitor3_cfg_setup ( hwmonitor3_cfg_t *cfg );
```

- `hwmonitor3_init` Initialization function.
```c
err_t hwmonitor3_init ( hwmonitor3_t *ctx, hwmonitor3_cfg_t *cfg );
```

- `hwmonitor3_default_cfg` Click Default Configuration function.
```c
err_t hwmonitor3_default_cfg ( hwmonitor3_t *ctx );
```

#### Example key functions :

- `hwmonitor3_enable_channel` This function enables the selected monitoring channels.
```c
err_t hwmonitor3_enable_channel ( hwmonitor3_t *ctx, uint8_t ch_mask );
```

- `hwmonitor3_set_scaling` This function sets the scaling level for the selected monitoring channels.
```c
err_t hwmonitor3_set_scaling ( hwmonitor3_t *ctx, uint8_t scaling, uint8_t ch_mask );
```

- `hwmonitor3_read_voltage` This function reads the voltage level from all 6 monitoring analog input channels.
```c
err_t hwmonitor3_read_voltage ( hwmonitor3_t *ctx, hwmonitor3_ch_mon_t *ch_mon );
```

## Example Description

> This example demonstrates the use of HW Monitor 3 Click board by reading and displaying the voltage level from 6 analog input channels.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hwmonitor3_cfg_t hwmonitor3_cfg;  /**< Click config object. */

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
    hwmonitor3_cfg_setup( &hwmonitor3_cfg );
    HWMONITOR3_MAP_MIKROBUS( hwmonitor3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hwmonitor3_init( &hwmonitor3, &hwmonitor3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HWMONITOR3_ERROR == hwmonitor3_default_cfg ( &hwmonitor3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the voltage level from all 6 analog input channels and displays the results on the USB UART once per second approximately.

```c
void application_task ( void )
{
    hwmonitor3_ch_mon_t ch_mon;
    if ( HWMONITOR3_OK == hwmonitor3_read_voltage ( &hwmonitor3, &ch_mon ) )
    {
        log_printf ( &logger, " CH1: %.3f V\r\n", ch_mon.ch1_v );
        log_printf ( &logger, " CH2: %.3f V\r\n", ch_mon.ch2_v );
        log_printf ( &logger, " CH3: %.3f V\r\n", ch_mon.ch3_v );
        log_printf ( &logger, " CH4: %.3f V\r\n", ch_mon.ch4_v );
        log_printf ( &logger, " CH5: %.3f V\r\n", ch_mon.ch5_v );
        log_printf ( &logger, " CH6: %.3f V\r\n\n", ch_mon.ch6_v );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HWMonitor3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
