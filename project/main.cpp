/*
----------------------------------------------------------------------------------------------------------
	File: main.cpp
	Author: Ozzie Mercado
	Created: September 25, 2020
	Modified: November 23, 2020
	Description: Entry point for the application. This demo was created to show off some of the features
		I worked on for Gateware 1.2a like being able to set the window icon at runtime, locking the size 
		of a window, and Xbox One controller support on all platforms.
----------------------------------------------------------------------------------------------------------
*/

// Add the Gateware libraries we intend to use.
#define GATEWARE_ENABLE_CORE // Needed by all libraries.
#define GATEWARE_ENABLE_SYSTEM // Needed for the window and graphics.
#define GATEWARE_ENABLE_GRAPHICS
#define GATEWARE_ENABLE_INPUT

// Turn off the libraries we don't intend to use.
#define GATEWARE_DISABLE_GLOG
#define GATEWARE_DISABLE_GFILE
#define GATEWARE_DISABLE_GOPENGLSURFACE
#define GATEWARE_DISABLE_GVULKANSURFACE
#define GATEWARE_DISABLE_GDIRECTX11SURFACE
#define GATEWARE_DISABLE_GDIRECTX12SURFACE
#define GATEWARE_DISABLE_BUFFEREDGINPUT
#define GATEWARE_DISABLE_GINPUT

// Now we can include the headers.
#include "Gateware/Gateware.h"
#include "Assets/AssetIconPinwheel.h"
#include "Code/Face.h"

namespace
{
	// Desired size of the client area of the window.
	constexpr unsigned int DISPLAY_WIDTH = 800;
	constexpr unsigned int DISPLAY_HEIGHT = 600;
	constexpr unsigned int DISPLAY_PIXEL_COUNT = DISPLAY_WIDTH * DISPLAY_HEIGHT;

	// Used to describe the controller number being polled.
	constexpr unsigned int CONTROLLER_ONE = 0;

	// Buffer for drawing.
	unsigned int displayBuffer[DISPLAY_WIDTH * DISPLAY_HEIGHT];
}

inline void PrintError(const char* _message);

int main(int argc, char** argv)
{
	GW::SYSTEM::GWindow window;

	if (+window.Create(100, 100, DISPLAY_WIDTH, DISPLAY_HEIGHT, GW::SYSTEM::GWindowStyle::WINDOWEDLOCKED)) // + operator returns true if the operation is successful.
	{
		window.SetWindowName("GATEWARE PUPPET - by Ozzie Mercado");
		window.SetIcon(PINWHEEL_WIDTH, PINWHEEL_HEIGHT, PINWHEEL_PIXELS);

		GW::GRAPHICS::GRasterSurface raster;

		if (+raster.Create(window))
		{
			GW::INPUT::GController controllerHandler;

			if (-controllerHandler.Create()) // - operator returns true if the operation is unsuccessful.
				PrintError("Failed to setup the controller handler. The program will run, but will not take controller input.");

			bool freezeFace = false;
			bool freezeFaceButtonReset = true; // Used to required the freezeFace button to be reset before freezeFace can change state again.
			bool controllerConnectionEstablished = false; // Used for changes in controller connection.
			Face face(DISPLAY_WIDTH, DISPLAY_HEIGHT);

			// Run loop
			while (+window.ProcessWindowEvents())
			{
				// Update the face based on controller input
				bool controllerConnected;
				if (+controllerHandler.IsConnected(CONTROLLER_ONE, controllerConnected) && controllerConnected) // This will fail safely if controllerHandler was not setup previously.
				{
					if (!controllerConnectionEstablished) // Change the color of the face if the controller just connected.
					{						
						face.SetColor(Face::Color::Purple);
						controllerConnectionEstablished = true;
					}

					float pollValue = 0;

					if (freezeFace)
					{
						// Check the state of the freezeFace button. Also make sure the button has been released since the last time it was pressed.
						if (+controllerHandler.GetState(CONTROLLER_ONE, G_SELECT_BTN, pollValue) && static_cast<bool>(pollValue))
						{
							if (freezeFaceButtonReset) // If the freezeFace button is pressed after the button reset, change the color of the face and unfreeze.
							{
								face.SetColor(Face::Color::Purple);
								freezeFace = false;
								freezeFaceButtonReset = false;
							}
						}
						else
							freezeFaceButtonReset = true;
					}
					else // If face is not frozen
					{
						if (+controllerHandler.GetState(CONTROLLER_ONE, G_SELECT_BTN, pollValue) && static_cast<bool>(pollValue))
						{
							if (freezeFaceButtonReset)
							{
								face.SetColor(Face::Color::Blue);
								freezeFace = true;
								freezeFaceButtonReset = false;
							}
						}
						else
							freezeFaceButtonReset = true;

						// Update face color on NWSE buttons
						if (+controllerHandler.GetState(CONTROLLER_ONE, G_NORTH_BTN, pollValue) && static_cast<bool>(pollValue))
							face.SetColor(Face::Color::Orange);
						else if (+controllerHandler.GetState(CONTROLLER_ONE, G_SOUTH_BTN, pollValue) && static_cast<bool>(pollValue))
							face.SetColor(Face::Color::Green);
						else if (+controllerHandler.GetState(CONTROLLER_ONE, G_WEST_BTN, pollValue) && static_cast<bool>(pollValue))
							face.SetColor(Face::Color::Purple);
						else if (+controllerHandler.GetState(CONTROLLER_ONE, G_EAST_BTN, pollValue) && static_cast<bool>(pollValue))
							face.SetColor(Face::Color::Red);

						// Update mouth based on D-pad
						if (+controllerHandler.GetState(CONTROLLER_ONE, G_DPAD_UP_BTN, pollValue) && static_cast<bool>(pollValue))
							face.SetMouth(Face::Expression::Smile);
						else if (+controllerHandler.GetState(CONTROLLER_ONE, G_DPAD_DOWN_BTN, pollValue) && static_cast<bool>(pollValue))
							face.SetMouth(Face::Expression::Sad);
						else if (+controllerHandler.GetState(CONTROLLER_ONE, G_DPAD_LEFT_BTN, pollValue) && static_cast<bool>(pollValue))
							face.SetMouth(Face::Expression::Happy);
						else if (+controllerHandler.GetState(CONTROLLER_ONE, G_DPAD_RIGHT_BTN, pollValue) && static_cast<bool>(pollValue))
							face.SetMouth(Face::Expression::Suprise);

						// Update eyelids based on triggers
						if (+controllerHandler.GetState(CONTROLLER_ONE, G_LEFT_TRIGGER_AXIS, pollValue))
							face.AdjustEyelid(pollValue, Face::Side::Left);

						if (+controllerHandler.GetState(CONTROLLER_ONE, G_RIGHT_TRIGGER_AXIS, pollValue))
							face.AdjustEyelid(pollValue, Face::Side::Right);

						// Move eyebrows based on shoulder buttons
						if (+controllerHandler.GetState(CONTROLLER_ONE, G_LEFT_SHOULDER_BTN, pollValue))
							face.MoveEyebrow(-pollValue, Face::Side::Left);

						if (+controllerHandler.GetState(CONTROLLER_ONE, G_RIGHT_SHOULDER_BTN, pollValue))
							face.MoveEyebrow(-pollValue, Face::Side::Right);

						// Move eyes based on right thumbstick
						float stickX = 0.0f, stickY = 0.0f;

						if (+controllerHandler.GetState(CONTROLLER_ONE, G_RY_AXIS, pollValue))
							stickY = -pollValue; // Note: Axis is flipped to bring it into the raster's coordinate system.

						if (+controllerHandler.GetState(CONTROLLER_ONE, G_RX_AXIS, pollValue))
							stickX = pollValue;

						face.MoveEye(stickX, stickY, Face::Side::Left);
						face.MoveEye(stickX, stickY, Face::Side::Right);
					}
				}
				else if (controllerConnectionEstablished) // Change the color of the face if the controller was just disconnected.
				{					
					face.SetColor(Face::Color::Violet);
					controllerConnectionEstablished = false;
				}

				// Draw the updated face to the display buffer.
				face.Render(displayBuffer, DISPLAY_WIDTH, DISPLAY_HEIGHT);

				// Draw the buffer to the screen.
				raster.SmartUpdateSurface(displayBuffer, DISPLAY_PIXEL_COUNT, DISPLAY_WIDTH, GW::GRAPHICS::ALIGN_X_CENTER | GW::GRAPHICS::ALIGN_Y_CENTER);
			}
		}
		else
			PrintError("Failed to create the raster. Exiting program.");
	}
	else
		PrintError("Failed to create the window. Exiting program.");

	// No need to delete. All Gateware Proxies will cleanup themselves when exiting. Face will also.
	return 0;
}

// Prints a formatted error message
inline void PrintError(const char* _message)
{
	printf("Error: %s\n", _message);
}