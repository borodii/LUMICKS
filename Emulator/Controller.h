#pragma once

#include <chrono>

#include "IController.h"

class IProtocol;

/**
 * Implements some exact version of controller that operate with different powerful lasers.\n
 * [Details...](InternalDocumentation\...\Controllers\ControllerV10.pdf)
 * \image html Images\ControllerV10.png
 */

class Controller : public IController{
public:
  explicit Controller();
  ~Controller() = default;

  Controller(const Controller& i_other) = delete;
  Controller& operator=(const Controller& i_other) = delete;

  virtual bool StartEmission() override;
  virtual bool StopEmission() override;
  virtual int GetEmissionStatus() const override;

  virtual bool KeepSignalAlive() override;

  virtual int GetLaserPower() const override;
  virtual bool SetLaserPower(int i_laser_power) override;

  virtual bool DisableSillyMode() override;
  virtual bool EnableSillyMode() override;
  virtual bool IsSillyMode() const override;

private:
  bool _CheckTimePointAndDisableEmissionIfNecessary() const;
  void _UpdateTimePoint() const;

private:
  mutable bool m_is_emitting;
  int m_laser_power;
  bool m_silly_mode;
  mutable std::chrono::time_point<std::chrono::system_clock> m_time_point;
};