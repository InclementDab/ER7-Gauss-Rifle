modded class WeaponEventBase
{
	override string DumpToString()
	{
		string res = "{ WpnEv id=" + m_eventID;
		res = res + " pl=" + Object.GetDebugName(m_player);
		res = res + " mag=" + Object.GetDebugName(m_magazine);
		res = res + " }";
		return res;
	}
};

const int WEAPON_EVENT_ID_ATTACH_BATTERY = 40;
const int WEAPON_EVENT_ID_REMOVE_BATTERY = 41;

/**@brief		event when user wants to attach battery
 **/
class WeaponEventAttachBattery extends WeaponEventBase
{
	void WeaponEventRemoveBattery (DayZPlayer p = NULL, Magazine m = NULL) { m_eventID = WEAPON_EVENT_ID_ATTACH_BATTERY; }
};

/**@brief		event when user wants to remove battery
 **/
class WeaponEventRemoveBattery extends WeaponEventBase
{
	void WeaponEventRemoveBattery (DayZPlayer p = NULL, Magazine m = NULL) { m_eventID = WEAPON_EVENT_ID_REMOVE_BATTERY; }
};