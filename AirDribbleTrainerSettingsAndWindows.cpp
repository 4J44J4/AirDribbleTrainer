#include "pch.h"
#include "AirDribbleTrainer.h"
#include "ImGui/imgui_internal.h"
#include "wtypes.h"

int calibrationTimer = 110;
int floorSetting = 0;

void AirDribbleTrainer::RenderSettings()
{
	ImGui::TextUnformatted("To use the plugin, go to the bindings tab, and set binds for the commands 'AirDribbleTrainer::on_off', and 'AirDribbleTrainer::reset_ball'.");
	ImGui::TextUnformatted("The first turns the plugin on and off, and the second resets the plugin to the starting position.");
	ImGui::NewLine();
	ImGui::TextUnformatted("The plugin will occasionally make the game freak out when turning it on -- if that happens, just turn it off and then back on or just wait until it works.");
	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::SliderInt("Calibration", &calibrationTimer, 0, 360);
	ImGui::TextUnformatted(" ^ Controls how long the ball will match the player's movement when the ball gets reset above the player's car (120 = 1 second).");
	ImGui::NewLine();
	ImGui::SliderInt("Floor Reset", &floorSetting, 0, 1);
	ImGui::TextUnformatted(" ^ 0 means the ball will bounce up off the ground, and 1 means the ball will fall through the ground (much harder to control).");
}

int AirDribbleTrainer::CalibrationSetting()
{
	return calibrationTimer;
}

int AirDribbleTrainer::FloorResetSetting()
{
	return floorSetting;
}