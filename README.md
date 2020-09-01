# Wooting Analog Unreal Plugin

This repo contains a plugin for Unreal Engine v4.23-25 which provides Analog Keyboard input, using the [Wooting Analog SDK](https://github.com/WootingKb/wooting-analog-sdk).

Currently this is an initial version which is not necessarily feature complete. Any feedback would be greatly appreciated, as we are not game developers so a lot of this was tested with Unreal's sample games.

## Plugin Usage

1. Download the plugin by clicking "Clone or download" and selecting "Download Zip"
2. In your project's root directory, create the folder "Plugins" if it doesn't already exist
3. Unzip the "WootingAnalogInput" folder from the downloaded zip into the "Plugins" directory
4. In your project root, right-click on your .uproject file and click "Generate Visual Studio project files" (You'll need Unreal Engine installed for this option to appear)
5. Open up your project in the Unreal Editor (by double clicking the .uproject file or otherwise). If prompted to recompile any files press yes

## Notes

- For the analog reading to work, the [Wooting Analog SDK](https://github.com/WootingKb/wooting-analog-sdk) must be installed, refer to [this page](https://github.com/WootingKb/wooting-analog-sdk) for installation instructions. If the Analog SDK cannot be initialised, regular key presses will still be passed through the Analog * key inputs
- This Plugin provides Analog versions of every keyboard key under "Analog Keyboard". This can be used as a full replacement for any bindings to regular keyboard keys. In the case where no analog keyboard is connected or being used, regular key presses will be passed through with values 1.0f when pressed and 0.0f when released. Analog keys will take priority over regular key presses, so if you were to press the key W on an analog keyboard as well as regular keyboard at the same time, the value of the analog press will be used.

## TODO

- [ ] Better handling when SDK cannot be initialised
- [ ] Multiple analog device support. Currently all analog input is sent under the same input device.
- [ ] Support Linux & Mac builds

## Images

![](https://i.imgur.com/ZHDp1WB.png)

![](https://i.imgur.com/vIsQ5G6.png)

![](https://i.imgur.com/Lkq9moY.png)

![](https://i.imgur.com/sSjJzB8.png)

![](https://i.imgur.com/B59mDMW.png)

## Credits

- Many thanks to Valve for the open source [SteamVR Unreal plugin](https://github.com/ValveSoftware/steamvr_unreal_plugin) which was a really good reference implementation to look at (as Unreal Engine plugin documentation seems to be fairly lacking)
