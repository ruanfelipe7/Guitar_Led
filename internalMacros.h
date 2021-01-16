#ifndef _INTERNAL_MACROS_
#define _INTERNAL_MACROS_

/*****************************************************************************
**                INTERNAL MACROS
*****************************************************************************/
#define lenVector(x)                                                         \
        ((sizeof(x))/(sizeof(x[0])))
/*#define SHIFT(x,y)                                                            \
        (x&(1<<y))       */
#define SHIFT(x,y)                                                         \
         ((x>>y)&(1))
#define DIV(x,y) ((x)/(y))


/*****************************************************************************
**                INTERNAL DEFINES INTERRUPT
*****************************************************************************/
#define GPIO_INTC_LINE_1                  (0x0)
#define GPIO_INTC_LINE_2                  (0x1)

/*
** Values used to enable/disable interrupt generation due to level
** detection on an input GPIO pin.
*/
#define GPIO_INTC_TYPE_NO_LEVEL           (0x01)
#define GPIO_INTC_TYPE_LEVEL_LOW          (0x04)
#define GPIO_INTC_TYPE_LEVEL_HIGH         (0x08)
#define GPIO_INTC_TYPE_BOTH_LEVEL         (0x0C)

/*
** Values used to enable/disable interrupt generation due to edge
** detection on an input GPIO pin.
*/
#define GPIO_INTC_TYPE_NO_EDGE            (0x80)
#define GPIO_INTC_TYPE_RISE_EDGE          (0x10)
#define GPIO_INTC_TYPE_FALL_EDGE          (0x20)
#define GPIO_INTC_TYPE_BOTH_EDGE          (0x30)

#define GPIO_IRQ_STATUS0                  (0x2C)
#define GPIO_IRQ_STATUS1                  (0x30)


#define TIMER_INITIAL_COUNT            (0xFF000000u)
#define TIMER_RLD_COUNT                (0xFFFFFF83u) //(0xFF000000u)

#define T_1MS_COUNT                     (0x5DC0u)
#define OVERFLOW                        (0xFFFFFFFFu)
#define TIMER_1MS_COUNT                 (0x5DC0u)


/*****************************************************************************
**                INTERNAL TYPES DEFINITIONS
*****************************************************************************/
typedef int CONTROL_MODULE;


enum SemaphoreStates{
   SemaphoreState1 = 1,
   SemaphoreState2,
   SemaphoreState3,
   SemaphoreState4,
   SemaphoreState5,
   SemaphoreState6,
   SemaphoreState7,
   SemaphoreState8,
   SemaphoreState9,

};

enum Display7SegStates{
   SegState1 = 1,
   SegState2,
   SegState3,
   SegState4,
   SegState5,
   SegState6,
   SegState7,
   SegState8,
   SegState9,
};

/*****************************************************************************
**                INTERNAL DEFINITIONS
*****************************************************************************/
#define TIME													                   (400)
#define TIME_1SEC                                        (1000)
#define LOW                                              (0x0)
#define HIGH                                             (0x1u)
#define OUTPUT                                           (0x0)
#define INPUT                                            (0x1u)
#define DOWN                                             (0x0)
#define UP                                               (0x1u)
#define OFF                                              (0x0)
#define ON                                               (0x1u)
#define CLEAR_LCD                                        (0x1u)

/*****************************************************************************
**                DEFINES CONFIGURATION GPIO
*****************************************************************************/
#define GPIO_OE                 								   (0x134)
#define GPIO_CLEARDATAOUT       								   (0x190)
#define GPIO_SETDATAOUT         								   (0x194)
#define GPIO_DATAIN                                      (0x138)

#define conf_module_mmode 										   (0x7) //111
#define conf_module_puden										   (1<<3) //0000
#define conf_module_typesel										(1<<4)
#define conf_module_rxactive									   (1<<5)

/*****************************************************************************
**                DEFINES NUMBER PINS
*****************************************************************************/
#define GPIO1_LED01												   (6)
#define GPIO1_LED02												   (2)
#define GPIO1_LED03												   (13)
#define GPIO1_LED04												   (15)
#define GPIO1_LED05												   (30)

#define GPIO1_LED06												   (7)
#define GPIO1_LED07												   (3)
#define GPIO1_LED08												   (12)
#define GPIO1_LED09												   (14)
#define GPIO1_LED10												   (31)

#define GPIO1_LED11                                      (4)
#define GPIO1_LED12                                      (5)
#define GPIO1_LED13                                      (1)
#define GPIO1_LED14                                      (0)
#define GPIO1_LED15                                      (29)

#define GPIO1_BUTTON1											               (16)
#define GPIO1_BUTTON2                                    (17)
#define GPIO2_BUTTON3                                    (17)
#define GPIO2_BUTTONPAUSE                                (16)
#define GPIO0_BUTTONPLUS                                 (27)
#define GPIO0_BUTTONLESS                                 (26)



#define BUZZER                                           (2)

//PINS LCD
#define DO                                               (6)
#define D1                                               (7)
#define D2                                               (8)
#define D3                                               (9)
#define D4                                               (10)
#define D5                                               (11)
#define D6                                               (12)
#define D7                                               (13)
#define RS                                               (14)
//#define RW                                             2// falta

#define GPIO3_LEDSEMAPHORE1                              (21)
#define GPIO3_LEDSEMAPHORE2                              (19)
#define GPIO3_LEDSEMAPHORE3                              (15)
#define GPIO3_LEDSEMAPHORE4                              (17)
#define GPIO3_LEDSEMAPHORE5                              (16)
#define GPIO3_LEDSEMAPHORE6                              (14)
#define GPIO1_LEDSEMAPHORE7                              (19)
#define GPIO1_LEDSEMAPHORE8                              (18)
#define GPIO1_LEDSEMAPHORE9                              (28)

#define GPIO2_SEGMENTOA                                  (22)
#define GPIO2_SEGMENTOB                                  (23)
#define GPIO2_SEGMENTOC                                  (24)
#define GPIO2_SEGMENTOD                                  (25)
#define GPIO2_SEGMENTOE                                  (5)
#define GPIO2_SEGMENTOF                                  (3)
#define GPIO2_SEGMENTOG                                  (4)





/*****************************************************************************
**                DEFINES CONFIGURATION LCD
*****************************************************************************/
#define ENABLE_LCD                                       (15)
#define LIMPA_LCD                                         0x01
#define LINHA_1                                          0x80
#define LINHA_2                                          0xC0

/*****************************************************************************
**                DEFINES CONFIGURATION MODULE CLOCK
*****************************************************************************/
#define CM_WKUP_GPIO0                                    (0x8)
#define CM_PER_GPIO1                                     (0xAC)
#define CM_PER_GPIO2                                     (0xB0)
#define CM_PER_GPIO3                                     (0xB4)
#define CM_WKUP_GPIO0_CLKCTRL_MODULEMODE_ENABLE          (0x2u)
#define CM_WKUP_GPIO0_CLKCTRL_OPTFCLKEN_GPIO_0_GDBCLK    (1<<18)
#define CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE           (0x2u)
#define CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK     (1<<18)
#define CM_PER_GPIO2_CLKCTRL_MODULEMODE_ENABLE           (0x2u)
#define CM_PER_GPIO2_CLKCTRL_OPTFCLKEN_GPIO_2_GDBCLK     (1<<18)
#define CM_PER_GPIO3_CLKCTRL_MODULEMODE_ENABLE           (0x2u)
#define CM_PER_GPIO3_CLKCTRL_OPTFCLKEN_GPIO_3_GDBCLK     (1<<18)
#define CM_WKUP_GPIO0_CLKCTRL_MODULEMODE_ENABLE          (0x2u)
#define CM_PER_GPIO0_CLKCTRL_OPTFCLKEN_GPIO_0_GDBCLK     (1<<18)

/*****************************************************************************
**                DEFINES CONFIGURATION WATCHDOG
*****************************************************************************/
#define WDT_WSPR                                         (0x48)
#define WDT_WSPR_DOWN_VALUE_TEST                         (0xAAAA)
#define WDT_WSPR_DOWN_VALUE                              (0x5555)
#define WDT_WSPR_UP_VALUE_TEST                           (0xBBBB)
#define WDT_WSPR_UP_VALUE                                (0x4444)

/*****************************************************************************
**                DEFINES MATRIZ PINS
*****************************************************************************/
//p0
#define CM_conf_mdio                 							(0x948)
#define CM_conf_mdc                  							(0x94C)
#define CM_conf_spi0_sclk            							(0x950)
#define CM_conf_spi0_d0              							(0x954)
#define CM_conf_spi0_d1              							(0x958)
#define CM_conf_spi0_cs0             							(0x95C)
#define CM_conf_spi0_cs1             							(0x960)
#define CM_conf_ecap0_in_pwm0_out    							(0x964)
#define CM_conf_lcd_data12           							(0x8D0)
#define CM_conf_lcd_data13           							(0x8D4)
#define CM_conf_lcd_data14           							(0x8D8)
#define CM_conf_lcd_data15           							(0x8DC)
#define CM_conf_uart1_ctsn           							(0x978)
#define CM_conf_uart1_rtsn           							(0x97C)
#define CM_conf_uart1_rxd            							(0x980)
#define CM_conf_uart1_txd            							(0x984)
#define CM_conf_mii1_txd3            							(0x91C)
#define CM_conf_mii1_txd2            							(0x920)
#define CM_conf_usb0_drvvbus         							(0xA1C)
#define CM_conf_xdma_event_intr0     							(0x9B0)
#define CM_conf_xdma_event_intr1     							(0x9B4)
#define CM_conf_mii1_txd1            							(0x924)
#define CM_conf_gpmc_ad8             							(0x820)
#define CM_conf_gpmc_ad9             							(0x824)
#define CM_conf_gpmc_ad10            							(0x828)
#define CM_conf_gpmc_ad11            							(0x82C)
#define CM_conf_mii1_txd0            							(0x928)
#define CM_conf_rmii1_ref_clk        							(0x944)
#define CM_conf_gpmc_wait0           							(0x870)
#define CM_conf_gpmc_wpn             							(0x874)
//p1
#define CM_conf_gpmc_ad0             							(0x800)
#define CM_conf_gpmc_ad1             							(0x804)
#define CM_conf_gpmc_ad2             							(0x808)
#define CM_conf_gpmc_ad3             							(0x80C)
#define CM_conf_gpmc_ad4             							(0x810)
#define CM_conf_gpmc_ad5             							(0x814)
#define CM_conf_gpmc_ad6             							(0x818)
#define CM_conf_gpmc_ad7             							(0x81C)
#define CM_conf_uart0_ctsn           							(0x968)
#define CM_conf_uart0_rtsn           							(0x96C)
#define CM_conf_uart0_rxd            							(0x970)
#define CM_conf_uart0_txd            							(0x974)
#define CM_conf_gpmc_ad12            							(0x830)
#define CM_conf_gpmc_ad13            							(0x834)
#define CM_conf_gpmc_ad14            							(0x838)
#define CM_conf_gpmc_ad15            							(0x83C)
#define CM_conf_gpmc_a0              							(0x840)
#define CM_conf_gpmc_a1              							(0x844)
#define CM_conf_gpmc_a2              							(0x848)
#define CM_conf_gpmc_a3              							(0x84C)

#define CM_conf_gpmc_a4              							(0x850)
#define CM_conf_gpmc_a5              							(0x854)
#define CM_conf_gpmc_a6              							(0x858)
#define CM_conf_gpmc_a7              							(0x85C)
#define CM_conf_gpmc_a8              							(0x860)
#define CM_conf_gpmc_a9              							(0x864)
#define CM_conf_gpmc_a10             							(0x868)
#define CM_conf_gpmc_a11             							(0x86C)
#define CM_conf_gpmc_ben1            							(0x878)
#define CM_conf_gpmc_csn0            							(0x87C)
#define CM_conf_gpmc_csn1            							(0x880)
#define CM_conf_gpmc_csn2            							(0x884)
//p2
#define CM_conf_gpmc_csn3            							(0x888)
#define CM_conf_gpmc_clk             							(0x88C)
#define CM_conf_gpmc_advn_ale        							(0x890)
#define CM_conf_gpmc_oen_ren         							(0x894)
#define CM_conf_gpmc_wen             							(0x898)
#define CM_conf_gpmc_ben0_cle        							(0x89C)
#define CM_conf_lcd_data0            							(0x8A0)
#define CM_conf_lcd_data1            							(0x8A4)
#define CM_conf_lcd_data2            							(0x8A8)
#define CM_conf_lcd_data3            							(0x8AC)
#define CM_conf_lcd_data4            							(0x8B0)
#define CM_conf_lcd_data5            							(0x8B4)
#define CM_conf_lcd_data6            							(0x8B8)
#define CM_conf_lcd_data7            							(0x8BC)
#define CM_conf_lcd_data8            							(0x8C0)
#define CM_conf_lcd_data9            							(0x8C4)
#define CM_conf_lcd_data10           							(0x8C8)
#define CM_conf_lcd_data11           							(0x8CC)
#define CM_conf_mii1_rxd3            							(0x934)
#define CM_conf_mii1_rxd2            							(0x938)
#define CM_conf_mii1_rxd1            							(0x93C)
#define CM_conf_mii1_rxd0            							(0x940)
#define CM_conf_lcd_vsync            							(0x8E0)
#define CM_conf_lcd_hsync            							(0x8E4)
#define CM_conf_lcd_pclk             							(0x8E8)
#define CM_conf_lcd_ac_bias_en       							(0x8EC)
#define CM_conf_mmc0_dat3            							(0x8F0)
#define CM_conf_mmc0_dat2            							(0x8F4)
#define CM_conf_mmc0_dat1            							(0x8F8)
#define CM_conf_mmc0_dat0            							(0x8FC)
#define CM_conf_mmc0_clk             							(0x900)
#define CM_conf_mmc0_cmd             							(0x904)
//p3
#define CM_conf_mii1_col             							(0x908)
#define CM_conf_mii1_crs             							(0x90C)
#define CM_conf_mii1_rx_er           							(0x910)
#define CM_conf_mii1_tx_en           							(0x914)
#define CM_conf_mii1_rx_dv           							(0x918)
#define CM_conf_i2c0_sda             							(0x988)
#define CM_conf_i2c0_scl             							(0x98C)
#define CM_conf_emu0                 							(0x9E4)
#define CM_conf_emu1                 							(0x9E8)
#define CM_conf_mii1_tx_clk          							(0x92C)
#define CM_conf_mii1_rx_clk          							(0x930)
#define CM_conf_usb1_drvvbus         							(0xA34)
#define CM_conf_mcasp0_aclkx         							(0x990)
#define CM_conf_mcasp0_fsx           							(0x994)
#define CM_conf_mcasp0_axr0          							(0x998)
#define CM_conf_mcasp0_ahclkr        							(0x99C)
#define CM_conf_mcasp0_aclkr         							(0x9A0)
#define CM_conf_mcasp0_fsr           							(0x9A4)
#define CM_conf_mcasp0_axr1          							(0x9A8)
#define CM_conf_mcasp0_ahclkx        							(0x9AC)


/*-----------------------------------------------------------------------------
 * insert [pin, port], get CM_conf adress
 * Datasheet 4.3.2
 *-----------------------------------------------------------------------------*/
static const CONTROL_MODULE GPIO_CTRL_MODULE_ARRAY[32][4] = {
    //p0                          //p1                          //p2                          //p3
   {CM_conf_mdio                 ,CM_conf_gpmc_ad0             ,CM_conf_gpmc_csn3            ,CM_conf_mii1_col       },//.0
   {CM_conf_mdc                  ,CM_conf_gpmc_ad1             ,CM_conf_gpmc_clk             ,CM_conf_mii1_crs       },//.1
   {CM_conf_spi0_sclk            ,CM_conf_gpmc_ad2             ,CM_conf_gpmc_advn_ale        ,CM_conf_mii1_rx_er     },//.2
   {CM_conf_spi0_d0              ,CM_conf_gpmc_ad3             ,CM_conf_gpmc_oen_ren         ,CM_conf_mii1_tx_en     },//.3
   {CM_conf_spi0_d1              ,CM_conf_gpmc_ad4             ,CM_conf_gpmc_wen             ,CM_conf_mii1_rx_dv     },//.4
   {CM_conf_spi0_cs0             ,CM_conf_gpmc_ad5             ,CM_conf_gpmc_ben0_cle        ,CM_conf_i2c0_sda       },//.5
   {CM_conf_spi0_cs1             ,CM_conf_gpmc_ad6             ,CM_conf_lcd_data0            ,CM_conf_i2c0_scl       },//.6
   {CM_conf_ecap0_in_pwm0_out    ,CM_conf_gpmc_ad7             ,CM_conf_lcd_data1            ,CM_conf_emu0           },//.7
   {CM_conf_lcd_data12           ,CM_conf_uart0_ctsn           ,CM_conf_lcd_data2            ,CM_conf_emu1           },//.8
   {CM_conf_lcd_data13           ,CM_conf_uart0_rtsn           ,CM_conf_lcd_data3            ,CM_conf_mii1_tx_clk    },//.9
   {CM_conf_lcd_data14           ,CM_conf_uart0_rxd            ,CM_conf_lcd_data4            ,CM_conf_mii1_rx_clk    },//.10
   {CM_conf_lcd_data15           ,CM_conf_uart0_txd            ,CM_conf_lcd_data5            ,-1                     },//.11
   {CM_conf_uart1_ctsn           ,CM_conf_gpmc_ad12            ,CM_conf_lcd_data6            ,-1                     },//.12
   {CM_conf_uart1_rtsn           ,CM_conf_gpmc_ad13            ,CM_conf_lcd_data7            ,CM_conf_usb1_drvvbus   },//.13
   {CM_conf_uart1_rxd            ,CM_conf_gpmc_ad14            ,CM_conf_lcd_data8            ,CM_conf_mcasp0_aclkx   },//.14
   {CM_conf_uart1_txd            ,CM_conf_gpmc_ad15            ,CM_conf_lcd_data9            ,CM_conf_mcasp0_fsx     },//.15
   {CM_conf_mii1_txd3            ,CM_conf_gpmc_a0              ,CM_conf_lcd_data10           ,CM_conf_mcasp0_axr0    },//.16
   {CM_conf_mii1_txd2            ,CM_conf_gpmc_a1              ,CM_conf_lcd_data11           ,CM_conf_mcasp0_ahclkr  },//.17
   {CM_conf_usb0_drvvbus         ,CM_conf_gpmc_a2              ,CM_conf_mii1_rxd3            ,CM_conf_mcasp0_aclkr   },//.18
   {CM_conf_xdma_event_intr0     ,CM_conf_gpmc_a3              ,CM_conf_mii1_rxd2            ,CM_conf_mcasp0_fsr     },//.19
   {CM_conf_xdma_event_intr1     ,CM_conf_gpmc_a4              ,CM_conf_mii1_rxd1            ,CM_conf_mcasp0_axr1    },//.20
   {CM_conf_mii1_txd1            ,CM_conf_gpmc_a5              ,CM_conf_mii1_rxd0            ,CM_conf_mcasp0_ahclkx  },//.21
   {CM_conf_gpmc_ad8             ,CM_conf_gpmc_a6              ,CM_conf_lcd_vsync            ,-1                     },//.22
   {CM_conf_gpmc_ad9             ,CM_conf_gpmc_a7              ,CM_conf_lcd_hsync            ,-1                     },//.23
   {-1                           ,CM_conf_gpmc_a8              ,CM_conf_lcd_pclk             ,-1                     },//.24
   {-1                           ,CM_conf_gpmc_a9              ,CM_conf_lcd_ac_bias_en       ,-1                     },//.25
   {CM_conf_gpmc_ad10            ,CM_conf_gpmc_a10             ,CM_conf_mmc0_dat3            ,-1                     },//.26
   {CM_conf_gpmc_ad11            ,CM_conf_gpmc_a11             ,CM_conf_mmc0_dat2            ,-1                     },//.27
   {CM_conf_mii1_txd0            ,CM_conf_gpmc_ben1            ,CM_conf_mmc0_dat1            ,-1                     },//.28
   {CM_conf_rmii1_ref_clk        ,CM_conf_gpmc_csn0            ,CM_conf_mmc0_dat0            ,-1                     },//.29
   {CM_conf_gpmc_wait0           ,CM_conf_gpmc_csn1            ,CM_conf_mmc0_clk             ,-1                     },//.30
   {CM_conf_gpmc_wpn             ,CM_conf_gpmc_csn2            ,CM_conf_mmc0_cmd             ,-1                     },//.31
};


#endif //_INTERNAL_MACROS_