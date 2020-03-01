
# Description

This Repositiory contains the source for the SKSEVR plugin used by the [moreHUD VR](https://www.nexusmods.com/skyrimspecialedition/mods/12688) mod for the VR Edition.  
The plugin works in conjunction with the [ahzaab/moreHUDVRScaleform](https://github.com/ahzaab/moreHUDVRScaleform) Scaleform Elements.  

## How it Works

* The SKSEVR plugin is loaded by [SKSEVR](http://skse.silverlock.org/) using the sksevr_loader.exe
* The plugin dynammically loads the Scaleform .swf movie clip into the Hud Menu when the menu loads.
* The plugin registers Scaleform functions used by the ActionScript 2.0 code associated with the [moreHUD VR swf file](https://github.com/ahzaab/moreHUDVRScaleform) 
* The plugin provides data to the ActionScript such as Known Ingredients, Magic Effects, Enemy Level, Known Echantments, etc.

## Installation
The compiled .dll is installed in the Skyrim Data Folder to `Data/SKSE/Plugins`

## Does it need papyrus?
Not by the Plugin. But only for the .swf file as described [here](https://github.com/ahzaab/moreHUDVRScaleform) 
