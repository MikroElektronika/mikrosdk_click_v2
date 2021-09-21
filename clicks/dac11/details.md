
---
# DAC 11 click

> DAC 11 Click is a compact add-on board that contains a highly accurate digital-to-analog converter. This board features the DAC128S085, a general-purpose OCTAL 12-bit analog voltage-output DAC from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dac11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dac-11-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the DAC11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DAC11 Click driver.

#### Standard key functions :

- `dac11_cfg_setup` Config Object Initialization function.
```c
void dac11_cfg_setup ( dac11_cfg_t *cfg );
```

- `dac11_init` Initialization function.
```c
err_t dac11_init ( dac11_t *ctx, dac11_cfg_t *cfg );
```

- `dac11_default_cfg` Click Default Configuration function.
```c
err_t dac11_default_cfg ( dac11_t *ctx );
```

#### Example key functions :

- `dac11_write_control_reg` This function writes data to a single control register by using SPI serial interface.
```c
err_t dac11_write_control_reg( dac11_t *ctx, uint8_t cmd, uint16_t data_in );
```

- `dac11_set_all_ch_voltage` This function sets the output voltage of all channels depending on the vref value defined by the VCC SEL on-board jumper. 
The VREF and Voltage values can be either in Volts or Milivolts.
```c
err_t dac11_set_all_ch_voltage( dac11_t *ctx, float vref, float voltage );
```

- `dac11_set_specific_ch_voltage` This function sets the output voltage of the specific channels depending on the vref value defined by the VCC SEL on-board jumper. 
The VREF and Voltage values can be either in Volts or Milivolts.
```c
err_t dac11_set_specific_ch_voltage( dac11_t *ctx, uint8_t channel, float vref, float voltage );
```

## Example Description

> This example demonstrates the use of DAC 11 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and executes the click default configuration which sets the WRM mode and disables all outputs.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    dac11_cfg_t dac11_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    Delay_ms( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    dac11_cfg_setup( &dac11_cfg );
    DAC11_MAP_MIKROBUS( dac11_cfg, MIKROBUS_1 );
    err_t init_flag  = dac11_init( &dac11, &dac11_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    dac11_default_cfg ( &dac11 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the output voltage of all channels every 2 seconds and logs the voltage value on the USB UART. 
It will go through the entire voltage range taking into account the number of steps which is defined below.

```c

void application_task ( void )
{
    float step = REFERENCE_VOLTAGE / NUMBER_OF_STEPS;
    float output_voltage = step;
    uint8_t cnt = 0;
    while ( cnt < NUMBER_OF_STEPS )
    {
        dac11_set_all_ch_voltage ( &dac11, REFERENCE_VOLTAGE, output_voltage );
        log_printf( &logger, " All channels output voltage set to %.2f V\r\n", output_voltage );
        
        output_voltage += step;
        cnt++;
        Delay_ms( 2000 );
    }
}

```

## Note

> Measure the voltage at VCC_SEL jumper and adjust the reference voltage value below for better accuracy.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
