class ER7ScopeLayoutHandler: ScriptedWidgetEventHandler
{
	protected Widget m_LayoutRoot;
	
	protected TextWidget range_text;
	protected TextWidget alt_base;
	protected TextWidget ang_base;
	
	protected ImageWidget contact_marker;
	
	protected ref Timer m_Timer;
	
	void ER7ScopeLayoutHandler()
	{
		Print("ER7ScopeLayoutHandler");
		m_Timer = new Timer(CALL_CATEGORY_GUI);		
		m_Timer.Run(0.1, this, "UpdateHud", null, true);
	}
	
	void ~ER7ScopeLayoutHandler()
	{	
		Print("~ER7ScopeLayoutHandler");
		m_Timer.Stop();
		delete m_Timer;
	}
	
	void OnWidgetScriptInit(Widget w)
	{
		m_LayoutRoot = w;
		m_LayoutRoot.SetHandler(this);
	}
	
		
	void UpdateHud()
	{
		if (!(GetGame().IsClient() || !GetGame().IsMultiplayer())) {
			return;
		}
	
		PlayerBase player = GetGame().GetPlayer();
		if (!player) {
			return;
		}
			
		vector begin = GetGame().GetCurrentCameraPosition();
		vector end = begin + (GetGame().GetCurrentCameraDirection() * 2500);
		vector contact_pos, contact_dir;
		int contact_component;
		set<Object> results = new set<Object>();
		
		DayZPhysics.RaycastRV(begin, end, contact_pos, contact_dir, contact_component, results, null, player, false, false);
		
		float distance = vector.Distance(begin, contact_pos);
		distance = Math.Round(distance);
		
		// Set Range
		range_text.SetText(distance.ToString()); 
		
		vector player_pos = player.GetPosition();
		vector player_ori = player.GetDirection();
		
		// Set ALT
		alt_base.SetText(string.Format("ALT: %1", Math.Round(contact_pos[1])));
		
		float ang = Math.Atan2(player_pos[2] - contact_pos[2], player_pos[0] - contact_pos[0]) * Math.RAD2DEG;
		
		// Set ANG
		ang_base.SetText(string.Format("ANG: %1", Math.Round(ang)));
		
		// Set Human Detection
		contact_marker.Show(false);
		foreach (Object result: results) {
			if (result.IsAlive() && result.IsMan()) {
				contact_marker.Show(true);
			}
		}
	}
}

class ER7Scope: ItemOptics
{
	protected bool m_IsEnabled;	
	protected Widget m_ScopeWidget;
	
	override void OnWorkStart()
	{
		super.OnWorkStart();
		m_ScopeWidget = GetGame().GetWorkspace().CreateWidgets("Namalsk_Weapon/GaussMk2/GUI/layouts/gauss_scope.layout");
	}
	

	override void OnWorkStop()
	{
		super.OnWorkStop();		
		if (m_ScopeWidget) {
			m_ScopeWidget.Unlink();
		}
	}
}


static const ref array<string> GAUSS_LIGHTNING_BOLT_TYPES = { "vfx_gauss_thunderboltnorm", "vfx_gauss_thunderboltheavy" };

class C3_Gauss: FAL_Base
{
	override void EEFired(int muzzleType, int mode, string ammoType)
	{
		Print("EEFired");
		
		if (GetGame().IsClient() || !GetGame().IsMultiplayer()) {
			
			for (int i = 0; i < 10; i++) {
				vector pos = GetPosition();
				vector ori = 180 * Vector(Math.RandomFloat01(), Math.RandomFloat01(), Math.RandomFloat01());
				float scl = GetScale() * 0.05;
				thread CreateFireBolt(pos, ori, scl);
			}
			
			Print("Pew electric effects!");
		}
		
		super.EEFired(muzzleType, mode, ammoType);
	}
	
	private void CreateFireBolt(vector position, vector orientation, float scale)
	{
		Print("CreateFireBolt " + position);
		Object bolt = GetGame().CreateObjectEx(GAUSS_LIGHTNING_BOLT_TYPES.GetRandomElement(), position, ECE_LOCAL);
		if (!bolt) return;
		bolt.SetOrientation(orientation);
		bolt.SetScale(scale);
		//Sleep(25);
		//bolt.Delete();
	}
}

modded class WeaponParticlesBase
{
	override void OnActivate(ItemBase weapon, int muzzle_index, string ammoType, ItemBase muzzle_owner, ItemBase suppressor, string config_to_search)
	{
		Print("onactivate");
		Print(weapon);
		Print(muzzle_owner);
		
		super.OnActivate(weapon, muzzle_index, ammoType, muzzle_owner, suppressor, config_to_search);
	}
}