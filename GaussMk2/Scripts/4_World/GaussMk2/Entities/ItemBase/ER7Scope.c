
class ER7ScopeLayoutHandler: ScriptedWidgetEventHandler
{
	protected Widget m_LayoutRoot;
	protected TextWidget range_text;
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
		Print("UpdateHud");
		Print(range_text);
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
		
		range_text.SetText("tiny pp");
		range_text.SetText(distance.ToString()); 
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