static const ref array<string> GAUSS_LIGHTNING_BOLT_TYPES = { "vfx_gauss_thunderboltnorm", "vfx_gauss_thunderboltheavy" };

class ER7_Gauss: FAL_Base
{
	override void EEFired(int muzzleType, int mode, string ammoType)
	{
		Print("EEFired");
		super.EEFired(muzzleType, mode, ammoType);
		
		if (GetGame().IsClient() || !GetGame().IsMultiplayer()) {
			
			//for (int i = 0; i < 10; i++) {
				vector pos = GetPosition();
				//vector ori = 180 * Vector(Math.RandomFloat01(), Math.RandomFloat01(), Math.RandomFloat01());
				float scl = GetScale() * 0.005;
				thread CreateFireBolt(pos, vector.Zero, scl);
			//}
			
			Print("Pew electric effects!");
		}
		
	}
	
	override bool JamCheck(int muzzleIndex)
	{ 
		bool jam_check = false;
		return (super.JamCheck(muzzleIndex) && jam_check);
	}
	
	override bool CanFire()
	{
		bool has_energy = false;
		
		Print(GetGame().IsClient());
		Print(GetGame().IsServer());
		
		Print(GetCompEM());
		if (GetCompEM().GetEnergySource() && GetCompEM().GetEnergySource().GetCompEM()) {
			Print(GetCompEM().GetEnergySource().GetCompEM().GetEnergy());
		}
		
		
		
		return (super.CanFire() && has_energy);
	}
	
	private void CreateFireBolt(vector position, vector orientation, float scale)
	{
		Print("CreateFireBolt " + position);
		Object bolt = GetGame().CreateObjectEx(GAUSS_LIGHTNING_BOLT_TYPES.GetRandomElement(), position, ECE_LOCAL);
		if (!bolt) return;
		bolt.SetOrientation(orientation);
		bolt.SetScale(scale);
		Sleep(25);
		GetGame().ObjectDelete(bolt);
	}
}