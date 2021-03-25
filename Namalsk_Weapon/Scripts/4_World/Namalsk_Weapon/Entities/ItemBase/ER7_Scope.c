class ER7_Scope: ItemOptics
{
	protected ref ER7_Scope_View m_ScopeWidget;
	protected ref Timer m_Timer;
	
	void ~ER7_Scope()
	{
		delete m_ScopeWidget;
		delete m_Timer;
	}
	
	override void OnWorkStart()
	{
		super.OnWorkStart();
		if (IsMissionClient() && GetGame().GetPlayer() == DayZPlayer.Cast(GetHierarchyRootPlayer()) && IsInOptics()) {	
			if (m_ScopeWidget) {
				return;
			}
			
			m_ScopeWidget = new ER7_Scope_View();
			m_Timer = new Timer(CALL_CATEGORY_GUI);		
			m_Timer.Run(0.05, this, "OnTimer", null, true);
		}
	}

	override void OnWorkStop()
	{
		super.OnWorkStop();		
		if (IsMissionClient()) {
			if (m_Timer) {
				m_Timer.Stop();
			}
		
			delete m_Timer;
			delete m_ScopeWidget;
		}
	}
	
	void OnTimer()
	{
		if (IsMissionClient() && GetGame().GetPlayer() == DayZPlayer.Cast(GetHierarchyRootPlayer())) {
			m_ScopeWidget.OnTimer(this);
		}
	}
}