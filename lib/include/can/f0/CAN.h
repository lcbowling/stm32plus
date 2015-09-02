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
  struct CAN_Custom : CANPeripheral<TPinPackage,PERIPHERAL_CAN>,
                       Features... {

    CAN_Custom(const typename CANPeripheral<TPinPackage,PERIPHERAL_CAN>::Parameters& params)
      : CANPeripheral<TPinPackage,PERIPHERAL_CAN>(params),
        Features(static_cast<_CAN&>(*this))... {
    }
  };


  /*
   * Default pin package:
   */

  struct CANDefaultPinPackage {
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
  struct Can : CANPeripheral<CANDefaultPinPackage,PERIPHERAL_CAN>,
                Features... {

    Can(const Parameters& params)
      : CANPeripheral<CANDefaultPinPackage,PERIPHERAL_CAN>(params),
        Features(static_cast<_CAN&>(*this))... {
    }
  };


  struct CANRemap1PinPackage {
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
  struct Can_Remap1 : CANPeripheral<CANRemap1PinPackage,PERIPHERAL_CAN>,
                       Features... {

    Can_Remap1(const Parameters& params)
      : CANPeripheral<CANRemap1PinPackage,PERIPHERAL_CAN>(params),
        Features(static_cast<_CAN&>(*this))... {
    }
  };

  struct CANRemap2PinPackage {
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
  struct Can_Remap2 : CANPeripheral<CANRemap2PinPackage,PERIPHERAL_CAN>,
                       Features... {

    Can_Remap2(const Parameters& params)
      : CANPeripheral<CANRemap2PinPackage,PERIPHERAL_CAN>(params),
        Features(static_cast<_CAN&>(*this))... {
    }
  };
}
