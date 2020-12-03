class ER7_ScopeLayoutHandler: Controller
{	
	protected int Range;
	protected string Altitude;
	protected string Angle;
		
	protected ImageWidget contact_marker;
	
	protected ref Timer m_Timer;
	
	void ER7_ScopeLayoutHandler()
	{
		Print("ER7_ScopeLayoutHandler");
		m_Timer = new Timer(CALL_CATEGORY_GUI);		
		m_Timer.Run(0.1, this, "UpdateHud", null, true);
	}
	
	void ~ER7_ScopeLayoutHandler()
	{	
		Print("~ER7_ScopeLayoutHandler");
		m_Timer.Stop();
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
			
		vector begin = GetGame().GetCurrentCameraPosition();
		vector end = begin + (GetGame().GetCurrentCameraDirection() * 2500);
		vector contact_pos, contact_dir;
		int contact_component;
		set<Object> results = new set<Object>();
		
		DayZPhysics.RaycastRV(begin, end, contact_pos, contact_dir, contact_component, results, null, player, false, false);
		
		Range = vector.Distance(begin, contact_pos);
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
		contact_marker.Show(false);
		foreach (Object result: results) {
			if (result.IsAlive() && result.IsMan()) {
				contact_marker.Show(true);
			}
		}
	}
}

class ER7_Scope: ItemOptics
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