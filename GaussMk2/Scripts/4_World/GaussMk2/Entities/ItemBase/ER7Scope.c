
class ER7ScopeLayoutHandler: ScriptedWidgetEventHandler
{
	protected Widget m_LayoutRoot;
	
	protected TextWidget range_text;
		
	void ER7ScopeLayoutHandler()
	{
		Print("ER7ScopeLayoutHandler");

	}
	
	void ~ER7ScopeLayoutHandler()
	{	
		Print("~ER7ScopeLayoutHandler");
	}
	
	void OnWidgetScriptInit(Widget w)
	{
		m_LayoutRoot = w;
		m_LayoutRoot.SetHandler(this);
	}
	
	void UpdateHud(array<ref RaycastRVResult> raycast_result)
	{
		range_text.SetText("RNG MAX");
		if (raycast_result.Count() > 0) {
			float distance = vector.Distance(GetGame().GetCurrentCameraPosition(), raycast_result[0].pos);
			distance = Math.Round(distance);
		
			// Set Range
			range_text.SetText(distance.ToString()); 
		}
	}
}


class ER7Scope: ItemOptics
{
	protected bool m_IsEnabled;	
	protected Widget m_ScopeWidget;
	protected ER7ScopeLayoutHandler m_ER7ScopeLayoutHandler;
	
	protected ref Timer m_Timer;
	
	override void OnWorkStart()
	{
		super.OnWorkStart();
		m_ScopeWidget = GetGame().GetWorkspace().CreateWidgets("Namalsk_Weapon/GaussMk2/GUI/layouts/gauss_scope.layout");
		m_ScopeWidget.GetScript(m_ER7ScopeLayoutHandler);
		
		
		m_Timer = new Timer(CALL_CATEGORY_GUI);		
		m_Timer.Run(0.1, this, "UpdateHud", null, true);
		
	}
	
	void UpdateHud()
	{
		
		if (!(GetGame().IsClient() || !GetGame().IsMultiplayer())) {
			return;
		}
		
		RaycastRVParams raycast_params(GetGame().GetCurrentCameraPosition(), GetGame().GetCurrentCameraPosition() + (GetGame().GetCurrentCameraDirection() * 1000), GetGame().GetPlayer());
				
		array<ref RaycastRVResult> raycast_results = {};
		DayZPhysics.RaycastRVProxy(raycast_params, raycast_results);
		
		// Set Human Detection
		SetSimpleHiddenSelectionState(GetHiddenSelectionIndex("contact_marker"), false);
		foreach (RaycastRVResult result: raycast_results) {
			if (result.obj.IsAlive() && result.obj.IsMan()) {
				SetSimpleHiddenSelectionState(GetHiddenSelectionIndex("contact_marker"), true);
			}
		}
		
		if (m_ER7ScopeLayoutHandler) {
			m_ER7ScopeLayoutHandler.UpdateHud(raycast_results);
		}	
	}
		
	
	override void OnWorkStop()
	{
		super.OnWorkStop();
		
		if (m_Timer) {
			m_Timer.Stop();
			delete m_Timer;
		}
		
		if (m_ScopeWidget) {
			m_ScopeWidget.Unlink();
		}
	}
}