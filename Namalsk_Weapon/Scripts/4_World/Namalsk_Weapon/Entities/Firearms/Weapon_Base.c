modded class Weapon_Base
{
    void Weapon_Base()
    {
        if (!m_EM && ConfigIsExisting("EnergyManager")) // TO DO: Check if this instance is a hologram (advanced placement). If Yes, then do not create Energy Manager component.
        {
            CreateComponent(COMP_TYPE_ENERGY_MANAGER);
            m_EM = ComponentEnergyManager.Cast(CreateComponent(COMP_TYPE_ENERGY_MANAGER));
            RegisterNetSyncVariableBool("m_EM.m_IsSwichedOn");
            RegisterNetSyncVariableBool("m_EM.m_CanWork");
            RegisterNetSyncVariableBool("m_EM.m_IsPlugged");
            RegisterNetSyncVariableInt("m_EM.m_EnergySourceNetworkIDLow");
            RegisterNetSyncVariableInt("m_EM.m_EnergySourceNetworkIDHigh");
        }
    }
}