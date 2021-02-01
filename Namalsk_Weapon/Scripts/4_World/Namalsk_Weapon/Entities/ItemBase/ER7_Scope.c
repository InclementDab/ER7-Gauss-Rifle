class ER7_Scope_View_Controller: Controller
{	
	protected string Range;
	protected string Altitude;
	protected string Angle;
	protected string Range_Force;
	protected string Battery_Level;
		
	protected ImageWidget contact_marker;
	protected TextWidget rng_base;
	protected TextWidget bat_base;
	
	protected ref Timer m_Timer;
	
	protected ER7_Scope m_Scope;
	
	void ER7_Scope_View_Controller()
	{
		m_Timer = new Timer(CALL_CATEGORY_GUI);		
		m_Timer.Run(0.1, this, "UpdateHud", null, true);
	}
	
	void ~ER7_Scope_View_Controller()
	{	
		Print("~ER7_Scope_View_Controller");
		if (m_Timer) {
			m_Timer.Stop();
		}
		
		delete m_Timer;
	}
	
	void UpdateHud()
	{
		if (!IsMissionClient()) {
			return;
		}
	
		PlayerBase player = GetGame().GetPlayer();
		if (!player) {
			return;
		}
				
		// Edge Case
		if (m_Scope && !m_Scope.GetHierarchyRootPlayer()) {			
 			m_Scope.CloseScope();
			return;
		}
		
		bool is_gauss = (m_Scope && m_Scope.GetHierarchyParent() && m_Scope.GetHierarchyParent().IsInherited(ER7_Gauss));
			
		vector begin = GetGame().GetCurrentCameraPosition();
		vector end = begin + (GetGame().GetCurrentCameraDirection() * 5000);
		vector contact_pos, contact_dir;
		int component;
		set<Object> results = new set<Object>();
		Object unused;
		float hit_fract;
		float distance;
		// main raycast
		// Set Range
		if (DayZPhysics.RayCastBullet(begin, end, PhxInteractionLayers.TERRAIN | PhxInteractionLayers.CHARACTER | PhxInteractionLayers.BUILDING, player, unused, contact_pos, contact_dir, hit_fract)) {
			distance = vector.Distance(begin, contact_pos);
			if (is_gauss) {
				// this does the math for TTI when gauss is attached
				Range = "" + distance / 3500; // 3500 m/s
				Range = Range[0] + Range[1] + Range[2] + "s";
			} else {
				// default to normal ranging
				Range = ((int)distance).ToString();
			}
		} else {
			Range = "- - -";
		}
		
		NotifyPropertyChanged("Range");
		
		vector player_pos = player.GetPosition();
		vector player_ori = player.GetDirection();
		
		// Set ALT
		Altitude = string.Format("ALT: %1", Math.Round(contact_pos[1]));
		NotifyPropertyChanged("Altitude");
		
		float ang = Math.Atan2(player_pos[2] - contact_pos[2], player_pos[0] - contact_pos[0]) * Math.RAD2DEG;
		
		// Set ANG
		Angle = string.Format("ANG: %1", Math.Round(ang));
		NotifyPropertyChanged("Angle");
		
		// Set Force Range (gauss only)
		if (is_gauss) {
			Range_Force = string.Format("Range: %1", (int)distance);
			NotifyPropertyChanged("Range_Force");
		} 
		
		rng_base.Show(is_gauss);
		
		// Set Battery Level (gauss only)
		if (is_gauss) {
			string battery_final;
			if (m_Scope.GetHierarchyParent().GetCompEM() && m_Scope.GetHierarchyParent().GetCompEM().GetEnergySource()) {
				string battery_exact = ((m_Scope.GetHierarchyParent().GetCompEM().GetEnergySource().GetQuantity() / m_Scope.GetHierarchyParent().GetCompEM().GetEnergySource().GetQuantityMax()) * 100).ToString();
				for (int i = 0; i < battery_exact.Length(); i++) {
					if (i <= 3) {
						battery_final += battery_exact[i];
					}
				}
			} else {
				// just a backup if no battery is found
				battery_final = "0";
			}
			
			Battery_Level = string.Format("ER7 Battery: %1%%", battery_final);
			NotifyPropertyChanged("Battery_Level");
		}
		
		bat_base.Show(is_gauss);
		
		
		// Set Human Detection
		// we do a second raycast since RaycastBullet doesnt have a way of returning characters (PhxInteractionLayers bug?)
		DayZPhysics.RaycastRV(begin, end, contact_pos, contact_dir, component, results); 
		contact_marker.Show(false);
		foreach (Object result: results) {
			if (result && result.IsAlive() && result.IsMan() && result != player) {
				contact_marker.Show(true);
			}
		}
	}
	
	void SetScope(ER7_Scope scope)
	{
		m_Scope = scope;
	}
}

class ER7_Scope_View: ScriptViewTemplate<ER7_Scope_View_Controller>
{
	void ER7_Scope_View(ER7_Scope scope)
	{
		GetTemplateController().SetScope(scope);
	}
	
	override string GetLayoutFile()
	{
		return "Namalsk_Weapon/GaussMk2/GUI/layouts/gauss_scope.layout";
	}
}

class ER7_Scope: ItemOptics
{
	protected ref ER7_Scope_View m_ScopeWidget;

	void ~ER7_Scope()
	{
		CloseScope();
	}
	
	override void OnWorkStart()
	{
		super.OnWorkStart();
		if (IsMissionClient() && GetGame().GetPlayer() == GetHierarchyRootPlayer() && IsInOptics()) {	
			if (m_ScopeWidget) {
				delete m_ScopeWidget;
			}
			
			m_ScopeWidget = new ER7_Scope_View(this);
		}
	}

	override void OnWorkStop()
	{
		super.OnWorkStop();		
		CloseScope();
	}
	
	void CloseScope()
	{
		if (IsMissionClient() && GetGame().GetPlayer() == GetHierarchyRootPlayer()) {
			delete m_ScopeWidget;
		}
	}
}