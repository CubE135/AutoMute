/*
* TeamSpeak 3 Auto Mute Plugin
*
* Copyright (c) 2018 CubE135.de
*/

#ifdef _WIN32
#pragma warning (disable : 4100)  /* Disable Unreferenced parameter warning */
#pragma warning (disable : 4996)  /* _CRT_SECURE_NO_WARNINGS */
#include <Windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "teamspeak/public_errors.h"
#include "teamspeak/public_errors_rare.h"
#include "teamspeak/public_definitions.h"
#include "teamspeak/public_rare_definitions.h"
#include "teamspeak/clientlib_publicdefinitions.h"
#include "ts3_functions.h"
#include "plugin.h"
#include <iostream>
#include <fstream>
#include <string>
#include <atlstr.h>

/* GUI */
#include "settings_qt.h"
settings* settings_ui = nullptr;

#include "about_qt.h"
about* about_ui = nullptr;

static struct TS3Functions ts3Functions;

#ifdef _WIN32
#define _strcpy(dest, destSize, src) strcpy_s(dest, destSize, src)
#define snprintf sprintf_s
#else
#define _strcpy(dest, destSize, src) { strncpy(dest, src, destSize-1); (dest)[destSize-1] = '\0'; }
#endif

#define PLUGIN_API_VERSION 23

#define PATH_BUFSIZE 512
#define COMMAND_BUFSIZE 128
#define INFODATA_BUFSIZE 128
#define SERVERINFO_BUFSIZE 256
#define CHANNELINFO_BUFSIZE 512
#define RETURNCODE_BUFSIZE 128

static char* pluginID = NULL;

/* Basic Configuration */
char pluginName[] = "AutoMute";
char pluginDescription[] = "AutoMute will let you choose, if you want to join servers muted. It will automaticly mute your mic and your speakers when you join a server.";
char pluginAuthor[] = "CubE";
char pluginVersion[] = "1.1.7";

/* Custom Function Declarations */
LPWSTR charToLPWSTR(char* text);
char* combineChars(char* text1, char* text2);
void refreshServerIdentifier(uint64 serverConnectionHandlerID);
void initGUI();
void shutdownGUI();
void openSettingsGUI();
void openAboutGUI();

#ifdef _WIN32
static int wcharToUtf8(const wchar_t* str, char** result) {
	int outlen = WideCharToMultiByte(CP_UTF8, 0, str, -1, 0, 0, 0, 0);
	*result = (char*)malloc(outlen);
	if (WideCharToMultiByte(CP_UTF8, 0, str, -1, *result, outlen, 0, 0) == 0) {
		*result = NULL;
		return -1;
	}
	return 0;
}
#endif

/*********************************** Required functions ************************************/
/*
* If any of these required functions is not implemented, TS3 will refuse to load the plugin
*/

const char* ts3plugin_name() {
#ifdef _WIN32
	static char* result = NULL;
	if (!result) {
		const wchar_t* name = charToLPWSTR(pluginName);
		if (wcharToUtf8(name, &result) == -1) {
			result = pluginName;
		}
	}
	return result;
#else
	return pluginName;
#endif
}

const char* ts3plugin_version() {
	return pluginVersion;
}

int ts3plugin_apiVersion() {
	return PLUGIN_API_VERSION;
}

const char* ts3plugin_author() {
	return pluginAuthor;
}

const char* ts3plugin_description() {
	return pluginDescription;
}

void ts3plugin_setFunctionPointers(const struct TS3Functions funcs) {
	ts3Functions = funcs;
}

int ts3plugin_init() {
	char appPath[PATH_BUFSIZE];
	char resourcesPath[PATH_BUFSIZE];
	char configPath[PATH_BUFSIZE];
	char pluginPath[PATH_BUFSIZE];

	ts3Functions.getAppPath(appPath, PATH_BUFSIZE);
	ts3Functions.getResourcesPath(resourcesPath, PATH_BUFSIZE);
	ts3Functions.getConfigPath(configPath, PATH_BUFSIZE);
	ts3Functions.getPluginPath(pluginPath, PATH_BUFSIZE, pluginID);

	initGUI();

	return 0;
}

void ts3plugin_shutdown() {
	shutdownGUI();

	if (pluginID) {
		free(pluginID);
		pluginID = NULL;
	}
}

/****************************** Optional functions ********************************/
/*
* Following functions are optional, if not needed you don't need to implement them.
*/

/*
 * If the plugin wants to use error return codes, plugin commands, hotkeys or menu items, it needs to register a command ID. This function will be
 * automatically called after the plugin was initialized. This function is optional. If you don't use these features, this function can be omitted.
 * Note the passed pluginID parameter is no longer valid after calling this function, so you must copy it and store it in the plugin.
 */
void ts3plugin_registerPluginID(const char* id) {
	const size_t sz = strlen(id) + 1;
	pluginID = (char*)malloc(sz * sizeof(char));
	_strcpy(pluginID, sz, id);
}

/* Plugin command keyword. Return NULL or "" if not used. */
const char* ts3plugin_commandKeyword() {
	return NULL;
}

/* Required to release the memory for parameter "data" allocated in ts3plugin_infoData and ts3plugin_initMenus */
void ts3plugin_freeMemory(void* data) {
	free(data);
}

/* Helper function to create a menu item */
static struct PluginMenuItem* createMenuItem(enum PluginMenuType type, int id, const char* text, const char* icon) {
	struct PluginMenuItem* menuItem = (struct PluginMenuItem*)malloc(sizeof(struct PluginMenuItem));
	menuItem->type = type;
	menuItem->id = id;
	_strcpy(menuItem->text, PLUGIN_MENU_BUFSZ, text);
	_strcpy(menuItem->icon, PLUGIN_MENU_BUFSZ, icon);
	return menuItem;
}

/* Some makros to make the code to create menu items a bit more readable */
#define BEGIN_CREATE_MENUS(x) const size_t sz = x + 1; size_t n = 0; *menuItems = (struct PluginMenuItem**)malloc(sizeof(struct PluginMenuItem*) * sz);
#define CREATE_MENU_ITEM(a, b, c, d) (*menuItems)[n++] = createMenuItem(a, b, c, d);
#define END_CREATE_MENUS (*menuItems)[n++] = NULL; assert(n == sz);

/* Menu IDs for this plugin */
enum {
	MENU_ID_AUTOMUTE_SETTINGS = 1,
	MENU_ID_AUTOMUTE_ABOUT
};

/* Plugin Menus */
void ts3plugin_initMenus(struct PluginMenuItem*** menuItems, char** menuIcon) {
	BEGIN_CREATE_MENUS(2);  /* IMPORTANT: Number of menu items must be correct! */
	CREATE_MENU_ITEM(PLUGIN_MENU_TYPE_GLOBAL, MENU_ID_AUTOMUTE_SETTINGS, "Settings", "settings.png");
	CREATE_MENU_ITEM(PLUGIN_MENU_TYPE_GLOBAL, MENU_ID_AUTOMUTE_ABOUT, "About", "about.png");
	END_CREATE_MENUS;

	/* Menu Icon */
	*menuIcon = (char*)malloc(PLUGIN_MENU_BUFSZ * sizeof(char));
	_strcpy(*menuIcon, PLUGIN_MENU_BUFSZ, "icon.png");
}

/************************** TeamSpeak callbacks ***************************/
/*
* Following functions are optional, feel free to remove unused callbacks.
* See the clientlib documentation for details on each function.
*/

/* Clientlib */
const char* ts3_identifier;
void ts3plugin_onConnectStatusChangeEvent(uint64 serverConnectionHandlerID, int newStatus, unsigned int errorNumber) {
	if (newStatus == STATUS_CONNECTION_ESTABLISHED) {
		refreshServerIdentifier(serverConnectionHandlerID);
		bool always_mute = settings_ui->getConfigOption("always_mute").toBool();
		bool mute_mic = settings_ui->getConfigOption("mute_mic").toBool();
		bool mute_speaker = settings_ui->getConfigOption("mute_speaker").toBool();
		QStringList list = settings_ui->getConfigOption("server_list").toStringList();

		if (always_mute || list.filter(ts3_identifier).length() > 0) {
			/* Microphone */
			if (mute_mic && ts3Functions.setClientSelfVariableAsString(serverConnectionHandlerID, CLIENT_INPUT_MUTED, "1") != ERROR_ok) {
				printf("Error setting client variable\n");
				return;
			}

			/* Speakers */
			if (mute_speaker && ts3Functions.setClientSelfVariableAsString(serverConnectionHandlerID, CLIENT_OUTPUT_MUTED, "1") != ERROR_ok) {
				printf("Error setting client variable\n");
				return;
			}

			/* Flush */
			if (ts3Functions.flushClientSelfUpdates(serverConnectionHandlerID, NULL) != ERROR_ok) {
				printf("Error flushing client updates");
			}
		}
	}
}

void ts3plugin_onMenuItemEvent(uint64 serverConnectionHandlerID, enum PluginMenuType type, int menuItemID, uint64 selectedItemID) {
	switch (type) {
	case PLUGIN_MENU_TYPE_GLOBAL:
		switch (menuItemID) {
		case MENU_ID_AUTOMUTE_SETTINGS: {
			refreshServerIdentifier(serverConnectionHandlerID);

			openSettingsGUI();
			break; }
		case MENU_ID_AUTOMUTE_ABOUT: {
			openAboutGUI();
			break; }
		default:
			break;
		}
		break;
	default:
		break;
	}
}

/* Custom Functions */
/* Convert char to LPWSTR */
LPWSTR charToLPWSTR(char* text) {
	static wchar_t wtext[PATH_BUFSIZE];
	mbstowcs(wtext, text, strlen(text) + 1);
	static LPWSTR textLPWSTR = wtext;

	return textLPWSTR;
}

/* Combine two chars */
char* combineChars(char* text1, char* text2) {
	static char buffer[PATH_BUFSIZE];
	strncpy_s(buffer, text1, sizeof(buffer));
	strncpy_s(buffer, text2, sizeof(buffer));

	return buffer;
}

/* Update Identifier */
void refreshServerIdentifier(uint64 serverConnectionHandlerID) {
	ts3Functions.requestServerVariables(serverConnectionHandlerID);
	char* ident;
	if (ts3Functions.getServerVariableAsString(serverConnectionHandlerID, VIRTUALSERVER_UNIQUE_IDENTIFIER, &ident) == ERROR_ok) {
		ts3_identifier = ident;
	}
}

/* Initiate GUI's */
void initGUI() {
	char path[128];
	ts3Functions.getConfigPath(path, 128);

	if (settings_ui == nullptr) {
		settings_ui = new settings(QString::fromUtf8(path));
	}

	if (about_ui == nullptr) {
		about_ui = new about();
	}
}

/* Shutdown GUI's */
void shutdownGUI() {
	if (settings_ui) {
		settings_ui->close();
		delete settings_ui;
		settings_ui = nullptr;
	}

	if (about_ui) {
		about_ui->close();
		delete about_ui;
		about_ui = nullptr;
	}
}

/* Open/Show Settings GUI */
void openSettingsGUI() {
	if (settings_ui->isVisible()) {
		settings_ui->raise();
		settings_ui->activateWindow();
	} else {
		settings_ui->show();
	}
}

/* Open/Show About GUI */
void openAboutGUI() {
	if (about_ui->isVisible()) {
		about_ui->raise();
		about_ui->activateWindow();
	} else {
		about_ui->show();
	}
}