modded class DayZPlayerImplement
{
	// Used to delay unlocking 3PP mode after using a restricted item or entering a restricted area
	protected ref Timer m_UnlockViewTimer;

	// Tracks if the player's camera has been restricted or not
	bool m_RestrictedView = false;

	// Check for weapon in hands
	override void HandleView()
	{
		// If running on the server or on a 1PP server, just pass to super
		if (GetGame().IsDedicatedServer() || GetGame().GetWorld().Is3rdPersonDisabled())
		{
			super.HandleView();
			return;
		}

		// This is necessary because if the player types in chat (for example) it will unlock view key again. Wait til timer ends to unlock key.
		if (m_RestrictedView && m_UnlockViewTimer && m_UnlockViewTimer.IsRunning())
		{
			// Ensure camera is locked and view key is disabled
			GetUApi().GetInputByName("UAPersonView").Lock();
			m_Camera3rdPerson = false;

			// Pass to super
			super.HandleView();
			return;
		}

		// Check if player is within a restricted zone
		if (IsInRestrictedArea())
		{
			RestrictView();
		}

		// No item in hands
		if (!GetHumanInventory().GetEntityInHands())
		{
			// Unlock view key input immediately if timer is not set
			if (GetZen3ppConfig().RestrictionTime <= 0 || !m_UnlockViewTimer || !m_UnlockViewTimer.IsRunning())
			{
				GetUApi().GetInputByName("UAPersonView").Unlock();
				m_RestrictedView = false;
			}

			// Pass to super
			super.HandleView();
			return;
		}

		// Check for Lock 1PP mode
		if (HasRestrictedItemInHands())
		{
			RestrictView();
		}
		else
		{
			// No weapon item found in hands and player is not in restricted area - Unlock view key input immediately if timer is not set.
			if (GetZen3ppConfig().RestrictionTime <= 0 || !m_UnlockViewTimer || !m_UnlockViewTimer.IsRunning())
			{
				GetUApi().GetInputByName("UAPersonView").Unlock();
				m_RestrictedView = false;
			}
		}

		// Finished checking for view lock - pass to super.
		super.HandleView();
	}

	// Restrict the player's view mode
	private void RestrictView()
	{
		// Lock to 1PP view and block view key input
		GetUApi().GetInputByName("UAPersonView").Lock();
		m_Camera3rdPerson = false;
		m_RestrictedView = true;

		// Only called if there is a delay on 3PP view restrictions, otherwise view is instantly unlocked
		if (GetZen3ppConfig().RestrictionTime > 0)
			ResetViewLockTimer();
	}

	// Reset the view unlock timer
	private void ResetViewLockTimer()
	{
		if (!m_UnlockViewTimer)
			m_UnlockViewTimer = new Timer();

		if (m_UnlockViewTimer.IsRunning())
			m_UnlockViewTimer.Stop();

		m_UnlockViewTimer.Run(GetZen3ppConfig().RestrictionTime, this, "ZenUnlockViewKey");
	}

	// Unlock 3pp view key
	private void ZenUnlockViewKey()
	{
		// If player still has a restricted item or is in a restricted area, stop here and reset timer.
		if (HasRestrictedItemInHands() || IsInRestrictedArea())
		{
			ResetViewLockTimer();
			return;
		}

		GetUApi().GetInputByName("UAPersonView").Unlock();
		m_RestrictedView = false;
	}

	// Check for restricted item
	private bool HasRestrictedItemInHands()
	{
		EntityAI ent = GetHumanInventory().GetEntityInHands();

		if (!ent)
			return false;

		// Check for config items
		foreach(string s : GetZen3ppConfig().ViewRestrictedItems)
		{
			s.ToLower();

			if (s == "weapon" && ent.IsInherited(Weapon))
			{
				return true;
			}

			if (s == "grenade" && ent.IsInherited(Grenade_Base))
			{
				return true;
			}

			if (ent.IsKindOf(s) || ent.GetType().Contains(s))
			{
				return true;
			}
		}

		return false;
	}

	// Check for restricted areas
	private bool IsInRestrictedArea()
	{
		// If there are no zones just stop here to save time
		if (GetZen3ppConfig().FirstPersonZones.Count() == 0)
			return false;

		// Get our position and check it against all zones
		vector myPos = GetPosition();

		for (int i = 0; i < GetZen3ppConfig().FirstPersonZones.Count(); i++)
		{
			ZenViewRestrictionZone area = GetZen3ppConfig().FirstPersonZones.Get(i);

			if (area.CheckZone(myPos))
			{
				return true;
			}
		}

		// No zone found - we're good.
		return false;
	}
};