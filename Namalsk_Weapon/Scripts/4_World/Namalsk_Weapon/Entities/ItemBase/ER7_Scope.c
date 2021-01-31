class ER7_ScopeLayoutHandler: Controller
{	
	protected string Range;
	protected string Altitude;
	protected string Angle;
		
	protected ImageWidget contact_marker;
	
	protected ref Timer m_Timer;
	
	protected ER7_Scope m_Scope;
	
	void ER7_ScopeLayoutHandler()
	{
		m_Timer = new Timer(CALL_CATEGORY_GUI);		
		m_Timer.Run(0.1, this, "UpdateHud", null, true);
	}
	
	void ~ER7_ScopeLayoutHandler()
	{	
		if (m_Timer) {
			m_Timer.Stop();
		}
		
		delete m_Timer;
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
		
		// Edge Case
		if (m_Scope && player.IsUnconscious()) {
			if (m_Timer) {
				m_Timer.Stop();
			}
		
			m_Scope.CloseScope();
			return;
		}
			
		vector begin = GetGame().GetCurrentCameraPosition();
		vector end = begin + (GetGame().GetCurrentCameraDirection() * 5000);
		vector contact_pos, contact_dir;
		int component;
		set<Object> results = new set<Object>();
		Object unused;
		float hit_fract;
		
		// main raycast
		// Set Range
		if (DayZPhysics.RayCastBullet(begin, end, PhxInteractionLayers.TERRAIN | PhxInteractionLayers.CHARACTER | PhxInteractionLayers.BUILDING, player, unused, contact_pos, contact_dir, hit_fract)) {
			float distance = vector.Distance(begin, contact_pos);
			if (m_Scope && m_Scope.GetHierarchyParent() && m_Scope.GetHierarchyParent().IsInherited(ER7_Gauss)) {
				Range = "" + distance / 3500; // 3500 m/s
				Range = Range[0] + Range[1] + Range[2] + "s";
			} else {
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

class ER7_Scope: ItemOptics
{
	protected Widget m_ScopeWidget;

	void ~ER7_Scope()
	{
		if (m_ScopeWidget && IsMissionClient() && GetGame().GetPlayer() == GetHierarchyRootPlayer()) {
			m_ScopeWidget.Unlink();
		}
	}
	
	override void OnWorkStart()
	{
		super.OnWorkStart();
		if (IsMissionClient() && GetGame().GetPlayer() == GetHierarchyRootPlayer() && IsInOptics()) {
			m_ScopeWidget = GetGame().GetWorkspace().CreateWidgets("Namalsk_Weapon/GaussMk2/GUI/layouts/gauss_scope.layout");
			ER7_ScopeLayoutHandler scope_handler;
			m_ScopeWidget.GetScript(scope_handler);
			if (scope_handler) {
				scope_handler.SetScope(this);
			}
		}
	}

	override void OnWorkStop()
	{
		super.OnWorkStop();		
		CloseScope();
	}
	
	void CloseScope()
	{
		if (m_ScopeWidget && IsMissionClient() && GetGame().GetPlayer() == GetHierarchyRootPlayer()) {
			m_ScopeWidget.Unlink();
		}
	}
}