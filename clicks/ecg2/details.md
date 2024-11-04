
---
# ECG 2 Click

> ECG 2 Click contains ADS1194 16-bit delta-sigma analog-to-digital converters from Texas Instruments, a built-in programmable gain amplifier (PGA), an internal reference, and an onboard oscillator.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ecg2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ecg-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the ECG 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ECG 2 Click driver.

#### Standard key functions :

- `ecg2_cfg_setup` Config Object Initialization function.
```c
void ecg2_cfg_setup ( ecg2_cfg_t *cfg );
```

- `ecg2_init` Initialization function.
```c
err_t ecg2_init ( ecg2_t *ctx, ecg2_cfg_t *cfg );
```

- `ecg2_default_cfg` Click Default Configuration function.
```c
err_t ecg2_default_cfg ( ecg2_t *ctx );
```

#### Example key functions :

- `ecg2_read_an_pin_value` ECG 2 read AN pin value function.
```c
err_t ecg2_read_an_pin_value ( ecg2_t *ctx, uint16_t *data_out );
```

- `ecg2_send_command` ECG 2 send command function.
```c
err_t ecg2_send_command ( ecg2_t *ctx, uint8_t command );
```

- `ecg2_read_channel_data` ECG 2 read data channel function.
```c
void ecg2_read_channel_data ( ecg2_t *ctx, uint8_t channel, uint16_t *data_out );
```

## Example Description

> This is an example that demonstrates the use of the ECG 2 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes SPI and UART communication, configures INT pin as INPUT, RST pin as OUTPUT, CS pin as 
> OUTPUT and PWM pin as OUTPUT. Initializes SPI driver, initializes ECG2 Click, sends START and 
> RDATAC opcodes.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ecg2_cfg_t ecg2_cfg;  /**< Click config object. */

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
    ecg2_cfg_setup( &ecg2_cfg );
    ECG2_MAP_MIKROBUS( ecg2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ecg2_init( &ecg2, &ecg2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    SET_SPI_DATA_SAMPLE_EDGE;
    
    if ( ECG2_ERROR == ecg2_default_cfg ( &ecg2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    ecg2_send_command( &ecg2, ECG2_START_CONVERSION );
    Delay_ms ( 100 );
    ecg2_send_command( &ecg2, ECG2_ENABLE_READ_DATA_CONT_MODE );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

```

### Application Task

> Captures readings from channel and plots data to serial plotter.

```c

void application_task ( void ) 
{   
    uint16_t ecg_an = 0;
    ecg2_read_channel_data( &ecg2, 5, &ecg_an );
    log_printf( &logger, " %.6u, %.8lu \r\n", ecg_an, time );
    time += 5;
    Delay_ms ( 5 );   
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ECG2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
