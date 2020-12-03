static const ref array<string> GAUSS_LIGHTNING_BOLT_TYPES = { "vfx_gauss_thunderboltnorm", "vfx_gauss_thunderboltheavy" };


class ER7_Gauss_Fire_Light: ScriptedLightBase
{
	void ER7_Gauss_Fire_Light()
	{
		FadeOut(1);
		SetBrightnessTo(1000);
		SetRadiusTo(500);
	}
}

class ER7_Gauss : FAL_Base
{
	override void EEFired(int muzzleType, int mode, string ammoType)
	{
		Print("EEFired");
		super.EEFired(muzzleType, mode, ammoType);
			
		if (GetGame().IsClient() || !GetGame().IsMultiplayer()) {
			thread CreateBolts();
			
			ScriptedLightBase.CreateLight(ER7_Gauss_Fire_Light, ModelToWorld(GetMemoryPointPos("usti hlavne")));
			
		}
	}
	
	private void CreateBolts()
	{		
		for (int i = 0; i < 8; i++) {			
			vector position = ModelToWorld(GetMemoryPointPos("usti hlavne"));
			vector orientation = 180 * Vector(Math.RandomFloat01(), Math.RandomFloat01(), Math.RandomFloat01());
			float scale = GetScale() * 0.008;
			Object bolt = GetGame().CreateObjectEx(GAUSS_LIGHTNING_BOLT_TYPES.GetRandomElement(), position, ECE_LOCAL);
 			
			if (bolt) {
	 			bolt.SetOrientation(orientation);
	 			bolt.SetScale(scale);
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(GetGame().ObjectDelete, Math.RandomInt(15, 35), false, bolt);
			}
			
			Sleep(10);
		}
	}
}