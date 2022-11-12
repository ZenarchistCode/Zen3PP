class CfgPatches
{
	class Zen3PP
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[] = { "DZ_Data" };
	};
};

class CfgMods
{
	class Zen3PP
	{
		dir="Zen3PP";
		picture=""; 
		action="";
		hideName=1;
		hidePicture=1;
		name="Zen3PP";
		credits=""; 
		author="Zenarchist";
		authorID="0";  
		version="1.0";
		extra=0;
		type="mod";
		dependencies[] =
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = { "Zen3PP/Scripts/3_Game" };
			};
			class worldScriptModule
			{
				value = "";
				files[] = { "Zen3PP/scripts/4_world" };
			};
			class missionScriptModule
			{
				value = "";
				files[] = { "Zen3PP/scripts/5_mission" };
			};
		}
	};
};