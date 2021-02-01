class ER7_Scope_View: ScriptViewTemplate<ER7_Scope_View_Controller>
{	
	void OnTimer(ER7_Scope scope)
	{
		GetTemplateController().OnTimer(scope);
	}
	
	override string GetLayoutFile()
	{
		return "Namalsk_Weapon/GaussMk2/GUI/layouts/gauss_scope.layout";
	}
}