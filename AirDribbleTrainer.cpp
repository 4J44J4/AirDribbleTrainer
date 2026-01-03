#include "pch.h"
#include "AirDribbleTrainer.h"
#include <cmath>


BAKKESMOD_PLUGIN(AirDribbleTrainer, "write a plugin description here", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

int calibration = 120;
bool activate = false;
int count = -1;
int resetTimer = 0;


void AirDribbleTrainer::onLoad()
{
	_globalCvarManager = cvarManager;

	cvarManager->registerNotifier("AirDribbleTrainer::on_off", [this](std::vector<std::string> args) {
		if (!activate)
		{
			activate = true;
			count = 20;
		}
		else
			activate = false;
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("AirDribbleTrainer::reset_ball", [this](std::vector<std::string> args) {
		if (activate)
			ManualReset();
		}, "", PERMISSION_ALL);
	
	this->loadHooks();
}

void AirDribbleTrainer::InitialSetup()
{
	//null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from controller, deactivating air dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from controller, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from controller, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from controller, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}

	car.SetLocation({0, -100, 500});
	ball.SetLocation({ 0, 0, 700 });
}

void AirDribbleTrainer::Controller()
{
	//null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from controller, deactivating air dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from controller, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from controller, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from controller, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}

	if (car.GetLocation().Z + 20 > ball.GetLocation().Z)
		ResetBall();
	if (abs(abs(car.GetLocation().Y) - abs(ball.GetLocation().Y)) > 500)
		ResetBall();
	if (abs(abs(car.GetLocation().X) - abs(ball.GetLocation().X)) > 500)
		ResetBall();

	if (car.GetLocation().Z > 1900 || ball.GetLocation().Z > 1900)
		HighReset();
	if (car.GetLocation().Z < 200 || ball.GetLocation().Z < 200)
		LowReset();
	if (car.GetLocation().Y > 4200 || ball.GetLocation().Y > 4200)
		FrontReset();
	if (car.GetLocation().Y < -4200 || ball.GetLocation().Y < -4200)
		BackReset();
	if (car.GetLocation().X > 3100 || ball.GetLocation().X > 3100)
		LeftReset();
	if (car.GetLocation().X < -3100 || ball.GetLocation().X < -3100)
		RightReset();

}

void AirDribbleTrainer::HighReset()
{
	//null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from HighReset, deactivating air dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from HighReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from HighReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from HighReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}

	car.SetLocation(Vector{ car.GetLocation().X, car.GetLocation().Y, car.GetLocation().Z - 900 });
	ball.SetLocation(Vector{ ball.GetLocation().X, ball.GetLocation().Y, ball.GetLocation().Z - 900 });
}

void AirDribbleTrainer::LowReset()
{
	//null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from LowReset, deactivating air dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from LowReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from LowReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from LowReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}

	if (FloorResetSetting() == 0)
	{
		car.SetLocation(Vector{ car.GetLocation().X, car.GetLocation().Y, car.GetLocation().Z + 50 });
		ball.SetLocation(Vector{ ball.GetLocation().X, ball.GetLocation().Y, ball.GetLocation().Z + 50 });
		car.SetVelocity(Vector{ car.GetVelocity().X, car.GetVelocity().Y, 1200 });
		ball.SetVelocity(Vector{ ball.GetVelocity().X, ball.GetVelocity().Y, 1200 });
		resetTimer = 15;
	}
	else
	{
		car.SetLocation(Vector{ car.GetLocation().X, car.GetLocation().Y, car.GetLocation().Z + 1000 });
		ball.SetLocation(Vector{ ball.GetLocation().X, ball.GetLocation().Y, ball.GetLocation().Z + 1000 });
	}
}

void AirDribbleTrainer::FrontReset()
{
	//null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from FrontReset, deactivating air dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from FrontReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from FrontReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from FrontReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}

	car.SetLocation(Vector{ car.GetLocation().X, car.GetLocation().Y - 7000, car.GetLocation().Z });
	ball.SetLocation(Vector{ ball.GetLocation().X, ball.GetLocation().Y - 7000, ball.GetLocation().Z });
}

void AirDribbleTrainer::BackReset()
{
	//null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from BackReset, deactivating air dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from BackReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from BackReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from BackReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}

	car.SetLocation(Vector{ car.GetLocation().X, car.GetLocation().Y + 7000, car.GetLocation().Z });
	ball.SetLocation(Vector{ ball.GetLocation().X, ball.GetLocation().Y + 7000, ball.GetLocation().Z });
}

void AirDribbleTrainer::LeftReset()
{
	//null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from LeftReset, deactivating air dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from LeftReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from LeftReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from LeftReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}

	car.SetLocation(Vector{ car.GetLocation().X - 5000, car.GetLocation().Y, car.GetLocation().Z });
	ball.SetLocation(Vector{ ball.GetLocation().X - 5000, ball.GetLocation().Y, ball.GetLocation().Z });
}

void AirDribbleTrainer::RightReset()
{
	//null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from RightReset, deactivating air dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from RightReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from RightReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from RightReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}

	car.SetLocation(Vector{ car.GetLocation().X + 5000, car.GetLocation().Y, car.GetLocation().Z });
	ball.SetLocation(Vector{ ball.GetLocation().X + 5000, ball.GetLocation().Y, ball.GetLocation().Z });
}

void AirDribbleTrainer::ResetBall()
{
	//null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from ResetBall, deactivating air dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from ResetBall, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from ResetBall, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from ResetBall, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}

	ball.SetLocation(Vector{ car.GetLocation().X + float(car.GetVelocity().X / 10.0), car.GetLocation().Y + float(car.GetVelocity().Y / 10.0), car.GetLocation().Z + 300 });
	ball.SetVelocity(car.GetVelocity());
	if (abs(abs(car.GetVelocity().X) + abs(car.GetVelocity().Y)) > 1800)
	{
		car.SetVelocity({ float(car.GetVelocity().X / 2.0), float(car.GetVelocity().Y / 2.0), 700.0f });
		ball.SetVelocity({ float(ball.GetVelocity().X / 2.0), float(ball.GetVelocity().Y / 2.0), 700.0f });
	}
	else
	{
		car.SetVelocity(Vector{ car.GetVelocity().X, car.GetVelocity().Y, 700 });
		ball.SetVelocity(Vector{ ball.GetVelocity().X, ball.GetVelocity().Y, 700 });
	}
	car.SetAngularVelocity({ 0.0f, 0.0f, 0.0f }, false);
	//if (car.GetVelocity().X > 0)
		car.SetRotation({ 12000, int(std::atan2(car.GetVelocity().Y, car.GetVelocity().X) * 180 / 3.14159 * 182.0444444), 0 });
	//else
		//car.SetRotation({ 16384 + 4000, int(std::atan2(car.GetVelocity().X, car.GetVelocity().Y)), int(std::atan2(car.GetVelocity().X, car.GetVelocity().Y)) });
	resetTimer = CalibrationSetting();
}

void AirDribbleTrainer::ResetCalibration()
{
	//null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from ResetCalibration, deactivating air dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from ResetCalibration, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from ResetCalibration, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from ResetCalibration, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}

	ball.SetVelocity(car.GetVelocity());
}

void AirDribbleTrainer::ManualReset()
{
	//null checks and variable initialization
	if (!gameWrapper->IsInFreeplay())
	{
		LOG("user is not in freeplay from ManualReset, deactivating air dribble trainer");
		activate = false;
		return;
	}
	CarWrapper car = gameWrapper->GetLocalCar(); {
		if (!car)
		{
			LOG("no car from ManualReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	ServerWrapper server = gameWrapper->GetCurrentGameState(); {
		if (!server)
		{
			LOG("no server from ManualReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}
	BallWrapper ball = server.GetBall(); {
		if (!ball)
		{
			LOG("no ball from ManualReset, deactivating air dribble trainer");
			activate = false;
			return;
		}
	}

	car.SetLocation(Vector{0, -100, 220});
	car.SetRotation(Rotator{12000, 16384, 0});
	ball.SetLocation(Vector{0, 0, 500});
	car.SetVelocity(Vector{0, 0, 1000});
	ball.SetVelocity(Vector{ 0, 0, 1000 });
	car.SetAngularVelocity({0, 0 ,0}, false);
	ball.SetAngularVelocity({ 0, 0 ,0 }, false);

	resetTimer = 0;
}

void AirDribbleTrainer::loadHooks()
{
	gameWrapper->HookEvent("Function TAGame.EngineShare_TA.EventPostPhysicsStep",
		[this](std::string eventName) {
			if (activate)
			{
				if (count > 0)
					InitialSetup();
				if (count == 0)
					ManualReset();
				if (count > -1)
					count--;
				if (count == -1)
					Controller();
				if (resetTimer > 0)
				{
					ResetCalibration();
					resetTimer--;
				}
			}
		});

	gameWrapper->HookEvent("Function TAGame.FreeplayCommands_TA.ResetTraining",
		[this](std::string eventName) {
			activate = false;
		});
}