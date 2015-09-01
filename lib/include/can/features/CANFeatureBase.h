/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013,2014 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#pragma once


namespace stm32plus {


  /**
   * Base class for CAN features
   */

  class CANFeatureBase {
    protected:
      CAN& _can;

    public:
      CANFeatureBase(CAN& can);
      operator CAN&();
  };


  /**
   * Constructor
   * @param can
   */

  inline CANFeatureBase::CANFeatureBase(CAN& can)
    : _can(can) {
  }


  /**
   * Cast to CAN reference
   */

  inline CANFeatureBase::operator CAN&() {
    return _can;
  }
}
