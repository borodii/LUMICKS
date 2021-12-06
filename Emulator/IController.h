#pragma once
#include <string>

class IProtocol;

//Common interface for controllers that operate with different powerful lasers
class IController {
public:
  virtual ~IController() = default;
  virtual bool StartEmission() = 0;
  virtual bool StopEmission() = 0;
  virtual int GetEmissionStatus() const = 0;

  virtual bool KeepSignalAlive() = 0;

  virtual int GetLaserPower() const = 0;
  virtual bool SetLaserPower(int i_laser_power) = 0;

  virtual bool DisableSillyMode() = 0;
  virtual bool EnableSillyMode() = 0;
  virtual bool IsSillyMode() const = 0;
};
