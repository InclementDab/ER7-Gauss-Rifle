static const ref array<string> GAUSS_LIGHTNING_BOLT_TYPES = { "vfx_gauss_thunderboltnorm", "vfx_gauss_thunderboltheavy" };


class ER7_Gauss : FAL_Base
{
	override void EEFired(int muzzleType, int mode, string ammoType)
	{
		Print("EEFired");
		super.EEFired(muzzleType, mode, ammoType);
	
		if (GetGame().IsClient() || !GetGame().IsMultiplayer()) {
		
			for (int i = 0; i < 10; i++) {
				vector pos = GetPosition();
				vector ori = 180 * Vector(Math.RandomFloat01(), Math.RandomFloat01(), Math.RandomFloat01());
				float scl = GetScale() * 0.01;
				CreateFireBolt(pos, ori, scl);
			}
		
			Print("Pew electric effects!");
		}
	}
	
 	private void CreateFireBolt(vector position, vector orientation, float scale)
 	{
 		Print("CreateFireBolt " + position);
 		Object bolt = GetGame().CreateObjectEx(GAUSS_LIGHTNING_BOLT_TYPES.GetRandomElement(), position, ECE_LOCAL);
 		if (!bolt) return;
 		bolt.SetOrientation(orientation);
 		bolt.SetScale(scale);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(GetGame().ObjectDelete, 25, false, bolt);
 	}
}