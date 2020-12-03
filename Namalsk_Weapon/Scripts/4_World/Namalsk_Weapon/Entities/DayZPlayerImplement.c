modded class DayZPlayerImplement
{/*
    #ifndef CF_DAYZPLAYERIMPLEMENT_IDT_REMOTE
	override void OnInputForRemote (ParamsReadContext ctx)
	{
		int userDataType = 0;
		if (!ctx.Read(userDataType))
		{
			Error("DayZPlayer: OnInputForRemote - cannot read input type");
			return;
		}
		
		switch (userDataType)
		{
			case INPUT_UDT_WEAPON_REMOTE_EVENT:
				OnEventForRemoteWeapon(ctx);
				break;
			case INPUT_UDT_HAND_REMOTE_EVENT:
				GetDayZPlayerInventory().OnHandEventForRemote(ctx);
				break;
			case INPUT_UDT_INVENTORY:
				GetDayZPlayerInventory().OnInputUserDataForRemote(ctx);
				break;
			default:
				Error("OnInputForRemote - unknown userDataType=" + userDataType);
				break;
		}
	}
    #else
	override bool CF_OnInputForRemote(int id, ParamsReadContext ctx)
    {
        if (id == INPUT_UDT_WEAPON_REMOTE_EVENT)
        {
            OnEventForRemoteWeapon(ctx); //! returns false if failed
            return true; //! prevent inheritance
        }

        return super.CF_OnInputForRemote(id, ctx);
    }
    #endif
		
    bool OnEventForRemoteWeapon(ParamsReadContext ctx)
    {
        if (GetHumanInventory().GetEntityInHands())
        {
            Weapon_Base wpn = Weapon_Base.Cast(GetHumanInventory().GetEntityInHands());
            if (wpn)
            {
                int packedType;
                ctx.Read(packedType);
                DayZPlayer player;
                ctx.Read(player);
                Magazine magazine;
                ctx.Read(magazine);

                int eventID = packedType >> 16;
                WeaponEvents animEvent = packedType & 0x0000ffff;
                WeaponEventBase e = null;

                switch (eventID)
                {
                case WeaponEventID.UNKNOWN:
                    break;
                case WeaponEventID.MECHANISM:
                    e = new WeaponEventMechanism(this, magazine);
                    break;
                case WeaponEventID.TRIGGER:
                    e = new WeaponEventTrigger(this, magazine);
                    break;
                case WeaponEventID.TRIGGER_JAM:
                    e = new WeaponEventTriggerToJam(this, magazine);
                    break;
                case WeaponEventID.LOAD1_BULLET:
                    e = new WeaponEventLoad1Bullet(this, magazine);
                    break;
                case WeaponEventID.CONTINUOUS_LOADBULLET_START:
                    e = new WeaponEventContinuousLoadBulletStart(this, magazine);
                    break;
                case WeaponEventID.CONTINUOUS_LOADBULLET_END:
                    e = new WeaponEventContinuousLoadBulletEnd(this, magazine);
                    break;
                case WeaponEventID.UNJAM:
                    e = new WeaponEventUnjam(this, magazine);
                    break;
                case WeaponEventID.ATTACH_MAGAZINE:
                    e = new WeaponEventAttachMagazine(this, magazine);
                    break;
                case WeaponEventID.UNJAMMING_FAILED_TIMEOUT:
                    e = new WeaponEventUnjammingFailedTimeout(this, magazine);
                    break;
                case WeaponEventID.UNJAMMING_TIMEOUT:
                    e = new WeaponEventUnjammingTimeout(this, magazine);
                    break;
                case WeaponEventID.DETACH_MAGAZINE:
                    e = new WeaponEventDetachMagazine(this, magazine);
                    break;
                case WeaponEventID.SWAP_MAGAZINE:
                    e = new WeaponEventSwapMagazine(this, magazine);
                    break;
                case WeaponEventID.HUMANCOMMAND_ACTION_FINISHED:
                    e = new WeaponEventHumanCommandActionFinished(this, magazine);
                    break;
                case WeaponEventID.HUMANCOMMAND_ACTION_ABORTED:
                    e = new WeaponEventHumanCommandActionAborted(this, magazine);
                    break;
                case WeaponEventID.RELOAD_TIMEOUT:
                    e = new WeaponEventReloadTimeout(this, magazine);
                    break;
                case WeaponEventID.DRY_FIRE_TIMEOUT:
                    e = new WeaponEventDryFireTimeout(this, magazine);
                    break;
                case WeaponEventID.SET_NEXT_MUZZLE_MODE:
                    e = new WeaponEventSetNextMuzzleMode(this, magazine);
                    break;
                case WEAPON_EVENT_ID_ATTACH_BATTERY:
                    //e = new WeaponEventAttachBattery(this, magazine);
                    break;
                case WEAPON_EVENT_ID_REMOVE_BATTERY:
                    //e = new WeaponEventRemoveBattery(this, magazine);
                    break;
                case WeaponEventID.ANIMATION_EVENT:
                    e = WeaponAnimEventFactory(animEvent, this, magazine);
                    break;
                }

                if (e)
                {
                    e.ReadFromContext(ctx);

                    GetWeaponManager().SetRunning(true);

                    fsmDebugSpam("[wpnfsm] " + Object.GetDebugName(wpn) + " recv event from remote: created event=" + e);
                    if (e.GetEventID() == WeaponEventID.HUMANCOMMAND_ACTION_ABORTED)
                    {
                        wpn.ProcessWeaponAbortEvent(e);
                    }
                    else
                    {
                        wpn.ProcessWeaponEvent(e);
                    }
					
                    GetWeaponManager().SetRunning(false);
                }
            }
            else
                Error("OnEventForRemoteWeapon - entity in hands, but not weapon. item=" + GetHumanInventory().GetEntityInHands());
        }
        else
            Error("OnEventForRemoteWeapon - no entity in hands");
        return true;
    }
    */
};