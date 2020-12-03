modded class ComponentEnergyManager
{
    override void Event_OnAwake()
    {
		string cfg_item = "CfgVehicles " + m_ThisEntityAI.GetType();
		if (!GetGame().ConfigIsExisting(cfg_item))
		{
			cfg_item = "cfgWeapons " + m_ThisEntityAI.GetType();
			if (!GetGame().ConfigIsExisting(cfg_item))
			{
				return;
			}
		}
		string cfg_energy_manager = cfg_item + " EnergyManager ";
		
		// Read all config parameters
		m_EnergyUsage					= GetGame().ConfigGetFloat (cfg_energy_manager + "energyUsagePerSecond");
		bool switch_on					= GetGame().ConfigGetFloat (cfg_energy_manager + "switchOnAtSpawn");
		m_AutoSwitchOff					= GetGame().ConfigGetFloat (cfg_energy_manager + "autoSwitchOff");
		m_HasElectricityIcon			= GetGame().ConfigGetFloat (cfg_energy_manager + "hasIcon");
		m_AutoSwitchOffWhenInCargo 		= GetGame().ConfigGetFloat (cfg_energy_manager + "autoSwitchOffWhenInCargo");
		
		m_Energy						= GetGame().ConfigGetFloat (cfg_energy_manager + "energyAtSpawn");
		m_EnergyStorageMax				= GetGame().ConfigGetFloat (cfg_energy_manager + "energyStorageMax");
		m_ReduceMaxEnergyByDamageCoef	= GetGame().ConfigGetFloat (cfg_energy_manager + "reduceMaxEnergyByDamageCoef");
		m_SocketsCount					= GetGame().ConfigGetFloat (cfg_energy_manager + "powerSocketsCount");
		
		m_IsPassiveDevice				= GetGame().ConfigGetFloat (cfg_energy_manager + "isPassiveDevice");
		m_CordLength 					= GetGame().ConfigGetFloat (cfg_energy_manager + "cordLength");
		m_PlugType 						= GetGame().ConfigGetFloat (cfg_energy_manager + "plugType");
		
		m_AttachmentActionType			= GetGame().ConfigGetFloat (cfg_energy_manager + "attachmentAction");
		m_WetnessExposure				= GetGame().ConfigGetFloat (cfg_energy_manager + "wetnessExposure");
		
		float update_interval			= GetGame().ConfigGetFloat (cfg_energy_manager + "updateInterval");
		
		m_ConvertEnergyToQuantity		= GetGame().ConfigGetFloat (cfg_energy_manager + "convertEnergyToQuantity");
		
		
		// Check if energy->quantity converion is configured properly
		float cfg_max_quantity = GetGame().ConfigGetFloat (cfg_item + " varQuantityMax");
		
		if (m_ConvertEnergyToQuantity  &&  cfg_max_quantity <= 0)
		{
			string error = "Error! Item " + m_ThisEntityAI.GetType() + " has invalid configuration of the energy->quantity conversion feature. To fix this, add 'varQuantityMax' parameter with value higher than 0 to the item's config. Then make sure to re-build the PBO containing this item!";
			Error(error);
			m_ConvertEnergyToQuantity = false;
		}
		else
		{
			if (m_ConvertEnergyToQuantity)
			{
				if (!m_UpdateQuantityTimer)
					m_UpdateQuantityTimer = new Timer( CALL_CATEGORY_SYSTEM );
				
				m_UpdateQuantityTimer.Run( 0.3 , this, "OnEnergyAdded", NULL, false);
			}
		}
		
		// Set update interval
		if ( update_interval <= 0 )
			update_interval = 1;
		
		SetUpdateInterval( update_interval );
		
		// If energyAtSpawn is present, then use its value for energyStorageMax if that cfg param is not present (for convenience's sake)
		string cfg_check_energy_limit = cfg_energy_manager + "energyStorageMax";
		
		if ( !GetGame().ConfigIsExisting (cfg_check_energy_limit)  &&  m_Energy > 0 )
		{
			m_EnergyStorageMax = m_Energy;
		}
		
		// Fill m_CompatiblePlugTypes
		string cfg_check_plug_types = cfg_energy_manager + "compatiblePlugTypes";
		
		if ( GetGame().ConfigIsExisting (cfg_check_plug_types) )
		{
			m_CompatiblePlugTypes = new TIntArray;
			GetGame().ConfigGetIntArray(cfg_check_plug_types, m_CompatiblePlugTypes);	
		}
		
		if (GetSocketsCount() > 0)
			m_PluggedDevices = new array<EntityAI>;
		
		if ( m_CordLength < 0 )
		{
			m_CordLength = 0;
			string error_message_cord = "Warning! " + m_ThisEntityAI.GetType() + ": config parameter 'cordLength' is less than 0! Cord length should not be negative!";
			DPrint(error_message_cord);
		}
		
		if (GetSocketsCount() > 0)
		{
			m_DeviceByPlugSelection = new map<string,EntityAI>;
			// Prepare the m_DeviceByPlugSelection
			string cfg_animation_sources = cfg_item + "AnimationSources ";
			int animation_sources_count = GetGame().ConfigGetChildrenCount(cfg_animation_sources);
			
			for (int i_selection = 0; i_selection < animation_sources_count; i_selection++)
			{
				// TO DO: This could be optimized so not all selections on item are considered as plug/socket selections.
				string selection;
				GetGame().ConfigGetChildName(cfg_animation_sources, i_selection, selection);
				m_DeviceByPlugSelection.Set(selection, NULL);
			}
		}
		
		
		
		// Prepare sockets
		if ( m_SocketsCount > MAX_SOCKETS_COUNT )
		{
			m_SocketsCount = MAX_SOCKETS_COUNT;
			string error_message_sockets = "Error! " + m_ThisEntityAI.GetType() + ": config parameter 'powerSocketsCount' is higher than the current limit (" + MAX_SOCKETS_COUNT.ToString() + ")! Raise the limit (constant MAX_SOCKETS_COUNT) or decrease the powerSocketsCount parameter for this device!";
			DPrint(error_message_sockets);
		}
		
		m_Sockets[MAX_SOCKETS_COUNT]; // Handles selections for plugs in the sockets. Feel free to change the limit if needed.
		
		GetGame().ConfigGetText(cfg_energy_manager + "cordTextureFile", m_CordTextureFile); 
		
		if ( switch_on )
		{
			SwitchOn();
		}
		
		for ( int i = 0; i <= GetSocketsCount(); ++i )
		{
			m_ThisEntityAI.HideSelection ( SOCKET_ + i.ToString() + _PLUGGED );
		}
		
		// Show/hide inventory sockets
		m_ShowSocketsInInventory = false;
		if ( GetSocketsCount() > 0  &&  IsPlugCompatible(PLUG_COMMON_APPLIANCE)  &&  m_ThisEntityAI.GetType() != "MetalWire" ) // metal wire filter is hopefully temporal.
		{
			m_ShowSocketsInInventory = true;
		}
		
		m_CanWork = HasEnoughStoredEnergy();
		
		m_ThisEntityAI.HideSelection ( SEL_CORD_PLUGGED );
    }

    override void ResetEnergyUsage()
    {
        m_EnergyUsage = m_ThisEntityAI.ConfigGetFloat("EnergyManager energyUsagePerSecond");
    }
	
	//! i hate this, re-adding these methods and unprotecting them fixes the compile error

	// Stops the device's main cycle
	override void StopUpdates()
	{
		if (m_UpdateTimer)
		{
			m_UpdateTimer.Stop();
			m_UpdateTimer = NULL; // Delete timer from memory
		}
	}

	// 'Wakes up' all devices down the network so they start working, if they have enough power, and are switched ON
	override void WakeUpWholeBranch( EntityAI original_caller )
	{
		if ( GetSocketsCount() > 0 )
		{
			array<EntityAI> plugged_devices = GetPluggedDevices();
			int plugged_devices_c = plugged_devices.Count();
			
			for ( int i = 0; i < plugged_devices_c; ++i )
			{
				EntityAI device = plugged_devices.Get(i);
				if ( device != original_caller ) // original_caller check here prevents infinite loops
				{
					device.GetCompEM().UpdateCanWork();
					device.GetCompEM().DeviceUpdate();
					device.GetCompEM().StartUpdates();
					device.GetCompEM().WakeUpWholeBranch( original_caller );
				}
			}
		}
	}

	// Finds an available socket and plugs the given device into it.
	// This is mainly about visualisation.
	override void PlugCordIntoSocket( EntityAI device_to_plug, int socket_id = -1 )
	{
		if (socket_id >= 0)
		{
			EntityAI plug_owner_by_socket = GetDeviceBySocketID(socket_id);
			
			if (!plug_owner_by_socket)
			{
				UpdateSocketSelections(socket_id, device_to_plug);
				return;
			}
		}

		int slots_c = GetSocketsCount();
		
		for ( int i = 0; i < slots_c; ++i )
		{
			EntityAI plug_owner = GetDeviceBySocketID(i);
			
			if ( !plug_owner ) // Check if this socket is available
			{
				UpdateSocketSelections(i, device_to_plug);
				break;
			}
		}
	}
	
	// Updates socket selections (plugged/unplugged) of the given ID and sets color texture of the plug.
	override void UpdateSocketSelections (int socket_id, EntityAI device_to_plug)
	{
		SetDeviceBySocketID(socket_id, device_to_plug);
		
		string plugged_selection = SOCKET_ + (socket_id+1).ToString() + _PLUGGED;
		SetPlugOwner( plugged_selection, device_to_plug );
		m_ThisEntityAI.ShowSelection ( plugged_selection );
		
		string unplugged_selection = SOCKET_ + (socket_id+1).ToString() + _AVAILABLE;
		m_ThisEntityAI.HideSelection ( unplugged_selection );
		string texture_path = device_to_plug.GetCompEM().GetCordTextureFile();
		int selection_index = m_ThisEntityAI.GetHiddenSelectionIndex( plugged_selection );
		m_ThisEntityAI.SetObjectTexture( selection_index, texture_path );
		device_to_plug.GetCompEM().SetMySocketID(socket_id);
	}
	
	
	// Sets energy source for this device
	override void SetEnergySource( EntityAI source )
	{	
		m_EnergySource = source;
		
		if (source)
		{
			m_IsPlugged = true;
			StartUpdates();
		}
		else
		{
			m_IsPlugged = false;
			m_EnergySourceNetworkIDLow = -1;
			m_EnergySourceNetworkIDHigh = -1;
		}
		
		if (m_EnergySource)
		{
			m_EnergySource.GetNetworkID( m_EnergySourceNetworkIDLow, m_EnergySourceNetworkIDHigh );
			
			//Print(m_EnergySource);
			//Print(m_EnergySourceNetworkIDLow);
			//Print(m_EnergySourceNetworkIDHigh);
		}
		
		Synch();
	}

	// Plugs the given device into this one
	override bool PlugInDevice(EntityAI device_to_plug, int socket_id = -1)
	{
		if ( CanReceivePlugFrom(device_to_plug) )
		{
			if ( device_to_plug.GetCompEM().IsPlugged() )
				device_to_plug.GetCompEM().UnplugThis();
			
			GetPluggedDevices().Insert( device_to_plug );
			device_to_plug.GetCompEM().SetEnergySource(m_ThisEntityAI);
			
			PlugCordIntoSocket( device_to_plug, socket_id ); // Visualisation
			OnOwnSocketTaken( device_to_plug );
			
			device_to_plug.GetCompEM().OnIsPlugged(m_ThisEntityAI);
			WakeUpWholeBranch( m_ThisEntityAI );
			
			if (GetGame().IsServer())
			{
				device_to_plug.HideSelection ( SEL_CORD_FOLDED );
				device_to_plug.ShowSelection ( SEL_CORD_PLUGGED );
			}
			
			return true;
		}
		
		return false;
	}

	// Sets the device to which the given plug selection belongs to
	override void SetPlugOwner(string selection_name, EntityAI device)
	{
		if( m_DeviceByPlugSelection.Contains(selection_name) )
		{
			m_DeviceByPlugSelection.Set(selection_name, device);
		}
	}
	
	// Frees the given socket.
	// This is only about visualisation.
	override void UnplugCordFromSocket( int socket_to_unplug_ID )
	{
		EntityAI plug_owner = GetDeviceBySocketID(socket_to_unplug_ID);
		
		if ( plug_owner )
		{
			SetDeviceBySocketID(socket_to_unplug_ID, NULL);
			string unplugged_selection = SOCKET_ + (socket_to_unplug_ID+1).ToString() + _AVAILABLE;
			m_ThisEntityAI.ShowSelection ( unplugged_selection );
			
			string plugged_selection = SOCKET_ + (socket_to_unplug_ID+1).ToString() + _PLUGGED;
			m_ThisEntityAI.HideSelection ( plugged_selection );
			SetPlugOwner( plugged_selection, NULL );
			plug_owner.GetCompEM().SetMySocketID(-1);
		}
	}

	// Sets the state of the device
	override void SetPowered( bool state )
	{
		m_IsWorking = state;
	}
	
	// Tries to consume the given amount of energy. If there is none in this device, then it tries to take it from some power source.
	override bool FindAndConsumeEnergy(EntityAI original_caller, float amount, bool ignore_switch_state = false)
	{
		if ( (ignore_switch_state  ||  IsSwitchedOn())  &&  !m_ThisEntityAI.IsRuined() )
		{
			float available_energy = AddEnergy(-amount);
			
			if ( available_energy < 0  &&  IsPlugged() )
			{
				// This devices does not has enough of stored energy, therefore it will take it from its power source (which can be a chain of cable reels)
				EntityAI next_power_source = GetEnergySource();
				
				if (next_power_source  &&  next_power_source != original_caller) // Prevents infinite loop if the power source is the original caller itself
				{
					return next_power_source.GetCompEM().FindAndConsumeEnergy( original_caller, -available_energy );
				}
			}
			
			if ( available_energy >= 0)
			{
				return true;
			}
			
			return false;
		}
		else
		{
			return false;
		}
	}
	
	// Gets the socket ID this device is powered from.
	override int GetMySocketID()
	{
		return m_MySocketID;
	}
	
	// Sets the socket ID this device is plugged into.
	override void SetMySocketID( int slot_ID )
	{
		m_MySocketID = slot_ID;
	}
	
};