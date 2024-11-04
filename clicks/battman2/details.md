
---
# BATT-MAN 2 Click

> BATT-MAN 2 Click is a compact add-on board representing an advanced battery and power management solution. This board features the MAX77654, a single inductor, multiple-output (SIMO) power management IC (PMIC) from Maxim Integrated, now part of Analog Devices. This I2C programmable board features a buck-boost regulator that provides three independently programmable power rails from a single inductor. Also, it has one 100mA LDO output with ripple rejection for audio and other noise-sensitive applications and a highly-configurable linear charger that supports a wide range of Li+ battery capacities featuring battery temperature monitoring for additional safety (JEITA).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/battman2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/batt-man-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the BATTMAN2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for BATTMAN2 Click driver.

#### Standard key functions :

- `battman2_cfg_setup` Config Object Initialization function.
```c
void battman2_cfg_setup ( battman2_cfg_t *cfg );
```

- `battman2_init` Initialization function.
```c
err_t battman2_init ( battman2_t *ctx, battman2_cfg_t *cfg );
```

- `battman2_default_cfg` Click Default Configuration function.
```c
err_t battman2_default_cfg ( battman2_t *ctx );
```

#### Example key functions :

- `battman2_set_charger_enable` BATT-MAN 2 set charger enable function.
```c
err_t battman2_set_charger_enable ( battman2_t *ctx, uint8_t en_chg );
```

- `battman2_set_charger_cfg` BATT-MAN 2 set charger configuration function.
```c
err_t battman2_set_charger_cfg ( battman2_t *ctx, battman2_chg_cnfg_t chg_cnfg );
```

- `battman2_get_charger_cfg` BATT-MAN 2 get charger configuration function.
```c
err_t battman2_get_charger_cfg ( battman2_t *ctx, battman2_chg_cnfg_t *chg_cnfg );
```

## Example Description

> This library contains API for BATT-MAN 2 Click driver.
> The library initializes and defines the I2C bus drivers 
> to write and read data from registers. 
> The library also includes a function for configuring appropriate charge current, 
> charge voltage, prequalification voltage, 
> Buck, Buck-Boost and Linear regulator configuration, etc.

**The demo application is composed of two sections :**

### Application Init

> The initialization of the I2C module, log UART, and additional pins. 
> After the driver inits and executes a default configuration, 
> the app disables charging, sets charger configuration, 
> enables charging, displays charger configuration, 
> or sets Buck-Boost configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    battman2_cfg_t battman2_cfg;  /**< Click config object. */

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
    battman2_cfg_setup( &battman2_cfg );
    BATTMAN2_MAP_MIKROBUS( battman2_cfg, MIKROBUS_1 );
    err_t init_flag = battman2_init( &battman2, &battman2_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    battman2_default_cfg ( &battman2 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 ); 
    
    battman2_set_charger_enable( &battman2, BATTMAN2_SET_CHARGER_DISABLE );
    Delay_ms ( 100 );
        
    #ifdef CHARGER
        log_printf( &logger, "-----------------------------------------------\r\n" );
        log_printf( &logger, "                Example: CHARGER               \r\n" );
    
        chg_cfg.thm_hot           = BATTMAN2_THM_HOT_411_mV;
        chg_cfg.thm_warm          = BATTMAN2_THM_WARM_511_mV;
        chg_cfg.thm_cool          = BATTMAN2_THM_COOL_747_mV;
        chg_cfg.thm_cold          = BATTMAN2_THM_COLD_867_mV;
        chg_cfg.vchgin_min        = 4.2;
        chg_cfg.ichgin_lim        = 95.0;
        chg_cfg.i_pq              = BATTMAN2_I_PQ_10_PERCENTAGE;
        chg_cfg.chg_pq            = 3.0;
        chg_cfg.i_term            = BATTMAN2_I_TERM_5_PERCENTAGE;
        chg_cfg.t_topoff          = BATTMAN2_T_TOPOFF_0_MIN;
        chg_cfg.tj_reg            = BATTMAN2_TJ_REG_60_C;
        chg_cfg.vsys_reg          = 4.100;
        chg_cfg.chg_cc            = 112.5;
        chg_cfg.t_fast_chg        = BATTMAN2_T_FAST_CHG_TIMER_7_HOURS;
        chg_cfg.chg_cc_jeita      = 15.0;
        chg_cfg.thm_en            = BATTMAN2_THM_EN_THERMISTOR_DISABLED;
        chg_cfg.chg_cv            = 3.775;
        chg_cfg.usbs              = BATTMAN2_USBS_CHGIN_IS_NOT_SUSPENDED;
        chg_cfg.chg_cv_jeita      = 3.6;
        chg_cfg.imon_dischg_scale = BATTMAN2_IMON_DISCHG_SCALE_300_mA;
        chg_cfg.mux_sel           = BATTMAN2_MUX_SEL_MULTIPLEXER_DISABLED;
        
        battman2_set_charger_cfg( &battman2, chg_cfg );
        Delay_ms ( 100 );
        
        battman2_set_charger_enable( &battman2, BATTMAN2_SET_CHARGER_ENABLE );
        Delay_ms ( 100 );  
    #endif
        
    #ifdef BUCKBOOST
        log_printf( &logger, "-----------------------------------------------\r\n" );
        log_printf( &logger, "              Example: BUCK-BOOST              \r\n" );
        
        sbb_sel = BATTMAN2_SBB_CH_1;
        sbb_cfg.output_vtg = 5.5;
        sbb_cfg.op_mode = BATTMAN2_OP_MODE_BUCK_AND_BOOST; 
        sbb_cfg.current_limit = BATTMAN2_CURRENT_LIMIT_500_mA;
        sbb_cfg.active_discharge_enable = BATTMAN2_ACTIVE_DISCHARGE_ENABLE;
        sbb_cfg.enable_control = BATTMAN2_ENABLE_CONTROL_ON_IRRESPECTIVE_FPS;
        sbb_cfg.ichgin_lim_def = BATTMAN2_ICHGIN_LIM_95_mA;
        sbb_cfg.drv_sbb = BATTMAN2_DRV_SBB_FAST_TRANSITION_TIME;
        battman2_set_sbb_config( &battman2, sbb_sel, sbb_cfg );
        log_printf( &logger, "-----------------------------------------------\r\n" );
        battman2_set_gpio_output( &battman2, BATTMAN2_SEL_LED_RED, BATTMAN2_PIN_STATE_OFF );
        battman2_set_gpio_output( &battman2, BATTMAN2_SEL_LED_YELLOW, BATTMAN2_PIN_STATE_ON );
        battman2_set_gpio_output( &battman2, BATTMAN2_SEL_LED_BLUE, BATTMAN2_PIN_STATE_OFF );
        Delay_ms ( 1000 );
    #endif
}

```

### Application Task

> This is an example that shows the use of a BATT-MAN 2 Click board™.
> The choice of example profile tasks depends on uncommented code.
> Examples profile: CHARGER and BUCK-BOOST.
> In the CHARGER profile, while on the BATT-MAN 2 Click board™ the 
> blue LED is the battery charging indicator, 
> while the red LED indicates the cessation of battery charging. 
> The yellow LED is an indicator of the BUCK-BOOST profile.
> Results are being sent to the USART terminal where the user can track their changes.

```c

void application_task ( void ) 
{   
    #ifdef CHARGER
        battman2_get_chg_status( &battman2, &chg_stat );
        Delay_ms ( 10 );
        
        display_charger_status( );
        Delay_ms ( 1000 );
        
        battman2_get_charger_cfg( &battman2, &chg_cfg );
        log_printf( &logger, " Fast-charge constant current value : %.1f mA\r\n", chg_cfg.chg_cc );
        log_printf( &logger, " Minimum CHGIN Regulation Voltage   : %.3f V\r\n", chg_cfg.vchgin_min );
        log_printf( &logger, " Battery Prequalific. Voltage Thld  : %.3f V\r\n", chg_cfg.chg_pq );
        log_printf( &logger, " System Voltage Regulation          : %.3f V\r\n", chg_cfg.vsys_reg );
        log_printf( &logger, " JEITA Ifast-chg-jeita              : %.2f mA\r\n", chg_cfg.chg_cc_jeita );
        log_printf( &logger, " Fast-charge battery Vreg           : %.3f V\r\n", chg_cfg.chg_cv );
        log_printf( &logger, " Vfast-chg-jeita                    : %.3f V\r\n", chg_cfg.chg_cv_jeita );
        log_printf( &logger, "-----------------------------------------------\r\n" );
        Delay_ms ( 1000 );
    #endif
        
    #ifdef BUCKBOOST 
        battman2_get_sbb_config( &battman2, sbb_sel, &sbb_cfg );
        Delay_ms ( 10 );
        
        display_sbb_status( );
        Delay_ms ( 1000 );
    #endif
}

```

## Additional Function
- `display_charger_status` BATT-MAN 2 display charger status function.
```c
static void display_charger_status ( void );
```
- `display_sbb_status` BATT-MAN 2 display Buck-Boost status function.
```c
static void display_sbb_status ( void ) 
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BATTMAN2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
