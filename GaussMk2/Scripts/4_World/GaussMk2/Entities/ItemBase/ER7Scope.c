class ER7Scope: ItemOptics
{
	protected bool m_IsEnabled;
	
	protected TextWidget test_widget;
	
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
		
		test_widget = GetGame().GetWorkspace().CreateWidgets("gui/layouts/gameplay/rangefinder_hud.layout");
		test_widget.SetText("Tiny dick jimmy");
		Print(test_widget);
	}
	
	override void OnWorkStop()
	{
		super.OnWorkStop();
		Print("WorkStop");
		
		Print(test_widget);
		if (test_widget) {
			test_widget.Unlink();
		}
	}
}