/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013,2014 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once


namespace stm32plus {

  /**
   * CAN peripheral base class
   */

  template<class TPinPackage,PeripheralName TPeripheralName>
  class CANPeripheral : public _CAN {

    public:

      /**
       * Parameters class
       */

      struct Parameters {
        uint8_t can_sjw;
        uint8_t can_bs1;
        uint8_t can_bs2;
        uint16_t can_prescaler;

        /**
         * Constructor, set suitable defaults for master mode. Generally you'll want to set at
         * least can_baudRatePrescaler to a suitable speed and check that the other defaults are OK.
         */

        Parameters() {
          can_sjw = CAN_SJW_1tq;
          can_bs1 = CAN_BS1_6tq;
          can_bs2 = CAN_BS2_7tq;
          can_prescaler=7-1;
        }
      };

    protected:
      CANPeripheral(const Parameters& params);
      ~CANPeripheral();
  };


  /**
   * Constructor
   * @param params The initialisation parameters
   */

  template<class TPinPackage,PeripheralName TPeripheralName>
  inline CANPeripheral<TPinPackage,TPeripheralName>::CANPeripheral(const Parameters& params)
    : _CAN((CAN_TypeDef *)PeripheralTraits<TPeripheralName>::PERIPHERAL_BASE) {

    CAN_InitTypeDef init;

    // deInit CAN

    deInit();

    // clocks on first before any features get initialised

    ClockControl<TPeripheralName>::On();

    // and next the GPIO pins, also before any features get initialised

    CANPinInitialiser<TPinPackage,TPeripheralName>::initialise();

    // initialise the peripheral

    CAN_StructInit(&init);

    init.CAN_SJW = params.can_sjw;
    init.CAN_BS1 = params.can_bs1;
    init.CAN_BS2 = params.can_bs2;
    init.CAN_Prescaler = params.can_prescaler;

    CAN_Init(_peripheralAddress,&init);

  }


  /**
   * Destructor
   */

  template<class TPinPackage,PeripheralName TPeripheralName>
  inline CANPeripheral<TPinPackage,TPeripheralName>::~CANPeripheral() {

    // clocks off

    ClockControl<TPeripheralName>::Off();
  }
}
