# Wooting Analog Unreal Plugin

This repo contains a plugin for Unreal Engine v4.23 which provides Analog Keyboard input, using the [Wooting Analog SDK](https://github.com/WootingKb/wooting-analog-sdk)

## Plugin Usage

1. Download the plugin by clicking "Clone or download" and selecting "Download Zip"
2. In your project's root directory, create the folder "Plugins" if it doesn't already exist
3. Unzip the "WootingAnalogInput" folder from the downloaded zip into the "Plugins" directory
4. In your project root, right-click on your .uproject file and click "Generate Visual Studio project files" (You'll need Unreal Engine installed for this option to appear)
5. Open up your project in the Unreal Editor (by double clicking the .uproject file or otherwise). If prompted to recompile any files press yes

## Notes

- For the plugin to work, the [Wooting Analog SDK](https://github.com/WootingKb/wooting-analog-sdk) must be installed, refer to [this page](https://github.com/WootingKb/wooting-analog-sdk) for installation instructions

## TODO

- [ ] Better handling when SDK cannot be initialised
- [ ] Deal with issue where Digital Keys take priority over Analog, so when Digital keys are enabled on the Wooting keyboard (which is standard) it will seamlessly use the Analog input over the Digital input

## Credits

- Many thanks to Valve for the open source [SteamVR Unreal plugin](https://github.com/ValveSoftware/steamvr_unreal_plugin) which was a really good reference implementation to look at (as Unreal Engine plugin documentation seems to be fairly lacking)