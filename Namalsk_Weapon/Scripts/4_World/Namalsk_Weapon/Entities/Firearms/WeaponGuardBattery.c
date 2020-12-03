class WeaponGuardBattery extends WeaponGuardBase
{
    protected Weapon_Base m_weapon;
    void WeaponGuardBattery(Weapon_Base w = NULL) { m_weapon = w; }

    override bool GuardCondition(WeaponEventBase e)
    {
        if (m_weapon.GetCompEM() && m_weapon.GetCompEM().CanWork())
        {
		    wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " WeaponGuardBattery - has power");
            return true;
        }

		wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " WeaponGuardBattery - no power");
        return false;
    }
};