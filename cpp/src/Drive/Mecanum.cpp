#include "ctre/phoenix/Drive/Mecanum.h"
#include "ctre/phoenix/MotorControl/GroupMotorControllers.h"
#include "HAL/DriverStation.h"
#include <cmath>

namespace CTRE { namespace Drive {

Mecanum::Mecanum(CTRE::MotorControl::IMotorController *m1, CTRE::MotorControl::IMotorController *m2,
		CTRE::MotorControl::IMotorController *m3, CTRE::MotorControl::IMotorController *m4)
{
	CTRE::MotorControl::GroupMotorControllers::Register(m1);

	CTRE::Mechanical::Gearbox *temp1 = new CTRE::Mechanical::Gearbox(m1);
	CTRE::Mechanical::Gearbox *temp2 = new CTRE::Mechanical::Gearbox(m2);
	CTRE::Mechanical::Gearbox *temp3 = new CTRE::Mechanical::Gearbox(m3);
	CTRE::Mechanical::Gearbox *temp4 = new CTRE::Mechanical::Gearbox(m4);

	_1 = temp1;
	_2 = temp2;
	_3 = temp3;
	_4 = temp4;
}
Mecanum::Mecanum(CTRE::Mechanical::Gearbox *m1, CTRE::Mechanical::Gearbox *m2,
		CTRE::Mechanical::Gearbox *m3, CTRE::Mechanical::Gearbox *m4)
{
	CTRE::MotorControl::GroupMotorControllers::Register(m1->GetMaster());

	_1 = m1;
	_2 = m2;
	_3 = m3;
	_4 = m4;
}
void Mecanum::Set(Styles::Basic mode, float forward, float turn){
	Drive(mode, forward, 0, turn);
}
void Mecanum::Set(Styles::Basic mode, float forward, float strafe, float turn){
	Drive(mode, forward, strafe, turn);
}
void Mecanum::SetVoltageRampRate(float rampRate){
	_1->SetVoltageRampRate(rampRate);
	_2->SetVoltageRampRate(rampRate);
	_3->SetVoltageRampRate(rampRate);
	_4->SetVoltageRampRate(rampRate);
}
void Mecanum::SetVoltageCompensationRampRate(float rampRate){
    _1->SetVoltageCompensationRate(rampRate);
    _2->SetVoltageCompensationRate(rampRate);
    _3->SetVoltageCompensationRate(rampRate);
    _4->SetVoltageCompensationRate(rampRate);
}
void Mecanum::ConfigPeakPercentOutputVoltage(float forwardVoltage, float reverseVoltage){
    _1->ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
    _2->ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
    _3->ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
    _4->ConfigPeakOutputVoltage(forwardVoltage, reverseVoltage);
}
void Mecanum::ConfigNominalPercentOutputVoltage(float forwardVoltage, float reverseVoltage){
    _1->ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
    _2->ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
    _3->ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
    _4->ConfigNominalOutputVoltage(forwardVoltage, reverseVoltage);
}
void Mecanum::Drive(Styles::Basic mode, float forward, float strafe, float turn){float leftFrnt_throt = (forward + strafe + turn); // left front moves positive for forward, strafe-right, turn-right
	float leftRear_throt = (forward - strafe + turn); // left rear moves positive for forward, strafe-left, turn-right
	float rghtFrnt_throt = (forward - strafe - turn); // right front moves positive for forward, strafe-left, turn-left
	float rghtRear_throt = (forward + strafe - turn); // right rear moves positive for forward, strafe-right, turn-left

	/* Set control mode */
	if(mode == Styles::Basic::PercentOutputBasic)
	{
		_1->SetControlMode(CTRE::MotorControl::ControlMode::BasicControlMode::kPercentVbusBasic);
		_2->SetControlMode(CTRE::MotorControl::ControlMode::BasicControlMode::kPercentVbusBasic);
		_3->SetControlMode(CTRE::MotorControl::ControlMode::BasicControlMode::kPercentVbusBasic);
		_4->SetControlMode(CTRE::MotorControl::ControlMode::BasicControlMode::kPercentVbusBasic);
	}
	else if(mode == Styles::Basic::VoltageBasic)
	{
		_1->SetControlMode(CTRE::MotorControl::ControlMode::BasicControlMode::kVoltageBasic);
		_2->SetControlMode(CTRE::MotorControl::ControlMode::BasicControlMode::kVoltageBasic);
		_3->SetControlMode(CTRE::MotorControl::ControlMode::BasicControlMode::kVoltageBasic);
		_4->SetControlMode(CTRE::MotorControl::ControlMode::BasicControlMode::kVoltageBasic);
	}

	/* Set motors */
	_1->Set(leftFrnt_throt);
	_2->Set(leftRear_throt);
	_3->Set(rghtFrnt_throt);
	_4->Set(rghtRear_throt);
}

}}
