#include "stdafx.h"
#include "Editor.h"

#include "Windows/MainWindow.h"
#include <QtGui/QApplication>
#include <QtGui/QWindowsVistaStyle.h>

#include <beLauncher/beInitEngine.h>
#include <beCore/beFileSystem.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

#ifdef QT_STYLE_WINDOWSVISTA
	QApplication::setStyle(new QWindowsVistaStyle());
#endif

	beLauncher::InitializeLog("Logs/breezEd.log");
	beLauncher::InitializeFilesystem();

	// Default directory configuration
	if (!beCore::FileSystem::Get().HasLocation("Effects"))
		beCore::FileSystem::Get().AddPath("Effects", "Data/Effects/2.0");
	if (!beCore::FileSystem::Get().HasLocation("EffectCache"))
		beCore::FileSystem::Get().AddPath("EffectCache", "Data/Effects/Cache/2.0");
	if (!beCore::FileSystem::Get().HasLocation("Textures"))
		beCore::FileSystem::Get().AddPath("Textures", "Data/Textures");
	if (!beCore::FileSystem::Get().HasLocation("Materials"))
		beCore::FileSystem::Get().AddPath("Materials", "Data/Materials");
	if (!beCore::FileSystem::Get().HasLocation("Meshes"))
		beCore::FileSystem::Get().AddPath("Meshes", "Data/Meshes");
	if (!beCore::FileSystem::Get().HasLocation("Maps"))
		beCore::FileSystem::Get().AddPath("Maps", "Data/Maps");

	Editor e;
	e.mainWindow()->show();
	
	return a.exec();
}
