class ER7_Gauss: Rifle_Base
{
	protected ref array<Particle> m_GaussHeat = {};
		
	ref WeaponStateBase D0;
	ref WeaponStateBase C0;
	ref	WeaponStateBase C1;
	ref	WeaponStateBase DF;
	ref	WeaponStateBase JF;
	
	override void InitStateMachine()
	{
		m_abilities.Insert(new AbilityRecord(WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_CLOSED));
		m_abilities.Insert(new AbilityRecord(WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_OPENED));
		m_abilities.Insert(new AbilityRecord(WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_STARTLOOPABLE_SHOTGUN_COCKED));
		m_abilities.Insert(new AbilityRecord(WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_STARTLOOPABLE_SHOTGUN_UNCOCKED));
		m_abilities.Insert(new AbilityRecord(WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_ENDLOOPABLE));
		m_abilities.Insert(new AbilityRecord(WeaponActions.UNJAMMING, WeaponActionUnjammingTypes.UNJAMMING_START));
		m_abilities.Insert(new AbilityRecord(WeaponActions.UNJAMMING, WeaponActionUnjammingTypes.UNJAMMING_END));
		m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_NORMAL));
		m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_COCKED));
		m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_UNCOCKED));
		m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY));
		
		D0 = new RPTEmptyDischarged(this, NULL, RPTAnimState.DEFAULT);
		C0 = new RPTEmptyDischarged(this, NULL, RPTAnimState.CHARGED);
		DF = new RPTLoadedDischarged(this, NULL, RPTAnimState.DEFAULT);
		C1 = new RPTLoadedCharged(this, NULL, RPTAnimState.CHARGED);
		JF = new RPTLoadedJammed(this, NULL, RPTAnimState.JAMMED);
		
		//WeaponStateBase	Mech_D0 = new WeaponChargingInnerMag(this, NULL, WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_CLOSED);
		WeaponStateBase	Mech_C1 = new WeaponChargingInnerMag(this, NULL, WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_OPENED);
		WeaponStateBase	Mech_DF = new WeaponChargingInnerMag(this, NULL, WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_CLOSED);

		LoopedChamberingEjectLast Chamber_D0 = new LoopedChamberingEjectLast(this, NULL, WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_STARTLOOPABLE_SHOTGUN_UNCOCKED, WeaponActionChamberingTypes.CHAMBERING_ENDLOOPABLE);
		LoopedChamberingEjectLast Chamber_C0 = new LoopedChamberingEjectLast(this, NULL, WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_STARTLOOPABLE_SHOTGUN_UNCOCKED, WeaponActionChamberingTypes.CHAMBERING_ENDLOOPABLE);
		LoopedChamberingEjectLast Chamber_C1 = new LoopedChamberingEjectLast(this, NULL, WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_STARTLOOPABLE_SHOTGUN_COCKED, WeaponActionChamberingTypes.CHAMBERING_ENDLOOPABLE);
		LoopedChamberingEjectLast Chamber_DF = new LoopedChamberingEjectLast(this, NULL, WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_STARTLOOPABLE_SHOTGUN_UNCOCKED, WeaponActionChamberingTypes.CHAMBERING_ENDLOOPABLE);
		
		WeaponStateBase	Unjam_JF = new WeaponUnjamming(this, NULL, WeaponActions.UNJAMMING, WeaponActionUnjammingTypes.UNJAMMING_START);
		
		WeaponStateBase	Trigger_D0 = new WeaponDryFire(this, NULL, WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY);
		WeaponStateBase	Trigger_C0 = new WeaponDryFire(this, NULL, WeaponActions.FIRE, WeaponActionFireTypes.FIRE_NORMAL);
		WeaponStateBase	Trigger_C1 = new WeaponFire(this, NULL, WeaponActions.FIRE, WeaponActionFireTypes.FIRE_NORMAL);
		WeaponStateBase	Trigger_DF = new WeaponDryFire(this, NULL, WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY);
		WeaponStateBase	Trigger_JF = new WeaponDryFire(this, NULL, WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY);
		
		WeaponStateBase	Trigger_C1J = new WeaponFireToJam(this, NULL, WeaponActions.FIRE, WeaponActionFireTypes.FIRE_JAM);

		
		WeaponEventBase _fin_ = new WeaponEventHumanCommandActionFinished;
		WeaponEventBase __L__ = new WeaponEventLoad1Bullet;
		WeaponEventBase __T__ = new WeaponEventTrigger;
		WeaponEventBase __TJ_ = new WeaponEventTriggerToJam;
		WeaponEventBase __U__ = new WeaponEventUnjam;
		WeaponEventBase	__M__ = new WeaponEventMechanism;
		WeaponEventBase _abt_ = new WeaponEventHumanCommandActionAborted;
		WeaponEventBase _rto_ = new WeaponEventReloadTimeout;
		WeaponEventBase _dto_ = new WeaponEventDryFireTimeout;

		m_fsm = new WeaponFSM();
		
		// Mechanism
//----------------------------------------
		m_fsm.AddTransition(new WeaponTransition( D0,			__M__,	Mech_DF));
		m_fsm.AddTransition(new WeaponTransition( C0,			__M__,	Mech_C1));
				
		m_fsm.AddTransition(new WeaponTransition( C1,			__M__,	Mech_C1));
		m_fsm.AddTransition(new WeaponTransition(  Mech_C1,		_fin_,	C0, NULL, new WeaponGuardCurrentChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition(  Mech_C1,		_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Mech_C1,		_abt_,	C0, NULL, new WeaponGuardCurrentChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition(  Mech_C1,		_abt_,	C1));
		
		m_fsm.AddTransition(new WeaponTransition( DF,			__M__,	Mech_DF));
		m_fsm.AddTransition(new WeaponTransition(  Mech_DF,		_fin_,	C0, NULL, new WeaponGuardCurrentChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition(  Mech_DF,		_fin_,	DF, NULL, new WeaponGuardCurrentChamberFiredOut(this)));
		m_fsm.AddTransition(new WeaponTransition(  Mech_DF,		_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Mech_DF,		_abt_,	C0, NULL, new WeaponGuardCurrentChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition(  Mech_DF,		_abt_,	DF, NULL, new WeaponGuardCurrentChamberFiredOut(this)));
		m_fsm.AddTransition(new WeaponTransition(  Mech_DF,		_abt_,	C1));
		
		
//----------------------------------------
		m_fsm.AddTransition(new WeaponTransition( C0,			__L__,	Chamber_D0));
		
		m_fsm.AddTransition(new WeaponTransition( D0,			__L__,	Chamber_D0));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_D0,	_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_D0,	_abt_,	C0, NULL, new WeaponGuardCurrentChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_D0,	_abt_,	C1));
		
		m_fsm.AddTransition(new WeaponTransition( C1,			__L__,	Chamber_C1, NULL, new GuardNot(new WeaponGuardInnerMagazineFull(this))));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_C1,	_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_C1,	_abt_,	C1));
		
		m_fsm.AddTransition(new WeaponTransition( DF,			__L__,	Chamber_DF, NULL, new GuardNot(new WeaponGuardInnerMagazineFull(this))));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_DF,	_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_DF,	_abt_,	DF, NULL, new WeaponGuardCurrentChamberFiredOut(this)));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_DF,	_abt_,	C1));
		
//------------------------------------------
		
		m_fsm.AddTransition(new WeaponTransition( JF, 			__U__,	Unjam_JF));
		m_fsm.AddTransition(new WeaponTransition(  Unjam_JF,	_fin_,	JF, NULL, new WeaponGuardJammed(this)));
		m_fsm.AddTransition(new WeaponTransition(  Unjam_JF,	_fin_,	C0, NULL, new WeaponGuardCurrentChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition(  Unjam_JF,	_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Unjam_JF,	_abt_,	JF, NULL, new WeaponGuardJammed(this)));
		m_fsm.AddTransition(new WeaponTransition(  Unjam_JF,	_abt_,	C0, NULL, new WeaponGuardCurrentChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition(  Unjam_JF,	_abt_,	C1));
		
		
		m_fsm.AddTransition(new WeaponTransition( C1,				__T__,	Trigger_C1, NULL, new WeaponGuardHasAmmoAndBattery(this)));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C1,		_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C1,		_rto_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C1,		_abt_,	C1));
				
		m_fsm.AddTransition(new WeaponTransition( C1,				__T__,	Trigger_DF, NULL, new WeaponGuardNoBattery(this)));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_DF,		_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_DF,		_rto_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_DF,		_abt_,	C1));
		
		
//-----------------------------------------
		
		// fire
		m_fsm.AddTransition(new WeaponTransition( D0,			__T__,	Trigger_D0)); // fire.cocked
		m_fsm.AddTransition(new WeaponTransition(  Trigger_D0,	_fin_,	D0));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_D0,	_dto_,	D0));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_D0,	_abt_,	D0));
		
		m_fsm.AddTransition(new WeaponTransition( C0,			__T__,	Trigger_C0)); // fire.cocked
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C0,	_fin_,	D0));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C0,	_dto_,	D0));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C0,	_abt_,	D0));
		
		m_fsm.AddTransition(new WeaponTransition( C1,			__T__,	Trigger_C1)); // fire.cocked
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C1,	_fin_,	DF));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C1,	_rto_,	DF));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C1,	_abt_,	DF));
		
		m_fsm.AddTransition(new WeaponTransition( DF,			__T__,	Trigger_DF)); // fire.cocked
		m_fsm.AddTransition(new WeaponTransition(  Trigger_DF,	_fin_,	DF));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_DF,	_dto_,	DF));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_DF,	_abt_,	DF));
		
		m_fsm.AddTransition(new WeaponTransition( JF,			__T__,	Trigger_JF)); // fire.cocked
		m_fsm.AddTransition(new WeaponTransition(  Trigger_JF,	_fin_,	JF));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_JF,	_dto_,	JF));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_JF,	_abt_,	JF));
		
		
		m_fsm.AddTransition(new WeaponTransition( JF,			__TJ_,	Trigger_C1J)); // fire.cocked
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C1J,	_fin_,	JF));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C1J,	_rto_,	JF));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C1J,	_abt_,	JF));
		
//---------------------------------------------	
		
		m_fsm.SetInitialState(D0);

		SelectionBulletHide();
		HideMagazine();

		m_fsm.Start();
	}
	
	override bool CanChamberBullet (int muzzleIndex, Magazine mag)
	{
		return CanChamberFromMag(muzzleIndex, mag) && !IsInternalMagazineFull(muzzleIndex);
	}
	
	override void SetActions()
	{
		super.SetActions();
		AddAction(FirearmActionLoadMultiBullet);

		RemoveAction(FirearmActionLoadBulletQuick); // Easy reload
		AddAction(FirearmActionLoadMultiBulletQuick); // Easy reload
	}
		
	override void EEFired(int muzzleType, int mode, string ammoType)
	{
		super.EEFired(muzzleType, mode, ammoType);
		
		if (GetCompEM()) {
			EntityAI source = GetCompEM().GetEnergySource();
			if (source) {				
				source.GetCompEM().AddEnergy(-1 * GetCompEM().GetEnergyUsage());
			}
			GetCompEM().UpdateCanWork();
		}
	
		if (GetGame().IsClient() || !GetGame().IsMultiplayer()) {
			for (int i = 1; i <= 4; i++) {
                m_GaussHeat.Insert(Particle.PlayOnObject(ParticleList.GAUSS_HEAT_RIGHT, this, GetMemoryPointPos("ParticlePoint_Right_" + i)));
                m_GaussHeat.Insert(Particle.PlayOnObject(ParticleList.GAUSS_HEAT_LEFT, this, GetMemoryPointPos("ParticlePoint_Left_" + i)));
                m_GaussHeat.Insert(Particle.PlayOnObject(ParticleList.GAUSS_FIRE, this, GetMemoryPointPos("usti hlavne")));
            }
			
			//ScriptedLightBase.CreateLight(ER7_Gauss_Fire_Light, ModelToWorld(GetMemoryPointPos("usti hlavne")));
		}
		
		if (GetGame().IsServer()) {
			thread OnFireServer();
		}
	}
	
	override RecoilBase SpawnRecoilObject()
	{
		return new ER7Recoil(this);
	}
	
	void OnFireFailed()
	{		
		EffectSound sound;
		if (PlaySoundSet(sound, "ER7_Shot_Failed_SoundSet", 0, 0)) {
			sound.Start();
		}
	}
	
	void OnFireServer()
	{
		//flaps 1 closest to barrel flaps 4 closest to user.
		SetAnimationPhase("AnimateLowerFlaps4Left", 1);
		SetAnimationPhase("AnimateLowerFlaps4Right", 1);
		SetAnimationPhase("AnimateUpperFlaps4Left", 1);
		SetAnimationPhase("AnimateUpperFlaps4Right", 1);
		Sleep(75);
		SetAnimationPhase("AnimateLowerFlaps3Left", 1);
		SetAnimationPhase("AnimateLowerFlaps3Right", 1);
		SetAnimationPhase("AnimateUpperFlaps3Left", 1);
		SetAnimationPhase("AnimateUpperFlaps3Right", 1);
		Sleep(100);
		SetAnimationPhase("AnimateLowerFlaps2Left", 1);
		SetAnimationPhase("AnimateLowerFlaps2Right", 1);
		SetAnimationPhase("AnimateUpperFlaps2Left", 1);
		SetAnimationPhase("AnimateUpperFlaps2Right", 1);
		Sleep(125);
		SetAnimationPhase("AnimateLowerFlaps1Left", 1);
		SetAnimationPhase("AnimateLowerFlaps1Right", 1);
		SetAnimationPhase("AnimateUpperFlaps1Left", 1);
		SetAnimationPhase("AnimateUpperFlaps1Right", 1);

		Sleep(850);

		SetAnimationPhase("AnimateLowerFlaps4Left", 0);
		SetAnimationPhase("AnimateLowerFlaps4Right", 0);
		SetAnimationPhase("AnimateUpperFlaps4Left", 0);
		SetAnimationPhase("AnimateUpperFlaps4Right", 0);
		Sleep(175);
		SetAnimationPhase("AnimateLowerFlaps3Left", 0);
		SetAnimationPhase("AnimateLowerFlaps3Right", 0);
		SetAnimationPhase("AnimateUpperFlaps3Left", 0);
		SetAnimationPhase("AnimateUpperFlaps3Right", 0);
		Sleep(150);
		SetAnimationPhase("AnimateLowerFlaps2Left", 0);
		SetAnimationPhase("AnimateLowerFlaps2Right", 0);
		SetAnimationPhase("AnimateUpperFlaps2Left", 0);
		SetAnimationPhase("AnimateUpperFlaps2Right", 0);
		Sleep(125);
		SetAnimationPhase("AnimateLowerFlaps1Left", 0);
		SetAnimationPhase("AnimateLowerFlaps1Right", 0);
		SetAnimationPhase("AnimateUpperFlaps1Left", 0);
		SetAnimationPhase("AnimateUpperFlaps1Right", 0);
	}
}



/*
m_abilities.Insert(new AbilityRecord(WeaponActions.RELOAD, GetWeaponSpecificCommand(WeaponActions.RELOAD, WeaponActionReloadTypes.RELOADRIFLE_MAGAZINE_BULLET)));
		m_abilities.Insert(new AbilityRecord(WeaponActions.RELOAD, GetWeaponSpecificCommand(WeaponActions.RELOAD, WeaponActionReloadTypes.RELOADRIFLE_NOMAGAZINE_BULLET)));
		m_abilities.Insert(new AbilityRecord(WeaponActions.RELOAD, GetWeaponSpecificCommand(WeaponActions.RELOAD, WeaponActionReloadTypes.RELOADRIFLE_MAGAZINE_NOBULLET)));
		m_abilities.Insert(new AbilityRecord(WeaponActions.RELOAD, GetWeaponSpecificCommand(WeaponActions.RELOAD, WeaponActionReloadTypes.RELOADRIFLE_NOMAGAZINE_NOBULLET)));
		m_abilities.Insert(new AbilityRecord(WeaponActions.RELOAD, GetWeaponSpecificCommand(WeaponActions.RELOAD, WeaponActionReloadTypes.RELOADRIFLE_NOMAGAZINE_NOBULLET_OPEN)));
		m_abilities.Insert(new AbilityRecord(WeaponActions.RELOAD, GetWeaponSpecificCommand(WeaponActions.RELOAD, WeaponActionReloadTypes.RELOADRIFLE_MAGAZINE_NOBULLET_OPEN)));
		m_abilities.Insert(new AbilityRecord(WeaponActions.RELOAD, GetWeaponSpecificCommand(WeaponActions.RELOAD, WeaponActionReloadTypes.RELOADRIFLE_MAGAZINE_DETACH)));

		m_abilities.Insert(new AbilityRecord(WeaponActions.CHAMBERING, GetWeaponSpecificCommand(WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_ONEBULLET_CLOSED)));
		m_abilities.Insert(new AbilityRecord(WeaponActions.CHAMBERING, GetWeaponSpecificCommand(WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_ONEBULLET_UNIQUE_CLOSED)));
		
		m_abilities.Insert(new AbilityRecord(WeaponActions.MECHANISM, GetWeaponSpecificCommand(WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_CLOSED)));
		m_abilities.Insert(new AbilityRecord(WeaponActions.MECHANISM, GetWeaponSpecificCommand(WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_OPENED)));//????
		
		m_abilities.Insert(new AbilityRecord(WeaponActions.UNJAMMING, GetWeaponSpecificCommand(WeaponActions.UNJAMMING, WeaponActionUnjammingTypes.UNJAMMING_START)));
		m_abilities.Insert(new AbilityRecord(WeaponActions.UNJAMMING, GetWeaponSpecificCommand(WeaponActions.UNJAMMING, WeaponActionUnjammingTypes.UNJAMMING_END)));
		
		m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_NORMAL)));
		m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_LAST)));
		m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_JAM)));
		m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY)));
		
		//m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_UNCOCKED));

		// setup state machine
		// basic weapon states
		// close-locked-jammed | nobullet-bullet | nomag-mag
		// regexp: [CLJ][01][01]
		C00 = new RBL_CLO_BU0_MA0(this, NULL, RBLAnimState.DEFAULT);
		C10 = new RBL_CLO_BU1_MA0(this, NULL, RBLAnimState.DEFAULT);
		C11 = new RBL_CLO_BU1_MA1(this, NULL, RBLAnimState.DEFAULT);
		C01 = new RBL_CLO_BU0_MA1(this, NULL, RBLAnimState.DEFAULT);
		O00 = new RBL_OPN_BU0_MA0(this, NULL, RBLAnimState.OPENED);
		O01 = new RBL_OPN_BU0_MA1(this, NULL, RBLAnimState.OPENED);
		JF0 = new RBL_JAM_BU1_MA0(this, NULL, RBLAnimState.JAMMED);
		JF1 = new RBL_JAM_BU1_MA1(this, NULL, RBLAnimState.JAMMED);

		// unstable (intermediate) states
		WeaponCharging Mech_C00 = new WeaponCharging(this, NULL, WeaponActions.MECHANISM, GetWeaponSpecificCommand(WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_CLOSED));
		WeaponCharging Mech_C01 = new WeaponCharging(this, NULL, WeaponActions.MECHANISM, GetWeaponSpecificCommand(WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_CLOSED));
		WeaponCharging Mech_O00 = new WeaponCharging(this, NULL, WeaponActions.MECHANISM, GetWeaponSpecificCommand(WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_OPENED));
		WeaponCharging Mech_O01 = new WeaponCharging(this, NULL, WeaponActions.MECHANISM, GetWeaponSpecificCommand(WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_OPENED));
	
		WeaponCharging Mech_C10 = new WeaponCharging(this, NULL, WeaponActions.MECHANISM, GetWeaponSpecificCommand(WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_CLOSED));
		WeaponCharging Mech_C11 = new WeaponCharging(this, NULL, WeaponActions.MECHANISM, GetWeaponSpecificCommand(WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_CLOSED));
		
		WeaponStateBase Trigger_C00 = new WeaponDryFire(this, NULL, WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY)); // cock without clip
		WeaponStateBase Trigger_C10 = new WeaponFireLast(this, NULL, WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_NORMAL)); // cock with clip
		WeaponFireAndChamberNext Trigger_C11 = new WeaponFireAndChamberNext(this, NULL, WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_NORMAL));
		WeaponStateBase Trigger_C11L = new WeaponFireLast(this, NULL, WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_LAST));
		WeaponStateBase Trigger_NB10 = new WeaponDryFire(this, NULL, WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY));
		WeaponStateBase Trigger_NB11 = new WeaponDryFire(this, NULL, WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY));
		WeaponStateBase Trigger_C01 = new WeaponDryFire(this, NULL, WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY));
		WeaponStateBase Trigger_O00 = new WeaponDryFire(this, NULL, WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY));
		WeaponStateBase Trigger_O01 = new WeaponDryFire(this, NULL, WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY));
		WeaponStateBase Trigger_JF0 = new WeaponDryFire(this, NULL, WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY));
		WeaponStateBase Trigger_JF1 = new WeaponDryFire(this, NULL, WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY));
	
		//Fire and jam
		WeaponStateBase Trigger_C10J = new WeaponFireToJam(this, NULL, WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_JAM)); // cock with clip
		WeaponStateBase Trigger_C11J = new WeaponFireToJam(this, NULL, WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_JAM));
		
//		WeaponStateBase Trigger_C11J = new WeaponFire(this, NULL, WeaponActions.FIRE, GetWeaponSpecificCommand(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_JAM));

		WeaponStateBase Unjam_JF0 = new WeaponUnjamming(this, NULL, WeaponActions.UNJAMMING, GetWeaponSpecificCommand(WeaponActions.UNJAMMING, WeaponActionUnjammingTypes.UNJAMMING_START));
		WeaponStateBase Unjam_JF1 = new WeaponUnjamming(this, NULL, WeaponActions.UNJAMMING, GetWeaponSpecificCommand(WeaponActions.UNJAMMING, WeaponActionUnjammingTypes.UNJAMMING_START));

		WeaponChambering Chamber_C00 = new WeaponChambering(this, NULL, WeaponActions.CHAMBERING, GetWeaponSpecificCommand(WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_ONEBULLET_CLOSED));
		WeaponChambering Chamber_C01 = new WeaponChambering(this, NULL, WeaponActions.CHAMBERING, GetWeaponSpecificCommand(WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_ONEBULLET_CLOSED));
		WeaponChambering Chamber_O00 = new WeaponChambering(this, NULL, WeaponActions.CHAMBERING, GetWeaponSpecificCommand(WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_ONEBULLET_UNIQUE_CLOSED));
		WeaponChambering Chamber_O01 = new WeaponChambering(this, NULL, WeaponActions.CHAMBERING, GetWeaponSpecificCommand(WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_ONEBULLET_UNIQUE_CLOSED));

		WeaponAttachMagazine Attach_C00 = new WeaponAttachMagazine(this, NULL, WeaponActions.RELOAD, GetWeaponSpecificCommand(WeaponActions.RELOAD, WeaponActionReloadTypes.RELOADRIFLE_NOMAGAZINE_NOBULLET));
		WeaponAttachMagazine Attach_C10 = new WeaponAttachMagazine(this, NULL, WeaponActions.RELOAD, GetWeaponSpecificCommand(WeaponActions.RELOAD, WeaponActionReloadTypes.RELOADRIFLE_NOMAGAZINE_BULLET));
		WeaponAttachMagazine Attach_O00 = new WeaponAttachMagazine(this, NULL, WeaponActions.RELOAD, GetWeaponSpecificCommand(WeaponActions.RELOAD, WeaponActionReloadTypes.RELOADRIFLE_NOMAGAZINE_NOBULLET_OPEN));//TODO Need add open animation
		WeaponAttachMagazine Attach_JF0 = new WeaponAttachMagazine(this, NULL, WeaponActions.RELOAD, GetWeaponSpecificCommand(WeaponActions.RELOAD, WeaponActionReloadTypes.RELOADRIFLE_NOMAGAZINE_BULLET));
		
		WeaponReplacingMagAndChamberNext Reload_C11 = new WeaponReplacingMagAndChamberNext(this, NULL, WeaponActions.RELOAD, GetWeaponSpecificCommand(WeaponActions.RELOAD, WeaponActionReloadTypes.RELOADRIFLE_MAGAZINE_BULLET));
		WeaponReplacingMagAndChamberNext Reload_C01 = new WeaponReplacingMagAndChamberNext(this, NULL, WeaponActions.RELOAD, GetWeaponSpecificCommand(WeaponActions.RELOAD, WeaponActionReloadTypes.RELOADRIFLE_MAGAZINE_NOBULLET));
		WeaponReplacingMagAndChamberNext Reload_O01 = new WeaponReplacingMagAndChamberNext(this, NULL, WeaponActions.RELOAD, GetWeaponSpecificCommand(WeaponActions.RELOAD, WeaponActionReloadTypes.RELOADRIFLE_MAGAZINE_NOBULLET_OPEN));//TODO Need add open animation
		WeaponReplacingMagAndChamberNext Reload_JF1 = new WeaponReplacingMagAndChamberNext(this, NULL, WeaponActions.RELOAD, GetWeaponSpecificCommand(WeaponActions.RELOAD, WeaponActionReloadTypes.RELOADRIFLE_MAGAZINE_BULLET));
		
		WeaponDetachingMag Detach_C11 = new WeaponDetachingMag(this, NULL, WeaponActions.RELOAD, GetWeaponSpecificCommand(WeaponActions.RELOAD, WeaponActionReloadTypes.RELOADRIFLE_MAGAZINE_DETACH));
		WeaponDetachingMag Detach_C01 = new WeaponDetachingMag(this, NULL, WeaponActions.RELOAD, GetWeaponSpecificCommand(WeaponActions.RELOAD, WeaponActionReloadTypes.RELOADRIFLE_MAGAZINE_DETACH));
		WeaponDetachingMag Detach_O01 = new WeaponDetachingMag(this, NULL, WeaponActions.RELOAD, GetWeaponSpecificCommand(WeaponActions.RELOAD, WeaponActionReloadTypes.RELOADRIFLE_MAGAZINE_DETACH));
		WeaponDetachingMag Detach_JF1 = new WeaponDetachingMag(this, NULL, WeaponActions.RELOAD, GetWeaponSpecificCommand(WeaponActions.RELOAD, WeaponActionReloadTypes.RELOADRIFLE_MAGAZINE_DETACH));
		
		//WeaponStateBase chmMag = new WeaponChamberFromAttMag(this, NULL, WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_CLOSED);

		// events
		WeaponEventBase __M__ = new WeaponEventMechanism;
		WeaponEventBase __T__ = new WeaponEventTrigger;
		WeaponEventBase __TJ_ = new WeaponEventTriggerToJam;
		WeaponEventBase __U__ = new WeaponEventUnjam;
		WeaponEventBase __L__ = new WeaponEventLoad1Bullet;
		WeaponEventBase __A__ = new WeaponEventAttachMagazine;
		WeaponEventBase __D__ = new WeaponEventDetachMagazine;
		WeaponEventBase __S__ = new WeaponEventSwapMagazine;
		WeaponEventBase _fin_ = new WeaponEventHumanCommandActionFinished;
		WeaponEventBase _abt_ = new WeaponEventHumanCommandActionAborted;
		WeaponEventBase _rto_ = new WeaponEventReloadTimeout;
		WeaponEventBase _dto_ = new WeaponEventDryFireTimeout;

		m_fsm = new WeaponFSM();

		// order: Discharged-Charged | nobullet-bullet | nomag-mag
		// charging
		m_fsm.AddTransition(new WeaponTransition( C00, 				__M__,	Mech_C00)); // charge from dischg nobullet nomag
		m_fsm.AddTransition(new WeaponTransition(  Mech_C00,		_fin_,	C00));
		m_fsm.AddTransition(new WeaponTransition(  Mech_C00,		_abt_,	C00));

		m_fsm.AddTransition(new WeaponTransition( C10,				__M__,	Mech_C10)); // charge from bullet nomag
		m_fsm.AddTransition(new WeaponTransition(  Mech_C10,		_fin_,	C00));
		m_fsm.AddTransition(new WeaponTransition(  Mech_C10,		_abt_,	C00, NULL, new WeaponGuardCurrentChamberEmpty(this) ));
		m_fsm.AddTransition(new WeaponTransition(  Mech_C10, 		_abt_,	C10));
		
		m_fsm.AddTransition(new WeaponTransition( C11,				__M__,	Mech_C11)); // charge from dischg nobullet nomag
		m_fsm.AddTransition(new WeaponTransition(  Mech_C11,		_fin_,	C01, NULL, new WeaponGuardCurrentChamberEmpty(this) ));
		m_fsm.AddTransition(new WeaponTransition(  Mech_C11,		_fin_,	C11));
		m_fsm.AddTransition(new WeaponTransition(  Mech_C11,		_abt_,	C01, NULL, new WeaponGuardCurrentChamberEmpty(this) ));
		m_fsm.AddTransition(new WeaponTransition(  Mech_C11,		_abt_,	C11));
		
		
		m_fsm.AddTransition(new WeaponTransition( C01,				__M__,	Mech_C01)); // charge from dischg nobullet nomag
		m_fsm.AddTransition(new WeaponTransition(  Mech_C01,		_fin_,	C01, NULL, new WeaponGuardCurrentChamberEmpty(this) ));
		m_fsm.AddTransition(new WeaponTransition(  Mech_C01,		_fin_,	C11));
		m_fsm.AddTransition(new WeaponTransition(  Mech_C01,		_abt_,	C01, NULL, new WeaponGuardCurrentChamberEmpty(this) ));
		m_fsm.AddTransition(new WeaponTransition(  Mech_C01,		_abt_,	C11));
		
		m_fsm.AddTransition(new WeaponTransition( O00,				__M__,	Mech_O00)); // charge from dischg nobullet nomag
		m_fsm.AddTransition(new WeaponTransition(  Mech_O00,		_fin_,	C00));
			Mech_O00.AddTransition(new WeaponTransition( Mech_O00.m_start,			_abt_,	O00));
			Mech_O00.AddTransition(new WeaponTransition( Mech_O00.m_eject,			_abt_,	C00));
			Mech_O00.AddTransition(new WeaponTransition( Mech_O00.m_onCK,			_abt_,	C00));
			Mech_O00.AddTransition(new WeaponTransition( Mech_O00.m_chamber,		_abt_,	C00));
		
		m_fsm.AddTransition(new WeaponTransition( O01,				__M__,	Mech_O01)); // charge from dischg nobullet nomag
		m_fsm.AddTransition(new WeaponTransition(  Mech_O01,		_fin_,	C01, NULL, new WeaponGuardCurrentChamberEmpty(this) ));
		m_fsm.AddTransition(new WeaponTransition(  Mech_O01,		_fin_,	C11)); 
			Mech_O01.AddTransition(new WeaponTransition( Mech_O01.m_start,			_abt_,	O01));
			Mech_O01.AddTransition(new WeaponTransition( Mech_O01.m_eject,			_abt_,	C01));
			Mech_O01.AddTransition(new WeaponTransition( Mech_O01.m_onCK,			_abt_,	C01));
			Mech_O01.AddTransition(new WeaponTransition( Mech_O01.m_chamber,		_abt_,	C11));

		// fire
		m_fsm.AddTransition(new WeaponTransition( C00,				__T__,	Trigger_C00));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C00,		_fin_,	C00));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C00,		_dto_,	C00));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C00,		_abt_,	C00));
		
		m_fsm.AddTransition(new WeaponTransition( C01,				__T__,	Trigger_C01));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C01,		_fin_,	C01));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C01,		_dto_,	C01));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C01,		_abt_,	C01));
		
		m_fsm.AddTransition(new WeaponTransition( C10,				__T__,	Trigger_C10, NULL, new WeaponGuardBattery(this)));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C10,		_fin_,	C00));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C10,		_rto_,	C00));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C10,		_abt_,	C00));
		
		m_fsm.AddTransition(new WeaponTransition( C11,				__T__,	Trigger_C11, NULL, new WeaponGuardHasAmmoAndBattery(this)));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C11,		_fin_,	C11));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C11,		_rto_,	C11));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C11,		_abt_,	C11));
		
		m_fsm.AddTransition(new WeaponTransition( C11,				__T__,	Trigger_C11L, NULL, new WeaponGuardBattery(this)));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C11L,	_fin_,	O01));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C11L,	_rto_,	O01));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C11L,	_abt_,	O01));
		
		m_fsm.AddTransition(new WeaponTransition( C10,				__T__,	Trigger_NB10, NULL, new WeaponGuardNoBattery(this)));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_NB10,		_fin_,	C10));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_NB10,		_rto_,	C10));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_NB10,		_abt_,	C10));
		
		m_fsm.AddTransition(new WeaponTransition( C11,				__T__,	Trigger_NB11, NULL, new WeaponGuardNoBattery(this)));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_NB11,		_fin_,	C11));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_NB11,		_rto_,	C11));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_NB11,		_abt_,	C11));
	
		m_fsm.AddTransition(new WeaponTransition( O00,				__T__,	Trigger_O00));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_O00,		_fin_,	O00));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_O00,		_dto_,	O00));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_O00,		_abt_,	O00));
		
		m_fsm.AddTransition(new WeaponTransition( O01,				__T__,	Trigger_O01));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_O01,		_fin_,	O01));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_O01,		_dto_,	O01));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_O01,		_abt_,	O01));
		
		m_fsm.AddTransition(new WeaponTransition( JF0,				__T__,	Trigger_JF0)); // opened fire.uncocked w mag
		m_fsm.AddTransition(new WeaponTransition(  Trigger_JF0,		_fin_,	JF0));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_JF0,		_dto_,	JF0));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_JF0,		_abt_,	JF0));
		
		m_fsm.AddTransition(new WeaponTransition( JF1,				__T__,	Trigger_JF1)); // opened fire.uncocked w mag
		m_fsm.AddTransition(new WeaponTransition(  Trigger_JF1,		_fin_,	JF1));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_JF1,		_dto_,	JF1));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_JF1,		_abt_,	JF1));
		

		m_fsm.AddTransition(new WeaponTransition( C10,				__TJ_,	Trigger_C10J, NULL, new WeaponGuardBattery(this)));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C10J,	_fin_,	JF0));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C10J,	_rto_,	JF0));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C10J,	_abt_,	JF0));		
		
		m_fsm.AddTransition(new WeaponTransition( C11,				__TJ_,	Trigger_C11J, NULL, new WeaponGuardBattery(this)));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C11J,	_fin_,	JF1));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C11J,	_rto_,	JF1));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C11J,	_abt_,	JF1));	


		// load cartridge
		m_fsm.AddTransition(new WeaponTransition( C00,				__L__,	Chamber_C00)); // chamber from closed=1
		m_fsm.AddTransition(new WeaponTransition(  Chamber_C00,		_fin_,	C10));
			Chamber_C00.AddTransition(new WeaponTransition( Chamber_C00.m_start,	_abt_,	C00));
			Chamber_C00.AddTransition(new WeaponTransition( Chamber_C00.m_eject,	_abt_,	O00));
			Chamber_C00.AddTransition(new WeaponTransition( Chamber_C00.m_chamber,	_abt_,	O00));
			Chamber_C00.AddTransition(new WeaponTransition( Chamber_C00.m_w4t,		_abt_,	C10));

		m_fsm.AddTransition(new WeaponTransition( C01,				__L__,	Chamber_C01)); // chamber from closed charged
		m_fsm.AddTransition(new WeaponTransition(  Chamber_C01,		_fin_,	C11));
			Chamber_C01.AddTransition(new WeaponTransition( Chamber_C01.m_start,	_abt_,	C01));
			Chamber_C01.AddTransition(new WeaponTransition( Chamber_C01.m_eject,	_abt_,	O01));
			Chamber_C01.AddTransition(new WeaponTransition( Chamber_C01.m_chamber,	_abt_,	O01));
			Chamber_C01.AddTransition(new WeaponTransition( Chamber_C01.m_w4t,		_abt_,	C11));
	
		m_fsm.AddTransition(new WeaponTransition( O00,				__L__,	Chamber_O00)); // chamber from closed charged
		m_fsm.AddTransition(new WeaponTransition(  Chamber_O00,		_fin_,	C10));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_O00,		_abt_ , O00, NULL, new WeaponGuardCurrentChamberEmpty(this) ));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_O00,		_abt_ , C10));
	
		m_fsm.AddTransition(new WeaponTransition( O01,				__L__,	Chamber_O01)); // chamber from closed charged
		m_fsm.AddTransition(new WeaponTransition(  Chamber_O01,		_fin_,	C11));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_O01,		_abt_,	O01, NULL, new WeaponGuardCurrentChamberEmpty(this) ));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_O01,		_abt_,	C11));

		// attach magazine (no mag in weapon)
		m_fsm.AddTransition(new WeaponTransition( C00,				__A__,	Attach_C00, NULL, new WeaponGuardCanAttachMag(this))); // attach from CLO/b0/m0
		m_fsm.AddTransition(new WeaponTransition(  Attach_C00,		_fin_,	C01, NULL, new WeaponGuardCurrentChamberEmpty(this)) );
		m_fsm.AddTransition(new WeaponTransition(  Attach_C00,		_fin_,	C11));
		//m_fsm.AddTransition(new WeaponTransition(  Attach_C00,		_abt_,	C11, NULL, new WeaponGuardCurrentChamberFull(this)) );
		//m_fsm.AddTransition(new WeaponTransition(  Attach_C00,		_abt_,	C01, NULL, new WeaponGuardHasMag(this)) );
		//m_fsm.AddTransition(new WeaponTransition(  Attach_C00,		_abt_,	C00));
			Attach_C00.AddTransition(new WeaponTransition( Attach_C00.m_start,		_abt_,	C00));
			Attach_C00.AddTransition(new WeaponTransition( Attach_C00.m_attach,		_abt_,	C00));
			Attach_C00.AddTransition(new WeaponTransition( Attach_C00.m_onCK,		_abt_,	C01));
			Attach_C00.AddTransition(new WeaponTransition( Attach_C00.m_chamber,	_abt_,	C11));		

		m_fsm.AddTransition(new WeaponTransition( C10,				__A__,	Attach_C10, NULL, new WeaponGuardCanAttachMag(this))); // attach from CLO/b1/m0
		m_fsm.AddTransition(new WeaponTransition(  Attach_C10,		_fin_,	C11));
		//m_fsm.AddTransition(new WeaponTransition(  Attach_C10,		_abt_,	C11, NULL, new WeaponGuardHasMag(this)) );
		//m_fsm.AddTransition(new WeaponTransition(  Attach_C10,		_abt_,	C10));
			Attach_C10.AddTransition(new WeaponTransition( Attach_C10.m_start,		_abt_,	C10));
			Attach_C10.AddTransition(new WeaponTransition( Attach_C10.m_attach,		_abt_,	C10));
	
		m_fsm.AddTransition(new WeaponTransition( O00,				__A__,	Attach_O00, NULL, new WeaponGuardCanAttachMag(this))); // attach from CLO/b0/m0
		m_fsm.AddTransition(new WeaponTransition(  Attach_O00,		_fin_,	C01, NULL, new WeaponGuardCurrentChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition(  Attach_O00,		_fin_,	C11));
			Attach_O00.AddTransition(new WeaponTransition( Attach_O00.m_start,		_abt_,	O00));
			Attach_O00.AddTransition(new WeaponTransition( Attach_O00.m_attach,		_abt_,	O00));
			Attach_O00.AddTransition(new WeaponTransition( Attach_O00.m_onCK,		_abt_,	C01));
			Attach_O00.AddTransition(new WeaponTransition( Attach_O00.m_chamber,	_abt_,	C11));
		
		m_fsm.AddTransition(new WeaponTransition( JF0,				__A__,	Attach_JF0, NULL, new WeaponGuardCanAttachMag(this))); // attach from JAM/b1/m0
		m_fsm.AddTransition(new WeaponTransition(  Attach_JF0,	_fin_,	JF1));
		//m_fsm.AddTransition(new WeaponTransition(  Attach_JF0,	_abt_,	JF1, NULL, new WeaponGuardHasMag(this)));
		//m_fsm.AddTransition(new WeaponTransition(  Attach_JF0,	_abt_,	JF0));
			Attach_JF0.AddTransition(new WeaponTransition( Attach_JF0.m_start,		_abt_,	JF0));
			Attach_JF0.AddTransition(new WeaponTransition( Attach_JF0.m_attach,		_abt_,	JF0));


		// replace magazine
		m_fsm.AddTransition(new WeaponTransition( C11,				__S__,	Reload_C11, NULL, new WeaponGuardCanSwapMag(this))); // swap in Chg/b1/m1
		m_fsm.AddTransition(new WeaponTransition(  Reload_C11,		_fin_,	C11));
		m_fsm.AddTransition(new WeaponTransition(  Reload_C11,		_abt_,	C11, NULL, new WeaponGuardHasMag(this)));
		m_fsm.AddTransition(new WeaponTransition(  Reload_C11,		_abt_,	C10));

	
		m_fsm.AddTransition(new WeaponTransition( C01,				__S__,	Reload_C01, NULL, new WeaponGuardCanSwapMag(this))); // swap in CLO/b0/m1
		m_fsm.AddTransition(new WeaponTransition(  Reload_C01,		_fin_,	C01, NULL, new WeaponGuardCurrentChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition(  Reload_C01,		_fin_,	C11));
		m_fsm.AddTransition(new WeaponTransition(  Reload_C01,		_abt_,	C11, NULL, new WeaponGuardCurrentChamberFull(this)) );
		m_fsm.AddTransition(new WeaponTransition(  Reload_C01,		_abt_,	C01, NULL, new WeaponGuardHasMag(this)) );
		m_fsm.AddTransition(new WeaponTransition(  Reload_C01,		_abt_,	C00));
		
	
		m_fsm.AddTransition(new WeaponTransition( O01,				__S__,	Reload_O01, NULL, new WeaponGuardCanSwapMag(this))); // swap in CLO/b0/m1
		m_fsm.AddTransition(new WeaponTransition(  Reload_O01,		_fin_,	C01, NULL, new WeaponGuardCurrentChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition(  Reload_O01,		_fin_,	C11));
			Reload_O01.AddTransition(new WeaponTransition( Reload_O01.m_start ,    _abt_,   O01));
			Reload_O01.AddTransition(new WeaponTransition( Reload_O01.m_eject,     _abt_,   O01));
			Reload_O01.AddTransition(new WeaponTransition( Reload_O01.m_detach,    _abt_,   O01));
			Reload_O01.AddTransition(new WeaponTransition( Reload_O01.m_hideOld,   _abt_,   O00));
			Reload_O01.AddTransition(new WeaponTransition( Reload_O01.m_swapMags,  _abt_,   O01));
			Reload_O01.AddTransition(new WeaponTransition( Reload_O01.m_attach,    _abt_,   O01));
			Reload_O01.AddTransition(new WeaponTransition( Reload_O01.m_onCK,      _abt_,   C01));
			Reload_O01.AddTransition(new WeaponTransition( Reload_O01.m_chamber,   _abt_,   C11));

		m_fsm.AddTransition(new WeaponTransition( JF1,				__S__,	Reload_JF1, NULL, new WeaponGuardCanSwapMag(this))); // swap in JAM/b1/m1
		m_fsm.AddTransition(new WeaponTransition(  Reload_JF1,		_fin_,	JF1));
		m_fsm.AddTransition(new WeaponTransition(  Reload_JF1,		_abt_,	JF1, NULL, new WeaponGuardHasMag(this)));
		m_fsm.AddTransition(new WeaponTransition(  Reload_JF1,		_abt_,	JF0));
			
      // @TODO: abort in jam

		// detach magazine
		m_fsm.AddTransition(new WeaponTransition( C11,				__D__,	Detach_C11, NULL, new WeaponGuardCanDetachMag(this))); // detach from Chg/b1/m1
		m_fsm.AddTransition(new WeaponTransition(  Detach_C11,		_fin_,	C10));
		m_fsm.AddTransition(new WeaponTransition(  Detach_C11,		_abt_,	C11, NULL, new WeaponGuardHasMag(this)));
		m_fsm.AddTransition(new WeaponTransition(  Detach_C11,		_abt_,	C10));
		
		m_fsm.AddTransition(new WeaponTransition( C01,				__D__,	Detach_C01, NULL, new WeaponGuardCanDetachMag(this))); // detach from Chg/b0/m1
		m_fsm.AddTransition(new WeaponTransition(  Detach_C01,		_fin_,	C00));
		m_fsm.AddTransition(new WeaponTransition(  Detach_C01,		_abt_,	C01, NULL, new WeaponGuardHasMag(this)));
		m_fsm.AddTransition(new WeaponTransition(  Detach_C01, 		_abt_,	C00));
		
		m_fsm.AddTransition(new WeaponTransition( O01,				__D__,	Detach_O01, NULL, new WeaponGuardCanDetachMag(this))); // detach from Dic/b0/m1
		m_fsm.AddTransition(new WeaponTransition(  Detach_O01,		_fin_,	O00));
		m_fsm.AddTransition(new WeaponTransition(  Detach_O01,		_abt_,	O01, NULL, new WeaponGuardHasMag(this)));
		m_fsm.AddTransition(new WeaponTransition(  Detach_O01,		_abt_,	O00));
		
		m_fsm.AddTransition(new WeaponTransition( JF1,				__D__,	Detach_JF1, NULL, new WeaponGuardCanDetachMag(this))); // detach from CLO/b1/m1 jammed
		m_fsm.AddTransition(new WeaponTransition(  Detach_JF1,		_fin_,	JF0));
		m_fsm.AddTransition(new WeaponTransition(  Detach_JF1,		_abt_,	JF1, NULL, new WeaponGuardHasMag(this)));
		m_fsm.AddTransition(new WeaponTransition(  Detach_JF1,		_abt_,	JF0));



		// unjam
		m_fsm.AddTransition(new WeaponTransition( JF0,				__U__,	Unjam_JF0)); // unjam nomag
		m_fsm.AddTransition(new WeaponTransition(  Unjam_JF0,		_fin_,	JF0, NULL, new WeaponGuardJammed(this)));
		m_fsm.AddTransition(new WeaponTransition(  Unjam_JF0,		_fin_,	C00, NULL, new GuardNot(new WeaponGuardJammed(this))));
		m_fsm.AddTransition(new WeaponTransition(  Unjam_JF0,		_abt_,	JF0));
		
		m_fsm.AddTransition(new WeaponTransition( JF1,				__U__,	Unjam_JF1)); // unjam with mag with ammo
		m_fsm.AddTransition(new WeaponTransition(  Unjam_JF1,		_fin_,	JF1, NULL, new WeaponGuardJammed(this)));
		m_fsm.AddTransition(new WeaponTransition(  Unjam_JF1,		_fin_,	C01, NULL, new WeaponGuardCurrentChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition(  Unjam_JF1,		_fin_,	C11));
		m_fsm.AddTransition(new WeaponTransition(  Unjam_JF1,		_abt_,	JF1));

		m_fsm.SetInitialState(C00);

		SelectionBulletHide();
		HideMagazine();

		m_fsm.Start();*/


		/*
		
functioning bolt action
		m_abilities.Insert(new AbilityRecord(WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_CLOSED));
		m_abilities.Insert(new AbilityRecord(WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_STARTLOOPABLE_CLOSED_KEEP));
		m_abilities.Insert(new AbilityRecord(WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_STARTLOOPABLE_CLOSED));
		m_abilities.Insert(new AbilityRecord(WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_ENDLOOPABLE));
		m_abilities.Insert(new AbilityRecord(WeaponActions.UNJAMMING, WeaponActionUnjammingTypes.UNJAMMING_START));
		m_abilities.Insert(new AbilityRecord(WeaponActions.UNJAMMING, WeaponActionUnjammingTypes.UNJAMMING_END));
		m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_NORMAL));
		m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_COCKED));
		m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_UNCOCKED));
		m_abilities.Insert(new AbilityRecord(WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY));
		
		
		C0 = new BARIMEmptyDischarged(this, NULL, BARIMAnimState.DEFAULT);
		C1 = new BARIMLoadedCharged(this, NULL, BARIMAnimState.DEFAULT);
		JF = new BARIMLoadedJammed(this, NULL, BARIMAnimState.JAMMED);
		D1 = new BARIMLoadedDischarged(this, NULL, BARIMAnimState.DEFAULT);
		
		WeaponStateBase	Mech_C1 = new WeaponChargingInnerMag(this, NULL, WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_CLOSED);
		WeaponStateBase	Mech_D1 = new WeaponChargingInnerMag(this, NULL, WeaponActions.MECHANISM, WeaponActionMechanismTypes.MECHANISM_CLOSED);

		
		LoopedChambering Chamber_C0 = new LoopedChambering(this, NULL, WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_STARTLOOPABLE_CLOSED, WeaponActionChamberingTypes.CHAMBERING_ENDLOOPABLE);
		LoopedChambering Chamber_C1 = new LoopedChambering(this, NULL, WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_STARTLOOPABLE_CLOSED_KEEP, WeaponActionChamberingTypes.CHAMBERING_ENDLOOPABLE);
		LoopedChambering Chamber_D1 = new LoopedChambering(this, NULL, WeaponActions.CHAMBERING, WeaponActionChamberingTypes.CHAMBERING_STARTLOOPABLE_CLOSED, WeaponActionChamberingTypes.CHAMBERING_ENDLOOPABLE);
		
		WeaponStateBase	Unjam_JF = new WeaponUnjamming(this, NULL, WeaponActions.UNJAMMING, WeaponActionUnjammingTypes.UNJAMMING_START);
		
		WeaponStateBase	Trigger_C0 = new WeaponDryFire(this, NULL, WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY);
		WeaponStateBase	Trigger_C1 = new WeaponFire(this, NULL, WeaponActions.FIRE, WeaponActionFireTypes.FIRE_NORMAL);
		WeaponStateBase	Trigger_D1 = new WeaponDryFire(this, NULL, WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY);
		WeaponStateBase	Trigger_JF = new WeaponDryFire(this, NULL, WeaponActions.FIRE, WeaponActionFireTypes.FIRE_DRY);
	
		
		WeaponStateBase	Trigger_C1J = new WeaponFireToJam(this, NULL, WeaponActions.FIRE, WeaponActionFireTypes.FIRE_JAM);

		
		WeaponEventBase _fin_ = new WeaponEventHumanCommandActionFinished;
		WeaponEventBase __L__ = new WeaponEventLoad1Bullet;
		WeaponEventBase __T__ = new WeaponEventTrigger;
		WeaponEventBase __TJ_ = new WeaponEventTriggerToJam;
		WeaponEventBase __U__ = new WeaponEventUnjam;
		WeaponEventBase	__M__ = new WeaponEventMechanism;
		WeaponEventBase _abt_ = new WeaponEventHumanCommandActionAborted;
		WeaponEventBase _rto_ = new WeaponEventReloadTimeout;
		WeaponEventBase _dto_ = new WeaponEventDryFireTimeout;

		m_fsm = new WeaponFSM();
		
		// Mechanism
//----------------------------------------
		m_fsm.AddTransition(new WeaponTransition( C0,			__M__,	Mech_C1));
				
		m_fsm.AddTransition(new WeaponTransition( C1,			__M__,	Mech_C1));
		m_fsm.AddTransition(new WeaponTransition(  Mech_C1,		_fin_,	C0, NULL, new WeaponGuardCurrentChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition(  Mech_C1,		_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Mech_C1,		_abt_,	C0, NULL, new WeaponGuardCurrentChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition(  Mech_C1,		_abt_,	C1));
		
		m_fsm.AddTransition(new WeaponTransition( D1,			__M__,	Mech_D1));
		m_fsm.AddTransition(new WeaponTransition(  Mech_D1,		_fin_,	C0, NULL, new WeaponGuardCurrentChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition(  Mech_D1,		_fin_,	D1, NULL, new WeaponGuardCurrentChamberFiredOut(this)));
		m_fsm.AddTransition(new WeaponTransition(  Mech_D1,		_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Mech_D1,		_abt_,	C0, NULL, new WeaponGuardCurrentChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition(  Mech_D1,		_abt_,	D1, NULL, new WeaponGuardCurrentChamberFiredOut(this)));
		m_fsm.AddTransition(new WeaponTransition(  Mech_D1,		_abt_,	C1));
		
		
//----------------------------------------
		
		m_fsm.AddTransition(new WeaponTransition( C0,			__L__,	Chamber_C0));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_C0,	_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_C0,	_abt_,	C0, NULL, new WeaponGuardCurrentChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_C0,	_abt_,	C1));
		
		m_fsm.AddTransition(new WeaponTransition( C1,			__L__,	Chamber_C1, NULL, new GuardNot(new WeaponGuardInnerMagazineFullShareChamber(this))));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_C1,	_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_C1,	_abt_,	C1));
		
		m_fsm.AddTransition(new WeaponTransition( D1,			__L__,	Chamber_D1));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_D1,	_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_D1,	_abt_,	D1, NULL, new WeaponGuardCurrentChamberFiredOut(this)));
		m_fsm.AddTransition(new WeaponTransition(  Chamber_D1,	_abt_,	C1));
		
//------------------------------------------
		
		m_fsm.AddTransition(new WeaponTransition( JF, 			__U__,	Unjam_JF));
		m_fsm.AddTransition(new WeaponTransition(  Unjam_JF,	_fin_,	JF, NULL, new WeaponGuardJammed(this)));
		m_fsm.AddTransition(new WeaponTransition(  Unjam_JF,	_fin_,	C0, NULL, new WeaponGuardCurrentChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition(  Unjam_JF,	_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Unjam_JF,	_abt_,	JF, NULL, new WeaponGuardJammed(this)));
		m_fsm.AddTransition(new WeaponTransition(  Unjam_JF,	_abt_,	C0, NULL, new WeaponGuardCurrentChamberEmpty(this)));
		m_fsm.AddTransition(new WeaponTransition(  Unjam_JF,	_abt_,	C1));
		
				
		m_fsm.AddTransition(new WeaponTransition( C1,				__T__,	Trigger_C1, NULL, new WeaponGuardHasAmmoAndBattery(this)));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C1,		_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C1,		_rto_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C1,		_abt_,	C1));
		

		
		m_fsm.AddTransition(new WeaponTransition( C1,				__T__,	Trigger_D1, NULL, new WeaponGuardNoBattery(this)));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_D1,		_fin_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_D1,		_rto_,	C1));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_D1,		_abt_,	C1));

		
//-----------------------------------------
		
		// fire
		m_fsm.AddTransition(new WeaponTransition( C0,			__T__,	Trigger_C0)); // fire.cocked
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C0,	_fin_,	C0));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C0,	_dto_,	C0));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C0,	_abt_,	C0));
		
		m_fsm.AddTransition(new WeaponTransition( C1,			__T__,	Trigger_C1)); // fire.cocked
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C1,	_fin_,	D1));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C1,	_rto_,	D1));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C1,	_abt_,	D1));
		
		m_fsm.AddTransition(new WeaponTransition( D1,			__T__,	Trigger_D1)); // fire.cocked
		m_fsm.AddTransition(new WeaponTransition(  Trigger_D1,	_fin_,	D1));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_D1,	_dto_,	D1));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_D1,	_abt_,	D1));
		
		m_fsm.AddTransition(new WeaponTransition( JF,			__T__,	Trigger_JF)); // fire.cocked
		m_fsm.AddTransition(new WeaponTransition(  Trigger_JF,	_fin_,	JF));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_JF,	_dto_,	JF));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_JF,	_abt_,	JF));
		
		
		m_fsm.AddTransition(new WeaponTransition( C1,			__TJ_,	Trigger_C1J)); // fire.cocked
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C1J,	_fin_,	JF));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C1J,	_rto_,	JF));
		m_fsm.AddTransition(new WeaponTransition(  Trigger_C1J,	_abt_,	JF));
		
//---------------------------------------------	
		
		m_fsm.SetInitialState(C0);

		SelectionBulletHide();
		HideMagazine();

		m_fsm.Start();
		*/
		