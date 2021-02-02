class ER7_TeleportLight: ScriptedLightBase
{
	void ER7_TeleportLight()
	{
		SetLightType(LightType.AMBIENT);
		SetVisibleDuringDaylight(true);
		SetLifetime(0.07);
		SetFadeOutTime(0.02);
		SetCastShadow(true);
		
		SetDiffuseColor(0.3, 0.3, 1);	
		SetAmbientColor(0.3, 0.3, 1);	
		SetBrightnessTo(25);
		SetRadiusTo(1200);
		SetFlareVisible(true);
	}
}