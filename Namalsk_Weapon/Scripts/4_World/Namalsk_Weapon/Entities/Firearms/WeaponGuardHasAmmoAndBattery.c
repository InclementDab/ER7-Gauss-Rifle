class WeaponGuardHasAmmoAndBattery extends WeaponGuardBase
{
    protected Weapon_Base m_weapon;
    void WeaponGuardHasAmmoAndBattery(Weapon_Base w = NULL) { m_weapon = w; }

    override bool GuardCondition(WeaponEventBase e)
    {
		int mi = m_weapon.GetCurrentMuzzle();
		Magazine mag = m_weapon.GetMagazine(mi);
		if (mag != NULL && mag.GetAmmoCount() > 0)
		{
			wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " WeaponGuardHasAmmoAndBattery - has ammo");

            if (m_weapon.GetCompEM() && m_weapon.GetCompEM().CanWork())
            {
		        wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " WeaponGuardHasAmmoAndBattery - has power");
                return true;
            } else
            {
		        wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " WeaponGuardHasAmmoAndBattery - no power");
                return false;
            }
		}
		wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " WeaponGuardHasAmmoAndBattery - no ammo");
		return false;
    }
}