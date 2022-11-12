modded class MissionGameplay
{
    // Register RPC
    void MissionGameplay()
    {
        GetRPCManager().AddRPC("RPC_Z3PP", "RPC_ReceiveZen3ppConfigOnClient", this, SingeplayerExecutionType.Client);
    }

    // Receive config sent from server -> client
    void RPC_ReceiveZen3ppConfigOnClient(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type == CallType.Client)
        {
            Param3<ref TStringArray, int, ref array<ref ZenViewRestrictionZone>> data;

            // If data fails to read, stop here.
            if (!ctx.Read(data))
            {
                Print("IMPORTANT ERROR: RPC_ReceiveZen3ppConfigOnClient failed to be read on client! Please tell Zenarchist he fucked up!");
                return;
            }

            // Data received - sync to client config
            GetZen3ppConfig().ViewRestrictedItems = data.param1;
            GetZen3ppConfig().RestrictionTime = data.param2;

            // Populate restricted zones
            for (int i = 0; i < data.param3.Count(); i++)
            {
                GetZen3ppConfig().FirstPersonZones.Insert(data.param3.Get(i));
            }
        }
    }
};