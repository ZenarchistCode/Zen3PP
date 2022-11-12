What Is This?

This mod is for 3PP servers who want to lock players into 1PP view when they are in PVP.

It's designed mostly for PVE and RP servers that want to allow 3rd person mode for adventurers, but don't want to allow players to exploit 3rd person in combat to look around corners or over fences etc.

There are two ways it works (either can be enabled/disabled in config): 

- You can lock the view to 1PP based on what item the player has in their hands (rifles, melee, grenades etc)
- You can lock the view to 1PP based on a proximity to a map location (military bases, contamination zones, certain POIs etc)

When either of these conditions are triggered, the player is locked into 1PP view and must wait X amount of seconds (60 by default) before the 3PP view hotkey will work again after leaving the area or putting their gun away.

To lock the player into 1PP mode when certain items are in their hands you can add the item class name or the item's parent class name to the ViewRestrictedItems list (eg. add "ToolBase" to restrict all knives/hatchets/etc).

If you only want to disable 3PP mode in certain areas and allow 3PP mode with weapons in hand elsewhere on the map, just remove the values from ViewRestrictedItems so the config looks like: "ViewRestrictedItems": []

You can also disable the 1PP view lock while inside a vehicle if you prefer, in order to stop the player being locked into 1PP mode randomly when driving past a military base or other view-restricted area.

Installation Instructions:

Install this mod like any other mod - copy it into your server's root directory, add it to your launch parameters, and make sure to copy the .bikey into your server keys.

This mod must be installed on both the server & client.

Once the mod is installed, on the next server start a JSON config will be generated in your server profiles folder (usually root/profiles/Zenarchist/Zen3ppConfig.json)

The default config automatically generates 1PP zones across military bases and checkpoints for Chernarus, Livonia and Namalsk, but any modded maps will require you to create your own.

Just use a tool like izurvive to get the coordinates and radius.

Config Guide:

"ConfigVersion": "1", // Do not touch - will reset entire config if changed
"RestrictionTime": 60, // Restrictin time (in seconds) when 1PP mode lock is engaged
"ApplyToVehicles": 0, // Set to 1 to enable 1PP lock in restricted zones or when holding guns etc
"RestrictAreas": 1, // Set to 0 to disable restricted areas
"ViewRestrictedItems": [
    "Firearm", // Restrict all firearms
    "Grenade", // Restrict all grenades
    "RemoteDetonatorTrigger" // Restrict individual items
],
"FirstPersonZones": [
{
    "Name": "Contam: Pavlovo", // Location name (can be anything)
    "X": 2099.0, // X coordinate
    "Z": 3375.0, // Z coordinate (Y coordinate is not needed - mod will always use zero for Y)
    "Radius": 250 // Radius in meters from the coordinates to begin locking player view
}

Repack & Source Code:

You can repack this mod if you like, and do anything else you want with it for that matter. The source code is on my GitHub at www.zenarchist.io

Enjoy!