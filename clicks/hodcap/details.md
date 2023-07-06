
---
# HOD CAP click

> HOD CAP Click is a compact add-on board that adds a smart sensing solution to your application. This board features the AS8579, a capacitive sensor from ams OSRAM. The sensor features I/Q signal demodulation, parasitic influences from cable, and PCB protection. It has ten sense outputs, five of which come with sensing line filter circuits. This Click board™ makes the perfect solution for the development of autonomous driving applications such as hands-on steering wheel detection and detection of any human presence inside a vehicle or outside of the vehicle, e.g., for automatic trunk opener and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hodcap_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hod-cap-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the HOD CAP Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for HOD CAP Click driver.

#### Standard key functions :

- `hodcap_cfg_setup` Config Object Initialization function.
```c
void hodcap_cfg_setup ( hodcap_cfg_t *cfg );
```

- `hodcap_init` Initialization function.
```c
err_t hodcap_init ( hodcap_t *ctx, hodcap_cfg_t *cfg );
```

- `hodcap_default_cfg` Click Default Configuration function.
```c
err_t hodcap_default_cfg ( hodcap_t *ctx );
```

#### Example key functions :

- `hodcap_get_i_q_data` HOD CAP gets the I and Q data function.
```c
err_t hodcap_get_i_q_data ( hodcap_t *ctx, uint16_t *i_data, uint16_t *q_data );
```

- `hodcap_mux_channel_selection` HOD CAP MUX channel selection function.
```c
err_t hodcap_mux_channel_selection ( hodcap_t *ctx, uint8_t sen_pos );
```

- `hodcap_wait_adc_data_ready` HOD CAP wait ADC data ready function.
```c
err_t hodcap_wait_adc_data_ready ( hodcap_t *ctx );
```

## Example Description

> This library contains API for the HOD CAP Click driver. 
> The demo application sets the sensor configuration 
> and detects the changes in capacity by measuring 
> the relative change of the impedance for each channel.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hodcap_cfg_t hodcap_cfg;  /**< Click config object. */

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
    hodcap_cfg_setup( &hodcap_cfg );
    HODCAP_MAP_MIKROBUS( hodcap_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hodcap_init( &hodcap, &hodcap_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HODCAP_ERROR == hodcap_default_cfg ( &hodcap ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "________________________\r\n" );
    Delay_ms( 100 );
}
```

### Application Task

> This example demonstrates the use of the HOD CAP Click board™.
> The demo application measures the relative change of the impedance 
> and displays I and Q data per channel.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{ 
    static uint16_t i_data, q_data;
    log_printf( &logger, " \tI/Q data \r\n" );
    for ( uint8_t sen_num = 0; sen_num < HODCAP_TOTAL_NUMBER_OF_CHANNELS; sen_num++ )
    {
        if ( HODCAP_OK == hodcap_mux_channel_selection ( &hodcap, sen_num ) )
        {
            if ( ( HODCAP_OK == hodcap_wait_adc_data_ready( &hodcap ) ) &&
                 ( HODCAP_OK == hodcap_get_i_q_data( &hodcap, &i_data, &q_data ) ) )
            {
                log_printf( &logger, " SEN%d -> ", ( uint16_t ) sen_num );
                log_printf( &logger, " I : %u |", i_data );
                log_printf( &logger, " Q : %u \r\n", q_data );       
                Delay_ms( 100 );
            }
        }
    }
    log_printf( &logger, "________________________\r\n" );
    Delay_ms( 2000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HODCAP

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
