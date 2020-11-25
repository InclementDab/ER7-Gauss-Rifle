
class ER7ScopeLayoutHandler: ScriptedWidgetEventHandler
{
	protected Widget m_LayoutRoot;
	
	protected TextWidget range_text;
	protected ImageWidget contact_image;
	
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
		Print("init");
		m_LayoutRoot = w;
		m_LayoutRoot.SetHandler(this);
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
		set<Object> results = new set<Object>();
		
		DayZPhysics.RaycastRV(begin, end, contact_pos, contact_dir, contact_component, results, null, GetGame().GetPlayer(), false, false);
		
		float distance = vector.Distance(begin, contact_pos);
		distance = Math.Round(distance);
		
		// Set Range
		range_text.SetText(distance.ToString()); 
		
		// Set Human Detection
		contact_image.Show(false);
		foreach (Object result: results) {
			if (result.IsAlive() && result.IsMan()) {
				contact_image.Show(true);
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
		Print("WorkStart");
		m_ScopeWidget = GetGame().GetWorkspace().CreateWidgets("Namalsk_Weapon/GaussMk2/GUI/layouts/gauss_scope.layout");
		Print(m_ScopeWidget);
	}
	
	override void OnWorkStop()
	{
		super.OnWorkStop();
		Print("OnWorkStop");
		if (m_ScopeWidget) {
			m_ScopeWidget.Unlink();
		}
	}
}