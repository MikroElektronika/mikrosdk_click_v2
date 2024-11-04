\mainpage Main Page

---
# CDC Click

> CDC Click is a compact add-on board that allows your application do a conversion of capacitance to a digital format. This board features the PCAP04, a capacitance-to-digital converter (CDC) from ScioSense. It also includes an integrated digital signal processor (DSP) for on-chip data post-processing. The converter has high flexibility and allows you to convert grounded capacitors and floating capacitors to a digital format. It has up to 50KHz sampling rate in up to 20-bit resolution.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/cdc_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/cdc-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the CDC Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for CDC Click driver.

#### Standard key functions :

- `cdc_cfg_setup` Config Object Initialization function.
```c
void cdc_cfg_setup ( cdc_cfg_t *cfg );
```

- `cdc_init` Initialization function.
```c
err_t cdc_init ( cdc_t *ctx, cdc_cfg_t *cfg );
```

- `cdc_default_cfg` Click Default Configuration function.
```c
err_t cdc_default_cfg ( cdc_t *ctx );
```

#### Example key functions :

- `cdc_write_config` This function writes configuration data starting from the selected config address.
```c
err_t cdc_write_config ( cdc_t *ctx, uint8_t address, const uint8_t *data_in, uint8_t len );
```

- `cdc_send_opcode` This function sends a desired opcode command byte.
```c
err_t cdc_send_opcode ( cdc_t *ctx, uint8_t opcode );
```

- `cdc_read_results` This function reads all results and status registers.
```c
err_t cdc_read_results ( cdc_t *ctx, cdc_results_t *results );
```

## Example Description

> This example demonstrates the use of CDC Click board by reading capacitance
measurements from C3/C2 and C5/C4 ports calculated from pure capacitance ratio
between those ports and port C1/C0 which is used as external C reference.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    cdc_cfg_t cdc_cfg;  /**< Click config object. */

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
    cdc_cfg_setup( &cdc_cfg );
    CDC_MAP_MIKROBUS( cdc_cfg, MIKROBUS_1 );
    err_t init_flag = cdc_init( &cdc, &cdc_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CDC_ERROR == cdc_default_cfg ( &cdc ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Starts measurement and reads the results. The results data is displayed on the USB UART.

```c
void application_task ( void )
{
    cdc_results_t results;
    cdc_send_opcode ( &cdc, CDC_OPCODE_CDC_START );
    Delay_ms ( 200 );
    if ( CDC_OK == cdc_read_results ( &cdc, &results ) )
    {
        log_printf ( &logger, " C1/C0: %.1f pF\r\n", 
                     results.res_0 * CDC_REF - CDC_INT_CAP_PF );
        log_printf ( &logger, " C3/C2: %.1f pF\r\n", 
                     results.res_1 * CDC_REF - CDC_INT_CAP_PF );
        log_printf ( &logger, " C5/C4: %.1f pF\r\n\n", 
                     results.res_2 * CDC_REF - CDC_INT_CAP_PF );
        Delay_ms ( 1000 );
    }
}
```

## Note

> For better accuracy and higher measurement range, add 200pF external
capacitor between C1/C0 ports and set it below as CDC_EXT_CAP_C1_C0_PF macro
before running the application. This way you will be able to measure capacitance
in range from 1 to 2000pF.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.CDC

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
