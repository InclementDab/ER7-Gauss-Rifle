class ER7Scope: ItemOptics
{
	protected bool m_IsEnabled;
	
	protected TextWidget m_ScopeWidget;
	
	protected ref Timer m_Timer;
		
	override void OnWorkStart()
	{
		super.OnWorkStart();
		
		m_ScopeWidget = GetGame().GetWorkspace().CreateWidgets("gui/layouts/gameplay/rangefinder_hud.layout");
		
		
		if (!m_Timer) {
			m_Timer = new Timer(CALL_CATEGORY_GAMEPLAY);
		}
		
		
		m_Timer.Run(0.1, this, "UpdateHud", null, true);
	}
	
	override void OnWorkStop()
	{
		super.OnWorkStop();


		if (m_ScopeWidget) {
			m_ScopeWidget.Unlink();
		}
		
		if (m_Timer) {
			m_Timer.Stop();
		}
	}
	
	void UpdateHud()
	{
		vector begin = GetGame().GetCurrentCameraPosition();
		vector end = GetGame().GetCurrentCameraPosition() + GetGame().GetCurrentCameraDirection() * 1000;
		vector contact_pos, contact_dir;
		int contact_component;
		
		DayZPhysics.RaycastRV(begin, end, contact_pos, contact_dir, contact_component);
		
		float distance = vector.Distance(begin, contact_pos);
		Print(distance);
		
		if (m_ScopeWidget) {
			m_ScopeWidget.SetText(distance.ToString());
		}
	}
}