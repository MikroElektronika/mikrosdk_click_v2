\mainpage Main Page

---
# DAC 15 Click

> DAC 15 Click is a compact add-on board that provides a highly accurate digital-to-analog conversion on two channels. This board features the DAC80502, a dual 16-bit 1-LSB INL voltage-output DAC from Texas Instruments. The DAC operates at a wide power supply range and is a low-power device with as low as 1mA per channel at 5.5V. It also includes a 2.5V, 5-ppm/°C internal reference, giving a full-scale voltage buffered output ranges of 1.25V, 2.5V, and 5.5V.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dac15_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dac-15-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the DAC 15 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DAC 15 Click driver.

#### Standard key functions :

- `dac15_cfg_setup` Config Object Initialization function.
```c
void dac15_cfg_setup ( dac15_cfg_t *cfg );
```

- `dac15_init` Initialization function.
```c
err_t dac15_init ( dac15_t *ctx, dac15_cfg_t *cfg );
```

- `dac15_default_cfg` Click Default Configuration function.
```c
err_t dac15_default_cfg ( dac15_t *ctx );
```

#### Example key functions :

- `dac15_set_dac_data` DAC 15 set DAC data function.
```c
err_t dac15_set_dac_data ( dac15_t *ctx, uint8_t dac_sel, uint16_t dac_data );
```

- `dac15_get_dac_data` DAC 15 get DAC data function.
```c
err_t dac15_get_dac_data ( dac15_t *ctx, uint8_t dac_sel, uint16_t *dac_data );
```

## Example Description

> This example demonstrates the use of DAC 15 Click board™ 
> by changing the output voltage level on the VOUTA and VOUTB.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C or SPI module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac15_cfg_t dac15_cfg;  /**< Click config object. */

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
    dac15_cfg_setup( &dac15_cfg );
    DAC15_MAP_MIKROBUS( dac15_cfg, MIKROBUS_1 );
    err_t init_flag = dac15_init( &dac15, &dac15_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC15_ERROR == dac15_default_cfg ( &dac15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " -------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application changes the output voltage level on the VOUTA and VOUTB.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{   
    static uint16_t dac_data = 0;
    for ( uint16_t n_cnt = 0; n_cnt < 60000; n_cnt += 5000 )
    {
        dac_data = n_cnt;
        if ( DAC15_OK == dac15_set_dac_data( &dac15, DAC15_SET_DAC_A, dac_data ) )
        {
            log_printf( &logger, "VOUTA: %u -> %.2f V\r\n", 
                        dac_data, 
                        ( float ) dac_data * DAC15_VREF_3V3 / DAC15_MAX_DAC_DATA );
        }
        
        dac_data = DAC15_DAC_RES_16BIT - n_cnt;
        if ( DAC15_OK == dac15_set_dac_data( &dac15, DAC15_SET_DAC_B, dac_data ) )
        {
            log_printf( &logger, "VOUTB: %u -> %.2f V\r\n", 
                        dac_data, 
                        ( float ) dac_data * DAC15_VREF_3V3 / DAC15_MAX_DAC_DATA );
        }
        log_printf( &logger, " -------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC15

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
