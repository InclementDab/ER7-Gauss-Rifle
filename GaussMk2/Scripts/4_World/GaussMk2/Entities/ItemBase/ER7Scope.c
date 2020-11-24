class ER7Scope: ItemOptics
{
	protected bool m_IsEnabled;
	
	TextWidget test_widget;
	
	/*
	override void StartPeriodicMeasurement()
	{
		if (!m_Timer) {
			m_Timer = new Timer(CALL_CATEGORY_GAMEPLAY);
		}
		
		m_RangeText = TextWidget.Cast(GetGame().GetWorkspace().CreateWidgets( "gui/layouts/gameplay/rangefinder_hud.layout"));
		
		m_Timer.Run(GetMeasurementUpdateInterval(), this, "DoMeasurement", null, true);
	}
	
	override void StopPeriodicMeasurement()
	{
		if (m_Timer) {
			m_Timer.Stop();
		}
		
		if (m_RangeText) {
			delete m_RangeText;
		}
	}*/
	
	override void OnWorkStart()
	{
		super.OnWorkStart();
		Print("WorkStart");
	}
	
	override void OnWorkStop()
	{
		super.OnWorkStop();
		Print("WorkStop");
	}
	
	override void ShowReddot(bool state)
	{
		
		Print("ShowReddot");
		if (m_IsEnabled == state) {
			return;
		}
		
		m_IsEnabled = state;
		
		if (test_widget) {
			test_widget.Unlink();
		}
		
		if (m_IsEnabled) {
			test_widget = GetGame().GetWorkspace().CreateWidgets("gui/layouts/gameplay/rangefinder_hud.layout");
		} else {
			test_widget.Unlink();
		}
		
		test_widget.SetText("Tiny dick jimmy");
	}
}