modded class ItemBase
{
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);		
		if (ammo == "Bullet_ER7RFW_Teleport") {
			ER7_TeleportObject(GetHierarchyRoot());
		}
	}
	
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		ER7_HandleRPC(sender, rpc_type, ctx);
	}
}

modded class PlayerBase
{
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		if (ammo == "Bullet_ER7RFW_Teleport") {
			ER7_TeleportObject(GetHierarchyRoot());
		}
	}
	
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		ER7_HandleRPC(sender, rpc_type, ctx);
	}
}

void ER7_TeleportObject(Object object)
{
	GetGame().RPCSingleParam(object, ER7_TeleportRPCs.PLAYSOUND, new Param3<string, vector, float>("Blowout_Teleport", object.GetPosition(), 1), true);
	GetGame().RPCSingleParam(object, ER7_TeleportRPCs.PLAYFLASH, new Param1<vector>(object.GetPosition()), true);
	ER7_TeleportObject(object, ER7_GetRandomTeleportPosition());
}

void ER7_TeleportObject(notnull Object object, vector position)
{
	if (dBodyIsDynamic(object)) {
		object.SetDynamicPhysicsLifeTime(0.001);
		dBodyActive(object, ActiveState.INACTIVE);
	}

	ER7_SetWorldPosition(object, position);
	dBodyActive(object, ActiveState.ACTIVE);
	//object.CreateDynamicPhysics(PhxInteractionLayers.DYNAMICITEM);
	
	//OnTeleportServer(object);
	
	thread ER7_FinishRandomTeleportObject(new Param2<Object, vector>(object, position));
}

void ER7_FinishRandomTeleportObject(ref Param2<Object, vector> params_ref)
{
	OLinkT link = new OLinkT(params_ref.param1);
	
	Sleep(500);
	GetGame().RPCSingleParam(params_ref.param1, ER7_TeleportRPCs.PLAYSOUND, new Param3<string, vector, float>("Blowout_Teleport", params_ref.param1.GetPosition(), 1), true);
	GetGame().RPCSingleParam(params_ref.param1, ER7_TeleportRPCs.PLAYFLASH, new Param1<vector>(params_ref.param2), true);
	
	// Safe
	Sleep(10000);
	PlayerBase p_base;
	if (Class.CastTo(p_base, params_ref.param1)) {
		p_base.SetTeleporting(false);
	}

	delete params_ref;
}


// Grabbed from Community-Online-Tools (thanks Jacob_Mango)
static void ER7_SetWorldPosition(Object object, vector position)
{
    Object parent = object;
    while (parent) { // find world entity parent, incase we are passing a player on a vehicle or a mod has entities as children.
        object = parent;
        parent = Object.Cast(parent.GetParent());
    }

    Transport transport;
    if (Class.CastTo(transport, object)) { // cast to a transport, they require special logic to lower the chance of collision issues
        vector transform[4];
        transport.GetTransform(transform);

        transform[3] = position;
        
        transport.PlaceOnSurfaceRotated(transform, position, 0, 0, 0, false);
        transport.SetTransform(transform);
        transport.Synchronize();

        return;
    }

    object.SetPosition(position);
}

static vector ER7_GetRandomTeleportPosition(float x = 5467, float z = 8660, float radius = 5750)
{				
	vector position;
	position[0] = Math.RandomInt(x - radius, x + radius);
	position[2] = Math.RandomInt(z - radius, z + radius);
	position[1] = GetGame().SurfaceY(position[0], position[2]) + 1;
	
	if (GetGame().SurfaceIsSea(position[0], position[2]) || GetGame().SurfaceIsPond(position[0], position[2])) {
		return ER7_GetRandomTeleportPosition(x, z, radius); 
	}
	
	array<Object> position_objects = {};
	array<CargoBase> position_cargos = {};
	GetGame().GetObjectsAtPosition(position, 3, position_objects, position_cargos);
	if (position_objects.Count() > 0) {
		return ER7_GetRandomTeleportPosition(x, z, radius);
	}
	
	return position;
}

class ER7_TeleportLight: ScriptedLightBase
{
	void ER7_TeleportLight()
	{
		SetLightType(LightType.AMBIENT);
		SetVisibleDuringDaylight(true);
		SetLifetime(0.07);
		SetFadeOutTime(0.02);
		SetCastShadow(true);
		
		SetDiffuseColor(0.3, 0.3, 1);	
		SetAmbientColor(0.3, 0.3, 1);	
		SetBrightnessTo(25);
		SetRadiusTo(1200);
		SetFlareVisible(true);
	}
}

enum ER7_TeleportRPCs
{
	PLAYSOUND = 42456,
	PLAYFLASH = 42457
}

void ER7_HandleRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
{
	switch (rpc_type) {
		case ER7_TeleportRPCs.PLAYSOUND: {
			Param3<string, vector, float> sound_param;
			if (!ctx.Read(sound_param)) {
				break;
			}
			
			EffectSound effect_sound = SEffectManager.PlaySound(sound_param.param1, sound_param.param2, 0, 0, false);
			if (!effect_sound) {
				PrintFormat("Sound failed to create %1", sound_param.param1);
				break;
			}
			// this doesnt work btw
			effect_sound.SetSoundVolume(sound_param.param3);
			effect_sound.SetSoundAutodestroy(true);			
			break;
		}
		
		case ER7_TeleportRPCs.PLAYFLASH: {
			Param1<vector> flash_params;
			if (!ctx.Read(flash_params)) {
				break;
			}
			
			ScriptedLightBase.CreateLight(ER7_TeleportLight, flash_params.param1);
			break;
		}
	}
}

modded class EmoteManager
{
	override void CommitSuicide()
	{
		ER7_Gauss weapon;
		WeaponEventBase weapon_event = new WeaponEventTrigger;
		// cast to ER7
		if (Class.CastTo(weapon, m_Player.GetItemInHands())) {
			//TODO : check multiple muzzles for shotguns, eventually
			string ammo;
			float damage;		
			
			if (weapon.CanFire() && weapon.GetCartridgeInfo(0, damage, ammo) && ammo == "Bullet_ER7RFW_Teleport") {
				
				m_Callback.RegisterAnimationEvent("Simulation_End", EmoteConstants.EMOTE_SUICIDE_SIMULATION_END);
				weapon.ProcessWeaponEvent(weapon_event);
				m_Callback.InternalCommand(DayZPlayerConstants.CMD_ACTIONINT_FINISH);
				
				ER7_TeleportObject(m_Player);
				return;
			}
		}

		super.CommitSuicide();
	}
}
