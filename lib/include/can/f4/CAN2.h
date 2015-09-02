/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013,2014 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once


namespace stm32plus {

  /**
   * Generic class for any pin package
   */

  template<class TPinPackage,class... Features>
  struct CAN2_Custom : CANPeripheral<TPinPackage,PERIPHERAL_CAN2>,
                       Features... {

    CAN2_Custom(const typename CANPeripheral<TPinPackage,PERIPHERAL_CAN2>::Parameters& params)
      : CANPeripheral<TPinPackage,PERIPHERAL_CAN2>(params),
        Features(static_cast<CAN&>(*this))... {
    }
  };


  /*
   * Default pin package:
   */

  struct CAN2DefaultPinPackage {
    enum {
      Port_RX = GPIOB_BASE,
      Port_TX = GPIOB_BASE,

      Pin_RX  = GPIO_Pin_12,
      Pin_TX  = GPIO_Pin_13
    };
  };


  /**
   * Convenience class to match the F1 pin for pin.
   */

  template<class... Features>
  struct Can2 : CANPeripheral<CAN2DefaultPinPackage,PERIPHERAL_CAN2>,
                Features... {

    Can2(const Parameters& params)
      : CANPeripheral<CAN2DefaultPinPackage,PERIPHERAL_CAN2>(params),
        Features(static_cast<CAN&>(*this))... {
    }
  };


  struct CAN2RemapPinPackage {
    enum {
      Port_RX = GPIOB_BASE,
      Port_TX = GPIOB_BASE,

      Pin_RX  = GPIO_Pin_5,
      Pin_TX  = GPIO_Pin_6
    };
  };


  /**
   * Convenience class to match the F1 pin for pin.
   */

  template<class... Features>
  struct Can2_Remap : CANPeripheral<CAN2RemapPinPackage,PERIPHERAL_CAN2>,
                       Features... {

    Can2_Remap(const Parameters& params)
      : CANPeripheral<CAN2RemapPinPackage,PERIPHERAL_CAN2>(params),
        Features(static_cast<CAN&>(*this))... {
    }
  };

}
