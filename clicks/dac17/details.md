
---
# DAC 17 Click

> DAC 17 Click is a compact add-on board that establishes precise voltage output control in various electronic applications. This board features the DAC7558, a 12-bit, octal-channel voltage output digital-to-analog (DAC) from Texas Instruments. It offers flexible internal or external power options with a voltage range from 2.7V to 5.5V. It features a rapid settling time of 5µs, rail-to-rail output amplifiers, and the ability to simultaneously or sequentially update outputs, ensuring precise and efficient performance.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dac17_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/dac-17-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the DAC 17 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DAC 17 Click driver.

#### Standard key functions :

- `dac17_cfg_setup` Config Object Initialization function.
```c
void dac17_cfg_setup ( dac17_cfg_t *cfg );
```

- `dac17_init` Initialization function.
```c
err_t dac17_init ( dac17_t *ctx, dac17_cfg_t *cfg );
```

- `dac17_default_cfg` Click Default Configuration function.
```c
err_t dac17_default_cfg ( dac17_t *ctx );
```

#### Example key functions :

- `dac17_send_command` This function is used to send specific command of the DAC 17 Click board.
```c
err_t dac17_send_command ( dac17_t *ctx, uint8_t command, uint8_t ch_sel, uint16_t data_in );
```

- `dac17_set_dac_output` This function is used to set output level of the sellected channel of the DAC 17 Click board.
```c
err_t dac17_set_dac_output ( dac17_t *ctx, uint8_t ch_sel, uint16_t dac_data );
```

- `dac17_set_all_dac_output` This function is used to set output level of the DAC 17 Click board.
```c
err_t dac17_set_all_dac_output ( dac17_t *ctx, uint16_t dac_data );
```

## Example Description

> This example demonstrates the use of DAC 17 Click board by changing the voltage level on the output channels.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac17_cfg_t dac17_cfg;  /**< Click config object. */

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
    dac17_cfg_setup( &dac17_cfg );
    DAC17_MAP_MIKROBUS( dac17_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == dac17_init( &dac17, &dac17_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC17_ERROR == dac17_default_cfg ( &dac17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the output channels voltage level starting from full scale ( REF voltage ),  
 to the mid-scale ( half of the REF voltage ), and then to zero every two seconds.

```c
void application_task ( void )
{
    #define DAC17_OUTPUT_ZERO           0x0000u
    #define DAC17_OUTPUT_MID_SCALE      0x0800u
    #define DAC17_OUTPUT_FULL_SCALE     0x0FFFu

    log_printf( &logger, " Setting all channels to full scale output \r\n" );
    dac17_set_all_dac_output( &dac17, DAC17_OUTPUT_FULL_SCALE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Setting all channels outputs to zero \r\n" );
    dac17_set_all_dac_output( &dac17, DAC17_OUTPUT_ZERO );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Setting all channels outputs to mid scale \r\n" );
    dac17_set_all_dac_output( &dac17, DAC17_OUTPUT_MID_SCALE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC17

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
