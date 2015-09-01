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
  struct CAN1_Custom : CANPeripheral<TPinPackage,PERIPHERAL_CAN1>,
                       Features... {

    CAN1_Custom(const typename CANPeripheral<TPinPackage,PERIPHERAL_CAN1>::Parameters& params)
      : CANPeripheral<TPinPackage,PERIPHERAL_CAN1>(params),
        Features(static_cast<CAN&>(*this))... {
    }
  };


  /*
   * Default pin package:
   */

  struct CAN1DefaultPinPackage {
    enum {
      Port_RX = GPIOA_BASE,
      Port_TX = GPIOA_BASE,

      Pin_RX  = GPIO_Pin_11,
      Pin_TX  = GPIO_Pin_12
    };
  };


  /**
   * Convenience class to match the F1 pin for pin.
   */

  template<class... Features>
  struct Can1 : CANPeripheral<CAN1DefaultPinPackage,PERIPHERAL_CAN1>,
                Features... {

    Can1(const Parameters& params)
      : CANPeripheral<CAN1DefaultPinPackage,PERIPHERAL_CAN1>(params),
        Features(static_cast<CAN&>(*this))... {
    }
  };


  struct CAN1Remap1PinPackage {
    enum {
      Port_RX = GPIOB_BASE,
      Port_TX = GPIOB_BASE,

      Pin_RX  = GPIO_Pin_8,
      Pin_TX  = GPIO_Pin_9
    };
  };


  /**
   * Convenience class to match the F1 pin for pin.
   */

  template<class... Features>
  struct Can1_Remap1 : CANPeripheral<CAN1Remap1PinPackage,PERIPHERAL_CAN1>,
                       Features... {

    Can1_Remap1(const Parameters& params)
      : CANPeripheral<CAN1Remap1PinPackage,PERIPHERAL_CAN1>(params),
        Features(static_cast<CAN&>(*this))... {
    }
  };

  struct CAN1Remap2PinPackage {
    enum {
      Port_RX = GPIOD_BASE,
      Port_TX = GPIOD_BASE,

      Pin_RX  = GPIO_Pin_0,
      Pin_TX  = GPIO_Pin_1
    };
  };


  /**
   * Convenience class to match the F1 pin for pin.
   */

  template<class... Features>
  struct Can1_Remap2 : CANPeripheral<CAN1Remap2PinPackage,PERIPHERAL_CAN1>,
                       Features... {

    Can1_Remap2(const Parameters& params)
      : CANPeripheral<CAN1Remap2PinPackage,PERIPHERAL_CAN1>(params),
        Features(static_cast<CAN&>(*this))... {
    }
  };
}
