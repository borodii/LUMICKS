#include "Controller.h"
#include "IProtocol.h"

Controller::Controller()
  : m_is_emitting(false)
  , m_laser_power(-1)
  , m_silly_mode(false)
  , m_time_point(std::chrono::system_clock::now())
{

}

bool Controller::StartEmission()
{
  _UpdateTimePoint();
  if (m_is_emitting)
    return false;

  m_is_emitting = true;
  return true;
}

bool Controller::StopEmission()
{
  if (!m_is_emitting)
    return false;

  m_is_emitting = false;
  return true;
}

int Controller::GetEmissionStatus() const
{
  _CheckTimePointAndDisableEmissionIfNecessary();
  return m_is_emitting ? 1: 0;
}

bool Controller::KeepSignalAlive()
{
  _CheckTimePointAndDisableEmissionIfNecessary();
  return m_is_emitting;
}

int Controller::GetLaserPower() const
{
  if (!_CheckTimePointAndDisableEmissionIfNecessary())
    return false;

  return m_laser_power;
}

bool Controller::SetLaserPower(int i_laser_power)
{
  if (!_CheckTimePointAndDisableEmissionIfNecessary())
    return false;

  if (i_laser_power < 1 || i_laser_power >100)
    return false;

  m_laser_power = i_laser_power;
  return true;
}

bool Controller::DisableSillyMode()
{
  if (!_CheckTimePointAndDisableEmissionIfNecessary())
    return false;

  m_silly_mode = false;
  return true;
}

bool Controller::EnableSillyMode()
{
  if (!_CheckTimePointAndDisableEmissionIfNecessary())
    return false;

  m_silly_mode = true;
  return true;
}

bool Controller::IsSillyMode() const
{
  if (!_CheckTimePointAndDisableEmissionIfNecessary())
    return false;

  return m_silly_mode;
}

bool Controller::_CheckTimePointAndDisableEmissionIfNecessary() const
{
  if (m_is_emitting)
    if (std::chrono::system_clock::now() - m_time_point > std::chrono::seconds(5))
    {
      m_is_emitting = false;
      return false;
    }

  _UpdateTimePoint();
  return true;
}

void Controller::_UpdateTimePoint() const
{
  m_time_point = std::chrono::system_clock::now();
}
