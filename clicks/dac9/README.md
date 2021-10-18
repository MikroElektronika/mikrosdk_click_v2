\mainpage Main Page

---
# DAC 9 click

> DAC 9 Click is a compact add-on board that contains a fully-featured, highly accurate digital-to-analog converter. This board features the DAC80501, a 16-bit voltage-output digital-to-analog converter with precision internal reference from Texas Instruments. It supports both I2C and SPI serial interface and offers a linearity of < 1 LSB. It also includes a 2.5V internal reference, giving full-scale output voltage ranges of 1.25V, 2.5V, or 5V, incorporate a Power-On Reset function, consume a low current of 1mA, and include a Power-Down feature that reduces current consumption to typically 15μA at 5V.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dac9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dac-9-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the DAC9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DAC9 Click driver.

#### Standard key functions :

- `dac9_cfg_setup` Config Object Initialization function.
```c
void dac9_cfg_setup ( dac9_cfg_t *cfg );
```

- `dac9_init` Initialization function.
```c
err_t dac9_init ( dac9_t *ctx, dac9_cfg_t *cfg );
```

#### Example key functions :

- `dac9_set_config` Set config function.
```c
err_t dac9_set_config ( dac9_t *ctx, uint16_t en_ref_pwdwn, uint16_t en_dac_pwdwn );
```

- `dac9_set_gain` Set gain function.
```c
err_t dac9_set_gain ( dac9_t *ctx, uint16_t en_ref_div, uint16_t en_buff_gain );
```

- `dac9_set_vout` Set Vout function.
```c
err_t dac9_set_vout ( dac9_t *ctx, uint16_t vout_mv );
```

## Example Description

> This is an example that demonstrates the use of the DAC 9 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initalizes SPI or I2C driver and applies default settings.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac9_cfg_t dac9_cfg;  /**< Click config object. */

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
    dac9_cfg_setup( &dac9_cfg );
    DAC9_MAP_MIKROBUS( dac9_cfg, MIKROBUS_1 );
    err_t init_flag  = dac9_init( &dac9, &dac9_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "     Soft reset      \r\n" );
    dac9_soft_reset( &dac9 );
    Delay_ms( 200 );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Vref divided by 2  \r\n" );
    log_printf( &logger, "  Set DAC gain of 2  \r\n" );
    dac9_set_gain( &dac9, DAC9_GAIN_REF_DIV_2, DAC9_GAIN_BUFF_GAIN_2 );
    Delay_ms( 100 );
    
    log_printf( &logger, "---------------------\r\n" );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Demonstrates use of DAC 9 click board by changeing output values every two seconds.

```c

void application_task ( void ) {
    uint16_t n_cnt;
    for ( n_cnt = 0; n_cnt <= res; n_cnt += 500 ) {
        log_printf( &logger, "Output Voltage : %d mV\r\n", ( uint16_t ) n_cnt );
        dac9_set_vout( &dac9, n_cnt );
        Delay_ms( 2000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
