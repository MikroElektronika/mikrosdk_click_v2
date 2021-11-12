\mainpage Main Page

---
# pH click

> pH Click is a compact add-on board that provides an opportunity for the user to read pH with the same accuracy and capabilities as with some other expensive solutions. This board features the pH EZO™, a 6th generation embedded pH circuit that offers the highest level of stability and accuracy from AtlasScientific.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ph_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ph-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2021.
- **Type**          : UART type


# Software Support

We provide a library for the pH Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for pH Click driver.

#### Standard key functions :

- `ph_cfg_setup` Config Object Initialization function.
```c
void ph_cfg_setup ( ph_cfg_t *cfg );
```

- `ph_init` Initialization function.
```c
err_t ph_init ( ph_t *ctx, ph_cfg_t *cfg );
```

- `ph_default_cfg` Click Default Configuration function.
```c
err_t ph_default_cfg ( ph_t *ctx );
```

#### Example key functions :

- `ph_send_cmd` Send command function.
```c
void ph_send_cmd ( ph_t *ctx, char *p_cmd );
```

- `ph_get_cmd_resp` Send get response function.
```c
void ph_get_cmd_resp ( ph_t *ctx, char *p_cmd, char *p_resp );
```

- `ph_switch_led` Toggle LED function.
```c
void ph_switch_led ( ph_t *ctx, uint8_t state, char *p_resp );
```

## Example Description

> This example reads and processes data from pH clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes UART driver, performing a factory reset of the device, disabling continuous read, 
> and performing calibration at the midpoint on the pH scale.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ph_cfg_t ph_cfg;  /**< Click config object. */

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
    ph_cfg_setup( &ph_cfg );
    PH_MAP_MIKROBUS( ph_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ph_init( &ph, &ph_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    ph_factory_rst( &ph, app_buf );
    Delay_ms( 1000 );
    
    ph_cont_read( &ph, 0, app_buf );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "   -- Initialized --   \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "  Place probe into pH  \r\n" );
    log_printf( &logger, " neutral substance for \r\n" );
    log_printf( &logger, " mid point calibration \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    for ( uint8_t n_cnt = 0; n_cnt < 20; n_cnt++ )
    {
        Delay_ms( 1000 );
    }
    log_printf( &logger, " Starting calibration  \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    ph_perf_calib ( &ph, PH_CMD_CALIB_MID, 7.000, app_buf );
    Delay_ms( 1000 );
    log_printf( &logger, " Calibration done!     \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    
    log_printf( &logger, " - Application  task -\r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    ph_send_cmd( &ph, PH_CMD_DIS_RSP_CODES );
    Delay_ms( 1000 );
    ph_clr_log_buf( app_buf );
}

```

### Application Task

> This example shows the capabilities of the pH Click board by performing a reading of the 
> pH value of the substance in which the probe is submerged and displaying readings via the 
> USART terminal.

```c

void application_task ( void ) 
{
    ph_send_cmd ( &ph, PH_CMD_SET_SNGL_READ );
    ph_response( &ph, app_buf );
    log_printf( &logger, " pH value: %s ", app_buf );
    log_printf( &logger, "-----------------------\r\n" );
    ph_clr_log_buf( app_buf );
    Delay_ms( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.pH

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
