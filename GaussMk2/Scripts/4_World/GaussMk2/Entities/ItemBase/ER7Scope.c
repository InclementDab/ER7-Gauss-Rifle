class ER7Scope: ItemOptics
{
	protected bool m_IsEnabled;
	
	protected Widget m_ScopeWidget;
	
	protected ref Timer m_Timer;
		
	override void OnWorkStart()
	{
		super.OnWorkStart();
		
		m_ScopeWidget = GetGame().GetWorkspace().CreateWidgets("Namalsk_Weapon/GUI/layouts/gauss_scope.layout");
		
		
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
		if (!(GetGame().IsClient() || !GetGame().IsMultiplayer())) {
			return;
		}
		
		vector begin = GetGame().GetCurrentCameraPosition();
		vector end = begin + (GetGame().GetCurrentCameraDirection() * 1000);
		vector contact_pos, contact_dir;
		int contact_component;
		
		DayZPhysics.RaycastRV(begin, end, contact_pos, contact_dir, contact_component, null, null, GetGame().GetPlayer(), false, false, ObjIntersectIFire);
		
		float distance = vector.Distance(begin, contact_pos);
		distance = Math.Round(distance);
		
		if (m_ScopeWidget) {
			m_ScopeWidget.SetText(distance.ToString());
		}
	}
}