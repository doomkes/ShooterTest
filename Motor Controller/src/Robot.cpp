#include <Joystick.h>
#include <SampleRobot.h>
#include <Talon.h>
#include <Timer.h>
#include <cantalon.h>



/**
 * This sample program shows how to control a motor using a joystick. In the
 * operator control part of the program, the joystick is read and the value is
 * written to the motor.
 *
 * Joystick analog values range from -1 to 1 and speed controller inputs as
 * range from -1 to 1 making it easy to work together. The program also delays a
 * short time in the loop to allow other threads to run. This is generally a
 * good idea, especially since the joystick values are only transmitted from the
 * Driver Station once every 20ms.
 */
class Robot: public frc::SampleRobot {
public:

	void OperatorControl() {

		static double speed1=1300,speed2=1300,voltage =1.0;
		static bool dir, test;
		while (IsOperatorControl() && IsEnabled()) {
			speed1=SmartDashboard::GetNumber("RPM1", 200);
			speed2=SmartDashboard::GetNumber("RPM2", 200);
			test=SmartDashboard::GetBoolean("TEST", 1);
			dir = SmartDashboard::GetBoolean("DIR", 0);
			voltage =SmartDashboard::GetNumber("VOLTS", 0.5);
			if(true)
			{
				if (dir){
					m_shoot1.Set(speed1);
					m_shoot2.Set(-speed1);
					m_pa1.Set(speed2);
					m_pa2.Set(-speed2);
				}
				else{
					m_shoot1.Set(-speed1);
					m_shoot2.Set(speed1);
					m_pa1.Set(-speed2);
					m_pa2.Set(speed2);
				}
			}
			else // indexer
			{
				m_pa2.SetControlMode(CANSpeedController::kPercentVbus);
				m_pa2.Set(voltage);

			}
			speed1 = m_shoot1.GetSpeed();
			speed2 = m_shoot2.GetSpeed();
			SmartDashboard::PutNumber("Wheel1", speed1);
			SmartDashboard::PutNumber("Wheel2", speed2);
			printf("speed1: %4.0f  speed2: %4.0f\n", speed1,speed2);
			frc::Wait(kUpdatePeriod);  // Wait 5ms for the next update.
		}
	}
	Robot() :
		m_shoot1(1), m_shoot2(2), m_pa1(3), m_pa2(4)
	{

	}

	void RobotInit() override {
		m_shoot1.SetControlMode(CANSpeedController::kVoltage);
		m_shoot2.SetControlMode(CANSpeedController::kVoltage);

		m_shoot1.SetFeedbackDevice(CANTalon::QuadEncoder);
		m_shoot1.ConfigNominalOutputVoltage(+0.0, -0.0);
		m_shoot1.ConfigPeakOutputVoltage(+12.0, -12.0);
		m_shoot1.SetControlMode(CANSpeedController::kSpeed);
		m_shoot1.SetSensorDirection(true);
		m_shoot1.SetInverted(false);
		m_shoot1.SetIzone(200);
		m_shoot1.ConfigEncoderCodesPerRev(20);
		m_shoot1.SetPID(8,0.005,0);
		m_shoot1.SetF(1.5);
		m_shoot1.SetVoltageRampRate(50);

		m_shoot2.SetFeedbackDevice(CANTalon::QuadEncoder);
		m_shoot2.ConfigNominalOutputVoltage(+0.0, -0.0);
		m_shoot2.ConfigPeakOutputVoltage(+12.0, -12.0);
		m_shoot2.SetControlMode(CANSpeedController::kSpeed);
		m_shoot2.SetSensorDirection(true);
		m_shoot2.SetInverted(false);
		m_shoot2.SetIzone(200);
		m_shoot2.ConfigEncoderCodesPerRev(20);
		m_shoot2.SetPID(8,0.005,0);
		m_shoot2.SetF(1.5);//(16.620);
		m_shoot2.SetVoltageRampRate(50);

		m_pa1.SetControlMode(CANSpeedController::kVoltage);
		m_pa2.SetControlMode(CANSpeedController::kVoltage);

		m_pa1.SetFeedbackDevice(CANTalon::QuadEncoder);
		m_pa1.ConfigNominalOutputVoltage(+0.0, -0.0);
		m_pa1.ConfigPeakOutputVoltage(+12.0, -12.0);
		m_pa1.SetControlMode(CANSpeedController::kSpeed);
		m_pa1.SetSensorDirection(true);
		m_pa1.SetInverted(true);
		m_pa1.SetIzone(200);
		m_pa1.ConfigEncoderCodesPerRev(20);
		m_pa1.SetPID(4,0.001,0);
		m_pa1.SetF(1.5);
		m_pa1.SetVoltageRampRate(50);

		m_pa2.SetFeedbackDevice(CANTalon::QuadEncoder);
		m_pa2.ConfigNominalOutputVoltage(+0.0, -0.0);
		m_pa2.ConfigPeakOutputVoltage(+12.0, -12.0);
		m_pa2.SetControlMode(CANSpeedController::kSpeed);
		m_pa2.SetSensorDirection(false);
		m_pa2.SetInverted(false);
		m_pa2.SetIzone(200);
		m_pa2.ConfigEncoderCodesPerRev(20);
		m_pa2.SetPID(4,0.001,0);
		m_pa2.SetF(1.5);//(16.620);
		m_pa2.SetVoltageRampRate(50);
		SmartDashboard::PutNumber("RPM1", 600);
	    SmartDashboard::PutNumber("RPM2", 600);
	    SmartDashboard::PutBoolean("DIR", 0);
	    SmartDashboard::PutBoolean("TEST", 0);
	    SmartDashboard::PutNumber("VOLTS", .5);

	}

private:

	CANTalon m_shoot1, m_shoot2, m_pa1, m_pa2;
	// Update every 0.005 seconds/5 milliseconds.
	static constexpr double kUpdatePeriod = 0.005;
};

START_ROBOT_CLASS(Robot)
