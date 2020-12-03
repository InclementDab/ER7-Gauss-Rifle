class WeaponGuardNoBattery extends WeaponGuardBase
{
    protected Weapon_Base m_weapon;
    void WeaponGuardNoBattery(Weapon_Base w = NULL) { m_weapon = w; }

    override bool GuardCondition(WeaponEventBase e)
    {
        if (m_weapon.GetCompEM() && m_weapon.GetCompEM().CanWork())
        {
		    wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " WeaponGuardNoBattery - has power");
            return false;
        }

		wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " WeaponGuardNoBattery - no power");
        return true;
    }
};