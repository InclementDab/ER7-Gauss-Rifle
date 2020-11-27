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



