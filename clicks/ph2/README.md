\mainpage Main Page

---
# pH 2 Click

> pH 2 Click is a compact add-on board used to determine the alkalinity or acidity of a sample. This board features the MCP607, a low-bias current Op Amp from Microchip, performing level shifting and high-input impedance buffering in a single-supply pH-electrode circuit.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ph2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ph-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2023.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the pH 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for pH 2 Click driver.

#### Standard key functions :

- `ph2_cfg_setup` Config Object Initialization function.
```c
void ph2_cfg_setup ( ph2_cfg_t *cfg );
```

- `ph2_init` Initialization function.
```c
err_t ph2_init ( ph2_t *ctx, ph2_cfg_t *cfg );
```

#### Example key functions :

- `ph2_calibrate` Ph 2 calibrate function.
```c
err_t ph2_calibrate ( ph2_t *ctx, float pH_value );
```

- `ph2_calculate_ph` Ph 2 calculate pH value function.
```c
err_t ph2_calculate_ph ( ph2_t *ctx, float *pH_value );
```

- `ph2_calibrate_offset` Ph 2 calibrate offset function.
```c
void ph2_calibrate_offset ( ph2_t *ctx );
```

## Example Description

> This library contains API for pH 2 Click driver. 
The library initializes and defines the I2C bus drivers or 
ADC drivers to read data from pH probe.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs offset calibration, 
as well as calibration in pH-neutral substance.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ph2_cfg_t ph2_cfg;  /**< Click config object. */

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
    ph2_cfg_setup( &ph2_cfg );
    PH2_MAP_MIKROBUS( ph2_cfg, MIKROBUS_1 );
    err_t init_flag = ph2_init( &ph2, &ph2_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, " ================================ \r\n" );
    log_printf( &logger, "     Performing calibration       \r\n" );
    log_printf( &logger, " ================================ \r\n" );
    log_printf( &logger, " Disconect BNC connector, \r\n" );
    log_printf( &logger, "    short-circuit it, \r\n" );
    log_printf( &logger, " adjust offset potentiometer \r\n" );
    log_printf( &logger, " ================================ \r\n" );
    log_printf( &logger, " STAT1 - turn clockwise \r\n" );
    log_printf( &logger, " STAT2 - turn counter-clockwise \r\n" );
    log_printf( &logger, " ================================ \r\n" );
    
    ph2_calibrate_offset( &ph2 );
    
    log_printf( &logger, " Calibration completed \r\n" );
    log_printf( &logger, " ================================ \r\n" );
    
    log_printf( &logger, " Connect probe back \r\n" );
    log_printf( &logger, " ================================ \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "  Place probe into pH  \r\n" );
    log_printf( &logger, " neutral substance for \r\n" );
    log_printf( &logger, " mid point calibration \r\n" );
    log_printf( &logger, " ================================ \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Starting calibration  \r\n" );
    log_printf( &logger, " ================================ \r\n" );  
    
    ph2_calibrate( &ph2, 7 );
    
    log_printf( &logger, " Calibration done!  \r\n" );
    log_printf( &logger, " ================================ \r\n" ); 
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ================================ \r\n" ); 
}

```

### Application Task

> This example demonstrates the use of the pH 2 Click board by 
reading pH value of the substance where probe is placed.

```c

void application_task ( void ) 
{
    float pH_val = 0;
    ph2_calculate_ph( &ph2, &pH_val );
    log_printf( &logger, " pH value: %.3f \r\n", pH_val );
    log_printf( &logger, " ================================ \r\n" ); 
    Delay_ms ( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.pH2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
